#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct _btnode{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

typedef struct _queueNode{
	BTNode *data;
	struct _queueNode *next;
}QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

//Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, BTNode * data);
int dequeue(Queue *qPtr);
BTNode* getFront(Queue q);
int isEmptyQueue(Queue q);

BTNode* createNode(int item);
void printBTNode(BTNode *root, int space, int left);
void deleteTree(BTNode **root);

BTNode* findLargestBST (BTNode* root);

int main()
{
    BTNode* root = NULL;
    BTNode* temp = NULL;
    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    int item;
    int flag=1;
    printf("Enter a list of numbers for a Binary Tree, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
    {
        if(root==NULL)
        {
            if(item!=-1){
                root =createNode(item);
                enqueue(&q,root);
            }
        }
        else{
            while(!isEmptyQueue(q)){
                temp = getFront(q);
                if(flag){
                    if(item != -1){
                        temp->left = createNode(item);
                        enqueue(&q,temp->left);
                    }
                    flag = 0;
                    break;
                }
                else if(temp->right==NULL){
                    if(item!=-1){
                        temp->right = createNode(item);
                        enqueue(&q,temp->right);
                    }
                    dequeue(&q);
                    flag=1;
                    break;
                }
                else  dequeue(&q);
            }
        }
    }
    scanf("%*s");
    printf("The input binary tree:\n");
    printBTNode(root,0,0);
    printf("\n");
    BTNode* BSTnode = findLargestBST (root);
    printf("The largest binary search subtree:\n");
    if(BSTnode)
        printBTNode(BSTnode,0,0);
    else
        printf("No BST\n");
    deleteTree(&root);

    return 0;
}

BTNode* createNode(int item)
{
    BTNode* node = (BTNode*) malloc(sizeof(BTNode));
	node->item = item;
	node->left = node->right = NULL;
	return node;
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
void enqueue(Queue *qPtr, BTNode *data){
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr){
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return 1;
    }
}

BTNode* getFront(Queue q){
    return q.head->data;
}

int isEmptyQueue(Queue q){
    if(q.size==0) return 1;
    else return 0;
}


// void appendSubtreeNodesToArray(BTNode* node, int arr[100]){
//     static int i = 0; // static declaration so that program keeps value of i, so that no overriding of values in array happens
//     if (node==NULL){return;}
//     printf("index %d cur iteration is %d\n",i, node->item);
//     arr[i] = node->item;
//     i++;
//     appendSubtreeNodesToArray(node->left, arr);
//     appendSubtreeNodesToArray(node->right, arr);
// }

Queue* appendNodesToQueue(Queue *q, BTNode* node){
    if (node==NULL){return q;}
    enqueue(q, node);
    appendNodesToQueue(q, node->left);
    appendNodesToQueue(q, node->right);
}

int min(Queue* q){
    int min = getFront(*q)->item;
    while (!isEmptyQueue(*q)){

        if (getFront(*q)->item < min){
            min = getFront(*q)->item;
        }
        
        dequeue(q);

    }
    
    return min;

}

int max(Queue* q){
    int max = getFront(*q)->item;
    while(!isEmptyQueue(*q)){
        if (getFront(*q)->item > max){
            max = getFront(*q)->item;
        }
        dequeue(q);
    }
    return max;
}

int count(Queue *q){
    int count = 0;
    while(!isEmptyQueue(*q)){
        count++;
        dequeue(q);
    }
    return count;
}

// int isLST(BTNode* root, int arr[100]){
//     int n=0;
//     appendSubtreeNodesToArray(root->left, arr);
//     while(arr[n]!=-1){
//         printf("arr element is %d\n", arr[n]);
//         if (root->item<arr[n]){
//             return 0; // means does not fulfil
//         }
//         n++;

//     }
//     return 1; // means fulfil
// }

// int highestBST(BTNode* root, int min, int max, int isTree){
//     highestBST(root->left, )
// }



// int isBST(BTNode* root, int min, int max){
//     if (root == NULL){return 1;}
//     if (root->item<min||root->item>max){
//         return 0;
//     }
//     return (isBST(root->left, min, root->item)&&isBST(root->right, root->item, max));
// }


//definition 1
// BTNode* findLargestBST(BTNode* root){
//     if (isBST(root, INT_MIN, INT_MAX)){
//         return root;
//     }
// }

// int* isBST(int* arr[3], BTNode* root, int maxL, int minR, int bt, int size){
//     *arr[0] = root->item;
//     if (root->item>maxL && root->item<minR && bt==1){
//         *arr[1] = 1; // 1 means it is a BST
//     }
//     Queue* q = (Queue*) malloc(sizeof(Queue));
//     appendNodesToQueue(q, root);
//     *arr[2] = count(q);
//     return *arr;
// }



BTNode* findLargestBST (BTNode* root)
{
    if (root==NULL){return NULL;}
    findLargestBST(root->left);
    findLargestBST(root->right);


    Queue* q = (Queue*) malloc(sizeof(Queue));
    q->head=NULL;
    q->tail=NULL;
    q->size=0;

    int maxL = INT_MIN;
    appendNodesToQueue(q, root->left);
    if (!isEmptyQueue(*q)){
        maxL = max(q);
    }


    q->head=NULL;
    q->tail=NULL;
    q->size=0;

    int minR = INT_MAX;
    appendNodesToQueue(q, root->right);
    if (!isEmptyQueue(*q)){
        minR = min(q);
    }

    q->head=NULL;
    q->tail=NULL;
    q->size=0;
    static int out[3];
    memset(out,-1,3);

    static int test[3];
    memset(test,-1,3);
    test[0] = -1;
    test[1] = -1;
    test[2] = -1;
    appendNodesToQueue(q, root);
    int size = count(q);

    if (root->item < minR && root->item > maxL){
        test[1] = 1&test[1];
        if (size>test[2]){
            test[2] = size;
            }
        }
    test[0] = root->item;

    

    
    static int temp_val = -1;

    if (test[1] == -1){
        temp_val = test[0];
    }


    if (root->left!=NULL && root->right!=NULL){
        if (root->left->item == temp_val || root->right->item == temp_val){

            test[1] = -1;
            temp_val = root->item;
        }

    }
    static int final_size = 0;
    static int element = 0;
    static int boo = 0;
    out[0] = element;
    out[1] = boo;
    out[2] = final_size;
    static BTNode* hold = NULL;
    
    if (test[1]==1 && test[2]>out[2]){
        element = test[0];
        boo = test[1];
        final_size = test[2];
        hold = root;
    }



    return hold;
}
