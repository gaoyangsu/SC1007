#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

void reverseKNodes(ListNode** head, int K);

int main()
{
    ListNode *head = NULL, *temp;
	int i = 0;
	int K = 0;

	scanf("%d",&K);

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


	reverseKNodes(&head, K);
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

void reverseKNodes(ListNode** head, int K){
//Write your code here
	ListNode * newNode,*newNodecpy,*newNodecpy2, *original;
    int i,j,index,counter=1;
    newNode = malloc(sizeof(ListNode));
    newNodecpy = newNode;
    newNodecpy2 = newNode;
    if(K==0 || K<0) return;
    int initial=1;
    original=*head;
        while(original->next!=NULL){
            original= original->next;
            initial++;
        }
    original=*head;
    while(original!=NULL){
        i=1;
        original=*head;
        while(original->next!=NULL){
            original= original->next;
            i++;
        }
        original=*head;
        if(i>=K){
            for (j=K;j>0;j--){
                index=j;
                while(index>1){
                    original=original->next;
                    index--;
                }
                
                newNodecpy->item=original->item;
                //printf("%d\n",newNodecpy->item);
                newNodecpy->next = malloc(sizeof(ListNode));
                newNodecpy=newNodecpy->next;
                original=*head;
            }
            original=*head;
            index=K;
            while(index>0){
                original=original->next;
                index--;
                }
            *head=original;
            //printf("%d\n",(*head)->item); 
        }
        else{ 
            for(j=i;j>0;j--){
                newNodecpy->item=original->item;
                //printf("%d\n",newNodecpy->item);
                newNodecpy->next = malloc(sizeof(ListNode));
                newNodecpy=newNodecpy->next;
                original=original->next;
            }  
            break;
        }
        
    }

    while(counter<=initial-1){
            newNodecpy2=newNodecpy2->next;
            counter++;
        }
            newNodecpy2->next=NULL;
    
    *head=newNode;
}