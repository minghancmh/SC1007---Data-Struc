#include <stdio.h>
#include <stdlib.h>

#define MAX_N 120

typedef struct _btnode{ //node pointers/symbols you can use
    char id;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

void buildTree(BTNode** node, char* preO, char* postO);
void inOrder(BTNode *cur);
void preOrder(BTNode *cur);
void postOrder(BTNode *cur);

int main()
{
    char preO[MAX_N];
    char postO[MAX_N];
    scanf("%s",preO);
    scanf("%s",postO);

    BTNode* root=NULL;
    buildTree(&root,preO,postO);
    if(root==NULL) printf("error\n");
    preOrder(root);
    printf("\n");
    postOrder(root);
    printf("\n");

    inOrder(root);
    printf("\n");

    return 0;
}
void inOrder(BTNode *cur){
    if (cur == NULL)
        return;

    inOrder(cur->left);
    printf("%c",cur->id);
    inOrder(cur->right);
}
void preOrder(BTNode *cur){
    if (cur == NULL)
        return;

    printf("%c",cur->id);
    preOrder(cur->left);
    preOrder(cur->right);
}
void postOrder(BTNode *cur){
    if (cur == NULL)
        return;

    postOrder(cur->left);
    postOrder(cur->right);
    printf("%c",cur->id);
}

struct _btnode* insertNode( char item)
{
    BTNode *temp;
    temp = (BTNode*) malloc(sizeof(BTNode));
    temp->id = item;
    temp->left = temp->right = NULL;
    return temp;
}

#include <string.h>

struct _btnode* construct(char* preO, char* postO, int i, int m, int j, int k){ //construct(pre[] index, first post[] index, second post[] index)
        BTNode* node = insertNode(preO[i]); //for the first loop: set the first char of preO as root
        i++; //update preO index

        //search for item in pre in post
        while(preO[i] != postO[j] && j<k) //j is now at same number as i
        {
            j++;
        }

        while(preO[m] != postO[j+1] && m>i) //m is now at same number as j+1
        {
            printf("m: %d\n", preO[m]);
            printf("i: %d\n", preO[i]);
            m--;
        }

        if(m>i)
        { 
            node->left = construct(preO, postO, i, m, 0, j);
            preO[strlen(preO)-m] = '\0';
            printf("new LHS preO: %s \n", preO); 
            postO[strlen(postO)-m] = '\0';
            printf("new LHS postO: %s \n", preO); 
            //printf("node->left\n");
            
        }

        if(j<k)
        {
            node->right = construct(preO, postO, m, strlen(preO)-1, j+1, strlen(postO)-1);
            preO += m;
            printf("new RHS preO: %s\n", preO);
            postO += (j+1);
            printf("new RHS postO: %s\n", postO);
            //printf("node->right\n");
        }

        if(j==k)
        {
            return node;
        }

        if(m==i)
        {
            return node;
        }

        if(i>=sizeof(preO) || i >m || k<j){
            return NULL;
        }

        return node;
    }
//preO and postO are string variables
void buildTree(BTNode** node, char* preO, char* postO) //use pre-order and post-order to produce in-order
{
    /*initiate the pointers*/
    //BTNode *cur;
    BTNode *left;
    BTNode *right;

    printf("string length is %lu\n", strlen(preO));

    /*index for pre and post strings*/
    int i = 0; //first index for pre string
    int m = strlen(preO)-1; //second index for pre string
    printf("this is int m %d", m);
    int j = 0; //first index for post string
    int k = strlen(postO) - 1; //second index for post string

    *node = construct(preO, postO, i, m, j , k);
}