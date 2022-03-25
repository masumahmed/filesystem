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
    // char array to store hexadecimal number
    char hexaDeciNum[100];
 
    // counter for hexadecimal number array
    int i = 0;
    while (n != 0) {
        // temporary variable to store remainder
        int temp = 0;
        temp = n % 16;
         if (temp < 10) {
            hexaDeciNum[i] = temp + 48;
            i++;
        }
        else {
            hexaDeciNum[i] = temp + 55;
            i++;
        }
 
        n = n / 16;
    }
 
    // printing hexadecimal number array in reverse order
    std::string result = "";
    for (int j = i - 1; j >= 0; j--)
        result += hexaDeciNum[j];

    std::string ResultWithLeadingZeros = "0x";
    // add try blcok for when result lenght is greater than 8
    for(int i=0; i<(8 - result.length()); i++)
    {
        ResultWithLeadingZeros += "0";
    }
    ResultWithLeadingZeros += result;

    return ResultWithLeadingZeros;
}
