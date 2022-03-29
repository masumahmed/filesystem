# File System Simulation

This project is to demonstrate and understanding of a file systems by implementing a simulation of a file system using a text file.

The contents of the text file will include UFT-8 encoded plain text characters representing the data stored within the storage volume.

It's important to note that the storage device is 1 level abstracted from a real implementation of a file system since real file systems store their data encoded in binary.

Since encoding from UFT-8 to binary is relatively trival plain text will be used for the human readability purposes.

# Specifications
**Blcoksize**: 256 Characters

*Note: Since this project works with textfiles block sizes are not measured with traditional unit of computing (i.e. bits, bytes, kilobites, etc).*

**Allocation** 

Linked Allocation: Linked List pointers live in the last 10 characters of a block starting with the characters '0x' (i.e. 0x00005000)

**Tables**
',' is the row delimiter
'|' is the column delimiter

**FAT**

The FAT is stored in the begining of the volume. The size of the FAT is denoted by the private member variables `FATSize`.

When it encounters speical character 'e' then that is the end of linked allocation.


| Busy | Next |
| - | - |
| 0 | 0 |
| 0 | 1 |

**Directory Table**
| filename | head |
| - | - | - |
| .FAT | 0x00000001 |
| .unaloc | 0x00000034 |

# Requirements
**GCC-11**

*Note: This program does not compile properly on **Clang**...*

# Testing
to be written...

# Compile Build and Run

##### Make
`$ make` compiles and builds the application
`$ make clean` deletes generated files
`$ make run` compiles, builds and runs the application
<!-- `$ make test` compiles, builds and runs the application with test -->


##### Run
`$ ./main.out` runs the program

<hr>

**Author**: Masum Ahmed
**Email**: MasumAhmed1798@gmail.com
**Github**: https://github.com/masumahmed

**Instructor**: Soumik Dey
**Class**: CSCI 49500 Capstone Project
