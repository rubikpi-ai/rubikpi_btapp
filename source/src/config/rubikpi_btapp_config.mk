#######################################
#  This makefile is written for a GNU make or equivalent.
#  
#   RUBIK PI BT APP config makefile
#  
# Copyright (c) 2010, Broadcom Corp., All Rights Reserved.
# TC Bluetooth Core. Proprietary and confidential.
#######################################
os_name := linux
CPU := arm64
app_name := rubikpi_btapp

#
# Compiler configuration
#
OPTIM ?= TIME
DEBUG ?= TRUE
FORTIFY ?= TRUE

# Check if the local build machine is 32 or 64 bits for x86



# check if the debug is enabled
ifeq ($(DEBUG),TRUE)
  CCDBGFLAGS := -g
endif

# check if the compilation optimization is enabled
ifeq ($(OPTIM),TIME)
  CCOPTIMFLAGS := -O3
else
ifeq ($(OPTIM),SIZE)
  CCOPTIMFLAGS := -Os
else
ifeq ($(OPTIM),NONE)
  CCOPTIMFLAGS := -O0
endif
endif
endif

ifeq ($(FORTIFY),TRUE)
  CCFORTIFYFLAGS := -D_FORTIFY_SOURCE=2
endif



#
# ------------------    arch   ----------------------
#

  # path library default value
#ARMGCCLIBPATH ?= /opt/toolchains/ToolChain_arm_v7/arm_v7_vfp_le/target/lib/

ARMCCFLAGS += -std=gnu99
CCCPUFLAGS := $(ARMCCFLAGS)
#LINKCPUFLAGS := $(patsubst %,-L %,$(ARMGCCLIBPATH)) $(ARMLINKFLAG)

# CC inclusion flags
CCINC = $(patsubst %,-I%,$(patsubst /,/,$(incdirs)))

# Compiler flags
CCFLAGS = $(CCDBGFLAGS) $(CCOPTIMFLAGS) $(CCCPUFLAGS)  $(CCFORTIFYFLAGS) -DBUILDCFG -Wall -Wextra -Wno-unused-parameter -c


# LINK flags (command line can specify EXTRALIBS=XXX to include specific libraries)
LINKFLAGS = $(LINKCPUFLAGS)
LINK = $(CC)
LINKLIBS := -lpthread


