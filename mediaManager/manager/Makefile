include ../support/standard_macro.mak


############################################################
#### THESE MACROS MUST BE SPECIFIED IN EVERY MAKEFILE!! ####
############################################################

BIN_DIR      = ../bin
GTEST_DIR    = ../../gtest-1.6.0

############################################################
############################################################
############################################################


#### Module-specific Options ####
INC_DIRS += -I /opt/COTS/defaults/boost/include

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
