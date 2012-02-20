CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix bin/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS := -lGL -lglut -lGLU -lboost_thread
CC_FLAGS := -Wall

bin/main: $(OBJ_FILES)
	g++ -o $@ $^ ${LD_FLAGS}

bin/%.o: src/%.cpp
	g++ -c -o $@ $< ${CC_FLAGS}

clean: 
	rm bin/*.o
	rm bin/main
