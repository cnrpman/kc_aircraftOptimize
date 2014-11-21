#include "calculator.h"

#include <iostream>

using namespace std;

void cal_dataReady(string msg){//从query载入需要数据
    stringstream st;
    st.str(msg);

    //read the query airDominance
    st>>airDomin;

    //read carrier
    int carrierNum;
    st>>carrierNum;
    string tmpName;
    int tmpAvailGrid,tmpAvailBit;
    for(int i=0;i<carrierNum;i++){
        st>>tmpName>>tmpAvailBit;
        int tmpCarrierID=carriers_m[tmpName];
        int tmpCarrierGridNum=carriers[tmpCarrierID].getGridNum();
        int bit=1;
        //insert grid
        for(int j=0;j<tmpCarrierGridNum;j++)
            if(tmpAvailBit&bit)//bit arithmatic judge if the grid available
                gridVec.push_back(Grid(i,j,carriers[tmpCarrierID].getGridSize(j),carriers[tmpCarrierID].getAtk()));
            bit<<=1;
    }
//    for(int i=0;i<gridVec.size();i++)
//        cout<<gridVec[i]<<endl;

    //read plane
    int planeTypeNum;
    st>>planeTypeNum;
    for(int i=0;i<planeTypeNum;i++){
        st>>tmpName;
        int tmpPlaneID=planes_m[tmpName];
        int tmpNum;
        st>>tmpNum;
        for(int i=0;i<tmpNum;i++)
            planeVec.push_back(planes[tmpPlaneID]);
    }
    for(int i=0;i<planeVec.size();i++)
        cout<<planeVec[i]<<endl;
}

bool cal_cmp_grid(const Grid &a,const Grid &b){
    return a.gridSize>b.gridSize;
}

bool cal_cmp_plane(Plane a,Plane b){
    return a.getAirDominance()>b.getAirDominance();
}

bool cal_cmp_plane_damage(Plane a,Plane b){
    return formulaDamage(a)>formulaDamage(b);
}

//TODO
double formulaDamage(Plane &item){
    double res=item.getBombAtk()*2+item.getTorpedoAtk()*1.5;
    return res;
}

double formulaDamageOP(int gridSize,Plane &item){
    double res=0;
    int cate=item.getCategoryID();
    if(cate==PLANE_TORPEDO_ATTACKER)
        res=(item.getTorpedoAtk()*sqrt(gridSize)+25)*1.15;
    else if(cate==PLANE_BOMBER)
        res=item.getBombAtk()*sqrt(gridSize)+25;
    return res;
}

double formulaFighter(int gridSize,int airDominance){
    return sqrt(gridSize)*airDominance;
}

int fsign[32],asign[32],ResA;

double calDomi(int gridS){
    double res=0;
    int pi=0;
    for(int i=0;i<gridS;i++)
        if(fsign[i]==1){
            res+=formulaFighter(gridVec[i].gridSize,planeVec[pi].getAirDominance());
            pi++;
        }
    return res;
}

//formulaDamage()
//planeA vec 攻击机的顺序

double calAtk(int gridS){
    double res=0;
    int pi=0;
    for(int i=0;i<gridS;i++)
        if(asign[i]&1){
            res+=formulaDamageOP(gridVec[i].gridSize,planeVecA[pi]);
            pi++;
        }
    return res;
}

bool checkA(int curlv,int remainA,int gridS){//根据伤害剪枝
    if(remainA<0)return false;//not enough
    for(int i=0;i<remainA;i++)//尝试最优的攻击机装载
        asign[curlv+i]=1;

    bool answer=(calAtk(gridS)>ResA);//判断开幕攻击力

    for(int i=0;i<remainA;i++)//恢复
        asign[curlv+i]=0;

    return answer;
}

void copystatus(char *answer,int gridS){
    for(int i=0;i<gridS;i++){
        answer[i]=fsign[i]+'0'+asign[i]*2;
    }
    answer[gridS]='\0';
}

char answer[32],tmpch[32];
int thatair;

bool checkF(int curlv,int remainF,int gridS){//根据制空剪枝
    if(remainF<0)return false;//not enough
    for(int i=0;i<remainF;i++)//尝试最优的战斗机装载
        fsign[curlv+i]=1;

    bool answer=(calDomi(gridS)>=airDomin);//判断制空值

    for(int i=0;i<remainF;i++)//恢复
        fsign[curlv+i]=0;

    return answer;
}

