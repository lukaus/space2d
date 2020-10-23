MAIN 		= space2d.cpp
CLASSES		= src/simulation.cpp src/node.cpp src/nodelist.cpp src/particle.cpp src/date.cpp
COMPFLAGS	= -std=c++17 -o
LINKFLAGS	= -lsfml-graphics -lsfml-window -lsfml-system
COMPILER 	= g++
EXEC		= space2d 
DEBUG_EXEC	= dbg-space2d 

all: main

main : $(PROGRAMS)
	$(COMPILER) $(COMPFLAGS) $(EXEC) $(MAIN) $(CLASSES) $(LINKFLAGS)

pure : 
	rm $(EXEC)

debug: $(PROGRAMS)
	$(COMPILER) -g $(COMPFLAGS) $(DEBUG_EXEC) $(MAIN) $(CLASSES) $(LINKFLAGS)
