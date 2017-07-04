#include "bisearchtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 *  创建二叉查找树
 *
 *  @return 指向一颗空树的指针
 */
BiSearchTree *bisearch_tree_new() {

	return NULL;

}

/**
 *  插入节点
 *
 *  @param tree tree a pointer to the root of a tree
 *  @param node 节点值 new inserted value
 */
BiSearchTree *bisearch_tree_insert(BiSearchTree *tree, ElemType node) {
//	assert(tree == NULL);
	BiSearchTree *t = tree;
	BiSearchTree *parent = NULL;
	// although  C中对指针类型转换的检查没有C++那么严格
	// good habit to make a conversion
	BiSearchTree *newNode = (BiSearchTree *) malloc(sizeof(BiSearchTree));
	if (NULL == newNode) {
		printf("malloc failure\n");
		return tree;
	}
	newNode->key = node;
	newNode->lChild = NULL;
	newNode->rChild = NULL;
	// if no element created before
	if (NULL == t) {
		tree = newNode;
		printf("insert first node %d!\n", node);
		return tree;
	}
//  printf("should not run to here for the first element insertion!");
	// 找合适的位置 how to make t point to NULL when insert end
	// **notice**  duplicate element are not allowed to insert and will be ignored
	// sink to find location to insert the newNode, until it reach the leaf
	while (t != NULL) {
		if (node < t->key) {
			parent = t;
			t = t->lChild;
		} else if (node > t->key) {
			parent = t;
			t = t->rChild;
		} else {
			printf("insert ignore:bi search tree has the node %d!\n", node);
			break;
		}
	}

	// parent was initiated as NULL, so if parent != NULL, it means the sink while loop excuted
	if (NULL != parent) {
		// t point to NULL when it point to leaf, so Segmentation fault (core dumped) throw
		// when if(node < key->key){
		if (node < parent->key) {
			parent->lChild = newNode;
			printf("insert node %d to left of %d\n", node, parent->key);
		} else {
			parent->rChild = newNode;
			printf("insert node %d to right of %d\n", node, parent->key);
		}
	}
	return tree;
}

/**
 *  查找节点
 *
 *  @param tree tree
 *  @param node 节点值
 * （也可以使用递归方式实现）
 *
 */
// redefinition of ‘bisearch_tree_search’
// did not included this function in header file previously
int bisearch_tree_search_recursive(BiSearchTree *tree, ElemType node) {

	// find node on tree
	BiSearchTree *t;
	// declare and  initiate could not done by one line for a pointer
	t = tree;
	if (NULL == t)
		return -1;
	printf("compare with %d:\n",t->key);
	if (node == t->key) {
		return 0;
	} else if (node < t->key) {
		// search left
		bisearch_tree_search_recursive(t->lChild, node);
	} else {
		bisearch_tree_search_recursive(t->rChild, node);
	}
}




// implemented with a while loop
int bisearch_tree_search(BiSearchTree *tree, ElemType node) {
    BiSearchTree *t;
    t =  tree;
    // notice : use pointer t to travel and move, tree point to the root node of the tree, do not touch it
    // fixed
    while (NULL != t){
    	if(node == t->key){
    		return 0;
    	}else if(node < t->key){
    		// move left
    		t = t->lChild;
    	}else{
    		t = t->rChild;
    	}
    }
   return -1;
}

//private
int _delete_node(BiSearchTree *node, BiSearchTree*parent) {

	//该节点为叶子节点，直接删除
	if (!node->rChild && !node->lChild) {

		free(node);    //父节点？？？不然野指针,造成崩溃
	} else if (!node->rChild) {	//右子树空则只需重接它的左子树
		BiSearchTree *target = node->lChild;
		node->key = node->lChild->key;
		node->lChild = node->lChild->lChild;
		node->rChild = node->lChild->rChild;

		free(target);
	} else if (!node->lChild) {	//左子树空只需重接它的右子树
		BiSearchTree *target = node->rChild;
		node->key = node->rChild->key;
		node->lChild = node->rChild->lChild;
		node->rChild = node->rChild->rChild;

		free(target);
	} else {	//左右子树均不空

		BiSearchTree *parent = node, *target = node->lChild;
		while (target->rChild) {
			parent = target;
			target = target->rChild;
		}	// 找到左子树最大的，是删除节点的直接“前驱”

		node->key = target->key;

		if (target != node) {
			parent->rChild = target->lChild;
		} else {
			node->lChild = target->lChild;
		}

		free(target);
	}
	return 0;
}

//删除节点,需要重建排序树
/*
 1) 删除节点是叶子节点（分支为0），结构不破坏
 2）删除节点只有一个分支(分支为1)，结构也不破坏
 3）删除节点有2个分支，此时删除节点

 思路一： 选左子树的最大节点，或右子树最小节点替换

 */
