CC = gcc
DIRS=code 

CS=$(foreach dir,$(DIRS),$(wildcard $(dir)/*.cpp))
OBJS=$(patsubst %.cpp,%.o,$(CS))

CXXFLAGS= -std=c++11
LIBS= -pthread
VPATH= code

.PHONY: all
all:$(OBJS)
	@echo $(OBJS)
	@echo "code下objs生成完毕"
	

$(OBJS): %.o:%.cpp
	g++ -c $< -o $@ $(CXXFLAGS)


.PHONY: clean 
clean:
	rm $(OBJS)
	echo "rm objs完毕"
