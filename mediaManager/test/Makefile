include ../support/make/standard_macro.mak


BIN_DIR      = ../bin
UT_DIR       = $(BIN_DIR)/UnitTest
GTEST_DIR    = /mnt/data/Development/Linux/COTS/gtest-1.7.0
BOOST_DIR    = /mnt/data/Development/Linux/COTS/boost_1_55_0
GLOG_DIR     = /mnt/data/Development/Linux/COTS/glog-0.3.3


#### Module-specific Options ####
SRC_DIR     = ../manager
LXXFLAGS   += -pthread
INC_DIRS   += -I $(GTEST_DIR) \
              -I $(GTEST_DIR)/include \
              -I $(BOOST_DIR)/include \
              -I $(GLOG_DIR)/include

LIBS        = -L $(GLOG_DIR)/lib -lglog


#### Objects to Build ####
GTEST_ALL   = gtest-all.o
GTEST_MAIN  = gtest-main.o

GTEST_STRING_EXE  = $(UT_DIR)/String_UT.exe
GTEST_STRING_OBJS = $(SRC_DIR)/String.o \
                    $(SRC_DIR)/Utility.o \
                    $(GTEST_MAIN) \
                    $(GTEST_ALL) \
                    String_unittest.o


#### Targets ####
all: $(GTEST_ALL) $(GTEST_MAIN) $(GTEST_STRING_EXE)
    # handled by standard_rules.mak


$(GTEST_ALL): $(GTEST_DIR)/src/gtest-all.cc
	@$(ECHO)
	@$(ECHO) "================================================================================"
	$(CXX) $(CXXFLAGS) $(INC_DIRS) -o $@ $<
	@$(ECHO)
	@$(ECHO) "Will store \"$(abspath $@)\""
	@$(ECHO) "================================================================================"
	@$(ECHO)


$(GTEST_STRING_EXE): $(GTEST_STRING_OBJS)
	@$(ECHO)
	@$(ECHO) "================================================================================"
	@$(MKDIR) $(UT_DIR)
	$(CXX) $(LXXFLAGS) $(GTEST_STRING_OBJS) $(LIBS) -o $@
	@$(ECHO)
	@$(ECHO) "Will store \"$(abspath $@)\""
	@$(ECHO) "================================================================================"
	@$(ECHO)


clean:
	@$(RM) $(GTEST_STRING_EXE)
	@$(RM) *.o
	@$(RM) gmon.out
	@$(RM) *.gcov
	@$(RM) *.gcno
	@$(RM) *.gcda


include ../support/make/standard_rules.mak
