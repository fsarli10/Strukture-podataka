#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct _Student {
	char ime[50];
	char prezime[50];
	int bodovi;
}stud;

int main() {
	int brojac = 0;
	FILE* fp;
	fp = fopen("popis.txt", "r");
	if (!fp) {
		printf("Greska");
		return -1;
	}
	char buffer[50] = { 0 };
	while (!feof(fp))
	{
		if(fgets(buffer, sizeof(buffer), fp) != NULL)
		brojac++;
	}
	stud* studenti = NULL;
	studenti = (stud*)malloc(brojac * sizeof(stud));
	if (!studenti) {
		printf("Greska pri alokaciji memorije!");
		fclose(fp); 
		return -1;
	}

	rewind(fp);

	int i = 0;
	while (!feof(fp)) {
		fscanf(fp, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
		i++;
	}
	fclose(fp);

	int max_bodovi = studenti[0].bodovi;
	for (int j = 1; j < brojac; j++) {
		if (studenti[j].bodovi > max_bodovi) {
			max_bodovi = studenti[j].bodovi;
		}
	}

	for (int j = 0; j < brojac; j++) {
		float relativni_br_bodova = ((float)studenti[j].bodovi / max_bodovi) * 100;
		printf("Ime: %s | Prezime: %s | Bodovi: %d | Relativni bodovi: %.2f%%\n", 
			studenti[j].ime, studenti[j].prezime, studenti[j].bodovi, relativni_br_bodova);
	}

	free(studenti);

	return 0;
}
