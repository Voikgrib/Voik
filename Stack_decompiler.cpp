
#include<stdio.h>
#include<string.h>
#include"my_assembly_command_info.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ START OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#define COMMAND( com_num, com_print)                                   \
        if(cur_num == com_num)                                         \
        {                                                              \
            fprintf(dec_prog, "\n");                                   \
            fprintf(dec_prog, com_print);                              \
            fprintf(dec_prog, " ");                                    \
        }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


long int get_file_size(FILE *prog);
long int scan_num(char *my_buff, long int cur_pos);
long int point_checker(char *point_data, long int scn_n);

void command_fprint(FILE *dec_prog, int cur_num);
void decompile(char* my_buff, long int size_of_prog);
void file_read(FILE *prog, long int size_of_prog, char *my_buff);
void place_pointers(char *point_data);
void buf_fill(char* my_buff, long int size_buff,int fill_counter);

//!-------------------------------------------------------------------------------
//!
//! Decompiler my assembler in my program  V - 1.5... Meow ^^ IT'S WORKING!!!!!!
//!
//! Author: Vladimir Gribanov
//!
//!-------------------------------------------------------------------------------
int main()
{
    long int size_of_prog = 0;

    FILE *comp_prog = fopen("compile.txt","rt");

    size_of_prog = get_file_size(comp_prog);

    char *my_buff = new char [size_of_prog];

    file_read(comp_prog, size_of_prog, my_buff);

    decompile(my_buff, size_of_prog);

    return 0;
}

//!-------------------------------------------------------------------------------
//!
//! This function decompile file
//!
//! @param[in] char* my_buff - buffer with decompile code
//! @param[in] long int size_of_prog - size of this file
//!
//!-------------------------------------------------------------------------------
void decompile(char* my_buff, long int size_of_prog)
{
    char point_data[Max_num_of_pointers] = {0};

    buf_fill(point_data, Max_num_of_pointers, -1);

    FILE *dec_prog = fopen("decprog.txt","w");

    const int yes = 0;
    const int no = 1;
    const int three_nums_time = 3;
    const int sec_end = 3;

    long int cur_pos = 0;
    long int point_num = 0;

    int is_com = yes;
    int is_end = no;
    int is_point = no;

    data_type cur_num = 0;

    while(is_end != sec_end && cur_pos < size_of_prog)
    {
        cur_num = scan_num(my_buff, cur_pos);

        while(my_buff[cur_pos] != '\n')
            cur_pos++;

        if(cur_pos == size_of_prog)
            is_end = sec_end;

        if(is_com == yes && COM_NEEDS_NOTHING(cur_num))
        {
            command_fprint(dec_prog, cur_num);

            if(cur_num == End)
                is_end++;

        }
        else if(is_com == yes && COM_NEEDS_NUM(cur_num))
        {
            command_fprint(dec_prog, cur_num);
            is_com = no;

            if(cur_num == Fcall)
                is_point = yes;
        }
        else if(is_com == yes && COM_NEEDS_TWO_NUM_AND_POINTER(cur_num))
        {
            command_fprint(dec_prog, cur_num);
            is_com = three_nums_time;
            is_point = yes;
        }
        else if(is_com == no && is_point == yes)
        {
            if(point_checker(point_data, cur_num) == -1)
            {
                point_data[point_num] = cur_num;
                fprintf(dec_prog, ":%ld", point_num);
                point_num++;
            }
            else
                fprintf(dec_prog, ":%ld", point_checker(point_data, cur_num));

            is_com--;
            is_point = no;
        }
        else if(is_com != yes)
        {
            fprintf(dec_prog, "%d ", cur_num);
            is_com--;
        }

        cur_pos++;
    }

    fclose(dec_prog);

    place_pointers(point_data);

}

//!-------------------------------------------------------------------------------
//!
//! This function places pointers
//!
//! @note if I have more time it was more beautiful
//!
//! @param[in] char *point_data - saved pointers
//!
//!-------------------------------------------------------------------------------
void place_pointers(char *point_data)
{
    long int cur_adress = 0;
    long int point_num = 0;
    long int cur_pos = 0;
    long int cur_size = 0;

    FILE *dec_prog = fopen("decprog.txt","rt");

    cur_size = get_file_size(dec_prog);

    char *my_buff = new char [cur_size];
    buf_fill(my_buff, cur_size, ' ');

    file_read(dec_prog, cur_size, my_buff);
    fclose(dec_prog);

    dec_prog = fopen("decprog.txt","w");
    fseek(dec_prog, 0, SEEK_SET);

    while(point_num != Max_num_of_pointers)
    {
        if(point_data[point_num] == cur_adress)
            fprintf(dec_prog, "\n:%ld", point_num);

        point_num++;
    }

    cur_adress++;

    while(cur_pos != cur_size)
    {
        fprintf(dec_prog, "%c", my_buff[cur_pos]);

        if((my_buff[cur_pos] != ' ' && my_buff[cur_pos] != '\n') && (my_buff[cur_pos + 1] == ' ' || my_buff[cur_pos + 1] == '\n'))
        {
            point_num = 0;

            while(point_num != Max_num_of_pointers)
            {
                if(point_data[point_num] == cur_adress)
                    fprintf(dec_prog, "\n:%ld", point_num);

                point_num++;
            }
            cur_adress++;
        }
        cur_pos++;
    }

}

//!-------------------------------------------------------------------------------
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
//! This function fills buffer
//!
//! @param[in] char* my_buff - buffer which we worked
//! @param[in] long int size_buff - size of buffer
//!
//!-------------------------------------------------------------------------------
void buf_fill(char* my_buff, long int size_buff, int fill_counter)
{
    int i = 0;

    while(i != size_buff)
    {
        my_buff[i] = fill_counter;
        i++;
    }
}


//!-------------------------------------------------------------------------------
//!
//! This function delaet chislo is ciferok v massive
//!
//! @param[in] char *my_buff - massif which we worked on
//! @param[in] long int cur_pos - current position in this massif
//!
//!-------------------------------------------------------------------------------
long int scan_num(char *my_buff, long int cur_pos)
{
    long int digit_number = 1;
    long int num = 0;

    while(my_buff[cur_pos] != '\n')
        cur_pos++;

    cur_pos--;

    if(my_buff[cur_pos] != 0)
        while(my_buff[cur_pos] != '\n' && cur_pos >= 0)
        {
            num = num + (my_buff[cur_pos] - '0') * digit_number;
            digit_number = digit_number * 10;
            cur_pos--;
        }
    else
        return 0;


    return num;
}

//!-------------------------------------------------------------------------------
//!
//! This function check was adress writed or not
//!
//! @param[in] char *point_data - saved pointers
//! @param[in] long int scn_n - current adress
//!
//!-------------------------------------------------------------------------------
long int point_checker(char *point_data, long int scn_n)
{
    int i = 0;

    while(i != Max_num_of_pointers)
    {
        if(point_data[i] == scn_n)
            return i;

        i++;
    }

    return -1;
}

//!-------------------------------------------------------------------------------
//!
//! This function print command in file
//!
//! @param[in] FILE *dec_prog - file which we print
//! @param[in] int cur_num - cur command code
//!
//!-------------------------------------------------------------------------------
void command_fprint(FILE *dec_prog, int cur_num)
{

    #include"my_command_shortcut.h"

    if(cur_num == End)
        fprintf(dec_prog, "\nend ");

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
