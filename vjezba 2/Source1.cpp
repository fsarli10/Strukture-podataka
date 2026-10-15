#define _CRT_SECURE_NO_WARNINGS
#define FILE_NOT_OPENED -1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Person* Position;

typedef struct _Person {
	char name[50];
	char lastname[50];
	int year;
	Position next;

}Person;

int insertBegin(Position p, char* name,char* lastname, int year) {
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));
	if (newPerson == NULL) {
		free(newPerson);
		return -1;
	}
	newPerson->year = year;
	strcpy(newPerson->name, name);
	strcpy(newPerson->lastname, lastname);
	insertAfter(p, newPerson);
	return 0;
}

int insertAfter(Position p, Position newP)
{
	newP->next = p->next,
		p->next = newP;
}

int insertEnd(Position p,char* name,char* lastname, int year) {
	Position newPerson = (Position)malloc(sizeof(Person));
	if (newPerson == NULL) {
		return -1;
	}
	newPerson->year = year;
	strcpy(newPerson->name, name);
	strcpy(newPerson->lastname, lastname);
	newPerson->next = NULL;
	while (p->next != NULL) {
		p = p->next;
	}
	insertAfter(p, newPerson);
	
	return 0;
}



int ispis(Position p){
		Position q = p->next;
	printf("\n--- POPIS OSOBA ---\n");
	if (q == NULL) {
		printf("lista je prazna\n");
	}
	while (q != NULL) {
		printf("ime: %s  prezime: %s  godina: %d\n", q->name, q->lastname, q->year);
		q = q->next;	
	}
	printf("-------------------\n");
	return 0;
}

Position findLName(char* lastName, Position p) {
	Position q = p->next;		// koristit uvik pomocni pokazivac tipa ode q a ne p za kretat se po listi
	for (q; q != NULL; q = q->next) {
		if (strcmp(q->lastname, lastName) == 0)
			return q;
	}
}

int deletePerson(char* lastN, Position p) {
	Position prev = p;                    // prije brisanja mora se stvorit nova veza da se ne izgubi dio baze
	Position curr = prev->next;
	curr = findLName(lastN, prev);
	while (prev->next != curr)
		prev = prev->next;
	prev->next = curr->next;
	free(curr);
}

int main() {
	Person Head = { .name = {0},
				   .lastname = {0},
				   .year = {0},
				   .next = NULL };

	Position p = &Head;
	insertBegin(p, "Ana", "Maric", 2006);
	insertEnd(p, "Roko", "Juric", 2007);
	
	ispis(p);

	return 0;
}