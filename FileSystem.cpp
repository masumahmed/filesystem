#pragma once

// Libraries
#include <iostream>
#include <fstream>
#include <string>

#include "SupportFunc.cpp"

class FileSystem
{
private:
    int BlockSize = 256; // Default Block size is 256 Characters

public:
    void CreateVolumeLinkedAllocation(const char *fname = "volume.txt", int bits = 0, int bytes = 0, int kilobytes = 0, int megabytes = 0) const
    {
        std::cout << fname << " is being created..." << std::endl;
        // remove file if it exists
        if (remove(fname) == 0)
            printf("The file is deleted successfully...\n");
        else
            printf("The file is not deleted...\n");

        // build file
        unsigned int size = bits + 8 * bytes + 8000 * kilobytes + 8000000 * megabytes;
        std::string text("");
        int j = 1;
        for (int i = 0; i < size; i++)
        {
            if (i % (BlockSize - 8) == 0 && i != 0)  
            {
                text += DecToHex(j);
                j++;
                i+=7; // account for the length of j with the leading zeroes
                continue;
            }
            text += '0';
        }
        text += '\n';

        // create and build files
        std::string volume(fname);
        std::fstream outfile;
        outfile.open(volume, std::ios_base::app);
        if (!outfile.is_open())
        {
            std::cerr << "failed to open... " << volume << '\n';
        }
        else
        {
            outfile.write(text.data(), text.size());
            std::cout << "Done Writing Volume!..." << std::endl;
        }
    }

    void FAT() const
    {
        std::string text = "'.FAT',0x00000000,0x00000032|'.unaloc',0x00000033,0x00098968|";
        std::fstream file;
        file.open("volume.txt");
        file.seekp(0, std::ios::beg);
        file.write(text.c_str(), text.size());
        file.close();
        print("Done");
    }
};
