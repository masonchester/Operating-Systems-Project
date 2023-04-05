#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  unsigned int base_address;
  unsigned int limit_offeset;

  struct node *next;
  struct node *prev;
};

struct node *node_find(struct node *list, int search_address)
{
  struct node *current = list;
  while (search_address >= current->base_address && search_address <= (current->base_address + current->limit_offeset) - 1)
  {
    return current;
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
