/*****************************************************************************
**
**  Name:           main.h
**
**  Description:    Rubik Pi application
**
**  Copyright (c) 2010-2014, Broadcom Corp., All Rights Reserved.
**  Broadcom Bluetooth Core. Proprietary and confidential.
**
*****************************************************************************/
#ifndef __MAIN_H__
#define __MAIN_H__

// all menu items handle functions
#ifdef BTAPP_MANAGER_ENABLE
#include "manager.h"
#else
void manager_menu_display(void)
{
    return;
}

int manager_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_OPP_ENABLE
#include "opp.h"
#else
void opp_menu_display(void)
{
    return;
}

int opp_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_PAN_ENABLE
#include "pan.h"
#else
void pan_menu_display(void)
{
    return;
}

int pan_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_HFP_AG_ENABLE
#include "hfp_ag.h"
#else
void hfp_ag_menu_display(void)
{
    return;
}

int hfp_ag_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_HFP_CLIENT_ENABLE
#include "hfp_client.h"
#else
void hfp_client_menu_display(void)
{
    return;
}

int hfp_client_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_AV_SW_ENABLE
#include "av_sw.h"
#else
void av_sw_menu_display(void)
{
    return;
}

int av_sw_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_A2DP_ENABLE
#include "a2dp.h"
#else
void a2dp_menu_display(void)
{
    return;
}

int a2dp_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_3D_ENABLE
#include "app_3d.h"
#else
void dtv_menu_display(void)
{
    return;
}

int dtv_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_AV_ENABLE
#include "av.h"
#else
void av_menu_display(void)
{
    return;
}

int av_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_CTN_ENABLE
#include "ctn.h"
#else
void ctn_menu_display(void)
{
    return;
}

int ctn_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_MAP_ENABLE
#include "ctn.h"
#else
void map_menu_display(void)
{
    return;
}

int map_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_DATA_GW_ENABLE
#include "data_gw.h"
#else
void data_gw_menu_display(void)
{
    return;
}

int data_gw_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_FM_ENABLE
#include "fm.h"
#else
void fm_menu_display(void)
{
    return;
}

int fm_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_FTP_ENABLE
#include "ftp.h"
#else
void ftp_menu_display(void)
{
    return;
}

int ftp_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_HEADLESS_ENABLE
#include "headless.h"
#else
void headless_menu_display(void)
{
    return;
}

int headless_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_HEALTH_ENABLE
#include "health.h"
#else
void health_menu_display(void)
{
    return;
}

int health_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_HID_DEV_ENABLE
#include "hid_dev.h"
#else
void hid_dev_menu_display(void)
{
    return;
}

int hid_dev_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_HID_HOST_ENABLE
#include "hid_host.h"
#else
void hid_host_menu_display(void)
{
    return;
}

int hid_host_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_NSA_ENABLE
#include "nsa.h"
#else
void nsa_menu_display(void)
{
    return;
}

int nsa_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_PBAP_ENABLE
#include "pbap.h"
#else
void pbap_menu_display(void)
{
    return;
}

int pbap_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_SAP_ENABLE
#include "sap.h"
#else
void sap_menu_display(void)
{
    return;
}

int sap_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_TEST_ENABLE
#include "test.h"
#else
void test_menu_display(void)
{
    return;
}

int test_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_BLE_ENABLE
#include "app_ble.h"
#else
void ble_menu_display(void)
{
    return;
}

int ble_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_BLE_ANCS_ENABLE
#include "app_ble_ancs.h"
#else
void ble_ancs_menu_display(void)
{
    return;
}

int ble_ancs_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_BLE_BLP_ENABLE
#include "app_ble_blp.h"
#else
void ble_blp_menu_display(void)
{
    return;
}

int ble_blp_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_BLE_CSCC_ENABLE
#include "app_ble_cscc.h"
#else
void ble_cscc_menu_display(void)
{
    return;
}

int ble_cscc_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_BLE_EDDYSTONE_ENABLE
#include "app_ble_eddystone.h"
#else
void ble_eddystone_menu_display(void)
{
    return;
}

int ble_eddystone_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_BLE_HRC_ENABLE
#include "app_ble.h"
#else
void ble_hrc_menu_display(void)
{
    return;
}

int ble_hrc_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_BLE_HTP_ENABLE
#include "app_ble_htp.h"
#else
void ble_htp_menu_display(void)
{
    return;
}

int ble_htp_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_BLE_PM_ENABLE
#include "app_ble_pm.h"
#else
void ble_pm_menu_display(void)
{
    return;
}

