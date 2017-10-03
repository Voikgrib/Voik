
#include<stdio.h>
#include<assert.h>
#include<string.h>

typedef int data_type;

const long int Max_size_of_my_stack = 666;
const int Poizon_num = '\0';

int Err_code = 0;

data_type my_pop(struct s_my_stack *my_stack);
int is_stack_ok(struct s_my_stack *my_stack);

void stack_construct(struct s_my_stack *my_stack);
void my_push(struct s_my_stack *my_stack, data_type num);
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
    const int max_comm_lenght = 100;

    char cur_command[max_comm_lenght] = {0};
    data_type num = 0;

    struct s_my_stack stack_1;

    printf("Stack created!\n");

    stack_construct(&stack_1);

    while(strcmp(cur_command,"exit") != 0)
    {
        com_cleaner(cur_command, max_comm_lenght);

        scanf("%s", &cur_command);

        if(strcmp(cur_command,"push") == 0)
        {
            scanf("%d", &num);
            my_push(&stack_1, num);
        }
        else if(strcmp(cur_command,"pop") == 0)
        {
            num = my_pop(&stack_1);
            printf("num = %d \n", num);
        }

        if(Err_code != 0)
        {
            err_print();
            Err_code = 0;
        }
    }

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

    if(is_stack_ok(my_stack) == -1)
        Err_code = 6;

    while(i != Max_size_of_my_stack)
    {
        my_stack->data[i] = 0;
        i++;
    }

    my_stack->counter = 0;

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
void my_push(struct s_my_stack *my_stack, data_type num)
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
data_type my_pop(struct s_my_stack *my_stack)
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
//! This function cleans command string
//!
//! @param[in] char* command - command string
//! @param[in] int com_size - size of command string
//!------------------------------------------------------------------------------------------
void com_cleaner(char* command, int com_size)
{
    int i = 0;

    while(i != com_size)
    {
        command[i] = Poizon_num;
        i++;
    }
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
        printf("!!!  ERROR_PRINT - ERROR_IN_CREARE_STACK_START  (Err_code = %d) !!!\n\n", Err_code);
    else if(Err_code == 5)
        printf("!!!  ERROR_PRINT - ERROR_IN_CREARE_STACK_END  (Err_code = %d) !!!\n\n", Err_code);

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
