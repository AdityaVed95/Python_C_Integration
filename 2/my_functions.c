// Created by Aditya Ved on 12/09/22.
//

// MAX_BITS_SIZE is the number of bits on which the operation is to be performed

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// all the below functions are meant to deal with an array or any data structure in which data is stored in contiguous memory locations
// they were created with arrays in mind

void convert_positive_decimal_number_to_binary(int , int *,int );
void convert_negative_decimal_number_to_binary(int, int *,int); // uses twos_complement_trick function internally
void ones_complement(int *, int *, int);
void binary_addition(int * , int *, int * , int);
int right_shift(int *,int *, int);
void twos_complement_trick(int *, int * , int );
void binary_subtraction(int *, int * , int *, int);
void convert_positive_or_negative_binary_number_to_decimal(int *, int *, int );
int convert_positive_binary_number_to_decimal(int * , int);
void left_shift(int *, int *, int);
void display_integer_binary_number_array(int *,int );

void convert_positive_decimal_number_to_binary(int decimal_input, int * ptr_to_binary_number,int MAX_BITS_SIZE) // converts +ve nos to binary
{

    int quotient=10,remainder; // 10 is just taken as a random number
    int copy_of_decimal_input= decimal_input;
    int i=MAX_BITS_SIZE-1;

    while (quotient != 0)
    {
        quotient=copy_of_decimal_input/2;
        remainder = copy_of_decimal_input%2;
        *(ptr_to_binary_number+i) = remainder;
        copy_of_decimal_input = quotient;
        i--;
    }
    int k;
    for(k=i;k>=0;k--)
    {
        *(ptr_to_binary_number+k) = 0;
    }
}

void ones_complement(int * ptr_to_binary_number, int * ptr_to_ones_complement_of_binary_number, int MAX_BITS_SIZE)

{
    int i;
    for(i=0;i<MAX_BITS_SIZE;i++)
    {
        if(*(ptr_to_binary_number+i) == 0)
        {
            *(ptr_to_ones_complement_of_binary_number+i) = 1;
        }

        if(*(ptr_to_binary_number+i) == 1)
        {
            *(ptr_to_ones_complement_of_binary_number+i) = 0;
        }
    }
}


void binary_addition(int * ptr_to_1st_binary_number,int * ptr_to_2nd_binary_number , int * ptr_to_final_sum , int MAX_BITS_SIZE )
{
    int i;
    int carry=0;
    int bit1,bit2;
    int sum;


    // simulating serial adder containing n number of 1 bit full adder
    // n = MAX_BITS_SIZE

    for(i=MAX_BITS_SIZE-1;i>=0;i--)
    {
        bit1 = *(ptr_to_1st_binary_number+i);
        bit2 = *(ptr_to_2nd_binary_number+i);

        // algorithms for 1 bit full adder
        // algorithm for sum
        if( (bit1 == 1 && bit2 == 1 && carry == 1) || (bit1 == 1 && bit2 == 0 && carry == 0) || (bit1 == 0 && bit2 == 1 && carry == 0) || (bit1 == 0 && bit2 == 0 && carry == 1))
        {
            sum = 1;
            *(ptr_to_final_sum+i) = sum;
        }
        else
        {
            sum = 0;
            *(ptr_to_final_sum+i) = sum;
        }

        // algorithm for carry
        if((bit1 == 1 && bit2 == 1)  ||  (bit1 == 1 && carry == 1)  ||  (bit2 == 1 && carry == 1))
        {
            carry = 1;
        }
        else
        {
            carry = 0;
        }
    }

//    printf("Carry is : %d\n",carry);
//    the carry generated in the last step has to be ignored because there is no space left in the array to accomodate it , and thus it is not significant

}

int right_shift(int *ptr_to_binary_number, int * ptr_to_right_shifted_binary_number , int MAX_BITS_SIZE)
{

    ptr_to_right_shifted_binary_number[0] = ptr_to_binary_number[0];
    for(int i=0;i<MAX_BITS_SIZE-1;i++)
    {
        ptr_to_right_shifted_binary_number[i + 1] = ptr_to_binary_number[i];
    }
    return ptr_to_binary_number[MAX_BITS_SIZE-1];
    // this function return the right most bit which is not going to be in the right_shifted_binary_number

}

