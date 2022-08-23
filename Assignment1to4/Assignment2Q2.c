#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000

enum ExpType {OPT,OPERAND};

typedef struct _queueNode
{
    int item;
    enum ExpType type;
    struct _queueNode *next;
}QueueNode;

typedef struct _queue{
    int size;
    QueueNode *head;
    QueueNode *tail;
}Queue;

void enqueue (Queue *qptr, int item, enum ExpType type);
int dequeue(Queue *qPtr);
QueueNode* getFront(Queue q);
int isEmptyQueue(Queue q);

void expressionQ(char *infix, Queue* qPtr);
void printExpQ(Queue* qPtr);

int main()
{
    char infix[SIZE];
    scanf("%[^\n]%*c",infix);

    Queue inExpQ;
    inExpQ.head = NULL;
    inExpQ.tail = NULL;
    inExpQ.size = 0;

    expressionQ(infix,&inExpQ);
    printf("Output:\n");
    printExpQ(&inExpQ);

    return 0;
}

void enqueue (Queue *qPtr, int item, enum ExpType type)
{
    QueueNode *newNode;
    newNode = (QueueNode*) malloc(sizeof(QueueNode));
    newNode->item = item;
    newNode->type = type;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head = newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail =newNode;
    qPtr->size++;

}
int dequeue(Queue *qPtr)
{
    if(qPtr == NULL || qPtr->head ==NULL)
        return 0;
    else{
        QueueNode *temp = qPtr->head;
        qPtr->head = qPtr->head->next;

        if(qPtr->head == NULL)
            qPtr->tail = NULL;

        free(temp);
        qPtr->size--;
        return 1;
    }
}

QueueNode* getFront(Queue q)
{
    return q.head;
}

int isEmptyQueue(Queue q){
   if(q.size==0) return 1;
    else return 0;
}

void printExpQ(Queue *qPtr){
    if(qPtr==NULL) return;

    QueueNode* temp = NULL;
    temp = getFront(*qPtr);

    while(temp!=NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
        else
            printf(" %c ",(char)(temp->item));
        dequeue(qPtr);
        temp = getFront(*qPtr);
    }
    printf("\n");

}



void expressionQ(char *infix, Queue* qPtr)
{
// Write your code here
 char digits[SIZE],*digitptr;
 memset(digits,0,sizeof(digits));
  Queue *ptrList;
  ptrList=qPtr;
  
  char *infixptr;
  infixptr=infix;
  digitptr=digits;
  
  
  while(*infixptr!='\0'){
      if(*infixptr>=48 && *infixptr<=57){ 
        
            *digitptr=*infixptr;
            infixptr++;
            digitptr++;
            *digitptr='\0';
            
        
      }
      else if (*infixptr=='+'||*infixptr=='-'||*infixptr=='*'||*infixptr=='/'||*infixptr=='('||*infixptr==')'||*infixptr=='%'){ 
        
        if(digits[0]!='\0'){
        //printf("%s\n",numbers);
        digitptr=digits;
        int loop=strlen(digitptr);
        //printf("%d\n",loop);
        int store=0,temp=1,i;
        while(*digitptr!='\0'){
            for( i =1;i<loop;i++){
                temp=temp*10;
                //printf("%d\n",temp);
            }
            temp=(*digitptr-48)*temp;
            //printf("%d\n",temp);
            store=store+temp;
            temp=1;
            loop--;
            digitptr++;
        }
        //store= atoi(digits);
        enqueue(ptrList,store,OPERAND);
        digits[0]='\0';
        digitptr=digits;
        }
        
        char tempo;
        tempo= *infixptr;
        //printf("%d\n",store);
        enqueue(ptrList,tempo,OPT);
        infixptr++;

        
      }
}
if(digits[0]!='\0'){
        //printf("%s\n",numbers);
        digitptr=digits;
        int loop=strlen(digitptr);
        //printf("%d\n",loop);
        int store=0,temp=1,i;
        while(*digitptr!='\0'){
            for( i =1;i<loop;i++){
                temp=temp*10;
                //printf("%d\n",temp);
            }
            temp=(*digitptr-48)*temp;
            //printf("%d\n",temp);
            store=store+temp;
            temp=1;
            loop--;
            digitptr++;
        }
        //store= atoi(digits);
        enqueue(ptrList,store,OPERAND);
        digits[0]='\0';
        digitptr=digits;
        }

}