CXX	= g++
CXXFLAGS= -Wall -ansi -g -std=c++11   #-std=c++0x
CC	= gcc
CCFLAGS	= -g
OBJS	= main.o client.o
#INCLUDES = -I/
LDFLAGS  = -lm


tester : $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $<

%.o : %.c
	$(CC) -c $(CCFLAGS) $<

clean:
	rm -rf *.o

cleanest: clean
	rm tester

