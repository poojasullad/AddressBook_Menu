#include <stdio.h>
#include "contact.h"

int main() 
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    //addressBook.contactCount = 0;


    do 
    {
        printf("\033[35m\nAddress Book Menu:\033[0m\n");
        printf("\033[33m1. Create contact\033[0m\n");
        printf("\033[33m2. Search contact\033[0m\n");
        printf("\033[33m3. Edit contact\033[0m\n");
        printf("\033[33m4. Delete contact\033[0m\n");
        printf("\033[33m5. List all contacts\033[0m\n");
    	printf("\033[33m6. Save and Exit\033[0m\n");		
        // printf("7. Exit\n");
        printf("\033[34mEnter your choice: \033[0m");
        scanf("%d", &choice);
        
        switch (choice) 
        {
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
                listContacts(&addressBook);
                break;
            case 6:
                printf("\033[32mSaving and Exiting...\033[0m\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
    return 0;
}
