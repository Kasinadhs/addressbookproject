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
    int i;
    int j;

    Contact temp;


    if (addressBook->contactCount == 0)
    {
        printf("\nNo contacts available.\n");
        return;
    }
    for (i = 0;
         i < addressBook->contactCount - 1;
         i++)
    {
        for (j = 0;
             j < addressBook->contactCount - 1 - i;
             j++)
        {
            int result = 0;


            if (sortCriteria == 1)
            {
                result = strcmp(
                    addressBook->contacts[j].name,
                    addressBook->contacts[j + 1].name
                );
             }

            else if (sortCriteria == 2)
            {
                result = strcmp(
                    addressBook->contacts[j].phone,
                    addressBook->contacts[j + 1].phone
                );
            }

            else if (sortCriteria == 3)
            {
                result = strcmp(
                    addressBook->contacts[j].email,
                    addressBook->contacts[j + 1].email
                );
            }
            if (result > 0)
            {
                temp = addressBook->contacts[j];

                addressBook->contacts[j] =
                    addressBook->contacts[j + 1];

                addressBook->contacts[j + 1] = temp;
            }
        }
    }

    printf("\n------------------------------------------------------------\n");

    printf("%-5s %-20s %-15s %-30s\n",
           "No.",
           "Name",
           "Phone",
           "Email");

    printf("------------------------------------------------------------\n");


    for (i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-5d %-20s %-15s %-30s\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }


    printf("------------------------------------------------------------\n");
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
    int choice;
    int i;
    int found = 0;

    char searchName[50];
    char searchPhone[20];
    char searchEmail[50];


    printf("\nSearch Contact By:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter choice: ");

    scanf("%d", &choice);

    switch (choice)
    {
        /* -------------------------------------------------
           SEARCH BY NAME
           ------------------------------------------------- */

        case 1:

            printf("Enter name: ");

            scanf(" %[^\n]", searchName);


            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(
                        addressBook->contacts[i].name,
                        searchName
                    ) == 0)
                {
                    printf("\nContact Found!\n");

                    printf("Name  : %s\n",
                           addressBook->contacts[i].name);

                    printf("Phone : %s\n",
                           addressBook->contacts[i].phone);

                    printf("Email : %s\n",
                           addressBook->contacts[i].email);

                    found = 1;

                    break;
                }
            }

            break;
        
        case 2:

            printf("Enter phone: ");

            scanf("%19s", searchPhone);


            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(
                        addressBook->contacts[i].phone,
                        searchPhone
                    ) == 0)
                {
                    printf("\nContact Found!\n");

                    printf("Name  : %s\n",
                           addressBook->contacts[i].name);

                    printf("Phone : %s\n",
                           addressBook->contacts[i].phone);

                    printf("Email : %s\n",
                           addressBook->contacts[i].email);
                           found = 1;

                    break;
                }
            }

            break;
        case 3:

            printf("Enter email: ");

            scanf("%49s", searchEmail);


            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(
                        addressBook->contacts[i].email,
                        searchEmail
                    ) == 0)
                {
                    printf("\nContact Found!\n");

                    printf("Name  : %s\n",
                           addressBook->contacts[i].name);

                    printf("Phone : %s\n",
                           addressBook->contacts[i].phone);

                    printf("Email : %s\n",
                           addressBook->contacts[i].email);

                    found = 1;

                    break;
                }
            }

            break;


        default:

            printf("Invalid search choice!\n");

            return;
    }
if (found == 0)
    {
        printf("\nContact not found!\n");
    }
}


void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int i;
    int found=0;
    int choice;
    char searchName[50];
    char newName[50];
    char newPhone[20];
    char newEmail[50];
    printf("\nEnter the name of contact to edit: ");

    scanf(" %[^\n]", searchName);

     for(i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].name,
                  searchName) == 0)
        {
            found = 1;

            break;
        }
    }


    if(found == 0)
    {
        printf("\nContact not found!\n");

        return;
    }
    printf("\nContact Found!\n");

    printf("1. Edit Name\n");
    printf("2. Edit Phone\n");
    printf("3. Edit Email\n");

    printf("Enter choice: ");

    scanf("%d", &choice);


    switch(choice)
    {
        case 1:

            while(1)
            {
                printf("Enter new name: ");

                scanf(" %[^\n]", newName);


                if(!validateName(newName))
                {
                    printf("Invalid name!\n");

                    continue;
                }

                strcpy(addressBook->contacts[i].name,
                       newName);

                break;
            }
            printf("\nName updated successfully!\n");

            break;
            case 2:

            while(1)
            {
                printf("Enter new phone: ");

                scanf("%19s", newPhone);


                if(!validatePhone(newPhone))
                {
                    printf("Invalid phone number!\n");

                    continue;
                }

                {
                    int j;
                    int duplicate = 0;
                    for(j = 0;
                        j < addressBook->contactCount;
                        j++)
                    {
                        if(j != i &&
                           strcmp(addressBook->contacts[j].phone,
                                  newPhone) == 0)
                        {
                            duplicate = 1;

                            break;
                        }
                    }


                    if(duplicate)
                    {
                        printf("Phone number already exists!\n");

                        continue;
                        }
                }


                strcpy(addressBook->contacts[i].phone,
                       newPhone);

                break;
            }

            printf("\nPhone updated successfully!\n");

            break;
            case 3:

            while(1)
            {
                printf("Enter new email: ");

                scanf("%49s", newEmail);


                if(!validateEmail(newEmail))
                {
                    printf("Invalid email!\n");

                    continue;
                }


            
                {
                    int j;
                    int duplicate = 0;
for(j = 0;
                        j < addressBook->contactCount;
                        j++)
                    {
                        if(j != i &&
                           strcmp(addressBook->contacts[j].email,
                                  newEmail) == 0)
                        {
                            duplicate = 1;

                            break;
                        }
                    }


                    if(duplicate)
                    {
                        printf("Email already exists!\n");

                        continue;
                    }
                }
                strcpy(addressBook->contacts[i].email,
                       newEmail);

                break;
            }

            printf("\nEmail updated successfully!\n");

            break;


        default:

            printf("\nInvalid edit choice!\n");

            break;
    }
}



void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
   
}
