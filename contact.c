#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include <ctype.h>


int validateName(char name[])
{
    int i;
    int length = strlen(name);
    int hasAlphaNumeric = 0;
    if (length < 2)
    {
        return 0;
    }
    for (i = 0; name[i] != '\0'; i++)
    {
        if (isalnum((unsigned char)name[i]))
        {
            hasAlphaNumeric = 1;
        }
         else if (name[i] == ' ')
        {
            
        }
        else{
            return 0;
        }

    }
    if (hasAlphaNumeric==0)
    {
        return 0;
    }
    return 1;
}

int validatePhone(char phone[])
{
    int i;
    if (strlen(phone)!=10)
    {
        return 0;

    }
    if(phone[0]<'6'||phone[0]>'9')
    {
        return 0;
    }
    for(i=0;phone[i]!='\0';i++)
    {
    if (!isdigit((unsigned char)phone[i]))
    
        {
            return 0;
        }
    }

    return 1;
}

int isDuplicatePhone(AddressBook *addressBook, char phone[])
{
    int i;

    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            return 1;
        }
    }

    return 0;
}

int validateEmail(char email[])
{
    int i;
    int length;
    int atPosition = -1;
    int atCount = 0;

    length = strlen(email);
    if (length < 6)
    {
        return 0;
    }
    if (email[0]=='@')
    {
        return 0;
    }
    for (i = 0; email[i] != '\0'; i++)
    {
        
        if (isupper((unsigned char)email[i]))
        {
            return 0;
        }

        
        if (email[i] == '@')
        {
            atCount++;
            atPosition = i;
        }

        
        if (email[i] == ' ')
        {
            return 0;
        }
    }
    if (atCount != 1)
    {
        return 0;
    }
    if (email[atPosition + 1] == '\0')
    {
        return 0;
    }
    for (i = atPosition + 1; email[i] != '\0'; i++)
    {
        if (email[i] == '.')
        {
            if (i == atPosition + 1)
            {
                return 0;
            }

            break;
        }
    }
    if (email[i] == '\0')
    {
        return 0;
    }


    if (length < 4)
    {
        return 0;
    }

    if (strcmp(&email[length - 4], ".com") != 0)
    {
        return 0;
    }

    return 1;
}

int isDuplicateEmail(AddressBook *addressBook, char email[])
{
    int i;

    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0)
        {
            return 1;
        }
    }

    return 0;
}


void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the choosen criteria
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    char name[50];
    char phone[20];
    char email[50];

    if (addressBook->contactCount>= MAX_CONTACTS)
    {
        printf("Address book is full \n");
        return;
    }
    while(1)
    {
        printf("Enter the name:");
        scanf(" %[^\n]",name);
        if(validateName(name))
        {
            break;
        }
        printf("Invalid name\n");
        printf("Name must contain minimum 2 characters.\n");
        printf("Only alphabets, digits and spaces are allowed.\n");
    }

    while (1)
    {
        printf("Enter phone: ");

        scanf("%19s", phone);


        

        if (!validatePhone(phone))
        {
            printf("Invalid phone number!\n");
            printf("Phone must contain exactly 10 digits.\n");
            printf("First digit must be between 6 and 9.\n");

            continue;
        }

        if (isDuplicatePhone(addressBook, phone))
        {
            printf("Phone number already exists!\n");
            printf("Please enter another phone number.\n");

            continue;
        }


        break;
    }
    while (1)
    {
        printf("Enter email: ");

        scanf("%49s", email);


        

        if (!validateEmail(email))
        {
            printf("Invalid email!\n");
            printf("Email must:\n");
            printf("- contain lowercase characters only\n");
            printf("- contain exactly one @\n");
            printf("- not start with @\n");
            printf("- have a character between @ and .\n");
            printf("- end with .com\n");

            continue;
        }
        if (isDuplicateEmail(addressBook, email))
        {
            printf("Email already exists!\n");
            printf("Please enter another email.\n");

            continue;
        }


        break;
    }
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
   
}
