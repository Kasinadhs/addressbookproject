#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"




void swapContacts(Contact *a, Contact *b)
{
    Contact temp = *a;
    *a = *b;
    *b = temp;
}

void listContacts(AddressBook *addressBook) 
{
    /* Define the logic for print the contacts */
    int i, j;
    if (addressBook -> contactCount == 0)
    {
        printf("Address Book is Empty!!!\n");
        return ;
    }

    for (i = 0; i < addressBook -> contactCount - 1; i++)
    {
        for (j = 0; j < addressBook -> contactCount - i - 1; j++)
        {
            if (strcasecmp(addressBook -> contacts[j].name, addressBook -> contacts[j + 1].name) > 0)
            {
                swapContacts(&addressBook -> contacts[j], &addressBook -> contacts[j + 1]);
            }
        }
    }
  
    for (i = 0; i < addressBook -> contactCount; i++)
    {
        printf("Contact %d :\n", i + 1);
        printf("Name: %s\n", addressBook -> contacts[i].name);
        printf("Phone: %s\n", addressBook -> contacts[i].phone);
        printf("Email: %s\n\n", addressBook -> contacts[i].email);
    }
    
}


void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);

    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); 
    exit(EXIT_SUCCESS); 
}


void createContact(AddressBook *addressBook)
{
    printf("\n******************************************************\n");
	printf("                Create Contact\n");
	printf("******************************************************\n");
    /* Define the logic to create a Contacts */
    if (addressBook -> contactCount >= MAX_CONTACTS)
    {
        printf("Address Book is FULL, Cannot add more contacts\n\n");
        return;
    }


printf("Enter contact name : ");
scanf(" %[^\n]", addressBook -> contacts[addressBook -> contactCount].name);

while(!validate_name(addressBook -> contacts[addressBook -> contactCount].name))
{
    printf("Enter contact name : ");
    scanf(" %[^\n]", addressBook -> contacts[addressBook -> contactCount].name);
}

    char number[15];
    printf("Enter phone number : ");
    scanf(" %[^\n]", number);

    while(!validate_phone(addressBook, number, 1))
    {
        printf("Enter phone number : ");
        scanf(" %[^\n]", number);
    }

    strcpy(addressBook -> contacts[addressBook -> contactCount].phone, number);

    char mail[20];
    printf("Enter email id : ");
    scanf(" %[^\n]", mail);    
    while(!validate_email(addressBook, mail, 1))
    {
        printf("Enter email id : ");
        scanf(" %[^\n]", mail);
    }
    strcpy(addressBook -> contacts[addressBook -> contactCount].email, mail);
    addressBook -> contactCount++;
    printf("New Contact Created!!!\n\n");

}

int validate_name(char *name)
{
    int i;
    if(strlen(name) < 2)
    {
        printf("Invalid Name!!! Minimum 2 characters required.\n\n");
        return 0;
    }
    for(i = 0; i < strlen(name); i++)
    {
         if((name[i] >= 'A' && name[i] <= 'Z') ||
           (name[i] >= 'a' && name[i] <= 'z') ||
           (name[i] >= '0' && name[i] <= '9') ||
           name[i] == ' ')
        {
            
        }
        else
        {
            printf("Invalid Name!!! Only alphabets, digits and spaces are allowed.\n\n");
            return 0;
        }
    }

    return 1;
}


