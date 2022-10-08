#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 1000 //The limit of expression length

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

void in2Post(char*, char*);

int main()
{
    char infix[SIZE];
    char postfix[SIZE];

    printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c",infix);

    in2Post(infix,postfix);
    printf("The postfix expression is \n");
    printf("%s\n",postfix);
    return 0;
}

void push(Stack *sPtr, char item){
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

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

void in2Post(char* infix, char* postfix)
{
 //Write your code here
    Stack *s = (Stack*) malloc(sizeof(Stack));
    s -> head = NULL;
    s -> size = 0;
    int j=0;


    for (int i=0; i<strlen(infix); i++){
        
        if (isalnum(infix[i])){
            postfix[j] = infix[i];
            j++;
        }
        else if (infix[i] == '('){
            push(s,'(');
        }
        else if (infix[i]==')'){
            while(peek(*s)!='('){
                postfix[j] = peek(*s);
                j++;
                pop(s);
            }
            pop(s);
        }
        else {
            while (!isEmptyStack(*s) && infix[i] != ')' && (((peek(*s)=='*')||(peek(*s)=='/')||(peek(*s) == '+') || (peek(*s)=='-')) && ((infix[i] == '+')||(infix[i] == '-')))){
                // printf("peek s is %c\n", peek(*s));
                postfix[j] = peek(*s);
                j++;
                pop(s);
            }
            push(s,infix[i]);
        }
        
    }

    while(!isEmptyStack(*s)){
        postfix[j] = peek(*s);

        // postfix[j] = peek(*s);
        j++;
        pop(s);
    }
 

 
 
 
}