#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Person {
    char name[40];
    char lastName[40];
    int birthYear;
    struct Person *nextPerson;
} Person;

int addStart(Person**, const char*, const char*, int);
int printList(Person*);
int addEnd(Person**, const char*, const char*, int);
Person* findPerson(Person*, const char*);
int deletePerson(Person**, const char*);
int insertAfter(Person*, const char*, const char*, const char*, int);
int insertBefore(Person**, const char*, const char*, const char*, int);
int sortList(Person*);
int writeToFile(Person*, const char*);
int readFromFile(Person**, const char*);

int main() {
    Person *head = NULL;

    addStart(&head, "Ana", "Anic", 2004);
    addStart(&head, "Ivan", "Ivic", 2000);
    addEnd(&head, "Stipe", "Stipic", 1999);

    insertAfter(head, "Ivic", "Marko", "Markic", 1995);
    insertBefore(&head, "Ana", "Maja", "Majic", 2002);

    sortList(head);

    printList(head);
    printf("\n");

    writeToFile(head, "osobe.txt");

    Person *headFromFile = NULL;
    readFromFile(&headFromFile, "osobe.txt");

    Person *current = head;
    Person *temp = NULL;
    while (current != NULL) {
        temp = current;
        current = current->nextPerson;
        free(temp);
    }
    head = NULL;

    current = headFromFile;
    while (current != NULL) {
        temp = current;
        current = current->nextPerson;
        free(temp);
    }
    headFromFile = NULL;

    return 0;
}

int addStart(Person **head, const char *name, const char *lastName, int birthYear) {
    Person *newPerson = (Person*)malloc(sizeof(Person));
    if (newPerson == NULL) {
        return -1;
    }

    strcpy(newPerson->name, name);
    strcpy(newPerson->lastName, lastName);
    newPerson->birthYear = birthYear;

    newPerson->nextPerson = *head;
    *head = newPerson;
    return 0;
}

int printList(Person *head) {
    Person *current = head;

    if (current == NULL) {
        return -1;
    }

    while (current != NULL) {
        printf("%s %s %d\n", current->name, current->lastName, current->birthYear);
        current = current->nextPerson;
    }
    return 0;
}

int addEnd(Person **head, const char *name, const char *lastName, int birthYear) {
    Person *newPerson = (Person*)malloc(sizeof(Person));
    if (newPerson == NULL) {
        return -1;
    }

    strcpy(newPerson->name, name);
    strcpy(newPerson->lastName, lastName);
    newPerson->birthYear = birthYear;
    newPerson->nextPerson = NULL;

    if (*head == NULL) {
        *head = newPerson;
        return 0;
    }

    Person *current = *head;
    while (current->nextPerson != NULL) {
        current = current->nextPerson;
    }

    current->nextPerson = newPerson;
    return 0;
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

int deletePerson(Person **head, const char *lastName) {
    if (*head == NULL) {
        return -1;
    }

    Person *current = *head;
    Person *prev = NULL;

    while (current != NULL && strcmp(current->lastName, lastName) != 0) {
        prev = current;
        current = current->nextPerson;
    }

    if (current == NULL) {
        return -1;
    }

    if (prev == NULL) {
        *head = current->nextPerson;
    } else {
        prev->nextPerson = current->nextPerson;
    }

    free(current);
    return 0;
}

int insertAfter(Person *head, const char *targetLastName, const char *name, const char *lastName, int birthYear) {
    Person *current = head;

    while (current != NULL && strcmp(current->lastName, targetLastName) != 0) {
        current = current->nextPerson;
    }

    if (current == NULL) {
        return -1;
    }

    Person *newPerson = (Person*)malloc(sizeof(Person));
    if (newPerson == NULL) {
        return -1;
    }

    strcpy(newPerson->name, name);
    strcpy(newPerson->lastName, lastName);
    newPerson->birthYear = birthYear;

    newPerson->nextPerson = current->nextPerson;
    current->nextPerson = newPerson;

    return 0;
}

int insertBefore(Person **head, const char *targetLastName, const char *name, const char *lastName, int birthYear) {
    if (*head == NULL) {
        return -1;
    }

    if (strcmp((*head)->lastName, targetLastName) == 0) {
        return addStart(head, name, lastName, birthYear);
    }

    Person *current = *head;
    Person *prev = NULL;

    while (current != NULL && strcmp(current->lastName, targetLastName) != 0) {
        prev = current;
        current = current->nextPerson;
    }

    if (current == NULL) {
        return -1;
    }

    Person *newPerson = (Person*)malloc(sizeof(Person));
    if (newPerson == NULL) {
        return -1;
    }

    strcpy(newPerson->name, name);
    strcpy(newPerson->lastName, lastName);
    newPerson->birthYear = birthYear;

    newPerson->nextPerson = current;
    prev->nextPerson = newPerson;

    return 0;
}

int sortList(Person *head) {
    if (head == NULL) {
        return -1;
    }

    int swapped;
    Person *ptr1;
    Person *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->nextPerson != lptr) {
            if (strcmp(ptr1->lastName, ptr1->nextPerson->lastName) > 0) {
                char tempName[40];
                char tempLastName[40];
                int tempYear;

                strcpy(tempName, ptr1->name);
                strcpy(tempLastName, ptr1->lastName);
                tempYear = ptr1->birthYear;

                strcpy(ptr1->name, ptr1->nextPerson->name);
                strcpy(ptr1->lastName, ptr1->nextPerson->lastName);
                ptr1->birthYear = ptr1->nextPerson->birthYear;

                strcpy(ptr1->nextPerson->name, tempName);
                strcpy(ptr1->nextPerson->lastName, tempLastName);
                ptr1->nextPerson->birthYear = tempYear;

                swapped = 1;
            }
            ptr1 = ptr1->nextPerson;
        }
        lptr = ptr1;
    } while (swapped);

    return 0;
}

int writeToFile(Person *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return -1;
    }

    Person *current = head;
    while (current != NULL) {
        fprintf(file, "%s %s %d\n", current->name, current->lastName, current->birthYear);
        current = current->nextPerson;
    }

    fclose(file);
    return 0;
}

int readFromFile(Person **head, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    char name[40];
    char lastName[40];
    int birthYear;

    while (fscanf(file, "%39s %39s %d", name, lastName, &birthYear) == 3) {
        addEnd(head, name, lastName, birthYear);
    }

    fclose(file);
    return 0;
}