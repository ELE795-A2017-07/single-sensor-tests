PRGM := lora_pingpong
CXX := g++
CXXFLAGS := #-std=c++0x #-Wall -Wextra
LDFLAGS := -lpthread -lwiringPi
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))
DEPS := $(patsubst %.cpp,%.d,$(SRC))

.PHONY: run
run: $(PRGM)
	sudo ./$(PRGM)

$(PRGM): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

-include $(DEPS)
$(DEPS): %.d: %.cpp
	$(CXX) $(CXXFLAGS) -MF"$@" -MG -MM -MP -MT"$@" -MT"$(subst $(SRC_DIR),$(OBJ_DIR),$(<:.cpp=.o))" "$<"
