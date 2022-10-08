#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

BTNode* insertBSTNode(BTNode* cur, int item);
void printBTNode(BTNode *root, int space,int left);
void deleteTree(BTNode **root);
int removeBSTNode(BTNode **nodePtr, int item);

int main()
{
    BTNode* root=NULL;
    int item;

    printf("Enter a list of numbers for a Binary Tree, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
        root = insertBSTNode(root, item);
    scanf("%*s");

    printf("The Binary Search Tree:\n");
    printBTNode(root,0,0);

    printf("Enter an integer to be removed from the tree:\n");
    scanf("%d",&item);

    if(removeBSTNode(&root,item))
       printf("%d was removed\n",item);

    else
       printf("%d is not in the tree.\n",item);

    printf("The Binary Search Tree:\n");
    printBTNode(root,0,0);

    deleteTree(&root);
    root=NULL;
    return 0;
}

BTNode* insertBSTNode(BTNode* cur, int item){
    if (cur == NULL){
        BTNode* node = (BTNode*) malloc(sizeof(BTNode));
    	node->item = item;
    	node->left = node->right = NULL;
    	return node;
	}
    if (item < cur->item)
        cur->left  = insertBSTNode (cur->left, item);
    else if (item > cur->item)
        cur->right = insertBSTNode (cur->right, item);
    else
        printf("Duplicated Item: %d\n",item);

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
BTNode* rightMostofLST(BTNode* cur){
    int count = 0;
    cur =  cur->left;
    while(cur->right!=NULL){
        cur = cur->right;
        count++;
    }
    if (count>0){
        return cur;
    }
    else{
        return NULL;
    }
    
}

BTNode* leftMostofRST(BTNode* cur){
    int count = 0;
    cur = cur->right;
    while(cur->left!=NULL){
        cur = cur->left;
        count++;
    }
    if (count>0){
        return cur;
    }
    else{
        return NULL;
    }
}

int removeUtilR(BTNode* nodePtr, int item){
    BTNode* cur = nodePtr;
    BTNode* pre;
    int flag = 0;
    printf("util cur: %d\n", cur->item);
    if (item < cur->item){
        cur = cur->left;
    }
    else if (item > cur -> item){
        cur = cur->right;
    }

    while (cur->item != item){
        
        if (item > cur->item){
            pre = cur;
            cur = cur->right;
            flag = 1;
        }
        else if (item < cur -> item){
            pre = cur;
            cur = cur -> left;
            flag = -1;
        }
    }
    if (cur->left!=NULL){
        pre->right = cur->left;
    }
    else (pre->right = NULL);
    return 1;
}

int removeUtilL(BTNode* nodePtr, int item){
    BTNode* cur = nodePtr;
    BTNode* pre;
    int flag = 0;
    printf("util cur: %d\n", cur->item);
    if (item < cur->item){
        cur = cur->left;
    }
    else if (item > cur -> item){
        cur = cur->right;
    }

    while (cur->item != item){
        
        if (item > cur->item){
            pre = cur;
            cur = cur->right;
            flag = 1;
        }
        else if (item < cur -> item){
            pre = cur;
            cur = cur -> left;
            flag = -1;
        }
    }
    if (cur->right!=NULL){
        pre->left = cur->right;
    }
    else (pre->left = NULL);
    return 1;
}



int removeBSTNode(BTNode **nodePtr, int item){
    //Write Your Code Here
    BTNode* cur = *nodePtr;
    BTNode* pre;
    int flag = 0;
    
    if (item < cur->item){
        cur = cur->left;
    }
    else if (item > cur -> item){
        cur = cur->right;
    }

    while (cur->item != item){
        if (item > cur->item){
            pre = cur;
            cur = cur->right;
            flag = 1;
        }
        else if (item < cur -> item){
            pre = cur;
            cur = cur -> left;
            flag = -1;
        }
    }

    if ((cur->right==NULL)&&(cur->left==NULL)){
        pre -> left = NULL;
        pre -> right = NULL;
    }
    else if ((cur->left == NULL) && (cur->right!=NULL)){
        if (flag == 1){
            pre->right = cur->right;
        }
        else if (flag == -1){
            pre->left = cur->right;
        }
    }
    else if ((cur->left != NULL) && (cur->right==NULL)){
        if (flag == 1){
            pre->right = cur->left;
        }
        else if (flag == -1){
            pre->left = cur->left;
        }
    }
    else if ((cur->left!= NULL) && (cur->right!=NULL)){
        // printf("option1: %d\n", rightMostofLST(cur)->item);
        // printf("option2: %d\n", leftMostofRST(cur)->item);
        BTNode* rMLST = rightMostofLST(cur);
        BTNode* lMRST = leftMostofRST(cur);
        // printf("cur points to %d\n", cur->item);
        int hold = cur->item;

        if (rMLST!=NULL){
            cur->item = rMLST->item;
            rMLST->item = hold;
            // printf("cur->left: %d\n", cur->left->item);
            removeUtilR(cur->left, item);
        }
        else if (lMRST!=NULL){
            cur->item = lMRST->item;
            lMRST->item = hold;
            removeUtilL(cur->right, item);
        }
        else{
            cur -> item = cur->left->item;
            cur->left = cur->left->left;
        }

    }








}
