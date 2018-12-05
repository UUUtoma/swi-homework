//ѧ�ţ�18342136 �������Լ��� 
/*
����ַ�����
	WHILE not ��Ϸ���� DO
		ch���ȴ�����
		CASE ch DO
		��A��:��ǰ��һ����break 
		��D��:��ǰ��һ����break    
		��W��:��ǰ��һ����break    
		��S��:��ǰ��һ����break    
		END CASE
		����ַ�����
	END WHILE
	��� Game Over!!! 

ͨ���ı��ַ������Ԫ��ʵ���ߵ��ƶ� -> �ı��Ԫ������
ͨ�������ʾ�ߵ�ÿһ�ڳ������ַ�������ĸ�λ�� -> �����鴢�棨x,y��һ����
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

//��ϸע����main������ĸ���������ǰ 

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

//��ʼ����ͼ
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

int main(){
	int game_step = 1;
	output();
	while(game_step) {
		char ch, enter;
		printf("game_step %d\nsnake_length %d\n\n", game_step, snake_length);
		printf("�������˶����򲢰��»س���\n��������Ϸ������'#'�����»س���\n");
		fflush(stdin); //���λ��з� 
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
			printf("������������ȷ�˶�����\n");
			break;
		}
		output();
		if(game_step) {
			game_step ++;
		}
	}
}

void snake_move(int change_y, int change_x){
	//����ԭ������ 
	clean_snake();
	//�ı������� 
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

void game_over(){
	printf("Game over!!!\n\nRestart\n\n");
	reset();
}
void reset(){
	//���������ͼ 
	for (int i = 1; i < 11; ++i) {
		for (int j = 1; j < 11; ++j) {
			map[i][j] = BLANK_CELL;
		}
	}
	//��ʼ��������
	for (int i = 0; i < snake_length; ++ i) {
		snake_X[i] = 5 - i;
	}
	for (int i = 0; i < snake_length; ++i) {
		snake_Y[i] = 1;
	}
}


