###############################
#### INITIAL CONFIGURATION ####
###############################

#### System variables ####
SYSTEM  = $(shell uname -s)
MACHINE = $(shell uname -m)

#### Set ARCH ####
SYS  = undef
MACH = undef

## Tailor system name ##
ifeq ($(SYSTEM),Linux)
    SYS = lin
endif

ifeq ($(SYSTEM),Darwin)
    SYS = mac
endif

ifeq ($(SYSTEM),SunOS)
    SYS = sun
endif

## Tailor machine name ##
ifeq ($(MACHINE),i386)
    MACH = 32
endif

ifeq ($(MACHINE),i686)
    MACH = 32
endif

ifeq ($(MACHINE),i86pc)
    MACH = 32
endif

ifeq ($(MACHINE),amd64)
    MACH = 64
endif

ifeq ($(MACHINE),x86_64)
    MACH = 64
endif

ARCH = $(SYS)$(MACH)

#######################
#### SYSTEM MACROS ####
#######################
CC    = /usr/bin/gcc
CXX   = /usr/bin/g++
AR    = /usr/bin/ar
RM    = /bin/rm -f
RMDIR = /bin/rm -fR
MKDIR = /bin/mkdir -p
MAKE  = /usr/bin/make -w
ECHO  = /bin/echo


ifeq ($(SYSTEM),SunOS)
    MAKE = /usr/gnu/bin/make -w
endif


#######################
#### COMMON MACROS ####
#######################
OBJ_DIR    = obj_$(ARCH)
INC_DIRS   = -I ../include
BIN_DIR    =

GCC_VER = $(shell $(CC)  --version | head -1 | cut -d ' ' -f 3)
OLD_GCC = undef

ifeq ($(SYSTEM),Linux)
    OLD_GCC = 4.6.1
endif

ifeq ($(SYSTEM),Darwin)
    OLD_GCC = 4.2.1
endif

ifeq ($(SYSTEM),SunOS)
    OLD_GCC = 4.5.2
endif


#############################
#### GOOGLE TEST OPTIONS ####
#############################
GTEST_C_FLAGS  = -Wall -Wextra -c
GTEST_L_FLAGS  = -Wall -Wextra
GTEST_OBJ_DIR  = obj-UT_$(ARCH)
UT_DIR         = UnitTest
GTEST_INC_DIRS =


########################
#### COMPILER FLAGS ####
########################

#### GCC Generic flags ####
## -ansi:  C = -std=c90; C++ = -std=c++98
##
## -pedantic:  Issue all the warnings demanded by strict ISO C and ISO C++
##
## -Wall:
##         -Waddress   
##         -Warray-bounds (only with -O2)  
##         -Wc++0x-compat  
##         -Wchar-subscripts  
##         -Wenum-compare (in C/Objc; this is on by default in C++) 
##         -Wimplicit-int (C and Objective-C only) 
##         -Wimplicit-function-declaration (C and Objective-C only) 
##         -Wcomment  
##         -Wformat   
##         -Wmain (only for C/ObjC and unless -ffreestanding)  
##         -Wmissing-braces  
##         -Wnonnull  
##         -Wparentheses  
##         -Wpointer-sign  
##         -Wreorder   
##         -Wreturn-type  
##         -Wsequence-point  
##         -Wsign-compare (only in C++)  
##         -Wstrict-aliasing  
##         -Wstrict-overflow=1  
##         -Wswitch  
##         -Wtrigraphs  
##         -Wuninitialized  
##         -Wunknown-pragmas  
##         -Wunused-function  
##         -Wunused-label     
##         -Wunused-value     
##         -Wunused-variable  
##         -Wvolatile-register-var 
##
## -Wextra:
##           -Wclobbered  
##           -Wempty-body  
##           -Wignored-qualifiers 
##           -Wmissing-field-initializers  
##           -Wmissing-parameter-type (C only)  
##           -Wold-style-declaration (C only)  
##           -Woverride-init  
##           -Wsign-compare  
##           -Wtype-limits  
##           -Wuninitialized  
##           -Wunused-parameter (only with -Wunused or -Wall) 
##           -Wunused-but-set-parameter (only with -Wunused or -Wall)  
##
## -Wformat=2:
##              -Wformat
##              -Wformat-nonliteral
##              -Wformat-security
##              -Wformat-y2k
## -Winit-self:  Warn about uninitialized variables which are initialized with themselves
## -Wmissing-include-dirs:  Warn if a user-supplied include directory does not exist
## -Wswitch-default:  Warn whenever a switch statement does not have a default case
## -Wswitch-enum:  Warn whenever a switch statement has an index of enumerated type and lacks a case for one or more of the named codes of that enumeration
## -Wunused-parameter:  Warn whenever a function parameter is unused aside from its declaration
## -Wunknown-pragmas:  Warn when a #pragma directive is encountered which is not understood by GCC
## -Wfloat-equal:  Warn if floating point values are used in equality comparisons
## -Wundef:  Warn if an undefined identifier is evaluated in an `#if' directive
## -Wshadow:  Warn whenever a local variable or type declaration shadows another variable, parameter, type, or class member
## -Wunsafe-loop-optimizations:  Warn if the loop cannot be optimized because the compiler could not assume anything on the bounds of the loop indices
## -Wcast-qual:  Warn whenever a pointer is cast so as to remove a type qualifier from the target type
## -Wcast-align:  Warn whenever a pointer is cast such that the required alignment of the target is increased
## -Wconversion:  Warn for implicit conversions that may alter a value
## -Wmissing-format-attribute:  Warn about function pointers which might be candidates for format attributes
## -Wpacked:  Warn if a structure is given the packed attribute, but the packed attribute has no effect on the layout or size of the structure
## -Wpadded:  Warn if padding is included in a structure, either to align an element of the structure or to align the whole structure
## -Wredundant-decls:  Warn if anything is declared more than once in the same scope
## -Winline:  Warn if a function can not be inlined and it was declared as inline
## -Winvalid-pch:  Warn if a precompiled header is found in the search path but can't be used
## -Wdisabled-optimization:  Warn if a requested optimization pass is disabled
## -Wstack-protector:  Warns about functions that will not be protected against stack smashing
GENERIC_CFLAGS  = -ansi -pedantic -Wall -Wextra -Wformat=2 \
                  -Winit-self -Wmissing-include-dirs -Wswitch-default -Wswitch-enum \
                  -Wunused-parameter -Wunknown-pragmas -Wfloat-equal \
                  -Wundef -Wshadow -Wunsafe-loop-optimizations  -Wcast-qual \
                  -Wcast-align -Wconversion \
                  -Wmissing-format-attribute -Wpacked \
                  -Wpadded -Wredundant-decls -Winline -Winvalid-pch -Wdisabled-optimization \
                  -Wstack-protector


