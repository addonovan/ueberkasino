PRODUCT     := uk
BIN         := bin
INC         := include
GEN         := gen
GEN_SRC     := $(GEN)/src
GEN_INC     := $(GEN)/include
SRC         := src
TEST        := test
OBJ         := obj

CXX         := g++
CXXFLAGS    := -Wall -Wextra -pedantic -Werror -g -std=c++11

LINKER      := g++
LFLAGS      := -lpthread

INCLUDE     := -I$(INC) -I$(GEN_INC)

EXT         := cpp
MAIN        := $(SRC)/main.$(EXT)
TEST_FMT    := test_%

IDLS        := $(wildcard $(IDL)/*.idl)

SRCS        := $(wildcard $(SRC)/*.$(EXT))
SRCS        := $(filter-out $(MAIN), $(SRCS))
TEST_SRCS   := $(wildcard $(TEST)/*.$(EXT))

OBJS        := $(patsubst $(SRC)/%.$(EXT), $(OBJ)/%.o, $(SRCS))
MAIN_OBJ    := $(patsubst $(SRC)/%.$(EXT), $(OBJ)/%.o, $(MAIN))

TEST_BINS   := $(patsubst $(TEST)/%.$(EXT), $(BIN)/$(TEST_FMT), $(TEST_SRCS))


################################################################################
# EXECUTABLES                                                                  #
################################################################################

test: build $(TEST_BINS)
	@for file in $(TEST_BINS); do\
		echo "$$file...";\
		./$$file 2> /dev/null;\
		if [ "$$?" != "0" ]; then\
			echo "";\
		fi;\
	done
.PHONY: test

run: build
	./$(BIN)/$(PRODUCT)
.PHONY: run


################################################################################
# BUILDING                                                                     #
################################################################################

test_build: prebuild $(OBJS) $(TEST_BINS)
.PHONY: test_build

build: prebuild $(BIN)/$(PRODUCT)
.PHONY: build 

$(BIN)/$(PRODUCT): $(OBJS) $(MAIN_OBJ)
	$(LINKER) $(LFLAGS) $(OBJS) $(MAIN_OBJ) -o $@

$(MAIN_OBJ): $(MAIN)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.$(EXT)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# Tests

$(BIN)/$(TEST_FMT): $(TEST)/%.$(EXT)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(OBJS) $< -o $@ $(LFLAGS)

# IDL shit

idl: $(IDLS)
	${OSPL_HOME}/bin/idlpp -d $(GEN) -l cpp $(IDLS)
	mv $(GEN)/*.cpp $(GEN_SRC)
	mv $(GEN)/*.h $(GEN_INC)

$(OBJ)/%.o: $(GEN_SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

################################################################################
# Miscellaneous                                                                #
################################################################################

prebuild: makedirs idl
.PHONY: prebuild

makedirs:
	@mkdir -p $(BIN) $(OBJ)
.PHONY: makedirs

clean:
	@rm -rf $(BIN) $(OBJ)
	@mkdir -p $(BIN) $(OBJ)
.PHONY: clean