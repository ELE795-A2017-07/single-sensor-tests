PRGM := gas_test
CXX := g++
CXXFLAGS := -std=c++0x -iquote ../common
LDFLAGS := -lwiringPi
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))
DEPS := $(patsubst %.cpp,%.d,$(SRC))
COMMON_OBJ := $(patsubst %.cpp,%.o,$(wildcard ../common/*.cpp))


$(PRGM): $(OBJ) $(COMMON_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: run
run: $(PRGM)
	sudo ./$(PRGM)

-include $(DEPS)
%.d: %.cpp
	$(CXX) $(CXXFLAGS) -MF"$@" -MG -MM -MP -MT"$@" -MT"$(<:.cpp=.o)" "$<"

$(COMMON_OBJ):
	$(MAKE) -f ../common/Makefile
