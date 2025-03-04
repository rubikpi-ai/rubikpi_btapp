/*****************************************************************************
**
**  Name:           gap.c
**
**  Description:    Bluetooth Manager menu application
**
**  Copyright (c) 2010-2014, Broadcom Corp., All Rights Reserved.
**  Broadcom Bluetooth Core. Proprietary and confidential.
**
*****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>

#include "gki.h"
#include "uipc.h"
#include "bsa_api.h"
#include "app_xml_utils.h"
#include "app_disc.h"
#include "app_utils.h"
#include "app_dm.h"
#include "app_services.h"
#include "app_mgt.h"
#include "menu.h"
#include "main.h"

#define BTAPP_VERSION "1.0.0"

int g_MGR_Init = 0;

#define RUBIKPI_BTAPP_CONFIG_FILE "/usr/src/rubikpi-btapp/rubikpi_btapp.conf"
#define BUFFER_SIZE 1024

int main_menu_item_enable_init(void)
{
    int max_main_items = NO_OF_COMMANDS(MainMenu);
    char buffer[BUFFER_SIZE];
    char *p_equal = NULL;
    char config_value[10] = "";
    int en_config = 0;

    FILE *file = fopen(RUBIKPI_BTAPP_CONFIG_FILE, "r");
    if (file == NULL) {
        APP_INFO1("Failed to open config file(%s),main menu item enable init failed",RUBIKPI_BTAPP_CONFIG_FILE);
        return 1;
    }

    while (fgets(buffer, BUFFER_SIZE, file)) {
        // Remove newline character at the end if present
        buffer[strcspn(buffer, "\n")] = 0;

        p_equal = strchr(buffer, '=');
        if (p_equal == NULL) 
        {
            continue;
        }

        // Check configuration items en status
        strcpy(config_value, p_equal + 2);
        if(strncmp(config_value, "true",4) == 0)
        {
            en_config = 1;
        }
        else if(strncmp(config_value, "false",5) == 0)
        {
            en_config = 0;
        }
        else 
        {
            continue;
        }

        // main menu item en status init
        for (int i = 0; i < max_main_items; i++)
        {
            if (strncmp(MainMenu[i].en_cfg_item, buffer,strlen(MainMenu[i].en_cfg_item)) == 0)
            {
                MainMenu[i].opt_en = en_config;
                break;
            }
        }
    }

    fclose(file);
    return 0;
}

int main_menu_item_enable_check(int menu_type)
{
    int max_main_items = NO_OF_COMMANDS(MainMenu);

    for (int i = 0; i < max_main_items; i++)
    {
        if (MainMenu[i].opt_id == menu_type)
        {
            return MainMenu[i].opt_en;
        }
    }

    return 0;
}
/*******************************************************************************
 **
 ** Function         btapp_mgt_callback
 **
 ** Description      This callback function is called in case of server
 **                  disconnection (e.g. server crashes)
 **
 ** Parameters
 **
 ** Returns          void
 **
 *******************************************************************************/
static BOOLEAN btapp_mgt_callback(tBSA_MGT_EVT event, tBSA_MGT_MSG *p_data)
{
    switch(event)
    {
    case BSA_MGT_STATUS_EVT:
        APP_DEBUG0("BSA_MGT_STATUS_EVT");
        if (p_data->status.enable)
        {
            APP_DEBUG0("Bluetooth restarted => re-initialize the application");
#ifdef BTAPP_MANAGER_ENABLE
            app_mgr_config();
#endif
        }
        break;

    case BSA_MGT_DISCONNECT_EVT:
        APP_DEBUG1("BSA_MGT_DISCONNECT_EVT reason:%d", p_data->disconnect.reason);
        exit(-1);
        break;

    default:
        break;
    }
    return FALSE;
}

