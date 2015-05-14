#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h" 
#include "sort.h"

int compare(void *leftOpr, void *rightOpr) {
  if ( (*(int *)leftOpr) == (*(int *)leftOpr) )
    return 0;

  if ( (*(int *)leftOpr) > (*(int *)leftOpr) )
    return 1;

  return -1;
}

void list_init(List *list, void (*destroy)(void *data)) {
  list -> size = 0;
  list -> destroy  = destroy;
  list -> head = NULL;
  list -> tail = NULL;
  
  return;
}

void list_destroy(List *list) {
  void *data;

  while(list_size(list) > 0) {
    if (list_rem_next(list, NULL, (void **)&data) == 0 && list -> destroy != NULL) {
      list -> destroy(data);
    }
  }

  memset(list , 0 , sizeof(List));

  return;
}

int list_ins_next(List *list , Node *element , const void *data) {

  Node *new_element;
  Node *temp;

  if ((new_element = (Node *)malloc(sizeof(Node))) == NULL)
    return -1;

  new_element -> data = (void *) data;

  if (element == NULL) {

    if (list_size(list) == 0) {
      list -> tail = new_element;
      list -> head = new_element;
    }
    else {
      new_element -> next = list -> head;
      list -> head -> prev = new_element;
      list -> head = new_element;
    }
  }
  else {
    
    if (element -> next == NULL) {
      list -> tail = new_element;
      list -> head = new_element;
    }
    else {
      new_element -> next = element -> next;
      element -> next = new_element;
      new_element -> prev = element;
    }
  }

  list -> size++;

  return 0;
}

int list_rem_next(List *list, Node *element, void **data) {

  Node *old_element;

  if (list_size(list) == 0)
    return -1;

  if (element = NULL) {

    *data = list -> head -> data;
    old_element = list -> head;
    list -> head = list -> head -> next;

    if (list_size(list) == 1)
      list -> tail = NULL;
  }
  else {

    if (element -> next == NULL)
      return -1;

    *data = element -> next -> data;
    old_element = element -> next;
    element -> next = element -> next -> next;

    if (element -> next == NULL)
      list -> tail = element;

  }

  free(old_element);

  list -> size--;

  return 0;
}

void print(List *list) {
  Node *temp;
  int *number;

  temp = list -> head;

  while (temp -> next != NULL) {
    number =  list_data(temp);
    fprintf(stdout, "%d\n", *number);
    temp = temp -> next;
  }
}

void populate_list(List *list) {
  
  int i;
  int *temp;
  
  for (i = 0; i < 30; i++) {
    if ((temp = (int *)malloc(sizeof(int))) == NULL)
      return;
    
    *temp = rand() % 100;
    list_ins_next(list, NULL, temp);
  }
}

int main() {
  List linkedList;
  list_init(&linkedList, free);

  populate_list(&linkedList);
  print(&linkedList);
  sort(&linkedList, compare);
  print(&linkedList);
}
