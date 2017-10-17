
#include<stdio.h>
#include<string.h>

int Err_code = 0;

const int Push = '1';
const int Pop = '2';
const int Add = '3';
const int Mul = '4';
const int Sub = '5';
const int Div = '6';
const int End = '0';

long int get_file_size(FILE *prog);

int str_get(char* my_buff, char* com_buf, long int cur_poz, long int buf_size, long int com_size);


void file_read(FILE *prog, long int size_of_prog, char* my_buff);
void compile_prog(char* my_buff, char* comp_my_buff, long int size_of_prog);
void s_n_t_sub(char* my_buff, long int size_of_prog);
void buf_clean(char* my_buff, long int size_buff);
void err_print(void);

//!-------------------------------------------------------------------------------
//!
//! Compiler my program in my assembler  V - 1.1
//!
//! Author: Vladimir Gribanov
//!
//!-------------------------------------------------------------------------------
int main()
{
    long int size_of_prog = 0;

    FILE *prog = fopen("prog.txt","rt");
    FILE *compile = fopen("compile.txt","w");

    size_of_prog = get_file_size(prog);

    char *my_buff = new char [size_of_prog];

    file_read(prog, size_of_prog, my_buff);

    char *comp_my_buff = new char [size_of_prog];

    buf_clean(comp_my_buff, size_of_prog);

    compile_prog(my_buff, comp_my_buff, size_of_prog);

    fprintf(compile, "%s \n", comp_my_buff);

    fclose(prog);
    fclose(compile);


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
    const int yes = 1;
    const int no = -1;
    const int com_buff_size = 100;

    long int cur_poz = 0;
    int is_com = yes;
    int is_end = no;
    int is_err_end = no;
    int skip = 0;
    int i = 0;

    char com_buff[com_buff_size] = {0};

    s_n_t_sub(my_buff, size_of_prog);

    while(cur_poz != size_of_prog)
    {
        skip = str_get(my_buff, com_buff, cur_poz, size_of_prog, com_buff_size);

        if(strcmp(com_buff,"push") == 0 && is_com == yes)
        {
            is_com = no;
            cur_poz = cur_poz + skip;
            comp_my_buf[i++] = Push;
        }
        else if(strcmp(com_buff,"pop") == 0 && is_com == yes)
        {
            cur_poz = cur_poz + skip;
            comp_my_buf[i++] = Pop;
        }
        else if(strcmp(com_buff,"add") == 0 && is_com == yes)
        {
            cur_poz = cur_poz + skip;
            comp_my_buf[i++] = Add;
        }
        else if(strcmp(com_buff,"mul") == 0 && is_com == yes)
        {
            cur_poz = cur_poz + skip;
            comp_my_buf[i++] = Mul;
        }
        else if(strcmp(com_buff,"sub") == 0 && is_com == yes)
        {
            cur_poz = cur_poz + skip;
            comp_my_buf[i++] = Sub;
        }
        else if(strcmp(com_buff,"div") == 0 && is_com == yes)
        {
            cur_poz = cur_poz + skip;
            comp_my_buf[i++] = Div;
        }
        else if(strcmp(com_buff,"end") == 0 && is_com == yes)
        {
            cur_poz = cur_poz + skip;
            comp_my_buf[i++] = End;
            comp_my_buf[i++] = '\n';
            is_end = yes;
        }
        else if(my_buff[cur_poz] != '\0' && is_com == no)
        {
            comp_my_buf[i++] = my_buff[cur_poz++];

            if(my_buff[cur_poz] == '\0')
                is_com = yes;
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
            return;

        if(is_err_end == yes)
        {
            err_print();
            buf_clean(comp_my_buf, size_of_prog);
            return;
        }
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
//! @param[in] long int cur_poz - word pozition
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


void err_print(void)
{
    if(Err_code == 1)
        printf("SYNTAX_ERR!!! (Err_code = %d)", Err_code);
    else if(Err_code == -1)
        printf("STR_GET_ERR!!! (Err_code = %d)", Err_code);
}
