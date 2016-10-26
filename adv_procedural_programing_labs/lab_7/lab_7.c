#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char name[20];
    int age;
    char  student_id[10];
    float gpa;
    char email[30];
    char phoneNum[15];

} student_t;

struct listelement
{
    student_t student;
    struct listelement* next;
};



void addElement(struct listelement** head_ptr);
/* Adds an element at the end of the list */
void addElementAt(struct listelement** head_ptr);
/* At an element at a given index */
void deleteElement(struct listelement** head_ptr);
/* Delete last element in list */
void deleteElementAt(struct listelement** head_ptr);
/* Delete an element at a given position */
void deleteElementAtStart(struct listelement** head_ptr);
/* Delete first element of a list */
void addElementAtStart(struct listelement** head_ptr);
/* Adds an element at the start of the list */
void printElements(struct listelement* head_ptr);
/* Print contents of the list */
void printElements_toFile(struct listelement* head_ptr);
/* Print contents of the list into a file */
void search(struct listelement* head_ptr);
/* Searches an element in the array and prints its index (Starting at 1)*/
int displayLength(struct listelement* head_ptr);
/* Returns the length of the list */
int check_id(struct listelement* head_ptr, char student_id[10]);
/* Searches an element in the array and returns 0 if doesn't exist, and 1 if it does*/

void main()
{
    struct listelement* top;
    /* Header pointer */
    int choice;
    /* Menu option selected */
    top = NULL;
    /* Prints menu while choice is not -1 */
    do
    {
   	 printf("*******************************MENU********************************\n");
   	 printf("Please Enter your choice: \n");
   	 printf("-------------------------------------------------------------------\n");
   	 printf(" 1: To add a student\n");
   	 printf(" 2: To add a student to the top of the list\n");
   	 printf(" 3: To display all the students\n");
   	 printf(" 4: To delete a student\n");
   	 printf(" 5: To delete first student\n");
   	 printf(" 6: To delete a student at a position\n");
   	 printf(" 7: To add a student at a position\n");
   	 printf(" 8: To search a student.\n");
   	 printf(" 9: To display the length of the list.\n");
   	 printf(" 10: To print students into a file.\n");
   	 printf(" -1: To terminate\n");
   	 printf("*******************************************************************\n");
   	 printf("Select: ");
   	 scanf("%d", &choice);
   	 if (choice == 1)
   		 addElement(&top);
   	 else if (choice == 2)
   		 addElementAtStart(&top);
   	 else if (choice == 3)
   		 printElements(top);
   	 else if (choice == 4)
   		 deleteElement(&top);
   	 else if (choice == 5)
   		 deleteElementAtStart(&top);
   	 else if (choice == 6)
   		 deleteElementAt(&top);
   	 else if (choice == 7)
   		 addElementAt(&top);
   	 else if (choice == 8)
   		 search(top);
   	 else if (choice == 9)
   		 printf("The length of the list is: %d\n", displayLength(top));
   	 else if (choice == 10)
   		 printElements_toFile(top);
    } while (choice != -1);

}

void addElement(struct listelement** head_ptr)
{

    struct listelement *temp;
    struct listelement *newNode;
    char sid[10];

    if (*head_ptr == NULL) {
   	 /* If the list is empty call  addElementAtStart function */
   	 addElementAtStart(head_ptr);

    }
    else {

   	 printf("Enter student ID: ");
   	 scanf("%s", sid);
   	 /* Check if the student id is already in use */
   	 if (check_id(*head_ptr, sid) != 1) {
   		 temp = *head_ptr;
   		 while (temp->next != NULL) // go to the last node
   		 {
   			 temp = temp->next;
   		 }
   		 /* Ask user input */
   		 newNode = (struct listelement*)malloc(sizeof(struct listelement));
   		 strcpy((*(newNode)).student.student_id, sid);
   		 printf("Enter age for this student: ");
   		 scanf("%d", &(*(newNode)).student.age);
   		 printf("Enter name for this student: ");
   		 scanf("%s", (*(newNode)).student.name);
   		 printf("Enter gpa for this student: ");
   		 scanf("%f", &(*(newNode)).student.gpa);
   		 printf("Enter email for this student: ");
   		 scanf("%s", (*(newNode)).student.email);
   		 printf("Enter phone number for this student: ");
   		 scanf("%s", (*(newNode)).student.phoneNum);
   		 printf("\n");

   		 /* Set the node value to user intput */
   		 newNode->next = NULL;
   		 /* point newNode to NULL */
   		 temp->next = newNode;
   		 /* point previous node->next in the list to newNode */
   	 }

    }
}

