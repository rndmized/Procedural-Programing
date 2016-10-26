
#include<string.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>


void main(){

    /* Variable Declaration */
    FILE * fptr; /* File Pointer */
    char line[60];/* Input String that store dept value(name) when reading from file */
    char dept[3][15]={{"Hardware"},{"Grocery"},{"Drapery"}};/* Department list*/
    float temp=0;/* temp variable to store sales values */
    float total=0;/* total value of sales*/
    /*
    0 = Hardware
    1 = Grocery
    2 = Drapery
    */
    float saleMax[3]= {0,0,0};/* max value of sale per department*/
    float avg[3] = {0,0,0};/* average sale per department*/
    int count[3] = {0,0,0};/* number of sales per department*/
    int i=0;/* loop variable */

    fptr = fopen("DailySales.txt","r");/* assign value to pointer */

    /* If the file pointer is pointing nowhere display message */
    if ((fptr = fopen("DailySales.txt", "r")) == NULL){
   	 printf("File could not be opened\n");
    } else {
   	 /* If file pointer points to file, file file contains records keep reading*/
   	 while(!feof(fptr)){
   		 /* Reads department from file */
   		 fscanf(fptr,"%s", line);
   		 /* Reads value sale for that department*/
   		 fscanf(fptr,"%f", &temp);
   		 /* Calculate total */
   		 total += temp;

   		 /* Determine department.
   		 If dept. matches adds a sale, adds sales value to calculate average,
   		 and checks if sale read value is greater than any previous sale, if it is
   		 store the new value*/
   		 if (strcmp(line, dept[0])==0){
   			 count[0]++;
   			 avg[0] += temp;
   			 if (temp > saleMax[0]){
   				 saleMax[0] = temp;
   			 }/* end if */
   		 } else if(strcmp(line, dept[1])==0){
   			 count[1]++;
   			 avg[1] += temp;
   			 if (temp > saleMax[1]){
   				 saleMax[1] = temp;
   			 }/* end if */
   		 } else if(strcmp(line, dept[2])==0){
   			 count[2]++;
   			 avg[2] += temp;
   			 if (temp > saleMax[2]){
   				 saleMax[2] = temp;
   			 }/* end if */

   		 }/* end if */
   	 }/* end while */
    }/* end if */
    /* Close the file*/
    fclose(fptr);
    /* Calculate the average per Department*/
    for (i=0;i<3;i++){
   	 avg[i] = avg[i]/count[i];
    }
    
    /* Print Results */
    printf("Sales: \n");
    printf("Total: %f\n", total);
    printf("Hardware Average: %.2f \t Hardaware Max Sale: %.2f \n", avg[0], saleMax[0]);
    printf("Grocery Average: %.2f \t Grocery Max Sale: %.2f \n", avg[1], saleMax[1]);
    printf("Drapery Average: %.2f \t Drapery Max Sale: %.2f \n", avg[2], saleMax[2]);

    getch();
}/* end main method */

 
