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

void CreateVolume(const char* fname = "volume.txt", int bits=0, int bytes=0, int kilobytes=0, int megabytes=0)
{
    std::cout << fname << std::endl;
    // remove file if it exists
    if (remove(fname) == 0) {
        printf("The file is deleted successfully.\n");
    } else {
        printf("The file is not deleted.\n");
    }
    
    // build file
    unsigned int size = bits + 8*bytes + 8000*kilobytes + 8000000*megabytes;
    std::string text("");
    for(int i=0; i<size; i++)
    {
        text+='0';
    }
    text+='\n';

    // create and build files
    std::string volume(fname);
    std::fstream outfile;
    outfile.open(volume, std::ios_base::app);
    if (!outfile.is_open()) {
        std::cerr << "failed to open " << volume << '\n';
    } else {
        outfile.write(text.data(), text.size());
        std::cerr << "Done Writing!" << std::endl;
    }
}
