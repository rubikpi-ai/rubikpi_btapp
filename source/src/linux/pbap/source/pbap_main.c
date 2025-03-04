/*****************************************************************************
 **
 **  Name:           app_pbs_main.c
 **
 **  Description:    Bluetooth PBAP application menu for BSA
 **
 **  Copyright (c) 2014, Broadcom Corp., All Rights Reserved.
 **  Broadcom Bluetooth Core. Proprietary and confidential.
 **
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "gki.h"
#include "uipc.h"
#include "bsa_api.h"
#include "app_xml_utils.h"
#include "app_disc.h"
#include "app_utils.h"
#include "app_mgt.h"
#include "app_xml_param.h"
#include "menu.h"
#include "pbaps.h"
#include "pbapc.h"

/*
 * Local Variables
 */
static tBSA_PBC_FEA_MASK   peer_features;
/*
 * Defines
 */
enum
{
    //pbap server menu
    APP_PBS_MENU_ENABLE = 2,
    APP_PBS_MENU_DISABLE,
    APP_PBS_ENABLE_ACCESS,
    APP_PBS_DISABLE_ACCESS,
    //pbap client menu
    APP_PBC_MENU_ENABLE,
    APP_PBC_MENU_DISABLE,
    APP_PBC_MENU_OPEN,
    APP_PBC_MENU_GET_VCARD,
    APP_PBC_MENU_GET_LISTVCARDS,
    APP_PBC_MENU_GET_PHONEBOOK,
    APP_PBC_MENU_SET_CHDIR,
    APP_PBC_MENU_CLOSE,
    APP_PBC_MENU_ABORT,
    APP_PBC_MENU_DISC

};

/*
 * Global Variables
 */

/*******************************************************************************
 **
 ** Function         pbap_menu_display
 **
 ** Description      This is the main menu
 **
 ** Parameters
 **
 ** Returns          void
 **
 *******************************************************************************/
