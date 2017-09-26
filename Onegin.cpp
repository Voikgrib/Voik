
#include<stdio.h>
#include<string.h>
#include <ctype.h>

int n_sub(char* my_buff, long int size_of_text);
int str_sort(struct str* str_info, long int num_of_str);
int str_treatment(char *my_buff, struct str* str_info,  long int size_of_text, long int num_of_str);
int compare_string(char* first, char* second);
int end_str_treatment(struct str* str_info, long int num_of_str);
int end_compare_string(char* first, int first_length, char* second, int second_length);

long int get_file_size(FILE *text);
long int file_read(FILE *text, long int size_of_text, char* my_buff);

void my_print(struct str* str_info, long int num_of_str);


//!-----------------------------------------------------
//!
//! �������� ���������, ��� �������� ���������� � �������
//!
//! @param char* str_start - ��������� �� ������ ������
//! @param int length - ����� ������
//!
//!-----------------------------------------------------
struct str
{
    char* str_start;
    int length;
};

//!-----------------------------------------------------
//!
//! ���������� ����� � ������ �� ��������
//!
//!-----------------------------------------------------
int main()
{
    long int size_of_text = 0;
    long int num_of_str = 0;
    int err = 0;

    FILE *text = fopen("Onegin_text.txt","rt");

    size_of_text = get_file_size(text);

    char *my_buff = new char [size_of_text];

    num_of_str = file_read(text, size_of_text, my_buff);

    struct str* str_info = new struct str [num_of_str];

    err = str_treatment(my_buff, str_info, size_of_text, num_of_str);

    my_print(str_info, num_of_str);

    if(err != 0)
    {
        printf("### ERROR 1 ###\n");
        return err;
    }

    err = str_sort(str_info, num_of_str);

    if(err != 0)
    {
        printf("### ERROR 2 ###\n");
        return err;
    }


    my_print(str_info, num_of_str);

    err = end_str_treatment(str_info, num_of_str);

    my_print(str_info, num_of_str);

    fclose(text);

    return err;
}

//!----------------------------------------------------------------
//!
//! ������� ������� '\n' � ������ � �������� �� �� '\0'
//!
//! @param[in] char *my_buff - ��������� �� �����
//! @param[in] long int size_of_text - ����� ������
//!
//! @param[out] num_of_str - ���������� ����� � ������
//!
//!----------------------------------------------------------------
int n_sub(char *my_buff, long int size_of_text)
{
    int cur_poz = 0;
    int num_of_str = 0;

    while(cur_poz != size_of_text)
    {
        if(my_buff[cur_poz] == '\n')
        {
            my_buff[cur_poz] = '\0';
            num_of_str++;
        }

        cur_poz++;
    }

    return num_of_str;
}

//!----------------------------------------------------------------
//!
//! ������� ���������� ���������� � ������� � ��������� str_info
//!
//! @param[in] char *my_buff - ��������� �� �����
//! @param[in] struct str *str_info - �����first_length���� �� ��������� � ����������� � �������
//! @param[in] long int size_of_text - ����� ������
//! @param[in] long int num_of_str - ���-�� ����� � ������
//!
//! @param[out] ������� 0 ���� ������ ���
//!
//!----------------------------------------------------------------
int str_treatment(char *my_buff, struct str* str_info, long int size_of_text, long int num_of_str)
{
    int cur_poz = 0;
    int cur_str = 0;

    if(my_buff[cur_poz] == '\0')
        return 1;

    str_info[cur_str].str_start = my_buff;// ������ ������ ������
    str_info[cur_str].length = strlen(str_info[cur_str].str_start);
    cur_poz++;
    cur_str++;

    while(cur_poz != size_of_text - num_of_str)
    {
        if(my_buff[cur_poz] == '\0' && cur_poz != size_of_text - num_of_str)
        {
            str_info[cur_str].str_start = my_buff + cur_poz + 1;
            str_info[cur_str].length = strlen(str_info[cur_str].str_start);

            cur_str++;
        }

        cur_poz++;
    }

    return 0;
}

//!----------------------------------------------------------------
//!
//! ��������� ���������� ����� �� ��������
//!
//! @param[in] struct str *str_info - ��������� �� ��������� � ����������� � �������
//! @param[in] long int num_of_str - ���-�� ����� � ������
//!
//! @param[out] ���������� 0 ��� ���������� ��� ������
//!
//!----------------------------------------------------------------
int str_sort(struct str* str_info, long int num_of_str)
{

    int cur_poz = 0;
    int end_of_sort = 0;

    const int yes = 1;
    const int no = -1;

    char* temp = NULL;
    int len_temp = 0;

    while(end_of_sort != yes)
    {
        cur_poz = 0;
        end_of_sort = yes;

        while(cur_poz != num_of_str - 1)
        {
            if(compare_string(str_info[cur_poz].str_start, str_info[cur_poz + 1].str_start) > 0)
            {

                temp = str_info[cur_poz].str_start;

                str_info[cur_poz].str_start = str_info[cur_poz + 1].str_start;
                str_info[cur_poz + 1].str_start = temp;


                len_temp = str_info[cur_poz].length;

                str_info[cur_poz].length = str_info[cur_poz + 1].length;
                str_info[cur_poz + 1].length = len_temp;


                end_of_sort = no;
            }

            cur_poz++;
        }
    }


    return 0;
}

