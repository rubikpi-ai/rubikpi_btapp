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
demo_name := hid_host


# include common makefile rules
include $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/common/build/common.def

# extra source list list
srcdirs :=
appsources :=

# add ENABLE_BTHID=TRUE at the command line to enable
ENABLE_BTHID ?= FALSE
ifeq ($(strip $(ENABLE_BTHID)),TRUE)
  GLOBAL_DEFINE += -DAPP_BTHID_INCLUDED=TRUE
endif

ENABLE_HID_AUDIO ?= TRUE
ifeq ($(strip $(ENABLE_HID_AUDIO)),TRUE)
  GLOBAL_DEFINE += -DAPP_HH_AUDIO_INCLUDED=TRUE
endif

ENABLE_BLE_AUDIO ?= FALSE
ifeq ($(strip $(ENABLE_BLE_AUDIO)),TRUE)
  GLOBAL_DEFINE += -DAPP_HH_BLE_AUDIO_INCLUDED=TRUE
endif
  
ENABLE_ALSA ?= FALSE
ifeq ($(strip $(ENABLE_ALSA)), TRUE)
  GLOBAL_DEFINE += -DPCM_ALSA
  LINKLIBS += -lasound
endif

ENABLE_OTAFWDL ?= TRUE
ifeq ($(strip $(ENABLE_OTAFWDL)),TRUE)
  GLOBAL_DEFINE += -DAPP_HH_OTA_FW_DL_INCLUDED=TRUE
endif

ENABLE_AUDIO_STREAMING ?= TRUE
ifeq ($(strip $(ENABLE_AUDIO_STREAMING)),TRUE)
  GLOBAL_DEFINE += -DAPP_HH_AUDIO_STREAMING_INCLUDED=TRUE
endif

# include variable definitions for each component
include $(RUBIKPI_BTAPP_DEMO_DIR)/demo_build/def/*.def

appsources += \
    app_wav.c \
    app_disc.c \
    app_mgt.c \
    app_utils.c \
    app_xml_param.c \
    app_xml_utils.c \
    app_services.c \
    app_link.c \
    app_dm.c \
    app_thread.c \
    app_ble_client_db.c \
    app_ble_client_xml.c \
    nanoxml.c

# incdirs uses srcdirs
srcdirs := $(srcdirs) $(demo_csrc_dir) $(demo_dir)/../app_ble/source
incdirs := $(incdirs) $(srcdirs) $(demo_cinc_dir) $(demo_dir)/../app_ble/include

# include the build rules for all the sample applications
include $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/common/build/common_make.def
