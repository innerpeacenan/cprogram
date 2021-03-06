#define TSIZE 45
typedef struct film {
    char title[TSIZE];
    int rating;
} Item;

// 有节点的概念后,就可以构成一个单项链表
typedef struct node{
    Item item;
    // typical usage
    struct node * next;
} Node;

/*
 * note: to manage a linked list, we need  a pointer to its beginning,
 * and we've used typedef to make List the name for a pointer of this
 * type.
 */
typedef struct list{
    // should point to linked list Node
    Node * head;
    // how man numbers are in the linked list,
    // make it easy to count its size
    int size;
} List;

void InitializeList( List *);

// const should declare in function prototype, not in its implement
int ListIsEmpty( const List *);

// indict whether a list is full
int ListIsFull( const List *);

unsigned int ListItemCount( const List *);

/* preconditions: item is an item to be added to list */
/* plist points to an initialized list */
/* postconditions: if possible, function adds item to end */
/* of list and returns 1; otherwise the */
/* function returns 0*/
int AddItem(Item item, List * plist);

void showmovies(Item item);

// 遍历接受一个用于处理节点的指针函数
void Traverse( List *, void (* pfun)(Item item));

void EmptyTheList(List *);


