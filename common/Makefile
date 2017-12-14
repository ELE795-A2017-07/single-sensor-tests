MAKEDIR := $(dir $(lastword $(MAKEFILE_LIST)))
CXX := g++
CXXFLAGS := -std=c++0x
SRC := $(wildcard $(MAKEDIR)/*.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))

.PHONY: all
all: $(OBJ)

$(OBJ): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@
