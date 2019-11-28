c = g++ -O3 -std=c++0x -Wall 

objects = Driver.o IOHelper.o SequenceToProfile.o
exe = alignSeqToProfile

$(exe): $(objects)
	$(c) -o $(exe) $(objects)

Driver.o: Driver.cpp
	$(c) -c Driver.cpp -o Driver.o

IOHelper.o: IOHelper.cpp
	$(c) -c IOHelper.cpp -o IOHelper.o

SequenceToProfile.o: SequenceToProfile.cpp
	$(c) -c SequenceToProfile.cpp -o SequenceToProfile.o

.PHONY: clean
clean:
	rm $(objects) $(exe)