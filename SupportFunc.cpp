#pragma once

#include <iostream>
#include <string>
#include <fstream>

void print(std::string s)
{
    std::cout << s << std::endl;
}

std::string DecimaltoBinary(int num)
{
    std::string buffer;
    while(num!=0) 
    {
        buffer=(num%2==0 ?'0':'1')+buffer; 
        num/=2;
    }
    return buffer;
}

