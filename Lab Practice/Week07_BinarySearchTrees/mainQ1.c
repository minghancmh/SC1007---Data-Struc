#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

void insertBSTNode(BTNode** cur, int item);
void printBTNode(BTNode *root, int space, int left);
void deleteTree(BTNode **root);

int main()
{
    BTNode* root = NULL;
    int item;

    printf("Enter a list of numbers for a Binary Tree, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
        insertBSTNode(&root, item);
    scanf("%*s");

    printf("The Binary Search Tree:\n");
    printBTNode(root,0,0);

    deleteTree(&root);
    root=NULL;
    return 0;
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

void insertBSTNode(BTNode** cur, int item){
    //Write Your Code Here
    if (*cur == NULL){
        BTNode* t = (BTNode*) malloc(sizeof(BTNode));
        t->item=item;
        t->left = NULL;
        t->right = NULL;
        *cur = t;
    }
    else{
        BTNode* temp; 
        BTNode* pre;
        int flag = 0;

        temp = *cur;
        pre = temp;
        // printf("temp: %d\n", temp->item);

        if (item > temp->item){
            temp = temp->right;
            flag = -1;
        }
        else if (item < temp-> item){
            temp = temp-> left;
            flag = 1;
        }
        else {
            printf("Duplicated Item: %d\n", item);
        }


        while(temp!=NULL){
            if (item == temp->item){
                printf("Duplicated Item: %d\n", item);
                flag =0;
                break;
            }
            else if (item > temp->item){
                pre = temp;
                temp = temp->right;
                // pre->right = temp;
                flag = -1;
            }
            else if (item < temp->item){
                pre = temp;
                temp = temp->left;
                // pre->left = temp;
                flag = 1;
            }
        }

        if (flag == -1){
            BTNode* r = (BTNode*) malloc(sizeof(BTNode));
            r->item=item;
            r->left = NULL;
            r->right = NULL;
            pre->right = r;

        }
        else if (flag == 1){
            BTNode* l = (BTNode*) malloc(sizeof(BTNode));
            l->item=item;
            l->left = NULL;
            l->right = NULL;
            pre->left = l;
        }    
    }
    





}
