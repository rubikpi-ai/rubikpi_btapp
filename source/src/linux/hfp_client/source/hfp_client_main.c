/*****************************************************************************
**
**  Name:           app_hs_main.c
**
**  Description:    Bluetooth Manager application
**
**  Copyright (c) 2009-2012, Broadcom Corp., All Rights Reserved.
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

#include "bsa_api.h"
#include "menu.h"
#include "hfp_client.h"

#include "gki.h"
#include "uipc.h"

#include "app_utils.h"
#include "app_xml_param.h"
#include "app_xml_utils.h"

#include "app_disc.h"
#include "app_mgt.h"

#include "app_dm.h"

int g_hfp_client_init = 0;
/* ui keypress definition */
enum
{
    APP_HS_ENABLE = 2,
    APP_HS_DISABLE,
    APP_HS_KEY_DISC_AG,
    APP_HS_KEY_OPEN,
    APP_HS_KEY_CLOSE,
    APP_HS_KEY_PICKUP_CALL,
    APP_HS_KEY_HANGUP_CALL,
    APP_HS_KEY_PLAY,
    APP_HS_KEY_RECORD,
    APP_HS_KEY_STOP_RECORDING
};

#define APP_HS_SCO_IN_SOUND_FILE    "/usr/src/rubikpi-btapp/sco_in.wav"
#define APP_HS_SCO_OUT_SOUND_FILE    APP_HS_SCO_IN_SOUND_FILE

/*******************************************************************************
 **
 ** Function         hfp_client_menu_display
 **
 ** Description      This is the main menu
 **
 ** Parameters
 **
 ** Returns          void
 **
 *******************************************************************************/
void hfp_client_menu_display(void)
{
    printf("\nBluetooth Application HFP client menu:\n");
#ifndef DEMO_MODE
    printf("    %d  => init\n", APP_HS_ENABLE);
    printf("    %d  => deinit\n", APP_HS_DISABLE);
#endif
    printf("    %d  => discover\n", APP_HS_KEY_DISC_AG);
    printf("    %d  => Connect\n", APP_HS_KEY_OPEN);
    printf("    %d  => Close \n", APP_HS_KEY_CLOSE);
    printf("    %d  => pick up the call \n", APP_HS_KEY_PICKUP_CALL);
    printf("    %d  => hang up the call \n", APP_HS_KEY_HANGUP_CALL);
    printf("    %d  => Play audio file\n", APP_HS_KEY_PLAY);
    printf("    %d  => Record audio file\n", APP_HS_KEY_RECORD);
    printf("    %d  => Stop recording audio file\n", APP_HS_KEY_STOP_RECORDING);
    printf("    %d  => Exit\n", MENU_QUIT);
}

/*******************************************************************************
 **
 ** Function         app_hs_mgt_callback
 **
 ** Description      This callback function is called in case of server
 **                  disconnection (e.g. server crashes)
 **
 ** Parameters
 **
 ** Returns          void
 **
 *******************************************************************************/
