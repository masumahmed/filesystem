#pragma once

// Libraries
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "SupportFunc.cpp"

class FileSystem
{
private:
    int BlockSize = 256;         // Default Block size is 256 Characters
    int FATSize = 50;            // in units of blocks
    int DirectoryTableSize = 50; // in units of blocks
    const char *FlileName = "volume.txt";

public:
    void BuildVolume(const char *fname = "volume.txt", int blocks = 1000) const
    {
        std::cout << fname << " is being created..." << std::endl;
        // remove file if it exists
        if (remove(fname) == 0)
            printf("The file is deleted successfully...\n");
        else
            printf("The file is not deleted...\n");

        // build file
        unsigned int size = blocks * this->BlockSize;

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
            std::cerr << "failed to open... " << volume << '\n';
        }
        else
        {
            outfile.write(text.data(), text.size());
            std::cout << "Done Writing Volume!..." << std::endl;
        }
    }

    void BuildFAT() const
    {
        std::string text = "'.FAT',0x00000001|'.unaloc',0x00000034|";
        std::fstream file;
        file.open("volume.txt");
        file.seekp(0, std::ios::beg);
        file.write(text.c_str(), text.size());
        file.close();
        print("Done");
    }

    void BuildDirectoryTable() const
    {
        std::string text = "0,0|0,0|";
        std::fstream file;
        file.open("volume.txt");
        file.seekp((this->FATSize * this->BlockSize) + 1, std::ios::beg);
        file.write(text.c_str(), text.size());
        file.close();
        print("Done");
    }

    // @description: transfers specified table from storage to memeory
    // @param int table takes arugement 0 for FAT and 1 for DirectoryTable
    // @return a std::vector<std::vector<std::string>> with the specified table contents inside
    std::vector<std::vector<std::string>> TabletoMemory(int table = -1) const
    {
        // error handling
        if (table == -1)
            throw std::invalid_argument("No argument supplied to TabletoMemory()");

        std::vector<std::vector<std::string>> Table;
        std::vector<std::string> buffer;

        std::fstream file;
        file.open("volume.txt", std::ios::in);
        std::string line;
        if (file.is_open())
        {
            getline(file, line);
            if (table == 0)
            {
                line = line.substr(0, this->FATSize * this->BlockSize);
            }
            else if (table == 1)
            {
                line = line.substr((this->FATSize * this->BlockSize) + 1, this->DirectoryTableSize * this->BlockSize);
            }
        }

        std::string temp = "";
        for (auto &i : line)
        {
            if (i == ',')
            {
                buffer.push_back(temp);
                temp = "";
                continue;
            }
            else if (i == '|')
            {
                buffer.push_back(temp);
                temp = "";
                Table.push_back(buffer);
                buffer.clear();
                continue;
            }
            temp += i;
        }
        return Table;
    }
};
