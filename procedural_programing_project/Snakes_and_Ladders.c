/*
91	92	93	94	95	96	97	98	99	100
81	82	83	84	85	86	87	88	89	90
71	72	73	74	75	76	77	78	79	80
61	62	63	64	65	66	67	68	69	70
51	52	53	54	55	56	57	58	59	60
41	42	43	44	45	46	47	48	49	50
31	32	33	34	35	36	37	38	39	40
21	22	23	24	25	26	27	28	29	30
11	12	13	14	15	16	17	18	19	20
1	2	3	4	5	6	7	8	9	10


Given the Board being 10x10:
●	Every ladder climbs to a random point on the row above.
●	Every snake slips down to the row below.
●	Given that there has to be 7 snakes and 7 ladders, the first and the last rows will be “Safe rows”(no snakes or ladders).
●	The beginning of a ladder can´t be in the same place as the beginning of a snake
●	There will be only one game saved at a time.


*/

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>

typedef struct
{
    int snake[2];
} snakes_t;

typedef struct
{
    int ladder[2];
} ladder_t;

typedef struct
{
    int tileNum;
    int ladders;
    ladder_t ladder;
    int snakes;
    snakes_t snake;
    int playerTurn;
} tile_t;

typedef struct
{
    int playerNum;
    int tilePos;
    int activeTurn;
} player_t;

void main();
int randomNum(int seed, int max);
void printBoard(ladder_t ladder[], snakes_t snake[]);
void playGame(int players, tile_t tiles[], snakes_t snake[], ladder_t ladder[], player_t ply[]);
void saveGame(int players, player_t ply[], snakes_t snake[], ladder_t ladder[]);



