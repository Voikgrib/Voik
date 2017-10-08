
#include<stdio.h>
#include<assert.h>
#include<string.h>

typedef int data_type;

const long int Max_size_of_my_stack = 666;
const int Poizon_num = '\0';
const int Push = 1;
const int Pop = 2;
const int Add = 3;
const int Mul = 4;
const int Sub = 5;
const int Div = 6;
const int End = 0;

int Err_code = 0;

data_type stack_pop(struct s_my_stack *my_stack);
int is_stack_ok(struct s_my_stack *my_stack);

void stack_add(struct s_my_stack *my_stack);
void stack_construct(struct s_my_stack *my_stack);
void stack_push(struct s_my_stack *my_stack, data_type num);
void stack_mul(struct s_my_stack *my_stack);
void stack_sub(struct s_my_stack *my_stack);
void stack_div(struct s_my_stack *my_stack);
void com_cleaner(char* command, int com_size);
void err_print(void);

//!------------------------------------------------------------------------------------------
//! Declare structure s_my_stack
//!
//! @param char data[] - massif with stack data
//! @param int counter - pointer on current pozition
//!------------------------------------------------------------------------------------------
struct s_my_stack
{
    char data [Max_size_of_my_stack];
    int counter;
};

//!------------------------------------------------------------------------------------------
//! This program contains stack and some function with it
//!
//! Author: Vladimir Gribanov
//!------------------------------------------------------------------------------------------
int main()
{
    FILE *compile = fopen("compile.txt","rt");

    int command_num = -1 ;
    data_type num = 0;

    struct s_my_stack stack_1;

    printf("Stack created!\n");

    stack_construct(&stack_1);

    while(command_num != End)
    {
        fscanf(compile, "%d", &command_num);

        if(command_num == Push)
        {
            fscanf(compile, "%d", &num);
            stack_push(&stack_1, num);
        }
        else if(command_num == Pop)
        {
            num = stack_pop(&stack_1);
            printf("num = %d \n", num);
        }
        else if(command_num == Add)
        {
            stack_add(&stack_1);
        }
        else if(command_num == Mul)
        {
            stack_mul(&stack_1);
        }
        else if(command_num == Sub)
        {
            stack_sub(&stack_1);
        }
        else if(command_num == Div)
        {
            stack_div(&stack_1);
        }

        if(Err_code != 0)
        {
            err_print();
            Err_code = 0;
        }
    }

    fclose(compile);
    return Err_code;
}

//!------------------------------------------------------------------------------------------
//! This function initialize stack: fulls data[] = {}, set counter = 0
//!
//! @param[in] struct s_my_stack *my_stack - stack which will be initialized
//!
//! @note Error codes 6 - if memory or pointer error before construct
//!                   7 - if memory or pointer error after construct
//!------------------------------------------------------------------------------------------
void stack_construct(struct s_my_stack *my_stack)
{
    int i = 0;

    my_stack->counter = 0;

    if(is_stack_ok(my_stack) == -1)
        Err_code = 6;

    while(i != Max_size_of_my_stack)
    {
        my_stack->data[i] = 0;
        i++;
    }

    if(is_stack_ok(my_stack) == -1)
        Err_code = 7;

}

//!------------------------------------------------------------------------------------------
//! This function put number in stack
//!
//! @param[in] struct s_my_stack *my_stack - stack we are working on
//! @param[in] int num - number which will be put in stack
//!
//! @note Error codes 1 - if stack is full
//!                   2 - memory or pointer error before push
//!                   3 - memory or pointer error after push
//!------------------------------------------------------------------------------------------
void stack_push(struct s_my_stack *my_stack, data_type num)
{
    if(is_stack_ok(my_stack) == -1)
        Err_code = 2;

    if(my_stack->counter != Max_size_of_my_stack)
    {
        my_stack->data[my_stack->counter] = num;
        my_stack->counter++;
    }
    else
    {
        Err_code = 1;
    }

    if(is_stack_ok(my_stack) == -1)
        Err_code = 3;
}

