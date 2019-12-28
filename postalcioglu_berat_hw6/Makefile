# c = g++ -g -fsanitize=address -O3 -std=c++0x -Wall 
# c = g++ -g -O3 -std=c++0x -Wall 
c = g++ -O3 -std=c++0x -Wall 

objects = objects/Driver.o
exe = bloomFilter 
common_headers = helpers/IOHelper.h data_structures/Typedefs.h data_structures/Seq.h

$(exe): $(objects)
	$(c) -o $(exe) $(objects)

objects/Driver.o: Driver.cpp
	$(c) -c Driver.cpp -o objects/Driver.o

.PHONY: clean
clean:
	rm $(objects) $(exe)
