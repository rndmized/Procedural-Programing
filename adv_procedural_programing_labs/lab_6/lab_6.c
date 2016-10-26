#include<stdio.h>
#include<stdlib.h>

struct listelement
{
    int value;
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
void search(struct listelement** head_ptr);
/* Searches an element in the array and prints its index (Starting at 1)*/
int displayLength(struct listelement* head_ptr);
/* Returns the length of the list */

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
   	 printf("Please Enter your choice: \n");
   	 printf(" 1: To add an element\n");
   	 printf(" 2: To add an element to the top of the list\n");
   	 printf(" 3: To display all the elements\n");
   	 printf(" 4: To delete an element\n");
   	 printf(" 5: To delete first element!\n");
   	 printf(" 6: To delete an element at a position\n");
   	 printf(" 7: To add an element at a position\n");
   	 printf(" 8: To search an element.\n");
   	 printf(" 9: To display the length of the list.\n");
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
   		 deleteElementAtStart(&top);
   	 else if (choice == 6)
   		 deleteElementAt(&top);
   	 else if (choice == 7)
   		 addElementAt(&top);
   	 else if (choice == 8)
   		 search(&top);
   	 else if (choice == 9)
   		 printf("The length of the list is: %d\n", displayLength(top));
    } while (choice != -1);

}

void addElement(struct listelement** head_ptr)
{

    struct listelement *temp;
    struct listelement *newNode;

    if (*head_ptr == NULL) {
   	 /* If the list is empty call  addElementAtStart function */
   	 addElementAtStart(head_ptr);

    }
    else {

   	 temp = *head_ptr;


   	 while (temp->next != NULL) // go to the last node
   	 {
   		 temp = temp->next;
   	 }

   	 newNode = (struct listelement*)malloc(sizeof(struct listelement));
   	 printf("\nEnter data for this node");
   	 scanf("%d", &newNode->value);
   	 /* Set the node value to user intput */
   	 newNode->next = NULL;
   	 /* point newNode to NULL */
   	 temp->next = newNode;
   	 /* point previous node->next in the list to newNode */
    }
}

void addElementAt(struct listelement** head_ptr)
{
    int position;
    int i;
    struct listelement *temp;
    struct listelement *newNode;
    struct listelement *old_temp;

    printf("Enter element position: ");
    scanf("%d", &position);

    if (*head_ptr == NULL) {

   	 addElementAtStart(head_ptr);
   	 /* If the list is empty call addElementAtStart function */
    }  else {

   	 temp = (struct listelement*)malloc(sizeof(struct listelement));
   	 temp = *head_ptr;
   	 old_temp = (struct listelement*)malloc(sizeof(struct listelement));

   	 /* If the first position call addElementAtStart function */
   	 if ((position - 1) == 0) {
   		 addElementAtStart(head_ptr);
   	 } else if ((position-1) < displayLength(*head_ptr)) {
   		 for (i = 0; i<position - 1; i++) {/* Move pointer to index position -1 and store pointers locations */
   			 old_temp = temp;
   			 temp = temp->next;
   		 }
   		 newNode = (struct listelement*)malloc(sizeof(struct listelement));
   		 printf("\nEnter data for this node: ");
   		 scanf("%d", &newNode->value);
   		 /* Set previous node->next pointing to newNode and newNode->next pointing to next node */
   		 newNode->next = old_temp->next;
   		 old_temp->next = newNode;
   	 } else if ((position-1) == displayLength(*head_ptr)) {
   		 /* if index is the last element call addElement function */
   		 addElement(head_ptr);
   	 } else {
   		 printf("\n Invalid index.\n");
   	 }
   	 
    }
}

void deleteElement(struct listelement** head_ptr)
{
    struct listelement *temp;
    struct listelement *newNode;
    struct listelement *old_temp;

    if (*head_ptr == NULL)
    {
   	 printf("Nothing to delete\n");
    } else {    

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

   	 printf("Deleting the element with %d\n", temp->value);
   	 free(temp);

    }
}

void deleteElementAt(struct listelement** head_ptr)
{

    int position;
    int i;
    struct listelement *temp;
    struct listelement *old_temp;

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
   	 if ((position-1) < displayLength(*head_ptr)) {
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
   	 } else if ((position-1) == displayLength(*head_ptr)) {
   		 /* If position is the first element call deleteElement function */
   		 deleteElement(head_ptr);
   	 } else {
   		 printf("\n Invalid index.\n");
   	 }
   	 printf("Deleting the element at %d\n", position);


    }
}

void deleteElementAtStart(struct listelement** head_ptr)
{
    struct listelement *temp;
    struct listelement *newNode;

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

   	 }
   	 else {
   		 found = 1;
   		 printf("Element found at Index: %d \n", counter+1);
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
