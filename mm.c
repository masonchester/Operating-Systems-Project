#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int pid;
  
  unsigned int base_address;
  unsigned int limit_offeset;

  struct node *next;
  struct node *prev;
};

struct node *node_find(struct node *list, int search_address)
{
  struct node* current = list;
  while(current != NULL){
    if(search_address == current->pid){
      return current;
    }
    current = current->next;
  }
  return NULL;
}

void sort_by_id(struct node *list)
{
}

void sort_by_size(struct node *list)
{
}

void add(struct node *head, unsigned int base_address, unsigned int limit_offset)
{
}

void delete_by_address(struct node *head, int delete_id)
{
}

void resize(struct node *head, unsigned int base_address, unsigned int limit_offset)
{
}
