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
demo_name := app_ble_eddystone


# include common makefile rules
include $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/common/build/common.def

# This flag is used to remove the debug information in the app trace
#GLOBAL_DEFINE += -DAPP_TRACE_NODEBUG

# This flag is used to add timestamp in the app traces
#GLOBAL_DEFINE += -DAPP_TRACE_TIMESTAMP

# This flag is used to add color in the app traces
GLOBAL_DEFINE += -DAPP_TRACE_COLOR

# extra source list list
srcdirs :=
appsources :=

# include variable definitions for each component
include $(RUBIKPI_BTAPP_DEMO_DIR)/demo_build/def/*.def

appsources += \
    app_ble.c \
    app_ble_client.c \
    app_ble_server.c \
    app_ble_client_xml.c \
    app_ble_client_db.c \
    app_disc.c \
    app_utils.c \
    app_dm.c \
    test_vse.c \
    app_mgt.c \
    app_xml_param.c \
    app_xml_utils.c \
    app_services.c \
    app_thread.c \
    nanoxml.c

# incdirs uses srcdirs
srcdirs := $(srcdirs) $(demo_csrc_dir) $(demo_dir)/../test/source $(demo_dir)/../app_ble/source
incdirs := $(incdirs) $(srcdirs) $(demo_cinc_dir) $(demo_dir)/../test/include $(demo_dir)/../app_ble/include

# include the build rules for all the sample applications
include $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/common/build/common_make.def
