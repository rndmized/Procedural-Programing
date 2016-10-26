#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

#pragma region Struct Definition

typedef struct gender_statistics{ 
	int survS[2][4];
	int survE[2][4];
	int survD[2][4];

	float survSP[2][4];
	float survEP[2][4];
	float survDP[2][4]; 
} gender_statistics_t;//Stores statistics by gender
typedef struct age_statistics {
	int survS[5][4];
	int survE[5][4];
	int survD[5][4];

	float survSP[5][4];
	float survEP[5][4];
	float survDP[5][4];
} age_statistics_t;//Stores statistics by age
typedef struct income_statistics {
	int survS[7][4];
	int survE[7][4];
	int survD[7][4];

	float survSP[7][4];
	float survEP[7][4];
	float survDP[7][4];
} income_statistics_t;//Stores statistics by income
typedef struct survey {

	char PPSN[10];
	char firstName[20];
	char lastName[20];
	char address[40];
	char email[30];
	int genderF;
	int ageF;
	int incomeF;
	int exerciseF;
	int drinkF;
	int smokeF;

} survey_t;//stores survey details
struct list {

	survey_t survey;
	struct list* next;

};//list of survey nodes
#pragma endregion

#pragma region Prototype Functions
/* Menu/List Functions */
int addSurvey(struct list** header); //adds a survey to the list
int updateSurvey(struct list** header);//change the values of a survey by ppsn
int deleteSurvey(struct list** header);//delete a survey by ppsn
void printSurveysDetails(struct list* header);//print all surveys details
void printSurveyDetail(struct list* header);//print survey details by ppsn
void statsMenu(struct list* header);//prints stats menu
int print_toStatsFile(struct list * header);//print stats and surveys into a file


/* Utility Functions */
struct list* getSurvey(struct list* header);//returns a survey node
int checkPPSN(struct list* header, char PPSN[10]);//checks if ppsn exists and returns its position
int checkEmail(char email[30]);//chesk if email is valid
int read_fromFile(struct list** header);//reads surveys froma file into a list
int print_toFile(struct list* header);//prints surveys into a file
void deleteLastSurvey(struct list** header);//delete survey if it is in last position
void deleteFirstSurvey(struct list** head_ptr);//delete survey if it is in first position
void deleteElementByPPSN(struct list** header);//delete survey if it is in not last nor first position
void passwordSurvey();//asks for user name and password in order to access the menu, exits if it doesn't match

/* Statistics Functions */
age_statistics_t getStatsByAge(struct list* header, int toFile); //returns stats by age
income_statistics_t getStatsByIncome(struct list * header, int toFile);//returns stats by income
gender_statistics_t getStatsByGender(struct list * header, int toFile);//returns stats by gender

/* String Functions */
char * getAgeBracket(int choice);//returns string with age options
char * getIncomeBracket(int choice);//returns string with income options
char * getAlcoholBracket(int choice);//returns string with drinking options
char * getExerciseBracket(int choice);//returns string with exercise options
char * getCigarettesBracket(int choice);//returns string with smoking options
char * getGender(int choice);
#pragma endregion

void main() {

	/* Variable declaration */
	struct list* top; /* Header pointer */
	int choice; /* Menu option selected */
	FILE * fptr;
	int test;

	//set pointer to null
	top = NULL;

	//ask user and password
	passwordSurvey();
	
	// if file cannot be read properly it sets the pointer to null again
	if (read_fromFile(&top) != -1) {
		if (getAgeBracket((*(top)).survey.ageF) == NULL)
		{
			top = NULL;
		}
	}
		
	//print menu
	do {
		system("cls");
		printf("****************************** MENU ******************************\n");
		printf("Please select one of the following: \n");
		printf("1: Add Survey. \n");
		printf("2: Display All Surveys. \n");
		printf("3: Display Survey Details. \n");
		printf("4: Update Survey. \n");
		printf("5: Delete Survey. \n");
		printf("6: Generate statistics. \n");
		printf("7: Print statistics to File. \n");
		printf("-1: Exit. \n");
		printf("Option Selected: ");
		scanf("%d", &choice);
		rewind(stdin);
		system("cls");

		switch (choice) {
			case -1:
				printf("Program Finished. Press any key to exit the program...");
				break;
			case 1:
				test = addSurvey(&top);
				print_toFile(top);
				break;
			case 2:
				printSurveysDetails(top);
				break;
			case 3:
				printSurveyDetail(top);
				break;
			case 4:
				updateSurvey(&top);
				print_toFile(top);
				break;
			case 5:
				deleteSurvey(&top);
				print_toFile(top);
				break;
			case 6:
				statsMenu(top);
				break;
			case 7:
				print_toStatsFile(top);
				break;
			default:
				printf("Invalid Option \n");
				break;
		}
		getch();
	} while (choice != -1);
	free(top);
}

#pragma region Menu/List Functions

int addSurvey(struct list** header)
{

	/* Adds anew survey to the list, if the list is empty it adds it to the front else it adds it in the last position*/
	struct list *temp;
	struct list *newNode;
	char PPSN[10];
	int test;

	if (*header == NULL) {

		newNode = (struct list*)malloc(sizeof(struct list));
		newNode = getSurvey(*header);
		if (newNode != -1) {
			newNode->next = *header;
			*header = newNode; // transfer the address of newNode' to'head'
			return 1;
		} else {
			return -1;
		}
	} else {

			temp = *header;
			while (temp->next != NULL) // go to the last node
			{
				temp = temp->next;
			}
			newNode = (struct list*)malloc(sizeof(struct list));
			newNode = getSurvey(*header);
			if (newNode != -1) {
				/* Set the node value to user intput */
				newNode->next = NULL;
				/* point newNode to NULL */
				temp->next = newNode;
				/* point previous node->next in the list to newNode */	
				return 1;
			} else {
				return -1;
			}
	}
	return 0;
}