//!------------------------------------------------------------------------------------------
//! This function get number from stack
//!
//! @param[in] struct s_my_stack *my_stack - stack we are working on
//!
//! @note Error codes 4 - memory or pointer error before pop
//!                   5 - memory or pointer error after pop
//!                   -1 - stack is empty
//!
//! @param[out] data_type num - number (or something) from stuck
//!------------------------------------------------------------------------------------------
data_type stack_pop(struct s_my_stack *my_stack)
{
    int num = 0;

    if(is_stack_ok(my_stack) == -1)
        return 4;

    if(my_stack->counter > 0)
    {
        num = my_stack->data[--my_stack->counter];
        my_stack->data[my_stack->counter] = Poizon_num;
        return num;

    }
    else if(is_stack_ok(my_stack) <= -1)
    {
        Err_code = 5;
        return -1;
    }
    else
    {
        Err_code = -1;
        return -1;
    }


}

//!------------------------------------------------------------------------------------------
//! This function pick two numbers from stack and do num 2 + num 1, and pop answer
//!
//! @param[in] struct s_my_stack *my_stack - stack we are working on
//!
//! @note Error codes 14 - memory or pointer error before mul
//!                   15 - memory or pointer error after mul
//!------------------------------------------------------------------------------------------
void stack_mul(struct s_my_stack *my_stack)
{
    if(is_stack_ok(my_stack) == -1)
        Err_code = 14;

    data_type fir_num = stack_pop(my_stack);
    data_type sec_num = stack_pop(my_stack);

    stack_push(my_stack, sec_num * fir_num);

    if(is_stack_ok(my_stack) == -1)
        Err_code = 15;
}

//!------------------------------------------------------------------------------------------
//! This function pick two numbers from stack and do num 2 - num 1, and pop answer
//!
//! @param[in] struct s_my_stack *my_stack - stack we are working on
//!
//! @note Error codes 13 - memory or pointer error before sub
//!                   12 - memory or pointer error after sub
//!------------------------------------------------------------------------------------------
void stack_sub(struct s_my_stack *my_stack)
{
    if(is_stack_ok(my_stack) == -1)
        Err_code = 13;

    data_type fir_num = stack_pop(my_stack);
    data_type sec_num = stack_pop(my_stack);

    stack_push(my_stack, sec_num - fir_num);

    if(is_stack_ok(my_stack) == -1)
        Err_code = 12;
}

//!------------------------------------------------------------------------------------------
//! This function pick two numbers from stack and do num 2 / num 1, and pop answer
//!
//! @param[in] struct s_my_stack *my_stack - stack we are working on
//!
//! @note Error codes 10 - memory or pointer error before div
//!                   11 - memory or pointer error after div
//!                   100 - if num 1 / 0
//!------------------------------------------------------------------------------------------
void stack_div(struct s_my_stack *my_stack)
{
    if(is_stack_ok(my_stack) == -1)
        Err_code = 10;

    data_type fir_num = stack_pop(my_stack);
    data_type sec_num = stack_pop(my_stack);

    if(sec_num == 0)
    {
        Err_code = 100;
        return;
    }

    stack_push(my_stack, sec_num / fir_num);

    if(is_stack_ok(my_stack) == -1)
        Err_code = 11;
}

//!------------------------------------------------------------------------------------------
//! This function pick two numbers from stack and do num 2 * num 1, and pop answer
//!
//! @param[in] struct s_my_stack *my_stack - stack we are working on
//!
//! @note Error codes 8 - memory or pointer error before add
//!                   9 - memory or pointer error after add
//!------------------------------------------------------------------------------------------
void stack_add(struct s_my_stack *my_stack)
{
    if(is_stack_ok(my_stack) == -1)
        Err_code = 8;

    data_type fir_num = stack_pop(my_stack);
    data_type sec_num = stack_pop(my_stack);

    stack_push(my_stack, sec_num + fir_num);

    if(is_stack_ok(my_stack) == -1)
        Err_code = 9;
}


