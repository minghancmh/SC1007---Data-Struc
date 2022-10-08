#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 120

typedef struct _btnode{
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


void buildTree(BTNode** node, char* preO, char* postO)
{   
    int i=0;
    *node = (BTNode*) malloc(sizeof(BTNode));
    (**node).id = preO[i];
    // int lenPre = strlen(preO);
    // int lenPost = strlen(postO);

    char postOut[MAX_N];
    memset(postOut, 0, MAX_N);
    while (postO [i] != preO[1]){
        postOut[i] = postO[i];
        i++;
    }
    postOut[i] = postO[i];

    char postROut[MAX_N];
    memset(postROut, 0, MAX_N);
    int n = 0;
    i++;
    while (postO[i]!=preO[n]){
        postROut[n] = postO[i];
        n++;
        i++;
    }

    char preOut[MAX_N]; 
    memset(preOut, 0, MAX_N);
    
    for (i=1; i<strlen(postOut)+1; i++){
        preOut[i-1] = preO[i];
    }
    n=0;
    char preROut[MAX_N];
    memset(preROut, 0, MAX_N);
    // printf("string preOut %lu, string preO %lu\n", strlen(preOut), strlen(preO));
    for (i=strlen(preOut)+1; i<strlen(preO); i++){
        // printf("preOut %c\n", preOut[i]);
        preROut[n] = preO[i];
        n++;
    }
    // printf("==========================\n");
    // printf("preout is %s\n", preOut);
    // printf("postout is %s\n", postOut);
    // printf("preROut is %s\n", preROut);
    // printf("postROut is %s\n", postROut);
    // printf("============================\n");

    if (strlen(preOut)!=0 && strlen(postOut)!=0){
        buildTree(&((*node)->left), preOut, postOut);
    }

    if (strlen(preROut)!=0 && strlen(postROut)!=0){
        buildTree(&((*node)->right), preROut, postROut);

    }
    
    // buildTree(&((*node)->right), preOut, postOut);

   
    // buildTree((**node).left, )




    
}