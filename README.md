<h1>TDA VECTOR</h1>
<div>
  This is a template implementation of a Vector structure wich is based on array data structure. It provides certain amount 
  of functions and procedures for his easy manipulation. This template allows to using any kind of data type as his 
  arguments wich make it very versatile. It has many ways of use. The objective of this template is an abstraction of the
  simple array that language c provides.
</div>

<div>
  <h2>These are the procedures and functions prototypes that TDA VECTOR provides:</h2>
</div>

<div>
  <h3><pre>Vector   vector_new_void(void) </pre> </h3>

  <h3><pre>Vector   vector_new(uint32_t maxsize) </pre> </h3>

  <h3><pre>void     vector_free(Vector v) </pre> </h3>

  <h3><pre>uint32_t vector_size(Vector  v)</pre> </h3>

  <h3><pre>bool     vector_isempty(Vector  v)</pre> </h3>

  <h3><pre>void*    vector_get(Vector  v,uint32_t index)</pre> </h3>

  <h3><pre>void*    vector_set(Vector  v,uint32_t index,void* value)</pre> </h3>

  <h3><pre>bool     vector_add(Vector  v,void* value)</pre> </h3>

  <h3><pre>bool     vector_insert(Vector  v,uint32_t index,void* value)</pre> </h3>

  <h3><pre>void*    vector_remove(Vector v,uint32_t index)</pre></h3>

  <h3><pre>void     vector_select_sort(Vector v,int (*compare)(void*,void*))</pre></h3>

  <h3><pre>void     vector_insert_sort(Vector v,int (*compare)(void*,void*))</pre></h3>

  <h3><pre>void     vector_bubble_sort(Vector v,int (*compare)(void*,void*))</pre></h3>

  <h3><pre>void     vector_bubble_sort_improved(Vector v,int (*compare)(void*,void*))</pre></h3>

  <h3><pre>void     vector_quick_sort(Vector  v,int (*compare)(void*,void*))</pre></h3>

  <h3><pre>void     vector_merge_sort(Vector v,int (*compare)(void*,void*))</pre></h3>

  <h3><pre>void     vector_shell_sort(Vector v,int (*compare)(void*,void*))</pre></h3>

  <h3><pre>uint32_t vector_sequential_search(Vector v,void* value,int (*compare)(void*,void*))</pre></h3>

  <h3><pre>uint32_t vector_binary_search(Vector v,void* value,int (*compare)(void*,void*))</pre></h3>

  <h3><pre>void     vector_traverse(Vector v,bool vector_do(void*,void*,uint32_t),void* context)</pre></h3>
 </div>

<div>
  <p>In the main.c file there are some examples of how you can use this template.</p>
</div>


