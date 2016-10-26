#include<stdio.h>
#include<conio.h>
　
void main()
{
	int day;
	int month;
	int year;
	int leap;
	int result=0;
	int i;
　
		printf("Enter day: ");
		scanf("%d", &day);
		printf("Enter month: ");
		scanf("%d", &month);
		printf("Enter year: ");
		scanf("%d", &year);
　
　
			for (i = 1; i < month; i++) {
				if(i==2){result+=28;}
				else if(i==7)	{result+=31;}
				else if (i%2==1 && i <= 6)	{result +=31;	}
				else if ((i%2 == 0) && (i <= 6)){result +=30;}
				else if ((i%2 == 0) && (i > 7)){	result +=31;}
				else if ((i%2 != 0) && (i > 7)){	result +=30;}
			}
			result += day;
			
if ((year % 400 == 0) || (year %100 != 0) && (year%4 == 0))
				{	leap = 1;
					printf("leap year\n");
				} else {
					leap = 0;
					printf("Not Leap\n");
				}
				if(leap==1 && month>2){result++;	}
				printf("day number %d", result);
		getch();
