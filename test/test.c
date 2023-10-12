#include "mm.h"

void main(){

struct node* mem_list = NULL;

struct node* hole_list = NULL;

mm_add(&mem_list, &hole_list,0x10000, 0x400, 0x10000, 0x40000 );
mm_add(&mem_list, &hole_list,0x11000, 0x1000, 0x10000, 0x40000 );
mm_add(&mem_list, &hole_list,0x20000, 0x400, 0x10000, 0x40000 );

print_memory(mem_list, hole_list, 0x10000, 0x40000);

}
