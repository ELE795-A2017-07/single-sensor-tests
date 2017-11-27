CXX := g++
CXXFLAGS := -std=c++0x

PRGM := timing_test
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))


.PHONY: run
run: $(PRGM)
	sudo nice -n -20 ./$(PRGM)

$(PRGM): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