void main() {
    
    ladder_t ladder[7];
    snakes_t snake[7];
    player_t *ply;
    FILE * fptr;
    
    int i=0;
    int j = 0;
    int temp=0;
    int loopFlag = 0;
    int players = 0;

    int option;

#pragma region Menu
    do {
   	 printf("Welcome to Snakes & Ladders!\n");
   	 printf("Please, select one of the following options:\n");
   	 printf("1. New Game\n");
   	 printf("2. Load Game\n");
   	 printf("3. Exit Game\n");
   	 scanf("%d", &option);
    } while (option != 1 && option != 2 && option != 3);
#pragma endregion

#pragma region New Game
    if (option == 1) {//if option selected is 1, it creates a new board ands asks for the number of players before starting the game
#pragma region Setting Tiles

   	 //Tiles Template
   	 tile_t newTile;
   	 newTile.ladders = 0;
   	 newTile.snakes = 0;
   	 //end of Template

   	 //Setting Tiles
   	 tile_t tiles[100];
   	 for (i = 0; i < 100; i++) {
   		 newTile.tileNum = i + 1;
   		 tiles[i] = newTile;
   	 }
   	 //end of Tile Setting
#pragma endregion
#pragma region Setting Snakes and Ladders
   	 do {
   		 loopFlag = 0;
   		 //Setting Ladders
   		 for (i = 0; i < 7; i++) {
   			 for (j = 0; j < 2; j++) {
   				 if (i != 0 && j < 1) {
   					 do {
   						 temp = 0;
   						 temp = randomNum((rand() % 512) + i + j, 9) + (10 * i) + (10 * j) + 10;
   						 ladder[i].ladder[j] = temp;
   					 } while (ladder[i].ladder[0] == ladder[i - 1].ladder[1]);//it generates random numbers until the begining of the ladder != to the end of the previous ladder
   				 }
   				 else {
   					 ladder[i].ladder[j] = randomNum((rand() % 512) + i + j, 9) + (10 * i) + (10 * j) + 10;//first ladder generated
   				 }
   			 }
   		 }

   		 //Adding ladders to Tiles
   		 for (i = 0; i < 7; i++) {
   			 int position = ladder[i].ladder[0];
   			 tiles[position].ladders = 1;
   			 tiles[position].ladder = ladder[i];
   		 }
   		 //end of Ladder Addition

   		 //End of Ladder Setting

   		 //Snake Setting
   		 for (i = 0; i < 7; i++) {
   			 for (j = 0; j < 2; j++) {
   				 if (i != 0 && j < 1) {
   					 do {
   						 temp = 0;
   						 temp = randomNum((rand() % 512) + i + j,9) + (10 * i) + (10 * j) + 10;
   						 snake[i].snake[j] = temp;
   					 } while (snake[i].snake[0] == snake[i - 1].snake[1]);//it generates random numbers until the begining of the snake != to the end of the previous snake
   				 }
   				 else {
   					 snake[i].snake[j] = randomNum((rand() % 512) + i + j,9) + (10 * i) + (10 * j) + 10;//returns a number between 1 and 10 and adds 10 for every iteration of every loop (design rule)
   				 }
   				 if (i != 0 && j > 0) {
   					 do {
   						 temp = 0;
   						 temp = randomNum((rand() % 512) + i + j,9) + (10 * i) + (10 * j) + 10;
   						 snake[i].snake[1] = temp;
   					 } while (tiles[snake[i].snake[1]].ladders != 0);//it generates random numbers until the begining of the snake != to the begining of the any ladder
   				 }
   			 }
   		 }
   		 for (i = 0; i < 7; i++) {
   			 int position = snake[i].snake[1];
   			 tiles[position].snakes = 1;
   			 tiles[position].snake = snake[i];
   		 }
   		 //End of Snake Setting

   		 for (i = 0; i < 7; i++) {//for every ladder and snake, checks if there is any loop and recreates the board if so until no loops are found
   			 for (j = 0; j < 7; j++) {
   				 if ((snake[i].snake[0] == ladder[j].ladder[0]) && (snake[i].snake[1] == ladder[j].ladder[1])) {
   					 loopFlag++;
   				 }
   			 }
   		 }
   	 } while (loopFlag != 0);//while loops are found the board is recreated
#pragma endregion
#pragma region Setting Players    
   	 do {
   		 printf("Select number of players (1 - 6): ");
   		 scanf("%d", &players);
   		 fflush(stdin);
   	 } while (players < 1 || players > 6 );//ask the number of players while it is smaller than 1 or bigger than 4
   	 ply = (player_t *)malloc(sizeof(player_t)*players);//allocates space if memory according to the number of players
   	 for (i = 0; i < players; i++) {
   		 (*(ply+i)).tilePos = 0;
   		 (*(ply + i)).playerNum = i + 1;
   	 }//sets the players
#pragma endregion
#pragma region Printing Board
   	 printBoard(ladder, snake);
#pragma endregion
#pragma region Game
   	 playGame(players, tiles, snake, ladder, ply,0);
#pragma endregion
    }
#pragma endregion
#pragma region Load Game
    if (option == 2) {//if option selected is 2, loads the previously saved game
   	 int playerTurn;
   	 /* fopen opens file; exits program if file cannot be opened */
   	 if ((fptr = fopen("savegame.dat", "r")) == NULL)
   	 {
   		 printf("File could not be opened\n");
   	 } /* end if */
   	 else
   	 { /* read data from file */
   		 fscanf(fptr, "%d\n", &players);//read the number of players
   		 ply = (player_t *)malloc(sizeof(player_t)*players);//allocates spaces in memory acording to the num of players readed
   		 switch (players)//for every player sets their player number and reads in their position
   		 {
   		 case 1:
   			 (*(ply)).playerNum = 1;
   			 fscanf(fptr, "%d", &(*(ply)).tilePos);
   			 break;
   		 case 2:
   			 (*(ply)).playerNum = 1;
   			 (*(ply + 1)).playerNum = 2;
   			 fscanf(fptr, "%d_%d_", &(*(ply)).tilePos, &(*(ply + 1)).tilePos);
   			 break;
   		 case 3:
   			 (*(ply)).playerNum = 1;
   			 (*(ply + 1)).playerNum = 2;
   			 (*(ply + 2)).playerNum = 3;
   			 fscanf(fptr, "%d_%d_%d_", &(*(ply)).tilePos, &(*(ply + 1)).tilePos, &(*(ply + 2)).tilePos);
   			 break;
   		 case 4:
   			 (*(ply)).playerNum = 1;
   			 (*(ply + 1)).playerNum = 2;
   			 (*(ply + 2)).playerNum = 3;
   			 (*(ply + 3)).playerNum = 4;
   			 fscanf(fptr, "%d_%d_%d_%d_", &(*(ply)).tilePos, &(*(ply + 1)).tilePos, &(*(ply + 2)).tilePos, &(*(ply + 3)).tilePos);
   			 break;
   		 case 5:
   			 (*(ply)).playerNum = 1;
   			 (*(ply + 1)).playerNum = 2;
   			 (*(ply + 2)).playerNum = 3;
   			 (*(ply + 3)).playerNum = 4;
   			 (*(ply + 4)).playerNum = 5;
   			 fscanf(fptr, "%d_%d_%d_%d_%d_", &(*(ply)).tilePos, &(*(ply + 1)).tilePos, &(*(ply + 2)).tilePos, &(*(ply + 3)).tilePos, &(*(ply + 4)).tilePos);
   			 break;
   		 case 6:
   			 (*(ply)).playerNum = 1;
   			 (*(ply + 1)).playerNum = 2;
   			 (*(ply + 2)).playerNum = 3;
   			 (*(ply + 3)).playerNum = 4;
   			 (*(ply + 4)).playerNum = 5;
   			 (*(ply + 5)).playerNum = 6;
   			 fscanf(fptr, "%d_%d_%d_%d_%d_%d_", &(*(ply)).tilePos, &(*(ply + 1)).tilePos, &(*(ply + 2)).tilePos, &(*(ply + 3)).tilePos, &(*(ply + 4)).tilePos, &(*(ply + 5)).tilePos);
   			 break;
   		 }
   		 for (i = 0; i < 7; i++) {//reads the ladders positions
   			 fscanf(fptr, "%d_%d\n", &(ladder[i].ladder[0]), &(ladder[i].ladder[1]));
   		 }

   		 fscanf(fptr, "\n");
   		 for (i = 0; i < 7; i++) {//reads the snakes positions
   			 fscanf(fptr, "%d_%d\n", &(snake[i].snake[0]), &(snake[i].snake[1]));
   		 }
   		 fscanf(fptr, "%d_\n", &playerTurn);//reads the las player active turn
   	  /* end Loading Data */

   		 fclose(fptr); /* fclose closes the file */

   		 //Tiles Template
   		 tile_t newTile;
   		 newTile.ladders = 0;
   		 newTile.snakes = 0;
   		 //end of Template
   		 //Setting Tiles
   		 tile_t tiles[100];
   		 for (i = 0; i < 100; i++) {
   			 newTile.tileNum = i + 1;
   			 tiles[i] = newTile;
   		 }
   		 //end of Tile Setting
   		 
   		 printf("\n");
   		 //re-setting Ladders
   		 for (i = 0; i < 7; i++) {
   			 int position = ladder[i].ladder[0];
   			 tiles[position].ladders = 1;
   			 tiles[position].ladder = ladder[i];
   		 }
   		 //re-setting Snakes
   		 for (i = 0; i < 7; i++) {
   			 int position = snake[i].snake[1];
   			 tiles[position].snakes = 1;
   			 tiles[position].snake = snake[i];
   		 }
   		 printBoard(ladder, snake);//prints board
   		 printf("Players Positions:\n");
   		 int h = 0;
   		 for (h = 0; h < players; h++) {//prints players position
   			 printf("Player %d: %d \t", (*(ply + h)).playerNum, (*(ply + h)).tilePos);
   		 }
   		 playGame(players, tiles, snake, ladder, ply, playerTurn);//re-creates the game with the loaded settings
   	 } /* end else */
    }

#pragma endregion
#pragma region Exit
    if (option == 3) exit(0);//if option selected is 3, the program finishes
#pragma endregion
    getch();
}