int updateSurvey(struct list ** header)
{
	/* Gets ppsn from user to search, if it exists it allows the user to fill a survey to overwrite it*/

	char PPSN[10];
	int position;
	int i;
	struct list * temp;
	temp = *header;

	printf("Enter PPSN: ");
	scanf("%s", PPSN);
	rewind(stdin);
	position = checkPPSN(*header, PPSN);
	if (position == -1) {
		printf("PPSN not Found");
		return -1;
	}
	else {
		for (i = 0; i < position; i++) {
			temp = temp->next;
		}
		temp->survey = getSurvey(*header)->survey;
	}

	return 0;
}

int deleteSurvey(struct list ** header)
{
	/* Calls delete element by ppsn function*/
	deleteElementByPPSN(header);
	return 0;
}

void printSurveysDetails(struct list* header)
{

	/*Loops through the list and print the surveys details*/
	/* Variable declaration */
	struct list *temp;
	/* end of Variable declaration */

	temp = header;
	/* Print fields */
	printf("--------------------------- Surveys List ---------------------------\n");
	printf("%-10s %-10s %-10s %-10s %-10s %-20s %-10s %-10s %-10s %-10s %-10s \n", "PPSN", "Name", "Last Name", "Gender", "Address", "Email Address", "Age", "Income", "Exercise", "Drinking", "Smoking" );
	printf("-----------------------------------------------------------------------------------------------------------------------------\n");
	while (temp != NULL) // go to the last node

	{
		//Display the contents
		printf("%-10s %-10s %-10s %-10s %-10s %-20s %-10s %-10s %-10s %-10s %-10s\n", (*(temp)).survey.PPSN, (*(temp)).survey.firstName, (*(temp)).survey.lastName, getGender((*(temp)).survey.genderF), (*(temp)).survey.address, (*(temp)).survey.email, getAgeBracket((*(temp)).survey.ageF), getIncomeBracket((*(temp)).survey.incomeF), getExerciseBracket((*(temp)).survey.exerciseF), getAlcoholBracket((*(temp)).survey.drinkF), getCigarettesBracket((*(temp)).survey.smokeF));
		temp = temp->next;

	}
	printf("-----------------------------------------------------------------------------------------------------------------------------\n");
}

void printSurveyDetail(struct list * header)
{

	/* Search a specific ppsn in the list and print its details*/
	char PPSN[10];
	int position;
	int i;
	struct list * temp;
	temp = header;

	printf("Enter PPSN: ");
	scanf("%s", PPSN);
	rewind(stdin);
	position = checkPPSN(header, PPSN);
	if (position == -1) {
		printf("PPSN not Found\n");
	}
	else {
		for (i = 0; i < position; i++) {
			temp = temp->next;
		}
		printf("%-10s %-10s %-10s %-10s %-10s %-20s %-10s %-10s %-10s %-10s %-10s \n", "PPSN", "Name", "Last Name", "Gender", "Address", "Email Address", "Age", "Income", "Exercise", "Drinking", "Smoking");
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
		printf("%-10s %-10s %-10s %-10s %-10s %-20s %-10s %-10s %-10s %-10s %-10s\n", (*(temp)).survey.PPSN, (*(temp)).survey.firstName, (*(temp)).survey.lastName, getGender((*(temp)).survey.genderF), (*(temp)).survey.address, (*(temp)).survey.email, getAgeBracket((*(temp)).survey.ageF), getIncomeBracket((*(temp)).survey.incomeF), getExerciseBracket((*(temp)).survey.exerciseF), getAlcoholBracket((*(temp)).survey.drinkF), getCigarettesBracket((*(temp)).survey.smokeF));
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
	}
}

void statsMenu(struct list * header)
{
	/* print statistics menu, each option calls a function that prints the statitstics from the surveys based on the criteria selected*/
	int choice;
	do {
		system("cls");
		printf("Enter Statistics Criteria: \n");
		printf("1: By Gender. \n");
		printf("2: By Age. \n");
		printf("3: By Income. \n");
		printf("-1: Return to main menu. \n");
		scanf("%d", &choice);
		rewind(stdin);
		system("cls");

		switch (choice) {
		case -1:
			printf("Press any key to go back to Main Menu. \n");
			break;
		case 1:
			getStatsByGender(header, 0);
			getch();
			break;
		case 2:
			getStatsByAge(header, 0);
			getch();
			break;
		case 3:
			getStatsByIncome(header, 0);
			getch();
			break;
		default:
			printf("Invalid Option. Please press any key to return to statistics menu");
			getch();
			break;
		}
	} while (choice != -1);
}

#pragma endregion

#pragma region Utility Functions

struct list * getSurvey(struct list* header)
{

	/* ask user input to fill the survey struct and returns the list node containing it */
	struct list *newNode;
	newNode = (struct list*)malloc(sizeof(struct list));
	int validation = 0;

