#include "my_functions.c"
#include <stdio.h>

int *do_conversion(int number, int size_of_input)
{
    int *arr = malloc(sizeof(int) * size_of_input);
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    convert_positive_decimal_number_to_binary(number, arr, size_of_input);

    return arr;
}


void free_array(int *arr)
{
    free(arr);
}