static BOOLEAN app_hs_mgt_callback(tBSA_MGT_EVT event, tBSA_MGT_MSG *p_data)
{
    switch(event)
    {
    case BSA_MGT_STATUS_EVT:
        APP_DEBUG0("BSA_MGT_STATUS_EVT");
        if (p_data->status.enable)
        {
            if(g_hfp_client_init)
            {
                /* Re-Init HID Host Application */
                printf("\tBluetooth restarted => re-initialize the application\n");
                app_hs_init();
            }
        }
        break;

    case BSA_MGT_DISCONNECT_EVT:
        APP_DEBUG1("BSA_MGT_DISCONNECT_EVT reason:%d\n", p_data->disconnect.reason);
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

    /* Open connection to BSA Server */
    app_mgt_init();
    if (app_mgt_open(NULL, app_hs_mgt_callback) < 0)
    {
        APP_ERROR0("Unable to connect to server");
        return -1;
    }

    /* Init XML state machine */
    app_xml_init();

    /* Example of function to get the Local Bluetooth configuration */
    if( app_dm_get_local_bt_config() < 0)
    {
        APP_ERROR0("app_dm_get_local_bt_config failed");
    }

    /* Init Headset Application */
    app_hs_init();
    g_hfp_client_init = 1;
    /* Start Headset service*/
    app_hs_start(NULL);

    do
    {
        hfp_client_menu_display();
        choice = app_get_choice("Select action");

        switch(choice)
        {
        case APP_HS_KEY_DISC_AG:
            /* Example to perform Device discovery (in blocking mode) */
            app_disc_start_regular(NULL);
            break;
        case APP_HS_KEY_OPEN:
            app_hs_open(NULL);
            break;

        case APP_HS_KEY_CLOSE:
            app_hs_close();
            break;

        case APP_HS_KEY_PICKUP_CALL:
            app_hs_answer_call();
            break;

        case APP_HS_KEY_HANGUP_CALL:
            app_hs_hangup();
             break;

        case APP_HS_KEY_RECORD:
            /* example to record SCO IN channel to a file */
            app_hs_open_rec_file(APP_HS_SCO_IN_SOUND_FILE);
            break;

        case APP_HS_KEY_STOP_RECORDING:
            /* example to record SCO IN channel to a file */
            app_hs_close_rec_file();
            break;
        case APP_HS_KEY_PLAY:
            /* example to play a file on SCO OUT channel */
            app_hs_play_file(APP_HS_SCO_OUT_SOUND_FILE);
            printf("Finished reading audio file...all data sent to SCO\n");
            break;

        case MENU_QUIT:
            printf("main: Bye Bye\n");
            break;

        default:
            printf("main: Unknown choice:%d\n", choice);
            break;
        }
    } while (choice != MENU_QUIT);      /* While user don't exit application */

    /* Start Headset service*/
    app_hs_stop();

    /* Close BSA Connection before exiting (to release resources) */
    app_mgt_close();

    return 0;
}
#else
int hfp_client_menu_handle(void)
{
        int choice;


    app_mgt_custom_cback_update(app_hs_mgt_callback);



    do
    {
        choice = app_get_choice("Select action");

        switch(choice)
        {
        case MENU_QUIT:
            return -1;
        case MAIN_MENU:
            APP_INFO0("Back to main menu...");
            return 0;
        case HELP_MENU:
            hfp_client_menu_display();
            break;
        case APP_HS_ENABLE:
            /* Init XML state machine */
            app_xml_init();

            /* Example of function to get the Local Bluetooth configuration */
            if( app_dm_get_local_bt_config() < 0)
            {
                APP_ERROR0("app_dm_get_local_bt_config failed");
            }

            /* Init Headset Application */
            app_hs_init();
            g_hfp_client_init = 1;
            /* Start Headset service*/
            app_hs_start(NULL);
            break;
        case APP_HS_DISABLE:
            /* Start Headset service*/
            app_hs_stop();
            break;
        case APP_HS_KEY_DISC_AG:
            /* Example to perform Device discovery (in blocking mode) */
            app_disc_start_regular(NULL);
            break;
        case APP_HS_KEY_OPEN:
            app_hs_open(NULL);
            break;

        case APP_HS_KEY_CLOSE:
            app_hs_close();
            break;

        case APP_HS_KEY_PICKUP_CALL:
            app_hs_answer_call();
            break;

        case APP_HS_KEY_HANGUP_CALL:
            app_hs_hangup();
             break;

        case APP_HS_KEY_RECORD:
            /* example to record SCO IN channel to a file */
            app_hs_open_rec_file(APP_HS_SCO_IN_SOUND_FILE);
            break;

        case APP_HS_KEY_STOP_RECORDING:
            /* example to record SCO IN channel to a file */
            app_hs_close_rec_file();
            break;
        case APP_HS_KEY_PLAY:
            /* example to play a file on SCO OUT channel */
            app_hs_play_file(APP_HS_SCO_OUT_SOUND_FILE);
            printf("Finished reading audio file...all data sent to SCO\n");
            break;

        default:
            printf("%s: Unknown choice:%d\n", __func__, choice);
            hfp_client_menu_display();
            break;
        }
    } while (choice != MENU_QUIT);      /* While user don't exit application */



    return 0;
}
#endif