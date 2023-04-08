#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct node
{
  unsigned int base_address;
  unsigned int limit_offeset;

  struct node *next;
  struct node *prev;
};

// global variable pointing to the head
struct node *head = NULL;

// global varaible pointing to the tail
struct node *tail = NULL;

void create_holes_list(struct node **head,unsigned int base_address,unsigned int limit_offset)
{
  struct node* the_hole_list =(struct node *) malloc(sizeof(struct node));
  the_hole_list->base_address = base_address;
  the_hole_list->limit_offeset = limit_offset;
  the_hole_list->next = NULL;
  the_hole_list->prev = NULL;
  *head = the_hole_list;
}

int remove_hole_from_list(struct node *holes_list, unsigned int limit_offset,unsigned int size_of_process)
{
   struct node *current = holes_list;
   if(current->next == NULL)
   {
      if(current->base_address + size_of_process <= current->limit_offeset + 1)
      {
        unsigned int temp = current->base_address;
        current->base_address = current->base_address + size_of_process + 1;
        return current->base_address;
      }
   }
   //While loop to look for either a null node or a node not in use in the list. 
   while(current->next != NULL)
   {
      if(current->base_address + size_of_process <= current->limit_offeset + 1)
      {
        unsigned int temp = current->base_address;
        current->base_address = current->base_address + size_of_process + 1;
        return current->base_address;
      }
      //Otherwise we continue looking. 
      *current = *current->next;
    }
    //indicate error by returning -1
    return -1;
}

void add_hole_to_list(struct node *holes_list, unsigned int base_address, unsigned int limit_offset)
{
  struct node *current = holes_list;
  while(current->next != NULL)
    {
      if(current->limit_offeset == base_address + 1)
      {
        current->limit_offeset = limit_offset;
        return;
      }
      else if(current->next->base_address == base_address + 1)
      {
        current->limit_offeset = current->next->limit_offeset;
        struct node *temp = current->next;
        current->next = current->next->next;
        free(temp);
        return; 
      }
      current = current->next;
    }
   if(current->next == NULL)
   {
    if(current->base_address == limit_offset + 1)
    {
      current->base_address = base_address;
      return;
    }
    else if(current->base_address > limit_offset)
    {
        struct node* new_node =(struct node *) malloc(sizeof(struct node));
        current->prev = new_node;
        current->prev->base_address = base_address;
        current->prev->limit_offeset = limit_offset;
        new_node->next = current;
    }
   }
}