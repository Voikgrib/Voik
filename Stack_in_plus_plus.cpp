
#include<stdio.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ START OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define POISON 666

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const int Max_size_of_stack = 20;

//=========================================================================
//!
//!     Stack structure
//!
//=========================================================================
struct s_stack
{
    int data[Max_size_of_stack];
    unsigned int counter;

    s_stack();
    ~s_stack();
    int push(int val);
    int pop();
};


//=========================================================================
//!
//!     Stack in c++
//!
//!     Author Vladimir Gribanov
//!
//=========================================================================
int main()
{
    struct s_stack my_stack;

    int err_code;

    err_code = my_stack.push(11);
    err_code = my_stack.push(22);

    int x = my_stack.pop();

    printf("x = %d\n", x);

    return 0;
}


//=========================================================================
//!
//!     This function push element into stack
//!
//=========================================================================
int s_stack::push(int val)
{
    if(counter < 0 || counter >= Max_size_of_stack)
    {
        printf("!!! ERR !!!         Stack is full\n");
        return POISON;
    }

    data[counter++] = val;

    return 0;
}


//=========================================================================
//!
//!     This function pick element from stack
//!
//=========================================================================
int s_stack::pop(void)
{
    if(counter > 0)
        return data[--counter];
    else
    {
        printf("!!! ERR !!!         Stack is empty\n");
        return POISON;
    }
}


//=========================================================================
//!
//!     Stack creator
//!
//=========================================================================
s_stack::s_stack():
    //data({}),       //?
    counter(0)
    {}


//=========================================================================
//!
//!     Stack destroyer
//!
//=========================================================================
s_stack::~s_stack()
{
    printf("Pein! Pein! Ia ne chuvstvuy nog!\n\n");
    counter = POISON;
}
