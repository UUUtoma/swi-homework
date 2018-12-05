# 贪吃蛇实验报告
作业文件地址：[https://github.com/UUUtoma/swi-homework](https://github.com/UUUtoma/swi-homework)  
包含 :  
1.snake_move_Dev.c  
2.snake_move_Sublime(UTF-8).c  
3.snake_eat_Dev.c  
4.snake_eat_Sublime(UTF-8).c  


问题记录：
#### 1. 
若不在字符串末尾加上'\0'，访问字符二维数组试图输出某行时会输出每一行直到输出数组最后一个字符；  
#### 2. 屏蔽输入方向后的'\n'：  
方法一：
```c
//在接收字符后，使用getchar()来读取一次回车符号
ch = getchar();
getchar();  //专门用来读取上次输入的回车符号
```
缺点：若用户不小心输入"DD\n" 则会一直提示“请重新输入正确运动方向”，因为被扔掉的是'D',而下次被读取的是ch = '\n'

方法二：  
```c
//在接收字符前，使用fflush()清空输入流中缓冲区中的内容
//注意必须引入 <stdlib.h> 头文件
ch = getchar(); 
fflush(stdin); 
ch = getchar();
```

#### 3. 摩根定律  
！(x = food && y= food) -> (x != food || y != food)
```c
void clean_map(){
	for (int i = 1; i < 11; ++i){
		for (int j = 1; j < 11; ++j){
			for(int k = 0; k < count_food; ++k){
				if (i != food_y[k] || j != food_x[k]) { //不清除食物,一开始错写作&&
					map[i][j] = BLANK_CELL;
				}
			}
		}
	}
}
```
ps.清除蛇原坐标即可，不用判断是否是食物

#### 4. 
若生成坐标不空，再次调用 put_food 时间小于1s,将导致一直生成同一个不空的坐标，程序无法运行
    
#### 5. 
game over 的 reset 功能几次测试后才发现漏了食物重置（因为一开始没有食物功能）、蛇的长度（因为一开始测试时蛇的长度还是初始长度没有发现）