	printf("Enter Survey Details: \n");
	printf("Enter PPSN: ");
	scanf("%s", newNode->survey.PPSN);
	if (checkPPSN(header, newNode->survey.PPSN) != -1) return -1;
	printf("Enter First Name: ");
	scanf("%s", newNode->survey.firstName);
	printf("Enter Last Name: ");
	scanf("%s", newNode->survey.lastName);
	printf("Enter Address: (City Only)");
	scanf("%s", newNode->survey.address);
	do {
		printf("Enter email address: ");
		scanf("%s", newNode->survey.email);
		validation = checkEmail(newNode->survey.email);
	} while (validation != 1);
	do {
		printf("Enter Age Bracket: \n");
		printf("1: 18-20yrs. \n");
		printf("2: 21-30yrs. \n");
		printf("3: 31-50yrs. \n");
		printf("4: 51-65yrs. \n");
		printf("5: 65+ yrs.  \n");
		scanf("%d", &newNode->survey.ageF);
		rewind(stdin);
	} while (newNode->survey.ageF < 1 || newNode->survey.ageF > 5);
	do {
		printf("Enter Gendert: \n");
		printf("1: Male. \n");
		printf("2: Female. \n");
		scanf("%d", &newNode->survey.genderF);
		rewind(stdin);
	} while (newNode->survey.genderF < 1 || newNode->survey.genderF > 2);
	do {
		printf("Enter Income Bracket: \n");
		printf("1: No Income. \n");
		printf("2: Less than €20,000. \n");
		printf("3: Less than €40,000. \n");
		printf("4: Less than €60,000. \n");
		printf("5: Less than €80,000. \n");
		printf("6: Less than €100,000. \n");
		printf("7: Greater than €100,000. \n");
		scanf("%d", &newNode->survey.incomeF);
		rewind(stdin);
	} while (newNode->survey.incomeF < 1 || newNode->survey.incomeF > 7);
	do {
		printf("How often do you exercise? \n");
		printf("1: Never. \n");
		printf("2: Less than three times per week. \n");
		printf("3: Less than five times per week. \n");
		printf("4: More than five times per week. \n");
		scanf("%d", &newNode->survey.exerciseF);
		rewind(stdin);
	} while (newNode->survey.exerciseF < 1 || newNode->survey.exerciseF > 4);
	do {
		printf("How much alcohol do you consume per week? \n");
		printf("1: None. \n");
		printf("2: Less than two units. \n");
		printf("3: Less than four units. \n");
		printf("4: More than four units. \n");
		scanf("%d", &newNode->survey.drinkF);
		rewind(stdin);
	} while (newNode->survey.drinkF < 1 || newNode->survey.drinkF > 4);
	do {
		printf("How many cigarettes do you smoke per week? \n");
		printf("1: None. \n");
		printf("2: Less than 20 cigarettes. \n");
		printf("3: Less than 40 cigarettes. \n");
		printf("4: More than 40 cigarettes. \n");
		scanf("%d", &newNode->survey.smokeF);
		rewind(stdin);
	} while (newNode->survey.smokeF < 1 || newNode->survey.smokeF > 4);
	return newNode;
}

int checkPPSN(struct list * header, char PPSN[10])
{

	/*  search through the list, at the first occurrence of the ppsn it returns its position,
		if it doesn;t find it returns -1, returns -1 if finds error*/
	/* Variable declaration */
	struct list *temp;
	int counter = 0, found = 0;
	/* end of Variable declaration */

	temp = (struct list*)malloc(sizeof(struct list));
	temp = header;

	while (temp != NULL) {/* Go to the last node */
						  /* if finds the searched element prints its position, if not it keeps moving to the next element of the list */
		if (strcmp((*(temp)).survey.PPSN, PPSN) != 0) {
			/* increments counter */
			counter++;
			/* moves to the next element of the list */
			temp = temp->next;
		}
		else {
			found = 1;
			printf("PPSN found at Index: %d \n", counter + 1);
			/* If PPSN is found return position */
			return counter;
			break;
		}/*end else*/
	}/* end while*/
	if (found != 1) {
		/* If PPSN is not found return -1 */
		return -1;
	}/* end if */
	printf("-2: Error.");
	return -2;

}

int checkEmail(char email[30])

{
	/*Checks string if contains @ and .com in it, returns 1 if so else -1*/
	if ( ( strstr(email, ".com") ) && ( strstr(email, "@") ) ) {
		return 1;
	}
	printf("Invalid email. Please try again.\n");
	return -1;

	
}

