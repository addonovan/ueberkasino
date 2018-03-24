PRODUCT := uk
BIN  	:= bin
INC 	:= include
IDL 	:= idl
SRC	:= src
GEN	:= gen
GEN_SRC := $(GEN)/src
GEN_INC := $(GEN)/include
TEST 	:= test
OBJ 	:= obj

CXX	 := g++
LINKER	 := g++
CXXFLAGS := -Wall -Wextra -pedantic -Werror -g3
INCLUDE  := -I$(INC) -I$(GEN_INC)

IDLS	  := $(wildcard $(IDL)/*.idl)

GEN_SRCS  := $(wildcard $(GEN_SRC)/*.cpp)
TEST_SRCS := $(wildcard $(TEST)/*.cpp)
SRCS      := $(wildcard $(SRC)/*.cpp)
SRCS      := $(filter-out src/main.cpp, $(SRCS))

GEN_OBJS  := $(patsubst $(GEN_SRC)/%.cpp, $(OBJ)/%.o, $(GEN_SRCS))
TEST_OBJS := $(patsubst $(TEST)/%.cpp, $(OBJ)/test_%.o, $(TEST_SRCS))
OBJS      := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

TEST_OUTS := $(patsubst $(TEST)/%.cpp, $(BIN)/test_%.out, $(TEST_SRCS))

#
# Test Builds
#

run_tests: $(TEST_OUTS)
	./$<
.PHONY: run_tests

build_tests: makedirs $(TEST_OUTS) idl
.PHONY: build_tests

$(BIN)/%.out: $(TEST_OBJS) $(OBJS) $(GEN_OBJS)
	$(LINKER) $(CXXFLAGS) $(TEST_OBJS) $(OBJS) -o $@

$(OBJ)/%.o: $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

#
# Full builds
#

run: build
	./$(BIN)/$(PRODUCT)
.PHONY: run

build: makedirs $(BIN)/$(PRODUCT) idl
.PHONY: build 

$(BIN)/$(PRODUCT): $(OBJS) $(GEN_OBJS)
	$(LINKER) $(CXXFLAGS) $(INCLUDE) $^ src/main.cpp -o $@

$(OBJ)/%.o: $(SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

#
# IDL Generation & Compilation
#

idl: $(IDLS)
	${OSPL_HOME}/bin/idlpp -d $(GEN) -l cpp $(IDLS)
	mv $(GEN)/*.cpp $(GEN_SRC)
	mv $(GEN)/*.h $(GEN_INC)

$(OBJ)/%.o: $(GEN_SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

#
# Miscellaneous
#

makedirs:
	@mkdir -p $(BIN)
	@mkdir -p $(OBJ)
	@mkdir -p $(GEN)
	@mkdir -p $(GEN_INC)
	@mkdir -p $(GEN_SRC)
.PHONY: makedirs

clean:
	@rm -rf $(BIN)
	@rm -rf $(OBJ)
	@rm -rf $(GEN)
	@rm -rf $(GEN_INC)
	@rm -rf $(GEN_SRC)
	@mkdir -p $(BIN)
	@mkdir -p $(OBJ)
	@mkdir -p $(GEN)
	@mkdir -p $(GEN_INC)
	@mkdir -p $(GEN_SRC)
.PHONY: clean