static void DisplayMenu(int menu_type) {

    sUser_Menu_List *menu = NULL;
    int index = 0, num_cmds = 0, main_num_cmds = 0;
    char * p_menu_name = NULL;
    int detail_info_flag = 0;

    switch(menu_type) {
        case MAIN_MENU:
            menu = &MainMenu[0];
            p_menu_name = "Main Menu";
            num_cmds  = NO_OF_COMMANDS(MainMenu);
            break;
        case HELP_MENU:
            menu = &MainMenu[0];
            p_menu_name = "Main Menu";
            num_cmds  = NO_OF_COMMANDS(MainMenu);
            detail_info_flag = 1;
            break;
        case MENU_QUIT:
            return;
        default:
            menu = &Basic_Menu[0];
            main_num_cmds  = NO_OF_COMMANDS(MainMenu);
            for(index = 0; index < main_num_cmds; index++)
            {
                if(MainMenu[index].opt_id == menu_type)
                {
                    p_menu_name = MainMenu[index].opt_name;
                    if(MainMenu[index].opt_en == 0)
                    {
                        fprintf (stdout, "%s menu is not enabled %s\n",p_menu_name,MainMenu[index].en_cfg_item);
                        return;
                    }
                    break;
                }
            }
            num_cmds  = NO_OF_COMMANDS(Basic_Menu);
            break;
    }
    fprintf (stdout, " \n*****************%s menu*******************\n",p_menu_name);
    for (index = 0; index < num_cmds; index++)
    {
        if(detail_info_flag == 0)
            fprintf (stdout, "\t %d ==>%s\n",  menu[index].opt_id , menu[index].opt_name);
        else
            fprintf (stdout, "\t %d ==>%s           %s \n",  menu[index].opt_id , menu[index].opt_name,menu[index].opt_help);
    }
    fprintf (stdout, " ****************************************************\n");

    return;
}

/*******************************************************************************
 **
 ** Function         main
 **
 ** Description      This is the main function
 **
 ** Parameters
 **
 ** Returns          void
 **
 *******************************************************************************/
