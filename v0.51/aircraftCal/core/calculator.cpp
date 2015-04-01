#include "calculator.h"

using namespace std;

//interior vars
int attackerAbleGridNum;
int sign[32],resSign[32];
int curBomberNum,curFighterNum,curAssign[16],curAssignGrid[16];
int resAS=0,resAssignGrid[16],resAssign[16],resOPAtk=0,resBomberNum;
float resAtk=-1.0;
bool flushFlag;

inline bool checkIfFighterOnly(int gridSize,int LAS, int IFO){
    if(IFO||gridSize<LAS)return true;
    else return false;
}

void cal_dataReady(stringstream &st){//从query载入需要数据
    int leastAttackerSz;
    st>>tarAirSupremacy>>op_coef>>accu_coef>>leastAttackerSz>>armor;
    //read carrier
    st>>carrierNum;
    string tmpName;
    int tmpAvailBit,ifFighterOnly;
    for(int i=0;i<carrierNum;i++){
        st>>tmpName>>tmpAvailBit>>ifFighterOnly;
        int tmpCarrierID=carriers_m[tmpName];
        int tmpCarrierGridNum=carriers[tmpCarrierID].gridNum;
        theCarrier.push_back(carriers[tmpCarrierID]);
        int bit=1;
        //insert grid
        availGrid[i]=0;
        for(int j=tmpCarrierGridNum-1;j>=0;j--){
            if(tmpAvailBit&bit){//bit arithmatic judge if the grid available
                int &tmpGridSize=carriers[tmpCarrierID].gridSize[j];
                gridVec.push_back(Grid(i,j,tmpGridSize,carriers[tmpCarrierID].atk,checkIfFighterOnly(tmpGridSize,leastAttackerSz,ifFighterOnly)));
                availGrid[i]++;
                if(!gridVec.back().isFighterOnly)
                    attackerAbleGridNum++;
            }
            bit<<=1;
        }
    }

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
}


inline int calASofBomber(int gridS){
    int res=0;
    for(int i=0;i<curBomberNum;i++){
        if(planeVecA[i].airSupremacy)
            res+=formulaFighter(theCarrier[curAssign[i]].gridSize[curAssignGrid[i]],planeVecA[i].airSupremacy);
    }
//    cout<<"returning"<<endl;
    return res;
}

inline int calAS(int gridS){
    int res=0;
    int iterFighter=0;
    for(int i=0;i<gridS;i++){
        if(iterFighter>=curFighterNum)break;
        if(sign[i]==1){//notset or fighter
            res+=formulaFighter(gridVec[i].gridSize,planeVecF[iterFighter].airSupremacy);
            iterFighter++;
        }
    }
    return res;
}

inline int calASpredict(int gridS){
    int res=0;
    int iterFighter=0;
    for(int i=0;i<gridS;i++){
        if(iterFighter>=curFighterNum)break;
        if(sign[i]==1||sign[i]==0){//notset or fighter
            res+=formulaFighter(gridVec[i].gridSize,planeVecF[iterFighter].airSupremacy);
            iterFighter++;
        }
    }
    return res;
}

inline float calOPAtk(int gridS){
    int pickuped[16];
    memset(pickuped,0,sizeof(pickuped));
    float res=0;

    int f=0;
    for(int i=0;i<gridS;i++){
        if(sign[i]==2){
            for(int j=0;j<curBomberNum;j++){
                if(gridVec[i].carrierPos==curAssign[j]&&(!pickuped[j])){
                    res+=formulaDamageOP(gridVec[i].gridSize,planeVecA[j]);
                    pickuped[j]=1;
                    curAssignGrid[j]=gridVec[i].gridPos;
                    break;
                }
            }
        }
        else if(sign[i]==1){
            res+=formulaDamageOP(gridVec[i].gridSize,planeVecF[f++]);
        }
    }
    return res;
}

inline bool cutF(int curlv,int remainF,int gridS){
    return calASpredict(gridS)+PRESET_AS_OF_BOMBER>=tarAirSupremacy;//判断制空值
}

inline void getAssignN(int tAssignN[],int gridS){
    for(int i=0;i<gridS;i++)
        if(sign[i]==2){
            tAssignN[gridVec[i].carrierPos]++;
        }
}

