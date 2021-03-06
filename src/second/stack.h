#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// 用单项链表实现栈
//a stack implement by single linked list
typedef struct _STACKnode {
	char item[50];
	struct _STACKnode * next;
} * STACKnode;

typedef struct _STACK {
	// head is the start position of a stack,it is also the last inserted member
	STACKnode head;
	int count;
} * STACK;

/**
 * initiate a stack
 */
STACK STACKinit();

/*
 * check if head equal to NULL to indicate whether the stack is empty or not
 */
int STACKisEmpty(STACK stack);

/*
 * insert a new item to the stack
 * <b>note</b> keep the head as the last inserted item
 *
 * allocate memory of size of link
 * and set item property as the given parameter
 * then move pointer header to the newest created and initiated node
 */
void STACKpush(STACK stack, char* item);

/**
 *  @return
 * record the item of head, it will be return value.
 * record the position of head->next ,delete head from the link list
 * by free(head)
 * and point head to the previous record position of head->next
 * and  return the item of head
 *  NULL indicate the stack is empty
 */
char* STACKpop(STACK stack);


void STACKtravel(STACK stack, void (*STACKnodePrinter)(STACKnode node));

void STACKprinter(STACK stack, void (*STACKnodePrinter)(STACKnode node));

void STACKnodePrinter(STACKnode node);