void pbap_menu_display(void)
{
    printf("Bluetooth PhoneBook Access Profile (PBAP) menu:\n");
    printf("pbap server:\n");
    printf("    %d => Server Enable\n", APP_PBS_MENU_ENABLE);
    printf("    %d => Server Disable\n", APP_PBS_MENU_DISABLE);
    printf("    %d => Enable access\n", APP_PBS_ENABLE_ACCESS);
    printf("    %d => Disable access\n",APP_PBS_DISABLE_ACCESS);
    printf("pbap client:\n");
    printf("    %d => Client Enable\n", APP_PBC_MENU_ENABLE);
    printf("    %d => Client Disable\n", APP_PBC_MENU_DISABLE);
    printf("    %d => Open connection\n", APP_PBC_MENU_OPEN);
    printf("    %d => Get vcard\n", APP_PBC_MENU_GET_VCARD);
    printf("    %d => Get list of vcards\n", APP_PBC_MENU_GET_LISTVCARDS);
    printf("    %d => Get phonebook\n", APP_PBC_MENU_GET_PHONEBOOK);
    printf("    %d => Set phonebook change directory\n", APP_PBC_MENU_SET_CHDIR);
    printf("    %d => Close connection\n", APP_PBC_MENU_CLOSE);
    printf("    %d => Abort operation\n", APP_PBC_MENU_ABORT);
    printf("    %d => Disconnect\n", APP_PBC_MENU_DISC);
    printf("\n");
    printf("    %d => Exit\n", MENU_QUIT);
}
/*******************************************************************************
**
** Function         app_pbc_display_vcard_properties
**
** Description      Display vCard property masks
**
** Parameters
**
** Returns          void
**
*******************************************************************************/
static void app_pbc_display_vcard_properties(void)
{
    printf("    VERSION (vCard Version)                     0x%08x\n", BSA_PBC_FILTER_VERSION);
    printf("    FN (Formatted Name)                         0x%08x\n", BSA_PBC_FILTER_FN);
    printf("    N (Structured Presentation of Name)         0x%08x\n", BSA_PBC_FILTER_N);
    printf("    PHOTO (Associated Image or Photo)           0x%08x\n", BSA_PBC_FILTER_PHOTO);
    printf("    BDAY (Birthday)                             0x%08x\n", BSA_PBC_FILTER_BDAY);
    printf("    ADR (Delivery Address)                      0x%08x\n", BSA_PBC_FILTER_ADR);
    printf("    LABEL (Delivery)                            0x%08x\n", BSA_PBC_FILTER_LABEL);
    printf("    TEL (Telephone Number)                      0x%08x\n", BSA_PBC_FILTER_TEL);
    printf("    EMAIL (Electronic Mail Address)             0x%08x\n", BSA_PBC_FILTER_EMAIL);
    printf("    MAILER (Electronic Mail)                    0x%08x\n", BSA_PBC_FILTER_MAILER);
    printf("    TZ (Time Zone)                              0x%08x\n", BSA_PBC_FILTER_TZ);
    printf("    GEO (Geographic Position)                   0x%08x\n", BSA_PBC_FILTER_GEO);
    printf("    TITLE (Job)                                 0x%08x\n", BSA_PBC_FILTER_TITLE);
    printf("    ROLE (Role within the Organization)         0x%08x\n", BSA_PBC_FILTER_ROLE);
    printf("    LOGO (Organization Logo)                    0x%08x\n", BSA_PBC_FILTER_LOGO);
    printf("    AGENT (vCard of Person Representing)        0x%08x\n", BSA_PBC_FILTER_AGENT);
    printf("    ORG (Name of Organization)                  0x%08x\n", BSA_PBC_FILTER_ORG);
    printf("    NOTE (Comments)                             0x%08x\n", BSA_PBC_FILTER_NOTE);
    printf("    REV (Revision)                              0x%08x\n", BSA_PBC_FILTER_REV);
    printf("    SOUND (Pronunciation of Name)               0x%08x\n", BSA_PBC_FILTER_SOUND);
    printf("    URL (Uniform Resource Locator)              0x%08x\n", BSA_PBC_FILTER_URL);
    printf("    UID (Unique ID)                             0x%08x\n", BSA_PBC_FILTER_UID);
    printf("    KEY (Public Encryption Key)                 0x%08x\n", BSA_PBC_FILTER_KEY);
    printf("    NICKNAME (Nickname)                         0x%08x\n", BSA_PBC_FILTER_NICKNAME);
    printf("    CATEGORIES (Categories)                     0x%08x\n", BSA_PBC_FILTER_CATEGORIES);
    printf("    PROID (Product ID)                          0x%08x\n", BSA_PBC_FILTER_PROID);
    printf("    CLASS (Class information)                   0x%08x\n", BSA_PBC_FILTER_CLASS);
    printf("    SORT-STRING (String used for sorting operation) 0x%08x\n", BSA_PBC_FILTER_SORT_STRING);
    printf("    X-IRMC-CALL-DATETIME (Time stamp)           0x%08x\n", BSA_PBC_FILTER_CALL_DATETIME);
    printf("    X-BT-SPEEDDIALKEY (Speed-dial shortcut)     0x%08x\n", BSA_PBC_FILTER_X_BT_SPEEDDIALKEY);
    printf("    X-BT-UCI (Uniform Caller Identifier)        0x%08x\n", BSA_PBC_FILTER_X_BT_UCI);
    printf("    X-BT-UID (Bluetooth Contact Unique Identifier)  0x%08x\n", BSA_PBC_FILTER_X_BT_UID);
}


/*******************************************************************************
**
** Function         app_pbc_evt_cback
**
** Description      Example of PBC callback function to handle events related to PBC
**
** Parameters
**
** Returns          void
**
*******************************************************************************/
static void app_pbc_evt_cback(tBSA_PBC_EVT event, tBSA_PBC_MSG *p_data)
{
    switch (event)
    {
    case BSA_PBC_OPEN_EVT: /* Connection Open */
        if(p_data->open.status == BSA_SUCCESS)
        {
            peer_features = p_data->open.peer_features;
        }
        break;

    default:
        break;
    }
}

/*******************************************************************************
**
** Function         app_pbc_menu_open
**
** Description      Example of function to open up a connection to peer
**
** Parameters
**
** Returns          void
**
*******************************************************************************/
static tBSA_STATUS app_pbc_menu_open(void)
{
    int device_index;
    BD_ADDR bda;

    printf("Bluetooth PBC menu:\n");
    printf("    0 Device from XML database (already paired)\n");
    printf("    1 Device found in last discovery\n");
    device_index = app_get_choice("Select source");
    switch (device_index)
    {
    case 0 :
        /* Devices from XML database */
        /* Read the Remote device xml file to have a fresh view */
        app_read_xml_remote_devices();
        app_xml_display_devices(app_xml_remote_devices_db,
            APP_NUM_ELEMENTS(app_xml_remote_devices_db));
        device_index = app_get_choice("Select device");
        if ((device_index >= APP_NUM_ELEMENTS(app_xml_remote_devices_db)) || (device_index < 0))
        {
            printf("Wrong Remote device index\n");
            return BSA_SUCCESS;
        }

        if (app_xml_remote_devices_db[device_index].in_use == FALSE)
        {
            printf("Wrong Remote device index\n");
            return BSA_SUCCESS;
        }
        bdcpy(bda, app_xml_remote_devices_db[device_index].bd_addr);
        break;
    case 1 :
        /* Devices from Discovery */
        app_disc_display_devices();
        device_index = app_get_choice("Select device");
        if ((device_index >= APP_DISC_NB_DEVICES) || (device_index < 0))
        {
            printf("Wrong Remote device index\n");
            return BSA_SUCCESS;
        }
        if (app_discovery_cb.devs[device_index].in_use == FALSE)
        {
            printf("Wrong Remote device index\n");
            return BSA_SUCCESS;
        }
        bdcpy(bda, app_discovery_cb.devs[device_index].device.bd_addr);
        break;
    default:
        printf("Wrong selection !!:\n");
        return BSA_SUCCESS;
    }

    return app_pbc_open(bda);
}

