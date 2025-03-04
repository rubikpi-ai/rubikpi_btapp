/*****************************************************************************
**
**  Name:           app_hd_main.c
**
**  Description:    Bluetooth HID Device main application
**
**  Copyright (c) 2010-2013, Broadcom Corp., All Rights Reserved.
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
#include "app_xml_param.h"
#include "app_xml_utils.h"
#include "app_disc.h"
#include "app_mgt.h"
#include "app_utils.h"
#include "app_services.h"
#include "hid_dev.h"
#if defined(APP_HD_AUDIO_STREAMING_INCLUDED) && (APP_HD_AUDIO_STREAMING_INCLUDED == TRUE)
#include "hid_dev_as.h"
#endif

#include "bsa_mgt_api.h"

extern void app_management_callback(tBSA_MGT_EVT event, tBSA_MGT_MSG *p_data);
extern int app_read_xml_remote_devices(void);
extern int app_write_xml_remote_devices(void);

#define APP_XML_REM_DEVICES_FILE_PATH "/usr/src/rubikpi-btapp/bt_devices.xml"


/* Menu items */
enum
{
    /* HD Menu */
    APP_HD_MENU_DISC_ABORT = 2,
    APP_HD_MENU_DISC,
    APP_HD_MENU_LISTEN,
    APP_HD_MENU_CONNECT,
    APP_HD_MENU_DISCONNECT,
    APP_HD_MENU_SEND_REGULAR_KEY,
    APP_HD_MENU_SEND_SPECIAL_KEY,
    APP_HD_MENU_SEND_MOUSE_DATA,
    APP_HD_MENU_SEND_CUSTOMER_DATA,
    APP_HD_MENU_SEND_HD_OUT_DATA,
#if defined(APP_HD_AUDIO_STREAMING_INCLUDED) && (APP_HD_AUDIO_STREAMING_INCLUDED == TRUE)
    APP_HD_MENU_START_STREAMING,
    APP_HD_MENU_STOP_STREAMING,
    APP_HD_MENU_CHANGE_AS_FILE,
#endif
    APP_HD_MENU_QUIT
};

/*
 * Local functions
 */


/*******************************************************************************
 **
 ** Function         hid_dev_menu_display
 **
 ** Description      This is the main menu
 **
 ** Parameters
 **
 ** Returns          void
 **
 *******************************************************************************/
void hid_dev_menu_display(void)
{
    printf("\nBluetooth Application HID Device menu:\n");
    printf("    %d => Discovery Abort\n", APP_HD_MENU_DISC_ABORT);
    printf("    %d => Discovery\n", APP_HD_MENU_DISC);
    printf("    %d => HID Listen \n", APP_HD_MENU_LISTEN);
    printf("    %d => HID Connect \n", APP_HD_MENU_CONNECT);
    printf("    %d => HID Disconnect \n", APP_HD_MENU_DISCONNECT);
    printf("    %d => Send Regular Key\n", APP_HD_MENU_SEND_REGULAR_KEY);
    printf("    %d => Send Special Key\n", APP_HD_MENU_SEND_SPECIAL_KEY);
    printf("    %d => Send Mouse Data\n", APP_HD_MENU_SEND_MOUSE_DATA);
    printf("    %d => Send Customer Data\n", APP_HD_MENU_SEND_CUSTOMER_DATA);
#if defined(APP_HD_AUDIO_STREAMING_INCLUDED) && (APP_HD_AUDIO_STREAMING_INCLUDED == TRUE)
    printf("    %d => Send Start streaming cmd\n",APP_HD_MENU_START_STREAMING);
    printf("    %d => Send Stop streaming cmd\n",APP_HD_MENU_STOP_STREAMING);
    printf("    %d => Change wav file to save audio streaming\n",APP_HD_MENU_CHANGE_AS_FILE);
#endif
    printf("    %d => Exit\n", MENU_QUIT);
}

/*******************************************************************************
 **
 ** Function         app_hd_mgt_callback
 **
 ** Description      This callback function is called in case of server
 **                  disconnection (e.g. server crashes)
 **
 ** Parameters
 **
 ** Returns          void
 **
 *******************************************************************************/
