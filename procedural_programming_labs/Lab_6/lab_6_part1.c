#include<stdio.h>
#include<conio.h>


void main(){
int matrix1[3][3];
int matrix2[3][3];
int matrixResult[3][3];
int i, j;

printf("Matrix 1\n");
for (i=0;i<3;i++){
    for (j=0;j<3;j++){
  	 printf("Please enter value for row %d, Column %d: ", (i+1), (j+1));
  	 scanf("%d", &matrix1[i][j]);
    }
}
printf("\nMatrix 2\n");
for (i=0;i<3;i++){
    for (j=0;j<3;j++){
  	 printf("Please enter value for row %d, Column %d: ", (i+1), (j+1));
  	 scanf("%d", &matrix2[i][j]);
    }
}

printf("Matrix Result:");
for (i=0;i<3;i++){
    printf ("\nRow %d: ", (i+1));
    for (j=0;j<3;j++){
  	 matrixResult[i][j] = matrix1[i][j] + matrix2[i][j];
  	 printf("%d  ", matrixResult[i][j]);
    }
}

getch();
}
