#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _btnode{
    int nodeV;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

typedef struct _queuenode{
    BTNode* node;
    struct _queuenode *next;
}QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

void printBTNode(BTNode *root, int space,int left);
//Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, BTNode * node);
int dequeue(Queue *qPtr);
BTNode* getFront(Queue q);
int isEmptyQueue(Queue q);

int twoNodesCost(BTNode* node, int nodeV1,int nodeV2);


int main()
{
    BTNode* root = (BTNode*) malloc(sizeof(BTNode));

    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    BTNode* node;
    enqueue(&q,root);

    int nodeV;
    char opL, opR;

    while(!isEmptyQueue(q)){
            scanf("%d %c %c",&nodeV,&opL,&opR);
            node = getFront(q);dequeue(&q);
            node->nodeV = nodeV;

            if(opL != '@'){
                node->left = (BTNode*) malloc(sizeof(BTNode));
                enqueue(&q,node->left);
            }
            else node->left =NULL;
            if(opR != '@'){
                node->right = (BTNode*) malloc(sizeof(BTNode));
                enqueue(&q,node->right);
            }
            else
                node->right = NULL;
    }

    int v1,v2;
    scanf("%d %d",&v1,&v2);
    int cost = twoNodesCost(root,v1,v2);

    printBTNode(root,0,0);

    printf("Distance is %d\n",cost);
    // printf("sum of toll is %d\n", valueOfPath(root, 7));


    return 0;
}

void enqueue(Queue *qPtr, BTNode *node){
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    newNode->node = node;
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
    return q.head->node;
}

int isEmptyQueue(Queue q){
    if(q.size==0) return 1;
    else return 0;
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

          printf("%d\n", root->nodeV);

          space++;
          printBTNode(root->left, space,1);
          printBTNode(root->right, space,0);
      }
}

// helper function to determine what is the value of the node at nodeV1 and nodeV2 (in the example case, node 5 and node 7)
int valueOfNode(BTNode* node, int nodeIdx){
    Queue *q = (Queue*) malloc(sizeof(Queue));
    q->head=NULL;
    q->tail=NULL;
    q->size=0;
    int idx = 0;
    int foundVal = node ->nodeV;
    BTNode *hold = NULL;
    enqueue (q, node);

    while (idx!=nodeIdx){
        hold = getFront(*q);
        if (hold->left!=NULL){enqueue(q, hold->left);}
        if (hold->right!=NULL){enqueue(q,hold->right);}
        dequeue(q);
        idx++;
    }

    return hold->nodeV;
}

int pathToNode(BTNode* root, int arr[100], int target, int idx){
    // printf("cur node is %d\n", root->nodeV);
    // printf("idx is %d\n", idx);

    if (root==NULL){return 0;}

    arr[idx] = root->nodeV;

    if (root->nodeV==target){
        // arr[idx] = root->nodeV;
        // printf("found!");
        // printf("index is %d\n", idx);
        // printf("value is %d\n", root->nodeV);
        return 1;
    }
    if (pathToNode(root->left, arr, target, idx+1)||pathToNode(root->right, arr, target, idx+1)){
        return 1;
        }
        else {
            // printf("else\n");
            arr[idx]=0;
            return 0;
        }

    return 0;
    
    
    

    // if (root->left!=NULL){printf("if root left loop\n");pathToNode(root->left, arr, target, idx+1);}
    
    // else if (root->right!=NULL){printf("if root right loop\n");pathToNode(root->right, arr, target, idx+2);}



    // return 0;
}   






int twoNodesCost(BTNode* node, int nodeV1,int nodeV2)
{
    // int valNodeV1 = valueOfNode(node, nodeV1);
    // int valNodeV2 = valueOfNode(node, nodeV2);
    // printf("val of 9th node is %d\n", valNodeV2);
    if (nodeV1==nodeV2){return nodeV1;}
    else{
        int n=0;
        int arr[100];
        int arr2 [100];
        memset(arr,-1,100);
        memset(arr2, -1, 100);
        pathToNode(node, arr, nodeV1, 0);
        pathToNode(node, arr2, nodeV2, 0);

        // printf("arr element is %d\n", arr[0]);
        // printf("arr2 element is %d\n", arr[1]);

        while (arr[n]!=-1){
            printf("arr element: %d\n", arr[n]);
            n++;
        }
        n=0;
        while (arr2[n]!=-1){
            printf("arr2 element: %d\n", arr2[n]);
            n++;
        }
        n=0;
        int sumArr = 0;
        int sumArr2 = 0;
        
        while (1){
            sumArr+=arr[n];
            if (arr[n]==nodeV1){break;}
            n++;
        }
        n=0;
        while (1){
            sumArr2+=arr2[n];
            if (arr2[n]==nodeV2){break;}
            n++;
        }

        int total = sumArr + sumArr2;

        n=0;
        int idx = 0;

        while (arr[n]==arr2[n]){
            total-=arr[n]*2;
            n++;
            idx++;
        }

        total += arr[idx-1];


        // printf("v1 %d\n", valNodeV1);
        // printf("v2 %d\n", valNodeV2);
        // printf("arr1 sum %d\n", sumArr);
        // printf("arr2 sum %d\n", sumArr2);
        // printf("idx is %d\n", idx);
        
        return total;

    }
    
}

