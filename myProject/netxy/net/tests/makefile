VPATH=../ 
DIRS= .. 
HS= $(foreach dir, $(DIRS), $(wildcard $(dir)/*.h))
CS= $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))
OBJS= $(patsubst  %.cpp, %.o, $(CS))
CXXFLAGS=-std=c++11 -pthread 
LIBS=-L ~/netxy/ -lnetxy 
TARGETS=TcpServerTest TcpClientTest

.PHONY:all
all:$(OBJS) $(TARGETS)
	@echo $(HS) 
	@echo $(CS) 
	@echo $(OBJS)

TcpClientTest:TcpClient.h 
	g++ TcpClientTest.cpp -o TcpClientTest $(CXXFLAGS) $(LIBS)

TcpServerTest:TcpServer.h 
	g++ TcpServerTest.cpp -o TcpServerTest $(CXXFLAGS) $(LIBS)

$(OBJS):%.o:%.cpp 
	g++ $< -c -o$@ $(CXXFLAGS)

.PHONY:clean 
clean:
	rm $(OBJS) $(TARGETS)

