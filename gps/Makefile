PRGM := gps_test
OTHER_PRGMS := record_data read_examples
CXX := g++
CXXFLAGS := -std=c++0x -iquote TinyGPS-RPi -iquote ../common #-Wall -Wextra
LDFLAGS := -lpthread -lwiringPi
SRC := $(filter-out $(patsubst %,%.cpp,$(OTHER_PRGMS) $(PRGM)),$(wildcard *.cpp))
OBJ := $(patsubst %.cpp,%.o,$(SRC))
DEPS := $(patsubst %.cpp,%.d,$(SRC))
LIB_SRC := $(wildcard TinyGPS-RPi/*.cpp)
LIB_OBJ := $(patsubst %.cpp,%.o,$(LIB_SRC))
COMMON_OBJ := $(patsubst %.cpp,%.o,$(wildcard ../common/*.cpp))

.PHONY: all
all: $(PRGM) record_data read_examples

$(PRGM): gps_test.o $(OBJ) $(LIB_OBJ) $(COMMON_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

record_data: record_data.o $(OBJ) $(LIB_OBJ) $(COMMON_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

read_examples: read_examples.o $(OBJ) $(LIB_OBJ) $(COMMON_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(LIB_OBJ): %.o: %.cpp $(COMMON_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

-include $(DEPS)
%.d: %.cpp
	$(CXX) $(CXXFLAGS) -MF"$@" -MG -MM -MP -MT"$@" -MT"$(<:.cpp=.o)" "$<"

$(COMMON_OBJ):
	$(MAKE) -f ../common/Makefile


.PHONY: run
run: $(PRGM)
	sudo ./$(PRGM)
