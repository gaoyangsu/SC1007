//
//  main.c
//  Assignment4Q2
//
//  Created by Gaoyang Su on 25/2/22.
#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

typedef struct _queueNode{
    BTNode *data;
    struct _queueNode *next;
}QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

typedef struct _stackNode{
    BTNode *data;
    struct _stackNode *next;
}StackNode;

typedef struct _stack
{
    int size;
    StackNode *top;
}Stack;

//Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, BTNode * data);
int dequeue(Queue *qPtr);
BTNode* getFront(Queue q);
int isEmptyQueue(Queue q);

BTNode* createNode(int item);
void printBTNode(BTNode *root, int space, int left);
void deleteTree(BTNode **root);

//Prototypes of Interface functions for Stack structure
void push(Stack *sPtr, BTNode *data);
int pop(Stack *sPtr);
BTNode* peek(Stack s);
int isEmptyStack(Stack s);

void BSTCorrection(BTNode* root);

int main()
{
    BTNode* root = NULL;
    BTNode* temp = NULL;
    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    int item;
    int flag=1;
    printf("Enter a list of numbers for a Binary Tree, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
    {
        if(root==NULL)
        {
            if(item!=-1){
                root =createNode(item);
                enqueue(&q,root);
            }
        }
        else{
            while(!isEmptyQueue(q)){
                temp = getFront(q);
                if(flag){
                    if(item != -1){
                        temp->left = createNode(item);
                        enqueue(&q,temp->left);
                    }
                    flag = 0;
                    break;
                }
                else if(temp->right==NULL){
                    if(item!=-1){
                        temp->right = createNode(item);
                        enqueue(&q,temp->right);
                    }
                    dequeue(&q);
                    flag=1;
                    break;
                }
                else  dequeue(&q);
            }
        }
    }
    scanf("%*s");

    printf("The input binary search tree:\n");
    printBTNode(root,0,0);
    printf("\n");
    printf("The corrected binary search tree:\n");
    BSTCorrection(root);

    printBTNode(root,0,0);

    deleteTree(&root);

    return 0;
}
BTNode* createNode(int item)
{
    BTNode* node = (BTNode*) malloc(sizeof(BTNode));
    node->item = item;
    node->left = node->right = NULL;
    return node;
}

void printBTNode(BTNode *root,int space,int left){
      if (root != NULL)
      {

          int i;
          for (i = 0; i < space-1; i++)
                 printf("|\t");


          if(i<space){
            if(left==1)
              printf("|---");
            else
              printf("|___");
          }

          printf("%d\n", root->item);

          space++;
          printBTNode(root->left, space,1);
          printBTNode(root->right, space,0);
      }
}

void deleteTree(BTNode **root){
    if (*root != NULL)
    {
        deleteTree(&((*root)->left));
        deleteTree(&((*root)->right));
        free(*root);
        *root = NULL;
    }
}
void enqueue(Queue *qPtr, BTNode *data){
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr){
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return 1;
    }
}

BTNode* getFront(Queue q){
    return q.head->data;
}

int isEmptyQueue(Queue q){
    if(q.size==0) return 1;
    else return 0;
}

void push(Stack *sPtr, BTNode *data){
    StackNode *newNode;
    newNode= (StackNode *)malloc(sizeof(StackNode));
    newNode->data = data;
    newNode->next = sPtr->top;
    sPtr->top = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr==NULL || sPtr->top==NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->top;
       sPtr->top = sPtr->top->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

BTNode* peek(Stack s){
    return s.top->data;
}

int isEmptyStack(Stack s){
     if(s.size==0) return 1;
     else return 0;
}

void BSTCorrection(BTNode* root)
{   // initialisation of variables to be used
    Queue main;
    main.size=0;
    main.head=NULL;
    main.tail=NULL;
    Queue toCompare;
    toCompare.size=0;
    toCompare.head=NULL;
    toCompare.tail=NULL;
    BTNode* temp;
    Stack inorder;
    inorder.size=0;
    inorder.top=NULL;
    //
    
    temp=root;
    
    //inorder iterative traversal and insert into Queue Main
    while(!((temp==NULL)&&(isEmptyStack(inorder)))){
        if(temp!=NULL){
            push(&inorder, temp);
            temp=temp->left;
        }
        else{
            temp=peek(inorder);
            pop(&inorder);
            enqueue(&main, temp);
            temp=temp->right;
        }
        
        
    }
    
    /* For debugging
     while(!isEmptyQueue(main)){
        printf("%d ", (getFront(main))->item);
        dequeue(&main);
    }
    printf("\n");
     */
    
    //perform bubble sort
    BTNode *A, *B,*reinsert,*C;
    int i,j;
    int size;
    size=main.size;
    for(i=0;i<size-1;i++){
        A=getFront(main);
        dequeue(&main);
        enqueue(&toCompare, A);
        for(j=0;j<size-i-1;j++){
            B=getFront(main);
            dequeue(&main);
            enqueue(&toCompare, B);
            reinsert=getFront(toCompare);
            dequeue(&toCompare);
            if((reinsert->item)>((getFront(toCompare))->item)){
                int temp;
                temp=reinsert->item;
                reinsert->item=(getFront(toCompare))->item;
                (getFront(toCompare))->item=temp;
            }
            enqueue(&main, reinsert);
        }
        C=getFront(toCompare);
        dequeue(&toCompare);
        
        
    }
    
}
