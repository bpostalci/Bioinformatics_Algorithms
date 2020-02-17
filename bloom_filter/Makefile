# c = g++ -g -fsanitize=address -O3 -std=c++0x -Wall 
c=g++ 
cflags=-O3 -std=c++0x -Wall

targets=objects/Driver.o objects/IOHelper.o objects/Murmur2.o objects/Bloomfilter.o objects/Jenkins.o objects/FNV.o
exe=bloomFilter 
common_headers=helpers/IOHelper.h data_structures/Typedefs.h

# hash algorithms paths 
murmur2_path=algos/Murmur2
jenkins_path=algos/Jenkins
fnv_path=algos/FNV

all: $(targets) 
	$(c) $(cflags) -o $(exe) $(targets)
objects/Driver.o: Driver.cpp $(common_headers)
	$(c) $(cflags) -c Driver.cpp -o $@
objects/Bloomfilter.o: data_structures/Bloomfilter.cpp data_structures/Typedefs.h
	$(c) $(cflags) -c data_structures/Bloomfilter.cpp -o $@ 
objects/IOHelper.o: helpers/IOHelper.cpp $(common_headers)
	$(c) $(cflags) -c helpers/IOHelper.cpp -o $@
objects/Murmur2.o: $(wildcard $(murmur2_path)/*) data_structures/Typedefs.h
	$(c) $(cflags) -c $(wildcard algos/Murmur2/*.cpp) -o $@
objects/Jenkins.o: $(wildcard $(jenkins_path)*) data_structures/Typedefs.h
	$(c) $(cflags) -c $(wildcard algos/Jenkins/*.cpp) -o $@
objects/FNV.o: $(wildcard $(fnv_path)/*)  data_structures/Typedefs.h
	$(c) $(cflags) -c $(wildcard algos/FNV/*.cpp) -o $@

.PHONY: clean
clean:
	rm $(targets) $(exe)
