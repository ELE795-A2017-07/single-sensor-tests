MAKEDIR := $(dir $(lastword $(MAKEFILE_LIST)))
CXX := g++
CXXFLAGS := -std=c++0x
SRC := $(wildcard $(MAKEDIR)/*.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))
DEPS := $(patsubst %.cpp,%.d,$(SRC))

.PHONY: all
all: $(OBJ)

$(OBJ): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

-include $(DEPS)
%.d: %.cpp
	$(CXX) $(CXXFLAGS) -MF"$@" -MG -MM -MP -MT"$@" -MT"$(<:.cpp=.o)" "$<"
