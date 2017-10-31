
#include<stdio.h>
#include<string.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ START OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define LIST_ASSERT( line , listok )                                                    \
                                    if(is_lisk_ok(listok) == 0)                         \
                                        list_dump(listok, line, 0);                     \
                                    else                                                \
                                        list_dump(listok, line, 1);


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const int Max_list_size = 16;
const int Canerry_security = 228;

int Err_code = 0;

typedef int t_list_data;

int is_lisk_ok(struct s_my_list *listik);
int empty_space_search(struct s_my_list *listik);
int start_search(struct s_my_list *listik);

void generate_list(struct s_my_list *listik);
void buf_fill(char* my_buff, long int size_buff,int fill_counter);
void interface(struct s_my_list *listik);
void list_add(struct s_my_list *listik, int position, t_list_data number);
void list_free(struct s_my_list *listik, int position);
void list_printer(struct s_my_list *listik);

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

int main()
{
    struct s_my_list listik;

    generate_list(&listik);

    interface(&listik);

    return 0;
}



void interface(struct s_my_list *listik)
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
    }
}



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

}


void list_free(struct s_my_list *listik, int position)
{
    int cur_pos = start_search(listik);
    int prev_pos = 0;
    int next_pos = 0;
    int counter = 0;

    while(counter != position)
    {
        cur_pos = listik->next_pointer[cur_pos];
        counter++;
    }

    next_pos = listik->next_pointer[cur_pos];
    prev_pos = listik->prev_pointer[cur_pos];

    listik->next_pointer[prev_pos] = next_pos;
    listik->prev_pointer[next_pos] = prev_pos;

    listik->next_pointer[cur_pos] = -1;
    listik->main_data[cur_pos] = -1;
    listik->prev_pointer[cur_pos] = -1;
}


void list_add(struct s_my_list *listik, int position, t_list_data number)///ERROR IN FIRST NUMS IN NEXT AND PREV
{
    int fill_pos = empty_space_search(listik);
    int cur_pos = start_search(listik);
    int cur_place = 1;
    int prev_place = 1;

    while(cur_pos != position)
    {
        if(listik->next_pointer[cur_place] != 0 && listik->next_pointer[cur_place] != -1)
            cur_place = listik->next_pointer[cur_place];

        cur_pos++;
    }

    if(listik->prev_pointer[cur_place] != 0)
        prev_place = listik->prev_pointer[cur_place];
    else
        prev_place = 0;

    listik->prev_pointer[fill_pos] = prev_place;
    listik->main_data[fill_pos] = number;
    listik->next_pointer[fill_pos] = cur_place;

    if(prev_place != 0)
        listik->next_pointer[prev_place] = fill_pos;
    else
        listik->start_point = fill_pos;

    listik->prev_pointer[cur_place] = fill_pos;

    if(listik->next_pointer[fill_pos] == listik->start_point)
       {
           listik->next_pointer[fill_pos] = 0;
           listik->end_point = fill_pos;
       }

    if(listik->prev_pointer[fill_pos] == listik->end_point)
        {
            listik->prev_pointer[fill_pos] = 0;
            listik->start_point = fill_pos;
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


void list_printer(struct s_my_list *listik)
{
    int cur_pos = 0;

    printf("num\tnext\tprev\n");

    while(cur_pos != Max_list_size)
    {
        printf("%d\t%d\t%d\n", listik->main_data[cur_pos], listik->next_pointer[cur_pos], listik->prev_pointer[cur_pos]);
        cur_pos++;
    }
}


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


int empty_space_search(struct s_my_list *listik)
{
    int cur_pos = 1;

    while(cur_pos != Max_list_size && listik->next_pointer[cur_pos] != -1)
        cur_pos++;

    if(cur_pos == Max_list_size)
        return -1;

    return cur_pos;
}


int start_search(struct s_my_list *listik)
{
    int cur_pos = 1;

    while(listik->prev_pointer[cur_pos] == 0)
        cur_pos++;

    return cur_pos;
}
