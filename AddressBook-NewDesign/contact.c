#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    
    /*
    int i;
    printf("====================================================================================================\n");
    printf("%-10s|  %-20s|  %-15s|  %-30s|\n", "S.NO" , "Name" , "Phone" , "Email");

    printf("\n");

    for(i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-10d  %-20s  %-15s  %-30s\n",i+1 ,addressBook->contacts[i].name ,addressBook->contacts[i].phone ,addressBook->contacts[i].email);
        
    }
    printf("\n");
    printf("-----------------------------------------------------------------------------------------\n");
    */
    
    Contact temp;
    int i , j;
    for(i = 0; i < addressBook->contactCount-1; i++)
    {
        for(j = 0 ; j < addressBook->contactCount-1-i ; j++)
        {
            if(strcasecmp(addressBook->contacts[j].name , addressBook->contacts[j+1].name) > 0)
            {
                temp = addressBook->contacts[j] ;
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1]= temp;  
            }
        }
    }
    
    printf("\033[33m--------------------------------------------------------------------------------\033[0m\n");
    printf("\033[33m%-10s  %-20s  %-15s  %-30s\033\n[0m", "S.NO" , "Name" , "Phone" , "Email");

    printf("\033[33m--------------------------------------------------------------------------------\033[0m\n");

    for(i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-10d  %-20s  %-15s  %-30s\n", i+1 ,addressBook->contacts[i].name ,addressBook->contacts[i].phone ,addressBook->contacts[i].email);
        
    }
    printf("\033[33m--------------------------------------------------------------------------------\033[0m\n");
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook);   // Pass only variable name

    printf("\033[32mContacts saved successfully.\033[0m\n");
    printf("\033[32mExiting Address Book...\033[0m\n");

    exit(EXIT_SUCCESS);
}

int validate_name(AddressBook *addressBook, char *name)
{
    // Loop till name[i] != '\0'
    //     check the name[i] is not in the range 'a' to 'z' and 'A' to 'Z'
    //         return 0; invalid

    // return 1; valid
    int i = 0;
    while(name[i] != '\0')
    {
        if((name[i] >= 'a' ) && (name[i] <= 'z') || (name[i] >= 'A' ) && (name[i] <= 'Z') || name[i] == ' ' || name[i] == '.')
        {
            i++;
        }
        else
        {
            return 0; // invalid
        }
    }
    return 1; // valid    
}

int validate_phone( AddressBook *addressBook,char *str)
{
    
    //check the length
         // != 10  ==> return 0 (invalid)

    // Loop till str[i] != '\0'
    //     check the str[i] is not in the rage '0' to '9'
    //         return 0; invalid

    // check unique or not
    //     not => return 0;

    // return 1 // valid;
    int i = 0;
    if(strlen(str) != 10)
    {
        printf("\033[35mPhone number should contain exactly 10 digits.\033[0m\n");
        return 0; // invalid
    }
    for(i = 0; str[i] != '\0'; i++)
    {
        if(!(str[i] >= '0' && str[i] <= '9'))
        {
            printf("Phone number should contain only digits.\n");
            return 0; // invalid
        }
    }        

    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(str, addressBook->contacts[i].phone) == 0)
        {
            printf("Phone number already exists.\n");
            return 0; // invalid
        }
    }
    return 1; // valid
}

int validate_mail(AddressBook *addressBook,char *str)
{
    // check the length
         // > 30  ==> return 0 (invalid)

    // check the '@' and '.' is present or not
    //     not => return 0;

    // return 1; valid
    int i = 0;

    if(strlen(str) > 30)
    {
        return 0; // invalid
    }
    int at_count = 0;
    int dot_count = 0;
    for(int i = 0; str[i] != '\0'; i++)
    {
        if(str[i] == '@')
        {
            at_count++;
        }
        else if(str[i] == '.')
        {
            dot_count++;
        }
    }
    if(at_count != 1 || dot_count < 1)
    {
        printf("Invalid email format.\n");
        return 0; // invalid
    }

    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(str, addressBook->contacts[i].email) == 0)
        {
            printf("Email already exists.\n");
            return 0; // invalid
        }
    }
    return 1; // valid
}

