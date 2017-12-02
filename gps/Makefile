PRGM := gps_test
CXX := g++
CXXFLAGS := -std=c++0x -iquote TinyGPS-RPi -iquote ../common #-Wall -Wextra
LDFLAGS := -lpthread -lwiringPi
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))
LIB_SRC := $(wildcard TinyGPS-RPi/*.cpp)
LIB_OBJ := $(patsubst %.cpp,%.o,$(LIB_SRC))
COMMON_OBJ := $(patsubst %.cpp,%.o,$(wildcard ../common/*.cpp))

$(PRGM): $(OBJ) $(LIB_OBJ) $(COMMON_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(LIB_OBJ): %.o: %.cpp $(COMMON_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(COMMON_OBJ):
	$(MAKE) -f ../common/Makefile


.PHONY: run
run: $(PRGM)
	sudo ./$(PRGM)
