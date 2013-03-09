include support/make/standard_macro.mak

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
	@$(RM_R) $(BIN_DIR)/*
	@$(RM_R) $(DOC_DIR)/*
	@$(RM_R) $(LOG_DIR)/*
	@$(RM_R) $(REP_DIR)/*

