#include<stdio.h>
#include<conio.h>

void instructions();
float average(int a, int b, int c);
void display(float number);

int count=1;

void main() {
   int i;
   int numbers[3];
   float avg;
   for (i=0; i<3;i++){
  	 instructions();
  	 scanf("%d", &numbers[i]);
   }
   avg = average(numbers[0],numbers[1],numbers[2]);
   display(avg);
   getch();
}

void instructions(){
   printf("Please enter integer number %d: ", count);
   count++;
}

float average(int a, int b, int c) {
   return ((float)(a+b+c)/3);
}

void display(float number){
   printf("The average of inputted numbers is: %f", number);
}
