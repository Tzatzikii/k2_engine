TARGET = main

CC = g++
CFLAGS = -Werror
DEBUGFLAGS = -g

ROOT = .
DEP = $(ROOT)/dep
SRC = $(ROOT)/src
ENGINE = $(SRC)/k2_engine
MATH = $(SRC)/k2_math
TEST = ./test

OBJS = main.o \
	engine_main.o world_elements.o gamespace.o\
	lightsources.o renderer.o shapes.o \
	triangle.o vertex.o \
	output.o \
	logics_module_test.o

HDRS = $(ENGINE)/engine_main.hpp $(ENGINE)/world_elements.hpp $(ENGINE)/gamespace.hpp\
	$(ENGINE)/lightsources.hpp $(ENGINE)/renderer.hpp $(ENGINE)/shapes.hpp \
	$(ENGINE)/triangle.hpp $(ENGINE)/vertex.hpp \
	$(DEP)/output.hpp $(DEP)/utils.hpp 

$(TARGET): $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) 
		
	
main.o: $(SRC)/main.cpp
	$(CC) -g -c $(SRC)/main.cpp

engine_main.o: $(ENGINE)/engine_main.cpp $(ENGINE)/engine_main.hpp
	$(CC) -g -c $(ENGINE)/engine_main.cpp

world_elements.o: $(ENGINE)/world_elements.cpp $(ENGINE)/world_elements.hpp
	$(CC) -g -c $(ENGINE)/world_elements.cpp

gamespace.o: $(ENGINE)/gamespace.cpp $(ENGINE)/gamespace.hpp
	$(CC) -g -c $(ENGINE)/gamespace.cpp
	
lightsources.o: $(ENGINE)/lightsources.cpp $(ENGINE)/lightsources.hpp
	$(CC) -g -c $(ENGINE)/lightsources.cpp

renderer.o: $(ENGINE)/renderer.cpp $(ENGINE)/renderer.hpp
	$(CC) -g -c $(ENGINE)/renderer.cpp

shapes.o: $(ENGINE)/shapes.cpp $(ENGINE)/shapes.hpp
	$(CC) -g -c $(ENGINE)/shapes.cpp

triangle.o: $(ENGINE)/triangle.cpp $(ENGINE)/triangle.hpp
	$(CC) -g -c $(ENGINE)/triangle.cpp

vertex.o: $(ENGINE)/vertex.cpp $(ENGINE)/vertex.hpp
	$(CC) -g -c $(ENGINE)/vertex.cpp

output.o: $(DEP)/output.cpp $(DEP)/output.hpp
	$(CC) -g -c $(DEP)/output.cpp

logics_module_test.o: $(TEST)/logics_module_test.cpp
	$(CC) -g -c $(TEST)/logics_module_test.cpp	

clean: 
	-rm $(TARGET) $(OBJS)

run: main 
	./main