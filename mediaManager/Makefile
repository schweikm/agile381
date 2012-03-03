include infrastructure/standard_macro.mak

# directories to be built
SUB_DIRS = .

# targets
all:
	@for dir in $(SUB_DIRS); do \
		$(ECHO) ; \
		$(MAKE) -C $$dir/source all; \
	done

clean:
	@for dir in $(SUB_DIRS); do \
		$(ECHO) ; \
		$(MAKE) -C $$dir/source clean; \
	done

