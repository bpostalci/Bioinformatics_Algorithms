c = g++ -O3 -std=c++0x -Wall 

objects = Driver.o FileHelper.o BurrowsWheelerTransform.o
exe = bwtfm.exe

$(exe): $(objects)
	$(c) -o $(exe) $(objects)

Driver.o: Driver.cpp
	$(c) -c Driver.cpp -o Driver.o

FileHelper.o: FileHelper.cpp
	$(c) -c FileHelper.cpp -o FileHelper.o

BurrowsWheelerTransform.o: BurrowsWheelerTransform.cpp
	$(c) -c BurrowsWheelerTransform.cpp -o BurrowsWheelerTransform.o

.PHONY: clean
clean:
	rm $(objects) $(exe)
