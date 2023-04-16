#include <stdlib.h>
#include <stdio.h>
#ifndef mm
#define mm

typedef struct node
{
  unsigned int base_address;
  unsigned int limit_offset;

  struct node *next;
  struct node *prev;
} node;

struct node *node_find(struct node *list, int search_address);

void sort_by_base_address(struct node *list);

void add(struct node **head, unsigned int base_address, unsigned int limit_offset);

void delete_by_address(struct node **head, unsigned int delete_address);

void resize(struct node **head, unsigned int base_address, unsigned int limit_offset);

void create_holes_list(struct node **holes_list,struct node **memoryList,unsigned int start, unsigned int end);

void delete_hole_list(struct node **head);

void mm_add(struct node **memory_list, struct node **holes_list,unsigned int base_address, unsigned int limit_offset, unsigned int min, unsigned int max);


void mm_delete(struct node **memory_list, struct node **holes_list,unsigned int base_address, unsigned int limit_offset, unsigned int min, unsigned int max);

void mm_resize(struct node **memory_list, struct node **holes_list, unsigned int base_address, unsigned int limit_offset, unsigned int min, unsigned int max);

void print_memory(struct node* memory_list,struct node* hole_list,unsigned int min,unsigned int max);

#endif
