# **实验：硬件编程–机器指令编程**
18342136 赵嘉仪  
<!-- TOC -->

- [**实验：硬件编程–机器指令编程**](#实验硬件编程机器指令编程)
    - [**一、实验名称**: 硬件编程–机器指令编程](#一实验名称-硬件编程机器指令编程)
    - [**二、实验目标** :](#二实验目标-)
    - [**三、实验步骤：**](#三实验步骤)
        - [1.安装win7虚拟机配置实验环境](#1安装win7虚拟机配置实验环境)
        - [2. 使用简单 CPU 仿真工具 Pippin CPUSim 进行实验](#2-使用简单-cpu-仿真工具-pippin-cpusim-进行实验)
            - [TASK 1 **Program 1：Add 2 number**](#task-1-program-1add-2-number)
                - [(1) 点step after step。观察并回答下面问题：](#1-点step-after-step观察并回答下面问题)
                - [(2) 点击“Binary”,观察回答下面问题](#2-点击binary观察回答下面问题)
            - [TASK 2 **PROGRAM 2:Count down loop**](#task-2-program-2count-down-loop)
                - [(1) 输入程序Program 2，运行并回答问题：](#1-输入程序program-2运行并回答问题)
                - [(2) 修改该程序，用机器语言实现 10+9+8+..1 ，输出结果存放于内存 Y](#2-修改该程序用机器语言实现-10981-输出结果存放于内存-y)
    - [**四、实验小结**](#四实验小结)

<!-- /TOC -->
## **一、实验名称**: 硬件编程–机器指令编程   
## **二、实验目标** :
* 理解冯·诺伊曼计算机的结构
* 理解机器指令的构成
* 理解机器指令执行周期
* 用汇编编写简单程序
## **三、实验步骤：**
### 1.安装win7虚拟机配置实验环境
[Download virtual machines  
Test Microsoft Edge and versions of IE8 through IE11 using free virtual machines you download and manage locally.](https://developer.microsoft.com/en-us/microsoft-edge/tools/vms/)

### 2. 使用简单 CPU 仿真工具 Pippin CPUSim 进行实验
[Pippin CPUSim](http://www.science.smith.edu/~jcardell/Courses/CSC103/CPUsim/cpusim.html)

#### TASK 1 **Program 1：Add 2 number**  
##### (1) 点step after step。观察并回答下面问题：  
    1. PC，IR 寄存器的作用。  
    2. ACC 寄存器的全称与作用。  
    3. 用“LOD #3”指令的执行过程，解释Fetch-Execute周期。  
    4. 用“ADD W” 指令的执行过程，解释Fetch-Execute周期。  
    5. “LOD #3” 与 “ADD W” 指令的执行在Fetch-Execute周期级别，有什么不同。


1. PC:存放下一条要执行的指令
IR：指令寄存器（Instruction Register），是临时放置从内存里面取得的程序指令的寄存器，用于存放当前从主存储器读出的正在执行的一条指令。
2. ACC：
ACC 寄存器全称为 accumulator。
累加器 (accumulator) 用来储存计算产生的中间结果。
3. 
    **3.1 Fetch instruction:**   
从PC中读取下一条指令的地址，访问PC中的内存地址，复制其中内容，将副本放入指令寄存器（IR）中。  
**3.2 Decode instruction:**   
Decoder 将指令译解成控制信号。  
ALU 信号为 = 。
**3.3 Get data:**  
获取数据3    
**3.4 Execute the instruction:**  
将数据放入累加器中
**3.5**  
 PC地址+2  
4. 
    **3.1 Fetch instruction:**  
从PC中读取下一条指令的地址，访问PC中的内存地址，复制其中内容，将副本放入指令寄存器（IR）中。  
**3.2 Decode instruction:**  
Decoder 将指令译解成控制信号。  
ALU 执行 + 运算。  
**3.3 Get data：**  
获取数据 W = 3 放到 ALU 中，将累加器中的 7 放到 ALU 中。
**3.4 Execute the instruction:**  
ALU执行加法运算，累加器中得到结果10。   
**3.5**  
 PC地址+2。  
5. 获取数据时的寻址方式不同： LOD #3 是立即寻址，ADD W 是直接寻址。  

##### (2) 点击“Binary”,观察回答下面问题  
    1. 写出指令 “LOD #7” 的二进制形式，按指令结构，解释每部分的含义。
    2. 解释 RAM 的地址。
    3. 该机器CPU是几位的？（按累加器的位数）
    4. 写出该程序对应的 C语言表达。

1. 00010100 00000111  
0001: 立即寻址（操作数是数值）  
0100：读取数值  
00000111：数值7  
2. 每个地址存放两个字节。
3. ALU能执行8位加法，该机器CPU是8位的。
4. C 语言表达
```c
int main(){
    int w = 3;
    int x = 7;
    int y = w + x;
}
```

#### TASK 2 **PROGRAM 2:Count down loop** 
##### (1) 输入程序Program 2，运行并回答问题：
    1. 用一句话总结程序的功能
    2. 写出对应的 c 语言程序

1. X初始值为0，每执行一次循环 X 的值 -1。
2. C 语言表达
```c
int main(){
    int x = 0;
    x = x - 1;
    while (x != 0){
        x = x -1;
    }
}
```

##### (2) 修改该程序，用机器语言实现 10+9+8+..1 ，输出结果存放于内存 Y
    1. 写出 c 语言的计算过程
    2. 写出机器语言的计算过程
    3. 用自己的语言，简单总结高级语言与机器语言的区别与联系。

1. 
```c
int main(){
    int Y = 0;
    for(int i = 0; i < 10; ++i){
        Y = Y + i + 1;
    }
}
```

2. 
|ADDRESS|INSTRUCTION|
|:-:|:-:|
|00|LOD X|
|02|ADD #10|
|04|STO X|
|06|LOD Y|
|08|ADD #1|
|10|STO Y|
|12|JMZ 34|
|14|LOD Z|
|16|ADD Y|
|18|STO Z|
|20|LOD Y|
|22|ADD #1|
|24|STO Y|
|26|LOD X|
|28|SUB #1|
|30|STO X|
|32|JMP 12|
|34|HLT|


![](images\lab07-task2.png)

3. 高级语言更偏向描述“要做什么“；  
机器语言更偏向“要实现‘要做什么’的具体操作”；  
两者实现同一事件。



## **四、实验小结**
本次实验通过
CPU 仿真工具加深了对冯·诺依曼计算机结构的了解，对于CPU如何通过Fetch - Execute周期来执行指令有了深刻的印象。并且初步了解了汇编语言的基本指令，以及如何与C 语言程序设计相关联。