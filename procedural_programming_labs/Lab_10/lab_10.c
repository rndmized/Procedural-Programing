#include<stdlib.h>
#include<conio.h>
#include<stdio.h>

//Creating struct to store employee values
typedef struct {
    char name[30];
    int id;
    float hours;
    float rate;
} employee_t;

void main() {

    int arraySize = 0; //Stores the size of the one dimension array
    employee_t * employeeArray; //points the space in memory for the one dimension array
    int i=0;//loop variable
    FILE * fptr;//file pointer
    printf("Please, enter number of employees: "); //Asks the user input
    scanf("%d", &arraySize);//stores input in variable

    employeeArray = (employee_t*)malloc(sizeof(employee_t)*arraySize);//allocates in memory space for the  array

    
    for (i = 0; i<arraySize; i++)//loop a total number of times as the size of the array
    {
   	 printf("Employee name: ");
   	 scanf("%s", (employeeArray+i)->name);//store value in the struct variable allocated in that memory space
   	 printf("Employee ID: ");
   	 scanf("%d", &(employeeArray+i)->id);//store value in the struct variable allocated in that memory space
   	 printf("Enter hours per week: ");
   	 scanf("%f", &(employeeArray + i)->hours);//store value in the struct variable allocated in that memory space
   	 printf("Enters hourly rate: ");
   	 scanf("%f", &(employeeArray + i)->rate);//store value in the struct variable allocated in that memory space
    }//end for
    
    fptr = fopen("Employee.txt", "w");//set the pointer to file and the mode to write

    if (fptr == NULL) {//checks if file exist
   	 printf("There are no employee records.\n");
    }//end if

    //print text to file
    fprintf(fptr, "Employe List\n");
    fprintf(fptr, "Name \t ID \t Hours per Week \t Hourly Rate\n");
    
    //print text to screen
    printf("Employe List\n");
    printf("Name \t ID \t Hours per Week \t Hourly Rate\n");

    for (i = 0; i<arraySize; i++)//loop a total number of times as the size of the array
    {
   	 fprintf(fptr, "%s \t %d \t %2.f  \t \t \t %2.f\n", (employeeArray + i)->name, (employeeArray + i)->id, (employeeArray + i)->hours, (employeeArray + i)->rate);//prints values into the file
   	 printf("%s \t %d \t %.2f  \t \t \t %.2f\n", (employeeArray + i)->name, (employeeArray + i)->id, (employeeArray + i)->hours, (employeeArray + i)->rate);//prints values in the screen
    }//end for

    fclose(fptr);//closes file

    getch();
}


