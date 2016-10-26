#include<stdio.h>
#include<conio.h>

void main(){

   int min=0;
   int max=0;
   int sum=0;
   int newNum=0;
   float avg=0;
   int count=0;

   printf("Please enter Integers. Enter -1 to terminate.\n");
   do{
  	 printf("Enter number: ");
  	 scanf("%d", &newNum);
  	 if (newNum == -1) {
  		 break;
  	 } else {
  		 if (newNum < min || count ==0 ){ min = newNum; }
  		 if (newNum > max || count ==0 ){ max = newNum; }
  		 sum += newNum;
  		 count++;
  	 }
   } while (newNum != -1);
  	
  	 if (count != 0) { avg = ((float)sum / (float)count); } else { avg=0; }

  	 printf("\nSum: %d\n", sum);
  	 printf("Average:  %.2f\n", avg);
  	 printf("Smallest Number: %d\n", min);
  	 printf("Largest number: %d\n", max);
  	 printf("Total of valid Integers: %d\n", count);

   getch();

}
