MAIN 		= sim.cpp
COMPFLAGS	= -std=c++11 -o
LINKFLAGS	= -lsfml-graphics -lsfml-window -lsfml-system
COMPILER 	= g++
EXEC		= space2d 

all: main

main : $(PROGRAMS)
	$(COMPILER) $(COMPFLAGS) $(EXEC) $(MAIN) $(LINKFLAGS)

pure : 
	rm $(EXEC)

