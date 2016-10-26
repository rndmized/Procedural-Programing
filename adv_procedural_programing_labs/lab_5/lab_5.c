#include<stdio.h>
#include<stdlib.h>



struct listelement
{
    int value;
    struct listelement* next;
    /* structure listelement contains an integer value and a memory reference of the next element of the list */

};

/* Passing the head pointer as an argument to the function*/
void addElement(struct listelement** head_ptr);
/* Adds an inputted int to the end of the list */
void deleteElement(struct listelement** head_ptr);
/* Deletes an element from the end of the list */
void addElementAtStart(struct listelement** head_ptr);
/* Adds an element at the begining of the list */
void printElements(struct listelement* head_ptr);
/* Prints the content of the list */
void search(struct listelement** head_ptr);
/* Searches an element in the array and prints its index (Starting at 0)*/
int displayLength(struct listelement* head_ptr);
/* Returns the length of the list */

void main()
{
    struct listelement* top;
    /* top pointer will point at the head of the list */
    int choice;
    /* stores the input from user*/
    top = NULL;
    do
    {
   	 /* Prints menu */
   	 printf("Please Enter your choice: \n");
   	 printf(" 1: To add an element\n");
   	 printf(" 2: To add an element to the top of the list\n");
   	 printf(" 3: To display all the elements\n");
   	 printf(" 4: To delete an element\n");
   	 printf(" 5: To search an element.\n");
   	 printf(" 6: To display the length of the list.\n");
   	 printf(" -1: To terminate\n");
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
   		 search(&top);
   	 else if (choice == 6)
   		 printf("The length of the list is: %d\n",displayLength(top));
    } while (choice != -1);
    /* While the choice is not -1  it will repeat the menu */

}

void addElement(struct listelement** head_ptr)
{
    int data;
    struct listelement *temp;
    struct listelement *newNode;

    if (*head_ptr == NULL) {

   	 addElementAtStart(head_ptr);

    }
    else {

   	 temp = *head_ptr;


   	 while (temp->next != NULL) // go to the last node
   	 {
   		 temp = temp->next;
   	 }

   	 newNode = (struct listelement*)malloc(sizeof(struct listelement));
   	 printf("\nEnter data for this node: ");
   	 scanf("%d", &newNode->value);
   	 newNode->next = NULL;
   	 temp->next = newNode;
    }
}

void deleteElement(struct listelement** head_ptr)
{
    int data;
    struct listelement *temp;
    struct listelement *newNode;
    struct listelement *old_temp;

    if (*head_ptr == NULL)
    {
   	 printf("Nothing to delete\n");
    }

    else
    {

   	 temp = (struct listelement*)malloc(sizeof(struct listelement));
   	 temp = *head_ptr;
   	 old_temp = (struct listelement*)malloc(sizeof(struct listelement));

   	 while (temp->next != NULL)
   	 {

   		 old_temp = temp;
   		 temp = temp->next;
   	 }

   	 old_temp->next = NULL;

   	 printf("Deleting the element with %d\n", temp->value);
   	 free(temp);

    }
}

void addElementAtStart(struct listelement** head_ptr)
{

    struct listelement *newNode;

    newNode = (struct listelement*)malloc(sizeof(struct listelement));

    printf("\nEnter data for this node: ");

    scanf("%d", &newNode->value);

    newNode->next = *head_ptr;

    *head_ptr = newNode; // transfer the address of newNode' to'head'

}

void printElements(struct listelement* head_ptr)
{

    int data;

    struct listelement *temp;

    temp = head_ptr;

    while (temp != NULL) // go to the last node

    {

   	 ///Display the contents

   	 printf("Contents: %d\n ", temp->value);

   	 temp = temp->next;

    }

}

void search(struct listelement ** head_ptr)
{
    int data;
    struct listelement *temp;
    int counter = 0, found = 0;

    printf("Enter integer value to search:");
    scanf("%d", &data);

    temp = (struct listelement*)malloc(sizeof(struct listelement));
    temp = *head_ptr;

    while (temp != NULL) {/* Go to the last node */
   	 /* if finds the searched element prints its position, if not it keeps moving to the next element of the list */
   	 if (temp->value != data) {
   		 /* increments counter */
   		 counter++;
   		 /* moves to the next element of the list */
   		 temp = temp->next;
   	 
   	 } else {
   		 found = 1;
   		 printf("Element found at Index: %d \n", counter);
   		 break;
   	 }/*end else*/
    }/* end while*/
    if (found != 1) {
   	 printf("Element not found in the list.");
    }/* end if */

}

int displayLength(struct listelement* head_ptr) {


    struct listelement *temp;
    int length = 0;
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