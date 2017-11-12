
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


#define WORK_TYPE( com )                                                                           \
            if(strcmp(work_type,"start") == 0)                                                     \
                work_par = LIST_START;                                                             \
            else if(strcmp(work_type,"end") == 0)                                                  \
                work_par = LIST_END;                                                               \
            else if(strcmp(work_type,"cur") == 0)                                                  \
                work_par = LIST_USR_POS;                                                           \
            else                                                                                   \
                printf(">>> Can not identify " #com " type!!!\n");


#define LIST_START              0

#define LIST_END                1

#define LIST_USR_POS            2


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const int Max_list_size = 16;
const int Canerry_security = 228;

int Err_code = 0;

typedef int t_list_data;

int is_lisk_ok(struct s_my_list *listik);
int empty_space_search(struct s_my_list *listik);
int start_search(struct s_my_list *listik);

void buf_fill(char* my_buff, long int size_buff, int fill_counter);
void generate_list(struct s_my_list *listik);
void my_interface(struct s_my_list *listik);

void list_add(struct s_my_list *listik, int position, t_list_data number, int where_point);
void list_free(struct s_my_list *listik, int position, int where_point);
void list_printer(struct s_my_list *listik);
void list_dump(struct s_my_list *listik);

void list_search_by_num(struct s_my_list *listik, t_list_data number);

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
//! List system (no bugs in add & free) v - 1.3   UPD - Now with Donov!!!
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

    int user_pos = 0;
    int work_par = -1;

    char command_line[comm_lenght];
    char work_type[comm_lenght];


    while(strcmp(command_line,"exit") != 0)
    {
        buf_fill(command_line, comm_lenght, '\0');
        buf_fill(work_type, comm_lenght, '\0');

        scanf("%s", &command_line);

        if(strcmp(command_line,"add") == 0)
        {
            scanf("%s", &work_type);
            scanf("%d", &num);

            WORK_TYPE( add )

            if(work_par != -1)
                list_add(listik, user_pos, num, work_par);

            work_par = -1;
        }
        else if(strcmp(command_line,"free") == 0)
        {
            scanf("%s", &work_type);

            WORK_TYPE( free );

            list_free(listik, user_pos, work_par);
        }
        else if(strcmp(command_line,"print") == 0)
        {
            list_printer(listik);
        }
        else if(strcmp(command_line,"dump") == 0)
        {
            list_dump(listik);
        }
        else if(strcmp(command_line,"setpos") == 0)
        {
            scanf("%d",&user_pos);
        }
        else if(strcmp(command_line,"data_search") == 0)
        {
            scanf("%d", &num);

            list_search_by_num(listik, num);
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
void list_free(struct s_my_list *listik, int position, int where_point)
{
    LIST_ASSERT( listik )

    int cur_pos = 0;
    int prev_pos = 0;
    int next_pos = 0;

    if(where_point == LIST_START)
    {
        cur_pos = listik->start_point;

        next_pos = listik->next_pointer[cur_pos];

        listik->prev_pointer[next_pos] = 0;
        listik->start_point = next_pos;
    }
    else if(where_point == LIST_END)
    {
        cur_pos = listik->end_point;

        prev_pos = listik->prev_pointer[cur_pos];

        listik->next_pointer[prev_pos] = 0;
        listik->end_point = prev_pos;
    }
    else if(where_point == LIST_USR_POS)
    {
        cur_pos = position;

        if(listik->prev_pointer[cur_pos] == -1 || listik->prev_pointer[cur_pos] == -1)
        {
            printf(">>> I can not free empty element, because it is already free! *smotrit na tebya vsgladom kepa* \n");
            return;
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
void list_add(struct s_my_list *listik, int position, t_list_data number, int where_point)
{
    LIST_ASSERT( listik )

    int fill_pos = empty_space_search(listik);
    int cur_place = 1;
    int prev_place = 1;

    if(where_point == LIST_END || (where_point == LIST_USR_POS && position == listik->end_point))
    {
        prev_place = listik->end_point;

        listik->next_pointer[prev_place] = fill_pos;

        listik->prev_pointer[fill_pos] = prev_place;
        listik->next_pointer[fill_pos] = 0;

        listik->end_point = fill_pos;
    }
    else if(where_point == LIST_START || (where_point == LIST_USR_POS && position == listik->start_point))
    {
        cur_place = listik->start_point;

        listik->prev_pointer[cur_place] = fill_pos;

        listik->prev_pointer[fill_pos] = 0;
        listik->next_pointer[fill_pos] = cur_place;

        listik->start_point = fill_pos;
    }
    else if(where_point == LIST_USR_POS)
    {
        cur_place = position;

        if(listik->prev_pointer[cur_place] == -1 || listik->prev_pointer[cur_place] == -1)
        {
            printf(">>> I can not put before empty element! \n");
            return;
        }

        prev_place = listik->prev_pointer[cur_place];

        listik->prev_pointer[fill_pos] = prev_place;
        listik->next_pointer[fill_pos] = cur_place;

        listik->prev_pointer[cur_place] = fill_pos;
        listik->next_pointer[prev_place] = fill_pos;

    }

    listik->main_data[fill_pos] = number;

    listik->next_pointer[listik->end_point] = 0;
    listik->prev_pointer[listik->start_point] = 0;

    LIST_ASSERT( listik )
}

//!-------------------------------------------------------------------------------
//!
//!
//!
//!
//!
//!-------------------------------------------------------------------------------
void list_search_by_num(struct s_my_list *listik, t_list_data number)
{
    const int answ_size = 10;

    int cur_pos = listik->start_point;
    int little_donov = 0;

    char answer[answ_size] = {};

    printf(">>> Are you sure? (yes/no)\n");

    buf_fill(answer, answ_size, '\0');
    scanf("%s", &answer);

    if(strcmp(answer,"no") == 0)
        return;

    printf(">>> A mnogo podtagivaeshsa? (yes/no)\n");

    buf_fill(answer, answ_size, '\0');
    scanf("%s", &answer);

    if(strcmp(answer,"no") == 0)
        return;

    while(cur_pos != 0)
    {
        little_donov = rand() % 100;

        if(little_donov <= 50)
            printf(">>> Podtanis rasok! \n");
        else
            printf(">>> *smotry na tebya wzgladom, polnim presreniya*\n");

        if(listik->main_data[cur_pos] == number)
        {
            printf("\n <><><><><> Equal number place in data_num = %d\n \n", cur_pos);
        }

        cur_pos = listik->next_pointer[cur_pos];
    }
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
