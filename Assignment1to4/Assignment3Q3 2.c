#include <stdio.h>
#include <stdlib.h>

#define MAX_N 120

typedef struct _btnode{
    char id;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

void buildTree(BTNode** node, char* preO, char* postO);
void inOrder(BTNode *cur);
void preOrder(BTNode *cur);
void postOrder(BTNode *cur);

int main()
{
    char preO[MAX_N];
    char postO[MAX_N];
    scanf("%s",preO);
    scanf("%s",postO);

    BTNode* root=NULL;
    buildTree(&root,preO,postO);
    if(root==NULL) printf("error\n");
    preOrder(root);
    printf("\n");
    postOrder(root);
    printf("\n");

    inOrder(root);
    printf("\n");

    return 0;
}
void inOrder(BTNode *cur){
    if (cur == NULL)
        return;

    inOrder(cur->left);
    printf("%c",cur->id);
    inOrder(cur->right);
}
void preOrder(BTNode *cur){
    if (cur == NULL)
        return;

    printf("%c",cur->id);
    preOrder(cur->left);
    preOrder(cur->right);
}
void postOrder(BTNode *cur){
    if (cur == NULL)
        return;

    postOrder(cur->left);
    postOrder(cur->right);
    printf("%c",cur->id);
}

void buildTree(BTNode** node, char* preO, char* postO)
{


// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
    // base case
    if(*preO=='\0') {
        return;
    }

    BTNode * New = (BTNode*) malloc(sizeof(BTNode));
    New->id=*preO;
    New->left=NULL;
    New->right=NULL;
    *node=New;

    char *temp;
    temp=preO;
    int i=0;
    while (*temp!='\0'){
        i++;
        temp++;
    }
    if(i==1) return;
    char *findlength; int length=0;
    findlength=preO;
    while(*findlength!='\0'){
        length++;
        findlength++;
    }
    preO++;
    // creating new strings for recursion
    char preOL[MAX_N], preOR[MAX_N], postOL[MAX_N], postOR[MAX_N];
    char *preOLp, *preORp, *postOLp,*postORp;
    preOLp=preOL; preORp=preOR; postOLp=postOL; postORp=postOR;
    preOL[0]='\0';preOR[0]='\0'; postOL[0]='\0';postOR[0]='\0';
    //
    char *temp1,*temp2;
    temp1=postO;
    int j=0;
    while(*temp1!=*preO){
        j++;
        temp1++;
    }
    temp1=postO;
    temp2=preO;
    int k;
    for(k=0;k<=j;k++){
        *preOLp=*temp2;
        *postOLp=*temp1;
        preOLp++; postOLp++;
        temp2++;
        temp1++;
    }
    *preOLp='\0';
    *postOLp='\0';
    

    int k2;
    for(k2=0;k2<=length-j-1;k2++){
        *preORp=*temp2;
        *postORp=*temp1;
        preORp++;postORp++;
        temp2++;
        temp1++;
    }
    *preORp='\0';
    *postORp='\0';
    
    //printf("preOL %s\n", preOL);
    //printf("preOR %s\n", preOR);
    //printf("postOL %s\n", postOL);
    //printf("postOR %s\n", postOR);
    
    buildTree(&((*node)->left),preOL,postOL);
    buildTree(&((*node)->right),preOR,postOR);
    return;


}