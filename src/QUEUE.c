#include <stdlib.h>
#include "QUEUE.h"
#include "Item.h"
typedef struct QUEUEnode* link;
struct QUEUEnode {
	Item item;
	link next;
};

static link head, tail;

link NEW(Item item, link next) {
	link x = malloc(sizeof *x);
	if (x) {
		x->item = item;
		x->next = next;
	}
	return x;
}

/*
 * [NULL is in stddef.h and stdlib.h](http://stackoverflow.com/questions/7433448/eclipse-cdt-symbol-null-could-not-be-resolved)
 */
void QUEUEinit(int MaxN) {
	head = NULL;
}

int QUEUEempty() {
	return head == NULL;
}

void QUEUEput(Item item) {
	if (head == NULL) {
		tail = NEW(item, head);
		head = tail;
		return;
	}
	tail->next = NEW(item, tail);
	tail = tail->next;
}


Item QUEUEget() {
	link t = head->next;
	Item item = head->item;
	free(head);
	head = t;
	return item;
}
