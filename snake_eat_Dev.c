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
int food_x[FOOD_MAX_NUM] = {0};
int food_y[FOOD_MAX_NUM] = {0};
int count_food = 0; 
int food_id = 0;//��һ������ʳ���λ��

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
		put_food();
		output();
		if(game_step) {
			game_step ++;
		}
	}
}


void snake_move(int change_y, int change_x){
	//����ԭ������ 
	clean_snake();
	//IF ��ͷ������Ե��������Ϸ
	if (snake_X[0] + change_x == 0 || snake_X[0] + change_x > 10
		||snake_Y[0] + change_y == 0 || snake_Y[0] + change_y > 10) {
		printf("Out of line! ");
		game_over();
		return;
	}
	//IF ��ͷ����������Ϸ���� 
	for (int i = 1; i < snake_length; ++i) {
		if (snake_X[0] + change_x == snake_X[i] && snake_Y[0] + change_y == snake_Y[i]){
			printf("Your head hits your body! ");
			game_over();
			return;
		}
	}
	//IF ��ͷ����ʳ�� AND δ������󳤶� 
	//  �߱䳤 -> snake.check_length 
	//	ʳ����� 
	//	�´η���ʳ������� food_id �ı� 
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

//IF (food.ʳ������ < FOOD_MAX_NUM)
//	food.�������һ�����꣨��Χ�ڣ� 
//		IF ��food.���������Ƿ�Ϊ��  != ��) 
//	 		put_food(); -> �������棬��������������� < 1s����Զ�޷����ɲ��յ����� 
// 		ENDIF
//		����ʳ�� 
//ENDIF 
void put_food(void){
	if(count_food < FOOD_MAX_NUM) { //�ﵽʳ�����޺��ٷ���ʳ��  
		srand((unsigned) time(NULL));
		int rand_x = rand() % 10 + 1; //�������귶Χ (1, 10) 
		int rand_y = rand() % 10 + 1;
		//�����������Ƿ�Ϊ�� 
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
			//put_food(); -> ��������������� < 1s����Զ�޷����ɲ��յ����������Ѿ������� 
		}	
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
	//��ʼ���߳��ȡ�����
	snake_length = 5; 
	for (int i = 0; i < snake_length; ++ i) {
		snake_X[i] = 5 - i;
	}
	for (int i = 0; i < snake_length; ++i) {
		snake_Y[i] = 1;
	}
	//��ʼ��ʳ������
	count_food = 0; 
}


