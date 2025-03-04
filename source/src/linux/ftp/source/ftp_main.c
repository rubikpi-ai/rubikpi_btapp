/*****************************************************************************
 **
 **  Name:           app_ftc_main.c
 **
 **  Description:    Bluetooth FTC application
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
#include "menu.h"
#include "ftc.h"
#include "fts.h"
#include "bsa_api.h"

#include "gki.h"
#include "uipc.h"

#include "app_utils.h"
#include "app_mgt.h"
#include "app_xml_param.h"

#include "app_disc.h"

#define APP_TEST_FILE_PATH "/usr/src/rubikpi-btapp/test_file.txt"
#define APP_TEST_FILE_PATH1 "/usr/src/rubikpi-btapp/test_file1.txt"
#define APP_TEST_FILE_PATH2 "/usr/src/rubikpi-btapp/test_file2.txt"
#define APP_TEST_FILE_PATH3 "/usr/src/rubikpi-btapp/test_file3.txt"
#define APP_TEST_DIR "test_dir"


/* ui keypress definition */
enum
{
    //ftp client
    APP_FTC_KEY_ENABLE = 2,
    APP_FTC_KEY_DISABLE,
    APP_FTC_KEY_OPEN,
    APP_FTC_KEY_PUT,
    APP_FTC_KEY_GET,
    APP_FTC_KEY_LS,
    APP_FTC_KEY_LS_XML,
    APP_FTC_KEY_CD,
    APP_FTC_KEY_MK_DIR,
    APP_FTC_KEY_CP,
    APP_FTC_KEY_MV,
    APP_FTC_KEY_RM,
    APP_FTC_KEY_CLOSE,
    APP_FTC_KEY_DISC,
    //ftp server
    APP_FTS_KEY_ENABLE,
    APP_FTS_KEY_DISABLE,
    APP_FTS_ENABLE_AUTO_ACCEPT,
    APP_FTS_DISABLE_AUTO_ACCEPT
};

/*******************************************************************************
 **
 ** Function         ftp_menu_display
 **
 ** Description      This is the main menu
 **
 ** Parameters
 **
 ** Returns          void
 **
 *******************************************************************************/
void ftp_menu_display(void)
{
    printf("Bluetooth Application FTP menu:\n");
    printf("FTP client:\n");
    printf("    %d => Client Enable \n",              APP_FTC_KEY_ENABLE);
    printf("    %d => Client Disable \n",             APP_FTC_KEY_DISABLE);
    printf("    %d => open ftp link \n", APP_FTC_KEY_OPEN);
    printf("    %d => put %s\n",              APP_FTC_KEY_PUT, APP_TEST_FILE_PATH);
    printf("    %d => get %s from src name %s\n",    APP_FTC_KEY_GET, APP_TEST_FILE_PATH3, APP_TEST_FILE_PATH);
    printf("    %d => list \n",               APP_FTC_KEY_LS);
    printf("    %d => list xml\n",            APP_FTC_KEY_LS_XML);
    printf("    %d => Change dir\n",       APP_FTC_KEY_CD);
    printf("    %d => Create dir\n",       APP_FTC_KEY_MK_DIR);
    printf("    %d => remove %s \n",          APP_FTC_KEY_RM, APP_TEST_FILE_PATH);
    printf("    %d => close\n",               APP_FTC_KEY_CLOSE);
    printf("    %d => discovery\n",           APP_FTC_KEY_DISC);
    printf("FTP server:\n");
    printf("    %d => Server Enable \n",              APP_FTS_KEY_ENABLE);
    printf("    %d => Server Disable \n",             APP_FTS_KEY_DISABLE);
    printf("    %d => Enable auto access\n", APP_FTS_ENABLE_AUTO_ACCEPT);
    printf("    %d => Disable auto access\n", APP_FTS_DISABLE_AUTO_ACCEPT);
    printf("\n");
    printf("    %d => Exit\n", MENU_QUIT);
}

/*******************************************************************************
 **
 ** Function         app_ftc_mgt_callback
 **
 ** Description      This callback function is called in case of server
 **                  disconnection (e.g. server crashes)
 **
 ** Parameters
 **
 ** Returns          void
 **
 *******************************************************************************/
static BOOLEAN app_ftc_mgt_callback(tBSA_MGT_EVT event, tBSA_MGT_MSG *p_data)
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
int ftp_menu_handle(void)
{
    int status;
    int choice;
    char* p_root_path = NULL;


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
            ftp_menu_display();
            break;
        case APP_FTC_KEY_ENABLE:
            /* Example of function to start FTS application */
            status = app_start_ftc();
            if (status != BSA_SUCCESS)
            {
                fprintf(stderr, "%s: Unable to start FTC\n",__func__);
                continue;
            }
            break;
        case APP_FTC_KEY_DISABLE:
            break;
        case APP_FTC_KEY_OPEN:
            app_ftc_open();
            break;
        case APP_FTC_KEY_PUT:
            app_ftc_put_file(APP_TEST_FILE_PATH);
            break;
        case APP_FTC_KEY_GET:
            app_ftc_get_file(APP_TEST_FILE_PATH3, APP_TEST_FILE_PATH);
            break;
        case APP_FTC_KEY_CD:
            app_ftc_cd();
            break;
        case APP_FTC_KEY_MK_DIR:
            app_ftc_mkdir();
            break;
        case APP_FTC_KEY_CP:
            app_ftc_cp_file(APP_TEST_FILE_PATH, APP_TEST_FILE_PATH1);
            break;
        case APP_FTC_KEY_MV:
            app_ftc_mv_file(APP_TEST_FILE_PATH, APP_TEST_FILE_PATH2);
            break;
        case APP_FTC_KEY_RM:
            app_ftc_rm_file(APP_TEST_FILE_PATH);
            break;
        case APP_FTC_KEY_LS:
            app_ftc_list_dir("/usr/src/rubikpi-btapp/",FALSE);
            break;
        case APP_FTC_KEY_LS_XML:
            app_ftc_list_dir("/usr/src/rubikpi-btapp/", TRUE);
            break;
        case APP_FTC_KEY_CLOSE:
            app_ftc_close();
            break;
        case APP_FTC_KEY_DISC:
            /* Example to perform Device discovery (in blocking mode) */
            app_disc_start_regular(NULL);
            break;

        case APP_FTS_KEY_ENABLE:
            /* Example of function to start FTS application */
            status = app_start_fts(p_root_path);
            if (status != BSA_SUCCESS)
            {
                fprintf(stderr, "main: Unable to start FTS\n");
                app_mgt_close();
                continue;
            }
            break;
        case APP_FTS_KEY_DISABLE:
            break;
        case APP_FTS_ENABLE_AUTO_ACCEPT:
            app_fts_auto_access(TRUE);
            break;
        case APP_FTS_DISABLE_AUTO_ACCEPT:
            app_fts_auto_access(FALSE);
            break;

        default:
            printf("%s: Unknown choice:%d\n",__func__, choice);
            ftp_menu_display();
            break;
        }
    } while (choice != MENU_QUIT); /* While user don't exit application */



    return 0;
}

