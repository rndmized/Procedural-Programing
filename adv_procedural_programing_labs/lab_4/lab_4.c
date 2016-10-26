#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>


/* Structure storing book values */
typedef struct {

    long bookNo; /* ISDN */
    char bookTitle[30];/* Book Title */
    char author[25];/* Book Author */
    double price;/* Book price */

} libraryBooks_t;/* struct name */

/* Prototype definition */
/* Check if there is an empty space in the array and if so allows user to add a book in that slot */
void add_book(libraryBooks_t *libaryBooks, int size);
/* Ask the user an ISDN and searches the array.
If ISDN is found prints book details else prints book not found. */
void display_book(libraryBooks_t *libaryBooks, int size);

/* Main Method */
void main(){

    libraryBooks_t *libraryBooks; /* libraryBooks pointer */
    int numOfBooks, i = 0;/*Stores number of books in the array. Loop variable */
    int menuOption =0;/* Stores menu option selected */

    /* ASk user input number of books in the library*/
    printf("Please enter number of books in the database: ");
    scanf("%d", &numOfBooks);
    /* Allocates space in memory for as many books as numOfBooks */
    libraryBooks = (libraryBooks_t*)malloc(sizeof(libraryBooks_t)*numOfBooks);
    
    /* Sets values of all books to 0 */
    for (i = 0; i <numOfBooks; i++){
   	 (*(libraryBooks+i)).bookNo = 0;
   	 (*(libraryBooks+i)).price =0;
   	 strcpy((*(libraryBooks+i)).bookTitle,"0");
   	 strcpy((*(libraryBooks+i)).author, "0");
    }

    /*While user doesn't enters -1 run the menu */
    do {
   	 fflush(stdin); /* Flushes user input */
   	 printf("\nLibrary System Menu:\n");
   	 printf("1. Add book\n");
   	 printf("2. Display Book\n");
   	 printf("Enter -1 to Exit Program\n");
   	 printf("Select option: ");
   	 scanf("%d", &menuOption);

   	 if (menuOption == 1 ){
   		 /* If selected Option = 1 call function add book */
   		 add_book(libraryBooks, numOfBooks);
   	 } else if (menuOption == 2) {
   		 /* If selected Option = 2 call function add book */
   		 display_book(libraryBooks, numOfBooks);
   	 }
    } while (menuOption !=-1);/* end while loop*/

    /* Program Finishes */
}/* end main */

void add_book(libraryBooks_t *libaryBooks, int size){
    
    int i; /* Loop variable */
    int noneEmpty=0; /* Store if there are empty book spaces*/

    for (i = 0; i < size; i++){ /* Loops through the array */
   	 if ((*(libaryBooks+i)).bookNo == 0){/* The first "empty" book it founds...*/
   		 printf("Empty Book\n");
   		 printf("Enter Book ISDN: ");
   		 scanf("%ld", &(*(libaryBooks+i)).bookNo);
   		 fflush(stdin);
   		 printf("Enter Book Title: ");
   		 gets((*(libaryBooks+i)).bookTitle);
   		 printf("Enter Book Author: ");
   		 gets((*(libaryBooks+i)).author);
   		 printf("Enter Book price: ");
   		 scanf("%lf", &(*(libaryBooks+i)).price);
   		 break;
   	 }/* end if*/
   	 noneEmpty++;/* Increments the variable in every iteration there isn't an empty book */
    }/*end for*/
    if (noneEmpty == size){ /* If all slots are filled */
   	 printf("The is no empty space to add a book\n");
    }/*end if*/
}/* end add_book(libraryBooks_t *libaryBooks, int size) */

void display_book(libraryBooks_t *libaryBooks, int size){
    
    long ISDNSearch = 0;/* Stores the ISDN input*/
    int i = 0;/* Loop variable */
    int notFound = 1; /* Stores if found or not */

    /* Asks user to input a ISDN to search*/
    printf("Please, enter Book ISDN: ");
    scanf("%ld", &ISDNSearch);

    /* Loops through the array looking for that ISDN*/
   	 for (i = 0; i < size; i++){
   		 if ((*(libaryBooks+i)).bookNo == ISDNSearch){
   			 printf("Book ISDN: %ld \n", (*(libaryBooks+i)).bookNo);
   			 printf("Book Title: %s \n", (*(libaryBooks+i)).bookTitle);
   			 printf("Book Author: %s \n", (*(libaryBooks+i)).author);
   			 printf("Book price: %lf \n", (*(libaryBooks+i)).price);
   			 notFound=0;
   		 }/* End if */
   	 }/* End For*/
   	 if (notFound==1){ /* In notFound remains 1, no book has been found */
   		 printf("Book ISDN not found.\n");
   	 }/* End if*/
}/*end display_book(libraryBooks_t *libaryBooks, int size)*/
