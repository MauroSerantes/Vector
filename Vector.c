#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include "Vector.h"

#define INIT_SIZE_DYNAMIC (uint32_t) 10

typedef struct{
 void** v;
 uint32_t size;
 uint32_t max_size;
 bool is_dynamic;
 uint32_t current_size_dynamic;
}vector_t;


// these are the prototypes of auxiliar procedures
void _quick_sort(void** start,void** end,int(*compare)(void*,void*));
void merge_sort(vector_t* v,uint32_t start,uint32_t end,int(*compare)(void*,void*));
void _merge(vector_t* v,uint32_t start,uint32_t middle,uint32_t end,int(*compare)(void*,void*));


/**
 * @brief creates a new vector structure. The max init size of the vector is 10
 * 
 * @return Vector 
 */
Vector vector_new_void(void){
  vector_t* vector = (vector_t*) malloc(sizeof(vector_t));
  if(vector!=NULL){
    vector->v = (void**) malloc(INIT_SIZE_DYNAMIC*sizeof(void*));
    vector->size = 0;
    vector->max_size = 0;
    vector->is_dynamic = true;
    vector->current_size_dynamic = INIT_SIZE_DYNAMIC;
  }
  return (Vector) vector;
}

/**
 * @brief creates a new vector structure of the specified size
 * 
 * @param maxsize 
 * @return Vector 
 */
Vector  vector_new(uint32_t maxsize){
  vector_t* vector = (vector_t*) malloc(sizeof(vector_t));
  if(vector!=NULL){
    vector->v = (void**) malloc(maxsize*sizeof(void*));
    vector->size = 0;
    vector->max_size = maxsize;
    vector->is_dynamic = false;
    vector->current_size_dynamic = 0;
  }
  return (Vector) vector;
}

/**
 * @brief free the memory of a vector structure
 * 
 * @param v 
 */
void vector_free(Vector v){
  if(v!=NULL){
    free(((vector_t*)v)->v);
    free(v);
  }
}

/**
 * @brief returns the size of a vector
 * 
 * @param v 
 * @return uint32_t 
 */
uint32_t vector_size(Vector  v){
  if(v == NULL) return 0;
  
  return ((vector_t*)v)->size;
}

/**
 * @brief checks if the vector is empty.Returns true if is empty and false otherwise
 * 
 * @param v 
 * @return true 
 * @return false 
 */
bool vector_isempty(Vector  v){
  if(v == NULL) return true;

  return ((vector_t*)v)->size == 0;
}


/**
 * @brief gets the element of the specified position 
 * 
 * @param v 
 * @param index 
 * @return void* 
 */
void*  vector_get(Vector  v,uint32_t index){
  if(v == NULL) return NULL;

  if(index>=((vector_t*)v)->size) return NULL; 

  return ((vector_t*)v)->v[index];
}


/**
 * @brief changes the element of the specified position
 * 
 * @param v 
 * @param index 
 * @param value 
 * @return void* 
 */
void*  vector_set(Vector  v,uint32_t index,void* value){
  if(v == NULL) return NULL;
  
  if(index>=((vector_t*)v)->size) return NULL;
   
  void* returned = ((vector_t*)v)->v[index];
  ((vector_t*)v)->v[index] = value;
  return returned; 
}

/**
 * @brief adds an element at the end of a vector. Returns true if the element was added and false otherwise.
 * 
 * @param v 
 * @param value 
 * @return true 
 * @return false 
 */
bool vector_add(Vector  v,void* value){
  if(v == NULL) return false;
  
  if(!((vector_t*)v)->is_dynamic && ((vector_t*)v)->size  == ((vector_t*)v)->max_size) return false;
 
  ((vector_t*)v)->size++;

  if(((vector_t*)v)->is_dynamic && ((vector_t*)v)->size == ((vector_t*)v)->current_size_dynamic){
       
      ((vector_t*)v)->current_size_dynamic += INIT_SIZE_DYNAMIC; 

      ((vector_t*)v)->v = (void**) realloc(((vector_t*)v)->v,((vector_t*)v)->current_size_dynamic * sizeof(void*));
  
  }
  
  ((vector_t*)v)->v[((vector_t*)v)->size-1] = value;

  return true;
}

/**
 * @brief Insert an element at the specified index. Returns true if the element was added and false otherwise.
 * 
 * @param v 
 * @param index 
 * @param value 
 * @return true 
 * @return false 
 */