/*******************************************************************************
**
** Function         app_pbc_menu_get_vcard
**
** Description      Example of function to perform a get VCard operation
**
** Parameters
**
** Returns          void
**
*******************************************************************************/
static tBSA_STATUS app_pbc_menu_get_vcard()
{
    char file_name[50] = {0};
    int file_len = 0;

    file_len = app_get_string("Enter filename ", file_name, sizeof(file_name));
    if (file_len < 0)
    {
        APP_ERROR0("app_get_string failed");
        return -1;
    }

    return app_pbc_get_vcard(file_name);
}

/*******************************************************************************
**
** Function         app_pbc_menu_get_list_vcards
**
** Description      Example of function to perform a GET - List VCards operation
**
** Parameters
**
** Returns          void
**
*******************************************************************************/
static tBSA_STATUS app_pbc_menu_get_list_vcards()
{
    UINT16 max_list_count = 65535;
    tBSA_PBC_ORDER order =  BSA_PBC_ORDER_INDEXED;
    tBSA_PBC_ATTR attr = BSA_PBC_ATTR_NAME;
    BOOLEAN is_reset_missed_calls = FALSE;
    tBSA_PBC_FILTER_MASK selector = BSA_PBC_FILTER_ALL;
    tBSA_PBC_OP selector_op = BSA_PBC_OP_OR;

    int dir_len, search_len;

    char string_dir[20] = "telecom";
    char searchvalue[20] = "";

    dir_len = app_get_string("Enter directory name", string_dir, sizeof(string_dir));
    if (dir_len < 0)
    {
        APP_ERROR0("app_get_string failed");
        return -1;
    }

    search_len = app_get_string("Enter search value", searchvalue, sizeof(searchvalue));
    if (search_len < 0)
    {
        APP_ERROR0("app_get_string failed");
        return -1;
    }

    if (peer_features & BSA_PBC_FEA_ENH_MISSED_CALLS)
    {
        APP_INFO0("Reset New Missed Calls?");
        APP_INFO0("    0 No");
        APP_INFO0("    1 Yes");
        is_reset_missed_calls = app_get_choice("Please select") == 0 ? FALSE : TRUE;
    }

    if (peer_features & BSA_PBC_FEA_VCARD_SELECTING)
    {
        APP_INFO0("List vCards with selected fields:");
        app_pbc_display_vcard_properties();
        selector = app_get_choice("Please enter selected fields (0 for all fields)");
        APP_INFO0("List vCards contain");
        APP_INFO0("    0 Any of selected fields");
        APP_INFO0("    1 All of selected fields");
        selector_op = app_get_choice("Please select");
    }

    return app_pbc_get_list_vcards(string_dir, order, attr, searchvalue, max_list_count,
        is_reset_missed_calls, selector, selector_op);
}

/*******************************************************************************
**
** Function         app_pbc_menu_get_phonebook
**
** Description      Example of function to perform a get phonebook operation
**
** Parameters
**
** Returns          void
**
*******************************************************************************/
static tBSA_STATUS app_pbc_menu_get_phonebook()
{
    BOOLEAN is_reset_missed_calls = FALSE;
    tBSA_PBC_FILTER_MASK selector = BSA_PBC_FILTER_ALL;
    tBSA_PBC_OP selector_op = BSA_PBC_OP_OR;

    char file_name[50] = {0};
    int file_len = 0;

    file_len = app_get_string("Enter filename like (telecom/pb.vcf)", file_name, sizeof(file_name));
    if (file_len < 0)
    {
        APP_ERROR0("app_get_string failed");
        return -1;
    }

    if (peer_features & BSA_PBC_FEA_ENH_MISSED_CALLS)
    {
        APP_INFO0("Reset New Missed Calls?");
        APP_INFO0("    0 No");
        APP_INFO0("    1 Yes");
        is_reset_missed_calls = app_get_choice("Please select") == 0 ? FALSE : TRUE;
    }

    if (peer_features & BSA_PBC_FEA_VCARD_SELECTING)
    {
        APP_INFO0("Get vCards with selected fields:");
        app_pbc_display_vcard_properties();
        selector = app_get_choice("Please enter selected fields (0 for all fields)");
        APP_INFO0("Get vCards contain");
        APP_INFO0("    0 Any of selected fields");
        APP_INFO0("    1 All of selected fields");
        selector_op = app_get_choice("Please select");
    }

    return app_pbc_get_phonebook(file_name, is_reset_missed_calls, selector, selector_op);
}

