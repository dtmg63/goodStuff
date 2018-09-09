CUDA_INSTALL_PATH = /usr/local/cuda
CXX      = g++
CC       = gcc
CCFLAGS  = -03  -fPIC #-g -Wall
CXXFLAGS = -03
NVCC     = nvcc --ptxas-options=-v
INCLUDES = -I$(CUDA_INSTALL_PATH)/include -I$(CUDA_INSTALL_PATH)/samples/common/inc
LDFLAGS  = -lm
LIBS     = -L$(CUDA_INSTALL_PATH)/lib -lcudart -lcufft


OBJS = fftBench3.cu
TARGET = exec
LINKLINE = $(LINK) -o $(TARGET) $(OBJS) $(LIB_CUDA)

#.SUFFIXES: .c .cpp .cu .o

#%.c.o: %.c
#        $(CC) $(CFLAGS) -c $< -o $@

#%.cu.o: %.cu
#        $(NVCC) $(NVCCFLAGS) -c $< -o $@

#%.cpp.o: %.cpp
#        $(CXX) $(CXXFLAGS) -c $< -o $@



fftBench3: fftBench3.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LIBS)

fftBench3.o: fftBench3.cu
	$(NVCC) -c $(NVCCFLAGS) $(INCLUDES) $<

.PHONY: clean cleanest

clean:
	rm -rf *.o

cleanest: clean
	rm -rf fftBench3.o fftBench3

#------------------------------------
# $@ name of the target
# $^ name of all prerequisites with duplicates removed
# $< name of the first prerequisite

# A good advanced example that handles dependencies:
# https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html




