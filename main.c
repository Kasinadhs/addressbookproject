#include <stdio.h>
#include "contact.h"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook);
    int sortChoice;
    int sortCriteria; // Initialize the address book

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                //listContacts(&addressBook,sortCriteria);
                //break;
                printf("\nSort contacts by:\n");

                printf("1. Name\n");
                printf("2. Phone\n");
                printf("3. Email\n");

                printf("Enter sorting choice: ");

                scanf("%d", &sortChoice);


                if (sortChoice < 1 || sortChoice > 3)
                {
                    printf("Invalid sorting choice!\n");
                }
                else
                {
                    listContacts(
                        &addressBook,
                        sortChoice
                    );
                }

                break;
            case 6:
                printf("Saving...\n");
                //saveContactsToFile(&addressBook);
                break;   
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
    
       return 0;
}
