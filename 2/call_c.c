#include "my_functions.c"
#include <stdio.h>

int main(int number)
{

    int size_of_input = 10;
    int arr[size_of_input];
    convert_positive_decimal_number_to_binary(number,arr,size_of_input);
    for (int i = 0; i < size_of_input; i++)
    {
        printf("%d",arr[i]);
    }

}