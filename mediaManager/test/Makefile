include ../support/standard_macro.mak


############################################################
#### THESE MACROS MUST BE SPECIFIED IN EVERY MAKEFILE!! ####
############################################################

BIN_DIR      = ../bin
GTEST_DIR    = /opt/COTS/defaults/gtest

############################################################
############################################################
############################################################


#### Module-specific Options ####
SRC_DIR     = ../manager
INC_DIRS   += -I $(GTEST_DIR)/include \
              -I /opt/COTS/defaults/boost/include \
              -I /opt/COTS/defaults/glog/include

LIBS        = -L /opt/COTS/defaults/glog/lib -lglog
COMMON_OBJS =  $(GTEST_DIR)/src/gtest-all.o \
               gtestMain.o 

LXXFLAGS   += -pthread


#### Objects to Build ####
GTEST_STRING_MEMBER      = $(BIN_DIR)/$(UT_DIR)/StringMemberTest_UT.exe
GTEST_STRING_MEMBER_OBJS = $(SRC_DIR)/String.o \
                           StringMemberTest_unittest.o

GTEST_STRING_NONMEMBER      = $(BIN_DIR)/$(UT_DIR)/StringNonMemberTest_UT.exe
GTEST_STRING_NONMEMBER_OBJS = $(SRC_DIR)/String.o \
                              StringNonMemberTest_unittest.o


#### Targets ####
all: gtestMain.o $(GTEST_STRING_MEMBER) $(GTEST_STRING_NONMEMBER)
    # handled by standard_rules.mak


$(GTEST_STRING_MEMBER): $(GTEST_STRING_MEMBER_OBJS)
	@$(ECHO)
	@$(ECHO) "================================================================================"
	@$(MKDIR) $(BIN_DIR)/$(UT_DIR)
	$(CXX) $(LXXFLAGS) $(GTEST_STRING_MEMBER_OBJS) $(COMMON_OBJS) $(LIBS) -o $@
	@$(ECHO)
	@$(ECHO) "Will store \"$(abspath $@)\""
	@$(ECHO) "================================================================================"
	@$(ECHO)


$(GTEST_STRING_NONMEMBER): $(GTEST_STRING_NONMEMBER_OBJS)
	@$(ECHO)
	@$(ECHO) "================================================================================"
	@$(MKDIR) $(BIN_DIR)/$(UT_DIR)
	$(CXX) $(LXXFLAGS) $(GTEST_STRING_NONMEMBER_OBJS) $(COMMON_OBJS) $(LIBS) -o $@
	@$(ECHO)
	@$(ECHO) "Will store \"$(abspath $@)\""
	@$(ECHO) "================================================================================"
	@$(ECHO)


clean:
	@$(RM) $(GTEST_STRING_MEMBER)
	@$(RM) $(GTEST_STRING_NONMEMBER)
	@$(RM) *.o
	@$(RM) gmon.out
	@$(RM) *.gcov
	@$(RM) *.gcno
	@$(RM) *.gcda


include ../support/standard_rules.mak
