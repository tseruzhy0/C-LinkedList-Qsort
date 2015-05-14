#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void sort(List *list,
	  int (*compare) (void *, void *));

void swap(List *list, Node *left, Node* right);

void quicksort(List *list, Node *leftIdx, Node *rightIdx,
	   int (*compare) (void *, void *));

Node* partition(List *list, Node *leftIdx, Node* rightIdx,
		int (*compare) (void *, void *));

int compare(void *leftOpr, void *rightOpr);


#endif
