
#include<stdio.h>
#include<string.h>
#include <ctype.h>

int n_sub(char* my_buff, long int size_of_text);
int str_sort(struct str* str_info, long int num_of_str);
int str_treatment(char *my_buff, struct str* str_info,  long int size_of_text, long int num_of_str);
int compare_string(char* first, char* second);

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
    const int zero = 0;

    long int size_of_text = 0;
    long int num_of_str = 0;
    int err = 0;
    int i = 0;

    FILE *text = fopen("Onegin_text.txt","rt");


    fseek(text, zero, SEEK_END);
    size_of_text = ftell(text);// ���������� ����� ������

    char *my_buff = new char [size_of_text];// �������� ������

    fseek(text, zero, SEEK_SET);
    fread(my_buff, sizeof(char), size_of_text, text);
    num_of_str = n_sub(my_buff, size_of_text);// ���������� ���������� ����� + ������ '\n' �� '\0'

    struct str* str_info = new struct str [num_of_str];// �������� ������� �������� ��� �������� ���������� � �������

    err = str_treatment(my_buff, str_info, size_of_text, num_of_str);//������ ���������� � ������� � ��������� str_info


    err = err + str_sort(str_info, num_of_str);// ���������� ����� "���������"


    while(i != num_of_str)// ������ �����
    {
         printf("# %d # %s \n",i , str_info[i].str_start);
         i++;
    }

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
        if(my_buff[cur_poz] == '\n')//���������� '\n' � ������ �� �� '\0' � ������
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
//! @param[in] struct str *str_info - ��������� �� ��������� � ����������� � �������
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
    int prev_str_start = 0;

    if(my_buff[cur_poz] == '\0')
        return 1;

    str_info[cur_str].str_start = my_buff;// ������ ������ ������
    cur_poz++;
    cur_str++;

    while(cur_poz != size_of_text - num_of_str)
    {
        if(my_buff[cur_poz] == '\0' && cur_poz != size_of_text - num_of_str)
        {
            str_info[cur_str].str_start = my_buff + cur_poz + 1;// ������ ������ ������ ������
            str_info[cur_str].length = cur_poz - prev_str_start;// ���������� ����� ������
            prev_str_start = cur_poz + 1;// ������ ������ ������ (���������� ��� ���������� ����� ������)


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

    char* temp = 0;
    int len_temp = 0;

    while(end_of_sort != yes)// ��������, ����������� �� ���� �� ���� ������ ����� �� ����
    {
        cur_poz = 0;// ��������� ������� �������
        end_of_sort = yes;// ��������� ������� ������ �� ����������

        while(cur_poz != num_of_str - 1)
        {
            if(compare_string(str_info[cur_poz].str_start, str_info[cur_poz + 1].str_start) > 0)// �������� �� �������� ������������ ����� �� ��������
            {

                temp = str_info[cur_poz].str_start;// ������ ������� �����

                str_info[cur_poz].str_start = str_info[cur_poz + 1].str_start;
                str_info[cur_poz + 1].str_start = temp;


                len_temp = str_info[cur_poz].length;// ������ ������� ���� �����

                str_info[cur_poz].length = str_info[cur_poz + 1].length;
                str_info[cur_poz + 1].length = len_temp;


                end_of_sort = no;// ������ ����, ��������� �� ���� ��� ������
            }

            cur_poz++;//������� � ��������� �������
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