bool vector_insert(Vector  v,uint32_t index,void* value){
  if(v == NULL) return false;

  if(!((vector_t*)v)->is_dynamic && ((vector_t*)v)->size == ((vector_t*)v)->max_size) return false;

  if(index > ((vector_t*)v)->size) return false;

  ((vector_t*)v)->size++;

  if(((vector_t*)v)->is_dynamic && ((vector_t*)v)->size == ((vector_t*)v)->current_size_dynamic){
      
      ((vector_t*)v)->current_size_dynamic += INIT_SIZE_DYNAMIC;

      ((vector_t*)v)->v = (void**) realloc(((vector_t*)v)->v,((vector_t*)v)->current_size_dynamic * sizeof(void*));
    
  }
 
  for(uint32_t i = ((vector_t*)v)->size-1; i>index;i--){

       ((vector_t*)v)->v[i] = ((vector_t*)v)->v[i-1];
    
  } 
    
  ((vector_t*)v)->v[index] = value;

  return true;
}


/**
 * @brief Removes the element in the index position. Returns the deleted element. 
 * 
 * @param v 
 * @param index 
 * @return void* 
 */
void* vector_remove(Vector v,uint32_t index){
  if(v == NULL) return NULL;
  
  if(vector_isempty(v)) return NULL;

  if(index >= ((vector_t*)v)->size) return NULL;

  void* returned = ((vector_t*)v)->v[index];
  
  ((vector_t*)v)->size--;
  
  for(uint32_t i = index; i<((vector_t*)v)->size ;i++){
    ((vector_t*)v)->v[i] = ((vector_t*)v)->v[i+1];
  }

  if(((vector_t*)v)->is_dynamic &&   ((vector_t*)v)->current_size_dynamic - ((vector_t*)v)->size == INIT_SIZE_DYNAMIC){

    ((vector_t*)v)->current_size_dynamic -= INIT_SIZE_DYNAMIC;
    
    ((vector_t*)v)->v = (void**) realloc(((vector_t*)v)->v,((vector_t*)v)->current_size_dynamic *sizeof(void*));  

  }

  return returned;
}
 

/**
 * @brief Selection sort algorithm for vector.
 * 
 * @param v 
 * @param compare 
 */
void  vector_select_sort(Vector v,int (*compare)(void*,void*)){
  if(v == NULL) return;

  uint32_t size = ((vector_t*)v)->size;

  for(;size>0;size--){

    for(uint32_t i=0;i<size;i++){

      if(compare(((vector_t*)v)->v[size-1],((vector_t*)v)->v[i])<0){
        void* auxiliar = ((vector_t*)v)->v[size-1];
        ((vector_t*)v)->v[size-1] = ((vector_t*)v)->v[i];
        ((vector_t*)v)->v[i] = auxiliar;
      }

    }

  }
}   

/**
 * @brief Insertion sort algorithm for vector.
 * 
 * @param v 
 * @param compare 
 */
void  vector_insert_sort(Vector v,int (*compare)(void*,void*)){
  if(v == NULL) return;
  
   for(int i=1;i<((vector_t*)v)->size;i++){
    
    if(compare(((vector_t*)v)->v[i],((vector_t*)v)->v[i-1])<0){
      int j = i-1;
      void* auxiliar = ((vector_t*)v)->v[j+1];
      
      while(j>=0 && compare(auxiliar,((vector_t*)v)->v[j])<0){
        ((vector_t*)v)->v[j+1]=((vector_t*)v)->v[j];
        j--;
      }

      ((vector_t*)v)->v[j+1]=auxiliar;
    }

  }

}

/**
 * @brief Bubble sort algorithm for vector.
 * 
 * @param v 
 * @param compare 
 */
void  vector_bubble_sort(Vector v,int (*compare)(void*,void*)){
  if(v == NULL) return;

  uint32_t size = ((vector_t*)v)->size;

  for(;size>0;size--){
    
    for(int i=1;i<size;i++){

      if(compare(((vector_t*)v)->v[i],((vector_t*)v)->v[i-1])<0){
        void* auxiliar  = ((vector_t*)v)->v[i];
        ((vector_t*)v)->v[i] = ((vector_t*)v)->v[i-1];
        ((vector_t*)v)->v[i-1]=auxiliar;
      }

    }

  }
}

/**
 * @brief Quick sort algorithm for vector.
 * 
 * @param v 
 * @param compare 
 */
void vector_quick_sort(Vector  v,int (*compare)(void*,void*)){
  if(v == NULL) return;

  _quick_sort(&((vector_t*)v)->v[0],&((vector_t*)v)->v[((vector_t*)v)->size-1],compare);
}


