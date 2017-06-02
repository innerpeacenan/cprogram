typedef struct node * link;
typedef int itemType;
struct node {
	itemType item;
	link next;
};

void initNodes(int);

/**
 * 利用从闲余链表上删除的一个元素,构建链表的一个新的节点,并返回该节点
 */
link newNode(int);

/**
 * 从闲余链中删除一个节点,返回被删除的节点,共新联表的新元素使用
 */
link deleteNext(link);

/**
 * 从使用的链表上删除一个元素,并将该元素放入到闲余链表中,
 * 以供第二次使用
 */
void freeNode(link);

void insertNext(link, link);

link Next(link);

itemType Item(link);
