#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  unsigned int base_address;
  unsigned int limit_offeset;

  struct node *next;
  struct node *prev;
};

struct node *head = NULL;
struct node *tail = NULL;

struct node *node_find(struct node *list, int search_address)
{
  struct node *current = list;
  while (current != NULL && current->base_address != search_address)
  {
    current = current->next;
  }
  return current;
}

void sort_by_baseaddress(struct node *list)
{
  struct node *current = list;
  while (current != NULL)
  {
    struct node *current_next = current->next;
    while (current_next != NULL)
    {
      if (current_next->base_address > current->base_address)
      {
        unsigned int temp_base = current->base_address;
        unsigned int temp_limit = current->limit_offeset;
        current->base_address = current_next->base_address;
        current->limit_offeset = current_next->limit_offeset;
        current_next->base_address = temp_base;
        current_next->limit_offeset = temp_limit;
      }
      current_next = current_next->next;
    }
    current = current->next;
  }
}
void sort_by_limitaddress(struct node *list)
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
