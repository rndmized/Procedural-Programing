#include<stdlib.h>
#include<stdio.h>
#include<conio.h>


void main() {

    //Variable declaration
    int d1Size = 0; //Stores the size of the one dimension array
    int d2Size1 = 0;//stores the number of rows of the two dimensional array
    int d2Size2 = 0;//stores the number of columns of the two dimensional array
    int i = 0; //loop variable
    int j = 0;//loop variable
    int* singleArray; //points the space in memory for the one dimension array
    int** doubleArray; //points the space in memory for the two dimension array
    int* position;//stores the first position of the pointer for the one dimension array
    int** position2D;//stores the first position of the pointer for the two dimension array
    //en of variable declaration


    printf("Enter size for a 1 Dimension Array: "); //Asks the user to input one dimension array size
    scanf("%d", &d1Size);//stores input in variable
    singleArray = (int*)malloc(sizeof(int)*d1Size);//allocates in memory space for the one dimension array
    position = singleArray;//stores the first position of the pointer for the one dimension array


    for (i = 0; i<d1Size; i++)//loop a total number of times as the size of the one dimension array
    {
   	 printf("Enter number %d: ", i + 1);//Asks the user to input a number
   	 scanf("%d", singleArray);//stores value in pointed location
   	 singleArray++;//increments the pointer position
    }//end for

    singleArray -= d1Size; //sets the pointes position back in the first position
    for (i = 0; i<d1Size; i++)//loop a total number of times as the size of the one dimension array
    {
   	 printf("%d ", *singleArray);//prints value in that pointer's position
   	 singleArray++;//increments the pointer position
    }//end for

    printf("\nEnter size for a 2 Dimension Array (Enter Values with a space in between and press enter): ");//Asks the user to input two dimension array size
    scanf("%d %d", &d2Size1, &d2Size2);//stores input in variables

    doubleArray = (int**)malloc(d2Size1*sizeof(int *)); // allocates in memory space for the two dimension array [rows]
    position2D = doubleArray;//stores the first position of the pointer for the two dimension array

    for (i = 0; i<d2Size1; i++) {//loop a total number of times as the number of rows in the two dimension array
   	 doubleArray[i] = (int*)malloc(sizeof(int)*d2Size2); // allocates in memory space for the one dimension array [Columns]
    }//end for

    for (i = 0; i<d2Size1; i++) {//loop a total number of times as the number of rows and columns in the two dimension array [rows]
   	 for (j = 0; j<d2Size2; j++) {//[Columns]
   		 printf("Enter row %d, Col. %d: ", i + 1, j + 1);//ask user for input for a row x column y
   		 scanf("%d", (*(doubleArray + i) + j));//stores value in pointers position
   	 }//end nested for
    }//end for

    doubleArray = position2D;//sets the pointes position back in the first position
    
    for (i = 0; i<d2Size1; i++) {//loop a total number of times as the number of rows and columns in the two dimension array [rows]
   	 printf("\n");//new line
   	 for (j = 0; j<d2Size2; j++) {//[Columns]
   		 printf(" %d ", *(*(doubleArray + i) + j));//prints value in that pointer's position
   	 }//end nested for
    }//end for
    getch();//wait for char input
}//end main
