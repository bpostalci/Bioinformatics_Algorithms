c = g++ -O3 -std=c++0x -Wall 

objects = Driver.o 
exe = allalign

$(exe): $(objects)
	$(c) -o $(exe) $(objects)

Driver.o: Driver.cpp
	$(c) -c Driver.cpp -o Driver.o

.PHONY: clean
clean:
	rm $(objects) $(exe)

