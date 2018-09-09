CC       = g++ 
CCFLAGS  = -std=c++0x -O3  #-g -Wall
INCLUDES = #-I/home/scale/g++Projects/gLib/
LDFLAGS  = -lm

all: findHiddenState clean

findHiddenState: findHiddenState.o
	$(CC) $(CCFLAGS) -o $@ $^ $(LDFLAGS)

findHiddenState.o: findHiddenState.cpp
	$(CC) -c $(INCLUDES) $<


clean:
	rm -rf *.o

cleanest: clean
	rm findHiddenState

#------------------------------------
# $@ name of the target
# $^ name of all prerequisites with duplicates removed
# $< name of the first prerequisite

# A good advanced example that handles dependencies:
# https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html

