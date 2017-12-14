CXX := g++
CXXFLAGS := -std=c++0x

PRGM := timing_test
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))


$(PRGM): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: run
run: $(PRGM)
	sudo nice -n -20 ./$(PRGM)
