include infrastructure/standard_macro.mak


############################################################
#### THESE MACROS MUST BE SPECIFIED IN EVERY MAKEFILE!! ####
############################################################

BIN_PATH     = bin
GTEST_DIR    = ../gtest-1.6.0

#### don't change this line ####
GTEST_OBJ_DIR = $(BIN_PATH)/$(UT_DIR)/$(UT_OBJ_DIR)

############################################################
############################################################
############################################################


#### Module-specific Options ####
TEST_REP_DIR = test_reports


#### Objects to Build ####
SUB_DIRS = .
GOOGLE_TEST = $(BIN_PATH)/$(UT_DIR)/All_Unit_Tests.exe


#### Targets ####
all: deps $(GOOGLE_TEST)

deps:
	@for dir in $(SUB_DIRS); do \
		$(ECHO) ; \
		$(MAKE) -C $$dir/source all; \
	done

$(GOOGLE_TEST):
	@$(ECHO)
	@$(ECHO) "================================================================================"
	$(CXX) $(GTEST_L_FLAGS) $(wildcard $(BIN_PATH)/$(UT_DIR)/$(UT_OBJ_DIR)/*.o) \
$(GTEST_DIR)/src/gtest-all.o $(GTEST_DIR)/src/gtest_main.o -pthread \
-o $(GOOGLE_TEST)
	@$(ECHO)
	@$(ECHO) "Will store \"$(abspath $(BIN_PATH)/$(UT_DIR)/All_Unit_Tests.exe)\""
	@$(ECHO) "================================================================================"
	@$(ECHO)

clean:
	@for dir in $(SUB_DIRS); do \
		$(ECHO) ; \
		$(MAKE) -C $$dir/source clean; \
	done
	$(RM) $(TEST_REP_DIR)/*
	$(RMDIR) $(BIN_PATH)/$(UT_DIR)

