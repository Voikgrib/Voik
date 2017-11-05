
#include<stdio.h>
#include<string.h>
#include<windows.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ START OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define LIST_ASSERT( listok )                                                                      \
                                    if(is_lisk_ok(listok) != 0)                                    \
                                    {                                                              \
                                        list_dump(listok);                                         \
                                        printf("(!) (!) (!) ERROR IN LIST ---> look at dump \n");  \
                                    }



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const int Max_list_size = 16;
const int Canerry_security = 228;

int Err_code = 0;

typedef int t_list_data;

int is_lisk_ok(struct s_my_list *listik);
int empty_space_search(struct s_my_list *listik);
int start_search(struct s_my_list *listik);

void generate_list(struct s_my_list *listik);
void buf_fill(char* my_buff, long int size_buff, int fill_counter);
void my_interface(struct s_my_list *listik);
void list_add(struct s_my_list *listik, int position, t_list_data number);
void list_free(struct s_my_list *listik, int position);
void list_printer(struct s_my_list *listik);
void list_dump(struct s_my_list *listik);

//!-------------------------------------------------------------------------------
//! @param int canarry_hello
//! @param char main_data
//! @param char next_pointer
//! @param char prev_pointer
//! @param int start_point
//! @param int end_point
//! @param int cannery_bye
//!-------------------------------------------------------------------------------
struct s_my_list
{
    int canarry_hello;
    char main_data[Max_list_size];
    char next_pointer[Max_list_size];
    char prev_pointer[Max_list_size];
    int start_point;
    int end_point;
    int cannery_bye;
};

//!-------------------------------------------------------------------------------
//!
//! List system (no bugs in add & free) v - 1.1
//!
//! Author: Gribanov Vladimir
//!
//!-------------------------------------------------------------------------------
int main()
{
    struct s_my_list listik;

    generate_list(&listik);

    my_interface(&listik);

    return 0;
}

//!-------------------------------------------------------------------------------
//!
//! This function realize user interface
//!
//! @param[in] struct s_my_list *listik - struct we are working on
//!
//!-------------------------------------------------------------------------------
void my_interface(struct s_my_list *listik)
{
    const int comm_lenght = 20;

    t_list_data num = 0;

    int pos = 0;

    char command_line[comm_lenght];


    while(strcmp(command_line,"exit") != 0)
    {
        buf_fill(command_line, comm_lenght, '\0');
        scanf("%s", &command_line);

        if(strcmp(command_line,"add") == 0)
        {
            scanf("%d", &pos);
            scanf("%d", &num);
            list_add(listik, pos, num);
        }
        else if(strcmp(command_line,"free") == 0)
        {
            scanf("%d", &pos);
            list_free(listik, pos);
        }
        else if(strcmp(command_line,"print") == 0)
        {
            list_printer(listik);
        }
        else if(strcmp(command_line,"dump") == 0)
        {
            list_dump(listik);
        }
    }
}

//!-------------------------------------------------------------------------------
//!
//! This function generate empty list
//!
//! @param[in] struct s_my_list *listik - struct we are working on
//!
//!-------------------------------------------------------------------------------
void generate_list(struct s_my_list *listik)
{
    const int poizon = -1;

    buf_fill(listik->main_data, Max_list_size, poizon);
    buf_fill(listik->next_pointer, Max_list_size, poizon);
    buf_fill(listik->prev_pointer, Max_list_size, poizon);

    listik->start_point = 1;
    listik->end_point = 1;

    listik->canarry_hello = Canerry_security;
    listik->cannery_bye = Canerry_security;

    LIST_ASSERT( listik )
}

//!-------------------------------------------------------------------------------
//!
//! This function clear pozition in stack
//!
//! @param[in] struct s_my_list *listik - struct we are working on
//! @param[in] int position - position which we clear
//!
//!-------------------------------------------------------------------------------
void list_free(struct s_my_list *listik, int position)
{
    LIST_ASSERT( listik )

    int cur_pos = listik->start_point;
    int prev_pos = 0;
    int next_pos = 0;
    int counter = 0;

    while(counter != position)
    {
        cur_pos = listik->next_pointer[cur_pos];
        counter++;
    }


    if(listik->start_point != cur_pos || cur_pos != listik->end_point)
    {
        if(listik->prev_pointer[cur_pos] == 0)
        {
            next_pos = listik->next_pointer[cur_pos];
            listik->start_point = next_pos;
            listik->prev_pointer[next_pos] = 0;
        }
        else if(listik->next_pointer[cur_pos] == 0)
        {
            prev_pos = listik->prev_pointer[cur_pos];
            listik->end_point = prev_pos;
            listik->next_pointer[prev_pos] = 0;
        }
        else
        {
            next_pos = listik->next_pointer[cur_pos];
            prev_pos = listik->prev_pointer[cur_pos];
            listik->prev_pointer[next_pos] = prev_pos;
            listik->next_pointer[prev_pos] = next_pos;
        }
    }

    listik->next_pointer[cur_pos] = -1;
    listik->main_data[cur_pos] = -1;
    listik->prev_pointer[cur_pos] = -1;

    LIST_ASSERT( listik )
}

