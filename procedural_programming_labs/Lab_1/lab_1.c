#include<stdio.h>
#include<conio.h>

void main()
{
    int numOfTwoEuro;
    int numOfOneEuro;
    int numOfFiftyCent;
    int numOfTwentyCent;
    int numOfTenCent;
    int numOfFiveCent;
    int numOfTwoCent;
    int numOfOneCent;
    int totalcents=0;

    do {
    printf("Enter the number of Two Euro Coins\n");
    scanf("%d",&numOfTwoEuro);
    } while(numOfTwoEuro<0);
    printf("Enter the number of One Euro Coins\n");
    scanf("%d",&numOfOneEuro);
    printf("Enter the number of Fifty Cent Coins\n");
    scanf("%d",&numOfFiftyCent);
    printf("Enter the number of Twenty Cent Coins\n");
    scanf("%d",&numOfTwentyCent);
    printf("Enter the number of Ten Cent Coins\n");
    scanf("%d",&numOfTenCent);
    printf("Enter the number of Five Cent Coins\n");
    scanf("%d",&numOfFiveCent);
    printf("Enter the number of Two Cent Coins\n");
    scanf("%d",&numOfTwoCent);
    printf("Enter the number of One Cent Coins\n");
    scanf("%d",&numOfOneCent);
    

    totalcents += numOfTwoEuro*200;
    totalcents += numOfOneEuro*100;
    totalcents += numOfFiftyCent*50;
    totalcents += numOfTwentyCent*20;
    totalcents += numOfTenCent*10;
    totalcents += numOfFiveCent*5;
    totalcents += numOfTwoCent*2;
    totalcents += numOfOneCent*1;

    printf("Total Value in cents is %d\n", totalcents);
    getch();
}
