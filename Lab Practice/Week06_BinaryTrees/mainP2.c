#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

typedef struct _btnode{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

BTNode* insertBTNode(BTNode* cur, int item);
void printBTNode(BTNode *root, int space,int left);
void deleteTree(BTNode **root);

int hasGreatGrandchild(BTNode *node);

int main()
{
    BTNode* root=NULL;
    int item;

    printf("Enter a list of numbers for a Binary Tree, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
        root = insertBTNode(root, item);
    scanf("%*s");

    printf("The Binary Tree:\n");
    printBTNode(root,0,0);

    printf("The node(s) with great grandchild:\n");
    hasGreatGrandchild(root);
    printf("\n");

    deleteTree(&root);
    root=NULL;
    return 0;
}

BTNode* insertBTNode(BTNode* cur, int item){
    if (cur == NULL){
	BTNode* node = (BTNode*) malloc(sizeof(BTNode));
	node->item = item;
	node->left = node->right = NULL;
	return node;
	}
    if (rand()%2)
        cur->left  = insertBTNode (cur->left, item);
    else
        cur->right = insertBTNode (cur->right, item);

    return cur;
}

void printBTNode(BTNode *root,int space,int left){
      if (root != NULL)
      {

          int i;
          for (i = 0; i < space-1; i++)
                 printf("|\t");


          if(i<space){
            if(left==1)
              printf("|---");
            else
              printf("|___");
          }

          printf("%d\n", root->item);

          space++;
          printBTNode(root->left, space,1);
          printBTNode(root->right, space,0);
      }
}

void deleteTree(BTNode **root){
    if (*root != NULL)
	{
		deleteTree(&((*root)->left));
		deleteTree(&((*root)->right));
		free(*root);
		*root = NULL;
	}
}

int maxHeight(BTNode* node){
    
    if (node==NULL){return -1;}

    int l, r;
    l=maxHeight(node->left)+1;
    r=maxHeight(node->right)+1;
    if (l>r){
        return l;
    }
    else{
        return r;
    }
    // printf("cur node: %d\n", node->item);
    // printf("height: %d\n", h);
    // if (h>maxx){maxx = h;}
    // printf("max: %d\n", maxx);
    // return maxx;
}


int hasGreatGrandchild(BTNode *node){
//Write your code here
    if (node==NULL){return 0;}
    // printf("cur node %d\n", node->item);

    // if (((node->left->left->left) !=NULL) || ((node->left->left->right)!=NULL) || ((node->left->right->left)!=NULL) ||((node->left->right->right)!=NULL) || ((node->right->left->left)!=NULL) || ((node->right->left->right)!=NULL) || ((node->right->right->left)!=NULL) || ((node->right->right->right)!=NULL)) {
    //     printf("%d\n", node->item);

    // }

    // hasGreatGrandchild(node->left);
    // hasGreatGrandchild(node->right);
    // return 1;
    // int h = 0;
    // int maxH;
    
    // maxH = maxHeight(node, h);
    
    hasGreatGrandchild(node->left);
    hasGreatGrandchild(node->right);
    if (maxHeight(node)>=3){
        printf("cur: %d\n", node->item);


    }
    // printf("maxH: %d\n", maxHeight(node));
    // if (maxHeight(node,h)>)
   


    // int h;
    // h = hasGreatGrandchild(node->left)+1;
    // h = hasGreatGrandchild(node->right) +1;
    // // h = hasGreatGrandchild(node->right) +1;
    // // if (h)
    // printf("cur: %d\n", node->item);
    // printf("h: %d\n", h);

    return 0;
}
