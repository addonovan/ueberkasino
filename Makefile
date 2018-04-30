PRODUCT     := uk
TEST_PROD   := test_uk
BIN         := bin
INC         := include
GEN         := gen
GEN_SRC     := $(GEN)/src
GEN_INC     := $(GEN)/include
RES         := res
SRC         := src
TEST        := test
OBJ         := obj
IDL         := idl

CXX         := g++
CXXFLAGS    := -Wall -Wextra -Werror -g -std=c++14 \
               `fltk-config --cxxflags` \
			   -DDEBUG -O0

LINKER      := g++
LFLAGS      := -L${OSPL_HOME}/lib \
			   -lpthread -lddskernel -ldcpssacpp \
			   -lboost_system -lboost_thread \
			   `fltk-config --ldflags`

INCLUDE		:= -I$(INC) -I$(GEN_INC) -I. \
			   -I${OSPL_HOME}/include/dcps/C++/SACPP/ \
			   -I${OSPL_HOME}/include/sys \

EXT         := cpp
MAIN        := $(SRC)/main.$(EXT)
TEST_FMT    := test_%
TEST_MAIN   := $(TEST)/main.$(EXT)

IDLS		:= $(wildcard $(IDL)/*.idl)

SRCS        := $(wildcard $(SRC)/*.$(EXT))
SRCS        := $(filter-out $(MAIN), $(SRCS))
GEN_SRCS    := $(GEN_SRC)/UberCasino.cpp \
               $(GEN_SRC)/UberCasinoDcps.cpp \
               $(GEN_SRC)/UberCasinoDcps_impl.cpp \
               $(GEN_SRC)/UberCasinoSplDcps.cpp

TEST_SRCS   := $(wildcard $(TEST)/*.$(EXT))
TEST_SRCS   := $(filter-out $(TEST_MAIN), $(TEST_SRCS))

OBJS        := $(patsubst $(SRC)/%.$(EXT), $(OBJ)/%.o, $(SRCS))
GEN_OBJS    := $(patsubst $(GEN_SRC)/%.$(EXT), $(OBJ)/%.o, $(GEN_SRCS))
OBJS        := $(GEN_OBJS) $(OBJS)
TEST_OBJS   := $(patsubst $(TEST)/%.$(EXT), $(OBJ)/$(TEST_FMT), $(TEST_SRCS))

MAIN_OBJ    := $(patsubst $(SRC)/%.$(EXT), $(OBJ)/%.o, $(MAIN))
TEST_OBJ    := $(patsubst $(TEST)/%.$(EXT), $(OBJ)/$(TEST_FMT).o, $(TEST_MAIN))


################################################################################
# EXECUTABLES																   #
################################################################################

test: test_build 
	./$(BIN)/$(TEST_PROD)
.PHONY: test

run: build
	./$(BIN)/$(PRODUCT)
.PHONY: run

debug: build
	gdb $(BIN)/$(PRODUCT)
.PHONY: run


################################################################################
# BUILDING																	   #
################################################################################

test_build: prebuild $(BIN)/$(TEST_PROD)
.PHONY: test_build

build: prebuild $(BIN)/$(PRODUCT)
.PHONY: build 

$(BIN)/$(PRODUCT): $(OBJS) $(MAIN_OBJ)
	$(LINKER) $(OBJS) $(MAIN_OBJ) -o $@ $(LFLAGS)

$(MAIN_OBJ): $(MAIN)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.$(EXT)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# Test Objects

$(BIN)/$(TEST_PROD): $(OBJS) $(TEST_OBJS) $(TEST_OBJ)
	$(LINKER) $(OBJS) $(TEST_OBJS) $(TEST_OBJ) -o $@ $(LFLAGS)

$(TEST_OBJ): $(TEST_MAIN)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ)/$(TEST_FMT): $(TEST)/%.$(EXT)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# IDL shit

$(GEN_SRCS): $(IDLS)
	${OSPL_HOME}/bin/idlpp -d $(GEN) -l cpp $(IDLS)
	mv $(GEN)/*.cpp $(GEN_SRC)
	mv $(GEN)/*.h $(GEN_INC)

$(OBJ)/%.o: $(GEN_SRC)/%.$(EXT)
	sed -i 's/#include "\(.*\)"/#include <\1>/' $<
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

################################################################################
# Miscellaneous																   #
################################################################################

DIRS := $(BIN) $(OBJ) $(GEN_INC) $(GEN_SRC) $(GEN)
CATCH := "https://github.com/catchorg/Catch2/releases/download/v2.2.2/catch.hpp"
CATCH_FILE := $(TEST)/catch.hpp

prebuild: makedirs $(CATCH_FILE) 
.PHONY: prebuild

$(CATCH_FILE):
	wget $(CATCH) -O $(CATCH_FILE)

makedirs:
	@mkdir -p $(DIRS)
.PHONY: makedirs

clean:
	rm -rf $(DIRS)
	mkdir -p $(DIRS)
	rm -f $(CATCH_FILE)
.PHONY: clean

echo:
	@echo "SRCS		 = $(SRCS)"
	@echo "GEN_SRCS  = $(GEN_SRCS)"
	@echo "TEST_SRCS = $(TEST_SRCS)"
	@echo "FLTK_SRCS = $(FLTK_SRCS)"
	@echo "OBJS      = $(OBJS)"
	@echo "TEST_OBJS = $(TEST_OBJS)"
.PHONY: echo
	@mkdir -p $(BIN) $(OBJ)
.PHONY: makedirs

