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
SRC_DIR        =  ../manager
GTEST_INC_DIRS += -I $(SRC_DIR)

#### Objects to Build ####
GTEST_OBJS = $(GTEST_OBJ_DIR)/StringMemberTest_unittest.o \
             $(GTEST_OBJ_DIR)/StringNonMemberTest_unittest.o

# Google Test targets
GTEST_STRING_MEMBER      = $(BIN_DIR)/$(UT_DIR)/StringMemberTest_UT.exe
GTEST_STRING_MEMBER_OBJS = $(SRC_DIR)/$(OBJ_DIR)/String.o $(GTEST_OBJ_DIR)/StringMemberTest_unittest.o

GTEST_STRING_NONMEMBER      = $(BIN_DIR)/$(UT_DIR)/StringNonMemberTest_UT.exe
GTEST_STRING_NONMEMBER_OBJS = $(SRC_DIR)/$(OBJ_DIR)/String.o $(GTEST_OBJ_DIR)/StringNonMemberTest_unittest.o

#### Targets ####
all: $(GTEST_OBJS) $(GTEST_STRING_MEMBER) $(GTEST_STRING_NONMEMBER)
    # handled by standard_rules.mak


$(GTEST_STRING_MEMBER): $(GTEST_STRING_MEMBER_OBJS)
	@$(ECHO)
	@$(ECHO) "================================================================================"
	@$(MKDIR) $(BIN_DIR)/$(UT_DIR)
	$(CXX) $(GTEST_L_FLAGS) $(GTEST_STRING_MEMBER_OBJS) \
$(GTEST_DIR)/src/gtest-all.o $(GTEST_DIR)/src/gtest_main.o -pthread -o $@
	@$(ECHO)
	@$(ECHO) "Will store \"$(abspath $@)\""
	@$(ECHO) "================================================================================"
	@$(ECHO)


$(GTEST_STRING_NONMEMBER): $(GTEST_STRING_NONMEMBER_OBJS)
	@$(ECHO)
	@$(ECHO) "================================================================================"
	@$(MKDIR) $(BIN_DIR)/$(UT_DIR)
	$(CXX) $(GTEST_L_FLAGS) $(GTEST_STRING_NONMEMBER_OBJS) \
$(GTEST_DIR)/src/gtest-all.o $(GTEST_DIR)/src/gtest_main.o -pthread -o $@
	@$(ECHO)
	@$(ECHO) "Will store \"$(abspath $@)\""
	@$(ECHO) "================================================================================"
	@$(ECHO)


clean:
	@$(RMDIR) $(GTEST_OBJ_DIR)
	@$(RM) $(GTEST_STRING_MEMBER)
	@$(RM) $(GTEST_STRING_NONMEMBER)
	@$(RM) gmon.out
	@$(RM) *.gcov


include ../support/standard_rules.mak