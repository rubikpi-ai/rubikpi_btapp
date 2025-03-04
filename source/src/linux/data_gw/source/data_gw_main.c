/*****************************************************************************
 **
 **  Name:           app_dg_main.c
 **
 **  Description:    Bluetooth Manager main application
 **
 **  Copyright (c) 2011-2012, Broadcom Corp., All Rights Reserved.
 **  Broadcom Bluetooth Core. Proprietary and confidential.
 **
 *****************************************************************************/
#include <stdlib.h>
#include <unistd.h>

#include "data_gw.h"
#include "menu.h"
#include "bsa_api.h"
#include "app_utils.h"
#include "app_mgt.h"
#include "app_disc.h"
#include "app_xml_param.h"

#define APP_DG_TEST_FILE "/usr/src/rubikpi-btapp/test_files/dg/tx_test_file.txt"

/*
 * Global Variables
 */

/* UI keypress definition */
/* Menu items */
enum
{
    APP_DG_MENU_DISC_ABORT  = 2,
    APP_DG_MENU_DISC,
    APP_DG_MENU_OPEN,
    APP_DG_MENU_CLOSE,
    APP_DG_MENU_LISTEN,
    APP_DG_MENU_SHUTDOWN,
    APP_DG_MENU_SEND_FILE,
    APP_DG_MENU_SEND_DATA,
    APP_DG_MENU_FIND_SERVICE,
    APP_DG_MENU_READ,
    APP_DG_MENU_LOOPBACK,
    APP_DG_MENU_SINGLE_MULTI
};

/*
 * Local functions
 */


/*******************************************************************************
 **
 ** Function         data_gw_menu_display
 **
 ** Description      This is the main menu
 **
 ** Parameters
 **
 ** Returns          void
 **
 *******************************************************************************/
void data_gw_menu_display(void)
{
    printf("Bluetooth Application Data Gateway menu:\n");
    printf("    %d => Abort Service Discovery\n", APP_DG_MENU_DISC_ABORT);
    printf("    %d => Services Discovery (SPP)\n", APP_DG_MENU_DISC);
    printf("    %d => DG Connect\n", APP_DG_MENU_OPEN);
    printf("    %d => DG Disconnect\n", APP_DG_MENU_CLOSE);
    printf("    %d => DG Listen\n", APP_DG_MENU_LISTEN);
    printf("    %d => DG Shutdown\n", APP_DG_MENU_SHUTDOWN);
    printf("    %d => Send a test file\n", APP_DG_MENU_SEND_FILE);
    printf("    %d => Send a test data\n", APP_DG_MENU_SEND_DATA);
    printf("    %d => Find Custom Service\n", APP_DG_MENU_FIND_SERVICE);
    printf("    %d => Read DG port\n", APP_DG_MENU_READ);
    printf("    %d => Toggle data Loopback\n", APP_DG_MENU_LOOPBACK);
    printf("    %d => Toggle Mono/Multi connection mode\n", APP_DG_MENU_SINGLE_MULTI);
    printf("    %d => Exit\n", MENU_QUIT);
}

/*******************************************************************************
 **
 ** Function         app_dg_mgt_callback
 **
 ** Description      This callback function is called in case of server
 **                  disconnection (e.g. server crashes)
 **
 ** Parameters
 **
 ** Returns          void
 **
 *******************************************************************************/
static BOOLEAN app_dg_mgt_callback(tBSA_MGT_EVT event, tBSA_MGT_MSG *p_data)
{
    switch(event)
    {
    case BSA_MGT_STATUS_EVT:
        APP_DEBUG0("BSA_MGT_STATUS_EVT");
        if (p_data->status.enable == FALSE)
        {
            APP_INFO0("Bluetooth Stopped");
            /* clean up application local variable, dg is already stopped in the server */
            app_dg_con_free_all();
        }
        else
        {
            /* Re-Init DG Application */
            APP_INFO0("Bluetooth restarted => re-initialize the application");
            if (app_dg_init() < 0)
            {
                APP_ERROR0("Unable to init DG");
                return FALSE;
            }

            if (app_dg_start() < 0)
            {
                APP_ERROR0("Unable to start DG");
            }
        }
        break;

    case BSA_MGT_DISCONNECT_EVT:
        APP_INFO1("BSA_MGT_DISCONNECT_EVT reason:%d", p_data->disconnect.reason);
        /* Connection with the Server lost => Just exit the application */
        exit(-1);
        break;

    default:
        break;
    }
    return FALSE;
}

