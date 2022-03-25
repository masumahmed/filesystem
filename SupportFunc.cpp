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

std::string DecToHex(int n)
{
    char hex[100];
 
    int i = 0;
    while (n != 0) {
        int temp = 0;
        temp = n % 16;
         if (temp < 10) {
            hex[i] = temp + 48;
            i++;
        }
        else {
            hex[i] = temp + 55;
            i++;
        }
 
        n = n / 16;
    }
 
    std::string result = "";
    for (int j = i - 1; j >= 0; j--)
        result += hex[j];

    std::string ResultWithLeadingZeros = "0x";
    for(int i=0; i<(8 - result.length()); i++) 
        ResultWithLeadingZeros += "0";
    
    ResultWithLeadingZeros += result;

    return ResultWithLeadingZeros;
}