int ble_pm_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_BLE_RSCC_ENABLE
#include "app_ble_rscc.h"
#else
void ble_rscc_menu_display(void)
{
    return;
}

int ble_rscc_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_BLE_TVSELECT_ENABLE
#include "app_ble_tvselect.h"
#else
void ble_tvselect_menu_display(void)
{
    return;
}

int ble_tvselect_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_BLE_WIFI_ENABLE
#include "app_ble_wifi.h"
#else
void ble_wifi_menu_display(void)
{
    return;
}

int ble_wifi_menu_handle(void)
{
    return 0;
}
#endif

#ifdef BTAPP_VSC_ENABLE
#include "app_vsc.h"
#else
void vsc_menu_display(void)
{
    return;
}

int vsc_menu_handle(void)
{
    return 0;
}
#endif


/**
 * Maximum command length
 */
#define COMMAND_SIZE        200

/**
 * Macro used to find the total commands number
 */
#define  NO_OF_COMMANDS(x)  (sizeof(x) / sizeof((x)[0]))


/**
 * Argument Count
 */
typedef enum {
    ZERO_PARAM,
    ONE_PARAM,
    TWO_PARAM,
    THREE_PARAM,
    FOUR_PARAM,
    FIVE_PARAM,
    SIX_PARAM,
} eMax_Param_Count;



/**
 * User Menu List structure
 */
typedef struct {
    int opt_en;
    int opt_id;
    const char opt_name[COMMAND_SIZE];
    eMax_Param_Count max_param;
    const char opt_help[COMMAND_SIZE];
    const char en_cfg_item[COMMAND_SIZE];
} sUser_Menu_List;

/* 
 * Main Menu items 
 */
typedef enum {
    //0,1 are reserved for the basic menu
    MANAGER_MENU = 2,
    OPP_MENU,
    A2DP_MENU,
    PAN_MENU,
    PBAP_MENU,
    SAP_MENU,
    HFP_AG_MENU,
    HFP_CLIENT_MENU,
    AV_SW_MENU,
    AV_MENU,
    DATA_GW_MENU,
    FM_MENU,
    FTP_MENU,
    HID_DEV_MENU,
    HID_HOST_MENU,
    HEADLESS_MENU,
    HEALTH_MENU,
    MAP_MENU,
    NSA_MENU,
    CTN_MENU,
    BT3D_MENU,
    TEST_MENU,
    VSC_MENU,
    BLE_MENU,
    BLE_ANCS_MENU,
    BLE_CSCC_MENU,
    BLE_BLP_MENU,
    BLE_EDDYSTONE_MENU,
    BLE_HRC_MENU,
    BLE_HTP_MENU,
    BLE_PM_MENU,
    BLE_RSCC_MENU,
    BLE_TVSELECT_MENU,
    BLE_WIFI_MENU
} eMenu_Type;

