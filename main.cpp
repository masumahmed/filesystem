// Libraries
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include "SupportFunc.cpp"

// buffer size 8 bits
void CreateFileAllocationTable()
{
    int TableSizeMB = 5; // table size 5 MB

    std::string text = "filename, block, ";
    std::string buffer = "";
    for(auto &i: text)
        buffer += std::bitset<8>(i).to_string();

    std::fstream file;
    file.open("volume.txt");
    file.seekp(0, std::ios::beg);
    file.write(buffer.c_str(), buffer.size());
    file.close();
}

void WriteFileAllocationTable(){}
void ReadFileAllocationTable(){}

int main()
{
    // CreateVolume("volume.txt", 0, 0, 0, 25); // Create a 25 MB virtual file
    CreateFileAllocationTable();
}
