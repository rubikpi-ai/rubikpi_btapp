#######################################
#  This makefile is written for a GNU make or equivalent.
#  For example:
#   make clean
#   make
# Copyright (c) 2010, Broadcom Corp., All Rights Reserved.
# Broadcom Bluetooth Core. Proprietary and confidential.
#######################################
# If compiling based on the root directory, path inherits from the root directory
ifeq ($(RUBIKPI_BTAPP_ROOTPATH),)
RUBIKPI_BTAPP_ROOTPATH := ../../../..
RUBIKPI_BTAPP_SRCPATH := $(RUBIKPI_BTAPP_ROOTPATH)/src
endif
ifeq ($(os_name),)
os_name := linux
endif
demo_name := av_sw


# include common makefile rules
include $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/common/build/common.def

# extra source list list
srcdirs :=
appsources :=

# add ENABLE_ALSA=TRUE at the command line to enable
ENABLE_ALSA ?= FALSE
ifeq ($(strip $(ENABLE_ALSA)), TRUE)
  GLOBAL_DEFINE += -DPCM_ALSA
  LINKLIBS += -lasound
endif

# AV Broadcast
#GLOBAL_DEFINE += -DAPP_AV_BCST_INCLUDED

# include variable definitions for each component
include $(RUBIKPI_BTAPP_DEMO_DIR)/demo_build/def/*.def

appsources += \
    av.c \
    av_bcst.c \
    app_disc.c \
    app_utils.c \
    app_mgt.c \
    app_xml_utils.c \
    app_xml_param.c \
    app_wav.c \
    app_playlist.c \
    app_mutex.c \
    app_thread.c \
    app_services.c \
    app_dm.c \
    nanoxml.c \
    a2dp.c \
	  hfp_client.c \
	  hfp_ag.c

# incdirs uses srcdirs
srcdirs := $(srcdirs) $(demo_csrc_dir) \
			$(demo_dir)/../av/source \
			$(demo_dir)/../hfp_ag/source \
			$(demo_dir)/../a2dp/source \
			$(demo_dir)/../hfp_client/source
incdirs := $(incdirs) $(srcdirs) $(demo_cinc_dir) \
      $(demo_dir)/../av/include \
      $(demo_dir)/../hfp_ag/include \
      $(demo_dir)/../a2dp/include \
			$(demo_dir)/../hfp_client/include

# include the build rules for all the sample applications
include $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/common/build/common_make.def
