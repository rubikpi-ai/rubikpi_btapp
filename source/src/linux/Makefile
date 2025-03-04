#######################################
#  This makefile is written for a GNU make or equivalent.
#  make for linux application
#   The makefile inherits only the makefile in the src root directory and cannot be compiled separately
#   
# Copyright (c) 2010, Broadcom Corp., All Rights Reserved.
# Broadcom Bluetooth Core. Proprietary and confidential.
#######################################
# If compiling based on the root directory, path inherits from the root directory
ifeq ($(RUBIKPI_BTAPP_ROOTPATH),)
RUBIKPI_BTAPP_ROOTPATH := ../..
RUBIKPI_BTAPP_SRCPATH := $(RUBIKPI_BTAPP_ROOTPATH)/src
endif
include $(RUBIKPI_BTAPP_SRCPATH)/config/rubikpi_btapp_config.mk
ifeq ($(os_name),)
os_name := linux
endif
ifeq ($(CCINC),)
# CC inclusion flags
CCINC = $(patsubst %,-I%,$(patsubst /,/,$(incdirs)))
endif
ifeq ($(app_name),)
#btapp default name
app_name := rubikpi_btapp
endif
ifeq ($(BSA_LIB_DIR),)
BSA_LIB_DIR := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/libbsa
# BSA library related directories
bsastaticlib := $(BSA_LIB_DIR)/build/$(CPU)/libbsa.a
ifeq ($(findstring CYGWIN_NT,$(shell uname -s)),CYGWIN_NT)
bsasharedlib := $(BSA_LIB_DIR)/build/$(CPU)/sharedlib/libbsa.dll
else
bsasharedlib := $(BSA_LIB_DIR)/build/$(CPU)/sharedlib/libbsa.so
endif
bsalibincdir := $(BSA_LIB_DIR)/include

#######################################
#
# BSA client library
#
#######################################
ifeq ($(BSASHAREDLIB), TRUE)
bsalib := $(bsasharedlib)
else
bsalib := $(BSA_LIB_DIR)/build/$(CPU)
endif

endif



# demo related directories
main_dir       := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/main
common_dir     := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/common
common_inc_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/common/include
common_src_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/common/source

build_dir     := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/build/$(CPU)
obj_dir       := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/build/$(CPU)/obj
exe_dir       := $(RUBIKPI_BTAPP_ROOTPATH)


# demo config file dir
cfgdir    := $(RUBIKPI_BTAPP_SRCPATH)/config

# base directory source, library, and target lists

srcdirs := $(main_dir)/source \
    $(common_src_dir)
incdirs := . \
	$(srcdirs) \
	$(bsalibincdir) \
	$(main_dir)/include \
    $(common_inc_dir)

appsources := main.c \
    app_disc.c \
    app_utils.c \
    app_dm.c \
    app_xml_param.c \
    app_xml_utils.c \
    app_services.c \
    app_mgt.c \
    nanoxml.c \
    app_thread.c \
	app_wav.c \
    app_mutex.c \
	app_link.c \
	app_op_vcard.c \
    app_op_fmt.c \
	app_playlist.c


include $(RUBIKPI_BTAPP_SRCPATH)/config/rubikpi_btapp.conf

