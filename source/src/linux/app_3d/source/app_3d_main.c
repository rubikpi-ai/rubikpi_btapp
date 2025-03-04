/*****************************************************************************
**
**  Name:           app_3d_main.c
**
**  Description:    Bluetooth DTV Main application
**
**  Copyright (c) 2011-2012, Broadcom Corp., All Rights Reserved.
**  Broadcom Bluetooth Core. Proprietary and confidential.
**
*****************************************************************************/

#include <stdlib.h>
#include "menu.h"
#include "app_3d.h"
#include "app_3dtv.h"
#include "app_utils.h"
#include "app_disc.h"
#include "app_mgt.h"
#include "app_dm.h"

/*
 * Defines
 */

/* 3D Menu items */
enum
{
    APP_3D_MENU_ABORT_DISC = 2,
    APP_3D_MENU_DISC_MASTER,
    APP_3D_MENU_SET_IDLE,
    APP_3D_MENU_SET_MASTER,
    APP_3D_MENU_SET_SLAVE,
    APP_3D_MENU_SET_OFFSET_DELAY,
    APP_3D_MENU_SEND_TX_DATA,
    APP_3D_MENU_ENABLE_VSYNC_DETECTION,
    APP_3D_MENU_DISABLE_VSYNC_DETECTION,
    APP_3D_MENU_SET_AFH_CHANNELS,
    APP_3D_MENU_TOGGLE_PROX_PAIR,
    APP_3D_MENU_TOGGLE_SHOWROOM,
    APP_3D_MENU_TOGGLE_RC_PAIRABLE,
    APP_3D_MENU_TOGGLE_RC_ASSO,
    APP_3D_MENU_SET_DUAL_VIEW
};


/*
 * Global Variables
 */

/*******************************************************************************
 **
 ** Function         dtv_menu_display
 **
 ** Description      This is the 3D menu
 **
 ** Returns          void
 **
 *******************************************************************************/
void dtv_menu_display (void)
{
    APP_INFO0("Bluetooth Application 3DTV menu:");
    APP_INFO1("\t%d => Abort Discovery", APP_3D_MENU_ABORT_DISC);
    APP_INFO1("\t%d => COD Discovery (3DTV Master)", APP_3D_MENU_DISC_MASTER);
    APP_INFO1("\t%d => Set 3DTV Idle mode", APP_3D_MENU_SET_IDLE);
    APP_INFO1("\t%d => Set 3DTV Master mode", APP_3D_MENU_SET_MASTER);
    APP_INFO1("\t%d => Set 3DTV Slave mode", APP_3D_MENU_SET_SLAVE);
    APP_INFO1("\t%d => Set 3DTV Offset/Delay", APP_3D_MENU_SET_OFFSET_DELAY);
    APP_INFO1("\t%d => Send 3D Offset/Delay (new profile)", APP_3D_MENU_SEND_TX_DATA);
    APP_INFO1("\t%d => Enable VSync Detection", APP_3D_MENU_ENABLE_VSYNC_DETECTION);
    APP_INFO1("\t%d => Disable VSync Detection", APP_3D_MENU_DISABLE_VSYNC_DETECTION);
    APP_INFO1("\t%d => Set AFH Configuration", APP_3D_MENU_SET_AFH_CHANNELS);
    APP_INFO1("\t%d => Toggle 3D Proximity Pairing (currently:%s)", APP_3D_MENU_TOGGLE_PROX_PAIR,
            (app_3d_cb.brcm_mask & BSA_DM_3D_CAP_MASK)?"Enabled":"Disabled");
    APP_INFO1("\t%d => Toggle 3D Showroom Mode (currently:%s)", APP_3D_MENU_TOGGLE_SHOWROOM,
            (app_3d_cb.brcm_mask & BSA_DM_SHOW_ROOM_MASK)?"Enabled":"Disabled");
    APP_INFO1("\t%d => Toggle RC Pairable (currently:%s)", APP_3D_MENU_TOGGLE_RC_PAIRABLE,
            (app_3d_cb.brcm_mask & BSA_DM_RC_PAIRABLE_MASK)?"Enabled":"Disabled");
    APP_INFO1("\t%d => Toggle RC Associated (currently:%s)", APP_3D_MENU_TOGGLE_RC_ASSO,
            (app_3d_cb.brcm_mask & BSA_DM_RC_ASSO_MASK)?"Enabled":"Disabled");
    APP_INFO1("\t%d => Dual/Multi View Control (currently:0x%02X)\n", APP_3D_MENU_SET_DUAL_VIEW,
            app_3d_dualview_get());
    APP_INFO1("\t%d => Exit", MENU_QUIT);
}


