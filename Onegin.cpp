
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
//! Создание структуры, для хранения информации о строках
//!
//! @param char* str_start - указатель на начало строки
//! @param int length - длина строки
//!
//!-----------------------------------------------------
struct str
{
    char* str_start;
    int length;
};

//!-----------------------------------------------------
//!
//! Сортировка строк в тексте по алфавиту и по алфавиту с конца строк
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
//! Функция находит '\n' в буфере и заменяет их на '\0'
//!
//! @param[in] char *my_buff - указатель на буфер
//! @param[in] long int size_of_text - длина буфера
//!
//! @param[out] num_of_str - количество строк в тексте
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
//! Функция записывает информацию о строках в структуру str_info
//!
//! @param[in] char *my_buff - Указатель на буфер
//! @param[in] struct str *str_info - Указаfirst_lengthтель на структуру с информацией о строках
//! @param[in] long int size_of_text - длина буфера
//! @param[in] long int num_of_str - Кол-во строк в буфере
//!
//! @param[out] Выводит 0 если ошибок нет
//!
//!----------------------------------------------------------------
int str_treatment(char *my_buff, struct str* str_info, long int size_of_text, long int num_of_str)
{
    int cur_poz = 0;
    int cur_str = 0;

    if(my_buff[cur_poz] == '\0')
        return 1;

    str_info[cur_str].str_start = my_buff;// Çàïèñü ïåðâîé ñòðîêè
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
//! Выполняет сортировку строк по алфавиту
//!
//! @param[in] struct str *str_info - Указатель на структуру с информацией о строках
//! @param[in] long int num_of_str - Кол-во строк в буфере
//!
//! @param[out] Возвращает 0 при выполнении без ошибок
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
//! Даёт информацию о том, какая из двух полученных строк стояла раньше по алфавиту
//!
//! @param[in] char* first - Первая строка
//! @param[in] char* second - Вторая строка
//!
//! @param[out] Отрицательное число, если первая строка раньше второй по алфавиту
//! @param[out] Положительное число, если вторая строка раньше первой по алфавиту
//! @param[out] ноль, если строки идентичны
//!
//!----------------------------------------------------------------
int compare_string(char* first, char* second)
{

    while(ispunct(*first) || isspace(*first))// Èñêëþ÷àåò çíàêè ïðåïèíàíèÿ è ïðîáåëû â íà÷àëå ïåðâîé ñòðîêè
        first++;

    while(ispunct(*second) || isspace(*second))// Èñêëþ÷àåò çíàêè ïðåïèíàíèÿ è ïðîáåëû â íà÷àëå âòîðîé ñòðîêè
        second++;


    return strcmp(first, second);
}

//!----------------------------------------------------------------
//!
//! Считывает размер файла для записи в буфер
//!
//! @param[in] FILE *text - файл, размер которого надо узнать
//!
//! @param[out] size_of_text - Размер текста
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
//! Считывает файл и записывает в буфер + возвращает количество строк
//!
//! @param[in] FILE *text - файл
//! @param[in] long int size_of_text - размер файла
//! @param[in] char* my_buff - буфер
//!
//! @param[out] num_of_str - количество строк
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
//! Выводит строки по указателям в структуре str
//!
//! @param[in] struct str* str_info - структура, содержащая информацию о строках
//! @param[in] long int num_of_str - количество строк
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
//! Сортировка "пузыриком" концов строк по алфавиту
//!
//! @param[in] struct str* str_info - Структура, содержащая информацию о строках
//! @param[in] long int num_of_str - Количество строк
//!
//! @param[out] 0 - если ошибок нет
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
//! Функция, аналогичная strcmp, но работающая с конца строки
//!
//! @param[in] char* first - Указатель на первую строку
//! @param[in] int first_length - Длина первой строки
//! @param[in] char* second - Указатель на вторую строку
//! @param[in] int second_length - Длина второй строки
//!
//! @param[out] Разность первой отличающейся буквы с конца строк
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
