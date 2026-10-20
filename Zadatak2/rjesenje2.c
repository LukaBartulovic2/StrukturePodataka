#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Person {
    char name[40];
    char lastName[40];
    int birthYear;
    struct Person *nextPerson;
} Person;

void addStart(Person**, const char*, const char*, int);
void printList(Person*);
void addEnd(Person**, const char*, const char*, int);
Person* findPerson(Person*, const char*);
void deletePerson(Person**, const char*);

int main() {
    Person *head = NULL;

    addStart(&head, "Ana", "Anic", 2004);
    addStart(&head, "Ivan", "Ivic", 2000);
    addStart(&head, "Stipe", "Stipic", 1999);
    printList(head);
    printf("\n\n");

    addEnd(&head, "Petra", "Petric", 1832);
    printList(head);

    Person *searchLastName = findPerson(head, "Stipic");
    if (searchLastName != NULL) {
        printf("\nPronadena osoba: %s %s %d\n",searchLastName->name, searchLastName->lastName, searchLastName->birthYear);
    } else {
        printf("\nnema");

    }

    deletePerson(&head, "Ivic");
    
    printf("\nLista nakon brisanja:\n");
    printList(head);

    Person *current = head;
    Person *temp = NULL;

    while (current != NULL) {
        temp = current;
        current = current->nextPerson;
        free(temp);
    }
    head = NULL;

    return 0;
}

void addStart(Person **head, const char *name, const char *lastName, int birthYear) {
    Person *newPerson = (Person*)malloc(sizeof(Person));
    if (newPerson == NULL) {
        printf("Greska, alokacija");
        return;
    }

    strcpy(newPerson->name, name);
    strcpy(newPerson->lastName, lastName);
    newPerson->birthYear = birthYear;

    newPerson->nextPerson = *head;
    *head = newPerson;
}

void printList(Person *head) {
    Person *current = head;

    if (current == NULL) {
        printf("prazna lista");
        return;
    }

    while (current != NULL) {
        printf("%s %s %d\n", current->name, current->lastName, current->birthYear);
        current = current->nextPerson;
    }
}

void addEnd(Person **head, const char *name, const char *lastName, int birthYear) {
    Person *newPerson = (Person*)malloc(sizeof(Person));
    if (newPerson == NULL) {
        printf("alokacija");
        return;
    }

    strcpy(newPerson->name, name);
    strcpy(newPerson->lastName, lastName);
    newPerson->birthYear = birthYear;
    newPerson->nextPerson = NULL;

    Person *current = *head;
    while (current->nextPerson != NULL) {
        current = current->nextPerson;
    }

    current->nextPerson = newPerson;
}

Person* findPerson(Person *head, const char *lastName) {
    Person *current = head;

    while (current != NULL) {
        if (strcmp(current->lastName, lastName) == 0) {
            return current;
        }
        current = current->nextPerson;
    }
    return NULL;
}

void deletePerson(Person **head, const char *lastName) {
    if (*head == NULL) {
        printf("lista je prazna\n");
        return;
    }

    Person *current = *head;
    Person *prev = NULL;

    while (current != NULL && strcmp(current->lastName, lastName) != 0) {
        prev = current;
        current = current->nextPerson;
    }

    if (current == NULL) {
        printf("nema osobe s tim prezimenom.\n", lastName);
        return;
    }

    if (prev == NULL) {
        *head = current->nextPerson;
    } 
    // SLUČAJ 2: Brišemo element iz sredine ili s kraja
    else {
        prev->nextPerson = current->nextPerson;
    }

    free(current);
    printf("%s je obrisan\n", lastName);
}