inline void getCurAssign(vector<int *>::iterator iter){//shiprem0~3,the kth belongings
    for(int i=0;i<16;i++)
        curAssign[i]=(*iter)[i];
}

inline float assignCalAtk(int tAssignN[]){
    return dpRes[tAssignN[0]][tAssignN[1]][tAssignN[2]][tAssignN[3]].biggestAtk;
}

inline int assignSz(int tAssignN[]){
    return dpRes[tAssignN[0]][tAssignN[1]][tAssignN[2]][tAssignN[3]].belongings.size();
}

inline void copySign2Res(int answer[],int gridS){
    for(int i=0;i<gridS;i++){
        answer[i]=sign[i]+'0';
    }
    answer[gridS]='\0';
}

inline void copyCurAssign2Res(int resAssign[],int resAssignGrid[]){
    for(int i=0;i<16;i++){
        resAssign[i]=curAssign[i];
        resAssignGrid[i]=curAssignGrid[i];
    }
}

void baoliSearch(int curlv,int remainF,int remainA,int gridSz){
    if(curlv == gridSz || (remainF == 0 && remainA == 0)){//递归出口
        int tAssignN[4] = {0, 0, 0, 0};
        getAssignN(tAssignN, gridSz);//sav avail grids num to ships
        vector<int *> &tlist=dpRes[tAssignN[0]][tAssignN[1]][tAssignN[2]][tAssignN[3]].belongings;
        for(vector<int *>::iterator iter=tlist.begin(),end=tlist.end();iter!=end;++iter){
            getCurAssign(iter);
            float newAtk = assignCalAtk(tAssignN) + op_coef * calOPAtk(gridSz);
            if(newAtk > resAtk){
                int newAS = calAS(gridSz) + calASofBomber(gridSz);
                if(newAS >= tarAirSupremacy){
                    //write cur data to res
                    resAtk = newAtk;
                    resAS = newAS;
                    resBomberNum = curBomberNum - remainA;
                    copySign2Res(resSign, gridSz);
                    copyCurAssign2Res(resAssign,resAssignGrid);

                    if(flushFlag){
                        ResPlaneVecA = planeVecA;
                        flushFlag = 0;
                    }
                }
            }
            return;
        }
    }
    if(remainF){//尝试放置战斗机，检测罚站
        sign[curlv]=1;
        baoliSearch(curlv+1,remainF-1,remainA,gridSz);
        sign[curlv]=0;
    }
    if(remainA){//尝试放置攻击机
        sign[curlv]=2;
        if(cutF(curlv+1,remainF,gridSz)){
            if(gridVec[curlv].isFighterOnly){
                sign[curlv]=0;
                baoliSearch(curlv+1,remainF,remainA,gridSz);
            }
            else baoliSearch(curlv+1,remainF,remainA-1,gridSz);
        }
        sign[curlv]=0;
    }
}

#ifdef WINDOWS
SYSTEMTIME t1;//记录暴搜时间
#endif

