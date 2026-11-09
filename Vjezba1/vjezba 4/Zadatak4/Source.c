#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct poli {
	int coef;
	int pow;
	struct poli* next;

}poli;


poli* insertSorted(poli* head, int coef, int pow) {
	poli* prev = NULL;;
	poli* temp = head;
	poli* n;


	if (coef == 0)return head;

	while (temp != NULL && temp->pow > pow) {
		prev = temp;
		temp = temp->next;
	}

	if (temp != NULL && temp->pow == pow) {
		temp->coef += coef;
		if (temp->coef == 0) {
			if (prev != NULL)
				prev->next = temp->next;

			else
				head = temp->next;
			free(temp);
		}
		return head;
	}

	n = (poli*)malloc(sizeof(poli));
	n->coef = coef;
	n->pow = pow;
	n->next = temp;


	if (prev == NULL) {
		head = n;
	}
	else
		prev->next = n;
	return head;
}


void print(poli* p) {
	if (p == NULL) {
		printf("0\n");
		return;
	}
	while (p != NULL) {
		printf("%dx na %d\n", p->coef, p->pow);
		p = p->next;
	}
	printf("\n");
}

poli* reader(const char* line) {
	poli* head = NULL;
	int c, e, used;
	const char* p = line;

	while (sscanf(p, "%d %d%n", &c, &e, &used) == 2) {
		head = insertSorted(head, c, e);
		p += used;
	}
	return head;
}

poli* zbroj(poli* a, poli* b) {
	poli* rez = NULL;
	while (a != NULL) {
		rez = insertSorted(rez, a->coef, a->pow);
		a = a->next;
	}
	while (b != NULL) {
		rez = insertSorted(rez, b->coef, b->pow);
		b = b->next;
	}
	return rez;
}

poli* mnozenje(poli* a, poli* b) {
	poli* umnozak = NULL;
	poli* q;
	while (a != NULL) {
		q = b;
		while (q != NULL) {
			umnozak = insertSorted(umnozak, a->coef*q->coef, a->pow+q->pow);
			q = q->next;
		}
		a = a->next;
	}
	return umnozak;
}

void Oslobodi(poli* p) {
	poli* temp;
	while (p != NULL) {
		temp = p;
		p = p->next;
		free(temp);
	}
}


int main() {
	char line1[1024], line2[1024];
	poli* p1, * p2;

	FILE* f = fopen("datoteka.txt", "r");
	if (f == NULL) {
		printf("Datoteka se ne moze otvoriti.");
		return 1;
	}

	fgets(line1, sizeof(line1), f);
	fgets(line2, sizeof(line2), f);
	fclose(f);

	p1 = reader(line1);
	p2 = reader(line2);

	printf("P1: \n");
	print(p1);
	printf("P2: \n");
	print(p2);

	poli* rezZbroj = zbroj(p1, p2);
	printf("Zbroj je :\n");
	print(rezZbroj);

	poli* rezMnoz = mnozenje(p1, p2);
	printf("Umnozak je :\n");
	print(rezMnoz);

	Oslobodi(p1);
	Oslobodi(p2);
	Oslobodi(rezZbroj);
	Oslobodi(rezMnoz);



	return 0;
}
	