Extractor.exe: Extractor.o FrameSequence.o
	g++ FrameSequence.o Extractor.o -o Extractor.exe -std=c++2a
Extractor.o: Extractor.cpp
	g++ -c Extractor.cpp -o Extractor.o -std=c++2a
FrameSequence.o: FrameSequence.cpp
	g++ -c FrameSequence.cpp -o FrameSequence.o -std=c++2a
clean:
	rm *.o Extractor.exe
