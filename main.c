#define VEC_IMPLEMENTATION
#include "src/vec.h"

#include <stdio.h>

int main() {
    int *my_vector = vec_new(); // Create a new vector.
    
    vec_push(my_vector, 10); // Append an element.
    vec_push(my_vector, 20); // Append another element.
   
	int value = my_vector[0];
    // int value = vec_get(my_vector, 0); // Get the first element.
	printf("%d\n", value);
    
    vec_delete(my_vector, 1); // Delete the second element.
    
    vec_free(my_vector); // Free the vector.
    return 0;
}
