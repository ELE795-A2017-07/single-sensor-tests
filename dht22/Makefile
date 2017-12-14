PRGM := dht22
CXX := g++
CXXFLAGS := -std=c++0x -iquote ../common/
LDFLAGS := -lwiringPi -rdynamic
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,%.o,$(foreach var,$(SRC),$(notdir $(var))))


$(PRGM): $(OBJ)
	$(CXX) -rdynamic $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: run
run: $(PRGM)
	sudo nice -n -20 ./$(PRGM)

$(OBJ): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

