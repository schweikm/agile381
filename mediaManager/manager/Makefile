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
INC_DIRS += -I ..

#### Objects to Build ####
OBJS       = $(OBJ_DIR)/String.o

#### Targets ####
all: $(OBJS)
    # handled by standard_rules.mak


clean:
	@$(RMDIR) $(OBJ_DIR)
	@$(RM) gmon.out
	@$(RM) *.gcov


include ../support/standard_rules.mak