/*******************************************************************************
**
** Function         app_pbc_menu_set_chdir
**
** Description      Example of function to perform a set current folder operation
**
** Parameters
**
** Returns          void
**
*******************************************************************************/
static tBSA_STATUS app_pbc_menu_set_chdir()
{
    char string_dir[20] = {0};
    int dir_len;

    dir_len = app_get_string("Enter directory name", string_dir, sizeof(string_dir));
    if (dir_len <= 0)
    {
        APP_ERROR0("No valid directory name entered!");
        return -1;
    }

    return app_pbc_set_chdir(string_dir);
}

/*******************************************************************************
 **
 ** Function         app_pbs_mgt_callback
 **
 ** Description      This callback function is called in case of server
 **                  disconnection (e.g. server crashes)
 **
 ** Parameters
 **
 ** Returns          void
 **
 *******************************************************************************/
static BOOLEAN app_pbs_mgt_callback(tBSA_MGT_EVT event, tBSA_MGT_MSG *p_data)
{
    switch(event)
    {
    case BSA_MGT_DISCONNECT_EVT:
        APP_DEBUG1("BSA_MGT_DISCONNECT_EVT reason:%d", p_data->disconnect.reason);
        /* Connection with the Server lost => Just exit the application */
        exit(-1);
        break;

    default:
        break;
    }
    return FALSE;
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
int pbap_menu_handle(void)
{
    tBSA_STATUS status;
    int choice;



    do
    {

        choice = app_get_choice("Select action");

        switch (choice)
        {
            case MENU_QUIT:
                return -1;
            case MAIN_MENU:
                APP_INFO0("Back to main menu...");
                return 0;
            case HELP_MENU:
                pbap_menu_display();
                break;
            case APP_PBS_MENU_ENABLE:
                /* Example of function to start PBS application */
                status = app_start_pbs();
                if (status != BSA_SUCCESS)
                {
                    printf("Unable to start PBS\n");
                    continue;
                }

                break;
            case APP_PBS_MENU_DISABLE:
                /* Example of function to stop PBS application */
                app_stop_pbs();
                break;
            case APP_PBS_ENABLE_ACCESS:
                printf("enable access");
                pbap_access_flag = BSA_PBS_ACCESS_ALLOW;
                break;
            case APP_PBS_DISABLE_ACCESS:
                printf("disable access");
                pbap_access_flag = BSA_PBS_ACCESS_FORBID;
                break;
            case APP_PBC_MENU_ENABLE:
                /* Example of function to start PBC application */
                status = app_pbc_enable(app_pbc_evt_cback);
                if (status != BSA_SUCCESS)
                {
                    fprintf(stderr, "main: Unable to start PBC\n");
                    app_mgt_close();
                    continue;
                }

                break;
            case APP_PBC_MENU_DISABLE:
                /* example to stop PBC service */
                app_pbc_disable();
                break;
            case APP_PBC_MENU_OPEN:
                app_pbc_menu_open();
                break;

            case APP_PBC_MENU_GET_VCARD:
                app_pbc_menu_get_vcard();
                break;

            case APP_PBC_MENU_GET_LISTVCARDS:
                app_pbc_menu_get_list_vcards();
                break;

            case APP_PBC_MENU_GET_PHONEBOOK:
                app_pbc_menu_get_phonebook();
                break;

            case APP_PBC_MENU_SET_CHDIR:
                app_pbc_menu_set_chdir();
                break;

            case APP_PBC_MENU_CLOSE:
                app_pbc_close();
                break;

            case APP_PBC_MENU_ABORT:
                app_pbc_abort();
                break;

            case APP_PBC_MENU_DISC:
                /* Example to perform Device discovery (in blocking mode) */
                app_disc_start_regular(NULL);
                break;

            default:
                printf("%s: Unknown choice:%d\n",__func__, choice);
                pbap_menu_display();
                break;
        }
    }
    while (choice != MENU_QUIT); /* While user don't exit application */


    return 0;
}
