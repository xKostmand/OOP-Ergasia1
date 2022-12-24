CXX=x86_64-w64-mingw32-g++
CXXFLAGS=-g -I include
LDFLAGS=-L lib -static -static-libgcc -static-libstdc++
LDLIBS=-lraylib -lopengl32 -lgdi32 -lwinmm

#add all .o files here
main: src/Main.o src/Implementation.o src/Load.o src/Interactions.o src/GameFlow.o
		$(CXX) $^ -o $@ $(LDFLAGS) $(LDLIBS)

#add all .o files than need local .h files
src/Implementation.o: src/Functions.h
src/Interactions.o: src/Functions.h
src/Load.o: src/Functions.h
src/GameFlow: src/Functions.h
src/Main.o: src/Classes.h

.PHONY: clean
clean:
		rm -f src/Main.o src/Implementation.o src/Load.o src/Interactions.o src/GameFlow.o