int bisearch_tree_delete(BiSearchTree **tree, ElemType node){
	// search and delete
    BiSearchTree *target;
    target = tree;
    BiSearchTree *parent;
    parent = NULL;

}


int bisearch_tree_delete(BiSearchTree **tree, ElemType node) {

	if (NULL == tree) {
		return -1;
	}

	// 查找删除目标节点
	BiSearchTree *target = *tree, *parent = NULL;
	// search where it is, make target point to it, and parent point to its parent
	while (NULL != target) {
		if (node < target->key) {
			parent = target;
			target = target->lChild;
		} else if (node == target->key) {
			break;
		} else {
			parent = target;
			target = target->rChild;
		}
	}

	if (NULL == target) {
		printf("树为空，或想要删除的节点不存在\n");
		return -1;
	}

	//该节点为叶子节点，直接删除
	if (!target->rChild && !target->lChild) {
		if (NULL == parent) {	////只有一个节点的二叉查找树
			*tree = NULL;
		} else {
			if (target->key > parent->key) {
				parent->rChild = NULL;
			} else {
				parent->lChild = NULL;
			}

		}
		free(target);	//父节点处理，不然野指针,造成崩溃
	}

	else if (!target->rChild) {	//右子树空则只需重接它的左子树
		// @todo try rebuilt according to my solution
		BiSearchTree *del = target->lChild;
		target->key = target->lChild->key;
		target->lChild = target->lChild->lChild;
		target->rChild = target->lChild->rChild;

		free(del);
	} else if (!target->lChild) {	//左子树空只需重接它的右子树
		BiSearchTree *del = target->rChild;
		target->key = target->rChild->key;
		target->lChild = target->rChild->lChild;
		target->rChild = target->rChild->rChild;

		free(del);
	} else {	//左右子树均不空

		BiSearchTree *p = target, *t = target->lChild;
		while (t->rChild) {
			p = t;
			t = t->rChild;
		}	// 找到左子树最大的，是删除节点的直接“前驱”

		target->key = t->key;

		if (p != target) {
			p->rChild = t->lChild;
		} else {
			target->lChild = t->lChild;
		}

		free(t);
	}
	return 0;

//    if (node==tree->key) {
//        return _delete_node(tree);
//    }else if(node>tree->key){
//        return bisearch_tree_delete(tree->rChild,node);
//    }else{
//        return bisearch_tree_delete(tree->lChild,node);
//    }

	/*

	 // 查找删除目标节点
	 BiSearchTree *t=tree,*parent=NULL;
	 while (NULL!=t) {
	 if (node<t->key) {
	 parent=t;
	 t=t->lChild;
	 }else if(node==t->key){
	 break;
	 }else{
	 parent=t;
	 t=t->rChild;
	 }
	 }

	 if (NULL==t) {
	 printf("树为空，或想要删除的节点不存在\n");
	 return -1;
	 }

	 // parent 可能为null

	 //删除节点0个分支
	 if (!t->lChild && !t->rChild) {
	 if (t->key>parent->key) {
	 parent->rChild=NULL;
	 }else{
	 parent->lChild=NULL;
	 }
	 free(t);
	 return 0;
	 }

	 //删除节点有1个分支
	 else if (t->lChild && !t->rChild) {
	 if (t->key>parent->key) {
	 parent->rChild=t->lChild;
	 }else{
	 parent->lChild=t->lChild;
	 }
	 free(t);
	 return 0;
	 }

	 else if (!t->lChild && t->rChild) {
	 if (t->key>parent->key) {
	 parent->rChild=t->rChild;
	 }else{
	 parent->lChild=t->rChild;
	 }
	 free(t);
	 return 0;
	 }

	 //删除节点有2个分支
	 else if (t->lChild && t->rChild) {

	 if (t->key->parent->key) {

	 }


	 }

	 return -1;

	 */
}

void bisearch_tree_inorder_traversal_internal(BiSearchTree *tree);
// 中序遍历节点，也就是从小到大输出
// void bisearch_tree_inorder_traversal_internal(BiSearchTree *tree)
// declare before call
void bisearch_tree_inorder_traversal(BiSearchTree *tree) {
	// if tree is not null
	if (tree) {
		printf("[ ");
		bisearch_tree_inorder_traversal_internal(tree);
		printf("]\n");
//		putchar('\n');
	}
}

void bisearch_tree_inorder_traversal_internal(BiSearchTree *tree) {
	if (tree) {
		bisearch_tree_inorder_traversal_internal(tree->lChild);
		printf("%d, ", tree->key);
		bisearch_tree_inorder_traversal_internal(tree->rChild);
	}
}
