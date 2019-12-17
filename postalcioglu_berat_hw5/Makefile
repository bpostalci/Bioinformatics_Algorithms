# c = g++ -g -fsanitize=address -O3 -std=c++0x -Wall 
c = g++ -O3 -std=c++0x -Wall 

objects = objects/Driver.o objects/IOHelper.o objects/NeedlemanWunschAffineAlignment.o objects/UPGMA.o\
		  objects/Cluster2.o objects/Cluster.o
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

objects/Cluster2.o: data_structures/Cluster2.cpp data_structures/Cluster2.h
	$(c) -c data_structures/Cluster2.cpp -o objects/Cluster2.o

objects/Cluster.o: data_structures/Cluster.cpp data_structures/Cluster.h
	$(c) -c data_structures/Cluster.cpp -o objects/Cluster.o

objects/UPGMA.o: algos/UPGMA.cpp data_structures/Cluster.h
	$(c) -c algos/UPGMA.cpp -o objects/UPGMA.o

.PHONY: clean
clean:
	rm $(objects) $(exe)