//int baoliSearch(int curlv,int curF,int curA,int remainF,int remainA,int gridS){
void baoliSearch(int curlv,int remainF,int remainA,int gridS){
    if(curlv==gridS||(remainF==0&&remainA==0)){//递归出口
        if(calDomi(gridS)>=airDomin){
            ResA=max((int)calAtk(gridS),ResA);
            thatair=calDomi(gridS);
            copystatus(answer,gridS);
        }
        return;
    }
    if(remainF){//try fighter
        fsign[curlv]=1;
//        if(checkA(curlv+1,curF+1,remainF-1,gridS)&&checkB(curlv+1,curA,remainA,gridS))
//            baoliSearch(curlv+1,curF+1,curA,remainF-1,remainA,gridS);
        if(checkF(curlv+1,remainF-1,gridS)&&checkA(curlv+1,remainA,gridS))//剪枝
            baoliSearch(curlv+1,remainF-1,remainA,gridS);
        fsign[curlv]=0;
    }
    if(remainA){
        asign[curlv]=1;
//        if(checkA(curlv+1,curF,remainF,gridS)&&checkB(curlv+1,curA+1,remainA-1,gridS))
//            baoliSearch(curlv+1,curF,curA+1,remainF,remainA-1,gridS);
        if(checkF(curlv+1,remainF,gridS)&&checkA(curlv+1,remainA-1,gridS))//剪枝
            baoliSearch(curlv+1,remainF,remainA-1,gridS);
        asign[curlv]=0;
    }
}

bool cal_run(){//if available result
    double curAir=0.0;
    //fighter greedy
    sort(gridVec.begin(),gridVec.end(),cal_cmp_grid);
    sort(planeVec.begin(),planeVec.end(),cal_cmp_plane);

    int gsz=gridVec.size(),fn=0,nn=0,psz=planeVec.size();
    for(int i=0;i<gsz;i++){//get fighter need
        if(curAir>=airDomin||i>psz)break;
        if(planeVec[i].getCategoryID()==PLANE_FIGHTER){
            curAir+=formulaFighter(gridVec[i].gridSize,planeVec[i].getAirDominance());
            fn++;
        }
    }
    for(int i=0;i<psz;i++)//get other have
        if(planeVec[i].getCategoryID()!=PLANE_FIGHTER)
            nn++;

    if(curAir<airDomin){
        cout<<"制空无法满足"<<endl;
        return false;
    }
    cout<<fn<<" "<<nn<<endl;

    //search data prepare
    planeVecA=planeVec;
    sort(planeVecA.begin(),planeVecA.end(),cal_cmp_plane_damage);
    memset(fsign,0,sizeof(fsign));
    memset(asign,0,sizeof(asign));
    ResA=0;
    //search
    baoliSearch(0,fn,nn,gsz);
    cout<<"AD: "<<thatair<<" Atk: "<<ResA<<" "<<answer<<endl;

    return true;
}

string answer_c[6][4];

string &cal_get_res(){
    int f=0,a=0;
    for(int i=0;i<6;i++)
        for(int j=0;j<4;j++)
            answer_c[i][j]=" - ";

    for(int i=0;answer[i]!='\0';i++){
        Grid curg=gridVec[i];
//        cout<<curg.carrierPos<<" "<<curg.gridPos<<endl;
        if(answer[i]=='1'){
            answer_c[curg.carrierPos][curg.gridPos]=planeVec[f].getName();
            f++;
        }
        else if(answer[i]=='2'){
            answer_c[curg.carrierPos][curg.gridPos]=planeVecA[f].getName();
            a++;
        }
    }

    stringstream stmp;
    for(int i=0;i<6;i++){
        for(int j=0;j<4;j++)
            stmp<<answer_c[i][j]<<" ";
        stmp<<endl;
    }
    string *ret=new string();
    *ret=stmp.str();
    return *ret;
}

ostream &operator<<(ostream &os,Grid &item){
    os<<item.carrierPos<<" "<<item.gridPos<<" "<<item.gridSize<<" "<<item.carrierAtk;
    return os;
}