void addElementAt(struct listelement** head_ptr)
{
    /* Variable declaration */
    int position;
    int i;
    char sid[10];
    struct listelement *temp;
    struct listelement *newNode;
    struct listelement *old_temp;
    /* End of variable declaration */

    printf("Enter element position: ");
    scanf("%d", &position);

    if (*head_ptr == NULL) {

   	 addElementAtStart(head_ptr);
   	 /* If the list is empty call addElementAtStart function */
    }
    else {

   	 temp = (struct listelement*)malloc(sizeof(struct listelement));
   	 temp = *head_ptr;
   	 old_temp = (struct listelement*)malloc(sizeof(struct listelement));

   	 /* If the first position call addElementAtStart function */
   	 if ((position - 1) == 0) {
   		 addElementAtStart(head_ptr);
   	 }
   	 else if ((position - 1) < displayLength(*head_ptr)) {
   		 printf("Enter student ID: ");
   		 scanf("%s", sid);
   		 /* Check if the student id is already in use */
   		 if (check_id(*head_ptr, sid) != 1) {
   			 for (i = 0; i < position - 1; i++) {/* Move pointer to index position -1 and store pointers locations */
   				 old_temp = temp;
   				 temp = temp->next;
   			 }
   			 /* ASk user intput */
   			 newNode = (struct listelement*)malloc(sizeof(struct listelement));
   			 strcpy((*(newNode)).student.student_id, sid);
   			 printf("Enter age for this student: ");
   			 scanf("%d", &(*(newNode)).student.age);
   			 printf("Enter name for this student: ");
   			 scanf("%s", (*(newNode)).student.name);
   			 printf("Enter gpa for this student: ");
   			 scanf("%f", &(*(newNode)).student.gpa);
   			 printf("Enter email for this student: ");
   			 scanf("%s", (*(newNode)).student.email);
   			 printf("Enter phone number for this student: ");
   			 scanf("%s", (*(newNode)).student.phoneNum);
   			 printf("\n");
   			 /* Set previous node->next pointing to newNode and newNode->next pointing to next node */
   			 newNode->next = old_temp->next;
   			 old_temp->next = newNode;
   		 }
   	 }
   	 else if ((position - 1) == displayLength(*head_ptr)) {
   		 /* if index is the last element call addElement function */
   		 addElement(head_ptr);
   	 }
   	 else {
   		 printf("\n Invalid index.\n");
   	 }

    }
}

void addElementAtStart(struct listelement** head_ptr)
{
    /* Variable declaration */
    struct listelement *newNode;
    char sid[10];
    /* end of Variable declaration */

    printf("Enter student ID: ");
    scanf("%s", sid);
    /* Check if the student id is already in use */
    if (check_id(*head_ptr, sid) != 1) {
   	 newNode = (struct listelement*)malloc(sizeof(struct listelement));
   	 /* Ask user input */
   	 strcpy((*(newNode)).student.student_id, sid);
   	 printf("Enter age for this student: ");
   	 scanf("%d", &(*(newNode)).student.age);
   	 printf("Enter name for this student: ");
   	 scanf("%s", (*(newNode)).student.name);
   	 printf("Enter gpa for this student: ");
   	 scanf("%f", &(*(newNode)).student.gpa);
   	 printf("Enter email for this student: ");
   	 scanf("%s", (*(newNode)).student.email);
   	 printf("Enter phone number for this student: ");
   	 scanf("%s", (*(newNode)).student.phoneNum);
   	 printf("\n");

   	 newNode->next = *head_ptr;

   	 *head_ptr = newNode; // transfer the address of newNode' to'head'
    }
}

