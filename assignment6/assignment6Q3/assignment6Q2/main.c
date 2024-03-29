#include <stdio.h>
#include <stdlib.h>

int *r;

typedef struct _listnode
{
    int vertex;
    struct _listnode *next;
} ListNode;

typedef struct _graph{
    int V;
    int E;
    int *visited;
    int **matrix;
}Graph;

typedef ListNode QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

int SD (Graph G, int v, int w);

void printGraphMatrix(Graph );

// You should not change the prototypes of these functions
void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);

int main()
{
    Graph g;
    int i,j;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);
    
    g.E = 0;
    g.matrix = (int **)malloc(g.V*sizeof(int *));
    r= malloc(g.V*sizeof(int));

    for(i=0;i<g.V;i++){
        g.matrix[i] = (int *)malloc(g.V*sizeof(int));
    }
    for(i=0;i<g.V;i++) r[i]=-1;

    for(i=0;i<g.V;i++)
       for(j=0;j<g.V;j++)
           g.matrix[i][j] = 0;

    g.visited = (int *) malloc(sizeof(int)*g.V);
    for(i=0;i<g.V;i++) g.visited[i] = 0;

    int V1, V2;
    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.matrix[V1-1][V2-1] = 1;
            g.matrix[V2-1][V1-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter two vertices which are adjacent to each other: (press a to stop)\n");
    }
    scanf("%*c");
    // printGraphMatrix(g);
    
    printf("Enter two vertices for finding their shortest distance: (press a to stop)\n");
    scanf("%d %d", &i, &j);

    int d = SD(g,i,j);
    if(d==-1)
        printf("%d and %d are unconnected.\n",i,j);
    else
        printf("The shortest distance is %d\n",d);
    return 0;
}
void ShortestPath(Graph g, int root , int end){
    if (end==root) {
        return;
    }
    int next;
    next= r[end];
    printf("%d-->", next+1);
    ShortestPath(g,root,next);
}

int SD(Graph g, int v, int z){
    // Write your code here
    
    Queue A;
    A.size=0;
    A.tail=NULL;
    A.head=NULL;
    int start=v;
    enqueue(&A, start);
    g.visited[start-1]=1;
    while (!isEmptyQueue(A)){
        int current;
        int count;
        current=getFront(A);
        int currentlength=g.visited[current-1]-1;
        if (current==z){
            printf("The path is:%d-->", z);
            ShortestPath(g,v-1,z-1);
            printf("\n");
            return currentlength;
        } 
        dequeue(&A);
        for(count=0;count<g.V;count++){
            if(g.matrix[current-1][count]==1 && !(g.visited[count])){
                r[count]=current-1;
                g.visited[count]=g.visited[current-1]+1;
                enqueue(&A, count+1);
                
            }
        }
        
    }
    return -1;
}

void printGraphMatrix(Graph g)
{
    int i,j;

    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.matrix[i][j]);
        printf("\n");
    }

}


void enqueue(Queue *qPtr, int item) {
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    if(newNode==NULL) exit(0);

    newNode->vertex = item;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr) {
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       int headValue = qPtr->head->vertex;
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return headValue;
    }
}

int getFront(Queue q){
    return q.head->vertex;
}

int isEmptyQueue(Queue q) {
    if(q.size==0) return 1;
    else return 0;
}

void removeAllItemsFromQueue(Queue *qPtr)
{
    while(dequeue(qPtr));
}
