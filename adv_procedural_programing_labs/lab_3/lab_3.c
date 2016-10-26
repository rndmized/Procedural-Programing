#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

/* Prototypes declaration */
/* Returns the winner at a given state */
int calculateStateVotes(int votes[][4], int state);
/* Returns the candidate who won in most states */
int calculateMayor(int votes[][4]);
/* Print to screen the winner of each state */
void displayStateWinner(int votes[][4]);
/* Print Votes table into a file */
void printTableToFile(int votes[][4], char state[5][15], char candidate[4][15]);

void main() {

    /* Variable declaration */
    int votes[5][4]; /* Stores values of votes per candidate per state*/
    char candidate[4][15] = { "Candidate 1","Candidate 2","Candidate 3","Candidate 4" }; /* Candidates names */
    char state[5][15] = { "State 1","State 2","State 3","State 4","State 5" };/* States names */
    int i, j;/* Loop variables */
    /* End of Variable declaration */

    /* Ask user input */
    printf("Please enter number of votes for:\n");
    for (i = 0; i<5; i++) {
   	 for (j = 0; j<4; j++) {
   		 /* Temp stores the input value */
   		 int temp;
   		 /* While temp is smaller tha 0 (negative number) it will keep
   		 asking for input for a given candidate at a given state*/
   		 do {
   			 printf("%s at %s: ", candidate[j], state[i]);
   			 scanf("%d", &temp);
   			 if (temp < 0) {
   				 printf("Invalid data (negative  votes )  – re-try\n");
   			 }
   		 } while (temp < 0);
   		 votes[i][j] = temp;/* Assign valid value to position in array */
   	 }/* End j for loop */
    }/* End i for loop */
    
    /* Print  to screen inputed values */
    printf("\nTable of the vote data.\n");
    printf("State \t %12s %12s %12s %12s\n", candidate[0], candidate[1], candidate[2], candidate[3]);
    for (i = 0; i<5; i++) {
   	 printf("%-s ", state[i]);
   	 for (j = 0; j<4; j++) {
   		 printf("%13d", votes[i][j]);
   	 }/* End j for loop */
   	 printf("\n");
    }/* End i for loop */

    /* Call method to print table into a file */
    printTableToFile(votes, state, candidate);

    /* Print to screen the winner for every state */
    displayStateWinner(votes);

    /* Print the candidate who won in most states */
    printf("\nThe new Mayor is %s.\n\n", candidate[calculateMayor(votes)]);

    /* Await user intput before finish main method*/
    getch();
}/* End of main method*/

int calculateStateVotes(int votes[][4], int state) {
    /* Variables */
    int i = 0;
    int mostVotes = 0;
    int elected = 0;
    /* End of variable declaration */

    /* Loop through the array at index [state] for every candidate */
    for (i = 0; i < 4; i++) {
   	 if (votes[state][i] > mostVotes) {
   		 mostVotes = votes[state][i];
   		 elected = i;
   	 }/* End if */
    }/* End i for loop */

    /* Return the candidate with most votes at a given state*/
    return elected;
}

int calculateMayor(int votes[][4]) {
    /* Variables */
    int i, j = 0; /* Loop variables */
    int winner = 0;/* Store the winner candidate*/
    int mostVotes = 0; /* Store the maximum amount of votes */
    int candidateVoted[4] = { 0,0,0,0 };/*Array to store number of victories of the candidates*/
    /* End of variable declaration */

    /* Loop through votes to calculate the candidate who won in most states,
   	 each iteration increases the number of victories of the correspondant candidate in a state [i]*/
    for (i = 0; i < 5; i++)
    {
   	 switch (calculateStateVotes(votes, i)) {
   		 case 0:
   			 candidateVoted[0]++;
   			 break;
   		 case 1:
   			 candidateVoted[1]++;
   			 break;
   		 case 2:
   			 candidateVoted[2]++;
   			 break;
   		 case 3:
   			 candidateVoted[3]++;
   			 break;
   	 }/* End switch */
    }/* End i for loop */
    /* Loop thorugh the array to determine the candidate with most victories */
    for (i = 0; i < 4; i++)
    {
   	 if (candidateVoted[i] > mostVotes) {
   		 mostVotes = candidateVoted[i];
   		 winner = i;
   	 }/* End if */
    }/* End i for loop */
    /* Return the candidate with most victories */
    return winner;
}

void displayStateWinner(int votes[][4])
{
    int i = 0;/* Loop variable */
    /* Loop throug votes, switch the returning value of calculateStateVotes()
   	 to display the winner of each state*/
    printf("\n");
    for (i = 0; i < 5; i++)
    {
   	 printf("\Winner of state %d: ", i + 1);
   	 switch (calculateStateVotes(votes, i)) {
   	 case 0:
   		 printf(" Candidate 1 \n");
   		 break;
   	 case 1:
   		 printf(" Candidate 2 \n");
   		 break;
   	 case 2:
   		 printf(" Candidate 3 \n");
   		 break;
   	 case 3:
   		 printf(" Candidate 4 \n");
   		 break;
   	 }/* End switch */
    }/* End i for loop */
}

void printTableToFile(int votes[][4], char state[5][15], char candidate[4][15])
{

    FILE * fptr;/* File Pointer */
    int i, j = 0;/* Loop variables */

    /* Open file in writing mode (File should be created or it will return NULL)*/
    fptr = fopen("votes.txt", "w");

    /* If pointer returns NULL File doesn't exist or user doesn't have access to it,
    else, write votes contents into file.*/
    if (fptr == NULL) {
   	 /* Print warning */
   	 printf("WARNING\nFile doesn't exist or it can't be read.\n");
    }
    else {
   	 /*  Print values into file */
   	 fptr = fopen("votes.txt", "w");
   	 fprintf(fptr, "\nTable of the vote data.\n");
   	 fprintf(fptr, "State \t %12s %12s %12s %12s\n", candidate[0], candidate[1], candidate[2], candidate[3]);
   	 for (i = 0; i<5; i++) {
   		 fprintf(fptr, "%-s ", state[i]);
   		 for (j = 0; j<4; j++) {
   			 fprintf(fptr, "%13d", votes[i][j]);
   		 }/* End j for loop */
   		 fprintf(fptr, "\n");
   	 }/* End i for loop */
   	 fclose(fptr);/* Close file */
    }/* end file */

}
