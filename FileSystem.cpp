#pragma once

// Libraries
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <math.h> /* ceil */

#include "FileSystem.SupportFunc.cpp"

class FileSystem
{
private:
    int BlockSize = 256;          // default Block size is 256 bits (characters)
    int DirectoryTableSize = 256; // in units of blocks
    int VolumeSize = 2048;        // in units of blocks
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
                line = line.substr(0, this->DirectoryTableSize * this->BlockSize);
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
    FileSystem(const char *FileName = "volume.txt")
    {
        srand(time(0));
        // this->_FILENAME = FileName;
        BuildVolume(FileName);
        BuildDirectoryTable();
        // FileSystemCommand();
    }

    void BuildVolume(const char *fname = "volume.txt") const
    {
        std::cout << fname << " is being created..." << std::endl;
        // remove file if it exists
        if (remove(fname) == 0)
            printf("The file is deleted successfully...\n");
        else
            printf("The file is not deleted...\n");

        // build file
        unsigned int size = this->VolumeSize * this->BlockSize;

        std::string text("");
        for (int i = 0; i < size; i++)
        {
            // std::string s = "0123456789";
            // char c = s[rand() % 10];
            // text += c;
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

    void BuildDirectoryTable() const
    {
        std::string text = "00000000000.DirectoryTable,0000|";

        for (int i = 1; i < this->DirectoryTableSize * this->BlockSize / 32; i++)
            text += "00000000000000000000000000,0000|";

        std::fstream file;
        file.open("volume.txt");
        file.seekp(0, std::ios::beg);
        file.write(text.c_str(), text.size());
        file.close();
        print("Done");
    }

    int FindFreeBlock() const
    {
        std::fstream file;
        file.open("volume.txt");
        std::string line;
        if (file.is_open())
        {
            getline(file, line);
            line = line.substr(this->DirectoryTableSize * this->BlockSize);
        }
        file.close();

        std::vector<int> FreeBlocks;
        for (int i = 0; i < line.size(); i += this->BlockSize)
        {
            if (line[i] == '0')
                FreeBlocks.push_back((i / this->BlockSize) + this->BlockSize);
        }

        int Range = FreeBlocks.size() - 1 + 1;
        int Random = rand() % Range + 1;

        return FreeBlocks[Random];
    }

    void WriteWrapper(std::string FileName, std::string input) const
    {
        // base case if filename exceeds length limit
        if (FileName.length() > 26)
        {
            std::cerr << "Max FileName length is 26" << std::endl;
            return;
        }

        // load DT into memory
        auto DT = GetDirectoryTable();

        // check if the filename already exists
        for (auto i : DT)
        {
            std::string str = i[0];
            if (str.find(FileName) != std::string::npos)
            {
                std::cerr << "err: duplicate filename" << std::endl;
                return;
            }
        }

        // insert filename into the DT
        int DTEntryIndex;
        for (int i = 0; i < DT.size(); i++)
        {
            if (DT[i][0] == "00000000000000000000000000")
            {
                DTEntryIndex = i;
                std::string fname;
                for (int i = 0; i < (26 - FileName.length()); i++)
                    fname += '0';

                DT[i][0] = fname + FileName;
                break;
            }
        }

        // insert index block into DT
        std::string hex = DecToHex(FindFreeBlock());
        DT[DTEntryIndex][1] = hex;
        WriteDirectoryTable(DT);

        // insert all other indecies into the the Index Block in the writable volume
        std::fstream file;
        file.open("volume.txt");
        std::string line;
        if (file.is_open())
        {
            getline(file, line);
            line = line.substr(this->DirectoryTableSize * this->BlockSize);
        }
        file.close();

        int BlocksNeeded = ceil(float(input.length()) / float(this->BlockSize));
        std::string IndexBuffer = "";
        for (int i = 0; i < BlocksNeeded; i++)
        {
            std::string temp = DecToHex(FindFreeBlock());
            IndexBuffer += temp;
        }

        for (int i = 0; i < IndexBuffer.length(); i++)
        {
            line[HexToDec(hex) * this->BlockSize + i] = IndexBuffer[i];
        }

        file.open("volume.txt");
        file.seekp(this->BlockSize * this->DirectoryTableSize + 1, std::ios::beg);
        file.write(line.c_str(), line.size());
        file.close();

        // insert the data stream into the blocks
        for (int i = 0; i < IndexBuffer.length(); i += 4)
        {
            std::string s = IndexBuffer.substr(i, 4);
            WriteToVolume(HexToDec(s), input.substr((i / 4) * this->BlockSize, this->BlockSize));
        }
    }

    void Delete(std::string FileName) const
    {
        auto DT = GetDirectoryTable();

        for(int i=0; i<DT.size(); i++)
        {
            if(DT[i][0].find(FileName) != std::string::npos)
            {
                DT[i][0] = "00000000000000000000000000";
                DT[i][1] = "0000";
            }
        }
        WriteDirectoryTable(DT);
    }

    std::string Read(std::string FileName) const
    {
        auto DT = GetDirectoryTable();
        int block = 0;
        for (int i = 0; i < DT.size(); i++)
            if (DT[i][0].find(FileName) != std::string::npos)
                block = HexToDec(DT[i][1]);

        std::cout << DecToHex(block) << std::endl;
        std::cout << GetBlock(block) << std::endl;
        return "";
    }

    void FileSystemCommand() const
    {
        std::string s = "";
        while (true)
        {
            std::cout << "\033[1;31m╭─user@FileSystem\033[0m\n\033[1;31m╰─$ \033[0m";
            std::cin >> s;

            std::vector<std::string> input = extract_strings(s);

            if (input[0] == "exit")
                break;
            else
                std::cout << "command not found: " << s << std::endl;
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
        file.seekp(0, std::ios::beg);
        file.write(text.c_str(), text.size());
        file.close();
    }

    void Write(std::string FileName) const
    {
        std::fstream file;
        file.open(FileName);
        std::string line;
        if (file.is_open())
        {
            getline(file, line);
        }
        WriteWrapper(FileName, line);
        file.close();
    }

    // @description overwrites a block within the writable volume
    // @param BlockIndex: the index block which will be overwritten
    // @param Input: the input data stream in form string that will be used to overwrite
    void WriteToVolume(int BlockIndex, std::string Input) const
    {
        std::fstream file;
        file.open("volume.txt");
        file.seekp(BlockIndex * this->BlockSize, std::ios::beg);
        file.write(Input.c_str(), Input.size());
        file.close();
    }

    // @description: retrive the datastream of block given an index
    // @param BlockIndex: the block index wanted for reterival
    // @return the string stream of the data
    std::string GetBlock(int BlockIndex) const
    {
        std::fstream file;
        file.open("volume.txt");
        std::string line;
        if (file.is_open())
        {
            getline(file, line);
            int size = BlockIndex * this->BlockSize;
            line = line.substr(size, this->BlockSize);
        }
        file.close();

        return line;
    }

    // @description: wrapper method: transfers DirectoryTable from storage to memeory
    // @return a std::vector<std::vector<std::string>> with the specified table contents inside
    std::vector<std::vector<std::string>> GetDirectoryTable() const { return TabletoMemory(0); }

    // getters
    int GetBlockSize() const { return this->BlockSize; }
    int GetDirectoryTableSize() const { return this->DirectoryTableSize; }

    // setters
    void SetBlockSize(int size) { this->BlockSize = size; }
    void SetDirectoryTableSize(int size) { this->DirectoryTableSize = size; }
};
