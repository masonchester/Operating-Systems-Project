#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  unsigned int base_address;
  unsigned int limit_offeset;

  struct node *next;
  struct node *prev;
} node;

// searchs for the node which contains the current base address
struct node *node_find(struct node *list, int search_address)
{
  struct node *current = list;
  while (current != NULL && current->base_address != search_address)
  {
    current = current->next;
  }
  return current;
}

// sorts the list by the base address in increasing order
void sort_by_baseaddress(struct node *list)
{
  struct node *current = list;
  while (current != NULL)
  {
    struct node *current_next = current->next;
    while (current_next != NULL)
    {
      if (current_next->base_address < current->base_address)
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

// sorts the list by the limit offset by increasing order
void sort_by_limitaddress(struct node *list)
{
  struct node *current = list;
  while (current != NULL)
  {
    struct node *current_next = current->next;
    while (current_next != NULL)
    {
      if (current_next->limit_offeset < current->limit_offeset)
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

// add a node in its sorted position
void add(struct node **head, unsigned int base_address, unsigned int limit_offset)
{
  // Allocate for a new node
  struct node *new_node = (struct node *)malloc(sizeof(struct node));
  new_node->base_address = base_address;
  new_node->limit_offeset = limit_offset;
  new_node->next = NULL;
  new_node->prev = NULL;

  if (*head == NULL) // if the head is empty
  {
    new_node->prev = NULL;
    *head = new_node;
    return;
  }
  struct node *current = *head;
  // search the list until you find a base address current base address smaller than the new nodes
  while (current->next != NULL && current->next->base_address <= base_address)
  {
    current = current->next;
  }

  // if the current address -> next is null than you are the last node
  if (current->next != NULL)
  {
    current->next->prev = new_node;
  }

  // link current node and new node
  new_node->next = current->next;
  current->next = new_node;
  new_node->prev = current;
}

void delete_by_address(struct node **head, unsigned int delete_address)
{
  struct node *current = *head;

  while (current != NULL && current->base_address != delete_address)
  {
    current = current->next;
  }

  // If the node is the head delete the head
  if (current->prev == NULL)
  {
    *head = current->next;
    return;
  }
  // If the node is the tail then delete it
  else if (current->next == NULL)
  {
    current->prev->next = NULL;
  }
  else // if the node is not a head or a tail then it must be in the middle of two nodes
  {
    current->prev->next = current->next;
    current->next->prev = current->prev;
  }
  free(current); // deallocate current
  return;
}

void resize(struct node **head, unsigned int base_address, unsigned int limit_offset)
{
}
