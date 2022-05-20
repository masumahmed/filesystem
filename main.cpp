// Libraries
#include "FileSystem.cpp"
#include "FileSystem.SupportFunc.cpp"
#include "test.cpp"

int main()
{
    FileSystem fs("volume.txt", 1000);
    fs.Write("test.txt", "Hello World");

    // FileSystem fs;
    // fs.BuildVolume("volume.txt", 1000); // Create a 1000 Block virtual file
    // fs.BuildFAT();
    // fs.BuildDirectoryTable();

    // fs.WriteFAT(fs.GetFAT());

    // print("FAT");
    // print("--------");
    // for (auto &i : fs.GetFAT())
    // {
    //     for (auto &j : i)
    //     {
    //         std::cout << j << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << std::endl;
    // print("Directory Table");
    // print("--------");
    // for (auto &i : fs.GetDirectoryTable())
    // {
    //     for (auto &j : i)
    //     {
    //         std::cout << j << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // fs.WriteDirectoryTable(fs.GetDirectoryTable());

    // std::cout << std::endl;
    // print("Directory Table");
    // print("--------");
    // for (auto &i : fs.GetDirectoryTable())
    // {
    //     for (auto &j : i)
    //     {
    //         std::cout << j << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // for (auto &i: extract_strings("testing testing testing test"))
    //     std::cout << i << std::endl;

    // auto FAT = fs.GetFAT();

    // for (int i = 0; i < FAT.size(); i++){
    //     print("|" + FAT[i][0] + "|" + FAT[i][1] + "|");
    // }

    
}