bool cal_run(){//if available result
    #ifdef WINDOWS
    GetLocalTime(&t1);
    memset(resAssign,0,sizeof(resAssign));
    #else
    gettimeofday(&starttime,0);
    #endif
    //prepare
    int gridSz=gridVec.size(),planeSz=planeVec.size();
    sort(gridVec.begin(),gridVec.end(),cal_cmp_grid);

    //choose fighters.
    int minFighterNum=-1,maxFighterNum=0;
    float maxAirSupremacy=0.0;//AirSupermacy Val
    sort(planeVec.begin(),planeVec.end(),cal_cmp_plane_AS);

    if(tarAirSupremacy==0)minFighterNum=0;
    for(int i=0;i<gridSz&&i<planeSz;i++){
        if(planeVec[i].airSupremacy!=0){
            maxFighterNum++;
            maxAirSupremacy+=formulaFighter(gridVec[i].gridSize,planeVec[i].airSupremacy);
            planeVecF.push_back(planeVec[i]);
        }
        if(maxAirSupremacy>tarAirSupremacy&&minFighterNum==-1){
                minFighterNum=i+1;
        }
    }
    if(maxAirSupremacy<tarAirSupremacy){
        cout<<"FighterPower unreachable.Currently reachable FighterPower: "<<maxAirSupremacy<<endl;
        return false;
    }
    maxFighterNum=min(maxFighterNum,minFighterNum+16);
    curFighterNum=minFighterNum;

    //for all possibility
    for(curFighterNum=(minFighterNum-1>0?minFighterNum-1:0);curFighterNum<=maxFighterNum;curFighterNum++){
        for(int i=0;i<curFighterNum;i++)
            planeVec[i].category=PLANE_FIGHTER; //set used AS plane as fighter.

        //choose bombers.
        planeVecA.clear();
        for(int i=0;i<planeSz;i++){
            Plane &tplane=planeVec[i];
            if(tplane.category==PLANE_BOMBER||tplane.category==PLANE_TORPEDO_ATTACKER)
                planeVecA.push_back(tplane);
        }
        sort(planeVecA.begin(),planeVecA.end(),cal_cmp_plane_damage);

//        for(int i=0;i<planeVecA.size();i++)
//            cout<<planeVecA[i]<<" "<<formulaDamageOP(49,planeVecA[i])<<endl;

        curBomberNum=min(gridSz-curFighterNum,(int)planeVecA.size());
        curBomberNum=min(curBomberNum,attackerAbleGridNum);
        flushFlag=1;//if copy resVecA
        if(curBomberNum>CBN_LIMIT){
            cout<<"Too much bomber, curBomberNum: "<<curBomberNum<<endl;
            return false;
        }

//        cout<<curBomberNum<<endl;
        sort(planeVecA.begin(),planeVecA.begin()+curBomberNum,cal_cmp_plane_damageOP);



        //dfs all bombers assignments
        atkdp(curBomberNum);

        // 0-1 search
        memset(sign,0,sizeof(sign));
        baoliSearch(0,curFighterNum,curBomberNum,gridSz);
    }

    return true;
}

string answer_c[6][4];

stringstream &cal_get_res(){
    #ifdef DEBUG2
    for(int i=0;i<planeVecA.size();i++)
        cout<<planeVecA[i];
    cout<<endl;
    for(int i=0;i<16;i++)
    cout<<resAssign[i]<<" ";
    cout<<endl;
    for(int i=0;i<16;i++)
    cout<<resAssignGrid[i]<<" ";
    cout<<endl;
    cout<<curBomberNum<<endl;
    #endif
    for(int i=0;i<6;i++)
        for(int j=0;j<4;j++)
            answer_c[i][j]=" - ";
    int f=0;
    for(int i=0;resSign[i]!='\0';i++){
        Grid &tGrid=gridVec[i];
        if(resSign[i]=='1'){
            answer_c[tGrid.carrierPos][tGrid.gridPos]=planeVecF[f].name;
            f++;
        }
    }
    for(int i=0;i<resBomberNum;i++)
        answer_c[resAssign[i]][resAssignGrid[i]]=ResPlaneVecA[i].name;

    stringstream &stmp=*(new stringstream());
    for(int i=0;i<6;i++){
        for(int j=0;j<4;j++)
            stmp<<answer_c[i][j]<<"|";
        stmp<<endl;
    }

    cout<<"AS: "<<resAS<<" Atk: "<<resAtk<<" ";
//    <<resSign<<" ";
    #ifdef WINDOWS
    SYSTEMTIME t2;
    GetLocalTime(&t2);
    cout<<(t2.wSecond-t1.wSecond)*1000+t2.wMilliseconds-t1.wMilliseconds<<"ms"<<endl;
    #else
    gettimeofday(&endtime,0);
    float timeuse=1000000*(endtime.tv_sec-starttime.tv_sec)+endtime.tv_usec-starttime.tv_usec;
    timeuse/=1000;
    cout<<"time: "<<timeuse<<" ms";
    #endif
    cout<<endl;

    return stmp;
}

ostream &operator<<(ostream &os,Grid &item){
    os<<item.carrierPos<<" "<<item.gridPos<<" "<<item.gridSize<<" "<<item.carrierAtk;
    return os;
}
