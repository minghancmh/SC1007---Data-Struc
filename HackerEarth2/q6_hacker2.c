#include <stdio.h>
#include <stdlib.h>

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
#include <string.h>
#include <ctype.h>

void concat(char arr[], char x){
    int len = strlen(arr);
    arr[len] = x;
}

LinkedList* expressionQ(char *infix, LinkedList* temp){
// Write your code here
    int len = strlen(infix);
    char hold[100];
    memset(hold,0,100);

    for (int i=0;i<len;i++){

        if (isdigit(infix[i])){
            concat(hold,infix[i]);
        }
        else if (infix[i] == '('){
            insertNode(temp, infix[i], OPT);

        }
        else if (infix[i] == ')'){
            int x = atoi(hold);
            if (x==0){}
            else{
                insertNode(temp, x, OPERAND);

            }
            insertNode(temp,')',OPT);

            memset(hold,0,100);
            int y = atoi(hold);
            if (y==0){}
            else{insertNode(temp,y,OPERAND);}
        }
        else{
            int x = atoi(hold);
            

            if (x==0){}
            else{
                insertNode(temp,x,OPERAND);

                
            }
            insertNode(temp,infix[i],OPT);

            memset(hold,0,100);
             
        }

        }
    int x = atoi(hold);
    if (x==0){}
    else{insertNode(temp,x,OPERAND);}
    
    return temp;
    }
void in2PreLL(char* infix, LinkedList *inExpLL)
{
    //Write your code here
    LinkedList *fin = (LinkedList*) malloc(sizeof(LinkedList));
    expressionQ(infix, fin); // reverse the input and forward iterate through

    


    Stack *s = (Stack*) malloc(sizeof(Stack));
    ListNode* cur = fin->head;

    while (cur!=NULL){
        if (cur->type==OPERAND){
            insertNode(inExpLL,cur->item,OPERAND);

        }
        else if (cur->item == ')'){
            push(s, cur->item);
        }
        else if (cur->item == '('){
            while (peek(*s)!=')'){
                insertNode(inExpLL,peek(*s),OPT);
                pop(s);
            }
            pop(s);
        }

        
        else{
            while(!isEmptyStack(*s) && cur->item !=')' && ((peek(*s)=='/' || peek(*s)=='*')&&(cur->item=='+'||cur->item=='-'))){
                insertNode(inExpLL,peek(*s),OPT);
                pop(s);
            }
        push(s,cur->item);  
        }

        cur = cur -> next;
    }
    while (!isEmptyStack(*s)){
            insertNode(inExpLL,peek(*s),OPT);
            pop(s);
        }
    }





