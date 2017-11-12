PRGM := lora_pingpong
CXX := g++
#CXXFLAGS := -Wall -Wextra
LDFLAGS := -lpthread
SRC := pingpong.cpp SX1272.cpp arduPi.cpp
OBJ := $(patsubst %.cpp,%.o,$(SRC))

$(PRGM): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