int    randomNum(int seed, int max) {    
    time_t t;
    srand((unsigned)time(&t)*seed);
    int num = ((rand() % max) + 1);
    return num;

}//Returns a random number given a seed and a maximum number (-1)

void printBoard(ladder_t ladder[], snakes_t snake[])
{
    int i = 0;
    printf("Ladders \t|\t Snakes\n");
    for (i = 0; i < 7; i++) {
   	 printf("%d - %d \t|\t %d - %d", ladder[i].ladder[0], ladder[i].ladder[1], snake[i].snake[1], snake[i].snake[0]);
   	 printf("\n");
    }
}//Prints the location of the snakes and the ladders on the board

void playGame(int players, tile_t tiles[], snakes_t snake[], ladder_t ladder[], player_t ply[], int j)
{
    int i;
    int h = 0;
    int temp=0;
    int win = 0;
    char yn;
    char eyn;
    
    if (j >= 6) { j = 0; }// j represents the last player's turn
    
    do {//while nobody wins...
   	 printf("\n");
   	 for (i = j; i < players; i++) {//for every player...
   		 printf("Turn Player %d\n", (*(ply + i)).playerNum);
   		 (*(ply + i)).activeTurn = 1;//sets current player turn to active
   		 printf("Player rolled dice (1 - 6).");
   		 temp = randomNum((rand() % 512) + i , 5);//asking for a random number between 1 and 6 (+1 is added in the function)
   		 printf("Dice rolled a %d!\n", temp);
   		 (*(ply + i)).tilePos += temp;//increases the player position
   		 if ((*(ply + i)).tilePos >= 100) {//check winning condition
   			 win = 1;
   			 printf("Player %d wins!\n", (*(ply + i)).playerNum);
   			 getch();
   			 exit(1);
   			 break;
   		 }
   		 if (tiles[(*(ply + i)).tilePos].ladders == 1 || tiles[(*(ply + i)).tilePos].snakes == 1) {//check id the player lands on a ladder or on a snake
   			 printf("Player %d is now at Tile %d\n", (*(ply + i)).playerNum, (*(ply + i)).tilePos);
   			 do {//while the player lands on a ladder/snake
   				 if (tiles[(*(ply + i)).tilePos].ladders == 1) {//if he lands on a ladder
   					 (*(ply + i)).tilePos = tiles[(*(ply + i)).tilePos].ladder.ladder[1];//set player position equal to the top of the ladder
   					 int ladderEnd = (*(ply + i)).tilePos;
   					 printf("Player %d found a ladder!\n Player %d advances to tile %d\n", (*(ply + i)).playerNum, (*(ply + i)).playerNum, ladderEnd);//print where the player ends
   				 }
   				 else if (tiles[(*(ply + i)).tilePos].snakes == 1) {//if he lands on a snake
   					 (*(ply + i)).tilePos = tiles[(*(ply + i)).tilePos].snake.snake[0];//set player position equal to the bottom of the snake
   					 int snakeTail = (*(ply + i)).tilePos;
   					 printf("Player %d found a snake!\n Player %d goes back to tile %d\n", (*(ply + i)).playerNum, (*(ply + i)).playerNum, snakeTail);//print where the player ends
   				 }
   			 } while (tiles[(*(ply + i)).tilePos].ladders == 1 || tiles[(*(ply + i)).tilePos].snakes == 1);//loop condition
   		 } else {//if the player doesn´t win, but doesnt land on a ladder/snake either...
   				 printf("Player %d is now at Tile %d\n", (*(ply + i)).playerNum, (*(ply + i)).tilePos);
   		 }

   		 printf("Players Positions:\n");
   		 for (h = 0; h < players; h++) { // prints to the screen every player position at the end of every player's turn
   			 printf("Player %d: %d \t", (*(ply + h)).playerNum, (*(ply + h)).tilePos);
   		 }
   		 printf("\n");
   		 printBoard(ladder, snake);// prints to the screen the board at the end of every player's turn
   		 yn = 'o';
   		 do {//asks the player if he wants to keep playing at the end of every player's turn while the answer is not y/Y or n/N
   			 printf("Keep playing? (Y/N)");
   			 scanf("%s", &yn);
   		 } while ((yn != 'n') && (yn != 'y') && (yn != 'N') && (yn != 'Y'));
   		 
   		 switch (yn) {
   		 case 'n':
   		 case 'N':
   			 do {//ask the player to exit and save or just exit while the answer is not y/Y or n/N
   				 printf("Exit and Save Game (Y) or Exit Game Without Saving (N)? (Y/N)");
   				 scanf("%s", &eyn);
   			 } while ((eyn != 'n') && (eyn != 'y') && (eyn != 'N') && (eyn != 'Y'));
   			 switch (eyn) {
   			 case 'n':
   			 case 'N':
   				 exit(1);
   				 break;
   			 case 'y':
   			 case 'Y':
   				 printf("Starting Saving Game and Exiting\n");
   				 saveGame(players, ply, snake, ladder);//saves the game
   				 getch();
   				 exit(1);
   				 break;
   			 }
   			 break;
   		 case 'y':
   		 case 'Y':
   			 (*(ply + i)).activeTurn = 0;//sets the players turn from "active"(1) to "inactive"(0)
   			 break;
   		 }
   		 printf("\n");
   	 }
    } while (win == 0);//winning condition
}//Game mechanics

void saveGame(int players, player_t ply[], snakes_t snake[], ladder_t ladder[])
{
    FILE * fptr;
    int i = 0;

    //opens the file
    fptr = fopen("savegame.dat","w");
    //saves the number of players
    fprintf(fptr, "%d\n", players);
    //saves the position of every player
    for (i = 0; i < players; i++) {
   	 fprintf(fptr, "%d_", (*(ply+i)).tilePos);
    }//end for
    fprintf(fptr, "\n");
    //ladders
    for (i = 0; i < 7; i++) {
   	 fprintf(fptr, "%d_%d\n", ladder[i].ladder[0], ladder[i].ladder[1]);
    }//end for
    fprintf(fptr, "\n");
    //snakes
    for (i = 0; i < 7; i++) {
   	 fprintf(fptr, "%d_%d\n", snake[i].snake[0], snake[i].snake[1]);
    }//end for
    //player turn
    for (i = 0; i < players; i++) {
   	 if ((*(ply + i)).activeTurn == 1) {
   		 fprintf(fptr, "%d_\n", (*(ply+i)).playerNum);
   	 }//end if
    }//end for
    //closes the file
    fclose(fptr);
}//saves the necessary data to load the game


