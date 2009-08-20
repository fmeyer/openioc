INCLUDE=-Iinclude
SRC=source
CC=g++
#AIX compiler otimization
#CC= xlC_r -bmaxdata:0x80000000 -O3 -qstrict -qnoansialias -qlibansi -qro -qtune=pwr5
DEBUG=-ggdb
CXXFLAGS = -pipe -Wall -W -O2 $(DEBUG)

OBJS= istring.o \
      itime.o \
      iexception.o \
      idate.o \
      iexceptionlocation.o \

ERASE = rm
BIN=bin
LIBNAME = libstlioc
LIB=$(BIN)/${LIBNAME}.a

all: $(OBJS)
	ar -v -q $(LIB) $(OBJS)
	chmod go+rx $(BIN)/*	

istring.o: 
	$(CC) $(CXXFLAGS) $(INCLUDE) -c $(SRC)/istring.cpp 

itime.o: 
	$(CC) $(CXXFLAGS) $(INCLUDE) -c $(SRC)/itime.cpp 

iexception.o:
	$(CC) $(CXXFLAGS) $(INCLUDE) -c $(SRC)/iexception.cpp 
	
idate.o:
	$(CC) $(CXXFLAGS) $(INCLUDE) -c $(SRC)/idate.cpp  
	
iexceptionlocation.o:
	$(CC) $(CXXFLAGS) $(INCLUDE) -c $(SRC)/iexceptionlocation.cpp

clean: 
	$(ERASE) $(OBJS) $(LIB)
