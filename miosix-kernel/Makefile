##
## Makefile for Miosix embedded OS
##

MAKEFILE_VERSION := 1.07

## Path to kernel directory (edited by init_project_out_of_git_repo.pl)
KPATH := miosix

## Path to config directory (edited by init_project_out_of_git_repo.pl)
CONFPATH := $(KPATH)
include $(CONFPATH)/config/Makefile.inc

ARM_MIOSIX_EABI := C:/arm-miosix-eabi
ARM_NONE_EABI = D:/arm-none-eabi

##
## List here subdirectories which contains makefiles
##
SUBDIRS := $(KPATH)

##
## List here your source files (both .s, .c and .cpp)
##
SRC := \
src/main.cpp \
src/fft/fft.cpp \
src/fft/window.cpp \
src/neural-network/aeabi_memcpy.c \
src/neural-network/arm_dot_prod_f32.c \
src/neural-network/network.c \
src/neural-network/network_data.c \
src/peripheral/button.cpp \
src/peripheral/crc.cpp \
src/peripheral/microphone.cpp

##
## List here additional static libraries with relative path
##
LIBS := lib/arm_cortexM4lf_math.a lib/network_runtime.a

##
## List here additional include directories (in the form -Iinclude_dir)
##
INCLUDE_DIRS :=

##############################################################################
## You should not need to modify anything below                             ##
##############################################################################

ifeq ("$(VERBOSE)","1")
Q := 
ECHO := @true
else
Q := @
ECHO := @echo
endif

## Replaces both "foo.cpp"-->"foo.o" and "foo.c"-->"foo.o"
OBJ := $(addsuffix .o, $(basename $(SRC)))

## Includes the miosix base directory for C/C++
## Always include CONFPATH first, as it overrides the config file location
CXXFLAGS := $(CXXFLAGS_BASE) -I$(CONFPATH) -I$(CONFPATH)/config/$(BOARD_INC)  \
            -I. -I$(KPATH) -I$(KPATH)/arch/common -I$(KPATH)/$(ARCH_INC)      \
            -I$(KPATH)/$(BOARD_INC) $(INCLUDE_DIRS)
CFLAGS   := $(CFLAGS_BASE)   -I$(CONFPATH) -I$(CONFPATH)/config/$(BOARD_INC)  \
            -I. -I$(KPATH) -I$(KPATH)/arch/common -I$(KPATH)/$(ARCH_INC)      \
            -I$(KPATH)/$(BOARD_INC) $(INCLUDE_DIRS)
AFLAGS   := $(AFLAGS_BASE)
LFLAGS   := $(LFLAGS_BASE)
DFLAGS   := -MMD -MP

# LINK_LIBS := $(LIBS) -L$(KPATH) -Wl,--start-group -lmiosix -lstdc++ -lc -lm -lgcc -Wl,--end-group
LINK_LIBS := $(LIBS) -L${CMAKE_CURRENT_BINARY_DIR}/${KPATH_REL} -Wl,--start-group -lmiosix $(ARCH_LIBS) -Wl,--end-group

all: all-recursive main

clean: clean-recursive clean-topdir

program:
	$(PROGRAM_CMDLINE)

all-recursive:
	$(foreach i,$(SUBDIRS),$(MAKE) -C $(i)                               \
	  KPATH=$(shell perl $(KPATH)/_tools/relpath.pl $(i) $(KPATH))       \
	  CONFPATH=$(shell perl $(KPATH)/_tools/relpath.pl $(i) $(CONFPATH)) \
	  || exit 1;)

clean-recursive:
	$(foreach i,$(SUBDIRS),$(MAKE) -C $(i)                               \
	  KPATH=$(shell perl $(KPATH)/_tools/relpath.pl $(i) $(KPATH))       \
	  CONFPATH=$(shell perl $(KPATH)/_tools/relpath.pl $(i) $(CONFPATH)) \
	  clean || exit 1;)

clean-topdir:
	-rm -f $(OBJ) main.elf main.hex main.bin main.map $(OBJ:.o=.d)

main: main.elf
	$(ECHO) "[CP  ] main.hex"
	$(Q)$(CP) -O ihex   main.elf main.hex
	$(ECHO) "[CP  ] main.bin"
	$(Q)$(CP) -O binary main.elf main.bin
	$(Q)$(SZ) main.elf

main.elf: $(OBJ) all-recursive
	$(ECHO) "[LD  ] main.elf"
    $(Q)$(ARM_NONE_EABI)/bin/arm-none-eabi-gcc $(LFLAGS) -o main.elf $(OBJ) $(KPATH)/$(BOOT_FILE) $(LINK_LIBS)
##	$(Q)$(CXX) $(LFLAGS) -o main.elf $(OBJ) $(KPATH)/$(BOOT_FILE) $(LINK_LIBS)

%.o: %.s
	$(ECHO) "[AS  ] $<"
	$(Q)$(AS)  $(AFLAGS) $< -o $@

%.o : %.c
	$(ECHO) "[CC  ] $<"
	$(Q)$(CC)  $(DFLAGS) $(CFLAGS) $< -o $@

%.o : %.cpp
	$(ECHO) "[CXX ] $<"
	$(Q)$(CXX) $(DFLAGS) $(CXXFLAGS) $< -o $@

#pull in dependecy info for existing .o files
-include $(OBJ:.o=.d)