gender_statistics_t getStatsByGender(struct list * header, int toFile)
{

	/* return struct with statistics based on gender, arg toFile represents 
		if it should print it to the screen or just return it for a file function*/

	/* Variable declaration */
	struct list *temp;
	gender_statistics_t gstats;
	int i, j, z;
	int stat = 0;
	int total[3] = { 0,0,0 };

	/* end of Variable declaration */
	/* Initialises values to 0*/
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 4; j++) {
			gstats.survS[i][j] = 0;
			gstats.survE[i][j] = 0;
			gstats.survD[i][j] = 0;
			gstats.survSP[i][j] = 0;
			gstats.survEP[i][j] = 0;
			gstats.survDP[i][j] = 0;
		}
	}
	temp = header;

	while (temp != NULL) // go to the last node
	{
		/*for every answer of the surve it adds up an array*/
		gstats.survS[temp->survey.genderF - 1][temp->survey.smokeF - 1]++;
		gstats.survE[temp->survey.genderF - 1][temp->survey.exerciseF - 1]++;
		gstats.survD[temp->survey.genderF - 1][temp->survey.drinkF - 1]++;
		temp = temp->next;
	}
	//calculate the total
	for (i = 0; i < 2; i++) {
		for (z = 0; z < 3; z++) {
			total[z] = 0;
		}
		for (j = 0; j < 4; j++) {
			total[0] += gstats.survS[i][j];
			total[1] += gstats.survE[i][j];
			total[2] += gstats.survD[i][j];
		}
		/*based on the total extract percentages*/
		if (total[0] != 0) {
			for (j = 0; j < 4; j++) {
				gstats.survSP[i][j] = (float)(100 * gstats.survS[i][j]) / total[0];
			}
		}
		if (total[0] != 0) {
			for (j = 0; j < 4; j++) {
				gstats.survEP[i][j] = (float)(100 * gstats.survE[i][j]) / total[0];
			}
		}
		if (total[0] != 0) {
			for (j = 0; j < 4; j++) {
				gstats.survDP[i][j] = (float)(100 * gstats.survD[i][j]) / total[0];
			}
		}
	}
	/*if its not for a file print to screen values*/
	if (toFile == 0) {
		printf("Exercise Statistics\n");
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
		printf("%-10s %-10s %-10s %-10s %-10s \n", "Gender", getExerciseBracket(1), getExerciseBracket(2), getExerciseBracket(3), getExerciseBracket(4));
		printf("%-10s %-10.2f %-10.2f %-10.2f %-10.2f \n", getGender(1), gstats.survEP[0][0], gstats.survEP[0][1], gstats.survEP[0][2], gstats.survEP[0][3]);
		printf("%-10s %-10.2f %-10.2f %-10.2f %-10.2f \n", getGender(2), gstats.survEP[1][0], gstats.survEP[1][1], gstats.survEP[1][2], gstats.survEP[1][3]);
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
		printf("Drinking Statistics\n");
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
		printf("%-10s %-10s %-10s %-10s %-10s \n", "Gender", getAlcoholBracket(1), getAlcoholBracket(2), getAlcoholBracket(3), getAlcoholBracket(4));
		printf("%-10s %-10.2f %-10.2f %-10.2f %-10.2f \n", getGender(1), gstats.survDP[0][0], gstats.survDP[0][1], gstats.survDP[0][2], gstats.survDP[0][3]);
		printf("%-10s %-10.2f %-10.2f %-10.2f %-10.2f \n", getGender(2), gstats.survDP[1][0], gstats.survDP[1][1], gstats.survDP[1][2], gstats.survDP[1][3]);
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
		printf("Smoking Statistics\n");
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
		printf("%-10s %-10s %-10s %-10s %-10s \n", "Gender", getCigarettesBracket(1), getCigarettesBracket(2), getCigarettesBracket(3), getCigarettesBracket(4));
		printf("%-10s %-10.2f %-10.2f %-10.2f %-10.2f \n", getGender(1), gstats.survSP[0][0], gstats.survSP[0][1], gstats.survSP[0][2], gstats.survSP[0][3]);
		printf("%-10s %-10.2f %-10.2f %-10.2f %-10.2f \n", getGender(2), gstats.survSP[1][0], gstats.survSP[1][1], gstats.survSP[1][2], gstats.survSP[1][3]);
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
	}
	return gstats;
}

age_statistics_t getStatsByAge(struct list * header, int toFile)
{

	/* return struct with statistics based on age, arg toFile represents
	if it should print it to the screen or just return it for a file function*/

	/* Variable declaration */
	struct list *temp;
	int i, j,z;
	int total[3] = {0,0,0};
	age_statistics_t astats;
	/* end of Variable declaration */
	
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 4; j++) {
			astats.survS[i][j] = 0;
			astats.survE[i][j] = 0;
			astats.survD[i][j] = 0;
			astats.survSP[i][j] = 0;
			astats.survEP[i][j] = 0;
			astats.survDP[i][j] = 0;
		}
	}
	temp = header;
	
	while (temp != NULL) // go to the last node
	{
		astats.survS[temp->survey.ageF-1][temp->survey.smokeF-1]++;
		astats.survE[temp->survey.ageF-1][temp->survey.exerciseF-1]++;
		astats.survD[temp->survey.ageF-1][temp->survey.drinkF-1]++;
		temp = temp->next;
	}
	for (i = 0; i < 5; i++) {
		for (z = 0; z < 3; z++) {
			total[z] = 0;
		}
		for (j = 0; j < 4; j++) {
			total[0] += astats.survS[i][j];
			total[1] += astats.survE[i][j];
			total[2] += astats.survD[i][j];
		}
			if (total[0] != 0) {
				for (j = 0; j < 4; j++) {
					astats.survSP[i][j] = (float)(100 * astats.survS[i][j]) / total[0];
				}
			}
			if (total[0] != 0) {
				for (j = 0; j < 4; j++) {
					astats.survEP[i][j] = (float)(100 * astats.survE[i][j]) / total[0];
				}
			}
			if (total[0] != 0) {
				for (j = 0; j < 4; j++) {
					astats.survDP[i][j] = (float)(100 * astats.survD[i][j]) / total[0];
				}
			}
	}
	if (toFile == 0) {
		printf("Exercise Statistics\n");
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
		printf("%-10s %-10s %-10s %-10s %-10s \n", "Age", getExerciseBracket(1), getExerciseBracket(2), getExerciseBracket(3), getExerciseBracket(4));
		for (i = 0; i < 5;i++) {
			printf("%-10s %-10.2f %-10.2f %-10.2f %-10.2f \n", getAgeBracket(i+1), astats.survEP[i][0], astats.survEP[i][1], astats.survEP[i][2], astats.survEP[i][3]);
		}
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
		printf("Drinking Statistics\n");
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
		printf("%-10s %-10s %-10s %-10s %-10s \n", "Age", getAlcoholBracket(1), getAlcoholBracket(2), getAlcoholBracket(3), getAlcoholBracket(4));
		for (i = 0; i < 5; i++) {
			printf("%-10s %-10.2f %-10.2f %-10.2f %-10.2f \n", getAgeBracket(i + 1), astats.survDP[i][0], astats.survDP[i][1], astats.survDP[i][2], astats.survDP[i][3]);
		}
		
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
		printf("Smoking Statistics\n");
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
		printf("%-10s %-10s %-10s %-10s %-10s \n", "Age", getCigarettesBracket(1), getCigarettesBracket(2), getCigarettesBracket(3), getCigarettesBracket(4));
		for (i = 0; i < 5; i++) {
			printf("%-10s %-10.2f %-10.2f %-10.2f %-10.2f \n", getAgeBracket(i + 1), astats.survSP[i][0], astats.survSP[i][1], astats.survSP[i][2], astats.survSP[i][3]);
		}
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
	}
	return astats;
}

