#include "linked_list.h"

#include <stdlib.h>

// WRITE THIS??
struct list_node *new_node(size_t value) { return NULL; }

void insert_at_head(struct linked_list *list, size_t value) 
{
  // Make new node and add value
  struct list_node * toadd = malloc(sizeof(struct list_node));
  toadd -> value = value;

  // Make new node's next point to beginning of list
  toadd -> next = list -> head;

  // Change list head to new node
  list -> head = toadd;
}

void insert_at_tail(struct linked_list *list, size_t value) 
{
  // Make new node and add value
  struct list_node * toadd = malloc(sizeof(struct list_node));
  toadd -> value = value;

  // Make new node's next point to NULL
  toadd -> next = NULL;

  // Change last node to point to new node
  struct list_node * findend = list -> head; // OR just list?
  while(findend -> next != NULL)
  {
    findend = findend -> next;
  }
  findend -> next = toadd;
}

size_t remove_from_head(struct linked_list *list) 
{ 
  // Define node to remove
  struct list_node * toremove = list -> head; // OR just list?

  // Rewire around node to remove
  list -> head = list -> head -> next; // list instead of list -> head?

  size_t rem_val = toremove -> value;

  // Free removed node
  free(toremove);
  return rem_val; 
}

size_t remove_from_tail(struct linked_list *list) 
{ 
  // precondition: list is size 1 or more
  struct list_node * findsec = list -> head;
  if(findsec -> next == NULL) // is my list size 1
  {
    size_t rem_val = findsec -> value;
    free(findsec);
    list -> head = NULL;
    return rem_val;
  }

  while(findsec -> next -> next != NULL)
  {
    findsec = findsec -> next;
  }
  
  size_t rem_val = findsec -> next -> value;
  free(findsec -> next);
  findsec -> next = NULL;

  return rem_val;
}

void free_list(struct linked_list list) 
{

  while(list.head != NULL)
  {
    remove_from_head(&list);
  }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
