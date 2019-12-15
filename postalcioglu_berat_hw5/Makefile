c = g++ -O3 -std=c++0x -Wall 

objects = objects/Driver.o objects/IOHelper.o objects/NeedlemanWunschAffineAlignment.o objects/UPGMA.o
exe = buildUPGMA
common_headers = helpers/IOHelper.h data_structures/Typedefs.h data_structures/Seq.h

$(exe): $(objects)
	$(c) -o $(exe) $(objects)

objects/Driver.o: Driver.cpp $(common_headers) 
	$(c) -c Driver.cpp -o objects/Driver.o

objects/IOHelper.o: helpers/IOHelper.cpp $(common_headers)
	$(c) -c helpers/IOHelper.cpp -o objects/IOHelper.o

objects/NeedlemanWunschAffineAlignment.o: algos/NeedlemanWunschAffineAlignment.cpp
	$(c) -c algos/NeedlemanWunschAffineAlignment.cpp -o objects/NeedlemanWunschAffineAlignment.o

objects/UPGMA.o: algos/UPGMA.cpp
	$(c) -c algos/UPGMA.cpp -o objects/UPGMA.o

.PHONY: clean
clean:
	rm $(objects) $(exe)
