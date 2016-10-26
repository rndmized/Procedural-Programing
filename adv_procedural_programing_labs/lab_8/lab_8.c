#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

/* Structure storing date values */
typedef struct {
    int day;
    int month;
    int year;
} date_t;


/* Structure storing book values */
typedef struct {

    long bookNo; /* ISDN */
    char author[25];/* Book Author */
    char bookTitle[30];/* Book Title */
    float price;/* Book price */
    date_t date;/* Book publishing date */

} libraryBooks_t;/* struct name */

/* Prototype definition */
/* Check if there is an empty space in the array and if so allows user to add a book in that slot */
void add_sort(libraryBooks_t *libraryBooks, int size);
/* Ask the user an ISDN and searches the array.
If ISDN is found prints book details else prints book not found. */
int display_book(libraryBooks_t *libraryBooks, int size);
/* Ask the user an ISDN and searches the array.
If ISDN is found prints details and allow user edit book details else prints book not found. */
void edit_book(libraryBooks_t *libraryBooks, int size);
/* Ask the user an ISDN and searches the array.
If ISDN is found prints details and delete book details else prints book not found. */
void delete_sort(libraryBooks_t *libraryBooks, int size);
/* If ISDN is found prints return book index else prints book not found (-1). */
int check_book(libraryBooks_t *libraryBooks, int size, long ISDNSearch);
void print_list(libraryBooks_t *libraryBooks, int size);

/* Main Method */
void main() {

    libraryBooks_t *libraryBooks; /* libraryBooks pointer */
    int numOfBooks, i = 0;/*Stores number of books in the array. Loop variable */
    int menuOption = 0;/* Stores menu option selected */

   					/* ASk user input number of books in the library*/
    printf("Please enter number of books in the database: ");
    scanf("%d", &numOfBooks);
    /* Allocates space in memory for as many books as numOfBooks */
    libraryBooks = (libraryBooks_t*)malloc(sizeof(libraryBooks_t)*numOfBooks);

    /* Sets values of all books to 0 */
    for (i = 0; i <numOfBooks; i++) {
   	 strcpy((*(libraryBooks + i)).bookTitle, "0");
   	 (*(libraryBooks + i)).bookNo = 0;
   	 (*(libraryBooks + i)).price = 0;
   	 strcpy((*(libraryBooks + i)).author, "Annonymous");
   	 (*(libraryBooks + i)).date.day = 0;
   	 (*(libraryBooks + i)).date.month = 0;
   	 (*(libraryBooks + i)).date.year = 0;
    }

    /*While user doesn't enters -1 run the menu */
    do {
   	 fflush(stdin); /* Flushes user input */
   	 printf("\nLibrary System Menu:\n");
   	 printf("1. Add book\n");
   	 printf("2. Display Book\n");
   	 printf("3. Edit Book\n");
   	 printf("4. Delete Book\n");
   	 printf("Enter -1 to Exit Program\n");
   	 printf("Select option: ");
   	 scanf("%d", &menuOption);

   	 if (menuOption == 1) {
   		 /* If selected Option = 1 call function add_sort book */
   		 add_sort(libraryBooks, numOfBooks);
   	 }
   	 else if (menuOption == 2) {
   		 /* If selected Option = 2 call function display book */
   		 display_book(libraryBooks, numOfBooks);
   	 }
   	 else if (menuOption == 3) {
   		 /* If selected Option = 3 call function edit book */
   		 edit_book(libraryBooks, numOfBooks);
   	 }
   	 else if (menuOption == 4) {
   		 /* If selected Option = 4 call function delete book */
   		 delete_sort(libraryBooks, numOfBooks);
   	 }
   	 else if (menuOption == 5) {
   		 /* If selected Option = 5 call function print list - does not appear on the menus - hidden option */
   		 print_list(libraryBooks, numOfBooks);
   	 }
    } while (menuOption != -1);/* end while loop*/

   							/* Program Finishes */
}/* end main */


int display_book(libraryBooks_t *libraryBooks, int size) {

    long ISDNSearch = 0;/* Stores the ISDN input*/
    int i = 0;/* Loop variable */
    int notFound = 1; /* Stores if found or not */

   				   /* Asks user to input a ISDN to search*/
    printf("Please, enter Book ISDN: ");
    scanf("%ld", &ISDNSearch);

    /* Loops through the array looking for that ISDN*/
    for (i = 0; i < size; i++) {
   	 if ((*(libraryBooks + i)).bookNo == ISDNSearch) {
   		 printf("Book ISDN: %ld \n", (*(libraryBooks + i)).bookNo);
   		 printf("Book Title: %s \n", (*(libraryBooks + i)).bookTitle);
   		 printf("Book Author: %s \n", (*(libraryBooks + i)).author);
   		 printf("Book price: %f \n", (*(libraryBooks + i)).price);
   		 printf("Book Publishing Date: %d/%d/%d ", (*(libraryBooks + i)).date.day, (*(libraryBooks + i)).date.month, (*(libraryBooks + i)).date.year);
   		 notFound = 0;
   		 return i;
   	 }/* End if */
    }/* End For*/
    if (notFound == 1) { /* In notFound remains 1, no book has been found */
   	 printf("Book ISDN not found.\n");
    }/* End if*/
    return -1;
}/*end display_book(libraryBooks_t *libraryBooks, int size)*/