void _quick_sort(void** start,void** end,int(*compare)(void*,void*)){
  if(start<end){
    
    void** left = start;
    void** right = end;
    void* aux = *left;
    
    while(left<right){
      
      while((left<right) && (compare(aux,*right)<0)){
        right--;
      }

      if(left<right){
        *left = *right;
        left++;
      }

      while((left<right) && (compare(aux,*left)>0)){
        left++;
      }

      if(left<right){
        *right=*left;
        right--;
      }

    }
    *left = aux;
    _quick_sort(start,left-1,compare);
    _quick_sort(left+1,end,compare);

  }
}

/**
 * @brief Merge sort algorithm for vector.
 * 
 * @param v 
 * @param compare 
 */
void  vector_merge_sort(Vector v,int (*compare)(void*,void*)){
  if(v == NULL) return;

  merge_sort(v,0,((vector_t*)v)->size-1,compare);
}



void merge_sort(vector_t* v,uint32_t start,uint32_t end,int(*compare)(void*,void*)){
  if(start < end){
    uint32_t middle = round((start+end)/2);
    merge_sort(v,start,middle,compare);
    merge_sort(v,middle+1,end,compare);
    _merge(v,start,middle,end,compare);
  }
}

void _merge(vector_t* v,uint32_t start,uint32_t middle,uint32_t end,int(*compare)(void*,void*)){
  uint32_t size_1 = middle-start+1;
  uint32_t size_2 = end-middle;
  void* array_left[size_1];
  void* array_right[size_2];

  for(uint32_t i=0;i<size_1;i++){
    array_left[i]=v->v[end+i];
  }
  
  for(int j=0;j<size_2;j++){
    array_right[j]=v->v[middle+1+j];
  }
  
  int i=0;
  int j=0;
  int k=end;

  while(i<size_1 && j<size_2){
    
    if(compare(array_left[i],array_right[j])<=0){
      v->v[k]=array_left[i];
      i++;
    }
    else{
      v->v[k]=array_right[j];
      j++;
    }

    k++;
  }

  while (i < size_1) {
    v->v[k]=array_left[i];
    i++;
    k++;
  }

  while (j < size_2) {
    v->v[k]=array_right[j];
    j++;
    k++;
  }
}


/**
 * @brief Shell sort algorithm for vector.
 * 
 * @param v 
 * @param compare 
 */
void  vector_shell_sort(Vector v,int (*compare)(void*,void*)){
  if(v == NULL) return;

  for(uint32_t interval = ((vector_t*)v)->size/2;interval > 0;interval /= 2){
    
    for (uint32_t i = interval; i < ((vector_t*)v)->size; i += 1) {
      
      void* auxiliar = ((vector_t*)v)->v[i];
      int j;
      
      for (j = i; j >= interval && compare(((vector_t*)v)->v[j-interval],auxiliar) > 0; j -= interval) {
        ((vector_t*)v)->v[j]=((vector_t*)v)->v[j-interval];
      }

      ((vector_t*)v)->v[j]=auxiliar;
    }

  }
}

/**
 * @brief Sequential search sort algorithm for vector.
 * 
 * @param v 
 * @param value 
 * @param compare 
 * @return uint32_t 
 */
uint32_t  vector_sequential_search(Vector v,void* value,int (*compare)(void*,void*)){
  uint32_t returned = 0;
  
  while(returned<((vector_t*)v)->size && compare(((vector_t*)v)->v[returned],value)){
    returned++;
  }

  return returned;
}


/**
 * @brief Binary search sort algorithm for vector.
 * 
 * @param v 
 * @param value 
 * @param compare 
 * @return uint32_t 
 */
uint32_t  vector_binary_search(Vector v,void* value,int (*compare)(void*,void*)){
  uint32_t lower = 0;
  uint32_t higher = ((vector_t*)v)->size-1;
  uint32_t returned = (lower+higher)/2;
  
  while(lower < higher && compare(((vector_t*)v)->v[returned],value)){
    
    if(compare(((vector_t*)v)->v[returned],value)<0){
      lower = returned + 1;
    }
    else{
      higher = returned - 1;
    }

    returned = (lower+higher)/2;
  }

  return (!compare(((vector_t*)v)->v[returned],value))? returned:((vector_t*)v)->size;
}


/**
 * @brief This procedure is a way to implement a generic function pointer. With this procedure it is posible
 * to implement many kind of operation with the vector.
 * 
 * @param v 
 * @param vector_do 
 * @param context 
 */
void  vector_traverse(Vector v,bool vector_do(void*,void*,uint32_t),void* context){
  if(v == NULL) return;

  uint32_t counter = 0;

  while(counter < ((vector_t*)v)->size  && vector_do(((vector_t*)v)->v[counter],context,counter)){
    counter++;
  }
}






























