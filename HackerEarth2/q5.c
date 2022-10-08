#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 1000

enum ExpType {OPT,OPERAND};

typedef struct _queueNode
{
    int item;
    enum ExpType type;
    struct _queueNode *next;
}QueueNode;

typedef struct _queue{
    int size;
    QueueNode *head;
    QueueNode *tail;
}Queue;

void enqueue (Queue *qptr, int item, enum ExpType type);
int dequeue(Queue *qPtr);
QueueNode* getFront(Queue q);
int isEmptyQueue(Queue q);

void expressionQ(char *infix, Queue* qPtr);
void printExpQ(Queue* qPtr);

int main()
{
    char infix[SIZE];
    scanf("%[^\n]%*c",infix);

    Queue inExpQ;
    inExpQ.head = NULL;
    inExpQ.tail = NULL;
    inExpQ.size = 0;

    expressionQ(infix,&inExpQ);
    printf("Output:\n");
    printExpQ(&inExpQ);

    return 0;
}

void enqueue (Queue *qPtr, int item, enum ExpType type)
{
    QueueNode *newNode;
    newNode = (QueueNode*) malloc(sizeof(QueueNode));
    newNode->item = item;
    newNode->type = type;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head = newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail =newNode;
    qPtr->size++;

}
int dequeue(Queue *qPtr)
{
    if(qPtr == NULL || qPtr->head ==NULL)
        return 0;
    else{
        QueueNode *temp = qPtr->head;
        qPtr->head = qPtr->head->next;

        if(qPtr->head == NULL)
            qPtr->tail = NULL;

        free(temp);
        qPtr->size--;
        return 1;
    }
}

QueueNode* getFront(Queue q)
{
    return q.head;
}

int isEmptyQueue(Queue q){
   if(q.size==0) return 1;
    else return 0;
}

void printExpQ(Queue *qPtr){
    if(qPtr==NULL) return;

    QueueNode* temp = NULL;
    temp = getFront(*qPtr);

    while(temp!=NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
        else
            printf(" %c ",(char)(temp->item));
        dequeue(qPtr);
        temp = getFront(*qPtr);
    }
    printf("\n");

}

void concat(char arr[], char x){
    int len = strlen(arr);
    arr[len] = x;
}


void expressionQ(char *infix, Queue* qPtr){
// Write your code here
    int len = strlen(infix);
    // printf("len:%d\n ", len);
    char hold[100];
    memset(hold,0,100);

    for (int i=0;i<len;i++){

        if (isdigit(infix[i])){
            // printf("if loop\n");
            concat(hold,infix[i]);
        }
        else if (infix[i] == '('){
            enqueue(qPtr, infix[i], OPT);
        }
        else if (infix[i] == ')'){
            int x = atoi(hold);
            if (x==0){}
            else{
                enqueue(qPtr, x, OPERAND);
            }
            enqueue(qPtr, ')', OPT);
            memset(hold,0,100);
            int y = atoi(hold);
            if (y==0){}
            else{enqueue(qPtr,y,OPERAND);}
        }
        else{
            // printf("else loop\n");
            int x = atoi(hold);
            
            // sscanf(hold,"%d",&i);
            // printf("x: %d\n", x);
            if (x==0){}
            else{
                enqueue(qPtr, x, OPERAND);
                
            }
            enqueue(qPtr, infix[i], OPT);
            memset(hold,0,100);
             
        }

        }
    int x = atoi(hold);
    if (x==0){}
    else{enqueue(qPtr, x, OPERAND);}
        
    }