void twos_complement_trick(int * ptr_to_original_binary_number, int * ptr_to_twos_complement_of_binary_number, int MAX_BITS_SIZE)
{
    int i;
    int flag = 0;
    for(i=MAX_BITS_SIZE-1;i>=0;i--)
    {
        if(flag == 0)
        {
            if(*(ptr_to_original_binary_number+i) == 1)
            {
                *(ptr_to_twos_complement_of_binary_number+i) = 1;
                flag = 1;
            }
            else if (*(ptr_to_original_binary_number+i) == 0)
            {
                *(ptr_to_twos_complement_of_binary_number+i) = 0;
            }

        }

        else if (flag == 1)
        {
            if(*(ptr_to_original_binary_number+i) == 0)
            {
                *(ptr_to_twos_complement_of_binary_number+i) = 1;
            }

            else if (*(ptr_to_original_binary_number+i) == 1)
            {
                *(ptr_to_twos_complement_of_binary_number+i) = 0;
            }
        }
    }
}


void convert_negative_decimal_number_to_binary(int negative_num, int * ptr_to_binary_number, int MAX_BITS_SIZE )
{
    int positive_num = abs(negative_num);
    int binary_of_corresponding_positive_number[MAX_BITS_SIZE];
    convert_positive_decimal_number_to_binary(positive_num,&(binary_of_corresponding_positive_number[0]),MAX_BITS_SIZE);
    // now we have to find 2's complement of binary_of_corresponding_positive_number to get
    // the binary pattern of actual negative number
    twos_complement_trick(&(binary_of_corresponding_positive_number[0]),ptr_to_binary_number, MAX_BITS_SIZE);

}


void binary_subtraction(int * ptr_to_1st_binary_number, int *ptr_to_2nd_binary_number , int *ptr_to_difference_binary_number , int MAX_BITS_SIZE)
{
    // difference_binary_number store  1st_binary_number - 2nd_binary_number
    // 1st bin is accumulator
    // 2nd bin is multiplicand
    int twos_complement_of_2nd_binary_number[MAX_BITS_SIZE];
    twos_complement_trick(ptr_to_2nd_binary_number,&(twos_complement_of_2nd_binary_number[0]),MAX_BITS_SIZE);
    // here the twos_complement_of_2nd_binary_number actually holds the value of 2's complement
    // of 2nd binary number

    binary_addition(ptr_to_1st_binary_number,&(twos_complement_of_2nd_binary_number[0]),ptr_to_difference_binary_number,MAX_BITS_SIZE);

}


void convert_positive_or_negative_binary_number_to_decimal(int *ptr_to_binary_number , int *ptr_to_decimal_number , int MAX_BITS_SIZE)
{
    if(*(ptr_to_binary_number) == 1)
    {
        // number is negative
        int binary_twos_complement_number[MAX_BITS_SIZE];
        twos_complement_trick(ptr_to_binary_number,&(binary_twos_complement_number[0]), MAX_BITS_SIZE);
        int positive_num = convert_positive_binary_number_to_decimal(binary_twos_complement_number,MAX_BITS_SIZE);
        int negative_num = -positive_num;
        *(ptr_to_decimal_number) = negative_num;
    }

    else
    {
        // number is positive
        *(ptr_to_decimal_number) = convert_positive_binary_number_to_decimal(ptr_to_binary_number,MAX_BITS_SIZE);

    }
}


int convert_positive_binary_number_to_decimal(int *ptr_to_binary_number , int MAX_BITS_SIZE)
{
    int count = (MAX_BITS_SIZE)-1;
    int sum=0;
    for(int i=0;i<MAX_BITS_SIZE;i++)
    {
        sum = sum + (pow(2,count)*(*(ptr_to_binary_number+i)));
        count--;
    }
    return sum;
}



void left_shift(int *ptr_to_binary_number, int * ptr_to_left_shifted_binary_number , int MAX_BITS_SIZE)
{
    // does the left shift of a number and then after that the right most bit
    // is intialised to 5 to indicate that it is garbage value and it will soon be replaced
    // at a particular point in the program

    int i;
    ptr_to_left_shifted_binary_number[MAX_BITS_SIZE-1] = 5;

    for(i=0;i<MAX_BITS_SIZE-1;i++)
    {
        ptr_to_left_shifted_binary_number[i] = ptr_to_binary_number[i+1];
    }

}

void display_integer_binary_number_array(int *ptr_to_binary_number,int MAX_BITS_SIZE)
{
    for(int i=0;i<MAX_BITS_SIZE;i++)
    {
        printf("%d",ptr_to_binary_number[i]);
    }
    printf("\n");
}