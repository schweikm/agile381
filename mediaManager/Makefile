include support/standard_macro.mak

#### Objects to Build ####
SUB_DIRS = .


#### Module-specific macros ####
TEST_REP_DIR = test_reports
BIN_DIR      = bin


#### Targets ####
all:
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir/source all; \
	done

clean:
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir/source clean; \
	done
	@$(RM) $(TEST_REP_DIR)/*
	@$(RMDIR) $(BIN_DIR)/$(UT_DIR)

