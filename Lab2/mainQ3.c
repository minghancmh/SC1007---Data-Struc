#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
{   Stack *s = (Stack*)malloc(sizeof(Stack));
    s->head = NULL;
    s->size =0;
    for (int i=0; i<strlen(postfix);i++){

        if (postfix[i]=='-'){
        
            double num1=peek(*s);
            pop(s);
            double num2=peek(*s);
            pop(s);
            double result = num2 - num1;
            // printf("result is %d\n", result);
            push(s,(result));

        }
        else if (postfix[i] == '+'){
            double num1=peek(*s);
            pop(s);
            double num2=peek(*s);
            pop(s);
            double result = num2 + num1;
            // printf("result is %d\n", result);
            push(s,(result));
        }
        else if (postfix[i] == '*'){
            double num1=peek(*s);
            pop(s);
            double num2=peek(*s);
            pop(s);
            double result = num2 * num1;
            // printf("result is %d\n", result);
            push(s,(result));
        }
        else if (postfix[i]=='/'){
            double num1=peek(*s);
            pop(s);
            double num2=peek(*s);
            pop(s);
            double result = num2/ num1;
            // printf("num1: %f\n", num1);
            // printf("num2:%f\n", num2);
            // printf("result is %f\n", result);
            push(s,(result));
        }
        else{push(s,postfix[i]-'0');}
    }

    double fin = peek(*s);
    return fin;
 //Write your code here



//9161/3+*+
//9163+*+
//919*+
//99+
//18

}