void deleteElement(struct listelement** head_ptr)
{
    /* Variable declaration */
    struct listelement *temp;
    struct listelement *newNode;
    struct listelement *old_temp;
    /* end of Variable declaration */

    if (*head_ptr == NULL)
    {
   	 printf("Nothing to delete\n");
    }
    else if ((*head_ptr)->next == NULL) {
   	 *head_ptr = NULL;
    }
    else {

   	 temp = (struct listelement*)malloc(sizeof(struct listelement));
   	 temp = *head_ptr;
   	 old_temp = (struct listelement*)malloc(sizeof(struct listelement));


   	 while (temp->next != NULL)/* Move pointer to last node*/
   	 {

   		 old_temp = temp;
   		 temp = temp->next;
   	 }

   	 /* POint second last node to NULL and free last element */
   	 old_temp->next = NULL;
   	 free(temp);

    }
}

void deleteElementAt(struct listelement** head_ptr)
{
    /* Variable declaration */
    int position;
    int i;
    struct listelement *temp;
    struct listelement *old_temp;
    /* end of Variable declaration */

    printf("Enter element position: ");
    scanf("%d", &position);

    if (*head_ptr == NULL)
    {
   	 /* if pointer is NULL list is empty */
   	 printf("Nothing to delete\n");
    }

    else
    {
   	 /* If position is the first element call deleteElementAtStart function */
   	 if ((position - 1) < displayLength(*head_ptr)) {
   		 if (position == 1) {
   			 deleteElementAtStart(head_ptr);

   		 }
   		 else {
   			 temp = (struct listelement*)malloc(sizeof(struct listelement));
   			 temp = *head_ptr;
   			 old_temp = (struct listelement*)malloc(sizeof(struct listelement));
   			 for (i = 0; i < position - 1; i++) {
   				 old_temp = temp;
   				 temp = temp->next;
   			 }
   			 /* POint previous node to next node and free the middle element */
   			 old_temp->next = temp->next;
   			 free(temp);
   		 }
   	 }
   	 else if ((position - 1) == displayLength(*head_ptr)) {
   		 /* If position is the first element call deleteElement function */
   		 deleteElement(head_ptr);
   	 }
   	 else {
   		 printf("\n Invalid index.\n");
   	 }
   	 printf("Deleting the element at %d\n", position);


    }
}

void deleteElementAtStart(struct listelement** head_ptr)
{
    /* Variable declaration */
    struct listelement *temp;
    struct listelement *newNode;
    /* end of Variable declaration */

    if (*head_ptr == NULL)
    {
   	 printf("Nothing to delete\n");
    }

    else
    {


   	 temp = (struct listelement*)malloc(sizeof(struct listelement));
   	 temp = *head_ptr;
   	 *head_ptr = temp->next;
   	 /* Set head pointer pointing to second node and free first node */
   	 printf("Deleting the element first element\n");
   	 free(temp);

    }
}

void printElements(struct listelement* head_ptr)
{
    /* Variable declaration */
    struct listelement *temp;
    /* end of Variable declaration */

    temp = head_ptr;
    /* Print fields */
    printf("Student List\n");
    printf("%-10s %-15s  %-10s %-10s %-15s  %-15s\n", "SID", "Name", "Age", "GPA", "EMAIL", "PHONE#");


    while (temp != NULL) // go to the last node

    {

   	 ///Display the contents
   	 printf("%-10s %-15s  %-10d %-10.1f %-15s  %-15s\n", (*(temp)).student.student_id, (*(temp)).student.name, (*(temp)).student.age, (*(temp)).student.gpa, (*(temp)).student.email, (*(temp)).student.phoneNum);

   	 temp = temp->next;

    }

}

