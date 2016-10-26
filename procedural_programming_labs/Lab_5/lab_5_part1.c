#include<string.h>
#include<conio.h>
#include<stdio.h>


void main(){

   char string1[40];
   char string2[40];
   int userInt;
   int length;
   int comp;

   printf("Please enter two text strings and an integer number.\n");
   printf("Enter first string:");
   gets(string1);
   printf("Enter second string:");
   gets(string2);
   printf("Enter an integer:");
   scanf("%d", &userInt);
   
   printf("String 1 lenght: %d\n", strlen(string1));
   printf("String 2 lenght: %d\n", strlen(string2));

   printf("\n%s",string1);
   printf("\n%s",string2);

   comp = strcmp(string1,string2);

   printf("\nThe bigger string is: ");
   if (comp < 0){
  	 printf("\n%s",string2);
   }
   else if (comp > 0){
  	 printf("\n%s",string1);
   } else {
  	 printf("Both strings have the same lenght");
   }

   comp = strncmp(string1,string2,userInt);
   printf("\nThe bigger string for the first %d characters is: ", userInt);
   if (comp < 0){
  	 printf("\n%s",string2);
   }
   else if (comp > 0){
  	 printf("\n%s",string1);
   } else {
  	 printf("Both strings have the same lenght");
   }

   printf("\nConcatenating strings: ");
   strcat(string1,string2);
   printf("\n%s",string1);
   printf("\n%s",string2);

   printf("\nConcatenating strings the 3 first chars of string 2: ");
   strncat(string1, string2, 3);
   printf("\n%s",string1);
   printf("\n%s",string2);

   printf("\nCopying String 2 into string 1: ");
   strcpy(string1,string2);
   string1[strlen(string2)] = '\0';
   printf("\n%s",string1);
   printf("\n%s",string2);

   printf("\nCopying the first 3 chars of String 2 into string 1: ");
   strcpy(string1,string2);
   string1[3] = '\0';
   printf("\n%s",string1);
   printf("\n%s",string2);

   getch();

}
