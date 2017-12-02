MAKEDIR := $(dir $(lastword $(MAKEFILE_LIST)))
CXX := g++
CXXFLAGS := -std=c++0x
SRC := $(wildcard $(MAKEDIR)/*.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))

$(OBJ): %.o: %.cpp
