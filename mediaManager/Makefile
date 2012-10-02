include support/standard_macro.mak

#### Objects to Build ####
SUB_DIRS = manager test


#### Module-specific macros ####
REP_DIR = reports
BIN_DIR = bin
LOG_DIR = log
DOC_DIR = doc

.PHONY: manager test

#### Targets ####
all:
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir all; \
	done

manager:
	$(MAKE) -C manager all

test:
	$(MAKE) -C test all

clean:
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	@$(RM)    $(REP_DIR)/*
	@$(RMDIR) $(BIN_DIR)/$(UT_DIR)
	@$(RM)    $(LOG_DIR)/*
	@$(RMDIR) $(DOC_DIR)/*

