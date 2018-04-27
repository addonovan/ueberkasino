PRODUCT     := uk
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
               `fltk-config --cxxflags`

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

IDLS		:= $(wildcard $(IDL)/*.idl)

SRCS        := $(wildcard $(SRC)/*.$(EXT))
SRCS        := $(filter-out $(MAIN), $(SRCS))
SRCS        := $(filter-out $(FLTK_SRCS), $(SRCS))
GEN_SRCS    := $(GEN_SRC)/UberCasino.cpp \
               $(GEN_SRC)/UberCasinoDcps.cpp \
               $(GEN_SRC)/UberCasinoDcps_impl.cpp \
               $(GEN_SRC)/UberCasinoSplDcps.cpp
TEST_SRCS   := $(wildcard $(TEST)/*.$(EXT))

OBJS        := $(patsubst $(SRC)/%.$(EXT), $(OBJ)/%.o, $(SRCS))
GEN_OBJS    := $(patsubst $(GEN_SRC)/%.$(EXT), $(OBJ)/%.o, $(GEN_SRCS))
OBJS        := $(GEN_OBJS) $(FLTK_SRCS) $(OBJS)
MAIN_OBJ    := $(patsubst $(SRC)/%.$(EXT), $(OBJ)/%.o, $(MAIN))
FLTK_OBJ    := $(OBJ)/fltk.o

TEST_BINS	:= $(patsubst $(TEST)/%.$(EXT), $(BIN)/$(TEST_FMT), $(TEST_SRCS))


################################################################################
# EXECUTABLES																   #
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

debug: build
	gdb $(BIN)/$(PRODUCT)
.PHONY: run


################################################################################
# BUILDING																	   #
################################################################################

test_build: prebuild $(OBJS) $(TEST_BINS)
.PHONY: test_build

build: prebuild $(BIN)/$(PRODUCT)
.PHONY: build 

$(BIN)/$(PRODUCT): $(OBJS) $(MAIN_OBJ)
	$(LINKER) $(OBJS) $(MAIN_OBJ) -o $@ $(LFLAGS)

$(MAIN_OBJ): $(MAIN)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.$(EXT)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# Tests

$(BIN)/$(TEST_FMT): $(TEST)/%.$(EXT)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(OBJS) $< -o $@ $(LFLAGS)

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

prebuild: makedirs
.PHONY: prebuild

makedirs:
	@mkdir -p $(DIRS)
.PHONY: makedirs

clean:
	@rm -rf $(DIRS)
	@mkdir -p $(DIRS)
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
