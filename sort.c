#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "sort.h"

void sort(List *list, int (*compare) (void *, void *)) {
  quicksort(list, list -> head, list -> tail,
	compare);
}

void swap(List *list, Node *left, Node *right) {
  Node *temp;
  temp = right;

  if (left == list -> head)
    list -> head = right;
  if (right == list -> tail)
    list -> tail = left;
  
  right -> prev = left -> prev;
  right -> next = left -> next;
  left -> prev = temp -> prev;
  left -> next = temp -> next;
}

void quicksort(List *list, Node *leftIdx, Node *rightIdx,
	   int (*compare)(void *, void *)) {

  Node  *middleIdx;
  if ( leftIdx != rightIdx) {
    middleIdx = partition(list, leftIdx, rightIdx,
			  compare);
    
    quicksort(list, leftIdx, middleIdx -> prev,
	  compare);
    
    quicksort(list, middleIdx -> next, rightIdx,
	  compare);
  }
  return;
}

Node* partition(List *list, Node *leftIdx, Node* rightIdx,
		int (*compare) (void *, void *)) {
  Node *temp;
  Node *itr = leftIdx;
  Node *index = leftIdx;

  while (itr != rightIdx) {
    if ( ((*compare)(itr -> data, leftIdx -> data)) <= 0 ) {
      index = itr;
      swap(list, index , itr);
    }
    itr = itr -> next;
  }
  swap(list, index -> next, rightIdx);
  return (index -> next);
}
      
  
