#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

void triPartition(ListNode** head, int pivot);

int main()
{
    ListNode *head = NULL, *temp;
	int i = 0;
	int pivot = 0;

	scanf("%d",&pivot);

	while (scanf("%d", &i)){
		if (head == NULL){
			head = (ListNode*) malloc(sizeof(ListNode));
			temp = head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = i;
	}
	temp->next = NULL;


	triPartition(&head, pivot);
	printList(head);
	deleteList(&head);

	return 0;
}

void printList(ListNode *head){
    while(head !=NULL){
        printf("%d ",head->item);
        head = head->next;
    }
    printf("\n");
}

void deleteList(ListNode **ptrHead){
    ListNode *cur = *ptrHead;
    ListNode *temp;
    while (cur!= NULL) {
		temp=cur->next;
		free(cur);
		cur=temp;
	}
	*ptrHead=NULL;
}

void triPartition(ListNode** head, int pivot){

// Write your code here
ListNode *listbigger,*listsame,*listsmaller,*temp;

int count=0,k=0,boolean=0;
temp=*head;
//---------------------small------------------------//
ListNode *listsmaller1,*listsmaller2;
listsmaller=malloc(sizeof(ListNode));
listsmaller1=listsmaller;
listsmaller2=listsmaller;
while(temp!=NULL){
    if((temp->item)<pivot){
        listsmaller1->item=temp->item;
        //printf("%d\n",listsmaller1->item);
        listsmaller1->next=malloc(sizeof(ListNode));
        listsmaller1=listsmaller1->next;
        count++;
    }
    temp=temp->next;
}
temp=*head;
    while(k<count-1){
        listsmaller2=listsmaller2->next;
        k++;
    }
    listsmaller2->next=NULL;
    //printList(listsmaller);

count=0;
k=0;
//---------------------same and bigger------------------------//
while(temp!=NULL){
    if(temp->item == pivot) {
        boolean=1; //boolean 1 means same + bigger, 0 means just bigger
        break;
    }
    temp = temp->next;
}
temp = *head;
if (boolean==1){
    temp=*head;
    ListNode *listsame1,*listsame2;
    listsame=malloc(sizeof(ListNode));
    listsame1=listsame;
    listsame2=listsame;
    while(temp!=NULL){
        if((temp->item)==pivot){
            listsame1->item=temp->item;
            //printf("%d\n",listsame1->item);
            listsame1->next=malloc(sizeof(ListNode));
            listsame1=listsame1->next;
            count++;
        }
        temp=temp->next;
}
temp=*head;
    while(k<count-1){
        listsame2=listsame2->next;
        k++;
    }
    listsame2->next=NULL;
    listsmaller2->next=listsame;
    //printList(listsame);
    //printList(listsmaller);


count=0;
k=0;

temp=*head;
ListNode *listbigger1,*listbigger2;
listbigger=malloc(sizeof(ListNode));
listbigger1=listbigger;
listbigger2=listbigger;
while(temp!=NULL){
    if((temp->item)>pivot){
        listbigger1->item=temp->item;
        //printf("%d\n",listbigger1->item);
        listbigger1->next=malloc(sizeof(ListNode));
        listbigger1=listbigger1->next;
        count++;
    }
    temp=temp->next;
}
temp=*head;
    while(k<count-1){
        listbigger2=listbigger2->next;
        k++;
    }
    listbigger2->next=NULL;
    listsame2->next=listbigger;
    //printList(listbigger);
    //printList(listsmaller);
count=0;
k=0;
temp=*head;
}
//----------------------big------------------------//
else{
    ListNode *listbigger1,*listbigger2;
listbigger=malloc(sizeof(ListNode));
listbigger1=listbigger;
listbigger2=listbigger;
while(temp!=NULL){
    if((temp->item)>pivot){
        listbigger1->item=temp->item;
        //printf("%d\n",listbigger1->item);
        listbigger1->next=malloc(sizeof(ListNode));
        listbigger1=listbigger1->next;
        count++;
    }
    temp=temp->next;
}
temp=*head;
    while(k<count-1){
        listbigger2=listbigger2->next;
        k++;
    }
    listbigger2->next=NULL;
    listsmaller2->next=listbigger;
    //printList(listsmaller);
    //printList(listbigger);
count=0;
k=0;
temp=*head;
}
*head=listsmaller;

}