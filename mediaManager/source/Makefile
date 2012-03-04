include ../infrastructure/standard_macro.mak

# define the objects to build
OBJS              = $(OBJ_DIR)/String.o
GTEST_STRING_OBJS = $(UT_OBJ_DIR)/String_unittest.o

# define the targets to build
GTEST_STRING = $(UT_DIR)/String_UT.exe

# module-specific options
GTEST_DIR        = ../../gtest-1.6.0
GTEST_INC_DIRS  += -I $(GTEST_DIR)/include
TEST_DIR         = ../test_reports

# targets
all: $(OBJS) $(GTEST_STRING)

$(GTEST_STRING): $(GTEST_STRING_OBJS)
	@$(ECHO)
	@$(ECHO) "================================================================================"
	@$(MKDIR) $(UT_DIR)$
	$(CXX) $(GTEST_L_FLAGS) $(GTEST_DIR)/src/gtest-all.o $(GTEST_DIR)/src/gtest_main.o -pthread -o $@ $<
	@$(ECHO)
	@$(ECHO) "Will store \"$(abspath $@)\""
	@$(ECHO) "================================================================================"
	@$(ECHO)

include ../infrastructure/standard_rules.mak
