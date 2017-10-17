
#include<stdio.h>
#include<assert.h>
#include<string.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ START OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#define STACK_ASSERT( stack , line)                                                             \
    if((is_stack_ok(stack) == -1))                                                              \
        {                                                                                       \
            info_dump(stack, 1, line);                                                          \
        }                                                                                       \
        else                                                                                    \
            info_dump(stack, 0, line);                                                          \


#define NAME_OF( name )             #name


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

typedef int data_type;

const long int Max_size_of_my_stack = 20;
const long int Max_size_of_num_data = 20;
const int Poizon_num = '\0';
const int Cannery_security_check = 228;
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

long int get_file_size(FILE *prog);

void stack_add(struct s_my_stack *my_stack);
void stack_construct(struct s_my_stack *my_stack);
void stack_push(struct s_my_stack *my_stack, data_type num);
void stack_mul(struct s_my_stack *my_stack);
void stack_sub(struct s_my_stack *my_stack);
void stack_div(struct s_my_stack *my_stack);
void com_cleaner(char* command, int com_size);
void com_worker(struct s_my_stack *my_stack, char *my_buff);
void info_dump(struct s_my_stack *my_stack, int is_err, int line);
void err_print(void);
void file_read(FILE *prog, long int size_of_prog, char* my_buff);
void buf_clean(char* my_buff, long int size_buff);
void dump_clean(void);


//!------------------------------------------------------------------------------------------
//! Declare structure s_my_stack
//!
//! @param char data[] - massif with stack data
//! @param int counter - pointer on current pozition
//!------------------------------------------------------------------------------------------
struct s_my_stack
{
    int start_canerry_men;
    char data [Max_size_of_my_stack];
    char num_data [Max_size_of_num_data];
    int counter;
    int end_cannery_men;
};

//!------------------------------------------------------------------------------------------
//! This program contains stack and some function with it   V - 1.1
//!
//! Author: Vladimir Gribanov
//!------------------------------------------------------------------------------------------
int main()
{
    FILE *compile = fopen("compile.txt","rt");

    long int size_of_prog = 0;

    size_of_prog = get_file_size(compile);

    char *my_buff = new char [size_of_prog];

    file_read(compile, size_of_prog, my_buff);

    struct s_my_stack stack_1;

    stack_construct(&stack_1);

    com_worker(&stack_1, my_buff);

    fclose(compile);

    return Err_code;
}

void com_worker(struct s_my_stack *my_stack, char *my_buff)
{
    long int cur_poz = 0;
    int command_num = -1;

    data_type num = 0;

    dump_clean();

    while(command_num != End)
    {
        command_num = my_buff[cur_poz];

        if(command_num == Push)
        {
            num = my_buff[++cur_poz];
            stack_push(my_stack, num);
        }
        else if(command_num == Pop)
        {
            num = stack_pop(my_stack);
            printf("num = %d \n", num);
        }
        else if(command_num == Add)
        {
            stack_add(my_stack);
        }
        else if(command_num == Mul)
        {
            stack_mul(my_stack);
        }
        else if(command_num == Sub)
        {
            stack_sub(my_stack);
        }
        else if(command_num == Div)
        {
            stack_div(my_stack);
        }

        if(Err_code != 0)
        {
            err_print();
            Err_code = 0;
        }

        cur_poz++;
    }

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
    my_stack->end_cannery_men = Cannery_security_check;
    my_stack->start_canerry_men = Cannery_security_check;

    if(is_stack_ok(my_stack) == -1)
        Err_code = 6;

    while(i != Max_size_of_my_stack)
    {
        my_stack->data[i] = 0;
        i++;
    }

    STACK_ASSERT(my_stack, __LINE__)

}

//!------------------------------------------------------------------------------------------
//! This function put number in stack
//!
//! @param[in] struct s_my_stack *my_stack - stack we are working on
//! @param[in] int num - number which will be put in stack
//!
//! @note Error codes 1 - if stack is full
//!
//!------------------------------------------------------------------------------------------
void stack_push(struct s_my_stack *my_stack, data_type num)
{
    STACK_ASSERT(my_stack, __LINE__)

    if(my_stack->counter != Max_size_of_my_stack)
    {
        my_stack->data[my_stack->counter] = num;
        my_stack->counter++;
    }
    else
    {
        Err_code = 1;
    }

    STACK_ASSERT(my_stack, __LINE__)
}

//!------------------------------------------------------------------------------------------
//! This function get number from stack
//!
//! @param[in] struct s_my_stack *my_stack - stack we are working on
//!
//! @note Error codes 101 - stack is empty
//!
//! @param[out] data_type num - number (or something) from stuck
//!------------------------------------------------------------------------------------------
data_type stack_pop(struct s_my_stack *my_stack)
{
    int num = 0;

    STACK_ASSERT(my_stack, __LINE__)

    if(my_stack->counter > 0)
    {
        num = my_stack->data[--my_stack->counter];
        my_stack->data[my_stack->counter] = Poizon_num;
        return num;

    }
    else
    {
        Err_code = 101;
        return -1;
    }

    STACK_ASSERT(my_stack, __LINE__)

}

//!------------------------------------------------------------------------------------------
//! This function pick two numbers from stack and do num 2 + num 1, and pop answer
//!
//! @param[in] struct s_my_stack *my_stack - stack we are working on
//!
//!------------------------------------------------------------------------------------------
void stack_mul(struct s_my_stack *my_stack)
{
    STACK_ASSERT(my_stack, __LINE__)

    data_type fir_num = stack_pop(my_stack);
    data_type sec_num = stack_pop(my_stack);

    stack_push(my_stack, sec_num * fir_num);

    STACK_ASSERT(my_stack, __LINE__)
}

