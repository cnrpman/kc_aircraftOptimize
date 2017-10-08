kc_aircraftOptimize
===================  
这是一个为网页游戏KantaiCollection设计的计算工具.  
可以根据给定的空母和舰载机配置, 计算出满足指定制空值的伤害优化方案.  

## Install ##  
可以使用code:blocks打开目录下的.cbp文件直接编译, 需要打开c++11选项
或通过Cmake进行编译

## Usage ##  
Query Format:  
`制空值 开幕系数 命中系数 最小限制 敌方装甲 空母数 冗余系数 (空母 装备掩码 是否罚站)x空母数 飞机数 (飞机 数量)x飞机数`  

具体查询Sample可见每次查询后返回的show query或目录下的query.txt

## Directory ##

        ├─main  界面
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
DEBUG --从query.txt读入查询, 而不是arg  

## Method ##
Searching Strategy:  
1. 做一个Greedy抽取出要使用的飞机(留出余量，多次尝试不同的舰战数量)
2. 搜出飞机数一定时, 空母对舰攻/舰爆可以最大化炮击伤害较优的Selection(带Pruning), 记录每个空母拥有的舰攻/舰爆及火力值
3. 根据slot放置舰战或是舰攻舰爆, 做01搜索。 利用制空值做Prune, 搜索出口根据2.中记录的解加上贪心排出的飞机摆放顺序做伤害检查
