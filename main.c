#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Vector.h"

// these are examples of how to use the vector structure

int compare(void* val_a,void* val_b);

void _delete_all_same_element_from_index(Vector vector,uint32_t starting_index,void* value,int compare(void*,void*));
void _delete_all_repeated_element(Vector vector,int compare(void*,void*),uint32_t size);
void delete_all_repeated_elements(Vector vector,int compare(void*,void*));


int main(void){
   
  srand(time(NULL));

  Vector new_vector = vector_new_void(); // generates a new dynamic vector  

  
  // insert 50 random elements
  for(uint32_t i = 0 ; i <50 ; i++){
     
    int* element = (int*) malloc(sizeof(int));
    *element = rand()%50;
    vector_add(new_vector,element); 

  }


  //print the 50 element (you could create a procedure with this purpose)
   for(uint32_t i = 0 ; i <50 ; i++){
     
    printf("%2d  ",*(int*)vector_get(new_vector,i));

  }

  //sort the elements of the vector from smallest to largest (you could use anyone of the sort functions that the
  //this template supports)
  // in this case i will use quick sort
  
  vector_quick_sort(new_vector,compare);
   
  printf("\n\n");

  //print again the 50 element 
  for(uint32_t i = 0 ; i <50 ; i++){
     
    printf("%2d  ",*(int*)vector_get(new_vector,i));

  }
  

  //now i will delete the repeated elemets
  
  delete_all_repeated_elements(new_vector,compare);  

  // print again all elements
  
  printf("\n");

  for(uint32_t i = 0 ; i <vector_size(new_vector) ; i++){
     
    printf("%2d  ",*(int*)vector_get(new_vector,i));

  }

  // free the memory of the vector

  while(!vector_isempty(new_vector)){
    void* removed = vector_remove(new_vector,0);
    free(removed);
  }

  vector_free(new_vector);

  return 0;      
}



int compare(void* val_a,void* val_b){
  return (*(int*)val_a - *(int*)val_b);
}





void _delete_all_same_element_from_index(Vector vector,uint32_t starting_index,void* value,int compare(void*,void*)){
  if(starting_index >= vector_size(vector)-1) return;
  
  for(uint32_t i = starting_index; i<vector_size(vector);i++){ 
     
     if(compare(vector_get(vector,i),value) == 0){
       
       int* removed = vector_remove(vector,i);
       
       if(removed != NULL) free(removed);

       i--;
     }

  }
}


void _delete_all_repeated_element(Vector vector,int compare(void*,void*),uint32_t size){
   if(size < vector_size(vector)){
      _delete_all_same_element_from_index(vector,size+1,vector_get(vector,size),compare);
      _delete_all_repeated_element(vector,compare,size+1);
   }
}


//example of a recursive function for delete all the repeated elements
void delete_all_repeated_elements(Vector vector,int compare(void*,void*)){
   _delete_all_repeated_element(vector,compare,0);
} 