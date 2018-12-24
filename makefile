COMPILER=g++ -std=c++0x
CFLAGS=-Wall -Werror
EXECUTABLE=lab3

SOURCES=main.cpp lazy_sync_set.cpp cg_sync_set.cpp

all: $(SOURCES)
	$(COMPILER) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES) -lpthread
clean:
	rm -f *.o $(EXECUTABLE)