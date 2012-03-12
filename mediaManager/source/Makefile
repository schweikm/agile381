include ../infrastructure/standard_macro.mak


############################################################
#### THESE MACROS MUST BE SPECIFIED IN EVERY MAKEFILE!! ####
############################################################

BIN_DIR      = ../bin
GTEST_DIR    = ../../gtest-1.6.0

############################################################
############################################################
############################################################


#### Module-specific Options ####

#### Objects to Build ####
OBJS       = $(OBJ_DIR)/String.o
GTEST_OBJS = $(GTEST_OBJ_DIR)/String_member_unittest.o \
             $(GTEST_OBJ_DIR)/String_nonmember_unittest.o

# Google Test targets
GTEST_STRING_MEMBER      = $(BIN_DIR)/$(UT_DIR)/String_member_UT.exe
GTEST_STRING_MEMBER_OBJS = $(OBJ_DIR)/String.o $(GTEST_OBJ_DIR)/String_member_unittest.o

GTEST_STRING_NONMEMBER      = $(BIN_DIR)/$(UT_DIR)/String_nonmember_UT.exe
GTEST_STRING_NONMEMBER_OBJS = $(OBJ_DIR)/String.o $(GTEST_OBJ_DIR)/String_nonmember_unittest.o

#### Targets ####
all: $(OBJS) $(GTEST_OBJS) $(GTEST_STRING_MEMBER) $(GTEST_STRING_NONMEMBER)
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
	@$(RMDIR) $(OBJ_DIR)
	@$(RMDIR) $(GTEST_OBJ_DIR)
	@$(RM) $(GTEST_STRING_MEMBER)
	@$(RM) $(GTEST_STRING_NONMEMBER)


include ../infrastructure/standard_rules.mak
