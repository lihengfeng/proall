CC = gcc
DIRS=../code 

CS=$(foreach dir,$(DIRS),$(wildcard $(dir)/*.cpp))
OBJS=$(patsubst %.cpp,%.o,$(CS))

LIBS= -pthread
CXXFLAGS= -std=c++11

TARGETS=http tcpClient

.PTHONY: all
all:$(OBJS) $(TARGETS)
	@echo $(OBJS)

http:http.o $(OBJS) 
	g++ $^ -o $@ $(CXXFLAGS) $(LIBS)

tcpClient:tcpClient.o
	g++ $^ -o $@ $(CXXFLAGS)

%.o:%.cpp
	g++ $< -c -o $@ $(CXXFLAGS) $(LIBS) 

%.d:%.cpp
	@set -e; \
	g++ -MM $^ -std=c++11 > $@.$$$$; \
	sed 's#\($*.o\)#\1 $@#g' <$@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(OBJS:.o=.d)
-include http.d 

.PHONY: clean 
clean:
	rm $(OBJS) $(TARGETS) $(OBJS:.o=.d) *.o *.d *.d.*   ../code/*.d.*
	echo "rm objs完毕"
