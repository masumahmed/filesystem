// Libraries
#include "FileSystem.cpp"
#include "SupportFunc.cpp"
#include "test.cpp"

int main()
{
    FileSystem fs("volume.txt", 1000);
    // FileSystem fs;
    // fs.BuildVolume("volume.txt", 1000); // Create a 1000 Block virtual file
    // fs.BuildFAT();
    // fs.BuildDirectoryTable();

    fs.WriteFAT(fs.GetFAT());

    print("FAT");
    print("--------");
    for (auto &i : fs.GetFAT())
    {
        for (auto &j : i)
        {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    print("Directory Table");
    print("--------");
    for (auto &i : fs.GetDirectoryTable())
    {
        for (auto &j : i)
        {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }

    fs.WriteDirectoryTable(fs.GetDirectoryTable());

    std::cout << std::endl;
    print("Directory Table");
    print("--------");
    for (auto &i : fs.GetDirectoryTable())
    {
        for (auto &j : i)
        {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}
