c = g++ -O3 -std=c++0x -Wall 

objects = Driver.o IOHelper.o NeedlemanWunschAlignment.o NeedlemanWunschAffineAlignment.o
exe = allalign

$(exe): $(objects)
	$(c) -o $(exe) $(objects)

Driver.o: Driver.cpp
	$(c) -c Driver.cpp -o Driver.o

IOHelper.o: IOHelper.cpp
	$(c) -c IOHelper.cpp -o IOHelper.o

NeedlemanWunschAlignment.o: NeedlemanWunschAlignment.cpp
	$(c) -c NeedlemanWunschAlignment.cpp -o NeedlemanWunschAlignment.o

NeedlemanWunschAffineAlignment.o: NeedlemanWunschAffineAlignment.cpp
	$(c) -c NeedlemanWunschAffineAlignment.cpp -o NeedlemanWunschAffineAlignment.o

.PHONY: clean
clean:
	rm $(objects) $(exe)

