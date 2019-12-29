# c = g++ -g -fsanitize=address -O3 -std=c++0x -Wall 
# c = g++ -g -O3 -std=c++0x -Wall 
c = g++ -O3 -std=c++0x -Wall 

objects = objects/Driver.o objects/IOHelper.o objects/Murmur2.o objects/Bloomfilter.o objects/Jenkins.o objects/FNV.o
exe = bloomFilter 
common_headers = helpers/IOHelper.h data_structures/Typedefs.h

$(exe): $(objects)
	$(c) -o $(exe) $(objects)

objects/Driver.o: Driver.cpp $(common_headers)
	$(c) -c Driver.cpp -o objects/Driver.o

objects/Bloomfilter.o: data_structures/Bloomfilter.cpp data_structures/Typedefs.h
	$(c) -c data_structures/Bloomfilter.cpp -o objects/Bloomfilter.o

objects/IOHelper.o: helpers/IOHelper.cpp $(common_headers)
	$(c) -c helpers/IOHelper.cpp -o objects/IOHelper.o

objects/Murmur2.o: algos/Murmur2.cpp algos/Murmur2.h data_structures/Typedefs.h
	$(c) -c algos/Murmur2.cpp -o objects/Murmur2.o

objects/Jenkins.o: algos/Jenkins.cpp algos/Jenkins.h data_structures/Typedefs.h
	$(c) -c algos/Jenkins.cpp -o objects/Jenkins.o

objects/FNV.o: algos/FNV.cpp algos/FNV.h data_structures/Typedefs.h
	$(c) -c algos/FNV.cpp -o objects/FNV.o

.PHONY: clean
clean:
	rm $(objects) $(exe)
