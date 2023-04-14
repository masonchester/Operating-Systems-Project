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
void sort_by_base_address(struct node *list)
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
  if (current->base_address > base_address)
  {
    if (current->next != NULL)
    {

      current->next->prev = new_node;
    }

    new_node->next = current->next;
    current->next = new_node;
    new_node->prev = current;

    new_node->base_address = current->base_address;
    new_node->limit_offeset = current->limit_offeset;
    current->base_address = base_address;
    current->limit_offeset = limit_offset;
  }
  else
  {
    // search the list until you find a base address current base address smaller than the new nodes
    while (current->next != NULL && current->next->base_address < base_address)
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
}

void resize(struct node **head, unsigned int base_address, unsigned int limit_offset)
{
  struct node *temp = *head;
  while (temp->next != NULL && temp->base_address != base_address)
  {
    temp = temp->next;
  }
  if (temp->next != NULL)
  {
    temp->limit_offeset = limit_offset;
    sort_by_base_address(temp);
  }
}

void create_holes_list(struct node **holes_list,struct node **memoryList,unsigned int base_address, unsigned int limit_offset)
{
  struct node *temp_memory = *memoryList;
  struct node *temp_hole = *holes_list;
  if(temp_memory == NULL)
  {
    add(holes_list,base_address,limit_offset);
    return;
  }
  else if(temp_memory->next == NULL)
  {
    if(temp_hole == NULL)
    {
      add(holes_list,temp_memory->limit_offeset+1,limit_offset);
    }
    else
    {
    temp_hole->base_address = temp_memory->limit_offeset + 1;
    temp_hole->limit_offeset = limit_offset;
    }
    return;
  }
  else if(temp_memory != NULL)
  {
    while(temp_memory->next != NULL)
    {
      if(temp_memory->base_address + temp_memory->limit_offeset + 1 < temp_memory->next->base_address-1)
      {
        add(holes_list,(temp_memory->limit_offeset + 1),temp_memory->next->base_address-1);
      }
      temp_memory = temp_memory->next;
    }
    if(temp_memory != NULL)
    {
      add(holes_list,temp_memory->limit_offeset +1, limit_offset);
    }
  }
}
void delete_hole_list(node **head)
{
  node *current = *head;
  node *next_node;
  while(current != NULL)
  {
    next_node = current->next;
    free(current);
    current = next_node;
  }
  *head = NULL;
}
void print_hole_list(node* the_list)
{
  node* current = the_list;
  while(current != NULL)
  {
    printf("%d", current->base_address);
    printf(" ");
    printf("%d",current->limit_offeset);
    printf(" ");
    current = current->next;
  }
}


void main()
{
  struct node *head = NULL;
  struct node *hole_list = NULL;
create_holes_list(&hole_list,&head,0,1024);
 printf("holes ");
 print_hole_list(hole_list);
printf("\n");

add(&head,0, 200);
 printf("Memory ");
 print_hole_list(head);
 printf("\n");
 create_holes_list(&hole_list,&head,0,1024);
 printf("holes ");
 print_hole_list(hole_list);
 printf("\n");
delete_hole_list(&hole_list);

 add(&head,300, 401);
 printf("Memory ");
 print_hole_list(head);
 printf("\n");
 create_holes_list(&hole_list,&head,0,1024);
 printf("hole_list ");
 print_hole_list(hole_list);
 printf("\n");
 delete_hole_list(&hole_list);


printf("Memory ");
 add(&head,800, 1000);
 print_hole_list(head);
 printf("\n");
 printf("Hole_list ");
 create_holes_list(&hole_list,&head,0,1024);
 print_hole_list(hole_list);

  //delete_hole_list(&hole_list);
  //add(&head, 201, 300);
  //create_holes_list(&hole_list,&head,0,0x400);
  //print_hole_list(&hole_list);
  
}