/*******************************************************************************
 **
 ** Function         app_3d_menu
 **
 ** Description      Handle the 3dtv menu
 **
 ** Returns          void
 **
 *******************************************************************************/
void app_3d_menu(void)
{
    int choice;
    unsigned int afh_ch1, afh_ch2;

    do
    {
        dtv_menu_display();

        choice = app_get_choice("Select action");

        switch(choice)
        {
        case APP_3D_MENU_ABORT_DISC:
            app_disc_abort();
            break;

        case APP_3D_MENU_DISC_MASTER:
            /* Example of function to Search 3D Master (Brcm Filter and COD) */
            app_disc_start_brcm_filter_cod(
                    BSA_DISC_BRCM_3DTV_MASTER_FILTER,
                    0, BTM_COD_MAJOR_AUDIO, BTM_COD_MINOR_VIDDISP_LDSPKR, NULL);
            break;

        case APP_3D_MENU_SET_IDLE:
            app_3d_set_idle();
            break;

        case APP_3D_MENU_SET_MASTER:
            app_3d_set_master();
            break;

        case APP_3D_MENU_SET_SLAVE:
            app_3d_set_slave();
            break;

        case APP_3D_MENU_SET_OFFSET_DELAY:
            /* Example of function set 3DTV Offset and Delay */
            app_3d_set_3d_offset_delay(FALSE);
            break;

        case APP_3D_MENU_SEND_TX_DATA:
            /* Example of function send 3D profile Offset and Delay */
            app_3d_send_3ds_data(FALSE);
            break;

        case APP_3D_MENU_ENABLE_VSYNC_DETECTION:
            app_3dtv_enable_vsync_detection(TRUE);
            break;

        case APP_3D_MENU_DISABLE_VSYNC_DETECTION:
            app_3dtv_enable_vsync_detection(FALSE);
            break;

        case APP_3D_MENU_SET_AFH_CHANNELS:
            /* Choose first channel*/
            APP_INFO0("    Enter First AFH CHannel (79 = complete channel map):");
            afh_ch1 = app_get_choice("");
            APP_INFO0("    Enter Last AFH CHannel:");
            afh_ch2 = app_get_choice("");
            app_dm_set_channel_map(afh_ch1,afh_ch2);
            break;

        case APP_3D_MENU_TOGGLE_PROX_PAIR:
            app_3d_toggle_proximity_pairing();
            break;

        case APP_3D_MENU_TOGGLE_SHOWROOM:
            app_3d_toggle_showroom();
            break;

        case APP_3D_MENU_TOGGLE_RC_PAIRABLE:
            app_3d_toggle_rc_pairable();
            break;

        case APP_3D_MENU_TOGGLE_RC_ASSO:
            app_3d_toggle_rc_associated();
            break;

        case APP_3D_MENU_SET_DUAL_VIEW:
            app_3d_dualview_set();
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
 ** Function         app_3d_mgt_callback
 **
 ** Description      This callback function is called in case of server
 **                  disconnection (e.g. server crashes)
 **
 ** Parameters
 **
 ** Returns          BOOLEAN
 **
 *******************************************************************************/
static BOOLEAN app_3d_mgt_callback(tBSA_MGT_EVT event, tBSA_MGT_MSG *p_data)
{
    switch(event)
    {
    case BSA_MGT_STATUS_EVT:
        APP_DEBUG0("BSA_MGT_STATUS_EVT");
        if (p_data->status.enable)
        {
            APP_DEBUG0("Bluetooth restarted => re-initialize the application");
            app_3d_start();
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

    /* Initialize 3D application */
    status = app_3d_init();
    if (status < 0)
    {
        APP_ERROR0("Couldn't Initialize 3D app, exiting");
        exit(-1);
    }

    /* Open connection to BSA Server */
    app_mgt_init();
    if (app_mgt_open(NULL, app_3d_mgt_callback) < 0)
    {
        APP_ERROR0("Unable to connect to server");
        return -1;
    }

    /* Start 3D application */
    status = app_3d_start();
    if (status < 0)
    {
        APP_ERROR0("Couldn't Start 3D app, exiting");
        return -1;
    }

    /* Switch TV to 3D Master mode by default */
    app_3d_set_master();

    /* The main 3D loop */
    app_3d_menu();

    /* Exit 3D mode */
    app_3d_exit();

    /* Close BSA Connection before exiting (to release resources) */
    app_mgt_close();

    return 0;
}
#else 
int dtv_menu_handle(void)
{
    int status,choice;
    unsigned int afh_ch1, afh_ch2;

    /* Initialize 3D application */
    status = app_3d_init();
    if (status < 0)
    {
        APP_ERROR0("Couldn't Initialize 3D, exiting");
        return 0;
    }

    app_mgt_custom_cback_update(app_3d_mgt_callback);
    /* Start 3D application */
    status = app_3d_start();
    if (status < 0)
    {
        APP_ERROR0("Couldn't start 3D, exiting");
        return 0;
    }

    /* Switch TV to 3D Master mode by default */
    app_3d_set_master();


    do
    {

        choice = app_get_choice("Select action");

        switch(choice)
        {
        case MENU_QUIT:
            /* Exit 3D mode */
            app_3d_exit();
            return -1;
        case MAIN_MENU:
            /* Exit 3D mode */
            app_3d_exit();
            APP_INFO0("Back to main menu...");
            return 0;
        case HELP_MENU:
            dtv_menu_display();
            break;
        case APP_3D_MENU_ABORT_DISC:
            app_disc_abort();
            break;

        case APP_3D_MENU_DISC_MASTER:
            /* Example of function to Search 3D Master (Brcm Filter and COD) */
            app_disc_start_brcm_filter_cod(
                    BSA_DISC_BRCM_3DTV_MASTER_FILTER,
                    0, BTM_COD_MAJOR_AUDIO, BTM_COD_MINOR_VIDDISP_LDSPKR, NULL);
            break;

        case APP_3D_MENU_SET_IDLE:
            app_3d_set_idle();
            break;

        case APP_3D_MENU_SET_MASTER:
            app_3d_set_master();
            break;

        case APP_3D_MENU_SET_SLAVE:
            app_3d_set_slave();
            break;

        case APP_3D_MENU_SET_OFFSET_DELAY:
            /* Example of function set 3DTV Offset and Delay */
            app_3d_set_3d_offset_delay(FALSE);
            break;

        case APP_3D_MENU_SEND_TX_DATA:
            /* Example of function send 3D profile Offset and Delay */
            app_3d_send_3ds_data(FALSE);
            break;

        case APP_3D_MENU_ENABLE_VSYNC_DETECTION:
            app_3dtv_enable_vsync_detection(TRUE);
            break;

        case APP_3D_MENU_DISABLE_VSYNC_DETECTION:
            app_3dtv_enable_vsync_detection(FALSE);
            break;

        case APP_3D_MENU_SET_AFH_CHANNELS:
            /* Choose first channel*/
            APP_INFO0("    Enter First AFH CHannel (79 = complete channel map):");
            afh_ch1 = app_get_choice("");
            APP_INFO0("    Enter Last AFH CHannel:");
            afh_ch2 = app_get_choice("");
            app_dm_set_channel_map(afh_ch1,afh_ch2);
            break;

        case APP_3D_MENU_TOGGLE_PROX_PAIR:
            app_3d_toggle_proximity_pairing();
            break;

        case APP_3D_MENU_TOGGLE_SHOWROOM:
            app_3d_toggle_showroom();
            break;

        case APP_3D_MENU_TOGGLE_RC_PAIRABLE:
            app_3d_toggle_rc_pairable();
            break;

        case APP_3D_MENU_TOGGLE_RC_ASSO:
            app_3d_toggle_rc_associated();
            break;

        case APP_3D_MENU_SET_DUAL_VIEW:
            app_3d_dualview_set();
            break;


        default:
            APP_ERROR1("%s: Unknown choice:%d", __func__,choice);
            dtv_menu_display();
            break;
        }
    } while (choice != MENU_QUIT); /* While user don't exit application */

    /* Exit 3D mode */
    app_3d_exit();


    return 0;
}
#endif
