CXX := g++
CXXFLAGS := -std=c++0x -iquote ../common
LDFLAGS := -lwiringPi
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))
COMMON_OBJ := $(patsubst %.cpp,%.o,$(wildcard ../common/*.cpp))

PRGM := adc_test

$(PRGM): $(OBJ) $(COMMON_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: run
run: $(PRGM)
	sudo ./$(PRGM)

$(COMMON_OBJ):
	$(MAKE) -f ../common/Makefile
