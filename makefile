MAIN 		= sim.cpp
CLASSES		= #particle.cpp
COMPFLAGS	= -std=c++11 -o
LINKFLAGS	= -lsfml-graphics -lsfml-window -lsfml-system
COMPILER 	= g++
EXEC		= space2d 

all: main

main : $(PROGRAMS)
	$(COMPILER) $(COMPFLAGS) $(EXEC) $(MAIN) $(CLASSES) $(LINKFLAGS)

pure : 
	rm $(EXEC)