static BOOLEAN app_hd_mgt_callback(tBSA_MGT_EVT event, tBSA_MGT_MSG *p_data)
{
    switch(event)
    {
    case BSA_MGT_STATUS_EVT:
        APP_DEBUG0("BSA_MGT_STATUS_EVT");
        if (p_data->status.enable)
        {
            APP_DEBUG0("Bluetooth restarted => re-initialize the application");
            app_hd_init();
        }
        break;

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
    if (app_mgt_open(NULL, app_hd_mgt_callback) < 0)
    {
        APP_ERROR0("Unable to connect to server");
        return -1;
    }

    /* Init XML state machine */
    app_xml_init();

    /* Init HID Device Application */
    app_hd_init();

    /* set COD to HID device */
    app_hd_set_cod();

    do
    {
        hid_dev_menu_display();

        choice = app_get_choice("Select action");

        switch(choice)
        {
        case APP_HD_MENU_DISC_ABORT:
            /* Example to abort Discovery */
            app_disc_abort();
            break;

        case APP_HD_MENU_DISC:
            app_disc_start_regular(NULL);
            break;

        case APP_HD_MENU_LISTEN:
            /* Example to connect HID Host */
            app_hd_listen();
            break;

        case APP_HD_MENU_CONNECT:
            /* Example to connect HID Host */
            app_hd_connect();
            break;

        case APP_HD_MENU_DISCONNECT:
            /* Example to disconnect HID Host */
            app_hd_disconnect();
            break;

        case APP_HD_MENU_SEND_REGULAR_KEY:
            app_hd_send_regular_key();
            break;

        case APP_HD_MENU_SEND_SPECIAL_KEY:
            app_hd_send_special_key();
            break;

        case APP_HD_MENU_SEND_MOUSE_DATA:
            app_hd_send_mouse_data();
            break;

        case APP_HD_MENU_SEND_CUSTOMER_DATA:
            app_hd_send_customer_data();
            break;

#if defined(APP_HD_AUDIO_STREAMING_INCLUDED) && (APP_HD_AUDIO_STREAMING_INCLUDED == TRUE)
        case APP_HD_MENU_CHANGE_AS_FILE:
            app_hd_as_close_wave_file();
            break;

        case APP_HD_MENU_START_STREAMING:
            app_hd_send_start_streaming();
            break;

        case APP_HD_MENU_STOP_STREAMING:
            app_hd_send_stop_streaming();
            break;
#endif

        case MENU_QUIT:
            printf("main: Bye Bye\n");
            break;

        default:
            APP_ERROR1("Unknown choice:%d", choice);
            break;
        }
    } while (choice != MENU_QUIT); /* While user don't exit application */

    /* Exit HD */
    app_hd_exit();

    /* Close BSA Connection before exiting (to release resources) */
    app_mgt_close();

    return 0;

}
#else 
int hid_dev_menu_handle(void)
{
    int choice;

    app_mgt_custom_cback_update(app_hd_mgt_callback);
    /* Init XML state machine */
    app_xml_init();

    /* Init HID Device Application */
    app_hd_init();

    /* set COD to HID device */
    app_hd_set_cod();

    do
    {

        choice = app_get_choice("Select action");

        switch(choice)
        {
        case MENU_QUIT:
            /* Exit HD */
            app_hd_exit();
            return -1;
        case MAIN_MENU:
            /* Exit HD */
            app_hd_exit();
            APP_INFO0("Back to main menu...");
            return 0;
        case HELP_MENU:
            hid_dev_menu_display();
            break;
        case APP_HD_MENU_DISC_ABORT:
            /* Example to abort Discovery */
            app_disc_abort();
            break;

        case APP_HD_MENU_DISC:
            app_disc_start_regular(NULL);
            break;

        case APP_HD_MENU_LISTEN:
            /* Example to connect HID Host */
            app_hd_listen();
            break;

        case APP_HD_MENU_CONNECT:
            /* Example to connect HID Host */
            app_hd_connect();
            break;

        case APP_HD_MENU_DISCONNECT:
            /* Example to disconnect HID Host */
            app_hd_disconnect();
            break;

        case APP_HD_MENU_SEND_REGULAR_KEY:
            app_hd_send_regular_key();
            break;

        case APP_HD_MENU_SEND_SPECIAL_KEY:
            app_hd_send_special_key();
            break;

        case APP_HD_MENU_SEND_MOUSE_DATA:
            app_hd_send_mouse_data();
            break;

        case APP_HD_MENU_SEND_CUSTOMER_DATA:
            app_hd_send_customer_data();
            break;

#if defined(APP_HD_AUDIO_STREAMING_INCLUDED) && (APP_HD_AUDIO_STREAMING_INCLUDED == TRUE)
        case APP_HD_MENU_CHANGE_AS_FILE:
            app_hd_as_close_wave_file();
            break;

        case APP_HD_MENU_START_STREAMING:
            app_hd_send_start_streaming();
            break;

        case APP_HD_MENU_STOP_STREAMING:
            app_hd_send_stop_streaming();
            break;
#endif


        default:
            APP_ERROR1("%s: Unknown choice:%d",__func__, choice);
            hid_dev_menu_display();
            break;
        }
    } while (choice != MENU_QUIT); /* While user don't exit application */

    /* Exit HD */
    app_hd_exit();


    return 0;
}
#endif
