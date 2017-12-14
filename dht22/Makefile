CXX := g++
PRGM := dht22
SRC := dht22.cpp utils.cpp
CXXFLAGS := -std=c++0x -I../temp/src/temp/
LDFLAGS := -lwiringPi -rdynamic
OBJ := $(patsubst %.cpp,%.o,$(foreach var,$(SRC),$(notdir $(var))))


$(PRGM): $(OBJ)
	$(CXX) -rdynamic $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: run
run: $(PRGM)
	sudo nice -n -20 ./$(PRGM)

$(OBJ): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

