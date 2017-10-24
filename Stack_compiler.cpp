
#include<stdio.h>
#include<string.h>
#include"my_assembly_command_info.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ START OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define J_FUNC_COMPILE( name )                                          \
            {                                                           \
            is_com = three_nums_time;                                   \
            cur_poz = cur_poz + skip;                                   \
            comp_my_buf[i++] = name;                                    \
            cur_adress++;                                               \
            }


#define FUNC_NEEDS_NUM_COMPILE( name )                                  \
            {                                                           \
            is_com = no;                                                \
            cur_poz = cur_poz + skip;                                   \
            comp_my_buf[i++] = name;                                    \
            cur_adress++;                                               \
            }


#define FUNC_NO_NUM_COMPILE( name )                                     \
            {                                                           \
            cur_poz = cur_poz + skip;                                   \
            comp_my_buf[i++] = name;                                    \
            cur_adress++;                                               \
            }



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int Err_code = 0;

long int get_file_size(FILE *prog);

int str_get(char* my_buff, char* com_buf, long int cur_poz, long int buf_size, long int com_size);

void file_read(FILE *prog, long int size_of_prog, char* my_buff);
void file_print(char *comp_my_buff, long int size_of_prog);

void compile_prog(char* my_buff, char* comp_my_buff, long int size_of_prog);
void precompile_pointers(char* my_point_buff, char* my_buff, long int cur_pos, long int cur_adress);
void aftercompile_pointers(char* my_point_buff, char* comp_my_buff, long int size_of_prog);

void s_n_t_sub(char* my_buff, long int size_of_prog);
void buf_clean(char* my_buff, long int size_buff);
void err_print(void);

//!-------------------------------------------------------------------------------
//!
//! Compiler my program in my assembler  V - 1.4
//!
//! Author: Vladimir Gribanov
//!
//!-------------------------------------------------------------------------------
int main()
{
    long int size_of_prog = 0;

    FILE *prog = fopen("prog.txt","rt");

    size_of_prog = get_file_size(prog);

    char *my_buff = new char [size_of_prog];

    file_read(prog, size_of_prog, my_buff);

    char *comp_my_buff = new char [size_of_prog];

    buf_clean(comp_my_buff, size_of_prog);

    compile_prog(my_buff, comp_my_buff, size_of_prog);

    file_print(comp_my_buff, size_of_prog);

    fclose(prog);

    return 0;
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

    fseek(prog, zero, SEEK_SET);
    fread(my_buff, sizeof(char), size_of_prog, prog);
}

