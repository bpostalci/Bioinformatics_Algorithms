# General Information 
  
  * Implementation of Brute force search, Knuth-Morris-Pratt, Boyer-Moore and Rabin-Karp pattern matching algorithms

  * Entry point of the program resides in "Driver.cpp".

  * Under "db" directory "pattern.fa" and "text.fa" files exist and they contain pattern and DNA information.

  * There are 5 source code files ending with ".cpp" which contain implementations of their corresponding header files.
	  Header files of algorithms provide necessary interface to the client such as "Driver.cpp".
  
  * Other than algorihms' header files, there are 2 additional header files: "Typedefs.h" which provides common typedefs to other files,
	  "Alphabet.h" which provides alphabet information to "RabinKarpSearch.cpp" and "BoyerMooreSearch.cpp" files.

# Compilation Process 

  * The program should be compiled with "make" tool using "Makefile" in the current directory. Compilation output will "driver.exe" executable file. 

  * The program is tested with "gcc" compiler. There is "#pragma warning(disable:4996)" line at the beginning of the "Driver.cpp" to disable warning from Microsoft C++ Compiler. 

  * Makefile also contains "clean" option to clear all object and executable files.