void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */

    char name[20];
    int valid;
    while(1)
    {
        printf("Enter the name : ");
        scanf(" %[^\n]", name);

        valid = validate_name( addressBook,name);
        if(valid == 1)// valid
            break;
    }

    char mobile[11];
    while(1)
    {
        printf("Enter the phone : ");
        scanf(" %[^\n]", mobile);

        valid = validate_phone(addressBook, mobile);
        if(valid == 1)// valid
            break;
    }

    char mail[30];
    while(1)
    {
        printf("Enter the mail : ");
        scanf(" %[^\n]", mail);

        valid = validate_mail(addressBook, mail);
        if(valid == 1)// valid
            break;
    }

    strcpy(addressBook->contacts[addressBook->contactCount].name, name);

    strcpy(addressBook->contacts[addressBook->contactCount].phone, mobile);

    strcpy(addressBook->contacts[addressBook->contactCount].email, mail);

    addressBook->contactCount++;   
}

int search_by_name(AddressBook *addressBook)
{
    char str[20];
    printf("Enter the name: \n");
    scanf(" %[^\n]" , str);
    int i , count = 0, ind = -1;

    printf("\033[32m---------------------------------------------------------------------------------------\033[0m\n");
    printf("%-10s  %-20s  %-15s  %-30s\n", "S.NO" , "Name" , "Phone" , "Email");

    printf("\033[32m--------------------------------------------------------------------------------------\033[0m\n");
    for(i = 0; i < addressBook -> contactCount; i++)
    {
        if(strcmp(str ,addressBook->contacts[i].name) == 0 )
        {
            printf( "%-10d %-20s %-15s %-30s\n", i + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            ind = i;
            count ++;
        }
    }
    printf("\033[32m---------------------------------------------------------------------------------------\033[0m\n");
    if(count == 0)
    {
        printf("Contact No Match\n");
        return -1;
    }
    else if(count == 1)
    {
        return ind;
    }
    else
    {
        printf("Multiple contacts found. Search using phone number.\n");
        return search_by_name(addressBook);
    }
}

int search_by_phone(AddressBook *addressBook)
{
    char str[11];
    int i;

    printf("Enter the phone number: ");
    scanf(" %s",str);

    printf("\033[32m---------------------------------------------------------------------------------------\033[0m\n");
    printf("%-10s  %-20s  %-15s  %-30s\n", "S.NO" , "Name" , "Phone" , "Email");
    
    
    printf("\033[32m---------------------------------------------------------------------------------------\033[0m\n");

    for(i = 0; i < addressBook->contactCount;i++)
    {
        if(strcmp(str, addressBook->contacts[i].phone)==0)
        {
            printf("Contact Found:\n");
            printf( "%-10d %-20s %-15s %-30s\n",i+1 ,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            return i;
        }
    }
    printf("No contact found.");
    return -1;
    
    printf("\033[32m---------------------------------------------------------------------------------------\033[0m\n");
}

int search_by_mail(AddressBook *addressBook)
{
    char str[30];
    int i;

    printf("Enter the email: ");
    scanf(" %s",str);
    
    printf("\033[32m---------------------------------------------------------------------------------------\033[0m\n");
    printf("%-10s  %-20s  %-15s  %-30s\n", "S.NO" , "Name" , "Phone" , "Email");

    printf("\033[32m--------------------------------------------------------------------------------------\033[0m\n");

    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(str , addressBook->contacts[i].email)==0)
        {
            printf("Contact Found:\n");
            printf( "%-10d %-20s %-15s %-30s\n",i+1 ,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            return i;

        }
    }
    printf("No contact found.\n");
    return -1;
    printf("\033[32m----------------------------------------------------------------------------------------\033[0m\n");

}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int choice, res ;
    
    printf("Search Contact By: \n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);

    
    switch(choice)
    {
        case 1:
            res = search_by_name(addressBook);
            break;
        case 2:
            res = search_by_phone(addressBook);
            break;
        case 3:
            res = search_by_mail(addressBook);
            break;
        default:
            res = printf("Invalid input\n");
            return;            

    }
    if(res != -1)
    {
        printf("\nContact found successfully.\n");
    }
}

void edit_name(AddressBook *addressBook, int res)
{
    
    char name[20];
    int valid;
    
    while(1)
    {
        printf("Enter the name : ");
        scanf(" %[^\n]", name);

        valid = validate_name(addressBook , name);
        if(valid == 1)// valid
            break;
    }

    strcpy(addressBook->contacts[res].name, name);

}

void edit_phone(AddressBook *addressBook, int res)
{
    char phone[11];
    int valid;

    while(1)
    {
        printf("Enter new phone number: ");
        scanf(" %[^\n]", phone);

        valid = validate_phone(addressBook ,phone);

        if(valid == 1)
        {
            break;
        }
        printf("Invalid phone number\n");
    }
    strcpy(addressBook->contacts[res].phone,phone);
}

void edit_mail(AddressBook *addressBook, int res)
{
    char mail[30];
    int valid;

    while(1)
    {
        printf("Enter new email: ");
        scanf(" %[^\n]", mail);

        valid = validate_mail(addressBook , mail);

        if(valid == 1)
            break;

        printf("Invalid email\n");
    }

    strcpy(addressBook->contacts[res].email, mail);
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */

    int choice, res = -1;
    
    printf("Search Contact By: \n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1:
            res = search_by_name(addressBook);
            break;
        case 2:
            res = search_by_phone(addressBook);
            break;
        case 3:
            res = search_by_mail(addressBook);
            break;
        default:
            printf("Invalid input\n");
            return;            
    }
    if(res == -1)
    {
        printf("Contact not found\n");
        return;
    }
    printf("\nContact found\n");
    printf("Name  : %s\n", addressBook->contacts[res].name);
    printf("Phone : %s\n", addressBook->contacts[res].phone);
    printf("Email : %s\n", addressBook->contacts[res].email);

    printf("Select to edit: \n");
    printf("1. Name\n");
    printf("2. Phone number\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d" , &choice);

    switch(choice)
    {
        case 1:
            edit_name(addressBook , res);
            printf("Name updated succesfully\n");
            break;
        case 2:
            edit_phone(addressBook , res);
            printf("Phone number updated successfully\n");
            break;
        case 3:
            edit_mail(addressBook , res);
            printf("Email updated successfully\n");
            break;
        default:
            printf("Invalid input\n");
            return;            
    }
        
}   

void delete_name(AddressBook *addressBook , int res)
{
    
    int i ;
    for(i = res ; i < addressBook->contactCount -1 ; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
    
}

void delete_phone(AddressBook *addressBook , int res)
{

    int i ;
    for(i = res ; i < addressBook->contactCount -1 ; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
   
 
}

void delete_Email(AddressBook *addressBook , int res)
{
    


    int i ;
    for(i = res ; i < addressBook->contactCount -1 ; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
    
  
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int choice , res = -1;

    printf("Search Contact By: \n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1:
            res = search_by_name(addressBook);
            break;
        case 2:
            res = search_by_phone(addressBook);
            break;
        case 3:
            res = search_by_mail(addressBook);
            break;
        default:
            printf("Invalid input\n");
            return;            
    }
    if(res == -1)
    {
        printf("Contact not found");
        return;
    }
    printf("\nContact found\n");
    printf("Name  : %s\n", addressBook->contacts[res].name);
    printf("Phone : %s\n", addressBook->contacts[res].phone);
    printf("Email : %s\n", addressBook->contacts[res].email);

    printf("Select to delete: \n");
    printf("1. Name\n");
    printf("2. Phone number\n");
    printf("3. Email\n");
    printf("Enter your choice: ");

    scanf("%d" , &choice);

    switch(choice)
    {
        case 1:
            delete_name(addressBook , res);
            printf("Name deleted succesfully\n");
            break;
        case 2:
            delete_phone(addressBook , res);
            printf("Phone number deleted successfully\n");
            break;
        case 3:
            delete_Email(addressBook , res);
            printf("Email deleted successfully\n");
            break;
        default:
            printf("Invalid input\n");
            return;            
    }
   
}
