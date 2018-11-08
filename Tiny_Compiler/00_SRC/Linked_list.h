#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	char *data;
	int usage;
	struct node *link;
} NODE;

typedef struct list {
	int count;
	NODE *head;
	NODE *last;
} LIST;

LIST* create_list();
void add_list(LIST* list, char* var);
