#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000 //The limit of expression length

typedef struct _stackNode{
    double item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, double item);
int pop(Stack *sPtr);
double peek(Stack s);
int isEmptyStack(Stack s);

double exePostfix(char*);

int main()
{
    char postfix[SIZE];

    printf("Enter a postfix expression:\n");
    scanf("%[^\n]%*c",postfix);

    printf("The answer is %.2lf.\n",exePostfix(postfix));

    return 0;
}

void push(Stack *sPtr, double item){
    StackNode *newNode;
    newNode = (StackNode *) malloc(sizeof(StackNode));
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

double peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

double exePostfix(char* postfix)
{
 //Write your code here
    Stack* s = (Stack*) malloc(sizeof(Stack));
    s->head = NULL;
    s-> size = 0;

    for (int i = 0; i<strlen(postfix); i++){
        // printf("postfix: %c\n", postfix[i]);

        if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/'){
            double op2 = peek(*s);
            pop(s);
            double op1 = peek(*s);
            pop(s);
            if (postfix[i] == '+'){
                double result = op1+op2;
                push(s, result);
            }
            else if (postfix[i] == '-'){
                double result = op1-op2;
                push(s, result);
            }
            if (postfix[i] == '*'){
                double result = op1*op2;
                push(s, result);
            }
            if (postfix[i] == '/'){
                double result = op1/op2;
                push(s, result);
            }
        }
        else{
            double toStack = postfix[i] - '0';
            // printf("ts: %f\n", toStack);
            push(s, toStack);
        }

    }

    double fin = peek(*s);
    return fin;

    







}