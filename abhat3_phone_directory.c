#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include<limits.h>
typedef struct
{
	char fName[20];
	char lName[20];
	char phone[15];
}Record;
	Record person[100000];
void create();
void search(char* fname, char* lname);
void delete(char* fname, char* lname, char* number);
void sort_contact(int first, int last);
void insert(char* fname, char* lname, char* phone_number);
int seperate(int first, int last);
//int size = 100;
int count;

int main(int argc, char*argv[])
{
	char fname[50], lname[20], number[15], details[70], *elements = NULL;
	int option, i;
	if (argc != 2)
	{
		printf("Invalid no of Arguments\n");
		exit(1);
	}
//	Record *person= malloc(sizeof(Record)* 100);
	create(argv[1]);

	while (1)
	{
 option=0;
		printf("\n1) sort_contact \n2) search \n3) delete \n4) insert \nEnter the Choice\n");
		scanf("%d", &option);
		switch (option)
		{
		case 1:
			sort_contact(0, count - 1);
			for (i = 0; i < count; i++)
				printf("%s %s, %s\n", person[i].fName, person[i].lName, person[i].phone);
			printf("\n");
			break;
		case 2:
			printf("Enter the Name -> ");
			scanf("%s %s", fname, lname);
			search(fname, lname);
			break;
		case 3: printf("Enter the Name -> ");
			scanf("%s", fname);
			fgets(details, sizeof(details), stdin);
			details[strlen(details) - 1] = '\0';
			for (i = 0; i < strlen(details); i++)
			if (details[i] == ',')
				details[i] = ' ';
			elements = strtok(details, " ");
			strcpy(lname, elements);
			elements = strtok(NULL, " ");
			if (elements != NULL)
			{
				strcpy(number, elements);
				elements = strtok(NULL, " ");
				delete(fname, lname, number);
			}
			else
			{
				elements = strtok(NULL, " ");
				delete(fname, lname, NULL);
			}
			break;
		case 4:
			printf("Enter the Name -> ");
			scanf("%s", fname);
			fgets(details, sizeof(details), stdin);
			details[strlen(details) - 1] = '\0';
			for (i = 0; i < strlen(details); i++)
			if (details[i] == ',')
				details[i] = ' ';
			elements = strtok(details, " ");
			strcpy(lname, elements);
			elements = strtok(NULL, " ");
			strcpy(number, elements);
			elements = strtok(NULL, " ");
			insert(fname, lname, number);
			break;
		default: printf("Invalid Entry... Please try again\n");
			break;
		}
	}
	return 0;
}

void create(char *text_file)
{
	FILE *fp;
	int i;
	char *elements = NULL;
	fp = fopen(text_file, "r");
	if (fp == NULL)
	{
		printf("Could not open file %s", text_file);
		exit(1);
	}
	char line[60], commaRemoved[60], extraSpaceRemoved[60];
	while (fgets(line, 60, fp) != NULL)
	{
		line[strlen(line) - 1] = '\0';
	/*	if (count == size)
		{
			person = realloc(person, 2 * sizeof(Record)*size);
			size = size * 2;
		}*/

		for (i = 0; i < strlen(line); i++)
		if (line[i] == ',')
			line[i] = ' ';
		elements = strtok(line, " ");
		strcpy(person[count].fName, elements);
		elements = strtok(NULL, " ");
		strcpy(person[count].lName, elements);
		elements = strtok(NULL, " ");
		strcpy(person[count].phone, elements);
		elements = strtok(NULL, " ");
		count++;
	}
	fclose(fp);
}


void search(char* fname, char* lname)
{
	int low = 0, high = count - 1, mid, found = 0;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (strcasecmp(person[mid].fName, fname) == 0 && strcasecmp(person[mid].lName, lname) == 0)
		{
			printf(" %s %s, %s\n", person[mid].fName, person[mid].lName, person[mid].phone);
			found = 1;
			break;
		}
		else if (strcasecmp(person[mid].fName, fname) > 0 || (strcasecmp(person[mid].fName, fname) == 0 && strcasecmp(person[mid].lName, lname) > 0))
			high = mid - 1;
		else if (strcasecmp(person[mid].fName, fname) < 0 || (strcasecmp(person[mid].fName, fname) == 0 && strcasecmp(person[mid].lName, lname) < 0))
			low = mid + 1;
	}
	if (found == 0)
		printf("Name not Found\n");
}



void delete(char* fname, char* lname, char* number)
{
	int i, j, found = 0;
	for (i = 0; i < count; i++)
	{
		if (strcasecmp(person[i].fName, fname) == 0 && strcasecmp(person[i].lName, lname) == 0)
		if ((number != NULL && strcasecmp(person[i].phone, number) == 0) || number == NULL)
		{
			for (j = i; j < count - 1; j++)
			{
				person[j] = person[j + 1];
			}
			count--;
			found = 1;
		}

	}
	if (found == 0)
		printf("Name not Found\n");
	else
	{
		for (i = 0; i < count; i++)
			printf(" %s %s, %s\n", person[i].fName, person[i].lName, person[i].phone);
	}
}




void insert(char* fname, char* lname, char* phone_number)
{
	int i, j;
	char insertname[60], comparename1[60];
	/*if (count == size)
	{
		person = realloc(person, 2 * sizeof(Record)*size);
		size = size * 2;
	}*/
	strcpy(insertname, fname);
	strcat(insertname, " ");
	strcat(insertname, lname);
	strcat(insertname, " ");
	strcat(insertname, phone_number);
	for (i = 0; i<count; i++)
	{
		strcpy(comparename1, person[i].fName);
		strcat(comparename1, " ");
		strcat(comparename1, person[i].lName);
		strcat(comparename1, " ");
		strcat(comparename1, person[i].phone);
		if (strcasecmp(comparename1, insertname)>0)
		{
			for (j = count - 1; j >= i; j--)
				person[j + 1] = person[j];


			strcpy(person[i].fName, fname);
			strcpy(person[i].lName, lname);
			strcpy(person[i].phone, phone_number);
			count++;
			break;
		}
	}
	for (i = 0; i < count; i++)
		printf(" %s %s, %s\n", person[i].fName, person[i].lName, person[i].phone);
	printf("\n");
}

void sort_contact(int first, int last)
{
	int p;
	if (first < last)
	{
		p = seperate(first, last);
		sort_contact(first, p);
		sort_contact(p + 1, last);
	}
}

int seperate(int first, int last)
{
	int randElement = rand() % (last - first);
	randElement = randElement + first;
	Record temp = person[randElement];
	person[randElement] = person[last];
	person[last] = temp;
	char compareName[70], compareName1[70];
	strcpy(compareName, temp.fName);
	strcat(compareName, " ");
	strcat(compareName, temp.lName);
	strcat(compareName, " ");
	strcat(compareName, temp.phone);
	int pivote = last;
	int i = first - 1, j = first;
	for (; j < last; j++)
	{
		strcpy(compareName1, person[j].fName);
		strcat(compareName1, " ");
		strcat(compareName1, person[j].lName);
		strcat(compareName1, " ");
		strcat(compareName1, person[j].phone);

		if (strcasecmp(compareName1, compareName) < 0)
		{
			i++;
			temp = person[i];
			person[i] = person[j];
			person[j] = temp;
		}
	}
	i++;
	temp = person[last];
	person[last] = person[i];
	person[i] = temp;
	return i;
}

