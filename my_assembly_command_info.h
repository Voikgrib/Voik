#ifndef MY_ASSEMBLY_COMMAND_INFO_H_INCLUDED
#define MY_ASSEMBLY_COMMAND_INFO_H_INCLUDED

//!----------------------------------------------------------------------------------
//! Main information about function v 1.4   UPD if_Jump function with pointers
//!
//! ( Say NO to copy-paste! )
//!
//! Author: Vladimir Gribanov
//!----------------------------------------------------------------------------------

const int Push = 1;
const int Pop = 2;
const int Add = 3;
const int Mul = 4;
const int Sub = 5;
const int Div = 6;
const int Jum = 7;
const int Push_reg = 8;
const int Pop_reg = 9;

const int Je = 100;     // if(a == b) jump :c   else jump to next line
const int Jne = 101;    // if(a != b) jump :c   else jump to next line
const int Ja = 102;     // if(a > b) jump :c    else jump to next line
const int Jae = 103;    // if(a >= b) jump :c   else jump to next line
const int Jb = 104;     // if(a < b) jump :c    else jump to next line
const int Jbe = 105;    // if(a <= b) jump :c   else jump to next line

const int End = 0;

typedef int data_type;  // !!! CHANGE DATA_TYPE HERE !!!

const long int Max_size_of_my_stack = 20;
const long int Max_size_of_num_data = 20;
const long int Max_num_of_pointers = 20;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ START OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define COM_NEEDS_NUM( cur_num )                                     \
            (                                                        \
            cur_num == Push ||                                       \
            cur_num == Pop_reg ||                                    \
            cur_num == Push_reg ||                                   \
            cur_num == Jum                                           \
            )



#define COM_NEEDS_TWO_NUM_AND_POINTER( cur_num )                     \
            (                                                        \
            cur_num == Je ||                                         \
            cur_num == Jne ||                                        \
            cur_num == Ja ||                                         \
            cur_num == Jae ||                                        \
            cur_num == Jb ||                                         \
            cur_num == Jbe                                           \
            )

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // MY_ASSEMBLY_COMMAND_INFO_H_INCLUDED