income_statistics_t getStatsByIncome(struct list * header, int toFile)
{

	/* return struct with statistics based on income, arg toFile represents
	if it should print it to the screen or just return it for a file function*/

	/* Variable declaration */
	struct list *temp;
	int i, j, z;
	int stat = 0;
	int total[3] = { 0,0,0 };
	income_statistics_t istats;
	/* end of Variable declaration */

	for (i = 0; i < 7; i++) {
		for (j = 0; j < 4; j++) {
			istats.survS[i][j] = 0;
			istats.survE[i][j] = 0;
			istats.survD[i][j] = 0;
			istats.survSP[i][j] = 0;
			istats.survEP[i][j] = 0;
			istats.survDP[i][j] = 0;
		}
	}
	temp = header;

	while (temp != NULL) // go to the last node
	{
		istats.survS[temp->survey.incomeF - 1][temp->survey.smokeF - 1]++;
		istats.survE[temp->survey.incomeF - 1][temp->survey.exerciseF - 1]++;
		istats.survD[temp->survey.incomeF - 1][temp->survey.drinkF - 1]++;
		temp = temp->next;
	}
	for (i = 0; i < 7; i++) {
		for (z = 0; z < 3; z++) {
			total[z] = 0;
		}
		for (j = 0; j < 4; j++) {
			total[0] += istats.survS[i][j];
			total[1] += istats.survE[i][j];
			total[2] += istats.survD[i][j];
		}

		if (total[0] != 0) {
			for (j = 0; j < 4; j++) {
				istats.survSP[i][j] = (float)(100 * istats.survS[i][j]) / total[0];
			}
		}
		if (total[1] != 0) {
			for (j = 0; j < 4; j++) {
				istats.survEP[i][j] = (float)(100 * istats.survE[i][j]) / total[1];
			}
		}
		if (total[2] != 0) {
			for (j = 0; j < 4; j++) {
				istats.survDP[i][j] = (float)(100 * istats.survD[i][j]) / total[2];
			}
		}
	}
	if (toFile == 0) {
		printf("Exercise Statistics\n");
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
		printf("%-10s %-10s %-10s %-10s %-10s \n", "Income", getExerciseBracket(1), getExerciseBracket(2), getExerciseBracket(3), getExerciseBracket(4));
		for (i = 0; i < 7; i++) {
			printf("%-10s %-10.2f %-10.2f %-10.2f %-10.2f \n", getIncomeBracket(i + 1), istats.survEP[i][0], istats.survEP[i][1], istats.survEP[i][2], istats.survEP[i][3]);
		}
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
		printf("Drinking Statistics\n");
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
		printf("%-10s %-10s %-10s %-10s %-10s \n", "Income", getAlcoholBracket(1), getAlcoholBracket(2), getAlcoholBracket(3), getAlcoholBracket(4));
		for (i = 0; i < 7; i++) {
			printf("%-10s %-10.2f %-10.2f %-10.2f %-10.2f \n", getIncomeBracket(i + 1), istats.survDP[i][0], istats.survDP[i][1], istats.survDP[i][2], istats.survDP[i][3]);
		}
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
		printf("Smoking Statistics\n");
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
		printf("%-10s %-10s %-10s %-10s %-10s \n", "Income", getCigarettesBracket(1), getCigarettesBracket(2), getCigarettesBracket(3), getCigarettesBracket(4));
		for (i = 0; i < 7; i++) {
			printf("%-10s %-10.2f %-10.2f %-10.2f %-10.2f \n", getIncomeBracket(i + 1), istats.survSP[i][0], istats.survSP[i][1], istats.survSP[i][2], istats.survSP[i][3]);
		}
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
	}
	return istats;
}

#pragma region Imported Code From Labs (Delete Functions)

void deleteLastSurvey(struct list** header)
{

	/* this function is called if element to delete is in the last position of the list*/
	struct list *temp;
	struct list *newNode;
	struct list *old_temp;

	if (*header == NULL)
	{
		printf("Nothing to delete\n");
	}
	else {

		temp = (struct list*)malloc(sizeof(struct list));
		temp = *header;
		old_temp = (struct list*)malloc(sizeof(struct list));

		while (temp->next != NULL)/* Move pointer to last node*/
		{

			old_temp = temp;
			temp = temp->next;
		}

		/* Point second last node to NULL and free last element */
		old_temp->next = NULL;
		free(temp);

	}
}

void deleteElementByPPSN(struct list** header)
{
	/* checks ppsn gets its position and deletes the survey of calls the appropriate function based on its location*/
	char PPSN[10];
	int position;
	int i;
	struct list *temp;
	struct list *old_temp;



	if (*header == NULL)
	{
		/* if pointer is NULL list is empty */
		printf("Nothing to delete\n");
	}

	else
	{

		printf("Enter PPSN: ");
		scanf("%s", PPSN);
		rewind(stdin);
		position = checkPPSN(*header, PPSN);

		/* If position is the first element call deleteElementAtStart function */
		if ((position) >= 0) {
			if (position == 0) {
				deleteFirstSurvey(header);

			}
			else {
				temp = (struct list*)malloc(sizeof(struct list));
				temp = *header;
				old_temp = (struct list*)malloc(sizeof(struct list));

				if (((temp)+position)->next == NULL) {
					deleteLastSurvey(header);
				}
				else {
					for (i = 0; i < position; i++) {
						old_temp = temp;
						temp = temp->next;
					}
					/* Point previous node to next node and free the middle element */
					old_temp->next = temp->next;
					free(temp);

				}

			}
		}
		else {
			printf("\n Invalid index.\n");
		}
		printf("Deleting the element at %d\n", position + 1);
	}

}

