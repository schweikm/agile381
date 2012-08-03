include ../support/standard_macro.mak


############################################################
#### THESE MACROS MUST BE SPECIFIED IN EVERY MAKEFILE!! ####
############################################################

BIN_DIR      = ../bin
GTEST_DIR    = ../../gtest-1.6.0

############################################################
############################################################
############################################################


#### Module-specific Options ####
SRC_DIR   = ../manager
INC_DIRS += -I $(GTEST_DIR)/include

#### Objects to Build ####
GTEST_OBJS = StringMemberTest_unittest.o \
             StringNonMemberTest_unittest.o

# Google Test targets
GTEST_STRING_MEMBER      = $(BIN_DIR)/$(UT_DIR)/StringMemberTest_UT.exe
GTEST_STRING_MEMBER_OBJS = $(SRC_DIR)/String.o StringMemberTest_unittest.o

GTEST_STRING_NONMEMBER      = $(BIN_DIR)/$(UT_DIR)/StringNonMemberTest_UT.exe
GTEST_STRING_NONMEMBER_OBJS = $(SRC_DIR)/String.o StringNonMemberTest_unittest.o

#### Targets ####
all: $(GTEST_STRING_MEMBER) $(GTEST_STRING_NONMEMBER)
    # handled by standard_rules.mak


$(GTEST_STRING_MEMBER): StringMemberTest_unittest.o
	@$(ECHO)
	@$(ECHO) "================================================================================"
	@$(MKDIR) $(BIN_DIR)/$(UT_DIR)
	$(CXX) $(LXXFLAGS) $(GTEST_STRING_MEMBER_OBJS) \
$(GTEST_DIR)/src/gtest-all.o $(GTEST_DIR)/src/gtest_main.o -pthread -o $@
	@$(ECHO)
	@$(ECHO) "Will store \"$(abspath $@)\""
	@$(ECHO) "================================================================================"
	@$(ECHO)


$(GTEST_STRING_NONMEMBER): StringNonMemberTest_unittest.o
	@$(ECHO)
	@$(ECHO) "================================================================================"
	@$(MKDIR) $(BIN_DIR)/$(UT_DIR)
	$(CXX) $(LXXFLAGS) $(GTEST_STRING_NONMEMBER_OBJS) \
$(GTEST_DIR)/src/gtest-all.o $(GTEST_DIR)/src/gtest_main.o -pthread -o $@
	@$(ECHO)
	@$(ECHO) "Will store \"$(abspath $@)\""
	@$(ECHO) "================================================================================"
	@$(ECHO)


clean:
	@$(RM) *.o
	@$(RM) $(GTEST_STRING_MEMBER)
	@$(RM) $(GTEST_STRING_NONMEMBER)
	@$(RM) gmon.out
	@$(RM) *.gcov
	@$(RM) *.gcno
	@$(RM) *.gcda


include ../support/standard_rules.mak
