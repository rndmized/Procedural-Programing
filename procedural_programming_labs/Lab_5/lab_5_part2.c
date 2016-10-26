#include<stdio.h>
#include<conio.h>


void main(){

   float avg=0;
   int integers[20];
   int i;

   printf("Enter 20 integers\n");
   for (i = 0; i<20;i++){   	
  	 printf("Enter integer number %d: ", i+1);
  	 scanf("%d", &integers[i]);
  	 avg+=integers[i];
   }    
   
   avg /= 20;
   printf("The average is: %f\n" , avg);
   for (i=0;i<20;i++){
  	 if (integers[i] < avg){

  		 printf("%d ", integers[i]);
  	 }
   }
   
   getch();

}