#### Language-specific warning flags ####
## -Wdeclaration-after-statement:  Warn when a declaration is found after a statement in a block
## -Wbad-function-cast:  Warn whenever a function call is cast to a non-matching type
## -Wc++-compat:  Warn about ISO C constructs that are outside of the common subset of ISO C and ISO C++
## -Wstrict-prototypes:  Warn if a function is declared or defined without specifying the argument types
## -Wold-style-definition:  Warn if an old-style function definition is used
## -Wmissing-prototypes:  Warn if a global function is defined without a previous prototype declaration
## -Wnested-externs:  Warn if an extern declaration is encountered within a function
## -Wunsuffixed-float-constants:  GCC will issue a warning for any floating constant that does not have a suffix
C_WARN_CFLAGS   = -Wdeclaration-after-statement -Wbad-function-cast -Wc++-compat \
                  -Wstrict-prototypes -Wold-style-definition -Wmissing-prototypes \
                  -Wnested-externs -Wunsuffixed-float-constants


## -Wctor-dtor-privacy:  Warn when a class seems unusable
## -Wnoexcept:  Warn when a noexcept-expression evaluates to false
## -Weffc++:  Warn about violations of the following style guidelines from Scott Meyers' Effective C++ book
## -Wstrict-null-sentinel:  Warn also about the use of an uncasted NULL as sentinel
## -Wold-style-cast:  Warn if an old-style (C-style) cast to a non-void type is used within a C++ program
## -Woverloaded-virtual:  Warn when a function declaration hides virtual functions from a base class
## -Wsign-promo:  Warn when overload resolution chooses a promotion from unsigned or enumerated type to a signed type
C++_WARN_CFLAGS = -Wctor-dtor-privacy -Wnoexcept -Weffc++ -Wstrict-null-sentinel \
                  -Wold-style-cast -Woverloaded-virtual -Wsign-promo


#####################
#### DEBUG FLAGS ####
#####################

ifeq ($(DEBUG),on)
    GENERIC_CFLAGS += -g3 -ggdb3 -DDEBUG
    GTEST_C_FLAGS  += -g3 -ggdb3 -DDEBUG
    GTEST_L_FLAGS  += -g3 -ggdb3 -DDEBUG
endif


#######################
#### RELEASE FLAGS ####
#######################

ifeq ($(RELEASE),on)
    GENERIC_CFLAGS += -O3
    GTEST_C_FLAGS  += -O3
    GTEST_L_FLAGS  += -O3
endif


#######################
#### PLAFORM FLAGS ####
#######################

ifneq ($(SYSTEM),Darwin)
    ## -Wsign-conversion:  Warn for implicit conversions that may change the sign of an integer value
    ## -Wlogical-op:  Warn about suspicious uses of logical operators in expressions
    PLATFORM_CFLAGS += -Wsign-conversion -Wlogical-op
endif

ifeq ($(SYSTEM),Linux)
    ## -Wdouble-promotion:  Give a warning when a value of type float is implicitly promoted to double
    ## -Wtrampolines:  Warn about trampolines generated for pointers to nested functions
    PLATFORM_CFLAGS += -Wdouble-promotion -Wtrampolines
endif

PLATFORM_C_CFLAGS   = $(PLATFORM_CFLAGS)
PLATFORM_C_C++FLAGS = $(PLATFORM_CFLAGS)

ifneq ($(SYSTEM),Darwin)
    ## -Wmissing-declarations:  Warn if a global function is defined without a previous declaration
    PLATFORM_C_CFLAGS   += -Wmissing-declarations
endif

#### Build the combined flags ####
BASE_CFLAGS   = $(GENERIC_CFLAGS) $(C_WARN_FLAGS) $(PLATFORM_C_CFLAGS)
BASE_C++FLAGS = $(GENERIC_CFLAGS) $(C++_WARN_FLAGS) $(PLATFORM_C_C++FLAGS)

CFLAGS   = -c $(BASE_CFLAGS)
C++FLAGS = -c $(BASE_C++FLAGS)


#######################
#### ARCHIVE FLAGS ####
#######################

ARFLAGS = crv


######################
#### LINKER FLAGS ####
######################

LFLAGS   = $(BASE_CFLAGS)
L++FLAGS = $(BASE_C++FLAGS)

