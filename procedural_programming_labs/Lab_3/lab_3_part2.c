#include<stdio.h>
#include<conio.h>
　
void main()
{
	float value1;
	float value2;
	char operation;
	float result;
		
		printf("Enter operation (A for addition, S for substraction, M for Multiplication, D for division):");
		scanf("%c", &operation);
		printf("Enter Value1: ");
		scanf("%f", &value1);
		printf("Enter Value2: ");
		scanf("%f", &value2);
		
		switch(operation){
			case 'A':
				result = value1+value2;
				break;
			case 'S':
				result = value1-value2;
				break;
			case 'M':
				result = value1*value2;
				break;
			case 'D':
				result = value1/value2;
				break;
			default:
				result = -9999;
				break;
		}
		printf("Result is: %f", result);
		getch();
}