//rubikpi_btapp.conf config items
#define BTAPP_MANAGER_ENABLE_CFG  "BtApp_Manager_Enable"
#define BTAPP_OPP_ENABLE_CFG  "BtApp_Opp_Enable"
#define BTAPP_PAN_ENABLE_CFG  "BtApp_Pan_Enable"
#define BTAPP_HFP_AG_ENABLE_CFG  "BtApp_HFP_AG_Enable"
#define BTAPP_HFP_CLIENT_ENABLE_CFG  "BtApp_HFP_Client_Enable"
#define BTAPP_DATA_GW_ENABLE_CFG  "BtApp_Data_GW_Enable"
#define BTAPP_FM_ENABLE_CFG  "BtApp_FM_Enable"
#define BTAPP_FTP_ENABLE_CFG  "BtApp_Ftp_Enable"
#define BTAPP_SAP_ENABLE_CFG  "BtApp_Sap_Enable"
#define BTAPP_PBAP_ENABLE_CFG  "BtApp_Pbap_Enable"
#define BTAPP_HID_DEV_ENABLE_CFG  "BtApp_HID_Dev_Enable"
#define BTAPP_HID_HOST_ENABLE_CFG  "BtApp_HID_Host_Enable"
#define BTAPP_NSA_ENABLE_CFG  "BtApp_Nsa_Enable"
#define BTAPP_MAP_ENABLE_CFG  "BtApp_Map_Enable"
#define BTAPP_HEALTH_ENABLE_CFG  "BtApp_Health_Enable"
#define BTAPP_CTN_ENABLE_CFG  "BtApp_CTN_Enable"
#define BTAPP_HEADLESS_ENABLE_CFG  "BtApp_Headless_Enable"
#define BTAPP_TESTMODE_ENABLE_CFG  "BtApp_TestMode_Enable"
#define BTAPP_3D_ENABLE_CFG  "BtApp_3D_Enable"
#define BTAPP_A2DP_ENABLE_CFG  "BtApp_A2dp_Enable"
#define BTAPP_AV_ENABLE_CFG  "BtApp_AV_Enable"
#define BTAPP_AV_SW_ENABLE_CFG  "BtApp_AV_SW_Enable"
#define BTAPP_VSC_ENABLE_CFG  "BtApp_Vsc_Enable"
#define BTAPP_BLE_ENABLE_CFG  "BtApp_BLE_Enable"
#define BTAPP_BLE_ANCS_ENABLE_CFG  "BtApp_BLE_Ancs_Enable"
#define BTAPP_BLE_BLP_ENABLE_CFG  "BtApp_BLE_Blp_Enable"
#define BTAPP_BLE_CSCC_ENABLE_CFG  "BtApp_BLE_Cscc_Enable"
#define BTAPP_BLE_EDDYSTONE_ENABLE_CFG  "BtApp_BLE_Eddystone_Enable"
#define BTAPP_BLE_HRC_ENABLE_CFG  "BtApp_BLE_Hrc_Enable"
#define BTAPP_BLE_HTP_ENABLE_CFG  "BtApp_BLE_Htp_Enable"
#define BTAPP_BLE_PM_ENABLE_CFG  "BtApp_BLE_PM_Enable"
#define BTAPP_BLE_RSCC_ENABLE_CFG  "BtApp_BLE_Rscc_Enable"
#define BTAPP_BLE_TVSELECT_ENABLE_CFG  "BtApp_BLE_TVselect_Enable"
#define BTAPP_BLE_WIFI_ENABLE_CFG  "BtApp_BLE_Wifi_Enable"

/**
 * list of supported commands for Main Menu
 */
