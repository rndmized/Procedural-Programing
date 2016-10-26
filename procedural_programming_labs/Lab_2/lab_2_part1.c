#include<stdio.h>
#include<conio.h>

void main()
{
     float totalWidth;
     float tileWidth;
     int numOfTiles;
     float gap;

   	 printf("Enter the total width: ");
   	 scanf("%f", &totalWidth);

   	 printf("Enter the tile's width: ");
   	 scanf("%f", &tileWidth);

   	 numOfTiles = totalWidth/tileWidth;
 
   	 if ((numOfTiles % 2) == 0){
   		 numOfTiles-=1;
   	 }
    
   	 gap = (totalWidth - (numOfTiles*tileWidth))/2;
   	 printf("Number of tiles: %d", numOfTiles);
   	 printf("\nGap at each side: %.2f", gap);
 
   	 getch();
}
