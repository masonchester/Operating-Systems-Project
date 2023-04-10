#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct node
{
  unsigned int base_address;
  unsigned int limit_offeset;

  struct node *next;
  struct node *prev;
} node;

typedef struct holeList{
  node* head;
} holeList;
//creates the holes list and returns it.
holeList* create_holes_list()
{
  holeList* the_hole_list = (holeList*) malloc(sizeof(holeList));
 the_hole_list->head = NULL;
  return the_hole_list;
}
//this method removes space from the holes list and returns base address of the current node
//which is the limit index + 1 for the new process.
int remove_hole_from_list(holeList* the_list,unsigned int size_of_process,unsigned int limit_offset)
{
  //We set current equal to the head of the list.
   struct node *current = the_list->head;
   //if current.next is null then we only have one big clump of memory to deal with.
   if(current->next == NULL)
   {
    //if the base address + the size of the process is less than or equal to the offset then
    //we know the process will fit into memory.
      if(current->base_address + size_of_process <= current->limit_offeset)
      {
        //in here if the process is not the same size as our total memory then we can set currents base address
        //equal to its base address plus the size of the process + 1. The +1 is because we want to make sure
        //that it starts at the next avaiable memory cell
        if(current->base_address + size_of_process + 1 <= limit_offset)
        {
          unsigned int temp = current->base_address;
          current->base_address = current->base_address + size_of_process + 1;
          //we return the starting position where the process should go in memory.
          return temp;
        }
        else
        //otherwise the process still fits but there is no next spot avaiable in the memory and we do not want the hole list to say 1001 and 1000.
        {
           unsigned int temp = current->base_address;
          current->base_address = current->base_address + size_of_process;
          //we return the starting position where the process should go in memory.
          return temp;
        }
        
      }
   }
   //The next case is that we have multiple holes in our holes list.
   while(current->next != NULL)
   {
    //we need to search through these holes and see if there is a spot where the process can fit.
      if(current->base_address + size_of_process <= current->limit_offeset + 1)
      {
         unsigned int temp = current->base_address;
        //if we find a spot we can update currents base address to reflect that space as not being open.
        current->base_address = current->base_address + size_of_process + 1;
        //we return the starting positon where the process should go in memory.
        return temp;
      }
      //Otherwise we continue looking. 
      *current = *current->next;
    }
    //indicate error by returning -1
    return -1;
}
//add_hole_to_list is used to add space back into the holes list. 
void add_hole_to_list(holeList* the_list, unsigned int base_address, unsigned int limit_offset)
{
  //if the head is null then we create our first hole. This will dicate the size of the entire list.
  if(the_list->head == NULL)
  {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->base_address = base_address;
    new_node->limit_offeset = limit_offset;
    new_node->next = NULL;
    new_node->prev = NULL;
    the_list->head = new_node;
    return;
  }
  //Otherwise we set current equal to head and start looking for the position in which the memory needs to be realocatted.
  node* current = the_list->head;
  while(current->next != NULL)
    {
    //first thing to check is if there is a gap in the holes list that can be recombined. 
    if(current->limit_offeset + 1 == base_address && current->next->base_address == limit_offset + 1)
    {
      //if the condition above is true then we need to delete the next node from current and adjust currents limit offset to be equal to current.next's limit offset.
      current->limit_offeset = current->next->limit_offeset;
      node* temp = current->next->next;
      free(current->next);
      current->next = temp;
      return;
    }
    //otherwise we check if currents limit offset + 1 is equal to the base address on the process being removed from memory.
    //if it is then we just adjust the limit offset of current.
     else if(current->limit_offeset + 1 == base_address)
      {
        current->limit_offeset = limit_offset;
        return;
      }
      current = current->next;
    }
    //If we are at the back of the list or there is only one node then
    //we need to check that the memory is not immediately behind the last node.
   if(current->next == NULL)
   {
    //if the memory that is being freed up is right behind current then we just adjust the base address.
    if(current->base_address == limit_offset + 1)
    {
      current->base_address = base_address;
      return;
    }
    //otherwise if the base address of current is bigger than the limit offset 
    //we need to allocate another node in the holes list and make it the head of the list.
    else if(current->base_address > limit_offset)
    {
        node* new_node = (node*)malloc(sizeof(node));
        new_node->base_address = base_address;
        new_node->limit_offeset = limit_offset;
        
       new_node->next = the_list->head;
       new_node->prev = NULL;
       if(the_list->head != NULL)
       {
        the_list->head->prev = new_node;
       }
       the_list->head = new_node;
    }
   }
}
//method to print the holes list.
void print_hole_list(holeList* the_list)
{
  node *current = the_list->head;
  while(current != NULL)
  {
    printf("%d", current->base_address);
    printf(" ");
    printf("%d",current->limit_offeset);
    printf(" ");
    current = current->next;
  }
  printf("\n");
}

int main()
{
  //Testing the holes list.
  unsigned int limit_offset = 1000;
  holeList* list = create_holes_list();
  add_hole_to_list(list,0,limit_offset);
  printf("%d",remove_hole_from_list(list,100,limit_offset));
  printf("\n");
  printf("%d",remove_hole_from_list(list,100,limit_offset));
  printf("\n");
  printf("%d",remove_hole_from_list(list,100,limit_offset));
  printf("\n");
  printf("%d",remove_hole_from_list(list,100,limit_offset));
  printf("\n");
  printf("%d",remove_hole_from_list(list,100,limit_offset));
  printf("\n");
  print_hole_list(list);
  printf("\n");
  add_hole_to_list(list,0,100);
  print_hole_list(list);
  printf("\n");
  add_hole_to_list(list,101,201);
  print_hole_list(list);
  printf("\n");
  add_hole_to_list(list,202,504);
  print_hole_list(list);
  printf("\n");
  return 0;
}
