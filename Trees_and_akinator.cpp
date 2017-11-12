
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include"my_lib.h"

const long int Max_size_of_text = 100;

const int Poizon_point = NULL;
const int Nil = 0;
const int Left = 1;
const int Right = 2;

struct s_my_tree_brunch *create_part(struct s_my_tree_brunch *parent, char *info, int direct);

void brunch_construct(struct s_my_tree_brunch* ak_tree, struct s_my_tree_brunch *parent_point);
void user_interface(void);
void tree_dump(struct s_my_tree_brunch *start_point);
void node_dump_gen(struct s_my_tree_brunch *cur_point, FILE *dump);
void arrows_dump_gen(struct s_my_tree_brunch *cur_point, FILE *dump, long int prev_num);
void relinker(struct s_my_tree_brunch *cur_point, char *qwest, char *yes_ans, char *no_ans);

void info_saver(struct s_my_tree_brunch *start_point);
void info_rec_saver(struct s_my_tree_brunch *cur_point, FILE *ak_info);
struct s_my_tree_brunch *info_reader(struct s_my_tree_brunch *start_point);
struct s_my_tree_brunch *info_rec_reader(struct s_my_tree_brunch *cur_point, FILE *ak_info);

void recur_gen_dot_dump(struct s_my_tree_brunch *node);

//!-------------------------------------------------------------------------------
//!
//! This structure for tree brunch
//!
//! @param struct s_my_tree_brunch *parent_pointer - pointer on parent brunch
//! @param char text_info - info about brunch
//! @param struct s_my_tree_brunch * left_point - pointer on left branch
//! @param struct s_my_tree_brunch * right_point - pointer on right brunch
//!-------------------------------------------------------------------------------
struct s_my_tree_brunch
{
    struct s_my_tree_brunch *parent_pointer;
    char text_info [Max_size_of_text];
    struct s_my_tree_brunch * left_point;
    struct s_my_tree_brunch * right_point;
};

//!-------------------------------------------------------------------------------
//!
//! It's my akinator  v - 1.3
//!
//! >>> UPD(1.2) - Akinator work? Yes! dump work? Nope (Magic)
//! >>> UPD(1.3) - I make memory! (but not dump, because he is byaka :p)
//!
//! Author: Vladimir Gribanov
//!
//!-------------------------------------------------------------------------------
int main()
{
    user_interface();

    return 0;
}

//!-------------------------------------------------------------------------------
//!
//! This function realize user interface
//!
//!-------------------------------------------------------------------------------
void user_interface(void)
{
    struct s_my_tree_brunch *start_point = 0;
    struct s_my_tree_brunch *cur_pos = 0;

    char command[Max_size_of_text] = {};
    char info_buf[Max_size_of_text] = {};
    char qwestion_buf[Max_size_of_text] = {};

    cur_pos = create_part(Poizon_point, "Eto_zwer", Nil);

    create_part(cur_pos, "kotik", Right);
    create_part(cur_pos, "mario", Left);

    start_point = cur_pos;

    while(cur_pos != NULL)
    {
        buf_fill(command, Max_size_of_text, '\0');
        buf_fill(info_buf, Max_size_of_text, '\0');
        buf_fill(qwestion_buf, Max_size_of_text, '\0');

        if(cur_pos->left_point == NULL || cur_pos == NULL)
        {
            printf("Eto %s ???\n", cur_pos->text_info);

            scanf("%s", command);

            if(strcmp(command,"yes") == 0)
            {
                printf("Xa-xa-xa ia znal!!!\n");
                cur_pos = start_point;
            }
            else
            {
                printf("Bebebe :p a kto eto?\n");
                scanf("%s", &info_buf);
                printf("Chto ect y %s i net y %s (no space please)?\n", info_buf, cur_pos->text_info);
                scanf("%s", &qwestion_buf);

                relinker(cur_pos, qwestion_buf, info_buf, cur_pos->text_info);
            }
            buf_fill(command, Max_size_of_text, '\0');

            printf("Play more? c: \n");
            scanf("%s", command);

            cur_pos = start_point;

            if(strcmp(command,"no") == 0)
                cur_pos = NULL;
        }
        else
        {
            printf("%s ?\n", cur_pos->text_info);

            scanf("%s", command);

            if(strcmp(command,"yes") == 0)
                cur_pos = cur_pos->right_point;
            else if(strcmp(command,"no") == 0)
                cur_pos = cur_pos->left_point;
            else
                printf("ajgkj;g;ks, wot, chto a yslishal!!!\n");
        }
    }

    //tree_dump(start_point);     ///======== WORK IN PROGRESS(?) =======///
    info_saver(start_point);
}