sUser_Menu_List MainMenu[] = {
    {1,MAIN_MENU,                        "main",         ZERO_PARAM,   "main menu","main menu"},
    {0,MANAGER_MENU,              "manager",         ZERO_PARAM,   "manager menu",BTAPP_MANAGER_ENABLE_CFG},
    {0,OPP_MENU,                          "opp",         ZERO_PARAM,   "opp(Object Push Profile) menu",BTAPP_OPP_ENABLE_CFG},
    {0,A2DP_MENU,                        "a2dp",         ZERO_PARAM,   "a2dp(Advanced Audio Distribution Profile) menu",BTAPP_A2DP_ENABLE_CFG},
    {0,PAN_MENU,                           "pan",         ZERO_PARAM,   "pan(Personal Area Network) menu",BTAPP_PAN_ENABLE_CFG},
    {0,PBAP_MENU,             "pbap",         ZERO_PARAM,   "pbap(Phone Book Access Profile) menu",BTAPP_PBAP_ENABLE_CFG},
    {0,SAP_MENU,             "sap",         ZERO_PARAM,   "sap(SIM Access Profile) menu",BTAPP_SAP_ENABLE_CFG},
    {0,HFP_AG_MENU,             "hfp ag",         ZERO_PARAM,   "hfp(Hands-Free Profile) ag role menu",BTAPP_HFP_AG_ENABLE_CFG},
    {0,HFP_CLIENT_MENU,             "hfp client",         ZERO_PARAM,   "hfp(Hands-Free Profile) client role menu",BTAPP_HFP_CLIENT_ENABLE_CFG},
    {0,AV_SW_MENU,             "hfp sw",         ZERO_PARAM,   "av<->hf sw menu",BTAPP_AV_SW_ENABLE_CFG},
    {0,AV_MENU,             "av",         ZERO_PARAM,   "av menu",BTAPP_AV_ENABLE_CFG},
    {0,DATA_GW_MENU,             "data gw",         ZERO_PARAM,   "dg(data gateway) menu",BTAPP_DATA_GW_ENABLE_CFG},
    {0,FM_MENU,             "fm",         ZERO_PARAM,   "fm(Frequency Modulation) menu",BTAPP_FM_ENABLE_CFG},
    {0,FTP_MENU,  "ftp",         ZERO_PARAM,   "ftp(File Transfer Protocol) menu",BTAPP_FTP_ENABLE_CFG},
    {0,HID_DEV_MENU,   "hid dev",         ZERO_PARAM,   "hid(Human Interface Device) device role menu",BTAPP_HID_DEV_ENABLE_CFG},
    {0,HID_HOST_MENU,             "hid host",         ZERO_PARAM,   "hid(Human Interface Device) host role menu",BTAPP_HID_HOST_ENABLE_CFG},
    {0,HEADLESS_MENU, "headless",         ZERO_PARAM,   "headless menu",BTAPP_HEADLESS_ENABLE_CFG},
    {0,HEALTH_MENU,             "health",         ZERO_PARAM,   "health menu",BTAPP_HEALTH_ENABLE_CFG},
    {0,MAP_MENU,             "map",         ZERO_PARAM,   "map(Message Access Profile) menu",BTAPP_MAP_ENABLE_CFG},
    {0,NSA_MENU,             "nsa",         ZERO_PARAM,   "nsa menu",BTAPP_NSA_ENABLE_CFG},
    {0,CTN_MENU,             "ctn",         ZERO_PARAM,   "ctn(Cordless Telephony Profile) menu",BTAPP_CTN_ENABLE_CFG},
    {0,BT3D_MENU,             "3d",         ZERO_PARAM,   "3d TV menu",BTAPP_3D_ENABLE_CFG},
    {0,TEST_MENU,             "test",         ZERO_PARAM,   "test module menu",BTAPP_TESTMODE_ENABLE_CFG},
    {0,VSC_MENU,             "vsc",         ZERO_PARAM,   "vsc menu",BTAPP_VSC_ENABLE_CFG},
    {0,BLE_MENU,             "ble",         ZERO_PARAM,   "ble(Bluetooth Low Energy) menu",BTAPP_BLE_ENABLE_CFG},
    {0,BLE_ANCS_MENU, "ble_ancs",         ZERO_PARAM,   "Apple Notification Center Service menu",BTAPP_BLE_ANCS_ENABLE_CFG},
    {0,BLE_CSCC_MENU, "ble_cscc",         ZERO_PARAM,   "BLE Cycling Speed and Cadence Collector menu",BTAPP_BLE_CSCC_ENABLE_CFG},
    {0,BLE_BLP_MENU,  "ble_blp",         ZERO_PARAM,   "BLE Blood Pressure menu",BTAPP_BLE_BLP_ENABLE_CFG},
    {0,BLE_EDDYSTONE_MENU,    "ble_eddystone",         ZERO_PARAM,   "BLE eddystone advertiser menu",BTAPP_BLE_EDDYSTONE_ENABLE_CFG},
    {0,BLE_HRC_MENU,  "ble_hrc",         ZERO_PARAM,   "BLE Heart Rate Controller menu",BTAPP_BLE_HRC_ENABLE_CFG},
    {0,BLE_HTP_MENU,  "ble_htp",         ZERO_PARAM,   "BLE Health Thermometer Collector menu",BTAPP_BLE_HTP_ENABLE_CFG},
    {0,BLE_PM_MENU,   "ble_pm",         ZERO_PARAM,   "BLE Proximity Monitor menu",BTAPP_BLE_PM_ENABLE_CFG},
    {0,BLE_RSCC_MENU, "ble_rscc",         ZERO_PARAM,   "BLE Running Speed and Cadence Collector menu",BTAPP_BLE_RSCC_ENABLE_CFG},
    {0,BLE_TVSELECT_MENU, "ble_tvselect",         ZERO_PARAM,   "BLE TVSELECT helper menu",BTAPP_BLE_TVSELECT_ENABLE_CFG},
    {0,BLE_WIFI_MENU,     "ble_wifi",         ZERO_PARAM,   "BLE WiFi helper menu",BTAPP_BLE_WIFI_ENABLE_CFG},
    {1,HELP_MENU,            "help",         ZERO_PARAM,   "help menu","help menu"},
    {1,MENU_QUIT,             "quit",             ZERO_PARAM,   "program exit","exit"},
};

/**
 * list of supported commands for Main Menu
 */
sUser_Menu_List Basic_Menu[] = {
    {1,MAIN_MENU,            "main_menu",         ZERO_PARAM,   "return main menu","main_menu"},
    {1,HELP_MENU,            "help_menu",         ZERO_PARAM,   "help_menu","help_menu"},
    {1,MENU_QUIT,             "quit",             ZERO_PARAM,   "quit","quit"},
};





#endif /* __MAIN_H__ */
