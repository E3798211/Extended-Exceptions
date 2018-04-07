#include <iostream>
#include "ExtException.h"

void F3()
{
    throw new ExtException("holy", 234, CALL_PARAMETERS);
}

void F2()
{
    try
    {
        F3();
    }
    catch(const ExtException* prev)
    {
        throw new ExtException("shit", 123, CALL_PARAMETERS, prev);
    }
}

void F1()
{
    try
    {
        F2();
    }
    catch(const ExtException* prev)
    {
        throw new ExtException("Terrible fault", -1, CALL_PARAMETERS, prev);
    }
}


int main()
{
    try
    {
        F1();
    }
    catch(const ExtException* prev)
    {
        std::cout << prev->GetAllInfo() << std::endl;

        prev->BuildDependencyGraph();

        delete prev;
    }

}