### enable manager（default）
ifeq ($(BtApp_Manager_Enable),true)
GLOBAL_DEFINE += -DBTAPP_MANAGER_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/manager
include $(demo_dir)/demo_build/def/*.def
else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/manager/include
endif
######################################################################

# enable opp
ifeq ($(BtApp_Opp_Enable),true)
GLOBAL_DEFINE += -DBTAPP_OPP_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/opp
include $(demo_dir)/build/def/*.def
else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/opp/include
endif
######################################################################

# enable pan
ifeq ($(BtApp_Pan_Enable),true)
GLOBAL_DEFINE += -DBTAPP_PAN_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/pan
include $(demo_dir)/demo_build/def/*.def
else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/pan/include
endif
######################################################################

# enable hfp_ag
ifeq ($(BtApp_HFP_AG_Enable),true)
GLOBAL_DEFINE += -DBTAPP_HFP_AG_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/hfp_ag

# add ENABLE_ALSA=TRUE at the command line to enable
ENABLE_ALSA ?= FALSE
ifeq ($(strip $(ENABLE_ALSA)), TRUE)
  LINKLIBS += -lasound
else
  GLOBAL_DEFINE += -DPCM_ALSA_DISABLE_AG
endif

include $(demo_dir)/demo_build/def/*.def
else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/hfp_ag/include
endif
######################################################################

# enable hfp_client
ifeq ($(BtApp_HFP_Client_Enable),true)
GLOBAL_DEFINE += -DBTAPP_HFP_CLIENT_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/hfp_client

ENABLE_ALSA ?= FALSE
ifeq ($(strip $(ENABLE_ALSA)), TRUE)
  GLOBAL_DEFINE += -DPCM_ALSA
  LINKLIBS += -lasound
else
  GLOBAL_DEFINE += -DPCM_ALSA_DISABLE_HS
endif

include $(demo_dir)/demo_build/def/*.def
else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/hfp_client/include
endif
######################################################################

# enable data gateway
ifeq ($(BtApp_Data_GW_Enable),true)
GLOBAL_DEFINE += -DBTAPP_DATA_GW_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/data_gw
include $(demo_dir)/demo_build/def/*.def
else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/data_gw/include
endif
######################################################################

# enable fm
ifeq ($(BtApp_FM_Enable),true)
GLOBAL_DEFINE += -DBTAPP_FM_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/fm
include $(demo_dir)/demo_build/def/*.def
GLOBAL_DEFINE += -DAPP_FM_DEFAULT_RSSI_THRESH=102
else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/fm/include
endif
######################################################################

# enable ftp
ifeq ($(BtApp_Ftp_Enable),true)
GLOBAL_DEFINE += -DBTAPP_FTP_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/ftp
include $(demo_dir)/build/def/*.def
else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/ftp/include
endif
######################################################################

# enable sap
ifeq ($(BtApp_Sap_Enable),true)
GLOBAL_DEFINE += -DBTAPP_SAP_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/sap
include $(demo_dir)/build/def/*.def
else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/sap/include
endif
######################################################################

# enable pbap
ifeq ($(BtApp_Pbap_Enable),true)
GLOBAL_DEFINE += -DBTAPP_PBAP_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/pbap
include $(demo_dir)/build/def/*.def
else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/pbap/include
endif
######################################################################

# enable hid_dev
ifeq ($(BtApp_HID_Dev_Enable),true)
GLOBAL_DEFINE += -DBTAPP_HID_DEV_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/hid_dev

ENABLE_AUDIO_STREAMING ?= TRUE
ifeq ($(strip $(ENABLE_AUDIO_STREAMING)),TRUE)
  GLOBAL_DEFINE += -DAPP_HD_AUDIO_STREAMING_INCLUDED=TRUE
endif

include $(demo_dir)/demo_build/def/*.def
else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/hid_dev/include
endif
######################################################################

# enable ctn
ifeq ($(BtApp_CTN_Enable),true)
GLOBAL_DEFINE += -DBTAPP_CTN_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/ctn
btasysdir    := $(componentdir)/bta/sys
include $(demo_dir)/demo_build/def/*.def
incdirs := $(incdirs) $(btasysdir)
else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/ctn/include
endif
######################################################################

# enable map
ifeq ($(BtApp_Map_Enable),true)
GLOBAL_DEFINE += -DBTAPP_MAP_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/map
btasysdir    := $(componentdir)/bta/sys
include $(demo_dir)/demo_build/def/*.def
incdirs := $(incdirs) $(btasysdir)
else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/map/include
endif
######################################################################

# enable health
ifeq ($(BtApp_Health_Enable),true)
GLOBAL_DEFINE += -DBTAPP_HEALTH_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/health

# This flag is used to add color in the app traces
GLOBAL_DEFINE += -DAPP_TRACE_COLOR

include $(demo_dir)/demo_build/def/*.def
else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/health/include
endif
######################################################################

# enable nsa
ifeq ($(BtApp_Nsa_Enable),true)
GLOBAL_DEFINE += -DBTAPP_NSA_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/nsa

# This flag is used to remove the debug information in the app trace
#GLOBAL_DEFINE += -DAPP_TRACE_NODEBUG

# This flag is used to add timestamp in the app traces
#GLOBAL_DEFINE += -DAPP_TRACE_TIMESTAMP

# This flag is used to add color in the app traces
GLOBAL_DEFINE += -DAPP_TRACE_COLOR

include $(demo_dir)/demo_build/def/*.def
else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/nsa/include
endif
######################################################################

# enable test mode
ifeq ($(BtApp_TestMode_Enable),true)
GLOBAL_DEFINE += -DBTAPP_TEST_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/test
include $(demo_dir)/demo_build/def/*.def
else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/test/include
endif
######################################################################

# enable av
ifeq ($(BtApp_AV_Enable),true)
GLOBAL_DEFINE += -DBTAPP_AV_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/av

# add ENABLE_ALSA=TRUE at the command line to enable
ENABLE_ALSA ?= FALSE
ifeq ($(strip $(ENABLE_ALSA)), TRUE)
  GLOBAL_DEFINE += -DPCM_ALSA
  LINKLIBS += -lasound
endif

# AV Broadcast
#GLOBAL_DEFINE += -DAPP_AV_BCST_INCLUDED
#GLOBAL_DEFINE += -DAPP_AV_BCST_DYNAMIC_LTADDR
#GLOBAL_DEFINE += -DAPP_AV_BCST_PLAY_LOOPDRV_INCLUDED

include $(demo_dir)/demo_build/def/*.def
else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/av/include
endif
######################################################################

# enable headless
ifeq ($(BtApp_Headless_Enable),true)
GLOBAL_DEFINE += -DBTAPP_HEADLESS_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/headless

# This flag is used to remove the debug information in the app trace
#GLOBAL_DEFINE += -DAPP_TRACE_NODEBUG

# This flag is used to add timestamp in the app traces
#GLOBAL_DEFINE += -DAPP_TRACE_TIMESTAMP

# This flag is used to add color in the app traces
GLOBAL_DEFINE += -DAPP_TRACE_COLOR

include $(demo_dir)/demo_build/def/*.def

# add test mode source for headless
ifneq ($(BtApp_TestMode_Enable),true)
srcdirs := $(srcdirs) $(demo_dir)/../test/source
incdirs := $(incdirs) $(demo_dir)/../test/include $(demo_dir)/../test/source
endif

else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/headless/include
endif
######################################################################

# enable 3D
ifeq ($(BtApp_3D_Enable),true)
GLOBAL_DEFINE += -DBTAPP_3D_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/app_3d

# This flag is used to remove the debug information in the app trace
#GLOBAL_DEFINE += -DAPP_TRACE_NODEBUG

# This flag is used to add timestamp in the app traces
#GLOBAL_DEFINE += -DAPP_TRACE_TIMESTAMP

# This flag is used to add color in the app traces
GLOBAL_DEFINE += -DAPP_TRACE_COLOR

# Add VSync delay (for old 3D TV)
#GLOBAL_DEFINE += -DAPP_3DTV_VSYNC_DELAY=8120

include $(demo_dir)/demo_build/def/*.def

#Check if the test source file is already included, The 3D demo will call the method
TEST_DIR := $(findstring test/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../test/source
incdirs := $(incdirs) $(demo_dir)/../test/include $(demo_dir)/../test/source
endif

TEST_FILE := $(findstring test_vse.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) test_vse.c
endif

else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/app_3d/include
endif
######################################################################

#enable a2dp
ifeq ($(BtApp_A2dp_Enable),true)
GLOBAL_DEFINE += -DBTAPP_A2DP_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/a2dp

# add ENABLE_ALSA=TRUE at the command line to enable
ENABLE_ALSA ?= FALSE
ifeq ($(strip $(ENABLE_ALSA)), TRUE)
  GLOBAL_DEFINE += -DPCM_ALSA
  LINKLIBS += -lasound
endif

include $(demo_dir)/demo_build/def/*.def
else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/a2dp/include
endif
######################################################################

# enable BLE
ifeq ($(BtApp_BLE_Enable),true)
GLOBAL_DEFINE += -DBTAPP_BLE_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/app_ble

# This flag is used to remove the debug information in the app trace
#GLOBAL_DEFINE += -DAPP_TRACE_NODEBUG

# This flag is used to add timestamp in the app traces
#GLOBAL_DEFINE += -DAPP_TRACE_TIMESTAMP

# This flag is used to add color in the app traces
GLOBAL_DEFINE += -DAPP_TRACE_COLOR

ENABLE_BLE_FWDL ?= FALSE
ifeq ($(strip $(ENABLE_BLE_FWDL)),TRUE)
  GLOBAL_DEFINE += -DAPP_BLE_OTA_FW_DL_INCLUDED=TRUE
endif

# This flag is used to Support Broadcom's Proprietary BLE2 menu
ENABLE_BLE2_BRCM ?= FALSE
ifeq ($(strip $(ENABLE_BLE2_BRCM)),TRUE)
GLOBAL_DEFINE += -DAPP_BLE2_BRCM_INCLUDED
endif

include $(demo_dir)/demo_build/def/*.def

#Check if the test source file is already included, The 3D demo will call the method
TEST_DIR := $(findstring test/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../test/source
incdirs := $(incdirs) $(demo_dir)/../test/include $(demo_dir)/../test/source
endif

TEST_FILE := $(findstring test_vse.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) test_vse.c
endif

else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/app_ble/include
endif
######################################################################

# enable hid_host
ifeq ($(BtApp_HID_Host_Enable),true)
GLOBAL_DEFINE += -DBTAPP_HID_HOST_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/hid_host

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

include $(demo_dir)/demo_build/def/*.def

TEST_FILE := $(findstring app_ble_client_db.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
srcdirs := $(srcdirs) $(demo_dir)/../app_ble/source
incdirs := $(incdirs) $(demo_dir)/../app_ble/include $(demo_dir)/../app_ble/source
appsources := $(appsources) \
    app_ble_client_db.c \
    app_ble_client_xml.c
endif

else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/hid_host/include
endif
######################################################################

# enable BLE ancs
ifeq ($(BtApp_BLE_Ancs_Enable),true)
GLOBAL_DEFINE += -DBTAPP_BLE_ANCS_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/app_ble_ancs
include $(demo_dir)/demo_build/def/*.def

#Check if the test source file is already included, The 3D demo will call the method
TEST_DIR := $(findstring test/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../test/source
incdirs := $(incdirs) $(demo_dir)/../test/include $(demo_dir)/../test/source
endif

#Check if the test source file is already included
TEST_DIR := $(findstring app_ble/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../app_ble/source
incdirs := $(incdirs) $(demo_dir)/../app_ble/include $(demo_dir)/../app_ble/source
endif

TEST_FILE := $(findstring app_ble.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) \
	app_ble.c \
    app_ble_client.c \
    app_ble_server.c \
    app_ble_client_xml.c \
    app_ble_client_db.c
endif

TEST_FILE := $(findstring test_vse.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) test_vse.c
endif

else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/app_ble_ancs/include
endif
######################################################################

# enable BLE blood pressure
ifeq ($(BtApp_BLE_Blp_Enable),true)
GLOBAL_DEFINE += -DBTAPP_BLE_BLP_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/app_ble_blp
include $(demo_dir)/demo_build/def/*.def

#Check if the test source file is already included, The 3D demo will call the method
TEST_DIR := $(findstring test/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../test/source
incdirs := $(incdirs) $(demo_dir)/../test/include $(demo_dir)/../test/source
endif

#Check if the test source file is already included
TEST_DIR := $(findstring app_ble/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../app_ble/source
incdirs := $(incdirs) $(demo_dir)/../app_ble/include $(demo_dir)/../app_ble/source
endif

TEST_FILE := $(findstring app_ble.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) \
	app_ble.c \
    app_ble_client.c \
    app_ble_server.c \
    app_ble_client_xml.c \
    app_ble_client_db.c
endif

TEST_FILE := $(findstring test_vse.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) test_vse.c
endif

else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/app_ble_blp/include
endif
######################################################################

# enable BLE cscc
ifeq ($(BtApp_BLE_Cscc_Enable),true)
GLOBAL_DEFINE += -DBTAPP_BLE_CSCC_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/app_ble_cscc
include $(demo_dir)/demo_build/def/*.def

#Check if the test source file is already included, The 3D demo will call the method
TEST_DIR := $(findstring test/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../test/source
incdirs := $(incdirs) $(demo_dir)/../test/include $(demo_dir)/../test/source
endif

#Check if the test source file is already included
TEST_DIR := $(findstring app_ble/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../app_ble/source
incdirs := $(incdirs) $(demo_dir)/../app_ble/include $(demo_dir)/../app_ble/source
endif

TEST_FILE := $(findstring app_ble.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) \
	app_ble.c \
    app_ble_client.c \
    app_ble_server.c \
    app_ble_client_xml.c \
    app_ble_client_db.c
endif

TEST_FILE := $(findstring test_vse.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) test_vse.c
endif

else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/app_ble_cscc/include
endif
######################################################################

# enable BLE eddystone
ifeq ($(BtApp_BLE_Eddystone_Enable),true)
GLOBAL_DEFINE += -DBTAPP_BLE_EDDYSTONE_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/app_ble_eddystone
include $(demo_dir)/demo_build/def/*.def

#Check if the test source file is already included
TEST_DIR := $(findstring test/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../test/source
incdirs := $(incdirs) $(demo_dir)/../test/include $(demo_dir)/../test/source
endif

#Check if the test source file is already included
TEST_DIR := $(findstring app_ble/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../app_ble/source
incdirs := $(incdirs) $(demo_dir)/../app_ble/include $(demo_dir)/../app_ble/source
endif

TEST_FILE := $(findstring app_ble.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) \
	app_ble.c \
    app_ble_client.c \
    app_ble_server.c \
    app_ble_client_xml.c \
    app_ble_client_db.c
endif

TEST_FILE := $(findstring test_vse.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) test_vse.c
endif

else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/app_ble_eddystone/include
endif
######################################################################

# enable BLE hrc
ifeq ($(BtApp_BLE_Hrc_Enable),true)
GLOBAL_DEFINE += -DBTAPP_BLE_HRC_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/app_ble_hrc
include $(demo_dir)/demo_build/def/*.def

#Check if the test source file is already included
TEST_DIR := $(findstring test/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../test/source
incdirs := $(incdirs) $(demo_dir)/../test/include $(demo_dir)/../test/source
endif

#Check if the test source file is already included
TEST_DIR := $(findstring app_ble/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../app_ble/source
incdirs := $(incdirs) $(demo_dir)/../app_ble/include $(demo_dir)/../app_ble/source
endif

TEST_FILE := $(findstring app_ble.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) \
	app_ble.c \
    app_ble_client.c \
    app_ble_server.c \
    app_ble_client_xml.c \
    app_ble_client_db.c
endif

TEST_FILE := $(findstring test_vse.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) test_vse.c
endif

else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/app_ble_hrc/include
endif
######################################################################

# enable BLE htp
ifeq ($(BtApp_BLE_Htp_Enable),true)
GLOBAL_DEFINE += -DBTAPP_BLE_HTP_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/app_ble_htp
include $(demo_dir)/demo_build/def/*.def

#Check if the test source file is already included
TEST_DIR := $(findstring test/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../test/source
incdirs := $(incdirs) $(demo_dir)/../test/include $(demo_dir)/../test/source
endif

#Check if the test source file is already included
TEST_DIR := $(findstring app_ble/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../app_ble/source
incdirs := $(incdirs) $(demo_dir)/../app_ble/include $(demo_dir)/../app_ble/source
endif

TEST_FILE := $(findstring app_ble.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) \
	app_ble.c \
    app_ble_client.c \
    app_ble_server.c \
    app_ble_client_xml.c \
    app_ble_client_db.c
endif

TEST_FILE := $(findstring test_vse.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) test_vse.c
endif

else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/app_ble_htp/include
endif
######################################################################

# enable BLE pm
ifeq ($(BtApp_BLE_PM_Enable),true)
GLOBAL_DEFINE += -DBTAPP_BLE_PM_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/app_ble_pm
include $(demo_dir)/demo_build/def/*.def

#Check if the test source file is already included
TEST_DIR := $(findstring test/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../test/source
incdirs := $(incdirs) $(demo_dir)/../test/include $(demo_dir)/../test/source
endif

#Check if the test source file is already included
TEST_DIR := $(findstring app_ble/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../app_ble/source
incdirs := $(incdirs) $(demo_dir)/../app_ble/include $(demo_dir)/../app_ble/source
endif

TEST_FILE := $(findstring app_ble.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) \
	app_ble.c \
    app_ble_client.c \
    app_ble_server.c \
    app_ble_client_xml.c \
    app_ble_client_db.c
endif

TEST_FILE := $(findstring test_vse.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) test_vse.c
endif

TEST_FILE := $(findstring app_ble2_brcm.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) app_ble2_brcm.c
endif

else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/app_ble_pm/include
endif
######################################################################

# enable BLE rscc
ifeq ($(BtApp_BLE_Rscc_Enable),true)
GLOBAL_DEFINE += -DBTAPP_BLE_RSCC_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/app_ble_rscc
include $(demo_dir)/demo_build/def/*.def

#Check if the test source file is already included
TEST_DIR := $(findstring test/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../test/source
incdirs := $(incdirs) $(demo_dir)/../test/include $(demo_dir)/../test/source
endif

#Check if the test source file is already included
TEST_DIR := $(findstring app_ble/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../app_ble/source
incdirs := $(incdirs) $(demo_dir)/../app_ble/include $(demo_dir)/../app_ble/source
endif

TEST_FILE := $(findstring app_ble.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) \
	app_ble.c \
    app_ble_client.c \
    app_ble_server.c \
    app_ble_client_xml.c \
    app_ble_client_db.c
endif

TEST_FILE := $(findstring test_vse.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) test_vse.c
endif

else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/app_ble_rscc/include
endif
######################################################################

# enable BLE tvselect
ifeq ($(BtApp_BLE_TVselect_Enable),true)
GLOBAL_DEFINE += -DBTAPP_BLE_TVSELECT_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/app_ble_tvselect
include $(demo_dir)/demo_build/def/*.def

#Check if the test source file is already included
TEST_DIR := $(findstring test/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../test/source
incdirs := $(incdirs) $(demo_dir)/../test/include $(demo_dir)/../test/source
endif

#Check if the test source file is already included
TEST_DIR := $(findstring app_ble/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../app_ble/source
incdirs := $(incdirs) $(demo_dir)/../app_ble/include $(demo_dir)/../app_ble/source
endif

TEST_FILE := $(findstring app_ble.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) \
	app_ble.c \
    app_ble_client.c \
    app_ble_server.c \
    app_ble_client_xml.c \
    app_ble_client_db.c
endif

TEST_FILE := $(findstring test_vse.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) test_vse.c
endif

else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/app_ble_tvselect/include
endif
######################################################################

###################### enable BLE wifi ##################################
ifeq ($(BtApp_BLE_Wifi_Enable),true)
GLOBAL_DEFINE += -DBTAPP_BLE_WIFI_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/app_ble_wifi
include $(demo_dir)/demo_build/def/*.def

#Check if the test source file is already included
TEST_DIR := $(findstring app_ble/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../app_ble/source
incdirs := $(incdirs) $(demo_dir)/../app_ble/include $(demo_dir)/../app_ble/source
endif

TEST_FILE := $(findstring app_ble.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) \
	app_ble.c \
    app_ble_client.c \
    app_ble_server.c \
    app_ble_client_xml.c \
    app_ble_client_db.c
endif

else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/app_ble_wifi/include
endif
######################################################################
ifeq ($(BtApp_AV_SW_Enable),true)
GLOBAL_DEFINE += -DBTAPP_AV_SW_ENABLE
demo_dir := $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/av_sw

# add ENABLE_ALSA=TRUE at the command line to enable
ENABLE_ALSA ?= FALSE
ifeq ($(strip $(ENABLE_ALSA)), TRUE)
  GLOBAL_DEFINE += -DPCM_ALSA
  LINKLIBS += -lasound
endif

# AV Broadcast
#GLOBAL_DEFINE += -DAPP_AV_BCST_INCLUDED

include $(demo_dir)/demo_build/def/*.def

#Check if the test source file is already included
TEST_DIR := $(findstring av/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../av/source
incdirs := $(incdirs) $(demo_dir)/../av/include $(demo_dir)/../av/source
endif

#Check if the test source file is already included
TEST_DIR := $(findstring hfp_ag/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../hfp_ag/source
incdirs := $(incdirs) $(demo_dir)/../hfp_ag/include $(demo_dir)/../hfp_ag/source
endif

#Check if the test source file is already included
TEST_DIR := $(findstring hfp_client/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../hfp_client/source
incdirs := $(incdirs) $(demo_dir)/../hfp_client/include $(demo_dir)/../hfp_client/source
endif

#Check if the test source file is already included
TEST_DIR := $(findstring a2dp/source,$(srcdirs))
ifeq ($(strip $(TEST_DIR)),)
srcdirs := $(srcdirs) $(demo_dir)/../a2dp/source
incdirs := $(incdirs) $(demo_dir)/../a2dp/include $(demo_dir)/../a2dp/source
endif

TEST_FILE := $(findstring av.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) \
    av.c \
    av_bcst.c
endif

TEST_FILE := $(findstring a2dp.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) \
    a2dp.c
endif

TEST_FILE := $(findstring hfp_client.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) \
    hfp_client.c
endif

TEST_FILE := $(findstring hfp_ag.c,$(appsources))
ifeq ($(strip $(TEST_FILE)),)
appsources := $(appsources) \
    hfp_ag.c
endif


else
incdirs += $(RUBIKPI_BTAPP_SRCPATH)/$(os_name)/av_sw/include
endif

# When not specified, search the files in the source directories
vpath %.c $(srcdirs)
vpath %.s $(srcdirs)


#######################################
#
# Objects
#
#######################################
c_objs := $(patsubst %.c,$(obj_dir)/%.o,$(appsources))
objs := $(patsubst %.s,$(obj_dir)/%.o,$(c_objs))

objlist := $(objs)

build_target := $(build_dir)/$(app_name)
#######################################
#
# Targets
#
#######################################

.PHONY: all clean

all: $(build_target)
	@echo copy application to $(exe_dir)
	-@cp $(build_target) $(exe_dir)/
	-@cp $(cfgdir)/*.conf $(exe_dir)/
	@echo Done building "$(app_name)"


%.s:%.S

$(build_dir):
	@echo Creating application directory '$(build_dir)'.
	-@mkdir -p $(build_dir)


$(obj_dir):
	@echo Creating object directory '$(obj_dir)'.
	-@mkdir -p $(obj_dir)

$(obj_dir)/%.o: %.c
	@echo Compiling [$(CC)] $<
	$(CC) -c -MD $(CCFLAGS) $(GLOBAL_DEFINE) $(TARGET_DEF) $(CCINC) -o $@ $<

# include the dependencies (if they exist)
-include $(objlist:.o=.d)

$(build_target): $(build_dir) $(obj_dir) $(objlist) $(bsalib)
ifneq ($(strip $(bsalib)),)
	@echo Linking application $@ with $(notdir $(bsalib))
	$(LINK) $(LINKFLAGS) -L$(bsalib) $(TARGET_LINK_FLAGS) -o $@ $(objlist) -lbsa $(LINKLIBS)
else
	@echo Linking application $@
	@$(LINK) $(LINKFLAGS) $(TARGET_LINK_FLAGS) -o $@ $(objlist) $(LINKLIBS)
endif

clean:
	@echo Cleaning up : $(obj_dir) $(build_dir)
	-@rm -rf $(obj_dir) $(build_dir)
	@echo Finished cleaning up bt_main_demo


