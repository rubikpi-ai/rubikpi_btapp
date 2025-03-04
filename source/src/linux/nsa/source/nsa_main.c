/*****************************************************************************
**
**  Name:           app_nsa_main.c
**
**  Description:    Bluetooth NSA Main application
**
**  Copyright (c) 2012, Broadcom Corp., All Rights Reserved.
**  Broadcom Bluetooth Core. Proprietary and confidential.
**
*****************************************************************************/

#include <stdlib.h>
#include "menu.h"
#include "nsa.h"
#include "app_mgt.h"
#include "app_utils.h"

/*
 * Defines
 */

/* NSA Menu items */
enum
{
    APP_NSA_MENU_ADD_IF = 2,
    APP_NSA_MENU_REMOVE_IF
};


/*
 * Global Variables
 */

/*******************************************************************************
 **
 ** Function         nsa_menu_display
 **
 ** Description      This is the NSA menu
 **
 ** Returns          void
 **
 *******************************************************************************/
void nsa_menu_display (void)
{
    APP_INFO0("Bluetooth Application NSA menu:");
    APP_INFO1("\t%d => Add NSA Interface", APP_NSA_MENU_ADD_IF);
    APP_INFO1("\t%d => Remove NSA Interface", APP_NSA_MENU_REMOVE_IF);
    APP_INFO1("\t%d => Exit", MENU_QUIT);
}


/*******************************************************************************
 **
 ** Function         app_nsa_menu
 **
 ** Description      Handle the NSA menu
 **
 ** Returns          void
 **
 *******************************************************************************/
void app_nsa_menu(void)
{
    int choice;

    do
    {
        nsa_menu_display();

        choice = app_get_choice("Select action");

        switch(choice)
        {
        case APP_NSA_MENU_ADD_IF:
            app_nsa_add_if();
            break;

        case APP_NSA_MENU_REMOVE_IF:
            app_nsa_remove_if();
            break;

        case MENU_QUIT:
            APP_INFO0("Quit");
            break;

        default:
            APP_ERROR1("Unknown choice:%d", choice);
            break;
        }
    } while (choice != MENU_QUIT); /* While user don't exit application */
}

/*******************************************************************************
 **
 ** Function         app_nsa_mgt_callback
 **
 ** Description      This callback function is called in case of server
 **                  disconnection (e.g. server crashes)
 **
 ** Parameters
 **
 ** Returns          BOOLEAN
 **
 *******************************************************************************/
BOOLEAN app_nsa_mgt_callback(tBSA_MGT_EVT event, tBSA_MGT_MSG *p_data)
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

#ifdef DEMO_MODE
/*******************************************************************************
 **
 ** Function        main
 **
 ** Description     This is the main function
 **
 ** Parameters      Program's arguments
 **
 ** Returns         status
 **
 *******************************************************************************/
int main(int argc, char **argv)
{
    int status;

    /* Initialize NSA application */
    status = app_nsa_init();
    if (status < 0)
    {
        APP_ERROR0("Couldn't Initialize NSA app, exiting");
        exit(-1);
    }

    /* Open connection to BSA Server */
    app_mgt_init();
    if (app_mgt_open(NULL, app_nsa_mgt_callback) < 0)
    {
        APP_ERROR0("Unable to connect to server");
        return -1;
    }

    /* The main NSA loop */
    app_nsa_menu();

    app_nsa_exit();

    /* Close BSA Connection before exiting (to release resources) */
    app_mgt_close();

    return 0;
}
#else 
int nsa_menu_handle(void)
{
    int status;
    int choice;

    /* Initialize NSA application */
    status = app_nsa_init();
    if (status < 0)
    {
        APP_ERROR0("Couldn't Initialize NSA, exiting");
        return 0;
    }

    do
    {

        choice = app_get_choice("Select action");

        switch(choice)
        {
        case MENU_QUIT:
            app_nsa_exit();
            return -1;
        case MAIN_MENU:
            app_nsa_exit();
            APP_INFO0("Back to main menu...");
            return 0;
        case HELP_MENU:
            nsa_menu_display();
            break;
        case APP_NSA_MENU_ADD_IF:
            app_nsa_add_if();
            break;

        case APP_NSA_MENU_REMOVE_IF:
            app_nsa_remove_if();
            break;


        default:
            APP_ERROR1("%s: Unknown choice:%d",__func__, choice);
            nsa_menu_display();
            break;
        }
    } while (choice != MENU_QUIT); /* While user don't exit application */

    app_nsa_exit();


    return 0;
}
#endif

