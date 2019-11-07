c = g++ -O3 -std=c++0x -Wall 

objects = Driver.o BruteForceSearch.o KnuthMorrisPrattSearch.o RabinKarpSearch.o BoyerMooreSearch.o
exe = driver.exe

$(exe): $(objects)
	$(c) -o driver.exe $(objects)

Driver.o: Driver.cpp
	$(c) -c Driver.cpp -o Driver.o

BruteForceSearch.o: BruteForceSearch.cpp
	$(c) -c BruteForceSearch.cpp -o BruteForceSearch.o

KnuthMorrisPrattSearch.o: KnuthMorrisPrattSearch.cpp
	$(c) -c KnuthMorrisPrattSearch.cpp -o KnuthMorrisPrattSearch.o

BoyerMooreSearch.o: BoyerMooreSearch.cpp
	$(c) -c BoyerMooreSearch.cpp -o BoyerMooreSearch.o

RabinKarpSearch.o: RabinKarpSearch.cpp
	$(c) -c RabinKarpSearch.cpp -o RabinKarpSearch.o

.PHONY: clean
clean:
	rm $(objects) $(exe)
