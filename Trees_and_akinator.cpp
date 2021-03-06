
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

int Err_code = 0;

struct s_my_tree_brunch *create_part(struct s_my_tree_brunch *parent, char *info, int direct);

long int get_file_size(FILE *text);

int f_skipper(FILE *file, int cym);

void brunch_construct(struct s_my_tree_brunch* ak_tree, struct s_my_tree_brunch *parent_point);
void user_interface(void);
void tree_dump(struct s_my_tree_brunch *start_point);
void node_dump_gen(struct s_my_tree_brunch *cur_point, FILE *dump);
void arrows_dump_gen(struct s_my_tree_brunch *cur_point, FILE *dump);
void relinker(struct s_my_tree_brunch *cur_point, char *qwest, char *yes_ans, char *no_ans);

void sub_podch_space(char* buff, long int size_of_text);
void buff_in_struct(char *buff, struct s_my_tree_brunch *brunch);

void info_saver(struct s_my_tree_brunch *start_point);
void info_rec_saver(struct s_my_tree_brunch *cur_point, FILE *ak_info);
struct s_my_tree_brunch *info_reader(void);
struct s_my_tree_brunch *info_rec_reader(struct s_my_tree_brunch *cur_point, char *buff, long int size_of_file);

void recur_gen_dot_dump(struct s_my_tree_brunch *node);
void freesher(struct s_my_tree_brunch *start_point);

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
//! It's my akinator  v - 1.5
//!
//! >>> UPD(1.2) - Akinator work? Yes! dump work? Nope (Magic)
//! >>> UPD(1.3) - I make memory! Not read, but save! (but not dump, because he is byaka :p)
//! >>> UPD(1.4) - Look at this dump! It's working now!! :D (add logo)
//! >>> UPD(1.5) - FINALLY IT'S MORE SMART THAN GOLDFISH! (reading program working correctly)
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

    //cur_pos = create_part(Poizon_point, "Eto_zwer", Nil);

    //create_part(cur_pos, "kotik", Right);
    //create_part(cur_pos, "mario", Left);

    start_point = cur_pos;

    start_point = info_reader();
    //tree_dump(start_point);
    cur_pos = start_point;
    //return;


    printf("\n\n\t\t+=========================================================+\n"
               "\t\t|      AKINATOR v 1.5      made by Vladimir Gribanov      |\n"
               "\t\t|                                                         |\n"
               "\t\t|     ! VMESTO PROBELOV PODCHERKIVANIA ! (krik dushi)     |\n"
               "\t\t+=========================================================+\n");

    while(cur_pos != NULL)
    {
        buf_fill(command, Max_size_of_text, '\0');
        buf_fill(info_buf, Max_size_of_text, '\0');
        buf_fill(qwestion_buf, Max_size_of_text, '\0');

        if(cur_pos->left_point == NULL || cur_pos == NULL)
        {
            printf("Ia znaiy!! Eto %s ???\n", cur_pos->text_info);

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

                sub_podch_space(info_buf, Max_size_of_text);
                sub_podch_space(qwestion_buf, Max_size_of_text);

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

    //tree_dump(start_point);
    info_saver(start_point);
    freesher(start_point);
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
//! This function create dump in dot language
//!
//! @param[in] struct s_my_tree_brunch *start_point - pointer on start structure
//!
//!-------------------------------------------------------------------------------
void tree_dump(struct s_my_tree_brunch *start_point)
{
    FILE *dump = fopen("dump.dot","w");

    fprintf(dump, "digraph list {\n\tnode [shape = record];\n");

    ///������� ��������!!!!
    /// node1 [label = "{<f0> Parent = %f |{ <f1> |{<f2> no = %f | <f3>  yes = %f }}}"]

    node_dump_gen(start_point, dump);
    arrows_dump_gen(start_point, dump);

    fprintf(dump, "}");

    fclose(dump);

    system("C:\\Users\\bqbq4\\OneDrive\\���������\\�����\\release\\bin\\dotty.exe dump.dot");
}

//!-------------------------------------------------------------------------------
//!
//! This function do recursive print nodes in dump file in dot language
//!
//! @param[in] struct s_my_tree_brunch *cur_point - pointer on current structure
//! @param[in] FILE *dump - dump file
//!
//!-------------------------------------------------------------------------------
void node_dump_gen(struct s_my_tree_brunch *cur_point, FILE *dump)
{
    if(cur_point->left_point != NULL)
        node_dump_gen(cur_point->left_point, dump);

    fprintf(dump, "\tnode%p [label = \"cur_poz = %p|{<f0> Parent = %p | <f1>%s |{<f2> no = %p | <f3> yes = %p }}\"];\n", cur_point, cur_point, cur_point->parent_pointer, cur_point->text_info, cur_point->left_point, cur_point->right_point);

    if(cur_point->right_point != NULL)
        node_dump_gen(cur_point->right_point, dump);
}

//!-------------------------------------------------------------------------------
//!
//! This function do recursive print arrows in dump file in dot language
//!
//! @param[in] struct s_my_tree_brunch *cur_point - pointer on current structure
//! @param[in] FILE *dump - dump file
//!
//!-------------------------------------------------------------------------------
void arrows_dump_gen(struct s_my_tree_brunch *cur_point, FILE *dump)
{
    if(cur_point->left_point != NULL)
        arrows_dump_gen(cur_point->left_point, dump);

    if(cur_point->left_point != NULL)
        fprintf(dump, "\t\"node%p\":f2 -> \"node%p\":f0[color = red];\n", cur_point, cur_point->left_point);

    if(cur_point->right_point != NULL)
        fprintf(dump, "\t\"node%p\":f3 -> \"node%p\":f0[color = green];\n", cur_point, cur_point->right_point);

    if(cur_point->right_point != NULL)
        arrows_dump_gen(cur_point->right_point, dump);
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
//!
//!
//! @param[in]
//! @param[in]
//!
//!-------------------------------------------------------------------------------
void sub_podch_space(char* buff, long int size_of_text)
{
    int i = 0;

    while(i != size_of_text)
    {
        if(buff[i] == '_')
            buff[i] = ' ';

        i++;
    }
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
        return;
    }

    fprintf(ak_info, "\t");
    fprintf(ak_info, "(");
    fprintf(ak_info, "'%s'\n", cur_point->text_info);
    fprintf(ak_info, "\t");


    info_rec_saver(cur_point->left_point, ak_info);
    info_rec_saver(cur_point->right_point, ak_info);

    fprintf(ak_info, "\t");
    fprintf(ak_info, ")\n");
}

//!-------------------------------------------------------------------------------
//!
//!  Prepare to read file
//!
//!-------------------------------------------------------------------------------
struct s_my_tree_brunch *info_reader(void)
{
    FILE *ak_info = fopen("ak_info.txt","r");

    struct s_my_tree_brunch *start_elem = create_part(NULL, " ", Nil);

    long int size_of_file = get_file_size(ak_info);

    char *buff = new char [size_of_file];

    fseek(ak_info, 0, SEEK_SET);
    fread(buff, sizeof(char), size_of_file, ak_info);

    start_elem = info_rec_reader(start_elem, buff, size_of_file);

    fclose(ak_info);

    return start_elem;
}

//!-------------------------------------------------------------------------------
//!
//! Read file with info using recursion
//!
//! @param[in] struct s_my_tree_brunch *cur_point - brunch we are working on
//! @param[in] FILE *ak_info - file with saved info
//!
//!-------------------------------------------------------------------------------
struct s_my_tree_brunch *info_rec_reader(struct s_my_tree_brunch *cur_point, char *buff, long int size_of_file)
{
    //if(Err_code != 0)
    //    return NULL;

    static long int pos_in_buff = 0;

    int inf_pos = 0;

    struct s_my_tree_brunch *n_element_l = (struct s_my_tree_brunch*) calloc(1, sizeof(struct s_my_tree_brunch));
    struct s_my_tree_brunch *n_element_r = (struct s_my_tree_brunch*) calloc(1, sizeof(struct s_my_tree_brunch));

    if(cur_point->parent_pointer == NULL)
    {
        while(buff[pos_in_buff] != '\'')
            pos_in_buff++;

        pos_in_buff++;

        while(buff[pos_in_buff] != '\'')
            cur_point->text_info[inf_pos++] = buff[pos_in_buff++];

        pos_in_buff++;

        inf_pos = 0;
    }

    while(buff[pos_in_buff] == ' ' || buff[pos_in_buff] == '\n' || buff[pos_in_buff] == '\t' || buff[pos_in_buff] == '\r')
        pos_in_buff++;

    if(buff[pos_in_buff] == '\'')
    {
        while(buff[pos_in_buff] != '\'')
            cur_point->text_info[inf_pos++] = buff[pos_in_buff++];

        pos_in_buff++;
    }

    while(buff[pos_in_buff] == ' ' || buff[pos_in_buff] == '\n' || buff[pos_in_buff] == '\t' || buff[pos_in_buff] == '\r')
        pos_in_buff++;

    if(buff[pos_in_buff] == '(')
    {
        cur_point->left_point = info_rec_reader(n_element_l, buff, size_of_file);
        cur_point->right_point = info_rec_reader(n_element_r, buff, size_of_file);

        while(buff[pos_in_buff] != ')')
            pos_in_buff++;

        pos_in_buff++;

        return cur_point;
    }
    else if(buff[pos_in_buff] == ')')
    {
        return cur_point;
    }
    else
    {
        return cur_point;
    }
        //printf(">>> ILI IA DURAK ILI TYT OSHIBKA \n");
}

//!------------------------------------------------------------------------------
//!
//! Why
//!
//!------------------------------------------------------------------------------
void freesher(struct s_my_tree_brunch *cur_point)
{
    if(cur_point->left_point != NULL)
        freesher(cur_point->left_point);

    if(cur_point->right_point != NULL)
        freesher(cur_point->right_point);

    free(cur_point);
}

//!------------------------------------------------------------------------------
//!
//! nobody
//!
//!------------------------------------------------------------------------------
int f_skipper(FILE *file, int cym)
{
    while(cym == ' ' || cym == '\t' || cym == '\n' || cym == '\r')
        cym = getc(file);

    return cym;
}

//!------------------------------------------------------------------------------
//!
//! reads
//!
//!------------------------------------------------------------------------------
void buff_in_struct(char *buff, struct s_my_tree_brunch *brunch)
{
    int i = 0;

    while(i != Max_size_of_text)
    {
        brunch->text_info[i] = buff[i];
        i++;
    }
}


//!----------------------------------------------------------------
//!
//! my
//!
//! @param[in] FILE *text - documentation
//!
//! @param[out] size_of_text - ???
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
