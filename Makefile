# Makefile for ConfigFileExtractor 
# by Wenhai Pan in CRSC
# 2013-06-24

CC = g++
TARGET = test
LIB_ARGS = 

OBJS = test.o \
	   ConfigFileExtractor.o \

OBJS_C = 

all: $(TARGET)


$(TARGET): $(OBJS) $(OBJS_C)
	$(CC) -o $@ $(OBJS) $(OBJS_C) $(LIB_ARGS)


$(OBJS):%.o:%.cpp *.h
	$(CC) -c $< -o $@

$(OBJS_C):%.o:%.c *.h
	gcc -c $< -o $@

.PHONY: clean

clean:
	-rm -f $(TARGET) *.o


