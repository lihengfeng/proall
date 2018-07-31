
CXXFLAGS=-std=c++11
LIBS= -pthread -lnetxy

.PHONY:all
all: DiscardClient DiscardServer TuntuClient TuntuServer

DiscardClient:
	g++ DiscardClient.cpp -o  $@ $(CXXFLAGS) $(LIBS) 
DiscardServer:
	g++ DiscardServer.cpp -o $@ $(CXXFLAGS) $(LIBS) 

TuntuClient:
	g++ TuntuClient.cpp -o  $@ $(CXXFLAGS) $(LIBS) 
TuntuServer:
	g++ TuntuServer.cpp -o $@ $(CXXFLAGS) $(LIBS) 

