#include "command.h"


bool processCommand(Group *group)
{

	char line[MAX_LINE_LENGTH];
	char *firstWord;

	if (fgets(line, MAX_LINE_LENGTH, stdin) != NULL) {
		if (line[0] == 'q' && line[1] == 'u' && line[2] == 'i' && line[3] == 't') {
			printf("\n");
            fclose(stdin);
			freeGroup(group);
			exit(0);
		}

		firstWord = strtok(line, " ");

		//book, salesperson, sale, list books, list group, list salesperson, and quit.
		if (strcmp(firstWord, "book") == 0) {
			char *id = strtok(NULL, " ");
			char *name = strtok(NULL, "\n");
			if (id == NULL || name == NULL || strlen(id) > MAX_ID || strlen(name) > MAX_NAME) {
				printf("\n");
				printf("Invalid command\n");
				return false;
			}
			Book *b = createBook(id, name);
			for (int i = 0; i < group->bCount; i++) {
				if (strcmp(id, group->bList[i]->id) == 0) {
					printf("\n");
					printf("Invalid command\n");
					return false;
				}
			}
			group->bList[group->bCount] = b;
			group->bCount = group->bCount + 1;

			if (group->bCount == group->bCap) {
				group->bCap *= 2;
				group->bList = realloc(group->bList, (group->bCap) *sizeof(Book));
			}
		}
		else if (strcmp(firstWord, "salesperson") == 0) {
			char *id = strtok(NULL, " ");
			char *name = strtok(NULL, "\n");
			if (id == NULL || name == NULL || strlen(id) > MAX_ID || strlen(name) > MAX_NAME) {
				printf("\n");
				printf("Invalid command\n");
				return false;
			}
			Salesperson *s = createSalesperson(id, name);
			for (int i = 0; i < group->sCount; i++) {
				if (strcmp(id, group->sList[i]->id) == 0)
				{
					printf("\n");
					printf("Invalid command\n");
					return false;
				}
			}
			group->sList[group->sCount] = s;
			group->sCount = group->sCount + 1;

			if (group->sCount == group->sCap) {
				group->sCap *= 2;
				group->sList = realloc(group->sList, (group->sCap) *sizeof(Salesperson));
			}
		}
		else if (strcmp(firstWord, "sale") == 0) {
			char *sID = strtok(NULL, " ");
			char *bID = strtok(NULL, " ");
			int num = atoi(strtok(NULL, "\n"));
			if (num < 1) {
				printf("\n");
				printf("Invalid command\n");
				return false;
			}
			bool validBook = false;
			bool validSalesperson = false;
			for (int i = 0; i < group->sCount; i++) {
				if (strcmp(sID, group->sList[i]->id) == 0) {
					validSalesperson = true;
				}
			}
			for (int i = 0; i < group->bCount; i++) {
				if (strcmp(bID, group->bList[i]->id) == 0) {
					group->bList[i]->sold = group->bList[i]->sold + num;
					validBook = true;
				}
			}
			if (!validSalesperson || !validBook) {
				printf("\n");
				printf("Invalid command\n");
				return false;
			}

			for (int i = 0; i < group->sCount; i++) {
				if (strcmp(sID, group->sList[i]->id) == 0) {
				    group->sList[i]->sold = group->sList[i]->sold + num;
				    Book *c = getBook(group, bID);


				    if (contains(group->sList[i]->head, bID)) {
					    bool nodeFound = false;
					    BookNode *temp = group->sList[i]->head;
					    while (!nodeFound) {
						    if (strcmp(temp->book->id, c->id) == 0) {
							    temp->sold = temp->sold + num;
							    nodeFound = true;
						    }
						    else {
							    temp = temp->next;
						    }
					    }
				    }
				    else {


					    insert(&(group->sList[i]->head), c, num);

				    }
				}
			}
		}
		else if (strcmp(firstWord, "list") == 0) {
			char *secondWord = strtok(NULL, "\n");
			if (strcmp(secondWord, "books") == 0) {
				sortGroupBooks(group);
				printf("\n");
				printf("ID         Name                                Sold\n");

				if (group->bCount == 0) {
					printf("\n");
				}
				else {
					int total = 0;
					for (int i = 0; i < group->bCount; i++) {
						printf("%-10s ", group->bList[i]->id);
						printf("%-30s ", group->bList[i]->name);
						printf("%9d\n", group->bList[i]->sold);
						total = total + group->bList[i]->sold;
					}
					printf("%-10s ", "Total");
					printf("%-30s ", "");
					printf("%9d", total);
				}
			}
			else if (strcmp(secondWord, "group") == 0) {
				sortGroupSalespersons(group);
				printf("\n");
				printf("ID         Name                                Sold\n");
				if (group->sCount == 0) {
					printf("\n");
				}
				else {
					int total = 0;
					for (int i = 0; i < group->sCount; i++) {
						printf("%-10s ", group->sList[i]->id);
						printf("%-30s ", group->sList[i]->name);
						printf("%9d\n", group->sList[i]->sold);
						total = total + group->sList[i]->sold;
					}
					printf("%-10s ", "Total");
					printf("%-30s ", "");
					printf("%9d", total);
				}
			}
			else if (strcmp(strtok(secondWord, " "), "salesperson") == 0) {
				char *id = strtok(NULL, "\n");
				bool validSalesperson = false;
				for (int i = 0; i < group->sCount; i++) {
					if (strcmp(id, group->sList[i]->id) == 0) {
						validSalesperson = true;
					}
				}
				if (!validSalesperson) {
					printf("\n");
					printf("Invalid command\n");
					return false;
				}
				Salesperson *s = getSalesperson(group, id);
				printf("\n");
				printf("ID         Name                                Sold\n");
				BookNode *temp = s->head;
				int total = 0;
				if (s->head->book->name == NULL) {
					printf("\n");
				}
				else {
					while (temp->next != NULL) {
						printf("%-10s ", temp->book->id);
						printf("%-30s ", temp->book->name);
						printf("%9d\n", temp->sold);
						total = total + temp->sold;
						temp = temp->next;
					}
					printf("%-10s ", "Total");
					printf("%-30s ", "");
					printf("%9d", total);
				}
			}
			else {
				printf("\n");
				printf("Invalid command\n");
				return false;
			}
		}
		else {
			printf("\n");
			printf("Invalid command\n");
			return false;
		}
	}
	else {
		freeGroup(group);
		exit(0);
	}
	printf("\n");
	return true;

}

