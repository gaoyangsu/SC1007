#include <stdio.h>
#include <string.h>
#define MAX 5
typedef struct {
 int nameCardID;
 char personName[20];
 char companyName[20];
} NameCard; 
int size =0;
void listNameCards(NameCard *person, int size);
void addNameCard(NameCard *person);

int main(){
    NameCard person[MAX];
    char personName[20], *p;
    int choice, result;
    printf("NTU NAME CARD HOLDER MANAGEMENT PROGRAM:  \n");
    printf("1: listNameCards() \n");      
    printf("2: addNameCard() \n");
    printf("3: removeNameCard()  \n");
    printf("4: getNameCard() \n");
    printf("5: quit \n");       
    do {
      printf("Enter your choice: \n");
      scanf("%d", &choice);
      switch (choice) {
         case 1:            
            listNameCards(person, size);
            break;           
         case 2:            
            printf("addNameCard(): \n");
            addNameCard(person);

         case 3:            
             
         case 4:
            ;
      }  
   } while (choice < 5);
   return 0;

}

void listNameCards(NameCard *person, int size){
    int i;
    
    printf("listNameCards(): \n");
    if (size==0)  
      printf("The name card holder is empty\n");
    else{
      for (i=0; i<size; i++)  
         printf("%d\n",person[i].nameCardID);  
         printf("%s\n",person[i].personName);  
         printf("%s\n",person[i].companyName);  
    }
}

void addNameCard(NameCard *person)
{  int i, namecardid;
   char *p,*personalname,*companyname;
   printf("Enter nameCardID: \n");
   scanf("%d",&namecardid);
   printf("Enter personName: \n");
   scanf("\n");
   fgets(personalname, 20, stdin);  
   if (p=strchr(personalname,'\n')) *p = '\0';
   printf("Enter companyName: \n");
   scanf("\n");
   fgets(companyname, 20, stdin);  
   if (p=strchr(companyname,'\n')) *p = '\0';
   if (size<MAX){
      for(i=0;i<size;i++,person++){
         if(person[i].nameCardID==namecardid){
            printf("The nameCardID has already existed\n");
            return;
            break;
         }
      person[size].nameCardID=namecardid;
      strcpy(person[size].personName,personalname);
      strcpy(person[size].companyName,companyname);
      size++;
      }
   }
   else {
      printf("The name card holder is full\n");
   }
}
