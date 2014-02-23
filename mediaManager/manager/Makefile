include ../support/make/standard_macro.mak


#### Module-specific Options ####
INC_DIRS += -I /mnt/data/Development/Linux/COTS/boost_1_55_0/include \
            -I /mnt/data/Development/Linux/COTS/glog-0.3.3/include

#### Objects to Build ####
OBJS       = String.o \
			 Utility.o

#### Targets ####
all: $(OBJS)
    # handled by standard_rules.mak


clean:
	@$(RM) $(OBJS)
	@$(RM) gmon.out
	@$(RM) *.gcov
	@$(RM) *.gcno
	@$(RM) *.gcda


include ../support/make/standard_rules.mak
