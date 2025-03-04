/*****************************************************************************
 **
 **  Name:           app_ops_main.c
 **
 **  Description:    Bluetooth Manager application
 **
 **  Copyright (c) 2010-2013, Broadcom Corp., All Rights Reserved.
 **  Broadcom Bluetooth Core. Proprietary and confidential.
 **
 *****************************************************************************/

#include <stdlib.h>
#include <unistd.h>

#include "menu.h"
#include "ops.h"
#include "opc.h"

#include "app_utils.h"
#include "app_disc.h"
#include "app_mgt.h"
#include "app_xml_utils.h"



/* Menu items */
enum
{
    //0,1 are reserved for the basic menu
    OPP_MENU_OPP_SERVER_ENABLE          = 2,
    OPP_MENU_OPP_SERVER_DISABLE         = 3,
    OPP_MENU_OPS_AUTO_ACCEPT,
    OPP_MENU_OPS_DISCONNECT_DEVICE,
    OPP_MENU_OPP_CLIENT_ENABLE,
    OPP_MENU_OPP_CLIENT_DISABLE,
    OPP_MENU_OPC_KEY_PUSH,
    OPP_MENU_OPC_KEY_EXCH,
    OPP_MENU_OPC_KEY_PULL,
    OPP_MENU_OPC_KEY_PUSH_FILE,
    OPP_MENU_OPC_DISCONNECT_DEVICE,
    OPP_MENU_OPC_KEY_DISC
};

#define OPP_TEST_FILE_PATH "/usr/src/rubikpi-btapp/test_file.txt"
/*******************************************************************************
 **
 ** Function         opp_mgt_callback
 **
 ** Description      This callback function is called in case of server
 **                  disconnection (e.g. server crashes)
 **
 ** Parameters      event and message
 **
 ** Returns          void
 **
 *******************************************************************************/
static BOOLEAN opp_mgt_callback(tBSA_MGT_EVT event, tBSA_MGT_MSG *p_data)
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
 ** Function         ops_menu_display
 **
 ** Description      This is the main menu
 **
 ** Parameters      void
 **
 ** Returns          void
 **
 *******************************************************************************/
void opp_menu_display(void)
{
    printf("Bluetooth Application OPP Menu:\n");
    printf("    %d => opp server enable\n", OPP_MENU_OPP_SERVER_ENABLE);
    printf("    %d => opp server disable\n",OPP_MENU_OPP_SERVER_DISABLE);
    printf("    %d => ops enable auto accept\n",OPP_MENU_OPS_AUTO_ACCEPT);
    printf("    %d => ops disconnect device\n",OPP_MENU_OPS_DISCONNECT_DEVICE);
    printf("    %d => opp client enable\n",OPP_MENU_OPP_CLIENT_ENABLE);
    printf("    %d => opp client disable\n",OPP_MENU_OPP_CLIENT_DISABLE);
    printf("    %d => push vcard\n", OPP_MENU_OPC_KEY_PUSH);
    printf("    %d => exchange vcard\n", OPP_MENU_OPC_KEY_EXCH);
    printf("    %d => pull vcard\n", OPP_MENU_OPC_KEY_PULL);
    printf("    %d => push %s\n", OPP_MENU_OPC_KEY_PUSH_FILE, OPP_TEST_FILE_PATH);
    printf("    %d => opc disconnect device\n", OPP_MENU_OPC_DISCONNECT_DEVICE);
    printf("    %d => discovery\n", OPP_MENU_OPC_KEY_DISC);
    printf("    %d => Exit\n", MENU_QUIT);
}

int opp_menu_handle(void){
    int status;
    int choice;


    /* Open connection to BSA Server */
    // app_mgt_init();
    // if (app_mgt_open(NULL, opp_mgt_callback) < 0)
    // {
    //     APP_ERROR0("Unable to connect to server");
    //     return -1;
    // }

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
                opp_menu_display();
                break;
            case OPP_MENU_OPP_SERVER_ENABLE:
                /* Example of function to start OPS application */
                status = app_start_ops();
                if (status != BSA_SUCCESS)
                {
                    printf("%s: Unable to start OPS err = %d\n",__func__, status);
                    //app_mgt_close();
                }

                break;
            case OPP_MENU_OPP_SERVER_DISABLE:
                /* example to stop OPC service */
                app_stop_ops();
                break;
            case OPP_MENU_OPS_AUTO_ACCEPT:
                app_ops_auto_accept();
                break;

            case OPP_MENU_OPS_DISCONNECT_DEVICE:
                app_ops_disconnect();
                break;

            case OPP_MENU_OPP_CLIENT_ENABLE:
                /* Example of function to start OPC application */
                status = app_opc_start();
                if (status != BSA_SUCCESS)
                {
                    fprintf(stderr, "%s: Unable to start OPC err = %d\n",__func__, status);
                    //app_mgt_close();
                }
                break;
            case OPP_MENU_OPP_CLIENT_DISABLE:
                /* example to stop OPC service */
                app_opc_stop();
                break;
            case OPP_MENU_OPC_KEY_PUSH:
                app_opc_push_vc();
                break;

            case OPP_MENU_OPC_KEY_EXCH:
                app_opc_exchange_vc();
                break;

            case OPP_MENU_OPC_KEY_PULL:
                app_opc_pull_vc();
                break;

            case OPP_MENU_OPC_KEY_PUSH_FILE:
                app_opc_push_file(OPP_TEST_FILE_PATH);
                break;

            case OPP_MENU_OPC_DISCONNECT_DEVICE:
                app_opc_disconnect();
                break;

            case OPP_MENU_OPC_KEY_DISC:
                /* Example to perform Device discovery (in blocking mode) */
                app_disc_start_regular(NULL);
                break;


            default:
                printf("%s: Unknown choice:%d\n", __func__, choice);
                opp_menu_display();
                break;
        }
    }
    while (choice != MENU_QUIT); /* While user don't exit application */

    /* Close BSA Connection before exiting (to release resources) */
    // app_mgt_close();

    return 0;
}


