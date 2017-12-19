MAKEDIR := $(dir $(lastword $(MAKEFILE_LIST)))

all:

include $(MAKEDIR)/Makefile.include

CXX := g++
CXXFLAGS := -std=c++0x
SRC := $(COMMON_SRC)
OBJ := $(COMMON_OBJ)
DEPS := $(patsubst %.cpp,%.d,$(SRC))

.PHONY: all
all: $(OBJ)
