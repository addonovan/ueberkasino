PRODUCT := uk
BIN  	:= bin
INC 	:= include
SRC	:= src
TEST 	:= test
OBJ 	:= obj

CXX	 := g++
LINKER	 := g++
CXXFLAGS := -Wall -Wextra -pedantic -Werror -g3

TEST_SRCS := $(wildcard $(TEST)/*.cpp)
SRCS      := $(wildcard $(SRC)/*.cpp)
SRCS      := $(filter-out src/main.cpp, $(SRCS))

TEST_OBJS := $(patsubst $(TEST)/%.cpp, $(OBJ)/test_%.o, $(TEST_SRCS))
OBJS      := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

TEST_OUTS := $(patsubst $(TEST)/%.cpp, $(BIN)/test_%.out, $(TEST_SRCS))

#
# Test Builds
#

run_tests: $(TEST_OUTS)
	./$<
.PHONY: run_tests

build_tests: makedirs $(TEST_OUTS)
.PHONY: build_tests

$(BIN)/%.out: $(TEST_OBJS) $(OBJS)
	$(LINKER) $(CXXFLAGS) $(TEST_OBJS) $(OBJS) -o $@

$(OBJ)/%.o: $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) -I$(INC) -c $< -o $@

#
# Full builds
#

run: build
	./$(BIN)/$(PRODUCT)
.PHONY: run

build: makedirs $(BIN)/$(PRODUCT)
.PHONY: build 

$(BIN)/$(PRODUCT): $(OBJS)
	$(LINKER) $(CXXFLAGS) -I$(INC) $^ src/main.cpp -o $@

$(OBJ)/%.o: $(SRCS)
	$(CXX) $(CXXFLAGS) -I$(INC) -c $< -o $@


#
# Miscellaneous
#

makedirs:
	@mkdir -p $(BIN)
	@mkdir -p $(OBJ)
.PHONY: makedirs

clean:
	@rm -rf $(BIN)
	@rm -rf $(OBJ)
.PHONY: clean

