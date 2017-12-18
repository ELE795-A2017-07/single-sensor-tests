CXX := g++
CXXFLAGS := -std=c++0x

PRGM := timing_test
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))
DEPS := $(patsubst %.cpp,%.d,$(SRC))


$(PRGM): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: run
run: $(PRGM)
	sudo nice -n -20 ./$(PRGM)

-include $(DEPS)
%.d: %.cpp
	$(CXX) $(CXXFLAGS) -MF"$@" -MG -MM -MP -MT"$@" -MT"$(<:.cpp=.o)" "$<"
