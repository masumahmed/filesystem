// Libraries
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include "SupportFunc.cpp"
#include "FileSystem.cpp"

int main()
{
    FileSystem fs;
    fs.CreateVolume("volume.txt", 0, 0, 0, 25); // Create a 25 MB virtual file
    fs.FAT();
}