//!-------------------------------------------------------------------------------
//!
//! This function pre-construct brunch
//!
//! @param[in] struct s_my_tree_brunch* ak_tree - brunch we are working on
//! @param[in] struct s_my_tree_brunch *parent_point - parent brunch for this brunch
//!
//!-------------------------------------------------------------------------------
void brunch_construct(struct s_my_tree_brunch* ak_tree, struct s_my_tree_brunch *parent_point)
{
        ak_tree->left_point = Poizon_point;
        ak_tree->right_point = Poizon_point;
        ak_tree->parent_pointer = parent_point;
        buf_fill(ak_tree->text_info, Max_size_of_text, '\0');
}

//!-------------------------------------------------------------------------------
//!
//! This function after-construct brunch
//!
//! @param[in] struct s_my_tree_brunch *parent - parent brunch for this brunch
//! @param[in] char *info - current brunch info
//! @param[in] int direct - brunch direction
//!
//! @param[out] struct s_my_tree_brunch - pointer to maked brunch
//!
//!-------------------------------------------------------------------------------
struct s_my_tree_brunch *create_part(struct s_my_tree_brunch *parent, char *info, int direct)
{
    struct s_my_tree_brunch *cur_branch = (struct s_my_tree_brunch*)calloc(1, sizeof(struct s_my_tree_brunch));

    int num = 0;

    brunch_construct(cur_branch, parent);

    if(direct == Left)
    {
        parent->left_point = cur_branch;
        cur_branch->parent_pointer = parent;
    }
    else if(direct == Right)
    {
        parent->right_point = cur_branch;
        cur_branch->parent_pointer = parent;
    }
    else if(direct == Nil)
    {
        cur_branch->parent_pointer = NULL;
    }

    while(num != Max_size_of_text)
    {
        cur_branch->text_info[num] = info[num];
        num++;
    }

    return cur_branch;
}

//!-------------------------------------------------------------------------------
//!
//! This function links tree brunches with new qwestions
//!
//! @param[in] struct s_my_tree_brunch *cur_point - pointer to current brunch
//! @param[in] char *qwest - qwestion
//! @param[in] char *yes_ans - info for right brunch
//! @param[in] char *no_ans - info for left brunch
//!
//!-------------------------------------------------------------------------------
void relinker(struct s_my_tree_brunch *cur_point, char *qwest, char *yes_ans, char *no_ans)
{
    struct s_my_tree_brunch *yes_cur = create_part(cur_point, yes_ans, Right);
    struct s_my_tree_brunch *no_cur = create_part(cur_point, no_ans, Left);

    long int num = 0;

    while(num != Max_size_of_text)
    {
        cur_point->text_info[num] = qwest[num];
        num++;
    }

    cur_point->left_point = no_cur;
    cur_point->right_point = yes_cur;
}

//!-------------------------------------------------------------------------------
//!
//! This function is not working correctly now =(
//!
//! @param[in]
//!
//!-------------------------------------------------------------------------------
void tree_dump(struct s_my_tree_brunch *start_point)
{
    FILE *dump = fopen("dump.dot","w");

    fprintf(dump, "digraph list {\n\tnode [shape = record];\n");

    ///—ƒ≈À¿“‹ –≈ ”–—»ﬁ!!!!
    /// node1 [label = "{<f0> Parent = %f |{ <f1> |{<f2> no = %f | <f3>  yes = %f }}}"]

    node_dump_gen(start_point, dump);
    arrows_dump_gen(start_point, dump, Nil);

    fprintf(dump, "}");

    fclose(dump);

    system("C:\\Users\\bqbq4\\OneDrive\\ƒÓÍÛÏÂÌÚ˚\\œÓ„Ë\\release\\bin\\dotty.exe dump.dot");
}

