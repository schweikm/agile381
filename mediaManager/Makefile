include infrastructure/standard_macro.mak

#### Objects to Build ####
SUB_DIRS = .


#### Targets ####
all:
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir/source all; \
	done

clean:
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir/source clean; \
	done

