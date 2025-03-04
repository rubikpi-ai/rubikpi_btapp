/*****************************************************************************
 **
 **  Name:           app_headless_main.h
 **
 **  Description:    ADD Headless Main
 **
 **  Copyright (c) 2015, Broadcom Corp., All Rights Reserved.
 **  Broadcom Bluetooth Core. Proprietary and confidential.
 **
 *****************************************************************************/
#ifndef _APP_HEADLESS_MAIN_H_
#define _APP_HEADLESS_MAIN_H_

#include <stdlib.h>
#include "headless.h"
#include "headless_ble.h"
#include "tvwakeup.h"
#include "app_utils.h"
#include "app_xml_param.h"
#include "app_xml_utils.h"
#ifndef DEMO_MODE
static void headless_menu_display (void);
int headless_menu_handle(void);
#endif
#endif /* _APP_HEADLESS_MAIN_H_ */
