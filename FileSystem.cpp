#pragma once

// Libraries
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include "SupportFunc.cpp"

class FileSystem
{
private:
public:
    void CreateVolume(const char *fname = "volume.txt", int bits = 0, int bytes = 0, int kilobytes = 0, int megabytes = 0)
    {
        std::cout << fname << std::endl;
        // remove file if it exists
        if (remove(fname) == 0)
        {
            printf("The file is deleted successfully.\n");
        }
        else
        {
            printf("The file is not deleted.\n");
        }

        // build file
        unsigned int size = bits + 8 * bytes + 8000 * kilobytes + 8000000 * megabytes;
        std::string text("");
        for (int i = 0; i < size; i++)
        {
            text += '0';
        }
        text += '\n';

        // create and build files
        std::string volume(fname);
        std::fstream outfile;
        outfile.open(volume, std::ios_base::app);
        if (!outfile.is_open())
        {
            std::cerr << "failed to open " << volume << '\n';
        }
        else
        {
            outfile.write(text.data(), text.size());
            std::cerr << "Done Writing!" << std::endl;
        }
    }

    void FAT()
    {
        print("Done");
        int TableSizeMB = 5; // table size 5 MB

        std::string text = "filename, block, ";
        std::string buffer = "";
        for (auto &i : text)
            buffer += std::bitset<8>(i).to_string();

        std::fstream file;
        file.open("volume.txt");
        file.seekp(0, std::ios::beg);
        file.write(buffer.c_str(), buffer.size());
        file.close();
    }
};
