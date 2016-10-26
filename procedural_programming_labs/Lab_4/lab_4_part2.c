#include<stdio.h>
#include<conio.h>

void main(){

   int i=0;
   long num=0;
   long totalResult=0;
   do
   {
   printf("Please, enter the number to get the factorial: ");
   scanf("%d", &num);
   }while(num<0 || num>19);


   totalResult=num;
   if (num !=0){
  	 for (i = num-1; i!=0; i--){
  		 totalResult *=i;
  	 }
   } else{totalResult= 1;}
   printf("Factorial of %d: %d", num, totalResult);
   getch();

}