//!-------------------------------------------------------------------------------
//!
//! This function is not working correctly now too =(
//!
//! @param[in]
//! @param[in]
//!
//!-------------------------------------------------------------------------------
void node_dump_gen(struct s_my_tree_brunch *cur_point, FILE *dump)
{
    static long int cur_pos = 0;

    if(cur_point->left_point != NULL)
        node_dump_gen(cur_point->left_point, dump);

    fprintf(dump, "\tnode%ld [label = \"cur_poz = %ld|{<f0> Parent = %p | <f1>%s |{<f2> no = %p | <f3> yes = %p }}\"];\n", cur_pos, cur_pos, cur_point->parent_pointer, cur_point->text_info, cur_point->left_point, cur_point->right_point);
    cur_pos++;

    if(cur_point->right_point != NULL)
        node_dump_gen(cur_point->right_point, dump);
}

//!-------------------------------------------------------------------------------
//!
//!
//!
//! @param[in]
//! @param[in]
//! @param[in]
//!
//!-------------------------------------------------------------------------------
void arrows_dump_gen(struct s_my_tree_brunch *cur_point, FILE *dump, long int prev_num)
{
    static long int cur_pos = 0;

    if(cur_pos != 0)
    {
        fprintf(dump, "\t\"node%ld\":f2 -> \"node%ld\":f0;\n", prev_num);
        fprintf(dump, "\t\"node%ld\":f3 -> \"node%ld\":f0;\n", prev_num);
    }

    if(cur_point->left_point != NULL)
    {
        arrows_dump_gen(cur_point->left_point, dump, cur_pos);
    }


    cur_pos++;

    if(cur_point->right_point != NULL)
    {
        arrows_dump_gen(cur_point->right_point, dump, cur_pos);
    }
}

//!-------------------------------------------------------------------------------
//!
//! Open file for save and call recursive function
//!
//! @param[in] struct s_my_tree_brunch *start_point - point on tree start
//!
//!-------------------------------------------------------------------------------
void info_saver(struct s_my_tree_brunch *start_point)
{
    FILE *ak_info = fopen("ak_info.txt","w");

    info_rec_saver(start_point, ak_info);

    fclose(ak_info);
}

//!-------------------------------------------------------------------------------
//!
//! Fill file with info using recursion
//!
//! @param[in] struct s_my_tree_brunch *cur_point - brunch we are working on
//! @param[in] FILE *ak_info - file with saved info
//!
//!-------------------------------------------------------------------------------
void info_rec_saver(struct s_my_tree_brunch *cur_point, FILE *ak_info)
{
    if(cur_point == NULL)
    {
        fprintf(ak_info, "!");
        return;
    }

    fprintf(ak_info, "(");
    fprintf(ak_info, " %s ", cur_point->text_info);

    info_rec_saver(cur_point->left_point, ak_info);
    info_rec_saver(cur_point->right_point, ak_info);

    fprintf(ak_info, ")");
}

//!-------------------------------------------------------------------------------
//!
//!                                                                                 ///Work in progress
//!
//! @param[in]
//!
//!-------------------------------------------------------------------------------
struct s_my_tree_brunch *info_reader(struct s_my_tree_brunch *start_point)
{
    FILE *ak_info = fopen("ak_info.txt","r");



    fclose(ak_info);
}

//!-------------------------------------------------------------------------------
//!
//! Read file with info using recursion                                              ///Work in progress
//!
//! @param[in] struct s_my_tree_brunch *cur_point - brunch we are working on
//! @param[in] FILE *ak_info - file with saved info
//!
//!-------------------------------------------------------------------------------
struct s_my_tree_brunch *info_rec_reader(struct s_my_tree_brunch *cur_point, FILE *ak_info)
{
    char buff[Max_size_of_text] = {};

    int symbol = 0;
    int cur_pos = 0;

    symbol = fgetc(ak_info);

    while(symbol != '(' && symbol != ')' && symbol != '!' && cur_pos != Max_size_of_text)
    {
        buff[cur_pos++] = symbol;
        symbol = fgetc(ak_info);
    }

    if(symbol == '(')
    {
        cur_point->left_point = info_rec_reader(cur_point, ak_info);
    }
    else if(symbol == ')')
    {
        cur_point->right_point = info_rec_reader(cur_point, ak_info);
    }
    else if(symbol == '!')
    {
        fgetc(ak_info);
        cur_point->left_point = NULL;
        cur_point->right_point = NULL;
    }
}