void edit_book(libraryBooks_t *libraryBooks, int size) {

    int index;
    index = display_book(libraryBooks, size);

    if (index != -1) {
   	 printf("Enter Book ISDN: ");
   	 scanf("%ld", &(*(libraryBooks + index)).bookNo);
   	 fflush(stdin);
   	 printf("Enter Book Title: ");
   	 gets((*(libraryBooks + index)).bookTitle);
   	 printf("Enter Book Author: ");
   	 gets((*(libraryBooks + index)).author);
   	 printf("Enter Book price: ");
   	 scanf("%f", &(*(libraryBooks + index)).price);
   	 printf("Enter Book Publishing Date: (dd/mm/yyyy)");
   	 scanf("%d/%d/%d", &(*(libraryBooks)).date.day, &(*(libraryBooks)).date.month, &(*(libraryBooks)).date.year);
    }//end if//

}//end edit_book

void add_sort(libraryBooks_t *libraryBooks, int size) {

    int temp, i, index;
    long ISBN;
    int noneEmpty = 0; /* Store if there are empty book spaces*/
    libraryBooks_t newBook;

    for (i = 0; i < size; i++) { /* Loops through the array */
   	 if ((*(libraryBooks + i)).bookNo == 0) {/* The first "empty" book it founds...*/
   		 break;
   	 }/* end if*/
   	 noneEmpty++;/* Increments the variable in every iteration there isn't an empty book */
    }/*end for*/
    if (noneEmpty == size) { /* If all slots are filled */
   	 printf("The is no empty space to add a book\n");
    }
    else {
   	 printf("Enter Book ISDN: ");
   	 scanf("%ld", &ISBN);

   	 temp = check_book(libraryBooks, size, ISBN);
   	 if (temp == -1) {
   		 newBook.bookNo = ISBN;
   		 fflush(stdin);
   		 printf("Enter Book Title: ");
   		 scanf("%s", newBook.bookTitle);
   		 printf("Enter Book Author: ");
   		 scanf("%s", newBook.author);
   		 printf("Enter Book price: ");
   		 scanf("%f", &newBook.price);
   		 printf("Enter Book Publishing Date: (dd/mm/yyyy)");
   		 scanf("%d/%d/%d", &newBook.date.day, &newBook.date.month, &newBook.date.year);
   		 for (i = 0; i < size; ++i) {
   			 if (((*(libraryBooks + i)).bookNo == 0) || (newBook.bookNo < (*(libraryBooks + i)).bookNo)) {
   				 index = i;
   				 break;
   			 }
   		 }

   		 for (i = size - 1; i > index; i--) {
   			 libraryBooks[i] = libraryBooks[i - 1];
   		 }
   		 *(libraryBooks + index) = newBook;
   	 }
   	 else {

   		 printf("A Book with same ISBN already exists");
   	 }



    }/*end if*/
}

int check_book(libraryBooks_t *libraryBooks, int size, long ISDNSearch) {

    int i = 0;/* Loop variable */
    int notFound = 1; /* Stores if found or not */

    /* Loops through the array looking for that ISDN*/
    for (i = 0; i < size; i++) {
   	 if ((*(libraryBooks + i)).bookNo == ISDNSearch) {
   		 notFound = 0;
   		 return i;
   	 }/* End if */
    }/* End For*/
    if (notFound == 1) { /* In notFound remains 1, no book has been found */
    }/* End if*/
    return -1;
}/*end display_book(libraryBooks_t *libraryBooks, int size)*/

void delete_sort(libraryBooks_t *libraryBooks, int size) {
    int i = 0;
    int index;

    index = display_book(libraryBooks, size);

    for (i = index; i< size - 1; i++) {
   	 *(libraryBooks + i) = *((libraryBooks + i) + 1);
    }
    (*(libraryBooks + size)).bookNo = 0;
    (*(libraryBooks + size)).price = 0;
    strcpy((*(libraryBooks + size)).bookTitle, "0");
    strcpy((*(libraryBooks + size)).author, "0");
    (*(libraryBooks + size)).date.day = 0;
    (*(libraryBooks + size)).date.month = 0;
    (*(libraryBooks + size)).date.year = 0;
    printf("Book Deleted \n");
}

void print_list(libraryBooks_t *libraryBooks, int size) {
    int i;
    printf("Books in library\n");
    printf("%s  %20s %15s %11s %11s\n", "ISBN", "Title", "Author", "Price", "Date");
    for (i = 0; i<size; i++) {
   	 printf("%d  %20s %20s %8.2f %8d/%d/%d\n", (*(libraryBooks + i)).bookNo, (*(libraryBooks + i)).bookTitle, (*(libraryBooks + i)).author, (*(libraryBooks + i)).price, (*(libraryBooks + i)).date.day, (*(libraryBooks + i)).date.month, (*(libraryBooks + i)).date.year);
    }



}
