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


person* addAfter(person* head, const char* target, const char* name, const char* lastname, int years) {
	person* temp = findP(head, target);
	if (temp == NULL) {
		return NULL;
	}
	person* newP = addNew(name, lastname, years);
	newP->next = temp->next;
	temp->next = newP;
	return newP;
}

person* addInFront(person** head, const char* target, const char* name, const char* lastname, int years) {
	if (*head == NULL) {
		return NULL;
	}
	if (strcmp((*head)->lastname, target) == 0) {
		return addBegin(head, name, lastname, years);
	}
	person* prev = *head;
	while (prev->next != NULL && strcmp(prev->next->lastname, target) != 0) {
		prev = prev->next;
	}
	if (prev->next == NULL) {
		return NULL;
	}

	person* newP = addNew(name, lastname, years);
	newP->next = prev->next;
	prev->next = newP;
	return newP;
}


void swapData(person* a, person* b) {
	char temp[50];
	int years;

	strcpy(temp, a->name);
	strcpy(a->name, b->name);
	strcpy(b->name, temp);

	strcpy(temp, a->lastname);
	strcpy(a->lastname, b->lastname);
	strcpy(b->lastname, temp);

	years = a->years;
	a->years = b->years;
	b->years = years;

}


void sortP(person* head) {
	if (head == NULL) {
		return;
	}
	int swapped;
	do {
		swapped = 0;
		for (person* p = head; p->next != NULL; p = p->next) {
			if (strcmp(p->lastname, p->next->lastname) > 0) {
				swapData(p, p->next);
				swapped = 1;
			}
		}
	} while (swapped);
}

void writeToFile(person* head, const char* filename) {
	FILE* f = fopen(filename, "w");
	if (f == NULL) {
		printf("Greska pri otvaranju datoteke");
		return;
	}
	for (person* temp = head; temp != NULL; temp = temp->next) {
		fprintf(f, "%s, %s, %d", temp->name, temp->lastname, temp->years);

	}
	fclose(f);
}

void readFromFile(person** head, const char* filename) {
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteteke.");
		return;
	}
	char name[50], lastname[50];
	int years;

	while (fscanf(fp, "%s %s %d", name, lastname, &years) == 3) {
		addEnd(head, name, lastname, years);
	}
	fclose(fp);



}
int main(){
	person* head = NULL;
addBegin(&head, "Roko", "Travica", 2006);
addEnd(&head, "Luka", "Soldic", 2006);
addBegin(&head, "Leon", "Nola", 2006);
addAfter(head, "Travica", "Ivan", "Kovac", 2005);
addInFront(&head, "Soldic", "Marko", "Babic", 2007);
printP(head);

person* found = findP(head, "Soldic");
if (found != NULL) {
	printf("Pronadjeno: %s %s, %d\n", found->name, found->lastname, found->years);
}
else {
	printf("Osoba nije pronadjena.\n");
}

deleteP(&head, "Nola");
sortP(head);
printP(head);

writeToFile(head, "osobe.txt");
freeP(&head);

readFromFile(&head, "osobe.txt");
printP(head);

freeP(&head);
return 0;
}