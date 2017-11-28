CXX := g++
CXXFLAGS := -std=c++0x
LDFLAGS := -lwiringPi
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))

PRGM := adc_test

.PHONY: run
run: $(PRGM)
	sudo ./$(PRGM)

$(PRGM): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
