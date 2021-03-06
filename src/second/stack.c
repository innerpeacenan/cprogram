#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"

/*
 * check if head equal to NULL to indicate whether the stack is empty or not
 */
int STACKisEmpty(STACK stack) {
	return 0 == stack->count;
}

/**
 * 终于搞定了,按照值返回行了
 * 他妈的,之前犯了一个严重错误,试图图过二级指针连分配待改变值,
 * 二级指针存改变值的前提是一级指针的存在啊,一级指针都不存在,改变个毛线
 */
STACK STACKinit() {
	STACK stack;
	stack = (STACK) malloc(sizeof(*stack));
	if (NULL == stack) {
		printf("not sufficient memory!\n");
		exit(EXIT_FAILURE);
	}
	stack->head = NULL;
	stack->count = 0;
	return stack;
}



/*
 * insert a new item to the stack
 * <b>note</b> keep the head as the last inserted item
 */
void STACKpush(STACK stack, char* item) {
	STACKnode *a;
	a = (STACKnode *) malloc(sizeof(*a));
	if (NULL == a) {
		printf("not sufficient memory!");
		exit(EXIT_FAILURE);
	}
	// assignment to expression with array type
	strcpy(a->item, item);
	a->next = stack->head;
	stack->head = a;
	// 之前这一步给忘记了
	stack->count++;
}

/**
 * record the item of head, it will be return value.
 * record the position of head->next ,delete head from the link list
 * by free(head)
 * and point head to the previous record position of head->next
 * and  return the item of head
 *
 *  bug: function returns address of local variable
 *  对了,怎么能返回局部变量值呢,系统自动申请的局部值的内存空间在程序执行完成后就释放了
 *  用 static
 *
 *  @return NULL indicate the stack is empty
 */
char* STACKpop(STACK stack) {
	// 1 表示true , c 语言中 boolean 值是从 C99 才开始引入的,引用的时候还要加头文件,麻烦
	if (1 == STACKisEmpty(stack))
		return NULL;
	// 这一片内存空间一定要一直留着(可以省取释放内存的麻烦)
	static char item[50];
	// invalid initializer,plase declare top as pointer
	STACKnode * top = stack->head;
	stack->head = stack->head->next;
	stack->count--;
	strcpy(item, top->item);
	free(top);
	return item;
}



/**
 * 函数指针原型写错了,之前未什么返回值类型 void
 */
void STACKtravel(STACK stack, void (*STACKnodePrinter)(STACKnode node)) {
	STACKnode  node;
	node = stack->head;
	/**
	 * 小于等于,将常量放在前面需要一段时间适应
	 */
	while (NULL != node) {
		//  expected expression before ‘STACKnode’
		// 要区分调用和原型申明
		(*STACKnodePrinter)(node);
		node = node->next;
	}
}

void STACKnodePrinter(STACKnode  node) {
	printf("'%s', ", node->item);
}

void STACKprinter(STACK stack, void (*STACKnodePrinter)(STACKnode node)) {
	printf("{'count' : %d, 'list': [ ", stack->count);
	STACKtravel(stack, STACKnodePrinter);
	printf(" ]}\n");
}

