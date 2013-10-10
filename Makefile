# Makefile for ConfigFileExtractor 
# by Wenhai Pan in CRSC
# 2013-06-24

CC = g++
TARGET = config_file_extractor  
LIB_ARGS = 

OBJS = main.o \
	   ConfigFileExtractor.o \
	   ConfigFileExtractorTest.o \

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


