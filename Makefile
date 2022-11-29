CXX=x86_64-w64-mingw32-g++
CXXFLAGS=-I include
LDFLAGS=-L lib -static -static-libgcc -static-libstdc++
LDLIBS=-lraylib -lopengl32 -lgdi32 -lwinmm

src/main.o: include/Classes.h

main: src/main.o, src/implementation.o
		$(CXX) $^ -o $@ $(LDFLAGS) $(LDLIBS)

.PHONY: clean
clean:
		rm -f main.exe src/main.o