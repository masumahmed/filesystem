// Libraries
#include "FileSystem.cpp"
#include "SupportFunc.cpp"
#include "test.cpp"

int main()
{
    FileSystem fs;
    // fs.CreateVolumeLinkedAllocation("volume.txt", 0, 0, 0, 10); // Create a 25 MB virtual file
    // fs.FAT();

    std::vector<std::vector<std::string>> FAT = fs.FATtoMemory();

    for (auto &i : FAT)
    {
        for (auto &j : i)
        {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}