//!------------------------------------------------------------------------------------------
//! This function pick two numbers from stack and do num 2 - num 1, and pop answer
//!
//! @param[in] struct s_my_stack *my_stack - stack we are working on
//!
//!------------------------------------------------------------------------------------------
void stack_sub(struct s_my_stack *my_stack)
{
    STACK_ASSERT(my_stack, __LINE__)

    data_type fir_num = stack_pop(my_stack);
    data_type sec_num = stack_pop(my_stack);

    stack_push(my_stack, sec_num - fir_num);

    STACK_ASSERT(my_stack, __LINE__)
}

//!------------------------------------------------------------------------------------------
//! This function pick two numbers from stack and do num 2 / num 1, and pop answer
//!
//! @param[in] struct s_my_stack *my_stack - stack we are working on
//!
//! @note Error codes 100 - if num 1 / 0
//!------------------------------------------------------------------------------------------
void stack_div(struct s_my_stack *my_stack)
{
    STACK_ASSERT(my_stack, __LINE__)

    data_type fir_num = stack_pop(my_stack);
    data_type sec_num = stack_pop(my_stack);

    if(sec_num == 0)
    {
        Err_code = 100;
        return;
    }

    stack_push(my_stack, sec_num / fir_num);

    STACK_ASSERT(my_stack, __LINE__)
}

//!------------------------------------------------------------------------------------------
//! This function pick two numbers from stack and do num 2 * num 1, and pop answer
//!
//! @param[in] struct s_my_stack *my_stack - stack we are working on
//!
//!------------------------------------------------------------------------------------------
void stack_add(struct s_my_stack *my_stack)
{
    STACK_ASSERT(my_stack, __LINE__)

    data_type fir_num = stack_pop(my_stack);
    data_type sec_num = stack_pop(my_stack);

    stack_push(my_stack, sec_num + fir_num);

    STACK_ASSERT(my_stack, __LINE__)
}


//!------------------------------------------------------------------------------------------
//! This function prints user error messages about last error
//!
//! @param Err_code - code of last error
//!------------------------------------------------------------------------------------------
void err_print()
{
    if(Err_code == -1)
        printf("!!!  ERROR_PRINT - STACK_IS_FULL  (Err_code = %d) !!!\n\n", Err_code);
    else if(Err_code == 100)
        printf("!!!  ERROR_PRINT - ERROR_IN_DIV I cann't do num / 0  (Err_code = %d) !!!\n\n", Err_code);
    else if(Err_code == 101)
        printf("!!!  ERROR_PRINT - STACK_IS_EMPTY  (Err_code = %d) !!!\n\n", Err_code);
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
       my_stack->data &&
       my_stack->start_canerry_men == Cannery_security_check &&
       my_stack->end_cannery_men == Cannery_security_check
        )
        return 0;
    else
        return -1;
}

//!-----------------------------------------------------------------------------------------
//!
//! This function creates dump
//!
//! @param[in] struct s_my_stack *my_stack - stack which we check
//! @param[in] int is_err - 0 - if no need in err_print
//!                         1 - if need err_ print
//!
//!-----------------------------------------------------------------------------------------
void info_dump(struct s_my_stack *my_stack, int is_err, int line)
{
    FILE *dump = fopen("dump.txt","a+");

    fseek(dump, 0, SEEK_END);

    int i = 0;

    fprintf(dump, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    fprintf(dump, "We are work with stack %s \n", NAME_OF( my_stack ));
    fprintf(dump, "dump from line = %d \n",line);

    if(is_err == 1)
        fprintf(dump, "!!! EEROR !!!\n in line = %d \n in file = %s \n",line ,__FILE__);

    while(i != Max_size_of_my_stack)
    {
        fprintf(dump, "%s.data[%d] = %d \n", NAME_OF( my_stack ), i, my_stack->data[i]);
        i++;
    }

    fclose(dump);
}

//!-------------------------------------------------------------------------------
//!
//! This function get size of reading file
//!
//! @param[in] FILE *prog - file which we worked
//!
//! @param[out] size of file
//!-------------------------------------------------------------------------------
long int get_file_size(FILE *prog)
{
    long int size_of_prog = 0;

    const int zero = 0;

    fseek(prog, zero, SEEK_END);
    size_of_prog = ftell(prog);

    return size_of_prog;
}

//!-------------------------------------------------------------------------------
//!
//! This function reading file
//!
//! @param[in] FILE *prog - file which we worked
//! @param[in] long int size_of_prog - size of file
//! @param[in] char *my_buff - buffer, which we worked
//!
//!-------------------------------------------------------------------------------
void file_read(FILE *prog, long int size_of_prog, char *my_buff)
{
    const int zero = 0;

    int cur_data = 0;
    int cur_poz = 0;

    buf_clean(my_buff, size_of_prog);

    fseek(prog, zero, SEEK_SET);

    while(ftell(prog) != size_of_prog)
    {
        fscanf(prog, "%d", &cur_data);
        my_buff[cur_poz++] = cur_data;
    }
}

//!-------------------------------------------------------------------------------
//!
//! This function clean buffer
//!
//! @param[in] char* my_buff - buffer which we worked
//! @param[in] long int size_buff - size of buffer
//!
//!-------------------------------------------------------------------------------
void buf_clean(char* my_buff, long int size_buff)
{
    int i = 0;

    while(i != size_buff)
    {
        my_buff[i] = '\0';
        i++;
    }
}


void dump_clean(void)
{
    FILE *dump = fopen("dump.txt","wb");
    fclose(dump);
}
