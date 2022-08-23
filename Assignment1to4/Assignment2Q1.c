#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000 //The size of the array

enum ExpType {OPT,OPERAND};


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

typedef struct _listnode
{
    int  item;
    enum ExpType type;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item,enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);


void in2PreLL(char* infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExp);

int main()
{
    char infix[SIZE];

    //printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c",infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

void printExpLL(LinkedList inExpLL)
{
    ListNode* temp = NULL;
    temp = inExpLL.head;
    while(temp!= NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
        else
            printf(" %c ",(char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if(newNode==NULL) exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head=newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if(LLPtr==NULL || LLPtr->size==0){
        return 0;
    }
    else{
       ListNode *temp = LLPtr->head;
       LLPtr->head = LLPtr->head->next;

       free(temp);
       LLPtr->size--;
       return 1;
    }
}

int isEmptyLinkedList (LinkedList ll) {
    if(ll.size==0) return 1;
    else return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
	while(deleteNode(LLPtr));
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


void in2PreLL(char* infix, LinkedList *inExpLL)
{
  //Write your code here
  char numbers[SIZE],*numberptr;
  LinkedList reverseinfix,*ptrList,reverseprefix;
  reverseinfix.head=NULL;
  reverseinfix.size=0;
  char *infixptr;
  infixptr=infix;
  numberptr=numbers;
  int store;
  while(*infixptr!='\0'){
      if((*infixptr!='+'&&*infixptr!='-'&&*infixptr!='*'&&*infixptr!='/'&&*infixptr!='('&&*infixptr!=')')){ // must &&!!! if not '+' would be accepted in other cases!
            *numberptr=*infixptr;
            infixptr++;
            numberptr++;
            *numberptr='\0';
      }
      else{ 
        
        if(numbers[0]!='\0'){
        //printf("%s\n",numbers);
        store= atoi(numbers);
        insertNode(&reverseinfix,store,OPERAND);
        numbers[0]='\0';
        numberptr=numbers;
        }
        
        store= *infixptr;
        //printf("%d\n",store);
        insertNode(&reverseinfix,store,OPT);
        infixptr++;

        
      }
}
if(numbers[0]!='\0'){
store= atoi(numbers);
insertNode(&reverseinfix,store,OPERAND);
numbers[0]='\0';
numberptr=numbers;
}

printExpLL(reverseinfix);

Stack operatorsSlot;
operatorsSlot.head=NULL;
operatorsSlot.size=0;
ptrList=inExpLL;
int temp2;
while(isEmptyLinkedList(reverseinfix)!=1){
    if((reverseinfix.head)->type==OPERAND){
            temp2=(reverseinfix.head)->item;
            insertNode(ptrList,temp2,OPERAND);
            //printExpLL(*ptrList);
        }
    else if((reverseinfix.head)->item=='('){
        while(peek(operatorsSlot)!=')'){
            insertNode(ptrList,peek(operatorsSlot),OPT);
            //printf("%c\n",*prefixptr);
            pop(&operatorsSlot);
        }
        pop(&operatorsSlot);
    }
    else if((reverseinfix.head)->item==')') {
        push(&operatorsSlot,(reverseinfix.head)->item);
        //printf("%c\n",peek(A));
    }
    else if ((reverseinfix.head)->item=='+'||(reverseinfix.head)->item=='-'||(reverseinfix.head)->item=='*'||(reverseinfix.head)->item=='/'){
        if (isEmptyStack(operatorsSlot)==1){
            push(&operatorsSlot,(reverseinfix.head)->item);
            //printf("%c\n",peek(tempstore));
        }

        else{
            int precedenceinfix=((reverseinfix.head)->item=='*'||(reverseinfix.head)->item=='/')?1:0;
            //printf("%d\n",precedenceinfix);
            int precedencestack=(peek(operatorsSlot)=='*'||peek(operatorsSlot)=='/')?1:0;
            //printf("%d\n",precedencestack);
            while((isEmptyStack(operatorsSlot)!=1)&&(peek(operatorsSlot)!=')')&&(precedencestack-precedenceinfix>0)){
            insertNode(ptrList,peek(operatorsSlot),OPT);
            //printf("%c\n",*prefixptr);
            pop(&operatorsSlot);
            if(isEmptyStack(operatorsSlot)!=1) precedencestack=(peek(operatorsSlot)=='*'||peek(operatorsSlot)=='/')?1:0;
        }
            push(&operatorsSlot,(reverseinfix.head)->item);
            //printf("%c\n",peek(A));
        }

    }
    deleteNode(&reverseinfix);
}
while(isEmptyStack(operatorsSlot)!=1){
        insertNode(ptrList,peek(operatorsSlot),OPT);
        //prefixptr++;
        pop(&operatorsSlot);
    }
ptrList=inExpLL;
//printExpLL(*ptrList);
  


}

