
TSP_MC: src/main.cpp TSPMO.o MST.o	
	g++ src/main.cpp TSPMO.o MST.o -Iinclude -o TSP_MC

TSPMO.o: src/TSPMO.cpp include/TSPMO.h
	g++ -c src/TSPMO.cpp -I./include -o TSPMO.o

MST.o: src/MST.cpp include/MST.h
	g++ -c src/MST.cpp -I./include -o MST.o