//!-------------------------------------------------------------------------------
//!
//! This function compile program
//!
//! @param[in] char* my_buff - uncompiled program
//! @param[in] char* comp_my_buf - compiled program
//! @param[in] long int size_of_prog - size of program
//!
//!-------------------------------------------------------------------------------
void compile_prog(char* my_buff, char* comp_my_buf, long int size_of_prog)
{
    const int yes = 0;
    const int no = 1;
    const int three_nums_time = 3;
    const int com_buff_size = 100;

    long int cur_poz = 0;
    long int cur_adress = 0;
    int is_com = yes;
    int is_end = no;
    int is_err_end = no;
    int skip = 0;
    int i = 0;

    char com_buff[com_buff_size] = {0};
    char my_point_buff[Max_num_of_pointers] = {0};

    s_n_t_sub(my_buff, size_of_prog);

    while(cur_poz != size_of_prog)
    {
        skip = str_get(my_buff, com_buff, cur_poz, size_of_prog, com_buff_size);


        if(my_buff[cur_poz] == ':' && is_com == yes)
        {
            cur_poz++;
            precompile_pointers(my_point_buff, my_buff, cur_poz, cur_adress);
            cur_poz = cur_poz + skip;
        }
        else if(strcmp(com_buff,"je") == 0 && is_com == yes)
            J_FUNC_COMPILE(Je)
        else if(strcmp(com_buff,"jne") == 0 && is_com == yes)
            J_FUNC_COMPILE(Jne)
        else if(strcmp(com_buff,"ja") == 0 && is_com == yes)
            J_FUNC_COMPILE(Ja)
        else if(strcmp(com_buff,"jae") == 0 && is_com == yes)
            J_FUNC_COMPILE(Jae)
        else if(strcmp(com_buff,"jb") == 0 && is_com == yes)
            J_FUNC_COMPILE(Jb)
        else if(strcmp(com_buff,"jbe") == 0 && is_com == yes)
            J_FUNC_COMPILE(Jbe)
        else if(strcmp(com_buff,"push") == 0 && is_com == yes)
            FUNC_NEEDS_NUM_COMPILE(Push)
        else if(strcmp(com_buff,"jump") == 0 && is_com == yes)
            FUNC_NEEDS_NUM_COMPILE(Jum)
        else if(strcmp(com_buff,"popr") == 0 && is_com == yes)
            FUNC_NEEDS_NUM_COMPILE(Pop_reg)
        else if(strcmp(com_buff,"pushr") == 0 && is_com == yes)
            FUNC_NEEDS_NUM_COMPILE(Push_reg)
        else if(strcmp(com_buff,"pop") == 0 && is_com == yes)
            FUNC_NO_NUM_COMPILE(Pop)
        else if(strcmp(com_buff,"add") == 0 && is_com == yes)
            FUNC_NO_NUM_COMPILE(Add)
        else if(strcmp(com_buff,"mul") == 0 && is_com == yes)
            FUNC_NO_NUM_COMPILE(Mul)
        else if(strcmp(com_buff,"sub") == 0 && is_com == yes)
            FUNC_NO_NUM_COMPILE(Sub)
        else if(strcmp(com_buff,"div") == 0 && is_com == yes)
            FUNC_NO_NUM_COMPILE(Div)
        else if(strcmp(com_buff,"end") == 0 && is_com == yes)
        {
            cur_poz = cur_poz + skip;
            comp_my_buf[i++] = End;
            comp_my_buf[i++] = '\n';
            is_end = yes;
            cur_adress++;
        }
        else if(my_buff[cur_poz] != '\0' && is_com != yes)
        {
            comp_my_buf[i++] = my_buff[cur_poz++];

            if(my_buff[cur_poz] == '\0')
            {
                is_com--;
                cur_adress++;
            }
        }
        else if(my_buff[cur_poz] == '\0')
        {
            comp_my_buf[i++] = '\n';
            cur_poz++;
        }
        else if(my_buff[cur_poz] != '\0' && is_com == yes)
        {
            Err_code = 1;
            is_err_end = yes;
        }
        else
            cur_poz++;


        if(is_end == yes)
        {
            aftercompile_pointers(my_point_buff, comp_my_buf, size_of_prog);
            return;
        }

        if(is_err_end == yes)
        {
            err_print();
            printf("ERROR IN %ld POZITION , %ld ADRESS \n", --cur_poz, cur_adress);
            buf_clean(comp_my_buf, size_of_prog);
            return;
        }
    }

}

//!-------------------------------------------------------------------------------
//!
//! This function save pointers
//!
//! @param[in] char* my_point_buff - massif with pointers
//! @param[in] char* my_buff - buffer with prog
//! @param[in] long int cur_pos - current position
//! @param[in] long int cur_adress - current adress
//!
//!-------------------------------------------------------------------------------
void precompile_pointers(char* my_point_buff, char* my_buff, long int cur_pos, long int cur_adress)
{
    long int digit_number = 1;
    long int num_adress = 0;

    while(my_buff[cur_pos] != '\0')
        cur_pos++;

    cur_pos--;

    while(my_buff[cur_pos] != ':')
    {
        num_adress = num_adress + (my_buff[cur_pos] - '0') * digit_number;
        digit_number = digit_number * 10;
        cur_pos--;
    }

    my_point_buff[num_adress] = cur_adress;
}

//!-------------------------------------------------------------------------------
//!
//! This function print adress on pointers
//!
//! @param[in] char* my_point_buff - saved pointers
//! @param[in] char* comp_my_buff - buffer with compiled prog
//! @param[in] long int size_of_prog - size of prog
//!
//!-------------------------------------------------------------------------------
void aftercompile_pointers(char* my_point_buff, char* comp_my_buff, long int size_of_prog)
{
    long int cur_pos = 0;
    long int point_num = 0;

    while(cur_pos < size_of_prog)
    {
        if(comp_my_buff[cur_pos] == ':')
        {
            cur_pos++;
            point_num = comp_my_buff[cur_pos] - '0';
            comp_my_buff[cur_pos] = my_point_buff[point_num];
        }

        cur_pos++;
    }
}

