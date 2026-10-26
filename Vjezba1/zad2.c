#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct person {
	char name[50];
	char lastname[50];
	int years;
	struct person* next;
}person;

person* addNew(const char* name, const char* lastname, int years) {
	person* newP = (person*)malloc(sizeof(person));
	if (newP == NULL) {
		printf("Greska pri alociranju");
		exit(1);
	}

	strcpy(newP->name, name);
	strcpy(newP->lastname, lastname);
	newP->years = years;
	newP->next = NULL;
	return newP;
}

person* addBegin(person** head, const char* name, const char* lastname, int years) {
	person* newP = addNew(name, lastname, years);
	newP->next = *head;
	*head = newP;
	return newP;
}

person* addEnd(person** head, const char* name, const char* lastname, int years) {
	person* newP = addNew(name, lastname, years);
	if (*head == NULL) {
		*head = newP;
		return newP;
	}
	person* temp = *head;
	while (temp->next != NULL) {
		temp = temp->next;

	}
	temp->next = newP;
	return newP;
}


person* findP(person* head, const char* lastname) {
	person* temp = head;
	while (temp != NULL) {
		if (strcmp(temp->lastname, lastname) == 0) {
			return temp;
		}temp = temp->next;
	}
	return NULL;
}

void deleteP(person** head, const char* lastname) {
	person* temp = *head;
	person* oldP = NULL;
	while (temp != NULL && strcmp(temp->lastname, lastname) != 0) {
		oldP = temp;
		temp = temp->next;
	}
	if (temp == NULL) {
		return;
	} if (oldP == NULL) {
		*head = temp->next;
	}
	else {
		oldP->next = temp->next;
	}
	free(temp);
}


void freeP(person** head) {
	person* temp = *head;
	while (temp != NULL) {
		person* nextP = temp->next;
		free(temp);
		temp = nextP;
	}
	*head = NULL;
}


void printP(person* head) {
	person* temp = head;
	printf("Sadrzaj tablice:\n");
	while (temp != NULL) {
		printf("Ime :%s, Prezime :%s, Godine :%d\n", temp->name, temp->lastname, temp->years);
		temp = temp->next;
	}
}




int main() {
	person* head = NULL;


	addBegin(&head, "Roko", "Travica", 2006);
	addEnd(&head, "Luka", "Soldic", 2006);
	addBegin(&head, "Leon", "Nola", 2006);
	printP(head);
	deleteP(&head, "Nola");

	printP(head);
	freeP(&head);

}