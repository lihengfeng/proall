VPATH= ../
DIRS= ..
CS= $(foreach dir,$(DIRS),$(wildcard $(dir)/*.cpp))
OBJS=  $(patsubst  %.cpp, %.o, $(CS))
TARGETS=messageCodecServer messageCodecClient protobufClient protobufServer

CXXFLAGS= -std=c++11 
LIBS= -L ~/netxy/ -lnetxy  -pthread  -lprotobuf

.PHONY:all
all: $(TARGETS)
	echo "succeed"

.PHONY:install
install:$(OBJS) 
	ar -rsv libcodec $(OBJS)

messageCodecClient:
	g++ messageCodecClient.cpp -o $@ $(CXXFLAGS) $(LIBS)
messageCodecServer:
	g++ messageCodecServer.cpp -o $@ $(CXXFLAGS) $(LIBS)

protobufClient:
	g++ protobufClient.cpp Person.pb.cc  -o $@ $(CXXFLAGS) $(LIBS)
protobufServer:
	g++ protobufServer.cpp Person.pb.cc  -o $@ $(CXXFLAGS) $(LIBS)

$(OBJS):%.o:%.cpp 
	g++ $< -c -o $@ $(CXXFLAGS)

.PHONY:clean
clean:
	rm $(OBJS) $(TARGETS) libcodec