//!------------------------------------------------------------------------------------------
//! This function prints error messages about last error
//!
//! @param Err_code - code of last error
//!------------------------------------------------------------------------------------------
void err_print()
{
    if(Err_code == -1)
        printf("!!!  ERROR_PRINT - STACK_IS_EMPTY  (Err_code = %d) !!!\n\n", Err_code);
    else if(Err_code == 1)
        printf("!!!  ERROR_PRINT - END_OF_MEMORY  (Err_code = %d) !!!\n\n", Err_code);
    else if(Err_code == 2)
        printf("!!!  ERROR_PRINT - ERROR_IN_PUSH_START  (Err_code = %d) !!!\n\n", Err_code);
    else if(Err_code == 3)
        printf("!!!  ERROR_PRINT - ERROR_IN_PUSH_END  (Err_code = %d) !!!\n\n", Err_code);
    else if(Err_code == 4)
        printf("!!!  ERROR_PRINT - ERROR_IN_POP_START  (Err_code = %d) !!!\n\n", Err_code);
    else if(Err_code == 5)
        printf("!!!  ERROR_PRINT - ERROR_IN_PUSH_END  (Err_code = %d) !!!\n\n", Err_code);
    else if(Err_code == 6)
        printf("!!!  ERROR_PRINT - ERROR_IN_CREATE_STACK_START  (Err_code = %d) !!!\n\n", Err_code);
    else if(Err_code == 7)
        printf("!!!  ERROR_PRINT - ERROR_IN_CREATE_STACK_END  (Err_code = %d) !!!\n\n", Err_code);
    else if(Err_code == 8)
        printf("!!!  ERROR_PRINT - ERROR_IN_ADD_START  (Err_code = %d) !!!\n\n", Err_code);
    else if(Err_code == 9)
        printf("!!!  ERROR_PRINT - ERROR_IN_ADD_END (Err_code = %d) !!!\n\n", Err_code);
    else if(Err_code == 10)
        printf("!!!  ERROR_PRINT - ERROR_IN_DIV_START  (Err_code = %d) !!!\n\n", Err_code);
    else if(Err_code == 11)
        printf("!!!  ERROR_PRINT - ERROR_IN_DIV_END  (Err_code = %d) !!!\n\n", Err_code);
    else if(Err_code == 12)
        printf("!!!  ERROR_PRINT - ERROR_IN_SUB_END  (Err_code = %d) !!!\n\n", Err_code);
    else if(Err_code == 13)
        printf("!!!  ERROR_PRINT - ERROR_IN_SUB_START  (Err_code = %d) !!!\n\n", Err_code);
    else if(Err_code == 14)
        printf("!!!  ERROR_PRINT - ERROR_IN_MUL_START  (Err_code = %d) !!!\n\n", Err_code);
    else if(Err_code == 15)
        printf("!!!  ERROR_PRINT - ERROR_IN_MUL_END  (Err_code = %d) !!!\n\n", Err_code);
    else if(Err_code == 100)
        printf("!!!  ERROR_PRINT - ERROR_IN_DIV I cann't do num / 0  (Err_code = %d) !!!\n\n", Err_code);
    else if(Err_code != 0)
        printf("!!! UNKNOWN_ERROR (Err_code = %d) !!!\n\n", Err_code);

}

//!------------------------------------------------------------------------------------------
//! This function check stack for errors
//!
//! @param[in] struct s_my_stack *my_stack - stack which we check
//!------------------------------------------------------------------------------------------
int is_stack_ok(struct s_my_stack *my_stack)
{
    if(my_stack &&
       my_stack->counter <= Max_size_of_my_stack &&
       my_stack->counter >= 0 &&
       my_stack->data)
        return 0;
    else
        return -1;
}
