PRGM := temp_test
CXX := g++

ifndef DEBUG
	DEBUG := 0
endif

override CXXFLAGS += -std=c++0x -DDEBUG=$(DEBUG) -iquote ../common
override LDFLAGS += -lwiringPi -lpthread

SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))
DEPS := $(patsubst %.cpp,%.d,$(SRC))


$(PRGM):

include ../common/Makefile.include

$(PRGM): $(OBJ) $(COMMON_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: run
run: $(PRGM)
	sudo ./$(PRGM)

$(OBJ): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

-include $(DEPS)
%.d: %.cpp
	$(CXX) $(CXXFLAGS) -MF"$@" -MG -MM -MP -MT"$@" -MT"$(<:.cpp=.o)" "$<"
