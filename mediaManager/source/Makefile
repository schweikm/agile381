include ../infrastructure/standard_macro.mak


############################################################
#### THESE MACROS MUST BE SPECIFIED IN EVERY MAKEFILE!! ####
############################################################

BIN_PATH     = ../bin
GTEST_DIR    = ../../gtest-1.6.0

#### don't change this line ####
GTEST_OBJ_DIR = $(BIN_PATH)/$(UT_DIR)/$(UT_OBJ_DIR)

############################################################
############################################################
############################################################


#### Module-specific Options ####

#### Objects to Build ####
OBJS       = $(OBJ_DIR)/String.o
GTEST_OBJS = $(GTEST_OBJ_DIR)/String_member_unittest.o \
             $(GTEST_OBJ_DIR)/String_nonmember_unittest.o


#### Targets ####
all: $(OBJS) $(GTEST_OBJS)
    # handled by standard_rules.mak

include ../infrastructure/standard_rules.mak
