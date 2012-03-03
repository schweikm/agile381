include ../../infrastructure/standard_macro.mak

# define the objects to build
OBJS           = $(OBJ_DIR)/main.o
GTEST_ADD_OBJS = $(UT_OBJ_DIR)/Addition_unittest.o

# define the targets to build
EXE       = ../../bin/calculator.exe
GTEST_ADD = $(UT_DIR)/Addition_UT.exe

# module-specific options
GTEST_DIR  = ../../../gtest-1.6.0
INC_DIRS  += -I $(GTEST_DIR)/include
TEST_DIR   = ../../test_reports

# targets
all: $(EXE) $(GTEST_BASE) $(GTEST_ADD)

$(EXE): $(OBJS)
	@$(ECHO)
	@$(ECHO) "================================================================================"
	$(CXX) $(L++FLAGS) $(OBJS) -o $(EXE)
	@$(ECHO)
	@$(ECHO) "Will store \"$(abspath $(EXE))\""
	@$(ECHO) "================================================================================"
	@$(ECHO)

$(GTEST_ADD): $(GTEST_ADD_OBJS)
	@$(ECHO)
	@$(ECHO) "================================================================================"
	@$(MKDIR) $(UT_DIR)$
	$(CXX) $(GTEST_L_FLAGS) $(GTEST_DIR)/src/gtest-all.o $(GTEST_DIR)/src/gtest_main.o -pthread -o $@ $<
	@$(ECHO)
	@$(ECHO) "Will store \"$(abspath $@)\""
	@$(ECHO) "================================================================================"
	@$(ECHO)

include ../../infrastructure/standard_rules.mak
