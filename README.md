# Pokemon Data Query

## Description:

The program uses multi-threading and dynamic memory allocation to read, copy, and write data from a .csv file while simultaneously processing user input.  After verifying that the “pokemon.csv” data file exists in the user’s working directory, the program asks the user whether they would like to search the file for Pokemon of a specific type.  The user also has the option to write their query results to a new file at any time.  

The purpose of the program is to demonstrate the efficiency of using multi-threading when, for example, performing operations on a large dataset or database.  Future improvements would involve expanding search criteria, developing the user interface, and incorporating larger, more comprehensive datasets.

## Requirements:

The program requires a C compiler and POSIX thread support.  The file “pokemon.csv” must also be in the current working directory.

## To build and run the program:

Open a command-line interface and navigate to the directory containing the file “main.c.”  To build the program, use the command “make” or “gcc -Wall -pthread main.c appendMain.c createPokemon.c addPokemon.c cleanUp.c copyData.c createFile.c fileCheck.c -o main.”  To run the program, use “./main.” 

## Notes:

The program was tested on macOS 15.7 using Clang.


