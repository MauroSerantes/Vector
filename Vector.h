#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include <stdbool.h>
#include <stdint.h>

typedef void (*Vector);

Vector      vector_new_void(void);
Vector      vector_new(uint32_t maxsize);
void        vector_free(Vector v);
uint32_t    vector_size(Vector  v);
bool        vector_isempty(Vector  v);
void*       vector_get(Vector  v,uint32_t index);
void*       vector_set(Vector  v,uint32_t index,void* value);
bool        vector_add(Vector  v,void* value);
bool        vector_insert(Vector  v,uint32_t index,void* value);
void*       vector_remove(Vector v,uint32_t index);
void        vector_select_sort(Vector v,int (*compare)(void*,void*));   
void        vector_insert_sort(Vector v,int (*compare)(void*,void*));
void        vector_bubble_sort(Vector v,int (*compare)(void*,void*));
void        vector_bubble_sort_improved(Vector v,int (*compare)(void*,void*));
void        vector_quick_sort(Vector  v,int (*compare)(void*,void*));
void        vector_merge_sort(Vector v,int (*compare)(void*,void*));
void        vector_shell_sort(Vector v,int (*compare)(void*,void*));
uint32_t    vector_sequential_search(Vector v,void* value,int (*compare)(void*,void*));
uint32_t    vector_binary_search(Vector v,void* value,int (*compare)(void*,void*));
void        vector_traverse(Vector v,bool vector_do(void*,void*,uint32_t),void* context);

#include "Vector.c"
#endif //VECTOR_H_INCLUDED