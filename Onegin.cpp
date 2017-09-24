
#include<stdio.h>
#include<string.h>
#include <ctype.h>

int n_sub(char* my_buff, long int size_of_text);
int str_sort(struct str* str_info, long int num_of_str);
int str_treatment(char *my_buff, struct str* str_info,  long int size_of_text, long int num_of_str);
int compare_string(char* first, char* second);

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
//! Сортировка строк в тексте по алфавиту
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
    size_of_text = ftell(text);// Вычисление длины текста

    char *my_buff = new char [size_of_text];// Создание буфера

    fseek(text, zero, SEEK_SET);
    fread(my_buff, sizeof(char), size_of_text, text);
    num_of_str = n_sub(my_buff, size_of_text);// Вычисление количества строк + замена '\n' на '\0'

    struct str* str_info = new struct str [num_of_str];// Создание массива структур для хранения информации о строках

    err = str_treatment(my_buff, str_info, size_of_text, num_of_str);//Запись информации о строках в структуру str_info


    err = err + str_sort(str_info, num_of_str);// Сортировка строк "пузырьком"


    while(i != num_of_str)// Печать строк
    {
         printf("# %d # %s \n",i , str_info[i].str_start);
         i++;
    }

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
        if(my_buff[cur_poz] == '\n')//Нахождение '\n' и замена их на '\0' в буфере
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
//! @param[in] struct str *str_info - Указатель на структуру с информацией о строках
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
    int prev_str_start = 0;

    if(my_buff[cur_poz] == '\0')
        return 1;

    str_info[cur_str].str_start = my_buff;// Запись первой строки
    cur_poz++;
    cur_str++;

    while(cur_poz != size_of_text - num_of_str)
    {
        if(my_buff[cur_poz] == '\0' && cur_poz != size_of_text - num_of_str)
        {
            str_info[cur_str].str_start = my_buff + cur_poz + 1;// Запись адреса начала строки
            str_info[cur_str].length = cur_poz - prev_str_start;// Нахождение длины строки
            prev_str_start = cur_poz + 1;// Запись начала строки (Необходимо для нахождения длины строки)


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

    char* temp = 0;
    int len_temp = 0;

    while(end_of_sort != yes)// Проверка, выполнялась ли хотя бы одна замена строк за цикл
    {
        cur_poz = 0;// Обнуление текущей позиции
        end_of_sort = yes;// Обнуления тригера выхода из сортировки

        while(cur_poz != num_of_str - 1)
        {
            if(compare_string(str_info[cur_poz].str_start, str_info[cur_poz + 1].str_start) > 0)// Проверка на неверное расположение строк по алфавиту
            {

                temp = str_info[cur_poz].str_start;// замена местами строк

                str_info[cur_poz].str_start = str_info[cur_poz + 1].str_start;
                str_info[cur_poz + 1].str_start = temp;


                len_temp = str_info[cur_poz].length;// замена местами длин строк

                str_info[cur_poz].length = str_info[cur_poz + 1].length;
                str_info[cur_poz + 1].length = len_temp;


                end_of_sort = no;// Тригер того, произошла ли хоть раз замена
            }

            cur_poz++;//переход к следующей позиции
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

    while(ispunct(*first) || isspace(*first))// Исключает знаки препинания и пробелы в начале первой строки
        first++;

    while(ispunct(*second) || isspace(*second))// Исключает знаки препинания и пробелы в начале второй строки
        second++;


    return strcmp(first, second);
}
