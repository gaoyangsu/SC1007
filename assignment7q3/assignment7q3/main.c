#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


int bottom_up_dp(int n, int *s, int *v, int C)
{
    //write your code here
    int Array[n+1][C+1];
    int i,c;
    
    for (i=0;i<n+1;i++){
        for(c=0;c<C+1;c++){
            Array[i][c]=0;
        }
    }
    
    for (i=1;i<n+1;i++){
        for(c=1;c<C+1;c++){
            if(s[i]<=c)
            Array[i][c]=(Array[i-1][c]>(Array[i-1][c-s[i]]+v[i]))?Array[i-1][c]:Array[i-1][c-s[i]]+v[i];// k=c-s[i] being, Array[i-1][k] was the value in memonic, +v[i] means the old memonic add with current value, see if bigger than previous value of Array[i-1][c]
            else Array[i][c]=Array[i-1][c];
        }
    }
    
    return Array[n][C];
    
}

 
int main ()
{
    int n,C;
    int function;
    int *s;
    int *v;
    int i,j;
    printf("Enter the number of items n:\n");
    scanf("%d",&n);
    printf("Enter the capacity C:\n");
    scanf("%d",&C);
    s = (int *) malloc(sizeof(int) * (n+1));
    v = (int *) malloc(sizeof(int) * (n+1));
    
    printf("Enter the sizes of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&s[i]);
        
    printf("Enter the values of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&v[i]);
    
    printf("The maximum value is: %d \n", bottom_up_dp(n,s,v,C));
        
}
