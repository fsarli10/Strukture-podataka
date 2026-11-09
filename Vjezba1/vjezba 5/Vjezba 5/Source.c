#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Stack {
	int broj;
	struct Stack* next;

}stack;


int push(stack* head, int num) {
	stack* n;

	n = (stack*)malloc(sizeof(stack));
	if (n == NULL) {
		printf("Greska pri alokaciji.\n");
		return -1;
	}

	n->broj = num;
	n->next = head->next;
	head->next = n;
	return 0;
}


int pop(stack* head, int* num) {
	stack* temp = head->next;

	if (temp == NULL)return -1;

	*num = temp->broj;
	head->next = temp->next;
	free(temp);
	return 0;
}

int izracunaj(stack* head, char op) {
	int a, b, rez;

	if (op != '+' && op != '-' && op != '*' && op != '/') {
		printf("Nepoznat znak %c.\n", op);
		return -1;
	}

	if (pop(head, &b) != 0 || pop(head, &a) != 0) {
		printf("Premalo brojeva na stogu.\n");
		return -1;
	}

	if (op == '+')
		rez = a + b;
	else if (op == '-')
		rez = a - b;
	else if (op == '*')
		rez = a * b;
	else {
		if (b == 0) {
			printf("Dijeljenje s nulom.\n");
			return -1;
		}
		rez = a / b;
	}

	return push(head, rez);
}

int racunaj(stack* head, const char* line, int* rezultat) {
	const char* p = line;
	int broj, used;
	char op;

	while (strlen(p) > 0) {
		if (sscanf(p, " %d %n", &broj, &used) == 1) {
			if (push(head, broj) != 0)
				return -1;
		}
		else if (sscanf(p, " %c %n", &op, &used) == 1) {
			if (izracunaj(head, op) != 0)
				return -1;
		}
		else
			break;

		p += used;
	}

	if (pop(head, rezultat) != 0) {
		printf("Izraz je prazan.\n");
		return -1;
	}
	if (head->next != NULL) {
		printf("Previse brojeva na stogu.\n");
		return -1;
	}
	return 0;
}

void Oslobodi(stack* head) {
	stack* temp;
	while (head->next != NULL) {
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
}


int main() {
	stack head = { .broj = 0, .next = NULL };
	char line[1024] = { 0 };
	int rezultat = 0;

	FILE* f = fopen("datoteka.txt", "r");
	if (f == NULL) {
		printf("Datoteka se ne moze otvoriti.");
		return 1;
	}

	fgets(line, sizeof(line), f);
	fclose(f);

	line[strcspn(line, "\n")] = '\0';
	printf("Postfiks izraz: %s\n", line);

	if (racunaj(&head, line, &rezultat) == 0)
		printf("Rezultat je: %d\n", rezultat);

	Oslobodi(&head);



	return 0;
}