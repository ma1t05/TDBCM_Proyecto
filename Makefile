
TSP_MC: src/main.cpp TSPMO.o MST.o BiObjetivo_TSP.o
	g++ src/main.cpp TSPMO.o MST.o BiObjetivo_TSP.o -I./include -o TSP_MC -Wall

TSPMO.o: src/TSPMO.cpp include/TSPMO.h
	g++ -c src/TSPMO.cpp -I./include -o TSPMO.o -Wall

MST.o: src/MST.cpp include/MST.h
	g++ -c src/MST.cpp -I./include -o MST.o -Wall

BiObjetivo_TSP.o: src/BiObjetivo_TSP.cpp include/BiObjetivo_TSP.h
	g++ -c src/BiObjetivo_TSP.cpp -I./include -o BiObjetivo_TSP.o -Wall