void deleteFirstSurvey(struct list** head_ptr)
{
	/* this function is called whe the survey to delete is in the first position of the lis*/
	struct list *temp;
	struct list *newNode;

	if (*head_ptr == NULL)
	{
		printf("Nothing to delete\n");
	}

	else
	{


		temp = (struct list*)malloc(sizeof(struct list));
		temp = *head_ptr;
		*head_ptr = temp->next;
		/* Set head pointer pointing to second node and free first node */
		printf("Deleting the element first element\n");
		free(temp);

	}
}

#pragma endregion

#pragma region File Functions

int read_fromFile(struct list ** header)
{

	/*reads survey from a file*/
	FILE * fptr;
	struct list *temp;
	struct list *newNode;



	fptr = fopen("Surveys.txt", "r+");

	if (fptr == NULL) {
		printf("File doesn't exists or cannot be accessed. Survey will start from anew\n");
		return -1;
	}
	else {
		while (!feof(fptr)) {
			if (*header == NULL) {
				/*the first time reads the first item of the list*/
				newNode = (struct list*)malloc(sizeof(struct list));
				fscanf(fptr, "%s", newNode->survey.PPSN);
				fscanf(fptr, "%s", newNode->survey.firstName);
				fscanf(fptr, "%s", newNode->survey.lastName);
				fscanf(fptr, "%d", &newNode->survey.genderF);
				fscanf(fptr, "%s", newNode->survey.address);
				fscanf(fptr, "%s", newNode->survey.email);
				fscanf(fptr, "%d", &newNode->survey.ageF);
				fscanf(fptr, "%d", &newNode->survey.incomeF);
				fscanf(fptr, "%d", &newNode->survey.exerciseF);
				fscanf(fptr, "%d", &newNode->survey.drinkF);
				fscanf(fptr, "%d", &newNode->survey.smokeF);
				newNode->next = *header;
				*header = newNode; // transfer the address of newNode' to'head'
				temp = *header;
			}
			else {
				//after the first time it adds the read surveys to the end of teh list until reaches end of file
				while (temp->next != NULL) // go to the last node
				{
					temp = temp->next;
				}
				newNode = (struct list*)malloc(sizeof(struct list));
				fscanf(fptr, "%s", newNode->survey.PPSN);
				fscanf(fptr, "%s", newNode->survey.firstName);
				fscanf(fptr, "%s", newNode->survey.lastName);
				fscanf(fptr, "%d", &newNode->survey.genderF);
				fscanf(fptr, "%s", newNode->survey.address);
				fscanf(fptr, "%s", newNode->survey.email);
				fscanf(fptr, "%d", &newNode->survey.ageF);
				fscanf(fptr, "%d", &newNode->survey.incomeF);
				fscanf(fptr, "%d", &newNode->survey.exerciseF);
				fscanf(fptr, "%d", &newNode->survey.drinkF);
				fscanf(fptr, "%d", &newNode->survey.smokeF);
				// Set the node value to user intput 
				newNode->next = NULL;
				// point newNode to NULL 
				temp->next = newNode;

			}

		}
		fclose(fptr);
	}

}

int print_toFile(struct list * header)
{
	/*prints the survey values to a file formatted so it can be read back if needed */
	FILE * fptr;
	struct list *temp;

	temp = header;

	fptr = fopen("Surveys.txt", "w");

	if (fptr == NULL) {
		printf("File doesn't exists or cannot be accessed. Survey will start from anew\n");
		return -1;
	}
	else {

		while (temp != NULL) // go to the last node
		{
			fprintf(fptr, "\n%s %s %s %d %s %s %d %d %d %d %d", temp->survey.PPSN, temp->survey.firstName, temp->survey.lastName, temp->survey.genderF, temp->survey.address, temp->survey.email, temp->survey.ageF, temp->survey.incomeF, temp->survey.exerciseF, temp->survey.drinkF, temp->survey.smokeF);
			temp = temp->next;
		}
		fclose(fptr);
		return 1;
	}
}

