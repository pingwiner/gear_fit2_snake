
#ifndef LOGIC_H_
#define LOGIC_H_

#define FIELD_SIZE_X 15
#define FIELD_SIZE_Y 28

#define GAME_PLAYING 0
#define GAME_OVER    1

extern char field[FIELD_SIZE_Y + 2][FIELD_SIZE_X + 2];
extern int game_state;
extern int score;

void model_init();
void model_tick();
void move_right();
void move_left();
void move_up();
void move_down();


#endif /* LOGIC_H_ */
