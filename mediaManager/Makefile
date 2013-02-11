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
all: make_dirs
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir all; \
	done

make_dirs:
	@$(MKDIR) $(BIN_DIR)
	@$(MKDIR) $(DOC_DIR)
	@$(MKDIR) $(LOG_DIR)
	@$(MKDIR) $(REP_DIR)

manager:
	$(MAKE) -C manager all

test:
	$(MAKE) -C test all

clean:
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	@$(RMDIR) $(BIN_DIR)
	@$(RMDIR) $(DOC_DIR)
	@$(RMDIR) $(LOG_DIR)
	@$(RMDIR) $(REP_DIR)