int print_toStatsFile(struct list * header)
{

	/*print survey details and all statistics that can be extracted from them to a file*/
	FILE * fptr;
	struct list *temp;
	int i;
	gender_statistics_t gstats;
	income_statistics_t istats;
	age_statistics_t astats;

	temp = header;

	fptr = fopen("SurveysStatistics.txt", "w");

	if (fptr == NULL) {
		printf("File doesn't exists or cannot be accessed. Survey will start from anew\n");
		return -1;
	}
	else {
		fprintf(fptr, "--------------------------- Surveys List ---------------------------\n");

		fprintf(fptr, "%-10s %-10s %-10s %-10s %-10s %-20s %-10s %-10s %-10s %-10s %-10s \n", "PPSN", "Name", "Last Name", "Gender", "Address", "Email Address", "Age", "Income", "Exercise", "Drinking", "Smoking");
		fprintf(fptr, "-----------------------------------------------------------------------------------------------------------------------------\n");
		while (temp != NULL) // go to the last node
		{
			fprintf(fptr, "%-10s %-10s %-10s %-10s %-10s %-20s %-10s %-10s %-10s %-10s %-10s\n", (*(temp)).survey.PPSN, (*(temp)).survey.firstName, (*(temp)).survey.lastName, getGender((*(temp)).survey.genderF), (*(temp)).survey.address, (*(temp)).survey.email, getAgeBracket((*(temp)).survey.ageF), getIncomeBracket((*(temp)).survey.incomeF), getExerciseBracket((*(temp)).survey.exerciseF), getAlcoholBracket((*(temp)).survey.drinkF), getCigarettesBracket((*(temp)).survey.smokeF));
			temp = temp->next;
		}
		fprintf(fptr,"\n\n\n");
		
		//Stats By gender
		gstats = getStatsByGender(header,1);
		fprintf(fptr, "Statistics by Gender.\n");
		fprintf(fptr, "Exercise Statistics.\n");
		fprintf(fptr, "-----------------------------------------------------------------------------------------------------------------------------\n");
		fprintf(fptr, "%-10s %-10s %-10s %-10s %-10s \n", "Gender", getExerciseBracket(1), getExerciseBracket(2), getExerciseBracket(3), getExerciseBracket(4));
		fprintf(fptr, "%-10s %-10.2f %-10.2f %-10.2f %-10.2f \n", getGender(1), gstats.survEP[0][0], gstats.survEP[0][1], gstats.survEP[0][2], gstats.survEP[0][3]);
		fprintf(fptr, "%-10s %-10.2f %-10.2f %-10.2f %-10.2f \n", getGender(2), gstats.survEP[1][0], gstats.survEP[1][1], gstats.survEP[1][2], gstats.survEP[1][3]);
		fprintf(fptr, "-----------------------------------------------------------------------------------------------------------------------------\n");
		fprintf(fptr, "Drinking Statistics\n");
		fprintf(fptr, "-----------------------------------------------------------------------------------------------------------------------------\n");
		fprintf(fptr, "%-10s %-10s %-10s %-10s %-10s \n", "Gender", getAlcoholBracket(1), getAlcoholBracket(2), getAlcoholBracket(3), getAlcoholBracket(4));
		fprintf(fptr, "%-10s %-10.2f %-10.2f %-10.2f %-10.2f \n", getGender(1), gstats.survDP[0][0], gstats.survDP[0][1], gstats.survDP[0][2], gstats.survDP[0][3]);
		fprintf(fptr, "%-10s %-10.2f %-10.2f %-10.2f %-10.2f \n", getGender(2), gstats.survDP[1][0], gstats.survDP[1][1], gstats.survDP[1][2], gstats.survDP[1][3]);
		fprintf(fptr, "-----------------------------------------------------------------------------------------------------------------------------\n");
		fprintf(fptr, "Smoking Statistics\n");
		fprintf(fptr, "-----------------------------------------------------------------------------------------------------------------------------\n");
		fprintf(fptr, "%-10s %-10s %-10s %-10s %-10s \n", "Gender", getCigarettesBracket(1), getCigarettesBracket(2), getCigarettesBracket(3), getCigarettesBracket(4));
		fprintf(fptr, "%-10s %-10.2f %-10.2f %-10.2f %-10.2f \n", getGender(1), gstats.survSP[0][0], gstats.survSP[0][1], gstats.survSP[0][2], gstats.survSP[0][3]);
		fprintf(fptr, "%-10s %-10.2f %-10.2f %-10.2f %-10.2f \n", getGender(2), gstats.survSP[1][0], gstats.survSP[1][1], gstats.survSP[1][2], gstats.survSP[1][3]);
		fprintf(fptr, "-----------------------------------------------------------------------------------------------------------------------------\n");
		//Stats by Age
		astats = getStatsByAge(header,1);
		fprintf(fptr, "Statistics by Age.\n");
		fprintf(fptr, "Exercise Statistics\n");
		fprintf(fptr, "-----------------------------------------------------------------------------------------------------------------------------\n");
		fprintf(fptr, "%-10s %-10s %-10s %-10s %-10s \n", "Age", getExerciseBracket(1), getExerciseBracket(2), getExerciseBracket(3), getExerciseBracket(4));
		for (i = 0; i < 5; i++) {
			fprintf(fptr, "%-10s %-10.2f %-10.2f %-10.2f %-10.2f \n", getAgeBracket(i + 1), astats.survEP[i][0], astats.survEP[i][1], astats.survEP[i][2], astats.survEP[i][3]);
		}
		fprintf(fptr, "Drinking Statistics\n");
		fprintf(fptr, "-----------------------------------------------------------------------------------------------------------------------------\n");
		fprintf(fptr, "%-10s %-10s %-10s %-10s %-10s \n", "Age", getAlcoholBracket(1), getAlcoholBracket(2), getAlcoholBracket(3), getAlcoholBracket(4));
		for (i = 0; i < 5; i++) {
			fprintf(fptr, "%-10s %-10.2f %-10.2f %-10.2f %-10.2f \n", getAgeBracket(i + 1), astats.survDP[i][0], astats.survDP[i][1], astats.survDP[i][2], astats.survDP[i][3]);
		}
		fprintf(fptr, "-----------------------------------------------------------------------------------------------------------------------------\n");
		fprintf(fptr, "Smoking Statistics\n");
		fprintf(fptr, "-----------------------------------------------------------------------------------------------------------------------------\n");
		fprintf(fptr, "%-10s %-10s %-10s %-10s %-10s \n", "Age", getCigarettesBracket(1), getCigarettesBracket(2), getCigarettesBracket(3), getCigarettesBracket(4));
		for (i = 0; i < 5; i++) {
			fprintf(fptr, "%-10s %-10.2f %-10.2f %-10.2f %-10.2f \n", getAgeBracket(i + 1), astats.survSP[i][0], astats.survSP[i][1], astats.survSP[i][2], astats.survSP[i][3]);
		}
		fprintf(fptr, "-----------------------------------------------------------------------------------------------------------------------------\n");
		//Stats By Income
		istats = getStatsByIncome(header,1);
		fprintf(fptr, "Statistics by Income.\n");
		fprintf(fptr, "Exercise Statistics\n");
		fprintf(fptr, "-----------------------------------------------------------------------------------------------------------------------------\n");
		fprintf(fptr, "%-10s %-10s %-10s %-10s %-10s \n", "Income", getExerciseBracket(1), getExerciseBracket(2), getExerciseBracket(3), getExerciseBracket(4));
		for (i = 0; i < 7; i++) {
			fprintf(fptr, "%-10s %-10.2f %-10.2f %-10.2f %-10.2f \n", getIncomeBracket(i + 1), istats.survEP[i][0], istats.survEP[i][1], istats.survEP[i][2], istats.survEP[i][3]);
		}

		fprintf(fptr, "-----------------------------------------------------------------------------------------------------------------------------\n");
		fprintf(fptr, "Drinking Statistics\n");
		fprintf(fptr, "-----------------------------------------------------------------------------------------------------------------------------\n");
		fprintf(fptr, "%-10s %-10s %-10s %-10s %-10s \n", "Income", getAlcoholBracket(1), getAlcoholBracket(2), getAlcoholBracket(3), getAlcoholBracket(4));
		for (i = 0; i < 7; i++) {
			fprintf(fptr, "%-10s %-10.2f %-10.2f %-10.2f %-10.2f \n", getIncomeBracket(i + 1), istats.survDP[i][0], istats.survDP[i][1], istats.survDP[i][2], istats.survDP[i][3]);
		}
		fprintf(fptr, "-----------------------------------------------------------------------------------------------------------------------------\n");
		fprintf(fptr, "Smoking Statistics\n");
		fprintf(fptr, "-----------------------------------------------------------------------------------------------------------------------------\n");
		fprintf(fptr, "%-10s %-10s %-10s %-10s %-10s \n", "Income", getCigarettesBracket(1), getCigarettesBracket(2), getCigarettesBracket(3), getCigarettesBracket(4));
		for (i = 0; i < 7; i++) {
			fprintf(fptr, "%-10s %-10.2f %-10.2f %-10.2f %-10.2f \n", getIncomeBracket(i + 1), istats.survSP[i][0], istats.survSP[i][1], istats.survSP[i][2], istats.survSP[i][3]);
		}
		fprintf(fptr, "-----------------------------------------------------------------------------------------------------------------------------\n");
		fclose(fptr);
		system("cls");
		printf("Surveys and Statistics printed succesfully into SurveysStatistics.txt\nPress any key to continue...\n");
		return 1;
	}
	return -1;
	
}