int validate_phone(AddressBook *addressBook, char *number, int flag)
{

    int i = 0;
    if(strlen(number) != 10)
    {
        printf("Invalid phone number!! Enter Again...\n\n");
        return 0;
    }
    if (number[0] < '6' || number[0] > '9')
    {
        printf("Phone number must start with 6, 7, 8 or 9!!\n\n");
        return 0;
    }
    for(i = 0; i < 10; i++)
    {
        if (number[i] <'0' || number[i] > '9')
            {
                printf("Invalid phone number!! Enter Again...\n\n");
                return 0;
            }
    }
    if(flag == 1)
    {
        for (i = 0; i < addressBook -> contactCount; i++)
        {
            if (strcmp(addressBook -> contacts[i].phone, number) == 0)
            {
                printf("Phone number already exist in address book!!!\n\n");
                return 0;
            }    
        }
    }
    else
    {
        return 1;
    }
    return 1;
}
int validate_email(AddressBook *addressBook, char *mail, int flag)
{
    int i;
    int at_count = 0;
    int dot_count = 0;
    int com_count = 0;
    int at_i = -1;
    int dot_i = -1;

    for (i = 0; i < strlen(mail); i++) 
    {
        if (mail[i] >= 'A' && mail[i] <= 'Z') 
        {
            printf("Invalid Email ID!!! Capital letters are not allowed\n");
            return 0;
        }
    }
    
    for (i = 0; i < strlen(mail); i++)
{
    if (mail[i] == '-')
    {
        printf("Invalid Email ID!!! '-' is not allowed\n\n");
        return 0;
    }
}
    if (mail[0] == '.')
    {
        printf("Invalid Email ID!!! Email should not start with '.'\n\n");
        return 0;
    }
  
    for (i = 0; i < strlen(mail); i++) 
    {
        if (mail[i] == '@') 
        {
            at_count++;
            at_i = i;
        } 
        else if (mail[i] == '.') 
        {
            dot_count++;
            dot_i = i;
        }
    }

    if (at_count > 1) 
    {
        printf("Invalid Email ID!!! Multiple '@' not allowed\n\n");
        return 0;
    }

    int dot_after_at = 0;
    for (i = at_i + 1; i < strlen(mail); i++) 
    {
        if (mail[i] == '.') 
        {
            dot_after_at++;
        }
    }
    if (dot_after_at > 1) 
    {
        printf("Invalid Email ID!!! Multiple '.' after '@' not allowed\n\n");
        return 0;
    }

    if (strlen(mail) < 4 || strcmp(mail + strlen(mail) - 4, ".com") != 0) 
    {
        printf("Invalid Email ID!!! Email should end with .com\n\n");
        return 0;
    }

    for (i = 0; i < strlen(mail) - 4; i++) 
    {
        if (strncmp(mail + i, ".com", 4) == 0) 
        {
            com_count++;
        }
    }
    if (com_count > 0) 
    {
        printf("Invalid Email ID!!! '.com' should be at the end\n\n");
        return 0;
    }
    if (dot_i == at_i + 1) 
    {
            printf("Invalid Email ID!!! At least one character required before '.com'\n\n");
            return 0;
    }
    if (at_i == -1 || dot_i == -1 || dot_i < at_i || dot_i > strlen(mail) - 4) 
    {
        printf("Invalid Email ID!!! Enter Again..\n\n");
        return 0;
    }
    if (flag == 1) 
    {
        for (i = 0; i < addressBook->contactCount; i++) 
        {
            if (strcmp(addressBook->contacts[i].email, mail) == 0) 
            {
                printf("Email already exist in address book!!!\n\n");
                return 0;
            }
        }
    }
    return 1;
}
void searchContact(AddressBook *addressBook) 
{
    printf("\n******************************************************\n");
	printf("                Search Contact\n");
	printf("******************************************************\n");
    /* Define the logic for search */
    int choose, found = 0;
    char search[50];

    printf("What are you searching : \n");
    printf("1.Name\n");
    printf("2.Phone Number\n");
    printf("3.Email\n");
    scanf("%d", &choose);

    switch (choose)
    {
    case 1:
        printf("Enter contact name : ");
        scanf(" %[^\n]", search);
        int matched = 0;
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            char *space = strchr(addressBook -> contacts[i].name, ' ');
            if (space != NULL)
            {
                if (strncasecmp(addressBook-> contacts[i].name, search, strlen(search)) == 0)
                {
                    printf("\nContact found:\n");
                    printf("Name: %s\n", addressBook->contacts[i].name);
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    matched++;
                }    
            }
            else
            {
                if (strcasecmp(addressBook-> contacts[i].name, search) == 0)
                {
                    printf("\nContact found:\n");
                    printf("Name: %s\n", addressBook->contacts[i].name);
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    matched++;
                }
            }
        }

        if (matched == 0)
        {
            printf("Contact not Found!!!\n\n");
        }
        else
        {
            printf("%d contact(s) found with name '%s'\n", matched, search);
        }
        break;

    case 2:
        printf("Enter phone number : ");
        scanf(" %[^\n]", search);
        while(!validate_phone(addressBook, search, 2))
        {
            printf("Enter phone number : ");
            scanf(" %[^\n]", search);
        }
        
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone, search) == 0)
            {
                printf("Contact found:\n");
                printf("Name: %s\n", addressBook->contacts[i].name);
                printf("Phone: %s\n", addressBook->contacts[i].phone);
                printf("Email: %s\n", addressBook->contacts[i].email);
                found = 1;
            }
        }

        if (!found)
        {
            printf("Contact not Found!!!\n\n");
        }
        break;

    case 3:
        printf("Enter email ID : ");
        scanf(" %[^\n]", search);
        while(!validate_email(addressBook, search, 2))
        {
            printf("Enter email ID : ");
            scanf(" %[^\n]", search);
        }

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].email, search) == 0)
            {
                printf("Contact found:\n");
                printf("Name: %s\n", addressBook->contacts[i].name);
                printf("Phone: %s\n", addressBook->contacts[i].phone);
                printf("Email: %s\n", addressBook->contacts[i].email);
                found = 1;
            }
        }
        
        if (!found)
        {
            printf("Contact not Found!!!\n\n");
        }
        break;

    default:
        printf("Wrong Choice!!\n\n");
        break;
    }
}

