CPP=g++ -g
RM=rm -f

graph : graphList.o graphMatrix.o main.o arrete.o auxi.o
	$(CPP) $^ -o $@


# On vérifie les dépendances
graphList.o : arrete.h graphList.cpp graphList.h graphMatrix.h
graphMatrix.o : arrete.h graphMatrix.cpp graphMatrix.h graphList.h
arrete.o : arrete.cpp
main.o : main.cpp graphList.h graphMatrix.h arrete.h auxi.h
auxi.o : auxi.cpp arrete.h graphList.h graphMatrix.h



%.o:%.cpp
	$(CPP) -o $@ -c $<

clean:
	$(RM) *.o graph

.PHONY: clean



