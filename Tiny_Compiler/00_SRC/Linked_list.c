#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Linked_list.h"

LIST* create_list() {
	
	printf("creating a list...\n");
	LIST* list = (LIST*)malloc(sizeof(LIST));
	if ( !list )  return 0;

	list->count = 0;
	list->head = 0;
	list->last = 0;
	return list;
}	

void add_list(LIST* list, char* var) {

	printf("adding a data into list");
	NODE* node = (NODE*)malloc(sizeof(NODE));
	if(!node) return;

	node->data = var;
	node->usage = 0;
	if(list->count == 0) {
		list->head = node;
		list->last = node;
		node->link = 0;
		(list->count)++;
	}
	else {

		list->last->link = node;
		list->last = node;
		(list->count)++;
	}
}	