void editContact(AddressBook *addressBook)
{
    printf("\n******************************************************\n");
	printf("                Edit Contact\n");
	printf("******************************************************\n");
    /* Define the logic for Editcontact */
    if (addressBook -> contactCount == 0)
    {
        printf("Address Book is empty!!!\n\n");
        return;
    }
    
    int s_choice, e_choice;
    int i, index;
    int found_i[MAX_CONTACTS];
    int f_count = 0;
    char edit[50];

    printf("Search By : \n");
    printf("1.Name\n");
    printf("2.Phone Number\n");
    printf("3.Email\n");
    scanf("%d", &s_choice);

    f_count = contact_search(addressBook, s_choice, found_i);

    if(f_count == 0)
    {
        printf("Contact not found!!!\n\n");
        return;
    }
    if(f_count > 1)
    {
        printf("Multiple contacts Found. Please select one :\n");
        for(i = 0; i < f_count; i++)
        {
            printf("%d. Name: %s, Phone: %s, Email: %s\n", i + 1, addressBook -> contacts[found_i[i]].name, addressBook -> contacts[found_i[i]].phone, addressBook -> contacts[found_i[i]].email);
        }
        int serial;
        printf("Enter serial number : ");
        scanf("%d", &serial);
        if(serial < 1 || serial > f_count)
        {
            printf("Invalid Serial Number!!!\n\n");
            return;
        }
        index = found_i[serial - 1];
    }

    else
    {
        index = found_i[0];
    }

    printf("What do you want to edit?\n");
    printf("1.Name\n");
    printf("2.Phone Number\n");
    printf("3.Email\n");
    scanf("%d", &e_choice);

    switch (e_choice)
    {
        case 1:
            printf("Enter new name : ");
            scanf(" %[^\n]", edit);
            strcpy(addressBook->contacts[index].name, edit);
            printf("Name updated successfully.\n\n");
            break;

        case 2:
            printf("Enter new phone number : ");
            scanf(" %[^\n]", edit);
            while(!validate_phone(addressBook, edit, 3))
            {
                printf("Enter new phone number : ");
                scanf(" %[^\n]", edit);
            }
            strcpy(addressBook->contacts[index].phone, edit);
            printf("Phone Number updated successfully.\n\n");
            break;
        
        case 3:
            printf("Enter new email ID : ");
            scanf(" %[^\n]", edit);
            while(!validate_email(addressBook, edit, 3))
            {
                printf("Enter new email ID : ");
                scanf(" %[^\n]", edit);
            }
            strcpy(addressBook->contacts[index].email, edit);
            printf("Email ID updated successfully.\n\n");
            break;    
        
        default:
            printf("Invalid Choice !!!\n\n");
            break;
    }
    
}

