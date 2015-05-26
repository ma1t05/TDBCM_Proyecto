
OBJS = TSPMO.o \
	MST.o \
	BiObjetivo_TSP.o \
	klein-tardos.o

TSP_MC: src/main.cpp $(OBJS)
	g++ src/main.cpp $(OBJS) -I./include -o TSP_MC -Wall

TSPMO.o: src/TSPMO.cpp include/TSPMO.h
	g++ -c src/TSPMO.cpp -I./include -o TSPMO.o -Wall

MST.o: src/MST.cpp include/MST.h
	g++ -c src/MST.cpp -I./include -o MST.o -Wall

BiObjetivo_TSP.o: src/BiObjetivo_TSP.cpp include/BiObjetivo_TSP.h
	g++ -c src/BiObjetivo_TSP.cpp -I./include -o BiObjetivo_TSP.o -Wall

klein-tardos.o: src/klein-tardos.cpp \
	include/klein-tardos.h \
	include/indexedlist.h \
	include/priqueue.h
	g++ -c src/klein-tardos.cpp -I./include -o klein-tardos.o -Wall