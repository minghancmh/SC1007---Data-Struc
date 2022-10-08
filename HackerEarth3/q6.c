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
    // make the head of the tree
    BTNode *headNode = (BTNode*) malloc(sizeof(BTNode));
    headNode -> id = preO[0];
    *node = headNode;

    // headNode -> left = preO[1];

    char leftSubtree[MAX_N];
    memset(leftSubtree,0,MAX_N);
    char rightSubtree[MAX_N];
    memset(rightSubtree,0,MAX_N);
    int post = 0;
    int ls = 0;
    int rs = 0;
    while(postO[post]!=preO[1]){
        leftSubtree[ls] = postO[post];
        ls++;
        post++;
    }
    leftSubtree[ls] = postO[post];
    post++;

    // printf("left subtree is %s\n", leftSubtree);

    while (postO[post] != '\0'){
        rightSubtree[rs] = postO[post];
        post++;
        rs++;
    }
    // printf("right subtree is %s\n", rightSubtree);

    char revLeft[strlen(leftSubtree)];
    memset(revLeft, 0, strlen(leftSubtree));
    char revRight[strlen(rightSubtree)];
    memset(revRight, 0, strlen(rightSubtree));


    ls = 0; // reversing post order left subtree
    for (int n=strlen(leftSubtree)-1; n>=0; n--){
        revLeft[ls] = leftSubtree[n];
        ls++;
    }
    printf("left post subtree is now %s\n", revLeft);

    rs = 0; // reversing post order right subtree
    for (int n=strlen(rightSubtree)-2; n>=0; n--){
        revRight[rs] = rightSubtree[n];
        rs++;
    }
    printf("right post subtree is now %s\n", revRight);

    ls = 1;

    char preLeft[MAX_N];
    char preRight [MAX_N];
    int n=0;
    for (int i=ls; i<strlen(revLeft)+1; i++){
        preLeft[n] = preO[i];
        n++;
        ls = i;
    }
    n=0;
    ls++;
    // printf("ls is %d\n", ls);
    for (int i=ls; i<strlen(preO); i++){
        preRight[n] = preO[i];
        n++;
    }
    printf("left pre subtree is now %s\n", preLeft);
    printf("right pre subtree is now %s\n", preRight);

    ls = 0;
    rs = 0;
    BTNode *cur = *node;
    BTNode* lN = (BTNode*) malloc(sizeof(BTNode));
    BTNode* rN = (BTNode*) malloc(sizeof(BTNode));
    cur -> left = lN;
    cur -> right = rN;
    lN -> id = preLeft[ls];
    rN -> id = preRight[rs];
    while (revLeft[ls]!='\0' || revRight[rs]!='\0'){
        if (preLeft[ls] == revLeft[ls]){
            lN -> left = (BTNode*) malloc(sizeof(BTNode));
            lN -> left -> id = preLeft[ls]; 
            lN -> right = NULL;
            lN = lN -> left;
        }
        else {
            lN -> left = (BTNode*) malloc(sizeof(BTNode));
            lN -> left -> id = preLeft[ls];
            lN -> right = (BTNode*) malloc(sizeof(BTNode));
            lN -> right -> id = revLeft[ls];
        }


    }

}