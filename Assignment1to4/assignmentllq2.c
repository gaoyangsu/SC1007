#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

typedef struct _linkedList{
    ListNode *head;
    int size;
}LinkedList;
void printListFunc(ListNode *list);
void printList(LinkedList ll);
void deleteList(LinkedList* llptr);

LinkedList rearrange (LinkedList ll);

int main()
{
    LinkedList ll;

    ll.head = NULL;
    ll.size = 0;
    ListNode* temp;

	int i = 0;

	while (scanf("%d", &i)){
		if (ll.head == NULL){
			ll.head = (ListNode*) malloc(sizeof(ListNode));
			temp = ll.head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = i;
		ll.size++;
	}
	temp->next = NULL;

	ll=rearrange(ll);

	printList(ll);
    deleteList(&ll);
	return 0;
}

void printList(LinkedList ll){
    ListNode* temp = ll.head;

    while(temp !=NULL){
        printf("%d ",temp->item);
        temp = temp->next;
    }
    printf("\n");
}

void printListFunc(ListNode *list){
    ListNode* temp=list;
    while(temp !=NULL){
        printf("%d ",temp->item);
        temp = temp->next;
    }
    printf("\n");
}

void deleteList(LinkedList* llptr){
    ListNode *cur = llptr->head;
    ListNode *temp;
    while (cur!= NULL) {
		temp=cur->next;
		free(cur);
		cur=temp;
	}
	llptr->head=NULL;
	llptr->size =0;
}

LinkedList rearrange (LinkedList ll){
// Write your code here
    ListNode *left, *right,*temp, *afterfirstswap, *aftersecondswap; 
    LinkedList afterswap;
    temp=ll.head;
    int i,index,count;
    afterfirstswap=malloc(sizeof(ListNode));
    ListNode *afterfirstswap1,*afterfirstswap2;
    afterfirstswap1=afterfirstswap;
    afterfirstswap2=afterfirstswap;
    int N;
    N=ll.size;
    
    left=temp;
    //printf("%d\n",left->item);
    count=1;
    while(count<=N/2){
        temp=temp->next;
        count++;
    }
    right=temp;
    //printf("%d\n",right->item);
    temp=ll.head;
    for(index=1;index<=N/2;index++){
        afterfirstswap1->item=right->item;
        //printf("%d\n",afterfirstswap1->item);
        right=right->next;
        afterfirstswap1->next=malloc(sizeof(ListNode));
        afterfirstswap1=afterfirstswap1->next;
        afterfirstswap1->item=left->item;
        //printf("%d\n",afterfirstswap1->item);
        left=left->next;
        afterfirstswap1->next=malloc(sizeof(ListNode));
        afterfirstswap1=afterfirstswap1->next;  
    }
    if (N%2!=0){ 
        afterfirstswap1->item=right->item;
        //printf("%d\n",afterfirstswap1->item);
        afterfirstswap1->next=malloc(sizeof(ListNode));
        afterfirstswap1=afterfirstswap1->next;
    }
    count=1;
    while(count<=N-1){
    afterfirstswap2=afterfirstswap2->next;
    count++;
    }
    afterfirstswap2->next=NULL;
    //printListFunc(afterfirstswap);
    afterfirstswap2=afterfirstswap;
    afterfirstswap1=afterfirstswap;

    //-----------after first swap ------------//
    
    aftersecondswap=malloc(sizeof(ListNode));
    ListNode *aftersecondswap1,*aftersecondswap2;
    aftersecondswap1=aftersecondswap;
    aftersecondswap2=aftersecondswap;
    temp=afterfirstswap;
    left=temp;
    //printf("%d\n",left->item);
    count=1;
    while(count<=N/2){
        temp=temp->next;
        count++;
    }
    right=temp;
    //printf("%d\n",right->item);
    for(index=1;index<=N/2;index++){
        aftersecondswap1->item=left->item;
        //printf("%d\n",afterfirstswap1->item);
        left=left->next;
        aftersecondswap1->next=malloc(sizeof(ListNode));
        aftersecondswap1=aftersecondswap1->next;
        aftersecondswap1->item=right->item;
        //printf("%d\n",afterfirstswap1->item);
        right=right->next;
        aftersecondswap1->next=malloc(sizeof(ListNode));
        aftersecondswap1=aftersecondswap1->next;  
    }
    if (N%2!=0){ 
        aftersecondswap1->item=right->item;
        //printf("%d\n",afterfirstswap1->item);
        aftersecondswap1->next=malloc(sizeof(ListNode));
        aftersecondswap1=aftersecondswap1->next;
    }
    count=1;
    while(count<=N-1){
    aftersecondswap2=aftersecondswap2->next;
    count++;
    }
    aftersecondswap2->next=NULL;
    //printListFunc(afterfirstswap);
    aftersecondswap2=aftersecondswap;
    aftersecondswap2=aftersecondswap;

    //------------------------------------------------------//

    afterswap.head=aftersecondswap;
    afterswap.size=N;

    return afterswap;

    
    //printf("%d\n",N);
}