int compSalesperson(const void *s1, const void *s2)
{

	const Salesperson *sp1 = *(Salesperson **) s1;
	const Salesperson *sp2 = *(Salesperson **) s2;
	if (sp2->sold < sp1->sold) {
		return -1;
	}
	else if (sp2->sold > sp1->sold) {
		return 1;
	}
	else {
		return strcmp(sp1->id, sp2->id);
	}
}

int compBook(const void *c1, const void *c2)
{

	const Book *book1 = *(Book **) c1;
	const Book *book2 = *(Book **) c2;

	if (strcmp(book1->name, book2->name) == 0) {
		return (strcmp(book1->id, book2->id));
	}
	else {
		return strcmp(book1->name, book2->name);
	}
}

void sortGroupBooks(Group *group)
{
	qsort(group->bList, group->bCount, sizeof(group->bList[0]), compBook);

}

void sortGroupSalespersons(Group *group)
{

	qsort(group->sList, group->sCount, sizeof(group->sList[0]), compSalesperson);
}

void insert(BookNode **head, Book *c, int val)
{
	BookNode * current;
	BookNode *newNode = malloc(sizeof(BookNode));
	newNode->book = c;
	newNode->sold = val;
	newNode->next = NULL;
	/*Special case for the head end */
	if ((*head)->book == NULL || compBook2((*head)->book, newNode->book) > 0) {  

		newNode->next = *head;
		*head = newNode;
	}
	else {

		/*Locate the node before the point of insertion */
		current = *head;
		while (current->next->book != NULL &&
			compBook2(current->next->book, newNode->book) < 0) {
			current = current->next;
		}
		newNode->next = current->next;
		current->next = newNode;
	}
}

bool contains(BookNode *head, char *bID)
{

	BookNode *current = head;
	while (current->book != NULL) {

		if (strcmp(current->book->id, bID) == 0) {
			return true;
		}
		current = current->next;
	}
	return false;
}

int compBook2(const Book *book1, const Book *book2)
{
	if (strcmp(book1->name, book2->name) == 0) {
		return (strcmp(book1->id, book2->id));
	}
	else {
		return strcmp(book1->name, book2->name);
	}
}