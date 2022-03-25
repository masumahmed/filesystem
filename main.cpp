// Libraries
#include "FileSystem.cpp"
#include "SupportFunc.cpp"
#include "test.cpp"

int main()
{
    FileSystem fs;
    fs.CreateVolumeLinkedAllocation("volume.txt", 0, 0, 0, 25); // Create a 25 MB virtual file
    fs.FAT();
}

