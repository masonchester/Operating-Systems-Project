#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  unsigned int base_address;
  unsigned int limit_offset;

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
        unsigned int temp_limit = current->limit_offset;
        current->base_address = current_next->base_address;
        current->limit_offset = current_next->limit_offset;
        current_next->base_address = temp_base;
        current_next->limit_offset = temp_limit;
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
  new_node->limit_offset = limit_offset;
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
    new_node->limit_offset = current->limit_offset;
    current->base_address = base_address;
    current->limit_offset = limit_offset;
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
// resize a given node
void resize(struct node **head, unsigned int base_address, unsigned int limit_offset)
{
  struct node *temp = *head;
  while (temp != NULL && temp->base_address != base_address)
  {
    temp = temp->next;
  }
  if (temp != NULL)
  {
    temp->limit_offset = limit_offset;
    sort_by_base_address(temp);
  }
}

//Method to create holes list. It scans the memory list and creates a new linked list to represent the holes.
void create_holes_list(struct node **holes_list,struct node **memoryList,unsigned int start, unsigned int end)
{
  //We create a pointer for both the holes list pointer and the memory list pointer.
  struct node *temp_memory = *memoryList;
  struct node *temp_hole = *holes_list;
  //If there is nothing in memory then we just set the hole list to the total size of the memory.
  if(temp_memory == NULL)
  {
    add(holes_list,start,end);
    return;
  }
  //if there is only one thing in memory then we can just adjust the holes list.
  else if(temp_memory->next == NULL)
  {
    //if the holes list is null then we just create a new node based on limit offset of the memory list and the limit offset of the total memory.
    if(temp_hole == NULL)
    {
      add(holes_list,((temp_memory->base_address + temp_memory->limit_offset)), end - ((temp_memory->base_address + temp_memory->limit_offset)));
    }
  }

  //If the memory is not null then we need to check if it has more than one thing in memory.
  else if(temp_memory != NULL)
  {
    while(temp_memory->next != NULL)
    {
      //if the next is not null then we need to start populating the holes list.
      //if the base address + limit offset + 1 < the next base address -1 then we have a hole inbetween two spots in memory.
      if(temp_memory->base_address + temp_memory->limit_offset + 1 < temp_memory->next->base_address-1)
      {
        add(holes_list,((temp_memory->base_address + temp_memory->limit_offset)),(temp_memory->next->base_address) - ((temp_memory->base_address + temp_memory->limit_offset)));
      }
      //otherwise we just continue looking.
      temp_memory = temp_memory->next;
    }
    //we have to check the last element in memory. If it is not null then we need to account for that in the holes list.
    if(temp_memory != NULL)
    {
	add(holes_list,((temp_memory->base_address + temp_memory->limit_offset)), end - ((temp_memory->base_address + temp_memory->limit_offset)));
    }
  }
}

//delete_hole_list is used to free the holes list so we can generate a new one. This way we do not have to maintain the holes list
//we can just scan the entire list and generate the holes.
void delete_hole_list(struct node **head)
{
  node *current = *head;
  node *next_node;
  while(current != NULL)
  {
    next_node = current->next;
    free(current);
    current = next_node;
  }
  free(current);
  *head = NULL;
}

void mm_add(struct node **memory_list, struct node **holes_list,unsigned int base_address, unsigned int limit_offset, unsigned int min, unsigned int max)
{
  add(memory_list,base_address,limit_offset);
  if(holes_list != NULL)
  {
    delete_hole_list(holes_list);
  }
  create_holes_list(holes_list,memory_list,min,max);
}

void mm_delete(struct node **memory_list, struct node **holes_list,unsigned int base_address, unsigned int limit_offset, unsigned int min, unsigned int max)
{
  delete_by_address(memory_list,base_address);
   if(holes_list != NULL)
  {
    delete_hole_list(holes_list);
  }
  create_holes_list(holes_list,memory_list,min,max);
    // if the current address -> next is null than you are the last node
}

//resize a nodes limit offset, node is found by the base address.
void mm_resize(struct node **memory_list, struct node **holes_list, unsigned int base_address, unsigned int limit_offset, unsigned int min, unsigned int max){
	resize(memory_list, base_address, limit_offset);	
	if(holes_list != NULL){
		delete_hole_list(holes_list);
	}
	create_holes_list(holes_list, holes_list,min, max);
}


void printlist(struct node *head)
{
  struct node *temp = head;
  while (temp != NULL)
  {
    printf("%x %x -> ", temp->base_address, temp->limit_offset);
    temp = temp->next;
  }
  printf("\n");
}

void print_memory(struct node* memory_list,struct node* hole_list,unsigned int min,unsigned int max)
{
 
  struct node* current_hole = hole_list;
  struct node* current_mem = memory_list;
  
  unsigned int total_free = 0;
  unsigned int total_allocated = 0;
  
  int hole_gap = 0;
  int mem_gap = 0;
  
  while(current_hole != NULL)
  {
    total_free += current_hole->base_address + current_hole->limit_offset;
    current_hole = current_hole->next;
    hole_gap++;
  }
  while(current_mem != NULL)
  {
    total_allocated +=  current_mem->limit_offset + current_mem->base_address;
    current_mem = current_mem->next;
    mem_gap++;
  }
   printf("Total Physical Memory: ");
  printf("%x", max);
  printf("\n");
  printf("Total Free: ");
  printf("%x", total_free);
  printf("\n");
  printf("Total Allocated: ");
  printf("%x", total_allocated);
  printf("\n");
  printf("Number of allocations: ");
  printf("%x", mem_gap);
  printf("\n");
  printf("Number of free gaps: ");
  printf("%x", hole_gap);
  printf("\n");
  printf("Start of Memory: ");
  printf("%x", min);
  printf("\n");
  printf("End of Memory: ");
  printf("%x", max);
  printf("\n");
}




void main()
{
	struct node* memory_list = NULL;
	struct node* holes_list = NULL;

	mm_add(&memory_list, &holes_list, 0x10000, 0x400, 0x10000, 0x40000);
	mm_add(&memory_list, &holes_list, 0x11000, 0x1000, 0x10000, 0x40000);
	mm_add(&memory_list, &holes_list, 0x20000, 0x400, 0x10000, 0x40000);

	printlist(memory_list);
	printlist(holes_list);

	print_memory(memory_list, holes_list, 0x10000, 0x40000);	
}





