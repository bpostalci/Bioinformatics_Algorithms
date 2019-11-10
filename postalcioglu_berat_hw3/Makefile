c = g++ -O3 -std=c++0x -Wall 

objects = Driver.o IOHelper.o ScoreMatrix.o NeedlemanWunschAlignment.o
exe = allalign

$(exe): $(objects)
	$(c) -o $(exe) $(objects)

Driver.o: Driver.cpp
	$(c) -c Driver.cpp -o Driver.o

IOHelper.o: IOHelper.cpp
	$(c) -c IOHelper.cpp -o IOHelper.o

ScoreMatrix.o: ScoreMatrix.cpp
	$(c) -c ScoreMatrix.cpp -o ScoreMatrix.o

NeedlemanWunschAlignment.o: NeedlemanWunschAlignment.cpp
	$(c) -c NeedlemanWunschAlignment.cpp -o NeedlemanWunschAlignment.o

.PHONY: clean
clean:
	rm $(objects) $(exe)