#pragma endregion

#pragma endregion

#pragma region String Returning Functions for Choices
char * getIncomeBracket(int choice)
{
	/*returns string income*/
	switch (choice) {
		case 1:
			return "No Income";
			break;
		case 2:
			return "< €20,000";
			break;
		case 3:
			return "< €40,000";
			break;
		case 4:
			return "< €60,000";
			break;
		case 5:
			return "< €80,000";
			break;
		case 6:
			return "< €100,000";
			break;
		case 7:
			return "> €100,000";
			break;
	}
	return NULL;
}
char * getAgeBracket(int choice)
{
	/*returns string age*/
	switch (choice) {
	case 1:
		return "18-20 yrs";
		break;
	case 2:
		return "21-30 yrs";
		break;
	case 3:
		return "31-50 yrs";
		break;
	case 4:
		return "51-65 yrs";
		break;
	case 5:
		return "65+ yrs";
		break;
	}
	return NULL;
}
char * getExerciseBracket(int choice)
{
	/*returns string exercise*/
	switch (choice) {
	case 1:
		return "Never";
		break;
	case 2:
		return "< 3t/week";
		break;
	case 3:
		return "< 5t/week";
		break;
	case 4:
		return "> 5t/week";
		break;
	}
	return NULL;
}
char * getAlcoholBracket(int choice)
{
	/*returns string alcohol*/
	switch (choice) {
	case 1:
		return "None";
		break;
	case 2:
		return "< 2 units";
		break;
	case 3:
		return "< 4 units";
		break;
	case 4:
		return "> 4 units";
		break;
	}
	return NULL;
}
char * getCigarettesBracket(int choice)
{
	/*returns string cigarettes*/
	switch (choice) {
	case 1:
		return "None";
		break;
	case 2:
		return "< 20";
		break;
	case 3:
		return "< 40";
		break;
	case 4:
		return "> 40";
		break;
	}
	return NULL;
}
char * getGender(int choice)
{
	/*returns string gender*/
	switch (choice) {
	case 1:
		return "Male";
		break;
	case 2:
		return "Female";
		break;
	}
	return NULL;
}
#pragma endregion

#pragma region Password

/* Function adapted from internet code */
void passwordSurvey()
{
	/* Variable Declarations */
	char username[7];
	char password[7];
	char ch;
	char userValidation[7];
	char passwordValidation[7];
	int i;
	int trys;
	int flag = 0;
	/* End of variable Declarations */
	
	/* Pointer to file with users and passwords */
	FILE* fptr; 

	 /* Open up the file with the password */
	fptr = fopen("credentials.txt", "r");


	/* If file is not available */
	if (fptr == NULL)
	{
		printf("Credentials file does not exiat or cannot be accessed at the moment.\n");
		system("pause");
		exit(0);
	}
	else
	{
		for (trys = 0; trys < 3; trys++)
		{
			fptr = fopen("credentials.txt", "r");

			printf("Enter Username: ");
			gets(username);
			rewind(stdin);
			printf("Enter the password: ");

			for (i = 0; i < 6; i++)
			{
				ch = getch();
				password[i] = ch;
				ch = '*';
				printf("%c", ch);
			}

			password[i] = '\0';

			/* while not end of file */
			while (!feof(fptr))
			{
				fscanf(fptr, "%s%s%", userValidation, passwordValidation);
				if (strcmp(userValidation, username) == 0 && strcmp(passwordValidation, password) == 0) {
					trys = 3;
					flag = 1;
				} /* end if */

			} /* end while */

			if (flag == 0)
			{
				printf("\n Username\\password does not match. Please try again...\n");
				fclose(fptr);
			}

			fclose(fptr); /* fclose closes the file */
		}

		fclose(fptr);

		if (flag == 0)
		{
			printf("Too many attemps. Program will terminate.\n");
			system("pause");
			exit(0);
		}

	} /* end else */

	system("cls");
}

#pragma endregion

