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
    int BlockSize = 256;         // default Block size is 256 Characters
    int FATSize = 50;            // in units of blocks
    int DirectoryTableSize = 50; // in units of blocks
    int VolumeSize = 1000;
    // char *_FILENAME = "";

protected:
    // @description: sub-routine transfers specified table from storage to memeory
    // @param int table takes arugement 0 for FAT and 1 for DirectoryTable
    // @return a std::vector<std::vector<std::string>> with the specified table contents inside
    auto TabletoMemory(int table = -1) const
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

public:
    FileSystem(const char *FileName = "volume.txt", int blocks = 1000)
    {
        // this->_FILENAME = FileName;
        VolumeSize = blocks;
        BuildVolume(FileName, blocks);
        BuildFAT();
        BuildDirectoryTable();
        FileSystemCommand();
    }

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
        std::string text = "0,0|12,0|";
        std::fstream file;
        file.open("volume.txt");
        file.seekp(0, std::ios::beg);
        file.write(text.c_str(), text.size());
        file.close();
        print("Done");
    }

    void BuildDirectoryTable() const
    {
        std::string text = "'.FAT',0x00000001|'.unaloc',0x00000034|";
        std::fstream file;
        file.open("volume.txt");
        file.seekp((this->FATSize * this->BlockSize) + 1, std::ios::beg);
        file.write(text.c_str(), text.size());
        file.close();
        print("Done");
    }

    // get directory path location
    // if the file exists then just reuse the head location
    // if the file doesn't exist then add it to the DirectoryTable
    //     form a link in the FAT
    //     using the FAT link write the file on the volume
    void WriteVolume() const
    {
    }

    void FileSystemCommand() const
    {
        std::string s = "";
        while (true)
        {
            std::cout << "\033[1;31m╭─user@FileSystem\033[0m\n\033[1;31m╰─$ \033[0m";
            std::cin >> s;

            if (s == "exit")
                break;
            else
                std::cout << "Not a command" << std::endl;
        }
    }

    // @description overwrites DirectoryTable with param
    // @param a vector of vector strings that will be used to overwrite the DirectoryTable
    void WriteDirectoryTable(const std::vector<std::vector<std::string>> &table) const
    {
        std::string text = "";

        for (int i = 0; i < table.size(); i++)
        {
            for (int j = 0; j < table[i].size(); j++)
            {
                text += table[i][j];
                if (j == 0)
                    text += ",";
            }
            text += "|";
        }

        int len = (GetDirectoryTableSize() * GetBlockSize()) - text.length();
        for (int i = 0; i < len; i++)
            text += '0';

        std::fstream file;
        file.open("volume.txt");
        file.seekp((this->FATSize * this->BlockSize) + 1, std::ios::beg);
        file.write(text.c_str(), text.size());
        file.close();
    }

    // @description overwrites FAT with param
    // @param a vector of vector strings that will be used to overwrite the FAT
    void WriteFAT(const std::vector<std::vector<std::string>> &table) const
    {
        std::string text = "";

        for (int i = 0; i < table.size(); i++)
        {
            for (int j = 0; j < table[i].size(); j++)
            {
                text += table[i][j];
                if (j != table[i].size() - 1)
                    text += ",";
            }
            text += "|";
        }

        std::fstream file;
        file.open("volume.txt");
        file.seekp(0, std::ios::beg);
        file.write(text.c_str(), text.size());
        file.close();
    }

    // @description: wrapper method: transfers FAT from storage to memeory
    // @return a std::vector<std::vector<std::string>> with the specified table contents inside
    auto GetFAT() const { return TabletoMemory(0); }

    // @description: wrapper method: transfers DirectoryTable from storage to memeory
    // @return a std::vector<std::vector<std::string>> with the specified table contents inside
    auto GetDirectoryTable() const { return TabletoMemory(1); }

    // getters
    int GetBlockSize() const { return this->BlockSize; }
    int GetFATSize() const { return this->FATSize; }
    int GetDirectoryTableSize() const { return this->DirectoryTableSize; }

    // setters
    void SetBlockSize(int size) { this->BlockSize = size; }
    void SetFATSize(int size) { this->FATSize = size; }
    void SetDirectoryTableSize(int size) { this->DirectoryTableSize = size; }
};
