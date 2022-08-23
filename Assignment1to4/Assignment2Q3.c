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
{
// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
    int N;
    CDblListNode *temp,*A,*B,*dxnptr;
    N= CDLL.size;
    if(N==0||N==1) return 0;
    else if (N==2) return 1;
    else if (N==3) return 3;
    else if (N>=4){
        int Nchange=N;
        temp=CDLL.head;
        A=temp;
        B=temp->next->next;
        //printf("%p\n",A);
        //printf("%p\n",temp);
        //printf("%p\n",B);
        int i,hmin,boolean; 
        int sum=0;
        for(i=0;i<(Nchange-3);i++){
            //printf("%d\n",B->item);//figure out the number of pairs for the first number 
            if((A->item)<(B->item)){
                
                dxnptr=A;
                hmin=A->item;
                while(dxnptr!=B){
                    //printf("dxnptr-->%d\n",dxnptr->item);
                    if (dxnptr->pre==B) {
                        boolean=1;
                        break;
                        }
                    if((dxnptr->pre->item)>hmin){
                        boolean=0;
                        break;
                        }
                    boolean=0;
                    dxnptr=dxnptr->pre;
                }
                if(boolean==0){
                    dxnptr=A;
                    hmin=A->item;
                    while(dxnptr!=B){
                    //printf("dxnptr-->%d\n",dxnptr->item);
                    if (dxnptr->next==B) {
                        boolean=1;
                        break;
                        }
                    if((dxnptr->next->item)>hmin){
                        boolean=0;
                        break;
                        }
                    boolean=0;
                    dxnptr=dxnptr->next;
                    }
                }
                if(boolean==1) sum++;
            }
            else{
                dxnptr=B;
                hmin=B->item;
                while(dxnptr!=A){
                    //printf("dxnptr-->%d\n",dxnptr->item);
                    if ((dxnptr->pre)==A) {
                        boolean=1;
                        break;
                        }
                    if((dxnptr->pre->item)>hmin){
                        boolean=0;
                        break;
                        }
                    boolean=0;
                    //printf("boolean-->%d\n",boolean);
                    
                    dxnptr=dxnptr->pre;
                }
                //printf("boolean-->%d\n",boolean);

                if(boolean==0){
                    dxnptr=B;
                    hmin=B->item;
                    while(dxnptr!=A){
                    //printf("dxnptr-->%d\n",dxnptr->item);
                    if (dxnptr->next==A) {
                        boolean=1;
                        break;
                        }
                    if((dxnptr->next->item)>hmin){
                        boolean=0;
                        break;
                        }
                    boolean=0;
                    //printf("dxnptr-->%d\n",dxnptr->item);
                    dxnptr=dxnptr->next;
                    }
                }
            //printf("boolean-->%d\n",boolean);
            if(boolean==1) sum++;
            }
        B=B->next;
        }
        //printf("-->%d\n",sum);
        
        //------------------------------------------------------------------------------------//
        temp=((CDLL.head)->next);
        //printf("%d\n",temp->item);
        int count=1;
        int value=Nchange;
        while (count != (Nchange-2)){ //for subsequent digits
            A=temp;
            B=temp->next->next;
            //printf("%p\n",A);
            //printf("%p\n",temp);
            //printf("%p\n",B);
            
            for(i=0;i<(value-3);i++){
                //printf("%d\n",B->item); //figure out the number of pairs for the first number 
            if((A->item)<(B->item)){
                dxnptr=A;
                hmin=A->item;
                while(dxnptr!=B){
                    //printf("dxnptr-->%d\n",dxnptr->item);
                    if (dxnptr->pre==B) {
                        boolean=1;
                        break;
                    }
                    if((dxnptr->pre->item)>hmin){
                        boolean=0;
                        break;
                    }
                    boolean=0;
                    dxnptr=dxnptr->pre;
                }
                if(boolean==0){
                    dxnptr=A;
                    hmin=A->item;
                    while(dxnptr!=B){
                    //printf("dxnptr-->%d\n",dxnptr->item);
                    if (dxnptr->next==B) {
                        boolean=1;
                        break;
                    }
                    if((dxnptr->next->item)>hmin){
                        boolean=0;
                        break;
                    }
                    boolean=0;
                    dxnptr=dxnptr->next;
                    }
                }
                if(boolean==1) sum++;
            }
            else{
                dxnptr=B;
                hmin=B->item;
                while(dxnptr!=A){
                    //printf("dxnptr-->%d\n",dxnptr->item);
                    if (dxnptr->pre==A) {
                        boolean=1;
                        break;
                    }
                    if((dxnptr->pre->item)>hmin){
                        boolean=0;
                        break;
                    }
                    boolean=0;
                    dxnptr=dxnptr->pre;
                }
                if(boolean==0){
                    dxnptr=B;
                    hmin=B->item;
                    while(dxnptr!=A){
                    //printf("dxnptr-->%d\n",dxnptr->item);
                    if (dxnptr->next==A) {
                        boolean=1;
                        break;
                    }
                    if((dxnptr->next->item)>hmin){
                        boolean=0;
                        break;
                    }
                    boolean=0;
                    dxnptr=dxnptr->next;
                }
                }
            if(boolean==1) sum++;
            }
        
        B=B->next;
        }
        //printf("-->%d\n",sum);
        count++;
        temp=temp->next;
        //printf("%d\n",temp->item);
        value--;

        }
    sum=sum+Nchange;
    return sum;
    }
}




