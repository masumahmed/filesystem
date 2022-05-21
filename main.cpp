// Libraries
#include "FileSystem.cpp"
#include "FileSystem.SupportFunc.cpp"
#include "test.cpp"

int main()
{
    FileSystem fs("volume.txt");
    fs.WriteWrapper("test.txt", "1HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH2HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH3HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH4HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH");
    // std::cout << fs.Read("test.txt") << std::endl;
    fs.Read("test.txt");
    std::cout << fs.GetBlock(HexToDec("05F6")) << std::endl;
    std::cout << fs.GetBlock(2048) << std::endl;

    fs.Write("hello.txt");

    // FileSystem fs;
    // fs.BuildVolume("volume.txt", 1000); // Create a 1000 Block virtual file
    // fs.BuildDirectoryTable();

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
