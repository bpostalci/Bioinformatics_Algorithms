# c = g++ -O3 -std=c++0x -Wall 
c = clang++ -O3 -std=c++0x -Wall 

objects = Driver.o IOHelper.o AlignmentCommon.o LocalAlignmentCommon.o NeedlemanWunschAlignment.o\
		  NeedlemanWunschAffineAlignment.o SmithWatermanAlignment.o SmithWatermanAffineAlignment.o 
alns = global-naiveGap.aln global-affineGap.aln local-naiveGap.aln local-affineGap.aln
exe = allalign

$(exe): $(objects)
	$(c) -o $(exe) $(objects)

Driver.o: Driver.cpp
	$(c) -c Driver.cpp -o Driver.o

IOHelper.o: IOHelper.cpp
	$(c) -c IOHelper.cpp -o IOHelper.o

AlignmentCommon.o: AlignmentCommon.cpp
	$(c) -c AlignmentCommon.cpp -o AlignmentCommon.o

LocalAlignmentCommon.o: LocalAlignmentCommon.cpp
	$(c) -c LocalAlignmentCommon.cpp -o LocalAlignmentCommon.o

NeedlemanWunschAlignment.o: NeedlemanWunschAlignment.cpp
	$(c) -c NeedlemanWunschAlignment.cpp -o NeedlemanWunschAlignment.o

NeedlemanWunschAffineAlignment.o: NeedlemanWunschAffineAlignment.cpp
	$(c) -c NeedlemanWunschAffineAlignment.cpp -o NeedlemanWunschAffineAlignment.o

SmithWatermanAlignment.o: SmithWatermanAlignment.cpp
	$(c) -c SmithWatermanAlignment.cpp -o SmithWatermanAlignment.o

SmithWatermanAffineAlignment.o: SmithWatermanAffineAlignment.cpp
	$(c) -c SmithWatermanAffineAlignment.cpp -o SmithWatermanAffineAlignment.o

.PHONY: clean
clean:
	rm $(objects) $(exe)

.PHONY: alnclean
alnclean:
	rm $(alns)

