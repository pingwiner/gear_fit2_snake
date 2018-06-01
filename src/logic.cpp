
#include <string.h>
#include <logic.h>
#include <stdlib.h>
#include <dlog.h>
#include "game.h"
#include "snake.h"

#define CELL_EMPTY 0
#define CELL_SNAKE 1
#define CELL_FOOD 2
#define CELL_OBSTACLE 3

char field[FIELD_SIZE_Y + 2][FIELD_SIZE_X + 2] = {{0,}};
int game_state;
int score;
int direction;
int tick_count;
Snake* pSnake = NULL;

#define DIR_UP 		0
#define DIR_DOWN 	1
#define DIR_LEFT 	2
#define DIR_RIGHT 	3

static void place_object(char v) {
	int food_x;
	int food_y;

	while(1) {
		food_x = (rand() % FIELD_SIZE_X) + 1;
		food_y = (rand() % FIELD_SIZE_Y) + 1;
		if (list_check_collision(pSnake, food_x, food_y) != STEP_COLLISION) {
			if (field[food_y][food_x] == CELL_EMPTY) {
				field[food_y][food_x] = v;
				return;
			}
		}
	}
}

void model_init() {
	memset(field, 0, sizeof(field));
	direction = DIR_UP;
	tick_count = 0;
	score = 0;
	if (pSnake) list_destroy(pSnake);
	pSnake = list_init(FIELD_SIZE_X /2, FIELD_SIZE_Y / 2);
	for (int i = 0; i < FIELD_SIZE_Y + 2; i++) {
		field[i][0] = CELL_OBSTACLE;
		field[i][FIELD_SIZE_X + 1] = CELL_OBSTACLE;
	}
	for (int i = 1; i <= FIELD_SIZE_X; i++) {
		field[FIELD_SIZE_Y + 1][i] = CELL_OBSTACLE;
		field[0][i] = CELL_OBSTACLE;
	}
	place_object(CELL_FOOD);
	game_state = GAME_PLAYING;
}

static void snake_draw(char v) {
	ListItem* item = pSnake->head;
	dlog_print(DLOG_ERROR, LOG_TAG, "draw start");
	while(item) {
		field[item->y][item->x] = v;
		item = item->next;
	}
	dlog_print(DLOG_ERROR, LOG_TAG, "draw end");
}

void model_tick() {
	int new_x = pSnake->head->x;
	int new_y = pSnake->head->y;
	tick_count++;
	if (game_state == GAME_OVER) return;

	snake_draw(CELL_EMPTY);
	if (tick_count % 2 == 0) {
		switch(direction) {
			case DIR_UP:
				new_y--;
				break;
			case DIR_DOWN:
				new_y++;
				break;
			case DIR_RIGHT:
				new_x++;
				break;
			case DIR_LEFT:
				new_x--;
				break;
		}
		if (field[new_y][new_x] == CELL_OBSTACLE) {
			game_state = GAME_OVER;
		} else if (field[new_y][new_x] == CELL_FOOD) {
			list_grow(pSnake, new_x, new_y);
			score += 10;
			place_object(CELL_FOOD);
		} else if (field[new_y][new_x] == 0) {
			if (list_step(pSnake, new_x, new_y) == STEP_COLLISION) {
				game_state = GAME_OVER;
			}
		}
	}

	if (tick_count % 50 == 49) {
		place_object(CELL_OBSTACLE);
	}

	snake_draw(CELL_SNAKE);
}

void move_right() {
	if (direction == DIR_LEFT) return;
	direction = DIR_RIGHT;
}

void move_left() {
if (direction == DIR_RIGHT) return;
	direction = DIR_LEFT;
}

void move_up() {
	if (direction == DIR_DOWN) return;
	direction = DIR_UP;
}

void move_down() {
	if (direction == DIR_UP) return;
	direction = DIR_DOWN;
}




