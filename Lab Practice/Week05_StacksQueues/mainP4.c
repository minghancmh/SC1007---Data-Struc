#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void in2Pre(char*, char*);

int main()
{
    char infix[SIZE];
    char prefix[SIZE];

    printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c",infix);

    in2Pre(infix,prefix);
    printf("The prefix expression is \n");
    printf("%s\n",prefix);

    return 0;
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

void in2Pre(char* infix, char* prefix)
{
 //Write your code here
    Stack *sI = (Stack*) malloc(sizeof(Stack));
    sI->head = NULL;
    sI -> size = 0;
    int preIdx = 0;

    Stack *s = (Stack*) malloc(sizeof(Stack));
    s->head = NULL;
    s->size = 0;

    Stack *hold = (Stack*) malloc(sizeof(Stack));
    hold->head = NULL;
    hold->size = 0;


    for (int i=0; i<strlen(infix); i++){
        push(sI, infix[i]);
    }


    while(!isEmptyStack(*sI)){
       
       char ch = peek(*sI);
       printf("cur iter: %c\n", ch);
       pop(sI);

       if (ch!='+' && ch!= '-' && ch!= '*' && ch!= '/' && ch!=')' && ch!='('){
            printf("push to s\n");
            push(s, ch);
       }
       else if (ch==')'){
            printf("push ) to hold\n");
            push(hold, ')');
       }
       else if (ch == '('){
            printf("( case)\n");
            while(peek(*hold)!=')'){
                char toS = peek(*hold);
                pop(hold);
                push(s, toS);
            }
            pop(hold);
       }
       else if (!isEmptyStack(*hold) && ((ch=='+'||ch=='-')&&(peek(*hold)=='*'||peek(*hold)=='/'))){
            printf("precedence\n");
            printf("peek hold: %c\n", peek(*hold));
            while (!isEmptyStack(*hold) && peek(*hold)!='+' && peek(*hold)!='-' && peek(*hold)!=')'){
                printf("while\n");
                char toS = peek(*hold);
                printf("toS: %c\n", toS);
                pop(hold);
                // printf("peek hold is %c\n", peek(*hold));
                push(s, toS);
                printf("peeks is %c\n", peek(*s));
                printf("size of hold is %d\n", hold -> size);
            }
            if (!isEmptyStack(*hold) && peek(*hold)==')'){
                pop(hold);
            }
            printf("pushing to hold ch\n");
            push(hold, ch);
       }
       else{
            printf("push to hold\n");
            push(hold, ch);
       }

    }

    while(!isEmptyStack(*hold)){
        printf("hold enter\n");
        char fin = peek(*hold);
        pop(hold);
        push(s, fin);
    }

    while(!isEmptyStack(*s)){
        char out = peek(*s);
        printf("out: %c\n", out);
        pop(s);
        prefix[preIdx] = out;
        preIdx++;
    }












}