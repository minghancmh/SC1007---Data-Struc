#include <stdio.h>
#include <stdlib.h>

typedef struct _dbllistnode
{
    int  item;
	struct _dbllistnode *next;
	struct _dbllistnode *pre;
} CDblListNode;

typedef struct _dbllinkedlist{
   int size;
   CDblListNode *head;
} CDblLinkedList;

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value);
void deleteList(CDblLinkedList *ptrCDLL);
void printList(CDblLinkedList CDLL);

int numMountainPairs(CDblLinkedList CDLL);

int main()
{
    CDblLinkedList himalayas;
    himalayas.head = NULL;
    himalayas.size = 0;

    int item;
    int i,cases;
    int numP;
    scanf("%d",&cases);
    for(i=0; i<cases; i++)
    {
        while(scanf("%d",&item))
            insertNode_AtFront(&himalayas, item);
        scanf("%*s");

        numP = numMountainPairs(himalayas);
        printList(himalayas);
        printf("%d Pairs.\n",numP);

        deleteList(&himalayas);
    }
    return 0;
}

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value){
      //create a new node
      CDblListNode* newNode;
      newNode = (CDblListNode *) malloc(sizeof(CDblListNode));
      newNode->item = value;

      if(ptrCDLL->size==0) //first node
      {
          newNode->next = newNode;
          newNode->pre = newNode;
          ptrCDLL->head = newNode;
      }
      else{
        newNode->next = ptrCDLL->head;
        newNode->pre = ptrCDLL->head->pre;

        newNode->pre->next = newNode; //update last node next link;
        ptrCDLL->head->pre = newNode;

        ptrCDLL->head = newNode;
      }
      ptrCDLL->size++;
}

void printList(CDblLinkedList CDLL){

    if(CDLL.head==NULL) return;

    CDblListNode* temp = CDLL.head;
    printf("Current List: ");

    while (temp->next != CDLL.head){
        printf("%d ", temp->item);
        temp = temp->next;

    }
    printf("%d\n",temp->item);
}

void deleteList(CDblLinkedList *ptrCDLL){
    if(ptrCDLL->head==NULL) return;
    CDblListNode *cur = ptrCDLL->head;
    CDblListNode *temp;

    while (cur->next!= ptrCDLL->head) {
        temp=cur->next;
        free(cur);
        cur=temp;
    }

    free(cur);
    ptrCDLL->head =NULL;
    ptrCDLL->size =0;

}



int numMountainPairs(CDblLinkedList CDLL)
{   int llsize = CDLL.size;
    int cwMax;
    int acwMax;
    int numPairs = 0;
    CDblListNode* head = CDLL.head;
    CDblListNode* cur; // to set end node and see if it can be seen
    CDblListNode* cwT; // to traverse in the cloclwise direction
    CDblListNode* acwT; // to traverse in the anticlockwise direction


    for (int i=0; i<llsize; i++){
        cur = head -> next;
        while (cur!=head){ // set the end node to be cur, traverse through the list
            // printf("cur points to %d\n", (*cur).item);
            cwT = head -> next; //cwT should be 
            acwT = head -> pre;
            cwMax = 0;
            acwMax = 0;
            int flag = 0;
            if (cwT == cur){printf("pair is %d and %d\n", (*cur).item, (*cwT).item);numPairs++;}
            else{
                // printf("else");
                while (cwT != cur){
                    if (cwT -> item > cwMax){cwMax = cwT -> item;}
                    cwT = cwT -> next;
                }
                if (cwMax <= head -> item && cwMax <= cur -> item){printf("pair is %d and %d\n", (*cur).item, (*cwT).item);flag = 1;}

                while (acwT != cur){
                    if (acwT -> item > acwMax){acwMax = acwT -> item;}
                    acwT = acwT -> pre;
                }
                if (acwMax <= head -> item && acwMax <= cur -> item){printf("pair is %d and %d\n", (*cur).item, (*cwT).item);flag = 1;}
            }
            if (flag == 1){numPairs++;}
            cur = cur -> next;
            // printf("loop run\n");
        }

        // printf("head points to %d\n", (*head).item);
        head = head -> next;
    }



    return numPairs/2;
}