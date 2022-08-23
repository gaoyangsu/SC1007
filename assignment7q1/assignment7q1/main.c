#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


int *Array;

int top_down_dp(int n)
{
    if (n==0) {
       Array[0]=0;
       return 0;
   }
   if (n==1){
       Array[1]=1;
       return 1;
   }
   if (n==2){
       Array[2]=2;
       return 2;
   }
   
   if(Array[n-1]==-5) Array[n-1]=top_down_dp(n-1);
   if(Array[n-2]==-5) Array[n-2]=top_down_dp(n-2);
   if(Array[n-3]==-5) Array[n-3]=top_down_dp(n-3);
   
   int result;
   result= Array[n-1]+2*Array[n-2]-3*Array[n-3];
   
   return result;
   
}


 
int main ()
{
    int n;
    
    printf("Enter the value of n:\n");
    scanf("%d",&n);
    
    int i;
    Array=malloc(sizeof(int)*(n+1));
    for (i=0;i<n+1;i++) Array[i]=-5;
    
    printf("The value of F(%d) is: %d \n", n, top_down_dp(n));
    
        
}
