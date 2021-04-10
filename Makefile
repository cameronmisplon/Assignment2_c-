Extractor.exe: Extractor.o
	g++ Extractor.o -o Extractor.exe -std=c++2a
Extractor.o: Extractor.cpp
	g++ -c Extractor.cpp -o Extractor.o -std=c++2a
clean:
	rm *.o Extractor.exe
run:
	chmod 700 Extractor.exe
	./Extractor.exe
