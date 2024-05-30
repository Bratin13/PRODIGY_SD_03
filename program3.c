#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "contacts.txt"
#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 15
#define MAX_EMAIL_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char email[MAX_EMAIL_LENGTH];
} Contact;

void addContact();
void viewContacts();
void editContact();
void deleteContact();
void saveContacts(Contact contacts[], int count);
int loadContacts(Contact contacts[]);

int main() {
    int choice;
    while (1) {
        printf("\nContact Management System\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // to consume the newline character

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                viewContacts();
                break;
            case 3:
                editContact();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
    return 0;
}

void addContact() {
    Contact newContact;
    FILE *file = fopen(FILENAME, "a");
    if (!file) {
        printf("Could not open file for writing.\n");
        return;
    }

    printf("Enter name: ");
    fgets(newContact.name, MAX_NAME_LENGTH, stdin);
    strtok(newContact.name, "\n"); // remove newline character

    printf("Enter phone number: ");
    fgets(newContact.phone, MAX_PHONE_LENGTH, stdin);
    strtok(newContact.phone, "\n"); // remove newline character

    printf("Enter email: ");
    fgets(newContact.email, MAX_EMAIL_LENGTH, stdin);
    strtok(newContact.email, "\n"); // remove newline character

    fprintf(file, "%s,%s,%s\n", newContact.name, newContact.phone, newContact.email);
    fclose(file);

    printf("Contact added successfully.\n");
}

void viewContacts() {
    Contact contacts[100];
    int count = loadContacts(contacts);

    if (count == 0) {
        printf("No contacts found.\n");
        return;
    }

    printf("\nContact List:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. Name: %s, Phone: %s, Email: %s\n", i + 1, contacts[i].name, contacts[i].phone, contacts[i].email);
    }
}

void editContact() {
    Contact contacts[100];
    int count = loadContacts(contacts);
    if (count == 0) {
        printf("No contacts to edit.\n");
        return;
    }

    int index;
    viewContacts();
    printf("Enter the contact number to edit: ");
    scanf("%d", &index);
    getchar(); // to consume the newline character

    if (index < 1 || index > count) {
        printf("Invalid contact number.\n");
        return;
    }

    index--; // convert to zero-based index
    printf("Enter new name: ");
    fgets(contacts[index].name, MAX_NAME_LENGTH, stdin);
    strtok(contacts[index].name, "\n"); // remove newline character

    printf("Enter new phone number: ");
    fgets(contacts[index].phone, MAX_PHONE_LENGTH, stdin);
    strtok(contacts[index].phone, "\n"); // remove newline character

    printf("Enter new email: ");
    fgets(contacts[index].email, MAX_EMAIL_LENGTH, stdin);
    strtok(contacts[index].email, "\n"); // remove newline character

    saveContacts(contacts, count);
    printf("Contact updated successfully.\n");
}

void deleteContact() {
    Contact contacts[100];
    int count = loadContacts(contacts);
    if (count == 0) {
        printf("No contacts to delete.\n");
        return;
    }

    int index;
    viewContacts();
    printf("Enter the contact number to delete: ");
    scanf("%d", &index);
    getchar(); // to consume the newline character

    if (index < 1 || index > count) {
        printf("Invalid contact number.\n");
        return;
    }

    index--; // convert to zero-based index
    for (int i = index; i < count - 1; i++) {
        contacts[i] = contacts[i + 1];
    }

    saveContacts(contacts, count - 1);
    printf("Contact deleted successfully.\n");
}

void saveContacts(Contact contacts[], int count) {
    FILE *file = fopen(FILENAME, "w");
    if (!file) {
        printf("Could not open file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%s,%s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
    }
    fclose(file);
}

int loadContacts(Contact contacts[]) {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%[^,],%[^,],%[^\n]\n", contacts[count].name, contacts[count].phone, contacts[count].email) != EOF) {
        count++;
    }
    fclose(file);

    return count;
}
