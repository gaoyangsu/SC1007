#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200 //The number digit limitation

typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

typedef struct _node{
     BTNode* item;
     struct _node *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void deleteTree(BTNode **root);

void createExpTree(BTNode** root,char* prefix);
void printTree(BTNode *node);
void printTreePostfix(BTNode *node);
double computeTree(BTNode *node);

void push(Stack *sPtr,  BTNode* item);
int pop(Stack *sPtr);
BTNode *peek(Stack s);
int isEmptyStack(Stack s);


int main()
{
    char prefix[SIZE];
    BTNode* root=NULL;

    //printf("Enter an prefix expression:\n");
    gets(prefix);

    createExpTree(&root, prefix);

    // printf("The Infix Expression:\n");
    printTree(root);
    printf("\n");
    //printf("The Postfix (Reverse Polish) Expression:\n");
    printTreePostfix(root);
    printf("\n");
    //printf("Answer ");
    printf("%.2f\n", computeTree(root));
    deleteTree(&root);
    return 0;
}

void push(Stack *sPtr, BTNode *item){
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

BTNode *peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

void deleteTree(BTNode **root){
    BTNode* temp;
    if(*root !=NULL)
    {
        temp = (*root)->right;
        deleteTree(&((*root)->left));
        free(*root);
        *root = NULL;
        deleteTree(&temp);
    }
}



void createExpTree(BTNode** root,char* prefix)
{  if((*prefix>=48)&&(*prefix<=57)) return;
   char *temp;
   temp=prefix;
   if(*temp==' '){
       while(*temp!=' '){
           temp++;
       }
       if ((*temp>=48)&&(*temp<=57)) return;
   }
   Stack rearrange, combine;
   BTNode *tempNode;
   char numbers[SIZE],*numberptr;
   numberptr=numbers;
   numbers[0]='\0';
   rearrange.head=NULL;
   rearrange.size=0;
   combine.head=NULL;
   combine.size=0;
    while(*prefix!='\0'){
        if((*prefix>=48)&&(*prefix<=57)){ 
                *numberptr=*prefix;
                prefix++;
                numberptr++;
                *numberptr='\0';
      }
        else if (*prefix==' '){ 
            if(numbers[0]!='\0'){
            //printf("%s\n",numbers);
            int store1= atoi(numbers);
            tempNode= malloc(sizeof(BTNode));
            tempNode->item=store1;
            tempNode->left=NULL;
            tempNode->right=NULL;
            push(&rearrange,tempNode);
            numbers[0]='\0';
            numberptr=numbers;
            }   
            prefix++;
        }
        else if (*prefix=='+'||*prefix=='-'||*prefix=='*'||*prefix=='/'){
            if(numbers[0]!='\0'){
            //printf("%s\n",numbers);
            int store4= atoi(numbers);
            tempNode= malloc(sizeof(BTNode));
            tempNode->item=store4;
            tempNode->left=NULL;
            tempNode->right=NULL;
            push(&rearrange,tempNode);
            numbers[0]='\0';
            numberptr=numbers;
            }   
            int store2= (*prefix-100);
            tempNode= malloc(sizeof(BTNode));
            tempNode->item=store2;
            tempNode->left=NULL;
            tempNode->right=NULL;
            int boolean =1;
            push(&rearrange,tempNode);
            prefix++;
        
        }
        else prefix++;
}
if(numbers[0]!='\0'){
int store3= atoi(numbers);
tempNode= malloc(sizeof(BTNode));
tempNode->item=store3;
tempNode->left=NULL;
tempNode->right=NULL;
push(&rearrange,tempNode);
numbers[0]='\0';
numberptr=numbers;
}


//push the Stack into another Stack

while(!isEmptyStack(rearrange)){
    if((peek(rearrange)->item)!=('+'-100)&&(peek(rearrange)->item)!=('-'-100)&&(peek(rearrange)->item)!=('*'-100)&&(peek(rearrange)->item)!=('/'-100)){
        push(&combine,peek(rearrange));
        //printf("%d ", peek(combine)->item);
        pop(&rearrange);
    }
    else{
        BTNode *A,*B,*C;
        A=peek(combine);
        pop(&combine);
        B=peek(combine);
        pop(&combine);
        C=peek(rearrange);
        pop(&rearrange);
        C->left=A;
        C->right=B;
        push(&combine,C);
        //printf("%d ", peek(combine)->item);
    }
}
if (!isEmptyStack(combine)){
    *root=peek(combine);
}
else return;
}


void printTree(BTNode *node){
    if(node==NULL) return;
    printTree(node->left);
    if(node->left==NULL && node->right==NULL) printf("%d ", node->item);
    else printf("%c ",node->item+100);
    printTree(node->right);
    
}

void printTreePostfix(BTNode *node){
   //Write your code here
    if(node==NULL) return;
    printTreePostfix(node->left);
    printTreePostfix(node->right);
    if(node->left==NULL && node->right==NULL) printf("%d ", node->item);
    else printf("%c ",node->item+100);
    
}

double computeTree(BTNode *node){
//Write your code here
    BTNode *temp;
    temp=node;
    double nodeL,nodeR;
    if (temp==NULL) return 0;
    if (temp->left==NULL && temp->right==NULL) return temp->item;
    
    nodeL= computeTree(temp->left);
    nodeR= computeTree(temp->right);

    if (temp->item=='+'-100) return nodeL+nodeR;
    else if (temp->item=='-'-100) return nodeL-nodeR;
    else if (temp->item=='*'-100) return nodeL*nodeR;
    else return nodeL/nodeR;
}

