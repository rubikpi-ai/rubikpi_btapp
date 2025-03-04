#######################################
#  This makefile is written for a GNU make or equivalent.
#  
#   src compile
#
# Copyright (c) 2010, Broadcom Corp., All Rights Reserved.
# Broadcom Bluetooth Core. Proprietary and confidential.
#######################################



# Basic path definitions
export RUBIKPI_BTAPP_ROOTPATH := $(shell pwd)/..
export RUBIKPI_BTAPP_SRCPATH := $(RUBIKPI_BTAPP_ROOTPATH)/src

include $(RUBIKPI_BTAPP_SRCPATH)/config/rubikpi_btapp_config.mk
os_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)

# config file dir
cfgincdir    := $(os_dir)/config
export BSA_LIB_PATH = $(os_dir)/libbsa

# BSA library related directories
bsastaticlib := $(BSA_LIB_PATH)/build/$(CPU)/libbsa.a
ifeq ($(findstring CYGWIN_NT,$(shell uname -s)),CYGWIN_NT)
bsasharedlib := $(BSA_LIB_PATH)/build/$(CPU)/sharedlib/libbsa.dll
else
bsasharedlib := $(BSA_LIB_PATH)/build/$(CPU)/sharedlib/libbsa.so
endif
bsalibincdir := $(BSA_LIB_PATH)/include

#######################################
#
# BSA client library
#
#######################################
ifeq ($(BSASHAREDLIB), TRUE)
bsalib := $(bsasharedlib)
else
bsalib := $(bsastaticlib)
endif

demo_build_dirs := $(wildcard $(os_dir)/*/demo_build/)
#######################################
#
# Targets
#
#######################################

.PHONY: all clean

all:
	@echo start building rubikpi_btapp
	@$(MAKE) -C $(os_dir)
	@echo Done Building rubikpi_btapp for  "$(os_name)" 


%:
	@echo start building bt $@ demo
	@$(MAKE) -C $(os_dir)/$@/demo_build
	@echo Done Building $@ for  "$(os_name)"

clean:
	@echo Cleaning up for "$(os_name) $(demo_build_dirs)"
	@$(MAKE) -C $(os_dir) clean
	@for dir in $(demo_build_dirs); do \
		$(MAKE) -C $$dir clean; \
		done
	@echo Finished cleaning up

