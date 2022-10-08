#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;

typedef struct _stackNode{
	BTNode *data;
	struct _stackNode *next;
}StackNode;

typedef struct _stack
{
    int size;
	StackNode *top;
}Stack;

//Prototypes of Interface functions for Stack structure
void push(Stack *sPtr, BTNode *data);
int pop(Stack *sPtr);
BTNode* peek(Stack s);
int isEmptyStack(Stack s);


BTNode* insertBTNode(BTNode* cur, int item);
void removeAll(BTNode **node);
void printBTNode(BTNode *root, int space,int left);
void preOrder(BTNode* root);


void preOrderIterative(BTNode *root);

int main()
{
    BTNode* root=NULL;
    int item;

    printf("Enter a list of numbers for a Binary Tree, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
        root = insertBTNode(root, item);
    scanf("%*s");

    printBTNode(root,0,0);
    printf("preorder recursive \n");
    preOrder(root);
    printf("\n");
    printf("preorder iterative\n");
    preOrderIterative(root);

    removeAll(&root);

    return 0;
}

void push(Stack *sPtr, BTNode *data){
    StackNode *newNode;
    newNode= (StackNode *)malloc(sizeof(StackNode));
    newNode->data = data;
    newNode->next = sPtr->top;
    sPtr->top = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr==NULL || sPtr->top==NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->top;
       sPtr->top = sPtr->top->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

BTNode* peek(Stack s){
    return s.top->data;
}

int isEmptyStack(Stack s){
     if(s.size==0) return 1;
     else return 0;
}

BTNode* insertBTNode(BTNode* cur, int item){
    if (cur == NULL){
	BTNode* node = (BTNode*) malloc(sizeof(BTNode));
	node->item = item;
	node->left = node->right = NULL;
	return node;
	}
    printf("rand value is %d\n", rand()%2);
    if (rand()%2)
        {cur->left  = insertBTNode (cur->left, item);}
    else
        {cur->right = insertBTNode (cur->right, item);}

    return cur;
}

void removeAll(BTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
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

void preOrderIterative(BTNode *root)
{
    Stack *s = (Stack*) malloc(sizeof(Stack));
    s -> size = 0;
    s -> top = NULL;
    push(s, root);
    BTNode* c = NULL;
    // printf("root is %d\n", root ->item);

    while(!isEmptyStack(*s)){
        c = peek(*s);
        printf("%d ",c->item);
        pop(s);
        if (c->right!=NULL){push(s, c->right);}
        if (c->left!=NULL){push(s, c->left);}
    
    }

}

void preOrder(BTNode *root){
    if (root == NULL){return;}
    else {
        printf("%d ", root -> item);
        preOrder(root -> left);
        preOrder(root -> right);
    }
}
