# c = g++ -g -fsanitize=address -O3 -std=c++0x -Wall 
# c = g++ -g -O3 -std=c++0x -Wall 
c = g++ -O3 -std=c++0x -Wall 

objects = objects/Driver.o objects/IOHelper.o objects/NeedlemanWunschAffineAlignment.o objects/MYUPGMA.o
exe = buildUPGMA
common_headers = helpers/IOHelper.h data_structures/Typedefs.h data_structures/Seq.h

$(exe): $(objects)
	$(c) -o $(exe) $(objects)

objects/Driver.o: Driver.cpp $(common_headers) 
	$(c) -c Driver.cpp -o objects/Driver.o

objects/IOHelper.o: helpers/IOHelper.cpp $(common_headers)
	$(c) -c helpers/IOHelper.cpp -o objects/IOHelper.o

objects/NeedlemanWunschAffineAlignment.o: algos/NeedlemanWunschAffineAlignment.cpp algos/NeedlemanWunschAffineAlignment.h
	$(c) -c algos/NeedlemanWunschAffineAlignment.cpp -o objects/NeedlemanWunschAffineAlignment.o

objects/MYUPGMA.o: algos/MYUPGMA.cpp data_structures/MyCluster.h
	$(c) -c algos/MYUPGMA.cpp -o objects/MYUPGMA.o

.PHONY: clean
clean:
	rm $(objects) $(exe)
