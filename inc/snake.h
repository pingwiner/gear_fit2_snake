
#ifndef SNAKE_H_
#define SNAKE_H_


typedef struct LIST_ITEM_T {
	int x;
	int y;
	struct LIST_ITEM_T* prev;
	struct LIST_ITEM_T* next;
} ListItem;

typedef struct SNAKE_T {
	ListItem* head;
	ListItem* tail;
} Snake;

Snake* list_init(int x, int y);
int list_step(Snake* p, int x, int y);
void list_grow(Snake* p, int x, int y);
void list_destroy(Snake* p);
int list_check_collision(Snake* p, int x, int y);


#define STEP_COLLISION 1


#endif /* SNAKE_H_ */
