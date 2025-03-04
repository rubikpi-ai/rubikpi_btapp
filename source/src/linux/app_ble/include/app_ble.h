/*****************************************************************************
**
**  Name:           app_ble.h
**
**  Description:    Bluetooth BLE include file
**
**  Copyright (c) 2015, Broadcom Corp., All Rights Reserved.
**  Broadcom Bluetooth Core. Proprietary and confidential.
**
*****************************************************************************/
#ifndef APP_BLE_H
#define APP_BLE_H

#include "bsa_api.h"

typedef struct
{
    tBT_UUID       attr_UUID;
    UINT16         service_id;
    UINT16         attr_id;
    UINT8          attr_type;
    UINT8          prop;
    BOOLEAN        is_pri;
    BOOLEAN        wait_flag;
} tAPP_BLE_ATTRIBUTE;

typedef struct
{
    tBT_UUID        service_UUID;
    BOOLEAN         enabled;
    tBSA_BLE_IF     client_if;
    UINT16          conn_id;
    BD_ADDR         server_addr;
    BOOLEAN         write_pending;
    BOOLEAN         read_pending;
    BOOLEAN         congested;
} tAPP_BLE_CLIENT;

typedef struct 
{
    BOOLEAN             enabled;
    BOOLEAN             congested;
    tBSA_BLE_IF         server_if;
    UINT16              conn_id;
    tAPP_BLE_ATTRIBUTE  attr[BSA_BLE_ATTRIBUTE_MAX];
} tAPP_BLE_SERVER;

typedef struct
{
    tAPP_BLE_CLIENT ble_client[BSA_BLE_CLIENT_MAX];
    tAPP_BLE_SERVER ble_server[BSA_BLE_SERVER_MAX];
} tAPP_BLE_CB;

/*
 * Global Variables
 */
extern tAPP_BLE_CB app_ble_cb;


/*******************************************************************************
 **
 ** Function         app_av_display_vendor_commands
 **
 ** Description      This function display the name of vendor dependent command
 **
 ** Returns          void
 **
 *******************************************************************************/
char *app_ble_display_service_name(UINT16 uuid);

/*******************************************************************************
 **
 ** Function        app_ble_init
 **
 ** Description     This is the main init function
 **
 ** Parameters      None
 **
 ** Returns         status: 0 if success / -1 otherwise
 **
 *******************************************************************************/
int app_ble_init(void);

/*******************************************************************************
 **
 ** Function        app_ble_exit
 **
 ** Description     This is the ble exit function
 **
 ** Parameters      None
 **
 ** Returns         status: 0 if success / -1 otherwise
 **
 *******************************************************************************/
int app_ble_exit(void);

/*******************************************************************************
 **
 ** Function        app_ble_start
 **
 ** Description     DTV Start function
 **
 ** Parameters      None
 **
 ** Returns         status: 0 if success / -1 otherwise
 **
 *******************************************************************************/
int app_ble_start(void);


/*******************************************************************************
 **
 ** Function        app_ble_read_phy
 **
 ** Description
 **
 ** Parameters
 **
 ** Returns         status: 0 if success / -1 otherwise
 **
 *******************************************************************************/
int app_ble_read_phy(UINT16 handle);


/*******************************************************************************
 **
 ** Function        app_ble_set_phy
 **
 ** Description
 **
 ** Parameters      None
 **
 ** Returns         status: 0 if success / -1 otherwise
 **
 *******************************************************************************/
int app_ble_set_phy(UINT16 handle, UINT8 tx_phys, UINT8 rx_phys, UINT16 phy_options);


/*******************************************************************************
 **
 ** Function        app_ble_set_default_phy
 **
 ** Description
 **
 ** Parameters      None
 **
 ** Returns         status: 0 if success / -1 otherwise
 **
 *******************************************************************************/
int app_ble_set_default_phy(UINT8 all_phys, UINT8 tx_phys, UINT8 rx_phys);


/*******************************************************************************
 **
 ** Function        app_ble_wake_configure
 **
 ** Description     Configure for Wake on BLE
 **
 ** Parameters      None
 **
 ** Returns         status: 0 if success / -1 otherwise
 **
 *******************************************************************************/
int app_ble_wake_configure(void);
#if defined (APP_BLE_DLE_TEST) /* for test purposes only */
int app_ble_read_default_data_len(void);
int app_ble_write_default_data_len(void);
int app_ble_read_max_data_len(void);
#endif

#ifndef DEMO_MODE
int ble_menu_handle(void);
void ble_menu_display(void);
#endif

#endif
