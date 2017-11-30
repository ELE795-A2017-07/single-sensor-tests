PRGM := lora_pingpong
CXX := g++
CXXFLAGS := -std=c++0x -iquote ../common #-Wall -Wextra
LDFLAGS := -lpthread -lwiringPi
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))
DEPS := $(patsubst %.cpp,%.d,$(SRC))
LIB_OBJ := $(patsubst %.cpp,%.o,$(wildcard ../common/*.cpp))

.PHONY: run
run: $(PRGM)
	sudo ./$(PRGM)

$(PRGM): $(OBJ) $(LIB_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(LIB_OBJ):
	$(MAKE) -f ../common/Makefile

-include $(DEPS)
$(DEPS): %.d: %.cpp
	$(CXX) $(CXXFLAGS) -MF"$@" -MG -MM -MP -MT"$@" -MT"$(subst $(SRC_DIR),$(OBJ_DIR),$(<:.cpp=.o))" "$<"
