#include<stdio.h>
#include<conio.h>

void main()
{
    float exam;
    float labExam;
    float assignment;
    int total;
    char grade;

   	 printf("Enter Exam's mark: ");
   	 scanf("%f", &exam);

   	 printf("Enter Lab Exam's mark: ");
   	 scanf("%f", &labExam);

   	 printf("Enter Assignment mark: ");
   	 scanf("%f", &assignment);

   	 total = ((exam*60)/100) +((labExam*10)/100) + ((assignment*30)/100);

   	 if (total > 70){
   		 grade = 'A';
   	 } else if (total >= 60 && total <=69) {
   		 grade = 'B';
   	 } else if (total >= 50 && total <=59) {
   		 grade = 'C';
   	 } else if (total >= 40 && total <=49) {
   		 grade = 'D';
   	 } else if (total < 40) {
   		 grade = 'E';
   	 }

   	 printf("Total is: %d%%",total);
   	 printf("\nGrade: %c", grade);

    getch();
}
