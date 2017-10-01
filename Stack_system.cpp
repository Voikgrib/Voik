
#include<stdio.h>
#include<assert.h>
#include<string.h>

const long int Max_size_of_my_stack = 666;

int stack_construct(struct t_my_stack *my_stack);
int my_push(struct t_my_stack *my_stack, int num);
int my_pop(struct t_my_stack *my_stack);

void com_cleaner(char* command, int com_size);
void err_print(int err_code);

//!------------------------------------------------------------------------------------------
//! Declare structure t_my_stack
//!
//! @param char data[] - massif with stack data
//! @param int counter - pointer on current pozition
//!------------------------------------------------------------------------------------------
struct t_my_stack
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

    int err = 0;
    char cur_command[max_comm_lenght] = {0};
    int num = 0;

    struct t_my_stack stack_1;

    printf("Stack created!\n");

    err = stack_construct(&stack_1);

    while(strcmp(cur_command,"exit") != 0)
    {
        com_cleaner(cur_command, max_comm_lenght);

        scanf("%s", &cur_command);

        if(strcmp(cur_command,"push") == 0)
        {
            scanf("%d", &num);
            err = my_push(&stack_1, num);
        }
        else if(strcmp(cur_command,"pop") == 0)
        {
            num = my_pop(&stack_1);
            printf("num = %d \n", num);
        }

        if(err != 0)
            err_print(err);
    }

    return err;
}

//!------------------------------------------------------------------------------------------
//! This function initialize stack: fulls data[] = {}, set counter = 0
//!
//! @param[in] struct t_my_stack *my_stack - stack which will be initialized
//!
//! @param[out] 0 - if no errors
//!------------------------------------------------------------------------------------------
int stack_construct(struct t_my_stack *my_stack)
{
    int i = 0;

    while(i != Max_size_of_my_stack)
    {
        my_stack->data[i] = 0;
        i++;
    }

    my_stack->counter = 0;

    return 0;
}

//!------------------------------------------------------------------------------------------
//! This function put number in stack
//!
//! @param[in] struct t_my_stack *my_stack - stack we are working on
//! @param[in] int num - number which will be put in stack
//!
//! @param[out] 0 - if no errors
//! @param[out] 1 - if stack is full
//!------------------------------------------------------------------------------------------
int my_push(struct t_my_stack *my_stack, int num)
{
    if(my_stack->counter != Max_size_of_my_stack)
    {
        my_stack->data[my_stack->counter] = num;
        my_stack->counter++;
    }
    else
    {
        return 1;
    }

    return 0;
}

//!------------------------------------------------------------------------------------------
//! This function get number from stack
//!
//! @param[in] struct t_my_stack *my_stack - stack we are working on
//!
//! @param[out] 0 - if no errors
//! @param[out] -1 & error_message - stack is empty
//!------------------------------------------------------------------------------------------
int my_pop(struct t_my_stack *my_stack)
{
    int num = 0;

    if(my_stack->counter > 0)
    {
        num = my_stack->data[--my_stack->counter];

        if(my_stack->counter == 0)
            printf("### Alarm! ###  Stack is empty mow! You can't get more numbers :c \n");


        return num;

    }
    else
    {
        printf("### Error! ###  You can't do this. Stack is empty! (return -1) meow :3 \n");
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
        command[i] = '\0';
        i++;
    }
}

//!------------------------------------------------------------------------------------------
//! This function prints error messages about last error
//!
//! @param[in] err_code - code of last error
//!------------------------------------------------------------------------------------------
void err_print(int err_code)
{
    if(err_code == 1)
        printf("!!!  ERROR_PRINT - END_OF_MEMORY  (err_code = %d) !!!\n\n", err_code);
}
