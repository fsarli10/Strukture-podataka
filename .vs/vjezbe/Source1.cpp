#define _CRT_SECURE_NO_WARNINGS
#define FILE_NOT_OPENED -1
#include <stdio.h>
#include <stdlib.h>

typedef struct _Person* Position;

typedef struct _Person {
	char name;
	char lastname;
	int year;
	Position next;

}Person;

int insertBegin(char* name, int  year) {
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));
	if (newPerson = NULL) {
		free(newPerson);
		return -1;
	}
	newPerson->god = year;
	strcpy(newPerson->ime, name);
	newPerson->next = NULL;
}

int insertAfter(Position p, Position newP)
{
	newP->next = p->next,
		p->next = newP;
}

int insertEnd(char* name, int year) {
	while (p->next != NULL) {
		p = p->next;
	}
	insertAfter(p, newPerson);
}



int ispis(){
	for (Position q = p->next; q != NULL; q = q->next)
		printf(".....");
}

Position findLName(char* lastName, Position p) {
	Position q = p->next;		// koristit uvik pomocni pokazivac tipa ode q a ne p za kretat se po listi
	for (q; q != NULL; q = q->next) {
		if (strcmp(q->lastname, lastName) == 0)
			return q;
	}
}

int deletePerson(char* lastN, position p) {
	Position prev = p;                    // prije brisanja mora se stvorit nova veza da se ne izgubi dio baze
	Position curr = prev->next;
	curr = findLname(lastN, prev);
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
	insertAfter(p, newPerson);
	


	return 0;
}