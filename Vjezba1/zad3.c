#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "tools/Assert.h"
#include "PersonList.h"

static Position CreatePerson(const char* name, const char* lastName, int birthYear);
static Position FindPrevious(Position head, const char* lastName);
static Position FindLast(Position first);
static int AddToList(Position position, Position newPerson);

int PrependList(Position head, const char* name, const char* lastName, int birthYear)
{
	Position newPerson = CreatePerson(name, lastName, birthYear);
	AddToList(head, newPerson);

	return SUCCESS;
}

int AppendList(Position head, const char* name, const char* lastName, int birthYear)
{
	Position last = NULL;
	Position newPerson = CreatePerson(name, lastName, birthYear);

	last = FindLast(head);

	AddToList(last, newPerson);

	return SUCCESS;
}

Position FindPersonByLastName(Position first, const char* lastName)
{
	Position temp = first;

	if (temp == NULL)
	{
		printf("Sorry person with last name: %s is not in the list. \n", lastName);
		return NULL;
	}

	for (temp = first; temp->next != NULL && strcmp(temp->lastName, lastName) != 0; temp = temp->next) {}

	if (strcmp(temp->lastName, lastName) == 0)
	{
		printf("Person with last name: %s is founded in the list. \n", lastName);
		return temp;
	}
	else
	{
		printf("Sorry person with last name: %s is not in the list. \n", lastName);
		return NULL;
	}

	return temp;
}

int RemovePerson(Position head, const char* lastName)
{
	Position temp = head;
	Position prev = FindPrevious(head, lastName);

	if (!prev)
	{
		printf("%s is not in the list \n", lastName);
		return FAILURE;
	}
	else
	{
		temp = prev->next;
		prev->next = temp->next;
		free(temp);

		printf("%s is removed from the list \n", lastName);

		return SUCCESS;
	}
}

int PrintList(Position first)
{
	Position temp = NULL;

	for (temp = first; temp != NULL; temp = temp->next)
	{
		printf("%s %s %d \n", temp->name, temp->lastName, temp->birthYear);
	}

	return SUCCESS;
}

int AddAfter(Position head, const char* search, const char* name, const char* lastName, int birthYear)
{
	Position oldPerson = FindPersonByLastName(head->next, search);
	Position newPerson = CreatePerson(name, lastName, birthYear);

	if (oldPerson)
	{
		AddToList(oldPerson, newPerson);
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}

int AddBefore(Position head, const char* search, const char* name, const char* lastName, int birthYear)
{
	Position oldPerson = FindPrevious(head, search);
	Position newPerson = CreatePerson(name, lastName, birthYear);

	if (oldPerson)
	{
		AddToList(oldPerson, newPerson);
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}

int SortList(Position head)
{
	Position i = head;
	Position j = i->next;

	Position last = NULL, temp = NULL;

	if (!j)
	{
		printf("No elements in the list\n");
		return FAILURE;
	}

	for (i = head; i->next != last; i = head, last = j)
	{
		for (i = head, j = i->next; j->next != last; i = j, j = j->next)
		{
			if (strcmp(j->lastName, j->next->lastName) > 0)
			{
				temp = j->next;
				i->next = temp;

				j->next = temp->next;
				temp->next = j;

				j = temp;
			}
		}
	}

	return SUCCESS;
}

int WriteToFile(const char* filePath, Position head)
{
	FILE* file = NULL;
	Position temp = head->next;

	if (!temp)
	{
		printf("No elements in the list\n");
		return FAILURE;
	}

	ASSERT(file = fopen(filePath, "w"));

	for (temp = head->next; temp != 0; temp = temp->next)
	{
		fprintf(file, "%s %s %d \n", temp->name, temp->lastName, temp->birthYear);
	}
	fclose(file);

	return SUCCESS;
}

int ReadFromFile(const char* filePath, Position head)
{
	FILE* file = NULL;
	Position temp = head->next;

	char buffer[1024] = { 0 };
	char name[20] = { 0 };
	char lastName[20] = { 0 };
	int birthYear = 0;
	int n = 0;

	file = fopen(filePath, "r");
	if (!file)
	{
		printf("Can not find or open file. \n");
		return FAILURE;
	}

	while (!feof(file))
	{
		fgets(buffer, 1024, file);
		n = sscanf(buffer, " %s %s %d", name, lastName, &birthYear);

		if (n == 3)
		{
			AppendList(head, name, lastName, birthYear);
		}
	}
	fclose(file);

	return SUCCESS;
}

int ClearList(Position head)
{
	Position temp = head;
	Position clear = NULL;

	if (!temp->next)
	{
		printf("List is already empty\n");
		return FAILURE;
	}

	for (temp = head; temp->next != NULL;)
	{
		clear = temp->next;
		temp->next = clear->next;

		free(clear);
	}

	return SUCCESS;
}

static Position CreatePerson(const char* name, const char* lastName, int birthYear)
{
	Position person = NULL;

	ASSERT(person = (Position)malloc(sizeof(Person)));

	strcpy(person->name, name);
	strcpy(person->lastName, lastName);
	person->birthYear = birthYear;
	person->next = NULL;

	return person;
}

static Position FindPrevious(Position head, const char* lastName)
{
	Position temp = head;

	if (temp->next == NULL)
	{
		return NULL;
	}

	for (temp = head; temp->next->next != NULL && strcmp(temp->next->lastName, lastName) != 0; temp = temp->next) {}

	if (strcmp(temp->next->lastName, lastName) != 0)
	{
		return NULL;
	}

	return temp;
}

static Position FindLast(Position head)
{
	Position temp = NULL;

	for (temp = head; temp->next != NULL; temp = temp->next) {}

	return temp;
}

static int AddToList(Position position, Position newPerson)
{
	newPerson->next = position->next;
	position->next = newPerson;

	return SUCCESS;
}