int contact_search(AddressBook *addressBook, int s_choice, int *found_i)
{
    int i, found = 0;
    char search[50];
    switch (s_choice) 
    {
        case 1:
            printf("Enter contact name : ");
            break;
        case 2:
            printf("Enter phone number : ");
            break;
        case 3:
            printf("Enter email : ");
            break;
    }
    scanf(" %[^\n]", search);
    for (i = 0; i < addressBook -> contactCount; i++)
    {
        switch (s_choice)
        {
            case 1:
                if (strcmp(addressBook->contacts[i].name, search) == 0) 
                {
                    printf("Contact found:\n");
                    printf("Name: %s\n", addressBook->contacts[i].name);
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    found_i[found++] = i;
                }
                break;
        
            case 2:
                if (strcmp(addressBook->contacts[i].phone, search) == 0) 
                {
                    printf("Contact found:\n");
                    printf("Name: %s\n", addressBook->contacts[i].name);
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    found_i[found++] = i;
                }
                break;

        case 3:
                if (strcmp(addressBook->contacts[i].email, search) == 0) 
                {
                    printf("Contact found:\n");
                    printf("Name: %s\n", addressBook->contacts[i].name);
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    found_i[found++] = i;
                }
                break;
        }
    }
    return found;   
}

void deleteContact(AddressBook *addressBook)
{
    printf("\n******************************************************\n");
	printf("                Delete Contact\n");
	printf("******************************************************\n");
    if (addressBook -> contactCount == 0)
    {
        printf("Address Book is empty!!!\n\n");
        return;
    }
    
    int s_choice;
    int i, index;
    int found_i[MAX_CONTACTS];
    int f_count = 0;

    printf("Search By : \n");
    printf("1.Name\n");
    printf("2.Phone Number\n");
    printf("3.Email\n");
    scanf("%d", &s_choice);

    f_count = contact_search(addressBook, s_choice, found_i);      
    
    if(f_count == 0)
    {
        printf("Contact not found!!!\n\n");
        return;
    }

    if(f_count > 1)
    {
        printf("Multiple contacts found. Please select one:\n");
        for(i = 0; i <f_count; i++)
        {
            printf("%d. Name: %s, Phone: %s, Email: %s\n", i + 1, addressBook -> contacts[found_i[i]].name, addressBook -> contacts[found_i[i]].phone, addressBook -> contacts[found_i[i]].email);
        }

        int serial;
        printf("Enter serial number : ");
        scanf("%d", &serial);

        if(serial < 1 || serial > f_count)
        {
            printf("Invalid serial number!!!\n\n");
            return;
        }

        char ch;
        printf("Are you sure you want to delete this contact (y/n) ?");
        scanf(" %c", &ch);

        index = found_i[serial - 1];
        if (ch == 'Y' || ch == 'y')
        {
            for (i = index; i < addressBook -> contactCount - 1; i++)
            {
                strcpy(addressBook -> contacts[i].name, addressBook -> contacts[i + 1].name);
                strcpy(addressBook -> contacts[i].phone, addressBook -> contacts[i + 1].phone);
                strcpy(addressBook -> contacts[i].email, addressBook -> contacts[i + 1].email);
            }

            addressBook -> contactCount--;
            printf("Contact Deleted Successfully.\n\n");
        }
        
        else
        {
            printf("Deletion Cancelled!!!\n\n");
        }

    }

    else
    {
        index = found_i[0];
        char ch;
        printf("Are you sure you want to delete this contact (y/n) ?");
        scanf(" %c", &ch);

        if (ch == 'Y' || ch == 'y')
        {
            for (i = index; i < addressBook -> contactCount - 1; i++)
            {
                strcpy(addressBook -> contacts[i].name, addressBook -> contacts[i + 1].name);
                strcpy(addressBook -> contacts[i].phone, addressBook -> contacts[i + 1].phone);
                strcpy(addressBook -> contacts[i].email, addressBook -> contacts[i + 1].email);
            }

            addressBook -> contactCount--;
            printf("Contact Deleted Successfully.\n\n");
        }
        
        else
        {
            printf("Deletion Cancelled!!!\n\n");
        }
    }
        
}