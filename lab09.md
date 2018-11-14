# **洗衣机算法设计**

- [**一、实验目的**](#一实验目的)
- [**二、实验准备**](#二实验准备)
     - [**1. 自顶向下编程方法**](#1-自顶向下编程方法)
     - [**2.伪代码**](#2伪代码)    
     - [**3.洗衣机基本操作**](#3洗衣机基本操作)   
- [**三、实验过程**](#三实验过程)   
     - [**1.应用自顶向下方法分析**](#1应用自顶向下方法分析)    
     - [**2.基本实现思路**](#2基本实现思路)       
         - [**注水**](#注水)  
         - [**浸泡**](#浸泡)  
         - [**洗涤**](#洗涤)            
         - [**脱水**](#脱水)        
     - [**3.具体实现**](#3具体实现)          
         - [**注水**](#注水-1)    
         - [**浸泡**](#浸泡-1)           
         - [**洗涤**](#洗涤-1)           
         - [**脱水**](#脱水-1)      
     - [**4.改进**](#4改进)       
     - [**5.提取共性功能**](#5提取共性功能)      
         - [**5.1 wait** //等待指定的时间](#51-wait-等待指定的时间)            
         - [**5.2 注水(volume,timeout)** //在指定时间内完成注水，否则停机；](#52-注水volumetimeout-在指定时间内完成注水否则停机)           
         - [**5.3 排水(timeout)**](#53-排水timeout)

         

## **一、实验目的**
理解“自顶向下，逐步求精”的编程方法，并以观察洗衣机为案例，用伪代码描述控制程序设计的方法
## **二、实验准备**
### **1. 自顶向下编程方法**

### **2.伪代码**
伪代码规范：[Pseudocode Standard](http://users.csc.calpoly.edu/~jdalbey/SWE/pdl_std.html)

### **3.洗衣机基本操作**
>假设洗衣机可执行的基本操作如下：  
water_in_switch(open_close) // open 打开上水开关，close关闭  
water_out_switch(open_close) // open 打开排水开关，close关闭  
get_water_volume() //返回洗衣机内部水的高度  
motor_run(direction) // 电机转动。left左转，right右转，stop停  
time_counter() // 返回当前时间计数，以秒为单位  
halt(returncode) //停机，success 成功 failure 失败  

## **三、实验过程**

### **1.应用自顶向下方法分析**
![](images\lab09-洗衣机功能.png)

### **2.基本实现思路**
#### **注水**
```
打开水开关
当 达到指定水位
    关闭水开关
```

#### **浸泡**
```
当 未达到指定时间
    停机
```

#### **洗涤**
 ```
 每一次洗涤
 当 未达到指定时间
    电机左转动 5s
    点击右转动 5s
 ```

#### **脱水**
```
当 未达到指定时间
    打开排水开关
    电机转动
电机停止
关闭排水开关
```


### **3.具体实现**

#### **注水**
```
SET 已用时间 = 0
water_in_switch(open) // 打开水开关  
WHILE　未达到指定水位
    get_water_volume() //返回洗衣机内部水的高度  
ENDWHILE
water_in_switch(close) // 关闭水开关
已用时间 = time_counter() 
```

#### **浸泡**
```
SET 浸泡时间
WHILE time_counter() - 已用时间 (已浸泡时间)小于设定时间
    motor_run(stop)//电机停止转动
ENDWHILE
已用时间 = time_counter() 
```
#### **洗涤**
```
SET 洗涤时间
SET 洗涤次数
FOR 每一次洗涤
    WHILE 已用时间 - time_counter() （已洗涤时间） 小于洗涤时间
        motor_run(left)
        motor_run(right)
    ENDWHILE
    WHILE 当前水位不为零
        water_out_switch(open) //打开排水开关
    ENDWHILE
    water_out_switch(close) //关闭排水开关
ENDFOR
```
#### **脱水**
```
SET　脱水时间
water_out_switch(open) //打开排水开关
WHILE 当前时间小于脱水时间
    motor_run(left)
ENDWHILE
motor_run(stop)
water_out_switch(close) //关闭排水开关
```


### **4.改进**
>根据你的实践，请分析“正常洗衣”与“快速洗衣”在用户目标和程序上的异同。  
你认为是否存在改进（创新）空间，简单说明你的改进意见？  


3.

|          |   正常洗衣   |                           快速洗衣                            |
|:--------:|:--------:|:---------------------------------------------------------:|
| 用户目标 | 把衣服洗干净 |                    快速把衣服洗完，基本干净                    |
|   程序   | 完整洗衣过程 | 控制每个步骤时间尽量短，在基本干净前提下减少循环部分的循环次数 |


改进空间：设置衣物肮脏程度供用户选择，根据这一变量决定快速洗衣的精简程度。


### **5.提取共性功能**

>功能参考：  
water_in_switch(open_close) // open 打开上水开关，close关闭  
water_out_switch(open_close) // open 打开排水开关，close关闭  
get_water_volume() //返回洗衣机内部水的高度  
motor_run(direction) // 电机转动。left左转，right右转，stop停  
time_counter() // 返回当前时间计数，以秒为单位  
halt(returncode) //停机，success 成功 failure 失败 

#### **5.1 wait** //等待指定的时间
```
SET waiting_time
WHILE time_counter() is less then waiting_time
    motor_run(stop)
ENDWHILE
```

#### **5.2 注水(volume,timeout)** //在指定时间内完成注水，否则停机； 
```
SET time, volume
WHILE get_water_volume() is less then volume
    water_in_switch(open)
    IF time_counter() is not less then time
        halt
ENDWHILE
```

#### **5.3 排水(timeout)**
```
WHIlE get_water_volume is not equal to 0
    water_out_switch(open)
ENDWHILE
    water_in_swithc(close)
```