int main(int argc, char **argv)
{
    int choice =1;
    int ret;
    if(argc > 1)
    {
        if(strcmp(argv[1],"-v") == 0)
        {
            APP_INFO1("Version:%s", BTAPP_VERSION);
        }
        return 0;
    }

    ret = main_menu_item_enable_init();
    if(ret != 0)
    {
        APP_ERROR0("main_menu_item_enable_init failed");
        return -1;
    }

    //Initialize communication with the server
    app_mgt_init();
    if (app_mgt_open(BTAPP_UIPC_PATH, btapp_mgt_callback) < 0)
    {
        APP_ERROR0("Unable to connect to server");
        return -1;
    }
    g_MGR_Init = 1;

    while(choice != MENU_QUIT)
    {
        DisplayMenu(MAIN_MENU);
        choice = app_get_choice("Select action");
        DisplayMenu(choice);

        switch (choice)
        {
            case MANAGER_MENU:
                manager_menu_display();
                ret = manager_menu_handle();
                if(ret == -1)
                    goto exit;
                break;
            case OPP_MENU:
                opp_menu_display();
                ret = opp_menu_handle();
                if(ret == -1)
                    goto exit;
                break;
            case PAN_MENU:
                pan_menu_display();
                ret = pan_menu_handle();
                if(ret == -1)
                    goto exit;
                app_mgt_custom_cback_update(btapp_mgt_callback);
                break;
            case HFP_AG_MENU:
                hfp_ag_menu_display();
                ret = hfp_ag_menu_handle();
                if(ret == -1)
                    goto exit;
                app_mgt_custom_cback_update(btapp_mgt_callback);
                break;
            case HFP_CLIENT_MENU:
                hfp_client_menu_display();
                ret = hfp_client_menu_handle();
                if(ret == -1)
                    goto exit;
                app_mgt_custom_cback_update(btapp_mgt_callback);
                break;
            case A2DP_MENU:
                a2dp_menu_display();
                ret = a2dp_menu_handle();
                if(ret == -1)
                    goto exit;
                app_mgt_custom_cback_update(btapp_mgt_callback);
                break;
            case PBAP_MENU:
                pbap_menu_display();
                ret = pbap_menu_handle();
                if(ret == -1)
                    goto exit;
                break;
            case SAP_MENU:
                sap_menu_display();
                ret = sap_menu_handle();
                if(ret == -1)
                    goto exit;
                break;
            case AV_SW_MENU:
                av_sw_menu_display();
                ret = av_sw_menu_handle();
                if(ret == -1)
                    goto exit;
                app_mgt_custom_cback_update(btapp_mgt_callback);
                break;
            case AV_MENU:
                av_menu_display();
                ret = av_menu_handle();
                if(ret == -1)
                    goto exit;
                app_mgt_custom_cback_update(btapp_mgt_callback);
                break;
            case DATA_GW_MENU:
                data_gw_menu_display();
                ret = data_gw_menu_handle();
                if(ret == -1)
                    goto exit;
                app_mgt_custom_cback_update(btapp_mgt_callback);
                break;
            case FM_MENU:
                fm_menu_display();
                ret = fm_menu_handle();
                if(ret == -1)
                    goto exit;
                app_mgt_custom_cback_update(btapp_mgt_callback);
                break;
            case FTP_MENU:
                ftp_menu_display();
                ret = ftp_menu_handle();
                if(ret == -1)
                    goto exit;
                break;
            case HID_DEV_MENU:
                hid_dev_menu_display();
                ret = hid_dev_menu_handle();
                if(ret == -1)
                    goto exit;
                app_mgt_custom_cback_update(btapp_mgt_callback);
                break;
            case HID_HOST_MENU:
                hid_host_menu_display();
                ret = hid_host_menu_handle();
                if(ret == -1)
                    goto exit;
                app_mgt_custom_cback_update(btapp_mgt_callback);
                break;
            case HEADLESS_MENU:
                headless_menu_display();
                ret = headless_menu_handle();
                if(ret == -1)
                    goto exit;
                break;
            case HEALTH_MENU:
                health_menu_display();
                ret = health_menu_handle();
                if(ret == -1)
                    goto exit;
                app_mgt_custom_cback_update(btapp_mgt_callback);
                break;
            case MAP_MENU:
                map_menu_display();
                ret = map_menu_handle();
                if(ret == -1)
                    goto exit;
                app_mgt_custom_cback_update(btapp_mgt_callback);
                break;
            case CTN_MENU:
                ctn_menu_display();
                ret = ctn_menu_handle();
                if(ret == -1)
                    goto exit;
                app_mgt_custom_cback_update(btapp_mgt_callback);
                break;
            case BT3D_MENU:
                dtv_menu_display();
                ret = dtv_menu_handle();
                if(ret == -1)
                    goto exit;
                app_mgt_custom_cback_update(btapp_mgt_callback);
                break;
            case TEST_MENU:
                test_menu_display();
                ret = test_menu_handle();
                if(ret == -1)
                    goto exit;
                break;
            case VSC_MENU:
                vsc_menu_display();
                ret = vsc_menu_handle();
                if(ret == -1)
                    goto exit;
                break;
            case BLE_MENU:
                ble_menu_display();
                ret = ble_menu_handle();
                if(ret == -1)
                    goto exit;
                app_mgt_custom_cback_update(btapp_mgt_callback);
                break;
            case BLE_ANCS_MENU:
                ble_ancs_menu_display();
                ret = ble_ancs_menu_handle();
                if(ret == -1)
                    goto exit;
                app_mgt_custom_cback_update(btapp_mgt_callback);
                break;
            case BLE_CSCC_MENU:
                ble_cscc_menu_display();
                ret = ble_cscc_menu_handle();
                if(ret == -1)
                    goto exit;
                app_mgt_custom_cback_update(btapp_mgt_callback);
                break;
            case BLE_EDDYSTONE_MENU:
                ble_eddystone_menu_display();
                ret = ble_eddystone_menu_handle();
                if(ret == -1)
                    goto exit;
                app_mgt_custom_cback_update(btapp_mgt_callback);
                break;
            case BLE_HRC_MENU:
                ble_hrc_menu_display();
                ret = ble_hrc_menu_handle();
                if(ret == -1)
                    goto exit;
                app_mgt_custom_cback_update(btapp_mgt_callback);
                break;
            case BLE_HTP_MENU:
                ble_htp_menu_display();
                ret = ble_htp_menu_handle();
                if(ret == -1)
                    goto exit;
                app_mgt_custom_cback_update(btapp_mgt_callback);
                break;
            case BLE_PM_MENU:
                ble_pm_menu_display();
                ret = ble_pm_menu_handle();
                if(ret == -1)
                    goto exit;
                app_mgt_custom_cback_update(btapp_mgt_callback);
                break;
            case BLE_RSCC_MENU:
                ble_rscc_menu_display();
                ret = ble_rscc_menu_handle();
                if(ret == -1)
                    goto exit;
                app_mgt_custom_cback_update(btapp_mgt_callback);
                break;
            case BLE_TVSELECT_MENU:
                ble_tvselect_menu_display();
                ret = ble_tvselect_menu_handle();
                if(ret == -1)
                    goto exit;
                app_mgt_custom_cback_update(btapp_mgt_callback);
                break;
            case BLE_WIFI_MENU:
                ble_wifi_menu_display();
                ret = ble_wifi_menu_handle();
                if(ret == -1)
                    goto exit;
                app_mgt_custom_cback_update(btapp_mgt_callback);
                break;
            case HELP_MENU:
                break;
            case MENU_QUIT:
                goto exit;
            default:
                APP_INFO1("Unknown choice:%d", choice);
                break;
        }
    }

exit:
    app_mgt_close();
    APP_INFO0("Application Exiting");
    return 0;
}
