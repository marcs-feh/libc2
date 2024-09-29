#include "generic.h"
#include "prelude.h"
#include "memory.h"

/* Arg check */
#if !defined(container_name) || !defined(container_type_param)
#error "Missing container_name and/or container_type_param"
#endif
#if !defined(container_prefix)
#define container_prefix M_EXP(container_name)
#endif
#define container_func(name) M_GLUE(container_prefix, _##name)
typedef struct container_name container_name;
#define generic_func static inline

/* Private macros */
#define Dyn_Array M_EXP(container_name)
#define T         M_EXP(container_type_param)

struct Dyn_Array {
	T* data;
	isize len;
	isize cap;
	Mem_Allocator allocator;
};

generic_func
bool container_func(init)(Dyn_Array* arr, Mem_Allocator allocator, isize initial_cap){
	T* data = NULL;
	if(initial_cap > 0){
		data = mem_alloc(allocator, sizeof(T) * initial_cap, alignof(T));
		if(!data){ return false; }
	}
	arr->data = data;
	arr->cap = initial_cap;
	arr->len = 0;
	arr->allocator = allocator;
	return true;
}

generic_func
void container_func(destroy)(Dyn_Array* arr){
	mem_free(arr->allocator, arr->data);
	arr->data = NULL;
}

generic_func
bool container_func(resize)(Dyn_Array* arr, isize new_cap){
	T* new_data = mem_alloc(arr->allocator, sizeof(T) * new_cap, alignof(T));
	if(!new_data){ return false; }

	isize new_len = min(new_cap, arr->len);
	mem_copy(new_data, arr->data, new_len * sizeof(T));
	arr->cap = new_cap;
	arr->len = new_len;

	mem_free(arr->allocator, arr->data);
	arr->data = new_data;
	return true;
}

generic_func
bool container_func(append)(Dyn_Array* arr, T elem){
	if(arr->len >= arr->cap){
		isize new_size = align_forward_size(1 + (arr->len * 2), 16);
		if(!container_func(resize)(arr, new_size)){
			return false;
		}
	}

	arr->data[arr->len] = elem;
	arr->len += 1;
	return true;
}

#undef Dyn_Array
#undef T
#undef container_name
#undef container_type_param
#undef container_prefix
#undef container_func
#undef generic_func
