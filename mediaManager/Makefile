include support/standard_macro.mak

#### Objects to Build ####
SUB_DIRS = manager test


#### Module-specific macros ####
REP_DIR = reports
BIN_DIR = bin


#### Targets ####
all:
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir all; \
	done

clean:
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	@$(RM) $(REP_DIR)/*
	@$(RMDIR) $(BIN_DIR)/$(UT_DIR)

