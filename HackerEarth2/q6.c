#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SIZE 1000 //The size of the array

enum ExpType {OPT,OPERAND};

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

typedef struct _listnode
{
    int  item;
    enum ExpType type;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item,enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);


void in2PreLL(char* infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExp);

int main()
{
    char infix[SIZE];

    //printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c",infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

void printExpLL(LinkedList inExpLL)
{
    ListNode* temp = NULL;
    temp = inExpLL.head;
    while(temp!= NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
        else
            printf(" %c ",(char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if(newNode==NULL) exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head=newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if(LLPtr==NULL || LLPtr->size==0){
        return 0;
    }
    else{
       ListNode *temp = LLPtr->head;
       LLPtr->head = LLPtr->head->next;

       free(temp);
       LLPtr->size--;
       return 1;
    }
}

int isEmptyLinkedList (LinkedList ll) {
    if(ll.size==0) return 1;
    else return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
	while(deleteNode(LLPtr));
}

void push(Stack *sPtr, char item){
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

void concat(char arr[], char x){
    int len = strlen(arr);
    arr[len] = x;
}


void in2PreLL(char* infix, LinkedList *inExpLL)
{
    //Write your code here
    int len = strlen(infix);
    char hold[100];
    memset(hold,0,100);
    LinkedList temp;

    for (int i=0; i<len; i++){ // reverse iterate thru infix expression
        if (isdigit(infix[i])){
            // printf("if loop\n");
            concat(hold,infix[i]);
        }
        else if (infix[i] == '('){
            insertNode(&temp, infix[i], OPT);
            // enqueue(qPtr, infix[i], OPT);
        }
        else if (infix[i] == ')'){
            int x = atoi(hold);
            if (x==0){}
            else{
                insertNode(&temp, x, OPERAND);
                // enqueue(qPtr, x, OPERAND);
            }
            insertNode(&temp, ')', OPT);
            // enqueue(qPtr, ')', OPT);
            memset(hold,0,100);
            int y = atoi(hold);
            if (y==0){}
            else{
                insertNode(&temp,y,OPERAND);
                // enqueue(qPtr,y,OPERAND);
                }
        }
        else{
            // printf("else loop\n");
            int x = atoi(hold);
            
            // sscanf(hold,"%d",&i);
            // printf("x: %d\n", x);
            if (x==0){}
            else{
                // enqueue(qPtr, x, OPERAND);
                insertNode(&temp,x,OPERAND);
                
            }
            insertNode(&temp,infix[i], OPT);
            // enqueue(qPtr, infix[i], OPT);
            memset(hold,0,100);
             
        }

        }
    int x = atoi(hold);
    if (x==0){}
    else{
        insertNode(&temp,x,OPERAND);
        // enqueue(qPtr, x, OPERAND);
        }

    // printExpLL(temp);
    // printExpLL(*inExpLL);

    Stack *s = (Stack*) malloc(sizeof(Stack));
    ListNode* cur = temp.head;

    while (cur!=NULL){
        if (cur->type==OPERAND){
            // printf("curr point to %d\n", cur->item);
            insertNode(inExpLL,cur->item,OPERAND);
        }
        else if (cur->item == ')'){
            // printf("cur is )\n");
            push(s, cur->item);
        }
        else if (cur->item == '('){
            // printf("cur is (\n");

            while (peek(*s)!=')'){
                // printf("peekasssss is %c\n",peek(*s));
                // printExpLL(*inExpLL);
                // printf("elif2while\n");
                // if (peek(*s)=='-'){insertNode(inExpLL,'-',OPT);}
                // else if (peek(*s)=='+'){insertNode(inExpLL,'+',OPT);}
                // else if (peek(*s)=='*'){insertNode(inExpLL,'*',OPT);}
                // else if (peek(*s)=='/'){insertNode(inExpLL,'/',OPT);}
                insertNode(inExpLL,peek(*s),OPT);
                pop(s);
            }
            pop(s);
        }
        // printf("peek s is %c\n",peek(*s));
        
        else{
            while(!isEmptyStack(*s) && cur->item !=')' && ((peek(*s)=='/' || peek(*s)=='*')&&(cur->item=='+'||cur->item=='-'))){
                // printf("peek s is %c\n",peek(*s));
                if (peek(*s)=='-'){insertNode(inExpLL,'-',OPT);}
                else if (peek(*s)=='+'){insertNode(inExpLL,'+',OPT);}
                else if (peek(*s)=='*'){insertNode(inExpLL,'*',OPT);}
                else if (peek(*s)=='/'){insertNode(inExpLL,'/',OPT);}
                // insertNode(inExpLL,peek(*s),OPT);
                pop(s);
            }
        push(s,cur->item);  
        }
        // printExpLL(*inExpLL);
        
        
        cur = cur -> next;
    }
    while (!isEmptyStack(*s)){
            // printf("peek s is %c\n", peek(*s));
            insertNode(inExpLL,peek(*s),OPT);
            pop(s);
        }

    }




