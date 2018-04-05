#include <iostream>
#include "ExtException.h"

void F3()
{
    ExtException a;
    throw ExtException("holy", 234, a);
}

void F2()
{
    try
    {
        F3();
    }
    catch(const ExtException& prev)
    {
        throw ExtException("shit", 123, prev);
    }
}

void F1()
{
    try
    {
        F2();
    }
    catch(const ExtException& prev)
    {
        throw ExtException("Terrible fault", -1, prev);
    }
}


int main()
{
    try
    {
        F1();
    }
    catch(const ExtException& prev)
    {
        std::cout << prev.GetErrorMessage() << std::endl;
    }

}
