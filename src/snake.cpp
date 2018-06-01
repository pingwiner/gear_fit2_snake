#include <snake.h>
#include <stdlib.h>

static ListItem* alloc_list_item(int x, int y) {
	ListItem* item = (ListItem*) malloc(sizeof(ListItem));
	item->x = x;
	item->y = y;
	item->prev = NULL;
	item->next = NULL;
	return item;
}

int list_check_collision(Snake* p, int x, int y) {
	ListItem* item = p->head;
	while(item) {
		if ((x == item->x) && (y == item->y)) return STEP_COLLISION;
		item = item->next;
	}
	return 0;
}

Snake* list_init(int x, int y) {
	Snake* list = (Snake*) malloc(sizeof(Snake));
	list->head = alloc_list_item(x, y);
	ListItem* middle = alloc_list_item(x, y + 1);
	list->tail = alloc_list_item(x, y + 2);
	list->head->next = middle;
	middle->next = list->tail;
	list->tail->prev = middle;
	middle->prev = list->head;
	return list;
}

void list_destroy(Snake* p) {
	ListItem* item = p->head;
	while(item) {
		ListItem* next = item->next;
		free(item);
		item = next;
	}
	free(p);
}

int list_step(Snake* p, int x, int y) {
	if (list_check_collision(p, x, y) == STEP_COLLISION) return STEP_COLLISION;
	ListItem* temp = p->tail;
	p->tail = p->tail->prev;
	p->tail->next = NULL;

	temp->prev = NULL;
	temp->next = p->head;
	p->head->prev = temp;

	temp->x = x;
	temp->y = y;
	p->head = temp;

	return 0;
}

void list_grow(Snake* p, int x, int y) {
	ListItem* temp = alloc_list_item(x, y);
	temp->next = p->head;
	p->head->prev = temp;
	p->head = temp;
}