#ifdef DEMO_MODE
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
    int choice;
    int connection = 0; /* Only one connection by default*/

    /* Open connection to BSA Server */
    app_mgt_init();
    if (app_mgt_open(NULL, app_dg_mgt_callback) < 0)
    {
        APP_ERROR0("Unable to connect to server");
        return -1;
    }
    /* Init XML state machine */
    app_xml_init();


    /* Initialize DG application */
    if (app_dg_init() < 0)
    {
        APP_ERROR0("Unable to init DG");
        return -1;
    }

    if (app_dg_start() < 0)
    {
        APP_ERROR0("Unable to start DG");
        return -1;
    }

    APP_INFO0("DG Application is in Single Connection mode");

    do
    {
        data_gw_menu_display();
        choice = app_get_choice("Select action");

        switch (choice)
        {
        case APP_DG_MENU_DISC_ABORT:
            app_disc_abort();
            break;

        case APP_DG_MENU_DISC:
            app_disc_start_services(BSA_SPP_SERVICE_MASK);
            break;

        case APP_DG_MENU_OPEN:
            app_dg_open_ex(connection == 0);
            break;

        case APP_DG_MENU_CLOSE:
            app_dg_close(connection);
            break;

        case APP_DG_MENU_LISTEN:
            app_dg_listen();
            break;

        case APP_DG_MENU_SHUTDOWN:
            app_dg_shutdown(connection);
            break;

        case APP_DG_MENU_READ:
            app_dg_read(-1);
            break;
        case APP_DG_MENU_SEND_FILE:
            app_dg_send_file(APP_DG_TEST_FILE, connection);
            break;
        case APP_DG_MENU_FIND_SERVICE:
            app_dg_find_service();
            break;
        case APP_DG_MENU_SEND_DATA:
            app_dg_send_data(connection);
            break;
        case APP_DG_MENU_LOOPBACK:
            app_dg_loopback_toggle();
            break;

        case APP_DG_MENU_SINGLE_MULTI:
            if (connection == 0)
            {
                connection = -1;    /* DG function will ask for connection */
                APP_INFO0("Switched to Multi Connection mode");
            }
            else
            {
                connection = 0;    /* DG function will use connection 0 */
                APP_INFO0("Switched to Single Connection mode");
            }
            break;

        case MENU_QUIT:
            break;

        default:
            APP_ERROR1("main: Unknown choice:%d", choice);
            break;
        }
    } while (choice != MENU_QUIT); /* While user don't exit application */

    /* Disable DG service */
    app_dg_stop();

    /* Close BSA before exiting (to release resources) */
    app_mgt_close();

    return 0;
}
#else
int data_gw_menu_handle(void)
{
    int choice;
    int connection = 0; /* Only one connection by default*/


    app_mgt_custom_cback_update(app_dg_mgt_callback);
    /* Init XML state machine */
    app_xml_init();

    /* Initialize DG application */
    if (app_dg_init() < 0)
    {
        APP_ERROR0("Unable to init DG");
        return 0;
    }

    if (app_dg_start() < 0)
    {
        APP_ERROR0("Unable to start DG");
        return 0;
    }

    APP_INFO0("DG Application is in Single Connection mode");

    do
    {
        choice = app_get_choice("Select action");

        switch (choice)
        {
        case MENU_QUIT:
            /* Disable DG service */
            app_dg_stop();
            return -1;
        case MAIN_MENU:
            /* Disable DG service */
            app_dg_stop();
            APP_INFO0("Back to main menu...");
            return 0;
        case HELP_MENU:
            data_gw_menu_display();
            break;
        case APP_DG_MENU_DISC_ABORT:
            app_disc_abort();
            break;

        case APP_DG_MENU_DISC:
            app_disc_start_services(BSA_SPP_SERVICE_MASK);
            break;

        case APP_DG_MENU_OPEN:
            app_dg_open_ex(connection == 0);
            break;

        case APP_DG_MENU_CLOSE:
            app_dg_close(connection);
            break;

        case APP_DG_MENU_LISTEN:
            app_dg_listen();
            break;

        case APP_DG_MENU_SHUTDOWN:
            app_dg_shutdown(connection);
            break;

        case APP_DG_MENU_READ:
            app_dg_read(-1);
            break;
        case APP_DG_MENU_SEND_FILE:
            app_dg_send_file(APP_DG_TEST_FILE, connection);
            break;
        case APP_DG_MENU_FIND_SERVICE:
            app_dg_find_service();
            break;
        case APP_DG_MENU_SEND_DATA:
            app_dg_send_data(connection);
            break;
        case APP_DG_MENU_LOOPBACK:
            app_dg_loopback_toggle();
            break;

        case APP_DG_MENU_SINGLE_MULTI:
            if (connection == 0)
            {
                connection = -1;    /* DG function will ask for connection */
                APP_INFO0("Switched to Multi Connection mode");
            }
            else
            {
                connection = 0;    /* DG function will use connection 0 */
                APP_INFO0("Switched to Single Connection mode");
            }
            break;


        default:
            APP_ERROR1("%s: Unknown choice:%d",__func__, choice);
            data_gw_menu_display();
            break;
        }
    } while (choice != MENU_QUIT); /* While user don't exit application */

    /* Disable DG service */
    app_dg_stop();


    return 0;
}
#endif