//!----------------------------------------------------------------
//!
//! ��� ���������� � ���, ����� �� ���� ���������� ����� ������ ������ �� ��������
//!
//! @param[in] char* first - ������ ������
//! @param[in] char* second - ������ ������
//!
//! @param[out] ������������� �����, ���� ������ ������ ������ ������ �� ��������
//! @param[out] ������������� �����, ���� ������ ������ ������ ������ �� ��������
//! @param[out] ����, ���� ������ ���������
//!
//!----------------------------------------------------------------
int compare_string(char* first, char* second)
{

    while(ispunct(*first) || isspace(*first))// ��������� ����� ���������� � ������� � ������ ������ ������
        first++;

    while(ispunct(*second) || isspace(*second))// ��������� ����� ���������� � ������� � ������ ������ ������
        second++;


    return strcmp(first, second);
}

//!----------------------------------------------------------------
//!
//! ��������� ������ ����� ��� ������ � �����
//!
//! @param[in] FILE *text - ����, ������ �������� ���� ������
//!
//! @param[out] size_of_text - ������ ������
//!
//!----------------------------------------------------------------
long int get_file_size(FILE *text)
{
    long int size_of_text = 0;

    const int zero = 0;

    fseek(text, zero, SEEK_END);
    size_of_text = ftell(text);

    return size_of_text;
}

//!----------------------------------------------------------------
//!
//! ��������� ���� � ���������� � ����� + ���������� ���������� �����
//!
//! @param[in] FILE *text - ����
//! @param[in] long int size_of_text - ������ �����
//! @param[in] char* my_buff - �����
//!
//! @param[out] num_of_str - ���������� �����
//!
//!----------------------------------------------------------------
long int file_read(FILE *text, long int size_of_text, char* my_buff)
{
    long int num_of_str = 0;

    const int zero = 0;

    fseek(text, zero, SEEK_SET);
    fread(my_buff, sizeof(char), size_of_text, text);
    num_of_str = n_sub(my_buff, size_of_text);

    return num_of_str;
}

//!----------------------------------------------------------------
//!
//! ������� ������ �� ���������� � ��������� str
//!
//! @param[in] struct str* str_info - ���������, ���������� ���������� � �������
//! @param[in] long int num_of_str - ���������� �����
//!
//!----------------------------------------------------------------
void my_print(struct str* str_info, long int num_of_str)
{
    int i = 0;

    while(i != num_of_str)
    {
         printf("# %d # %s \n",i , str_info[i].str_start);
         i++;
    }

    printf("\n \n \n");
}

//!----------------------------------------------------------------
//!
//! ���������� "���������" ������ ����� �� ��������
//!
//! @param[in] struct str* str_info - ���������, ���������� ���������� � �������
//! @param[in] long int num_of_str - ���������� �����
//!
//! @param[out] 0 - ���� ������ ���
//!
//!----------------------------------------------------------------
int end_str_treatment(struct str* str_info, long int num_of_str)
{
    long int cur_str = 0;
    int end_of_sort = 0;

    char* temp = NULL;
    int len_temp = 0;

    const int yes = 1;
    const int no = -1;

    while(end_of_sort != yes)
    {
        end_of_sort = yes;
        cur_str = 0;

        while(cur_str != num_of_str - 1)
        {

            if(end_compare_string(str_info[cur_str].str_start, str_info[cur_str].length, str_info[cur_str + 1].str_start, str_info[cur_str + 1].length) > 0)
            {
                temp = str_info[cur_str].str_start;

                str_info[cur_str].str_start = str_info[cur_str + 1].str_start;
                str_info[cur_str + 1].str_start = temp;

                len_temp = str_info[cur_str].length;

                str_info[cur_str].length = str_info[cur_str + 1].length;
                str_info[cur_str + 1].length = len_temp;


                end_of_sort = no;
            }


            cur_str++;
        }
    }

    return 0;

}

//!----------------------------------------------------------------
//!
//! �������, ����������� strcmp, �� ���������� � ����� ������
//!
//! @param[in] char* first - ��������� �� ������ ������
//! @param[in] int first_length - ����� ������ ������
//! @param[in] char* second - ��������� �� ������ ������
//! @param[in] int second_length - ����� ������ ������
//!
//! @param[out] �������� ������ ������������ ����� � ����� �����
//!
//!----------------------------------------------------------------
int end_compare_string(char* first, int first_length, char* second, int second_length)
{
    int end_difference = 0;

    first = first + first_length-1;
    second = second + second_length-1;

    while(ispunct(*first) || isspace(*first))
        first--;

    while(ispunct(*second) || isspace(*second))
        second--;

    end_difference = *first - *second;

    while(end_difference == 0)
    {
        end_difference = *first - *second;
        second--;
        first--;

    }

    return end_difference;
}
