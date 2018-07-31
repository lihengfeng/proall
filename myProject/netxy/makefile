CC = gcc
DIRS=base net codec
OBJDIR= objs

#hs保存所有的.h文件
HS= $(foreach dir, $(DIRS), $(wildcard $(dir)/*.h))

#下面两行，生成所有的.cpp对应的.o
FILES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))
OBJS = $(patsubst %.cpp, %.o, $(FILES))

CXXFLAGS= -std=c++11 

VPATH=base:net:codec


.PHONY:all
all: $(OBJDIR) $(OBJS)
	cp $(OBJS) ~/netxy/objs
	ar -rsv libnetxy.a $(OBJS)
	ctags -R

.PHONY:install
install:
	$(foreach dir, $(DIRS), $(shell mkdir -p  /usr/include/netxy/$(dir)))
	$(foreach file, $(HS), $(shell cp $(file) /usr/include/netxy/$(dir $(file)) ) )
	cp libnetxy.a /usr/lib
	@echo $(HS)

$(OBJDIR):
	mkdir -p $@
$(OBJS):%.o:%.cpp
	g++ $< -c -o $@  $(CXXFLAGS) 
	
.PHONY:clean
clean: 
	rm -rf $(OBJDIR)
	rm $(OBJS)  libnetxy.a tags 
