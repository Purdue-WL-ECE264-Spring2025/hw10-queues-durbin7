#include "linked_list.h"

#include <stdlib.h>

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

void insert_at_tail(struct linked_list *list, size_t value) {}

size_t remove_from_head(struct linked_list *list) { return 0; }

size_t remove_from_tail(struct linked_list *list) { return 0; }

void free_list(struct linked_list list) {}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
