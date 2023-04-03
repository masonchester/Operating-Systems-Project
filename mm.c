typedef struct node{
  unsigned int base_address;
  unsigned int limit_offeset;

  struct node* next;
  struct node* prev;
}

struct node* head = NULL;
struct node* tail = NULL;
struct node* current = NULL;


struct node* node_find(node* list, int search_address){
}

void sort_by_id(node* list){
}

void sort_by_size(node* list){
}

void add(node* head, unsigned int base_address, unsigned int limit_offset){
}

void add(node * head, node* new_node){
}

void delete_by_address(node* head, int delete_id){
}

void resize(node* head, unsigned int base_address, unsigned int limit_offset){
}

