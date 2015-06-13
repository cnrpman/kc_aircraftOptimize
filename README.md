kc_aircraftOptimize
===================
v0.11 只根据开幕优化的版本(2014.11)  
v0.2-0.4 炮击优先逻辑版本，已被取代  
v0.52 当前运行的版本(2015.4)

查询格式:
制空值 开幕系数 命中系数 最小限制 敌方装甲 空母数 冗余系数 (空母 装备掩码 是否罚站){空母数} 飞机数 (飞机 数量){飞机数}  

具体查询Sample可见每次查询后返回的show query或目录下的query.txt


        ├─main  临时界面
        │
        └─core
           ├─predef        预设常量
           │
           ├─io            从P_DAT和C_DAT读入航母&舰载机设定
           │
           ├─calculator    主体计算逻辑
           ├─formulation   公式，内联的公式定义在formular_inline.h中
           ├─atkdp         对炮击伤害的搜索
           ├─belongingStructure  存放炮击伤害搜索结果的数据结构
           │
           ├─grid          航母格子类
           ├─Carrier
           ├─Plane
           │
           └─gobal

core/predef.h下的define:  
DEBUG -- 将输入从query.txt读入查询而不是shell  
WINDOWS -- 是否windows  

搜索策略：
I.先做一个贪心抽取出要使用的飞机(留出余量)  
II.然后先根据组合搜出所有的空母对舰攻/舰爆的选择一定的飞机数时炮击伤害较优的一些解(没做剪枝，也是留有一定的余量)根据每个空母拥有的舰攻/舰爆数做状态记忆 (<4^12)  
III.最后根据某个格子是选取舰战亦或是舰攻舰爆做01搜索+根据制空稍微剪一下，搜索出口根据II记录的解加上贪心排出的飞机摆放顺序做伤害的检查 (2^16*II中对应状态的解数)  
