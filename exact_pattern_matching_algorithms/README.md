# General Information 
  
  * Implementation of Brute force search, Knuth-Morris-Pratt, Boyer-Moore and Rabin-Karp pattern matching algorithms

	* Entry point of the program resides in "Driver.cpp".

	* Under "db" directory "pattern.fa" and "text.fa" files exist and contains pattern and dna information respectively to be used by the program.
	  If the paths of these files should be changed, the first lines of the main function in "Driver.cpp" should be edited.

	* There are 5 source code files ending with ".cpp" which contain implementations of their corresponding header files.
	  Header files of algorihms provide necessary interface to the client such as "Driver.cpp" file to be called.

	* Other than algorihms' header files, there are 2 additional header files: "Typedefs.h" which provides common typedefs to other files,
	  "Alphabet.h" which provides alphabet information to "RabinKarpSearch.cpp" and "BoyerMooreSearch.cpp" files.

# Compilation Process 

	* The program should be compiled with "make" tool using "Makefile" in the current directory. After building the program final "driver.exe" executable which should be run. 

	* The program is tested with "g++" compiler, it works on both Windows system through "MinGW" and Linux system. There is "#pragma warning(disable:4996)" line at the beginning
	  of the "Driver.cpp" to disable warning from Microsoft C++ Compiler on Windows system. On Linux system, "g++" displays ignoring message for this pragma.

	* When a source file is changed, just that file is recompiled and relinked to generate "driver.exe" executable file with make script.

	* Makefile also contains "clean" option to clear all object and executable files.
