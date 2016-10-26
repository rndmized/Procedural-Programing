#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

typedef struct{

    char name[30];
    int id;
    int VAT_id;

}COMPANY_T; /*Struct COMPANY_T stores company values such as company name, company number and company VAT number*/

void main(){

    int numOfCompanies; /* Stores number of companies to input */
    COMPANY_T *company; /* Pointer to company_t */
    FILE *fptr; /* FILE pointer */
    int i; /* Loop variable */
    
    /* Ask user number of companies to input*/
    printf("Welcome to the Structures and Dynamic Memory Allocation Revision.\n");
    printf("NOTE. Please create COMPANIES.dat in the folder before attempting\nto save the    file.\n");
    printf("Please enter the number of companies to store:");
    /* Store number of companies into numOfCompanies variable*/
    scanf("%d", &numOfCompanies);

    /* Allocate memory depending on the number of companies and set company pointer value */
    company = (COMPANY_T *)malloc(sizeof(COMPANY_T)*numOfCompanies);

    /*For every company, ask user input */
    for (i = 0; i < numOfCompanies; i++){
   	 printf("Please, enter company name:\n");
   	 scanf("%s", (*(company+i)).name);
   	 printf("Please, enter company ID number:\n");
   	 scanf("%d", &(*(company+i)).id);
   	 printf("Please, enter company VAT number:\n");
   	 scanf("%d", &(*(company+i)).VAT_id);
   	 printf("\n");
    }/* end for */
    
    /* For every company, print values to screen*/
    printf("COMPANY NAME \t COMPANY ID \t COMPANY VAT\n");
    printf("---------------------------------------------------------------\n");
    for (i = 0; i< numOfCompanies; i++){
   		 printf("%-15s %11d %17d\n", (*(company+i)).name, (*(company+i)).id, (*(company+i)).VAT_id);
   	 }
    printf("---------------------------------------------------------------\n");


    /* Open file in reading mode (File should exist or it will return NULL)*/
    fptr = fopen("COMPANIES.dat","r");

    /* If pointer returns NULL File doesn't exist or user doesn't have access to it,
   	 else, write company contents into file.*/
    if (fptr == NULL){
   	 /* Print warning */
   	 printf("WARNING\nFile doesn't exist or it can't be read.\n");
    } else {
   	 /* Close reading mode */
   	 fclose(fptr);
   	 /* Open file in writing mode and print values */
   	 fptr = fopen("COMPANIES.dat","w");
   	 fprintf(fptr,"COMPANY NAME \t COMPANY ID \t COMPANY VAT\n");
   	 fprintf(fptr,"---------------------------------------------------------------\n");
   	 for (i = 0; i< numOfCompanies; i++){
   		 fprintf(fptr,"%-15s %11d %17d\n", (*(company+i)).name, (*(company+i)).id, (*(company+i)).VAT_id);
   	 }
   	 fprintf(fptr,"---------------------------------------------------------------\n");
   	 /* Close file */
   	 fclose(fptr);
    }/* end file */

    /*Waint for chat input before exit program*/
    getch();
}/* end main */