//!-------------------------------------------------------------------------------
//!
//! This function add new number in the list
//!
//! @param[in] struct s_my_list *listik - struct we are working on
//! @param[in] int position - position were we place new number
//! @param[in] t_list_data number - new number
//!
//!-------------------------------------------------------------------------------
void list_add(struct s_my_list *listik, int position, t_list_data number)
{
    LIST_ASSERT( listik )

    int fill_pos = empty_space_search(listik);
    int cur_pos = listik->start_point;
    int cur_place = 1;
    int prev_place = 1;

    while(cur_pos != position)
    {
        if(cur_place != listik->end_point)
            cur_place = listik->next_pointer[cur_place];
        else
        {
            listik->end_point = fill_pos;
            prev_place = cur_place;
        }

        cur_pos++;
    }

    if(listik->end_point != fill_pos)
    {
        prev_place = listik->prev_pointer[cur_place];

        if(listik->prev_pointer[cur_place] == 0)
        {
            prev_place = 0;
            listik->start_point = fill_pos;
        }
    }

    if(listik->start_point != fill_pos)
    {
        listik->prev_pointer[fill_pos] = prev_place;
        listik->next_pointer[prev_place] = fill_pos;
    }
    else
    {
        listik->prev_pointer[fill_pos] = 0;
    }

    listik->main_data[fill_pos] = number;

    if(listik->end_point != fill_pos)
    {
        listik->next_pointer[fill_pos] = cur_place;
        listik->prev_pointer[cur_place] = fill_pos;
    }
    else
        listik->next_pointer[fill_pos] = 0;

    LIST_ASSERT( listik )
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
//! This function do simple list print
//!
//! @param[in] struct s_my_list *listik - struct we are working on
//!
//!-------------------------------------------------------------------------------
void list_printer(struct s_my_list *listik)
{
    LIST_ASSERT( listik )

    int cur_pos = 0;

    printf("num\tnext\tprev\n");

    while(cur_pos != Max_list_size)
    {
        printf("%d\t%d\t%d\n", listik->main_data[cur_pos], listik->next_pointer[cur_pos], listik->prev_pointer[cur_pos]);
        cur_pos++;
    }

    LIST_ASSERT( listik )
}

//!-------------------------------------------------------------------------------
//!
//! List Assert
//!
//! @param[in] struct s_my_list *listik - struct we are working on
//!
//!-------------------------------------------------------------------------------
int is_lisk_ok(struct s_my_list *listik)
{
    if
    (
    listik->main_data &&
    listik->next_pointer &&
    listik->prev_pointer &&
    listik->canarry_hello == Canerry_security &&
    listik->cannery_bye == Canerry_security
    )
        return 0;
    else
        return -1;
}

//!-------------------------------------------------------------------------------
//!
//! This function search empty space in list
//!
//! @param[in] struct s_my_list *listik - struct we are working on
//!
//!-------------------------------------------------------------------------------
int empty_space_search(struct s_my_list *listik)
{
    int cur_pos = 1;

    while(cur_pos != Max_list_size && listik->next_pointer[cur_pos] != -1)
        cur_pos++;

    if(cur_pos == Max_list_size)
        return -1;

    return cur_pos;
}


//!-------------------------------------------------------------------------------
//!
//! This function do graphic dump
//!
//! @param[in] struct s_my_list *listik - struct we are working on
//!
//!-------------------------------------------------------------------------------
void list_dump(struct s_my_list *listik)
{
    LIST_ASSERT( listik )

    FILE *dump = fopen("dump.dot","w");

    long int cur_pos = 0;

    fprintf(dump, "digraph list {\n\tnode [shape = record,height=.1];\n");

    while(cur_pos != Max_list_size)
    {
        fprintf(dump, "\tnode%ld[label = \"<f0>data = %d |<f1>next = %d |<f2>prev = %d|<f3> data_num = %ld\" ] ;\n", cur_pos, listik->main_data[cur_pos], listik->next_pointer[cur_pos], listik->prev_pointer[cur_pos], cur_pos);
        cur_pos++;
    }

    cur_pos = 0;

    while(cur_pos != Max_list_size)
    {
        if(listik->prev_pointer[cur_pos] != -1 && listik->prev_pointer[cur_pos] != -1)
        {
            fprintf(dump, "\t\"node%ld\":f1 -> \"node%d\":f1;\n", cur_pos, listik->next_pointer[cur_pos]);
            fprintf(dump, "\t\"node%ld\":f2 -> \"node%d\":f2;\n", cur_pos, listik->prev_pointer[cur_pos]);
        }
        cur_pos++;
    }

    fprintf(dump, "}");

    fclose(dump);

    system("C:\\Users\\bqbq4\\OneDrive\\Документы\\Проги\\release\\bin\\dotty.exe dump.dot");

    LIST_ASSERT( listik )
}
