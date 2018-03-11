#include "config.h"
#include <Gaem.hpp>

#include<iostream>
#include<stdexcept>

int main ()
{
    try
    {
        Gaem gaem;
        gaem.run();
    }
    catch(std::exception& e)
    {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
    }
}
