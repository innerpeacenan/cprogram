#include <stdio.h>
#include <stdlib.h>

struct binary_tree {
    int data;
    struct binary_tree * left;
    struct binary_tree * right;
}; // 结构体结尾必须加引号

typedef struct binary_tree node;

node *tree;

// 接下来我们需要把数据插入到对应的位置上；
//
//   我们希望树左边分支的的数据总是比树右边分支的要小；
//
//   至于为什么我们暂时不解释；

void insert (node ** tree, int val){
    node * temp = NULL;
    if(!(*tree)) {
        // return
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        // bug :忘记给跟节点赋值了，导致输出的结果都是0
        temp->data = val;
        *tree = temp;
        return;
    }
    if(val < ((*tree)->data)){
        // & 明白了
        insert(&(*tree)->left,val);
    }else if (val > ((*tree)->data)){
       insert(&(*tree)->right, val);
    }
}

// 这个内存释放函数写的不错
void deltree (node *tree){
    if(tree){
     deltree(tree->left);
     deltree(tree->right);
//直接释放啦free就只是释放啦根节点；
        free(tree);
    }
}

void print_preorder(node * tree) {
    if(tree) {
        printf("%d\n",tree->data);
        print_preorder(tree->left);
        print_preorder(tree->right);
    }
}

                   void print_inorder(node * tree) {
    if(tree) {
        print_inorder(tree->left);
        printf("%d\n",tree->data);
        print_inorder(tree->right);
    }
}

void print_postorder(node * tree) {
    if(tree) {
        print_postorder(tree->left);
        print_postorder(tree->right);
        printf("%d\n",tree->data);
    }
}


int main(void)
{
    node * root;
    node * tmp;
    //int i;

    root = NULL;
    /* Inserting nodes into tree */
    insert(&root,9);
    insert(&root,4);
    insert(&root,15);
    insert(&root,6);
    insert(&root,12);
    insert(&root,17);
    insert(&root,2);

    printf("Pre Order Display\n");
    print_preorder(root);

    printf("In Order Display\n");
    print_inorder(root);

    printf("Post Order Display\n");
    print_postorder(root);


    /* Deleting all nodes of tree */
    deltree(root);
}