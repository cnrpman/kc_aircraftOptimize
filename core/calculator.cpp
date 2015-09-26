#include "calculator.h"

using namespace std;

//interior vars
int attackerAbleGridNum;
int sign[32],resSign[32];
int curBomberNum,curFighterNum,curAssign[16],curAssignGrid[16];
int resAS=0,resAssignGrid[16],resAssign[16],resOPAtk=0,resBomberNum;
float resAtk=-1.0;
bool flushFlag;
std::chrono::time_point<std::chrono::system_clock> logtime;
std::chrono::microseconds restime;

inline bool checkIfFighterOnly(int gridSize,int LAS, int IFO){
    if(IFO||gridSize<LAS)return true;
    else return false;
}

void cal_dataReady(stringstream &st){//从query载入需要数据
    int leastAttackerSz;
    st>>tarAirSupremacy>>op_coef>>accu_coef>>leastAttackerSz>>armor>>nearing_coef;

    armor_max=armor*(4.0/3);
    armor_min=armor*(2.0/3);
    //read carrier
    st>>carrierNum;
    string tmpName;
    int tmpAvailBit,ifFighterOnly;
    for(int i=0;i<carrierNum;i++){
        st>>tmpName>>tmpAvailBit>>ifFighterOnly;
        int tmpCarrierID=carriers_m[tmpName];
        int tmpCarrierGridNum=carriers[tmpCarrierID].gridNum;
        theCarrier.push_back(carriers[tmpCarrierID]);
        int bit=1<<(4-tmpCarrierGridNum);
        //insert grid
        availGrid[i]=0;

        for(int j=tmpCarrierGridNum-1;j>=0;j--){
            if(tmpAvailBit&bit){//bit arithmatic judge if the grid available
                int &tmpGridSize=carriers[tmpCarrierID].gridSize[j];
                gridVec.push_back(Grid(i,j,tmpGridSize,carriers[tmpCarrierID].atk,checkIfFighterOnly(tmpGridSize,leastAttackerSz,ifFighterOnly)));
                if(!gridVec.back().isFighterOnly){
                    availGrid[i]++;
                    attackerAbleGridNum++;
                }
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
            res+=(planeVecF[iterFighter].category == PLANE_FIGHTER?25:3) + formulaFighter(gridVec[i].gridSize,planeVecF[iterFighter].airSupremacy);
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
            res+=(planeVecF[iterFighter].category == PLANE_FIGHTER?25:3)+formulaFighter(gridVec[i].gridSize,planeVecF[iterFighter].airSupremacy);
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
        if(restime=std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now()-logtime),restime.count()>TLE*1000000){
            cout<<"ERROR:TLE"<<endl;
            exit(0);
        }
        int tAssignN[4] = {0, 0, 0, 0};
        getAssignN(tAssignN, gridSz);//sav avail grids num to ships
        BelongStructure &curres=dpRes[tAssignN[0]][tAssignN[1]][tAssignN[2]][tAssignN[3]];
        vector<int *> &tlist=curres.belongings;
        int i=0;
        for(vector<int *>::iterator iter=tlist.begin(),end=tlist.end();iter!=end;++iter){
            getCurAssign(iter);
            float newAtk = curres.as[i++] + op_coef * calOPAtk(gridSz);
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
        }
        return;
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

bool cal_run(){//if available result
    auto starttime=std::chrono::system_clock::now();
    logtime=starttime;
    //prepare
    int gridSz=gridVec.size(),planeSz=planeVec.size();
    sort(gridVec.begin(),gridVec.end(),cal_cmp_grid);

    //choose fighters.
    int minFighterNum=-1,maxFighterNum=0;

    sort(planeVec.begin(),planeVec.end(),cal_cmp_plane_AS);

    //cal min
    float tAS=PRESET_AS_OF_BOMBER;//AirSupermacy Val
    if(tAS>=tarAirSupremacy)minFighterNum=0;
    for(int i=0;i<gridSz&&i<planeSz;i++){
        tAS+=(planeVec[i].category == PLANE_FIGHTER?25:3)+formulaFighter(gridVec[i].gridSize,planeVec[i].airSupremacy);
        if(tAS>=tarAirSupremacy&&minFighterNum==-1){
            minFighterNum=i+1;
        }
    }
    //cal max
    tAS=0;
    for(int i=0;i<gridSz&&i<planeSz;i++){
        if(planeVec[i].airSupremacy!=0){
            maxFighterNum++;
            tAS+=(planeVec[i].category == PLANE_FIGHTER?25:3)+formulaFighter(gridVec[i].gridSize,planeVec[i].airSupremacy);
            planeVecF.push_back(planeVec[i]);
        }

    }
    if(tAS<tarAirSupremacy){
        cout<<"ERROR:FighterPower unreachable.Currently reachable FighterPower: "<<tAS<<endl;
        return false;
    }
    maxFighterNum=min(maxFighterNum,minFighterNum+10);

    //for all possibility
    for(curFighterNum=minFighterNum;curFighterNum<=maxFighterNum;curFighterNum++){
        for(int i=0;i<curFighterNum;i++)
            if(planeVec[i].category!=PLANE_FIGHTER) break; //not enough
        //choose bombers.
        planeVecA.clear();
        for(int i=0;i<planeSz;i++){
            Plane &tplane=planeVec[i];
            if(tplane.category==PLANE_BOMBER||tplane.category==PLANE_TORPEDO_ATTACKER)
                planeVecA.push_back(tplane);
        }
        sort(planeVecA.begin(),planeVecA.end(),cal_cmp_plane_damage);
        curBomberNum=min(gridSz-curFighterNum,(int)planeVecA.size());
        curBomberNum=min(curBomberNum,attackerAbleGridNum);
        flushFlag=1;//if copy resVecA
//        cout<<curBomberNum<<endl;
//        if(curBomberNum>CBN_LIMIT){
//            cout<<"ERROR:Too much bomber, curBomberNum: "<<curBomberNum<<"  LIMIT: "<<CBN_LIMIT-1<<endl;
//            return false;
//        }

//        cout<<curBomberNum<<endl;
        sort(planeVecA.begin(),planeVecA.begin()+curBomberNum,cal_cmp_plane_damageOP);

        //dfs all bombers assignments
        atkdp(curBomberNum);
//        cout<<"dp finished"<<endl;
        // 0-1 search
        memset(sign,0,sizeof(sign));
        baoliSearch(0,curFighterNum,curBomberNum,gridSz);
    }
    restime=std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - starttime);

    return true;
}

string answer_c[6][4],answer_n[6][4];
char tmp[200];

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
        for(int j=0;j<4;j++){
            answer_c[i][j]=" - ";
            answer_n[i][j]=" - ";
        }
    int f=0;
    for(int i=0;resSign[i]!='\0';i++){
        Grid &tGrid=gridVec[i];
        if(resSign[i]=='1'){
            answer_c[tGrid.carrierPos][tGrid.gridPos]=planeVecF[f].name;
            answer_n[tGrid.carrierPos][tGrid.gridPos]=" - ";
            f++;
        }
    }

    int shipHit[6];
    float shipAtk[6];
    memset(shipAtk,0,sizeof(shipAtk));
    memset(shipHit,0,sizeof(shipHit));
    for(int i=0;i<resBomberNum;i++){
        answer_c[resAssign[i]][resAssignGrid[i]]=ResPlaneVecA[i].name;
        answer_n[resAssign[i]][resAssignGrid[i]] = formula_damageOP_str(theCarrier[resAssign[i]].gridSize[resAssignGrid[i]],ResPlaneVecA[i]);

        shipAtk[resAssign[i]] += formulaDamage(ResPlaneVecA[i]);
        shipHit[resAssign[i]] += ResPlaneVecA[i].accuracy;
    }

    stringstream &stmp=*(new stringstream());
    for(int i=0;i<6;i++){
        for(int j=0;j<4;j++)
            stmp<<answer_c[i][j]<<"|";
        stmp<<endl;
    }
    for(int i=0;i<6;i++){
        for(int j=0;j<4;j++)
            stmp<<answer_n[i][j]<<"|";
        if(shipAtk[i] == 0){
            stmp<<" - | - |"<<endl;
            continue;
        }
        int rd = formula_shipAtk_rawDamage(shipAtk[i], theCarrier[i].atk);
        stmp<<formula_shipAtk_cocurHeading(rd)<<'|'<<formula_shipAtk_invertHeading(rd)<<'|'<<endl;
    }

    cout<<"AS: "<<resAS<<" Atk: "<<resAtk<<" time: "<<(restime.count()/1000.0)<<" ms"<<endl;

    return stmp;
}

ostream &operator<<(ostream &os,Grid &item){
    os<<item.carrierPos<<" "<<item.gridPos<<" "<<item.gridSize<<" "<<item.carrierAtk;
    return os;
}
