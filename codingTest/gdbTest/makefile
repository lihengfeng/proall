#makefile
CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g
LDFLAGS=-g
LDLIBS=
AR=ar

SRCS=main.cc functions.cc
OBJS=$(subst .cc,.o,$(SRCS))

.PHONY: all
all: main
	
main: $(OBJS)
	@echo $(OBJS)
	$(CXX)  $(OBJS) -o main -g 
		    
#main.o: main.cc functions.h 
#functions.o: functions.h functions.cc

%.o: %.cc
	g++ $<  -g -c

.PHONY: clean 
clean:
	$(RM) $(OBJS)

all-clean: clean
	    $(RM) main
