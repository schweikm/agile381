include ../support/standard_macro.mak


#### Module-specific Options ####
INC_DIRS += -I /opt/COTS/defaults/boost/include \
            -I /opt/COTS/defaults/glog/include

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


include ../support/standard_rules.mak
