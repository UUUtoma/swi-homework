//学号：18342136 姓名：赵嘉仪
/*
输出字符矩阵
	WHILE not 游戏结束 DO
		ch＝等待输入
		CASE ch DO
		‘A’:左前进一步，break 
		‘D’:右前进一步，break    
		‘W’:上前进一步，break    
		‘S’:下前进一步，break    
		END CASE
		输出字符矩阵
	END WHILE
	输出 Game Over!!! 

通过改变字符矩阵的元素实现蛇的移动 -> 改变各元素坐标
通过坐标表示蛇的每一节出现在字符矩阵的哪个位置 -> 用数组储存（x,y各一个）
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define bool int

#define SNAKE_MAX_LENGTH 20
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define SNAKE_FOOD '$'
#define WALL_CELL '*'
#define FOOD_MAX_NUM 4

//详细注释在main函数后的各函数定义前 

//(y, x) up: (1, 0); down (-1, 0); left (0, -1); rigth(0, 1).
void snake_move(int, int);
void clean_snake(void);

//print the map
void output(void);
void set_head(void);
void set_body(void);

//put a food randomized on a blank cell
void put_food(void);

//if out of line, gameover and restart
void game_over(void);
void reset(void);

//初始化地图
char map[12][13] = 
	{"************",
	"*XXXXH     *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"************"};

int snake_X[SNAKE_MAX_LENGTH] = {5,4,3,2,1};
int snake_Y[SNAKE_MAX_LENGTH] = {1,1,1,1,1};
int snake_length = 5;
int food_x[FOOD_MAX_NUM] = {0};
int food_y[FOOD_MAX_NUM] = {0};
int count_food = 0; 
int food_id = 0;//下一个放置食物的位置

int main(){
	int game_step = 1;
	put_food();
	output();
	while(game_step) {
		if(game_step < 4) {
			food_id ++;
		}
		char ch, enter;
		printf("game_step %d\nsnake_length %d\n\n", game_step, snake_length);
		printf("请输入运动方向并按下回车：\n（结束游戏请输入'#'并按下回车）\n");
		fflush(stdin); //屏蔽换行符 
		ch = getchar();
		switch (ch) {
		case 'A':
			snake_move(0, -1);
			break;
		case 'D':
			snake_move(0, 1);
			break;
		case 'W':
			snake_move(-1 , 0);
			break;
		case 'S':
			snake_move(1, 0);
			break;
		case '#':
			game_step = 0;
			break;
		default:
			printf("请重新输入正确运动方向\n");
			break;
		}
		put_food();
		output();
		if(game_step) {
			game_step ++;
		}
	}
}


void snake_move(int change_y, int change_x){
	//擦除原来的蛇 
	clean_snake();
	//IF 蛇头碰到边缘，结束游戏
	if (snake_X[0] + change_x == 0 || snake_X[0] + change_x > 10
		||snake_Y[0] + change_y == 0 || snake_Y[0] + change_y > 10) {
		printf("Out of line! ");
		game_over();
		return;
	}
	//IF 蛇头碰到蛇身游戏结束 
	for (int i = 1; i < snake_length; ++i) {
		if (snake_X[0] + change_x == snake_X[i] && snake_Y[0] + change_y == snake_Y[i]){
			printf("Your head hits your body! ");
			game_over();
			return;
		}
	}
	//IF 蛇头碰到食物 AND 未超过最大长度 
	//  蛇变长 -> snake.check_length 
	//	食物变少 
	//	下次放置食物的坐标 food_id 改变 
	bool eat_food = 0;
	for (int i = 0; i < count_food; ++i) {
		if (snake_X[0] + change_x == food_x[i] && 
			snake_Y[0] + change_y == food_y[i]) {
			eat_food = 1;
			food_id = i;
		}
	}
	if (eat_food) {
		if (snake_length < SNAKE_MAX_LENGTH) {
			snake_length ++;
			count_food --;
		}
	}
	//改变蛇坐标 
	for (int i = 0; i < snake_length - 1; ++i) {
		snake_X[snake_length - 1 - i] = snake_X[snake_length - 2 - i];
		snake_Y[snake_length - 1 - i] = snake_Y[snake_length - 2 - i];
	}
	snake_X[0] += change_x;
	snake_Y[0] += change_y;
}

void clean_snake(){
	for (int i = 0; i < snake_length; ++i) {
		map[snake_Y[i]][snake_X[i]] = BLANK_CELL;
	}
}

void output(){
	set_head();
	set_body();
	for (int i = 0; i < 12; ++i) {
		printf("%s\n", map[i]);
	}
}


void set_head(){
	int head_x = snake_X[0], head_y = snake_Y[0];
	map[head_y][head_x] = SNAKE_HEAD;
}

void set_body(){
	for (int i = 1; i < snake_length; ++i) {
		int body_x = snake_X[i], body_y = snake_Y[i];
		map[body_y][body_x] = SNAKE_BODY;
	}
}

//IF (food.食物数量 < FOOD_MAX_NUM)
//	food.随机生成一个坐标（范围内） 
//		IF （food.检查该坐标是否为空  != 空) 
//	 		put_food(); -> 空语句代替，待解决：由于运行 < 1s，永远无法生成不空的坐标 
// 		ENDIF
//		放置食物 
//ENDIF 
void put_food(void){
	if(count_food < FOOD_MAX_NUM) { //达到食物上限后不再放置食物  
		srand((unsigned) time(NULL));
		int rand_x = rand() % 10 + 1; //控制坐标范围 (1, 10) 
		int rand_y = rand() % 10 + 1;
		//检查随机坐标是否为空 
		bool is_snake = 0, is_food = 0;
		for (int i = 0; i < snake_length; ++i) {
			if (rand_x == snake_X[i] && rand_y == snake_Y[i]) {
				is_snake = 1;
			}
		}
		for (int i = 0; i < count_food; ++i) {
			if (rand_x == food_x[i] && rand_y == food_y[i]) {
				is_food = 1;
			}
		}
		bool is_blank = (!is_food) && (!is_snake);
		if (is_blank) {
			food_x[food_id] = rand_x;
			food_y[food_id] = rand_y;
			map[food_y[food_id]][food_x[food_id]] = SNAKE_FOOD;
			count_food ++;
		}
		else if (!is_blank) {
			; 
			//put_food(); -> 待解决：由于运行 < 1s，永远无法生成不空的坐标程序就已经结束了 
		}	
	}
}

void game_over(){
	printf("Game over!!!\n\nRestart\n\n");
	reset();
}
void reset(){
	//清空整个地图 
	for (int i = 1; i < 11; ++i) {
		for (int j = 1; j < 11; ++j) {
			map[i][j] = BLANK_CELL;
		}
	}
	//初始化蛇长度、坐标
	snake_length = 5; 
	for (int i = 0; i < snake_length; ++ i) {
		snake_X[i] = 5 - i;
	}
	for (int i = 0; i < snake_length; ++i) {
		snake_Y[i] = 1;
	}
	//初始化食物数量
	count_food = 0; 
}

