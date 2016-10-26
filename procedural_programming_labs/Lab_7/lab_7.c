#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
 
void openFile(char mode);
void closeFile();

typedef struct {
   	 char name[15];
   	 int id;
   	 int hoursPerWeek;
   	 float hourlyRate;
    } employee_t;

FILE *efPr;
int numOfEmployees;
employee_t employee[1];
int i;

void main(){

    openFile('r');

    if (efPr==NULL){
   	 printf("There are no employee records.\n");
    }

    printf("Enter number of employees to add: ");
    scanf("%d", &numOfEmployees);
   	 
    for (i = 0; i < numOfEmployees;i++)
    {
   	 printf("Employee name: ");
   	 scanf("%s", employee[i].name);
   	 printf("Employee ID: ");
   	 scanf("%d", &employee[i].id);
   	 printf("Enter hours per week: ");
   	 scanf("%d",&employee[i].hoursPerWeek);
   	 printf("Enters hourly rate: ");
   	 scanf("%f", &employee[i].hourlyRate);
    }

    openFile('a');
    for (i=0;i<numOfEmployees;i++){
   	 fprintf(efPr, "Employe name: %s\n",employee[i].name);
   	 fprintf(efPr, "Employee ID: %d\n", employee[i].id);
   	 fprintf(efPr, "Hours per Week: %d\n", employee[i].hoursPerWeek);
   	 fprintf(efPr, "Hourly rate: %f\n",employee[i].hourlyRate);
   	 fputs("------------------------------------------\n",efPr);
    }
    closeFile();
    puts("Records added to Employee.txt ");

getch();
}

void openFile(char mode){
    efPr = fopen("Employee.txt", &mode);
}

void closeFile(){
    fclose(efPr);
}
