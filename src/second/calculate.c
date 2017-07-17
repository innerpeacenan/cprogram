#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 用单项链表实现栈
//a stack implement by single linked list
typedef struct _STACKnode {
	char item;
	struct _STACKnode * next;
}* STACKnode;

typedef struct _STACK {
	// head is the start position of a stack,it is also the last inserted member
	STACKnode head;
	int count;
}* STACK;

/*
 * check if head equal to NULL to indicate whether the stack is empty or not
 */
int STACKisEmpty(STACK stack) {
	return 0 == stack->count;
}

/**
 * 终于搞定了,按照值返回行了
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
void STACKpush(STACK stack, char item) {
	STACKnode a;
	a = (STACKnode) malloc(sizeof(*a));
	if (NULL == a) {
		printf("not sufficient memory!");
		exit(EXIT_FAILURE);
	}
	a->item = item;
	a->next = stack->head;
	stack->head = a;
	stack->count++;
}

/**
 * record the item of head, it will be return value.
 *  bug: function returns address of local variable
 *  @return NULL indicate the stack is empty
 */
char STACKpop(STACK stack) {
	// 1 表示true , c 语言中 boolean 值是从 C99 才开始引入的,引用的时候还要加头文件,麻烦
	if (1 == STACKisEmpty(stack)) {
		return 13; // return "enter" indict an error
	}
	STACKnode top = stack->head;
	char item = top->item;
	stack->head = stack->head->next;
	stack->count--;
	free(top);
	return item;
}

void STACKnodePrinter(STACKnode node) {
	printf("%c , ", node->item);
}

void STACKtravel(STACK stack, void (*STACKnodePrinter)(STACKnode node)) {
	STACKnode node;
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

void STACKprinter(STACK stack, void (*STACKnodePrinter)(STACKnode node)) {
	printf("{'count' : %d, 'list': [ ", stack->count);
	STACKtravel(stack, STACKnodePrinter);
	printf(" ]}\n");
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("usage: input first argument as the expression\n");
		exit(EXIT_FAILURE);
	}
	/**
	 * "1 2 3 + 4 5 * * +"
	 * 测试用例在终端输入的时候,一定要用引号扩起来,避免出问题
	 */
	char *a = argv[1];
	int i;
	int N = strlen(a);
	STACK stack = STACKinit();
	for (i = 0; i < N; i++) {
		if (a[i] != ' ') {
			// empty character constant
			STACKpush(stack, a[i]);
		}
	}
	STACKprinter(stack, STACKnodePrinter);

	for (i = 0; i < N; i++) {
		if (a[i] == '+') {
			STACKpush(stack, STACKpop(stack) + STACKpop(stack));
		}
		if (a[i] == '*') {
			STACKpush(stack, STACKpop(stack) * STACKpop(stack));
		}
		// 将字符转化为数字压入栈中,这一块比较巧妙
		if ((a[i] >= '0') && (a[i] <= '9')) {
			STACKpush(stack, 0);
		}
		while ((a[i] >= '0') && (a[i] <= '9')) {
			STACKpush(stack, 10 * STACKpop(stack) + (a[i++] - '0'));
		}
	}
	printf("%d \n", STACKpop(stack));

}