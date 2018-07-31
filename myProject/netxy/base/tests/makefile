VPATH=../ 
DIRS= .. .
HS= $(foreach dir, $(DIRS), $(wildcard $(dir)/*.h))
CS= $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))
OBJS= $(patsubst  %.cpp, %.o, $(CS))
CXXFLAGS=-std=c++11 
LIBS= -lnetxy -pthread 
TARGETS=testCdebug testThreadPool testTimeStamp testBuffer 

.PHONY:all
all:$(OBJS) $(TARGETS)
	@echo $(HS) 
	@echo $(CS) 
	@echo $(OBJS)

testCdebug:Cdebug.h 
	g++ testCdebug.cpp -o $@ $(CXXFLAGS) $(LIBS)
testBuffer:Buffer.o Cdebug.h 
	g++ testBuffer.cpp -o $@ $(CXXFLAGS) $(LIBS)
testThreadPool:ThreadPool.o Cdebug.h
	g++ testThreadPool.cpp -o $@ $(CXXFLAGS) $(LIBS)
testTimeStamp:TimeStamp.h  Cdebug.h
	g++ testTimeStamp.cpp -o $@ $(CXXFLAGS) $(LIBS)


$(OBJS):%.o:%.cpp 
	g++ $< -c -o$@ $(CXXFLAGS)


.PHONY:clean 
clean:
	rm $(OBJS) $(TARGETS)

