#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    float item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

ListNode *reverseSegment(ListNode* head, int start, int end);

int main()
{
    ListNode *head = NULL, *temp;
	float f = 0.0;
	int S, E;

	scanf("%d %d",&S, &E);

	while (scanf("%f", &f)){
		if (head == NULL){
			head = (ListNode*) malloc(sizeof(ListNode));
			temp = head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = f;
	}
	temp->next = NULL;

	head = reverseSegment(head,S,E);
	printList(head);
	deleteList(&head);
	return 0;

}

void printList(ListNode *head){
    while(head !=NULL){
        printf("%.2f ",head->item);
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

ListNode *reverseSegment(ListNode* head, int start, int end)
{
// Write your code here
    ListNode *temp, *tempprevious,*tempnext;
    int range,counter,i,indexrear,indexfront;
    indexrear=end;
    indexfront=start;
    temp=head;
    
    counter=0;
    while(temp->next!=NULL){
        temp=temp->next;
        counter++;
    }
    temp=head;
    
    //printf("%d\n",counter);
    if(start==end) return head;
    else if(start<0 || end<0|| (end-start)>counter) return head;
    else if(start==0){
        tempnext=NULL;
        while(indexrear>0){
            temp=temp->next;
            indexrear--;
        }
        //printf("%2f\n",temp->item);
        tempprevious=temp->next;
        temp=head;
        range=end-start;
        for(i=0;i<=range;i++){
            tempnext=temp->next;
            temp->next=tempprevious;
            tempprevious=temp;
            temp=tempnext;    
        }
        head=tempprevious;
        return head;
    }
    else{
        ListNode *cur=head;
        tempnext=NULL;
        while(indexrear>0){
            temp=temp->next;
            indexrear--;
        }
        printf("%2f\n",temp->item);
        tempprevious=temp->next;
        temp=head;

        while(indexfront>0){
            temp=temp->next;
            indexfront--;
        }
        //printf("%2f\n",temp->item);
        cur=temp;
        temp=head;
        
        range=end-start;
        for(i=0;i<=range;i++){
            tempnext=cur->next;
            cur->next=tempprevious;
            tempprevious=cur;
            cur=tempnext;    
        }
        cur=tempprevious;
        indexfront= start;
        temp=head;
        while((indexfront-1)>0){
            temp=temp->next;
            indexfront--;
        }
        temp->next=cur;


        return head;
    }


}