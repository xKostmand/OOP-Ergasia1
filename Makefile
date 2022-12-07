CXX=x86_64-w64-mingw32-g++
CXXFLAGS=-g -I include
LDFLAGS=-L lib -static -static-libgcc -static-libstdc++
LDLIBS=-lraylib -lopengl32 -lgdi32 -lwinmm

#add all .o files here
main: src/main.o src/implementation.o
		$(CXX) $^ -o $@ $(LDFLAGS) $(LDLIBS)

#add all .o files than need local .h files
src/implementation.o: src/Classes.h
src/main.o: src/Classes.h

.PHONY: clean
clean:
		rm -f src/main.o src/implementation.o