//!-------------------------------------------------------------------------------
//!
//! This function substitute ' ','\n','\t' => '\0'
//!
//! @param[in] char* my_buff - buffer which we worked
//! @param[in] long int size_of_prog - size of buffer
//!
//!-------------------------------------------------------------------------------
void s_n_t_sub(char* my_buff, long int size_of_prog)
{
    int cur_poz = 0;

    while(cur_poz != size_of_prog)
    {
        if(my_buff[cur_poz] == ' ' || my_buff[cur_poz] == '\n' || my_buff[cur_poz] == '\t')
        {
            my_buff[cur_poz] = '\0';
        }
        cur_poz++;
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

//!-------------------------------------------------------------------------------
//!
//! This function get size of current word in word buffer
//!
//! @param[in] char* my_buff - buffer which we worked (uncompiled)
//! @param[in] char* com_buf - word buffer
//! @param[in] long int cur_poz - word position
//! @param[in] long int buf_size - size of uncompiled buffer
//! @param[in] long int com_size - max wold size
//!
//!-------------------------------------------------------------------------------
int str_get(char* my_buff, char* com_buf, long int cur_poz, long int buf_size, long int com_size)
{
    int i = 0;
    int skip = 0;

    if(cur_poz > buf_size)
    {
        Err_code = -1;
        return -1;
    }

    buf_clean(com_buf, com_size);

    while(my_buff[cur_poz] != '\0' && cur_poz <= buf_size && i < com_size)
    {
        com_buf[i++] = my_buff[cur_poz++];
        skip++;
    }

    if(i >= com_size)
    {
        Err_code = -2;
        return -1;
    }

    return skip;
}

//!------------------------------------------------------------------------------------------------
//!
//! This function save file with compile prog
//!
//! @param[in] char *comp_my_buff - buffer which we worked (compiled)
//! @param[in] long int size_of_prog - size of buffer
//!------------------------------------------------------------------------------------------------
void file_print(char *comp_my_buff, long int size_of_prog)
{
    const int yes = 0;
    const int no = 1;
    const int need_three_nums = 3;
    long int cur_pos = 0;

    FILE *compile = fopen("compile.txt","w");

    int is_command = yes;
    int is_end = no;

    data_type cur_num = 0;
    data_type next_num = 0;

    while(is_end == no && cur_pos < size_of_prog)
    {
        cur_num = comp_my_buff[cur_pos];
        next_num = comp_my_buff[cur_pos + 1];

        if(is_command == yes && cur_num != '\n')
        {

            if(COM_NEEDS_NUM(cur_num))
                is_command = no;
            else if(COM_NEEDS_TWO_NUM_AND_POINTER(cur_num))
                is_command = need_three_nums;
            else if(cur_num == End)
                is_end = yes;

            fprintf(compile, "%d", cur_num);
        }
        else if(cur_num == '\n')
        {
            fprintf(compile, "\n");
        }
        else if(is_command != yes)
        {
            if(cur_num != ':')
                fprintf(compile, "%c", cur_num);
            else
            {
                fprintf(compile, "%d", next_num);
                cur_pos++;
                next_num = comp_my_buff[cur_pos + 1];
            }

            if(next_num == '\n')
                is_command--;
        }

        cur_pos++;
    }

    fclose(compile);
}

//!------------------------------------------------------------------------------------------------
//!
//! This function print user errors
//!
//!------------------------------------------------------------------------------------------------
void err_print(void)
{
    if(Err_code == 1)
        printf("SYNTAX_ERR!!! (Err_code = %d)", Err_code);
    else if(Err_code == -1)
        printf("STR_GET_ERR!!! (Err_code = %d)", Err_code);
    else if(Err_code != 0)
        printf("MAGIC_ERR   I forgot to declare this Err_num, sorry :c (Err_code = %d)", Err_code);
}
