c = g++ -O3 -std=c++0x -Wall 

objects = Driver.o IOHelper.o 
exe = buildUPGMA
common_headers = IOHelper.h Typedefs.h Seq.h

$(exe): $(objects)
	$(c) -o $(exe) $(objects)

Driver.o: Driver.cpp $(common_headers) 
	$(c) -c Driver.cpp -o Driver.o

IOHelper.o: IOHelper.cpp $(common_headers)
	$(c) -c IOHelper.cpp -o IOHelper.o

.PHONY: clean
clean:
	rm $(objects) $(exe)