void printElements_toFile(struct listelement* head_ptr)
{
    /* Variable declaration */
    FILE * fptr;
    /* File Pointer */
    struct listelement *temp;
    /* struct pointer */
    /* end of Variable declaration */

    temp = head_ptr;
    /* Assign temp the value of head pinter */

    fptr = fopen("students.txt", "w");
    /* Open file in writting mode  */

    //Check if file exists or has been created
    if (fptr == NULL) {
   	 printf("File cannot be found or created. Please make sure there is spaice available and you have the necessary privileges.");

    }
    else {
   	 //Print fields
   	 fprintf(fptr, "Student List\n");
   	 fprintf(fptr, "%-10s %-15s  %-10s %-10s %-15s  %-15s\n", "SID", "Name", "Age", "GPA", "EMAIL", "PHONE#");

   	 while (temp != NULL) // go to the last node

   	 {
   		 ///print the contents
   		 fprintf(fptr, "%-10s %-15s  %-10d %-10.1f %-15s  %-15s\n", (*(temp)).student.student_id, (*(temp)).student.name, (*(temp)).student.age, (*(temp)).student.gpa, (*(temp)).student.email, (*(temp)).student.phoneNum);

   		 temp = temp->next;

   	 }
   	 fclose(fptr);

    }



}

void search(struct listelement * head_ptr)
{
    /* Variable declaration */
    char sid[10];
    struct listelement *temp;
    int counter = 0, found = 0;
    /* end of Variable declaration */

    printf("Enter student ID value to search:");
    scanf("%s", sid);

    temp = (struct listelement*)malloc(sizeof(struct listelement));
    temp = head_ptr;

    while (temp != NULL) {/* Go to the last node */
   					   /* if finds the searched element prints its position, if not it keeps moving to the next element of the list */
   	 if (strcmp((*(temp)).student.student_id, sid) != 0) {
   		 /* increments counter */
   		 counter++;
   		 /* moves to the next element of the list */
   		 temp = temp->next;

   	 }
   	 else {
   		 found = 1;
   		 printf("Student found at Index: %d \n", counter + 1);
   		 break;
   	 }/*end else*/
    }/* end while*/
    if (found != 1) {
   	 printf("Student not found in the list.\n");
    }/* end if */

}

int displayLength(struct listelement* head_ptr) {

    /* Variable declaration */
    struct listelement *temp;
    int length = 0;
    /* end of Variable declaration */

    temp = head_ptr;

    while (temp != NULL) /* Go to the last node */

    {
   	 /* Increments length*/
   	 length++;
   	 /* Moves to the next element of the list */
   	 temp = temp->next;

    }/* end while */

    return length;

}

int check_id(struct listelement * head_ptr, char student_id[10])
{
    /* Variable declaration */
    struct listelement *temp;
    int counter = 0, found = 0;
    /* end of Variable declaration */

    temp = (struct listelement*)malloc(sizeof(struct listelement));
    temp = head_ptr;

    while (temp != NULL) {/* Go to the last node */
   					   /* if finds the searched element prints its position, if not it keeps moving to the next element of the list */
   	 if (strcmp((*(temp)).student.student_id, student_id) != 0) {
   		 /* increments counter */
   		 counter++;
   		 /* moves to the next element of the list */
   		 temp = temp->next;
   	 }
   	 else {
   		 found = 1;
   		 printf("Student ID already exists at Index: %d \n", counter + 1);
   		 /* If student id is found return 1 */
   		 return 1;
   		 break;
   	 }/*end else*/
    }/* end while*/
    if (found != 1) {
   	 /* If student id is not found return 0 */
   	 return 0;
    }/* end if */
    printf("Error.");
    return -1;
}
