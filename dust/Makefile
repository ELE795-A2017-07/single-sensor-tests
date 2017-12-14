PRGM := dust_test
CXX := g++
CXXFLAGS := -std=c++0x -iquote ../common/
LDFLAGS := -lwiringPi
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))
COMMON_OBJ := $(patsubst %.cpp,%.o,$(wildcard ../common/*.cpp))

.PHONY: run
run: $(PRGM)
	sudo ./$(PRGM)

$(PRGM): $(OBJ) $(COMMON_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(COMMON_OBJ):
	$(MAKE) -f ../common/Makefile
