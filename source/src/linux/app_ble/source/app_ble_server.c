/*****************************************************************************
**
**  Name:           app_ble_server.c
**
**  Description:    Bluetooth BLE Server general application
**
**  Copyright (c) 2015-2016, Broadcom Corp., All Rights Reserved.
**  Broadcom Bluetooth Core. Proprietary and confidential.
**
*****************************************************************************/
#include <unistd.h>
#include "app_ble.h"
#include "app_xml_utils.h"
#include "app_utils.h"
#include "app_mgt.h"
#include "app_disc.h"
#include "app_dm.h"

#include "app_ble_server.h"

/*
 * Global Variables
 */


/*
 * Local functions
 */
typedef struct
{
    UINT16 char_uuid;
    UINT16 char_hndl;
    int char_index;
    int serv_index;
}UUID_HANDLE;

#define UUID_HANDLE_RECORD_MAX           64
static UUID_HANDLE s_uuid_handle_record[UUID_HANDLE_RECORD_MAX] = {{0, 0, 0, 0}};

const UINT8 app_hogp_device_cfg_report[] =
{
    0x05, 0x01,         /* Usage page Desktop 01 */
    0x09, 0x06,         /* Usage Keyboard 06 */
    0xa1, 0x01,         /* Collection appliction */
        0x05, 0x07,        /* Usage page Keyboard */
        0x85, BTA_HD_REPT_ID_KBD,        /* Report ID 1 */
        0x19, 0xe0,        /* Usage minimum e0 (leftControl) */
        0x29, 0xe7,        /* Usage maximum e7 (right gui) */
        0x15, 0x00,        /* Logical mimumum 0 */
        0x25, 0x01,        /* Logical Maximum 1 */
        0x75, 0x01,        /* Report size 1 */
        0x95, 0x08,        /* Report count 8 */
        0x81, 0x02,        /* Input Variable Abs */
        0x95, 0x01,        /* Report count 1 */
        0x75, 0x08,        /* Report size 8 */
        0x81, 0x03,        /* Iput constant variable   */
        0x95, 0x06,        /* Report Count 6 */
        0x75, 0x08,        /* Report size 8 */
        0x15, 0x00,        /* Logical mimumum 0 */
        0x26, 0xff, 0x00,  /* Logical Maximum 00ff */
        0x05, 0x07,        /* Usage page Keyboard */
        0x19, 0x00,        /* Usage minimum 0 */
        0x29, 0xff,        /* Usage maximum a4 */
        0x81, 0x00,        /* Input data array absolute */
    0xc0,
};


/*
 * BLE common functions
 */

/*******************************************************************************
 **
 ** Function         app_ble_server_add_hanle_by_index
 **
 ** Description      add char handle and its attr_index
 **
 ** Parameters
 **
 ** Returns          positive number(include 0) if successful, error code otherwise
 **
 *******************************************************************************/
int app_ble_server_add_hanle_by_index(UINT16 char_hndl, int char_index, int serv_index)
{
    int index;

    for (index = 0; index < UUID_HANDLE_RECORD_MAX; index++)
    {
        if ((s_uuid_handle_record[index].char_index == char_index) && (s_uuid_handle_record[index].serv_index == serv_index))
        {
            s_uuid_handle_record[index].char_hndl = char_hndl;
            APP_INFO1("%s add char_hndl:0x%x by char_index:%d serv_index:%d successfully", __func__, char_hndl, char_index, serv_index);
            return index;
        }
    }
    APP_ERROR1("%s fails to add char_hndl:0x%x, index:%d", __func__, char_hndl, index);
    return -1;
}

/*******************************************************************************
 **
 ** Function         app_ble_server_add_uuid_index
 **
 ** Description      add char uuid and its index
 **
 ** Parameters
 **
 ** Returns          positive number(include 0) if successful, error code otherwise
 **
 *******************************************************************************/
int app_ble_server_add_uuid_index(UINT16 char_uuid, int char_index, int serv_index)
{
    int index;

    for (index = 0; index < UUID_HANDLE_RECORD_MAX; index++)
    {
        if (s_uuid_handle_record[index].char_uuid == 0)
        {
            s_uuid_handle_record[index].char_uuid = char_uuid;
            s_uuid_handle_record[index].char_index = char_index;
            s_uuid_handle_record[index].serv_index = serv_index;
            APP_INFO1("%s add char_uuid:0x%x, char_index:%d, serv_index:%d successfully", __func__,
                char_uuid, char_index, serv_index);
            return index;
        }
    }
    APP_ERROR1("%s fails to add char_uuid:0x%x, char_index:%d, serv_index:%d", __func__,
        char_uuid, char_index, serv_index);
    return -1;
}


/*******************************************************************************
 **
 ** Function         app_ble_server_find_uuid_by_handle
 **
 ** Description      find char's uuid by its handle
 **
 ** Parameters
 **
 ** Returns
 **
 *******************************************************************************/
UINT16 app_ble_server_find_uuid_by_handle(UINT16 char_hndl)
{
    int index;

    for (index = 0; index < UUID_HANDLE_RECORD_MAX; index++)
    {
        if (s_uuid_handle_record[index].char_hndl== char_hndl)
        {
            APP_INFO1("%s get char_uuid:0x%x, char_hndl:0x%x successfully", __func__, s_uuid_handle_record[index].char_uuid, char_hndl);
            return s_uuid_handle_record[index].char_uuid;
        }
    }
    APP_ERROR1("%s fails to get uuid, char_hndl:0x%x index:%d", __func__, char_hndl, index);
    return 0;
}

/*******************************************************************************
 **
 ** Function         app_ble_server_find_uuid_by_index
 **
 ** Description      find char's uuid by its index
 **
 ** Parameters
 **
 ** Returns
 **
 *******************************************************************************/
UINT16 app_ble_server_find_uuid_by_index(int char_index, int serv_index)
{
    int index;

    for (index = 0; index < UUID_HANDLE_RECORD_MAX; index++)
    {
        if ((s_uuid_handle_record[index].char_index == char_index) && (s_uuid_handle_record[index].serv_index == serv_index))
        {
            APP_INFO1("%s get char uuid:0x%x, char_index:0x%x, serv_index:0x%x successfully", __func__,
                s_uuid_handle_record[index].char_uuid, char_index, serv_index);
            return s_uuid_handle_record[index].char_uuid;
        }
    }
    APP_ERROR1("%s fails to get uuid, char_index:0x%x, serv_index:0x%x, index:%d", __func__, char_index, serv_index, index);
    return 0;
}


/*******************************************************************************
 **
 ** Function         app_ble_server_find_handle_by_uuid
 **
 ** Description      find char's handle by its uuid
 **
 ** Parameters
 **
 ** Returns
 **
 *******************************************************************************/
UINT16 app_ble_server_find_handle_by_uuid(UINT16 uuid)
{
    int index;

    for (index = 0; index < UUID_HANDLE_RECORD_MAX; index++)
    {
        if ((s_uuid_handle_record[index].char_uuid == uuid) && (s_uuid_handle_record[index].char_hndl != 0))
        {
            APP_INFO1("%s get char handle:0x%x, uuid:0x%x successfully", __func__,
                s_uuid_handle_record[index].char_hndl, s_uuid_handle_record[index].char_uuid);
            return s_uuid_handle_record[index].char_hndl;
        }
    }
    APP_INFO1("%s fails to get handle, uuid:0x%x, index=%d", __func__, uuid, index);
    return 0;
}



/*******************************************************************************
 **
 ** Function         app_ble_server_find_uuid_by_handle
 **
 ** Description      find char's uuid by its handle
 **
 ** Parameters
 **
 ** Returns          positive number(include 0) if successful, error code otherwise
 **
 *******************************************************************************/
void app_ble_server_clear_uuid_handle_record(void)
{
    memset(s_uuid_handle_record, 0, UUID_HANDLE_RECORD_MAX*sizeof(s_uuid_handle_record[0]));
    APP_INFO1("%s is done.", __func__);
}



/*******************************************************************************
 **
 ** Function         app_ble_server_find_free_server
 **
 ** Description      find free server for BLE server application
 **
 ** Parameters
 **
 ** Returns          positive number(include 0) if successful, error code otherwise
 **
 *******************************************************************************/
int app_ble_server_find_free_server(void)
{
    int index;

    for (index = 0; index < BSA_BLE_SERVER_MAX; index++)
    {
        if (!app_ble_cb.ble_server[index].enabled)
        {
            return index;
        }
    }
    return -1;
}

/*******************************************************************************
 **
 ** Function         app_ble_server_find_free_attr
 **
 ** Description      find free attr for BLE server application
 **
 ** Parameters
 **
 ** Returns          positive number(include 0) if successful, error code otherwise
 **
 *******************************************************************************/
int app_ble_server_find_free_attr(UINT16 server)
{
    int index;

    for (index = 0; index < BSA_BLE_ATTRIBUTE_MAX; index++)
    {
        if (!app_ble_cb.ble_server[server].attr[index].attr_UUID.uu.uuid16)
        {
            return index;
        }
    }
    return -1;
}

/*******************************************************************************
 **
 ** Function         app_ble_server_display
 **
 ** Description      display BLE server
 **
 ** Parameters
 **
 ** Returns          void
 **
 *******************************************************************************/
void app_ble_server_display(void)
{
    int index, attr_num;

    APP_INFO0("*************** BLE SERVER LIST *****************"); 
    for (index = 0; index < BSA_BLE_SERVER_MAX; index++)
    {
        if (app_ble_cb.ble_server[index].enabled)
        {
            APP_INFO1("%d:BLE Server server_if:%d", index,
                       app_ble_cb.ble_server[index].server_if);
            for (attr_num = 0; attr_num < BSA_BLE_ATTRIBUTE_MAX ; attr_num++)
            {
                if (app_ble_cb.ble_server[index].attr[attr_num].attr_UUID.uu.uuid16)
                {
                    if ((app_ble_cb.ble_server[index].attr[attr_num].attr_type == BSA_GATTC_ATTR_TYPE_SRVC) ||
                       (app_ble_cb.ble_server[index].attr[attr_num].attr_type == BSA_GATTC_ATTR_TYPE_INCL_SRVC))
                    {
                        APP_INFO1("\t attr_num:%d:uuid:0x%04x, is_pri:%d, service_id:%d attr_id:%d",
                            attr_num,
                            app_ble_cb.ble_server[index].attr[attr_num].attr_UUID.uu.uuid16,
                            app_ble_cb.ble_server[index].attr[attr_num].is_pri,
                            app_ble_cb.ble_server[index].attr[attr_num].service_id,
                            app_ble_cb.ble_server[index].attr[attr_num].attr_id);
                    }
                    else
                    {
                        APP_INFO1("\t\t attr_num:%d:uuid:0x%04x, is_pri:%d, service_id:%d attr_id:%d",
                            attr_num,
                            app_ble_cb.ble_server[index].attr[attr_num].attr_UUID.uu.uuid16,
                            app_ble_cb.ble_server[index].attr[attr_num].is_pri,
                            app_ble_cb.ble_server[index].attr[attr_num].service_id,
                            app_ble_cb.ble_server[index].attr[attr_num].attr_id);
                    }
                }
            }
        }
    }
    APP_INFO0("*************** BLE SERVER LIST END *************");
}

/*******************************************************************************
 **
 ** Function         app_ble_server_find_reg_pending_index
 **
 ** Description      find registration pending index
 **
 ** Parameters
 **
 ** Returns          positive number(include 0) if successful, error code otherwise
 **
 *******************************************************************************/
int app_ble_server_find_reg_pending_index(void)
{
    int index;

    for (index = 0; index < BSA_BLE_SERVER_MAX; index++)
    {
        if ((app_ble_cb.ble_server[index].enabled) &&
         (app_ble_cb.ble_server[index].server_if == BSA_BLE_INVALID_IF))
        {
            return index;
        }
    }
    return -1;
}

/*******************************************************************************
 **
 ** Function         app_ble_server_find_index_by_interface
 **
 ** Description      find BLE server index by interface 
 **
 ** Parameters    if_num: interface number
 **
 ** Returns          positive number(include 0) if successful, error code otherwise
 **
 *******************************************************************************/
int app_ble_server_find_index_by_interface(tBSA_BLE_IF if_num)
{
    int index;

    for (index = 0; index < BSA_BLE_SERVER_MAX; index++)
    {
        if (app_ble_cb.ble_server[index].server_if == if_num)
        {
            return index;
        }
    }
    return -1;
}

/*******************************************************************************
 **
 ** Function         app_ble_server_find_index_by_conn_id
 **
 ** Description      find BLE server index by connection ID
 **
 ** Parameters       conn_id: Connection ID
 **
 ** Returns          positive number(include 0) if successful, error code otherwise
 **
 *******************************************************************************/
int app_ble_server_find_index_by_conn_id(UINT16 conn_id)
{
    int index;

    for(index = 0; index < BSA_BLE_CLIENT_MAX ; index++)
    {
        if(app_ble_cb.ble_server[index].conn_id == conn_id)
        {
            return index;
        }
    }
    return -1;
}

/*
 * BLE Server functions
 */
/*******************************************************************************
 **
 ** Function        app_ble_server_register
 **
 ** Description     Register server app
 **
 ** Parameters      None
 **
 ** Returns         status: 0 if success / -1 otherwise
 **
 *******************************************************************************/
int app_ble_server_register(UINT16 uuid, tBSA_BLE_CBACK *p_cback)
{
    tBSA_STATUS status;
    tBSA_BLE_SE_REGISTER ble_register_param;
    UINT16 choice;
    int server_num;

    server_num = app_ble_server_find_free_server();
    if (server_num < 0)
    {
        APP_ERROR0("No more spaces!!");
        return -1;
    }

    if (!uuid)
    {
        APP_INFO0("Bluetooth BLE register menu:");
        choice = app_get_choice("Register app UUID(eg. x9999)");
    }
    else
    {
        choice = uuid;
    }

    status = BSA_BleSeAppRegisterInit(&ble_register_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAppRegisterInit failed status = %d", status);
        return -1;
    }

    ble_register_param.uuid.len = 2;
    ble_register_param.uuid.uu.uuid16 = choice;
    if (p_cback == NULL)
    {
        ble_register_param.p_cback = app_ble_server_profile_cback;
    }
    else
    {
        ble_register_param.p_cback = p_cback;
    }
    
    //BTM_BLE_SEC_NONE: No authentication and no encryption
    //BTM_BLE_SEC_ENCRYPT: encrypt the link with current key
    //BTM_BLE_SEC_ENCRYPT_NO_MITM: unauthenticated encryption
    //BTM_BLE_SEC_ENCRYPT_MITM: authenticated encryption
    ble_register_param.sec_act = BTM_BLE_SEC_NONE;

    status = BSA_BleSeAppRegister(&ble_register_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAppRegister failed status = %d", status);
        return -1;
    }
    app_ble_cb.ble_server[server_num].enabled = TRUE;
    app_ble_cb.ble_server[server_num].server_if = ble_register_param.server_if;
    APP_INFO1("enabled:%d, server_if:%d", app_ble_cb.ble_server[server_num].enabled,
                    app_ble_cb.ble_server[server_num].server_if);
    return 0;
}

/*******************************************************************************
 **
 ** Function        app_ble_server_deregister
 **
 ** Description     Deregister server app
 **
 ** Parameters      None
 **
 ** Returns         status: 0 if success / -1 otherwise
 **
 *******************************************************************************/
int app_ble_server_deregister(void)
{
    tBSA_STATUS status;
    tBSA_BLE_SE_DEREGISTER ble_deregister_param;
    int num;

    APP_INFO0("Bluetooth BLE deregister menu:");
    APP_INFO0("Select Server:");
    app_ble_server_display();
    num = app_get_choice("Select");
    if ((num < 0) || (num >= BSA_BLE_SERVER_MAX))
    {
        APP_ERROR1("Wrong server number! = %d", num);
        return -1;
    }
    if (app_ble_cb.ble_server[num].enabled != TRUE)
    {
        APP_ERROR1("Server was not registered! = %d", num);
        return -1;
    }

    status = BSA_BleSeAppDeregisterInit(&ble_deregister_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAppDeregisterInit failed status = %d", status);
        return -1;
    }

    ble_deregister_param.server_if = app_ble_cb.ble_server[num].server_if;

    status = BSA_BleSeAppDeregister(&ble_deregister_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAppDeregister failed status = %d", status);
        return -1;
    }

    return 0;
}

/*******************************************************************************
 **
 ** Function        app_ble_server_create_service
 **
 ** Description     create service
 **
 ** Parameters      None
 **
 ** Returns         status: 0 if success / -1 otherwise
 **
 *******************************************************************************/
int app_ble_server_create_service(void)
{
    tBSA_STATUS status;
    tBSA_BLE_SE_CREATE ble_create_param;
    UINT16 service;
    UINT16  num_handle;
    BOOLEAN  is_primary;
    int server_num, attr_num;

    APP_INFO0("Select Server:");
    app_ble_server_display();
    server_num = app_get_choice("Select");
    if ((server_num < 0) || (server_num >= BSA_BLE_SERVER_MAX))
    {
        APP_ERROR1("Wrong server number! = %d", server_num);
        return -1;
    }
    if (app_ble_cb.ble_server[server_num].enabled != TRUE)
    {
        APP_ERROR1("Server was not enabled! = %d", server_num);
        return -1;
    }

    service = app_get_choice("Enter Service UUID to create(eg. x180A)");
    if (!service)
    {
        APP_ERROR1("wrong value = %d", service);
        return -1;
    }

    APP_INFO0("Enter num of handle(x2) to create.");
    APP_INFO0("\tFor Example, if you will add 5 characteristics in this service");
    APP_INFO0("\tUse 12 (1 service x 2 + 5 characteristics x 2)");
    num_handle = app_get_choice("Enter num of handle");
    if (!num_handle)
    {
        APP_ERROR1("wrong value = %d", num_handle);
        return -1;
    }
    is_primary = app_get_choice("Select primary(1) or not(0)");
    if (!(is_primary == 0) && !(is_primary == 1))
    {
        APP_ERROR1("wrong value = %d", is_primary);
        return -1;
    }
    attr_num = app_ble_server_find_free_attr(server_num);
    if (attr_num < 0)
    {
        APP_ERROR1("Wrong attr number! = %d", attr_num);
        return -1;
    }
    status = BSA_BleSeCreateServiceInit(&ble_create_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeCreateServiceInit failed status = %d", status);
        return -1;
    }

    ble_create_param.service_uuid.uu.uuid16 = service;
    ble_create_param.service_uuid.len = 2;
    ble_create_param.server_if = app_ble_cb.ble_server[server_num].server_if;
    ble_create_param.num_handle = num_handle;
    if (is_primary != 0)
    {
        ble_create_param.is_primary = TRUE;
    }
    else
    {
        ble_create_param.is_primary = FALSE;
    }

    app_ble_cb.ble_server[server_num].attr[attr_num].wait_flag = TRUE;

    status = BSA_BleSeCreateService(&ble_create_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeCreateService failed status = %d", status);
        app_ble_cb.ble_server[server_num].attr[attr_num].wait_flag = FALSE;
        return -1;
    }

    /* store information on control block */
    app_ble_cb.ble_server[server_num].attr[attr_num].attr_UUID.len = 2;
    app_ble_cb.ble_server[server_num].attr[attr_num].attr_UUID.uu.uuid16 = service;
    app_ble_cb.ble_server[server_num].attr[attr_num].is_pri = ble_create_param.is_primary;
    app_ble_cb.ble_server[server_num].attr[attr_num].attr_type = BSA_GATTC_ATTR_TYPE_SRVC;
    return 0;
}

/*******************************************************************************
 **
 ** Function        app_ble_server_add_char
 **
 ** Description     Add character to service
 **
 ** Parameters      None
 **
 ** Returns         status: 0 if success / -1 otherwise
 **
 *******************************************************************************/
int app_ble_server_add_char(void)
{
    tBSA_STATUS status;
    tBSA_BLE_SE_ADDCHAR ble_addchar_param;
    UINT16      char_uuid;
    int server_num, srvc_attr_num, char_attr_num;
    int attribute_permission;
    int characteristic_property = 0;
    int is_descript;

    APP_INFO0("Select Server:");
    app_ble_server_display();
    server_num = app_get_choice("Select");
    if ((server_num < 0) || (server_num >= BSA_BLE_SERVER_MAX))
    {
        APP_ERROR1("Wrong server number! = %d", server_num);
        return -1;
    }
    if (app_ble_cb.ble_server[server_num].enabled != TRUE)
    {
        APP_ERROR1("Server was not enabled! = %d", server_num);
        return -1;
    }

    APP_INFO0("Select service's attribute number");
    srvc_attr_num = app_get_choice("Select");

    if(srvc_attr_num < 0)
    {
        APP_ERROR0("app_ble_server_add_char : Invalid srvc_attr_num entered");
        return -1;
    }

    char_attr_num = app_ble_server_find_free_attr(server_num);

    char_uuid = app_get_choice("Add char UUID(eg. x9999)");

    status = BSA_BleSeAddCharInit(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddCharInit failed status = %d", status);
        return -1;
    }
    ble_addchar_param.service_id = app_ble_cb.ble_server[server_num].attr[srvc_attr_num].service_id;
    ble_addchar_param.char_uuid.len = 2;
    ble_addchar_param.char_uuid.uu.uuid16 = char_uuid;

    is_descript = app_get_choice("Select descriptor? (yes=1 or no=0)");

    if(is_descript)
    {
        ble_addchar_param.is_descr = TRUE;

        APP_INFO0("Enter Attribute Permissions[Eg: Read-0x1, Write-0x10, Read|Write-0x11]");
        attribute_permission = app_get_choice("Enter");
        ble_addchar_param.perm = attribute_permission;
    }
    else
    {
        ble_addchar_param.is_descr = FALSE;

        APP_INFO0("Enter Attribute Permissions[Eg: Read-0x1, Write-0x10, Read|Write-0x11]");
        attribute_permission = app_get_choice("Enter");
        ble_addchar_param.perm = attribute_permission;

        APP_INFO0("Enter Characterisic Properties Eg: WRITE-0x08, READ-0x02, Notify-0x10, Indicate-0x20");
        APP_INFO0("Eg: For READ|WRITE|NOTIFY|INDICATE enter 0x3A");
        characteristic_property = app_get_choice("Enter");
        ble_addchar_param.property = characteristic_property;
    }

    app_ble_cb.ble_server[server_num].attr[char_attr_num].wait_flag = TRUE;
    status = BSA_BleSeAddChar(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddChar failed status = %d", status);
        return -1;
    }

    app_ble_server_add_uuid_index(char_uuid, char_attr_num, server_num);

    /* save all information */
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.len = 2;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.uu.uuid16 = char_uuid;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].prop = characteristic_property;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_type = BSA_GATTC_ATTR_TYPE_CHAR;

    return 0;
}

/*******************************************************************************
 **
 ** Function        app_ble_server_start_service
 **
 ** Description     Start Service
 **
 ** Parameters      None
 **
 ** Returns         status: 0 if success / -1 otherwise
 **
 *******************************************************************************/
int app_ble_server_start_service(void)
{
    tBSA_STATUS status;
    tBSA_BLE_SE_START ble_start_param;
    int num, attr_num;

    APP_INFO0("Select Server:");
    app_ble_server_display();
    num = app_get_choice("Select");
    if ((num < 0) || (num >= BSA_BLE_SERVER_MAX))
    {
        APP_ERROR1("Wrong server number! = %d", num);
        return -1;
    }
    if (app_ble_cb.ble_server[num].enabled != TRUE)
    {
        APP_ERROR1("Server was not enabled! = %d", num);
        return -1;
    }

    APP_INFO0("Select Service's attribute number :");
    attr_num = app_get_choice("Select");

    if(attr_num < 0)
    {
        APP_ERROR0("app_ble_server_start_service : Invalid attr_num entered");
        return -1;
    }

    status = BSA_BleSeStartServiceInit(&ble_start_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeStartServiceInit failed status = %d", status);
        return -1;
    }

    ble_start_param.service_id = app_ble_cb.ble_server[num].attr[attr_num].service_id;
    ble_start_param.sup_transport = BSA_BLE_GATT_TRANSPORT_LE_BR_EDR;

    APP_INFO1("service_id:%d, num:%d", ble_start_param.service_id, num);

    status = BSA_BleSeStartService(&ble_start_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeStartService failed status = %d", status);
        return -1;
    }
    return 0;
}

/*******************************************************************************
 **
 ** Function        app_ble_server_stop_service
 **
 ** Description     Stop Service
 **
 ** Parameters      None
 **
 ** Returns         status: 0 if success / -1 otherwise
 **
 *******************************************************************************/
int app_ble_server_stop_service(void)
{
    tBSA_STATUS status;
    tBSA_BLE_SE_STOP ble_stop_param;
    int num, attr_num;

    APP_INFO0("Select Server:");
    app_ble_server_display();
    num = app_get_choice("Select");
    if ((num < 0) || (num >= BSA_BLE_SERVER_MAX))
    {
        APP_ERROR1("Wrong server number! = %d", num);
        return -1;
    }
    if (app_ble_cb.ble_server[num].enabled != TRUE)
    {
        APP_ERROR1("Server was not enabled! = %d", num);
        return -1;
    }

    APP_INFO0("Select Service's attribute number :");
    attr_num = app_get_choice("Select");

    if(attr_num < 0)
    {
        APP_ERROR0("app_ble_server_stop_service : Invalid attr_num entered");
        return -1;
    }

    status = BSA_BleSeStopServiceInit(&ble_stop_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeStopServiceInit failed status = %d", status);
        return -1;
    }

    ble_stop_param.service_id = app_ble_cb.ble_server[num].attr[attr_num].service_id;

    APP_INFO1("service_id:%d, num:%d", ble_stop_param.service_id, num);

    status = BSA_BleSeStopService(&ble_stop_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeStopService failed status = %d", status);
        return -1;
    }
    return 0;
}

/*******************************************************************************
 **
 ** Function        app_ble_server_send_indication
 **
 ** Description     Send indication to client
 **
 ** Parameters      None
 **
 ** Returns         status: 0 if success / -1 otherwise
 **
 *******************************************************************************/
int app_ble_server_send_indication(void)
{
    tBSA_STATUS status;
    tBSA_BLE_SE_SENDIND ble_sendind_param;
    int num, length_of_data, index, attr_num;

    APP_INFO0("Select Server:");
    app_ble_server_display();
    num = app_get_choice("Select");
    if ((num < 0) || (num >= BSA_BLE_SERVER_MAX))
    {
        APP_ERROR1("Wrong server number! = %d", num);
        return -1;
    }
    if (app_ble_cb.ble_server[num].enabled != TRUE)
    {
        APP_ERROR1("Server was not enabled! = %d", num);
        return -1;
    }
    if(app_ble_cb.ble_server[num].congested)
    {
        APP_ERROR1("fail : congested(%d)!", app_ble_cb.ble_server[num].congested);
        return -1;
    }

    APP_INFO0("Select Service's attribute number :");
    if (-1 == (attr_num = app_get_choice("Select")))
        return -1;

    status = BSA_BleSeSendIndInit(&ble_sendind_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeSendIndInit failed status = %d", status);
        return -1;
    }

    ble_sendind_param.conn_id = app_ble_cb.ble_server[num].conn_id;
    ble_sendind_param.attr_id = app_ble_cb.ble_server[num].attr[attr_num].attr_id;

    length_of_data = app_get_choice("Enter length of data");
    ble_sendind_param.data_len = length_of_data;

    for (index = 0; index < length_of_data ; index++)
    {
        ble_sendind_param.value[index] = app_get_choice("Enter data in byte");
    }

    ble_sendind_param.need_confirm = FALSE;

    status = BSA_BleSeSendInd(&ble_sendind_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeSendInd failed status = %d", status);
        return -1;
    }

    return 0;
}

/*******************************************************************************
 **
 ** Function        app_ble_server_start_battery_service
 **
 ** Description     Send indication to client
 **
 ** Parameters      None
 **
 ** Returns         status: 0 if success / -1 otherwise
 **
 *******************************************************************************/
int app_ble_server_start_battery_service(void)
{
    tBSA_STATUS status;
    tBSA_BLE_SE_REGISTER ble_register_param;
    UINT16 server_app_uuid = 0x8888;               //server app uuid
    tBSA_BLE_SE_CREATE ble_create_param;
    UINT16 service_uuid = BSA_BLE_UUID_SERVCLASS_BATTERY_SERVICE;    //service uuid
    UINT16 num_handle = 5;
    BOOLEAN  is_primary_service = TRUE;
    UINT16 char_uuid = BSA_BLE_GATT_UUID_BATTERY_LEVEL;
    int characteristic_property = 0x3A;
    int server_num, srvc_attr_num, char_attr_num;
    tBSA_BLE_SE_ADDCHAR ble_addchar_param;
    tBSA_BLE_SE_START ble_start_param;
    UINT16 delay_ms = 100;

    static BOOLEAN s_is_battery_service_started = FALSE;

    if (s_is_battery_service_started)
    {
        APP_ERROR1("%s battery service is started already!", __func__);
        return 0;
    }

    //1.  register a server app
    server_num = app_ble_server_find_free_server();
    if (server_num < 0)
    {
        APP_ERROR0("No more spaces!!");
        return -1;
    }

    status = BSA_BleSeAppRegisterInit(&ble_register_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAppRegisterInit failed status = %d", status);
        return -1;
    }

    ble_register_param.uuid.len = 2;
    ble_register_param.uuid.uu.uuid16 = server_app_uuid;

    ble_register_param.p_cback = app_ble_server_profile_cback;

    ble_register_param.sec_act = BTM_BLE_SEC_NONE;

    status = BSA_BleSeAppRegister(&ble_register_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAppRegister failed status = %d", status);
        return -1;
    }
    app_ble_cb.ble_server[server_num].enabled = TRUE;
    app_ble_cb.ble_server[server_num].server_if = ble_register_param.server_if;
    APP_INFO1("enabled:%d, server_if:%d", app_ble_cb.ble_server[server_num].enabled,
                    app_ble_cb.ble_server[server_num].server_if);
    usleep(delay_ms * 1000);

    //2. create a battery service 0x180F
    if ((server_num < 0) || (server_num >= BSA_BLE_SERVER_MAX))
    {
        APP_ERROR1("Wrong server number! = %d", server_num);
        return -1;
    }

    srvc_attr_num = app_ble_server_find_free_attr(server_num);
    if (srvc_attr_num < 0)
    {
        APP_ERROR1("Wrong attr number! = %d", srvc_attr_num);
        return -1;
    }
    status = BSA_BleSeCreateServiceInit(&ble_create_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeCreateServiceInit failed status = %d", status);
        return -1;
    }

    ble_create_param.service_uuid.uu.uuid16 = service_uuid;
    ble_create_param.service_uuid.len = 2;
    ble_create_param.server_if = app_ble_cb.ble_server[server_num].server_if;
    ble_create_param.num_handle = num_handle;
    ble_create_param.is_primary = is_primary_service;

    app_ble_cb.ble_server[server_num].attr[srvc_attr_num].wait_flag = TRUE;

    status = BSA_BleSeCreateService(&ble_create_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeCreateService failed status = %d", status);
        app_ble_cb.ble_server[server_num].attr[srvc_attr_num].wait_flag = FALSE;
        return -1;
    }

    /* store information on control block */
    app_ble_cb.ble_server[server_num].attr[srvc_attr_num].attr_UUID.len = 2;
    app_ble_cb.ble_server[server_num].attr[srvc_attr_num].attr_UUID.uu.uuid16 = service_uuid;
    app_ble_cb.ble_server[server_num].attr[srvc_attr_num].is_pri = ble_create_param.is_primary;
    app_ble_cb.ble_server[server_num].attr[srvc_attr_num].attr_type = BSA_GATTC_ATTR_TYPE_SRVC;
    usleep(delay_ms * 1000);

    //3. add battery level characteristic 0x2A19
    char_attr_num = app_ble_server_find_free_attr(server_num);
    app_ble_server_add_uuid_index(char_uuid, char_attr_num, server_num);

    status = BSA_BleSeAddCharInit(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddCharInit failed status = %d", status);
        return -1;
    }
    ble_addchar_param.service_id = app_ble_cb.ble_server[server_num].attr[srvc_attr_num].service_id;
    ble_addchar_param.char_uuid.len = 2;
    ble_addchar_param.char_uuid.uu.uuid16 = char_uuid;

    ble_addchar_param.is_descr = FALSE;
    ble_addchar_param.perm = BSA_GATT_PERM_READ;
    ble_addchar_param.property = BSA_GATT_CHAR_PROP_BIT_READ | BSA_GATT_CHAR_PROP_BIT_NOTIFY;

    app_ble_cb.ble_server[server_num].attr[char_attr_num].wait_flag = TRUE;
    status = BSA_BleSeAddChar(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddChar failed status = %d", status);
        return -1;
    }

    /* save all information */
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.len = 2;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.uu.uuid16 = char_uuid;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].prop = BSA_GATT_CHAR_PROP_BIT_READ | BSA_GATT_CHAR_PROP_BIT_NOTIFY;;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_type = BSA_GATTC_ATTR_TYPE_CHAR;
    usleep(delay_ms * 1000);


    //4. add battery level characteristic descriptor 0x2901
    char_attr_num = app_ble_server_find_free_attr(server_num);
    char_uuid = BSA_BLE_GATT_UUID_CHAR_DESCRIPTION;
    app_ble_server_add_uuid_index(char_uuid, char_attr_num, server_num);

    status = BSA_BleSeAddCharInit(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddCharInit failed status = %d", status);
        return -1;
    }
    ble_addchar_param.service_id = app_ble_cb.ble_server[server_num].attr[srvc_attr_num].service_id;
    ble_addchar_param.char_uuid.len = 2;
    ble_addchar_param.char_uuid.uu.uuid16 = char_uuid;

    ble_addchar_param.is_descr = TRUE;
    ble_addchar_param.perm = BSA_GATT_PERM_READ;

    app_ble_cb.ble_server[server_num].attr[char_attr_num].wait_flag = TRUE;
    status = BSA_BleSeAddChar(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddChar failed status = %d", status);
        return -1;
    }

    /* save all information */
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.len = 2;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.uu.uuid16 = char_uuid;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_type = BSA_GATTC_ATTR_TYPE_CHAR_DESCR;
    usleep(delay_ms * 1000);

    //5. add battery level characteristic descriptor 0x2902
    char_attr_num = app_ble_server_find_free_attr(server_num);
    char_uuid = BSA_BLE_GATT_UUID_CHAR_CLIENT_CONFIG;
    app_ble_server_add_uuid_index(char_uuid, char_attr_num, server_num);

    status = BSA_BleSeAddCharInit(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddCharInit failed status = %d", status);
        return -1;
    }
    ble_addchar_param.service_id = app_ble_cb.ble_server[server_num].attr[srvc_attr_num].service_id;
    ble_addchar_param.char_uuid.len = 2;
    ble_addchar_param.char_uuid.uu.uuid16 = char_uuid;

    ble_addchar_param.is_descr = TRUE;
    ble_addchar_param.perm = BSA_GATT_PERM_READ;

    app_ble_cb.ble_server[server_num].attr[char_attr_num].wait_flag = TRUE;
    status = BSA_BleSeAddChar(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddChar failed status = %d", status);
        return -1;
    }

    /* save all information */
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.len = 2;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.uu.uuid16 = char_uuid;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_type = BSA_GATTC_ATTR_TYPE_CHAR_DESCR;
    usleep(delay_ms * 1000);

    //6. start service
    status = BSA_BleSeStartServiceInit(&ble_start_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeStartServiceInit failed status = %d", status);
        return -1;
    }

    ble_start_param.service_id = app_ble_cb.ble_server[server_num].attr[srvc_attr_num].service_id;
    ble_start_param.sup_transport = BSA_BLE_GATT_TRANSPORT_LE;

    APP_INFO1("service_id:%d, num:%d", ble_start_param.service_id, srvc_attr_num);

    status = BSA_BleSeStartService(&ble_start_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeStartService failed status = %d", status);
        return -1;
    }

    s_is_battery_service_started = TRUE;

    return 0;
}

/*******************************************************************************
 **
 ** Function        app_ble_server_start_device_info_service
 **
 ** Description     Send indication to client
 **
 ** Parameters      None
 **
 ** Returns         status: 0 if success / -1 otherwise
 **
 *******************************************************************************/
int app_ble_server_start_device_info_service(void)
{
    tBSA_STATUS status;
    tBSA_BLE_SE_REGISTER ble_register_param;
    UINT16 server_app_uuid = 0x8111;               //server app uuid
    tBSA_BLE_SE_CREATE ble_create_param;
    UINT16 service_uuid = BSA_BLE_UUID_SERVCLASS_DEVICE_INFORMATION;    //device information service uuid
    UINT16 num_handle = 12;
    BOOLEAN  is_primary_service = TRUE;
    UINT16 char_uuid = BSA_BLE_GATT_UUID_MANU_NAME; //manufacturer name characristic
    int characteristic_property = 0x3A;
    int server_num, srvc_attr_num, char_attr_num;
    tBSA_BLE_SE_ADDCHAR ble_addchar_param;
    tBSA_BLE_SE_START ble_start_param;
    UINT16 delay_ms = 100;
    static BOOLEAN s_is_device_info_service_started = FALSE;

    if (s_is_device_info_service_started)
    {
        APP_ERROR1("%s device information service is started already!", __func__);
        return 0;
    }

    //1.  register a server app
    server_num = app_ble_server_find_free_server();
    if (server_num < 0)
    {
        APP_ERROR0("No more spaces!!");
        return -1;
    }

    status = BSA_BleSeAppRegisterInit(&ble_register_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAppRegisterInit failed status = %d", status);
        return -1;
    }

    ble_register_param.uuid.len = 2;
    ble_register_param.uuid.uu.uuid16 = server_app_uuid;

    ble_register_param.p_cback = app_ble_server_profile_cback;

    ble_register_param.sec_act = BTM_BLE_SEC_NONE;

    status = BSA_BleSeAppRegister(&ble_register_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAppRegister failed status = %d", status);
        return -1;
    }
    app_ble_cb.ble_server[server_num].enabled = TRUE;
    app_ble_cb.ble_server[server_num].server_if = ble_register_param.server_if;
    APP_INFO1("enabled:%d, server_if:%d", app_ble_cb.ble_server[server_num].enabled,
                    app_ble_cb.ble_server[server_num].server_if);
    usleep(delay_ms * 1000);

    //2. create a device information service 0x180A
    if ((server_num < 0) || (server_num >= BSA_BLE_SERVER_MAX))
    {
        APP_ERROR1("Wrong server number! = %d", server_num);
        return -1;
    }

    srvc_attr_num = app_ble_server_find_free_attr(server_num);
    if (srvc_attr_num < 0)
    {
        APP_ERROR1("Wrong attr number! = %d", srvc_attr_num);
        return -1;
    }
    status = BSA_BleSeCreateServiceInit(&ble_create_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeCreateServiceInit failed status = %d", status);
        return -1;
    }

    ble_create_param.service_uuid.uu.uuid16 = service_uuid;
    ble_create_param.service_uuid.len = 2;
    ble_create_param.server_if = app_ble_cb.ble_server[server_num].server_if;
    ble_create_param.num_handle = num_handle;
    ble_create_param.is_primary = is_primary_service;

    app_ble_cb.ble_server[server_num].attr[srvc_attr_num].wait_flag = TRUE;

    status = BSA_BleSeCreateService(&ble_create_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeCreateService failed status = %d", status);
        app_ble_cb.ble_server[server_num].attr[srvc_attr_num].wait_flag = FALSE;
        return -1;
    }

    /* store information on control block */
    app_ble_cb.ble_server[server_num].attr[srvc_attr_num].attr_UUID.len = 2;
    app_ble_cb.ble_server[server_num].attr[srvc_attr_num].attr_UUID.uu.uuid16 = service_uuid;
    app_ble_cb.ble_server[server_num].attr[srvc_attr_num].is_pri = ble_create_param.is_primary;
    app_ble_cb.ble_server[server_num].attr[srvc_attr_num].attr_type = BSA_GATTC_ATTR_TYPE_SRVC;
    usleep(delay_ms * 1000);

    //3. add manufacturer name characteristic 0x2A29
    char_attr_num = app_ble_server_find_free_attr(server_num);
    app_ble_server_add_uuid_index(char_uuid, char_attr_num, server_num);

    status = BSA_BleSeAddCharInit(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddCharInit failed status = %d", status);
        return -1;
    }
    ble_addchar_param.service_id = app_ble_cb.ble_server[server_num].attr[srvc_attr_num].service_id;
    ble_addchar_param.char_uuid.len = 2;
    ble_addchar_param.char_uuid.uu.uuid16 = char_uuid;

    ble_addchar_param.is_descr = FALSE;
    ble_addchar_param.perm = BSA_GATT_PERM_READ;
    ble_addchar_param.property = BSA_GATT_CHAR_PROP_BIT_READ;

    app_ble_cb.ble_server[server_num].attr[char_attr_num].wait_flag = TRUE;
    status = BSA_BleSeAddChar(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddChar failed status = %d", status);
        return -1;
    }

    /* save all information */
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.len = 2;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.uu.uuid16 = char_uuid;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].prop = BSA_GATT_CHAR_PROP_BIT_READ;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_type = BSA_GATTC_ATTR_TYPE_CHAR;
    usleep(delay_ms * 1000);

    //4. add model number characteristic 0x2A24
    char_attr_num = app_ble_server_find_free_attr(server_num);
    char_uuid = BSA_BLE_GATT_UUID_MODEL_NUMBER_STR;
    app_ble_server_add_uuid_index(char_uuid, char_attr_num, server_num);

    status = BSA_BleSeAddCharInit(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddCharInit failed status = %d", status);
        return -1;
    }
    ble_addchar_param.service_id = app_ble_cb.ble_server[server_num].attr[srvc_attr_num].service_id;
    ble_addchar_param.char_uuid.len = 2;
    ble_addchar_param.char_uuid.uu.uuid16 = char_uuid;

    ble_addchar_param.is_descr = FALSE;
    ble_addchar_param.perm = BSA_GATT_PERM_READ;
    ble_addchar_param.property = BSA_GATT_CHAR_PROP_BIT_READ;

    app_ble_cb.ble_server[server_num].attr[char_attr_num].wait_flag = TRUE;
    status = BSA_BleSeAddChar(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddChar failed status = %d", status);
        return -1;
    }

    /* save all information */
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.len = 2;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.uu.uuid16 = char_uuid;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].prop = BSA_GATT_CHAR_PROP_BIT_READ;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_type = BSA_GATTC_ATTR_TYPE_CHAR;
    usleep(delay_ms * 1000);

    //5. add serial number characteristic descriptor 0x2A25
    char_attr_num = app_ble_server_find_free_attr(server_num);
    char_uuid = BSA_BLE_GATT_UUID_SERIAL_NUMBER_STR;
    app_ble_server_add_uuid_index(char_uuid, char_attr_num, server_num);

    status = BSA_BleSeAddCharInit(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddCharInit failed status = %d", status);
        return -1;
    }
    ble_addchar_param.service_id = app_ble_cb.ble_server[server_num].attr[srvc_attr_num].service_id;
    ble_addchar_param.char_uuid.len = 2;
    ble_addchar_param.char_uuid.uu.uuid16 = char_uuid;

    ble_addchar_param.is_descr = FALSE;
    ble_addchar_param.perm = BSA_GATT_PERM_READ;
    ble_addchar_param.property = BSA_GATT_CHAR_PROP_BIT_READ;

    app_ble_cb.ble_server[server_num].attr[char_attr_num].wait_flag = TRUE;
    status = BSA_BleSeAddChar(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddChar failed status = %d", status);
        return -1;
    }

    /* save all information */
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.len = 2;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.uu.uuid16 = char_uuid;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].prop = BSA_GATT_CHAR_PROP_BIT_READ;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_type = BSA_GATTC_ATTR_TYPE_CHAR;
    usleep(delay_ms * 1000);

    //6. add hardware revision characteristic descriptor 0x2A26
    char_attr_num = app_ble_server_find_free_attr(server_num);
    char_uuid = BSA_BLE_GATT_UUID_FW_VERSION_STR;
    app_ble_server_add_uuid_index(char_uuid, char_attr_num, server_num);

    status = BSA_BleSeAddCharInit(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddCharInit failed status = %d", status);
        return -1;
    }
    ble_addchar_param.service_id = app_ble_cb.ble_server[server_num].attr[srvc_attr_num].service_id;
    ble_addchar_param.char_uuid.len = 2;
    ble_addchar_param.char_uuid.uu.uuid16 = char_uuid;

    ble_addchar_param.is_descr = FALSE;
    ble_addchar_param.perm = BSA_GATT_PERM_READ;
    ble_addchar_param.property = BSA_GATT_CHAR_PROP_BIT_READ;

    app_ble_cb.ble_server[server_num].attr[char_attr_num].wait_flag = TRUE;
    status = BSA_BleSeAddChar(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddChar failed status = %d", status);
        return -1;
    }

    /* save all information */
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.len = 2;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.uu.uuid16 = char_uuid;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].prop = BSA_GATT_CHAR_PROP_BIT_READ;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_type = BSA_GATTC_ATTR_TYPE_CHAR;
    usleep(delay_ms * 1000);

    //7. add software revision characteristic descriptor 0x2A28
    char_attr_num = app_ble_server_find_free_attr(server_num);
    char_uuid = BSA_BLE_GATT_UUID_SW_VERSION_STR;
    app_ble_server_add_uuid_index(char_uuid, char_attr_num, server_num);

    status = BSA_BleSeAddCharInit(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddCharInit failed status = %d", status);
        return -1;
    }
    ble_addchar_param.service_id = app_ble_cb.ble_server[server_num].attr[srvc_attr_num].service_id;
    ble_addchar_param.char_uuid.len = 2;
    ble_addchar_param.char_uuid.uu.uuid16 = char_uuid;

    ble_addchar_param.is_descr = FALSE;
    ble_addchar_param.perm = BSA_GATT_PERM_READ;
    ble_addchar_param.property = BSA_GATT_CHAR_PROP_BIT_READ;

    app_ble_cb.ble_server[server_num].attr[char_attr_num].wait_flag = TRUE;
    status = BSA_BleSeAddChar(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddChar failed status = %d", status);
        return -1;
    }

    /* save all information */
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.len = 2;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.uu.uuid16 = char_uuid;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].prop = BSA_GATT_CHAR_PROP_BIT_READ;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_type = BSA_GATTC_ATTR_TYPE_CHAR;
    usleep(delay_ms * 1000);

    //8. add system id characteristic descriptor 0x2A23
    char_attr_num = app_ble_server_find_free_attr(server_num);
    char_uuid = BSA_BLE_GATT_UUID_SYSTEM_ID;
    app_ble_server_add_uuid_index(char_uuid, char_attr_num, server_num);

    status = BSA_BleSeAddCharInit(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddCharInit failed status = %d", status);
        return -1;
    }
    ble_addchar_param.service_id = app_ble_cb.ble_server[server_num].attr[srvc_attr_num].service_id;
    ble_addchar_param.char_uuid.len = 2;
    ble_addchar_param.char_uuid.uu.uuid16 = char_uuid;

    ble_addchar_param.is_descr = FALSE;
    ble_addchar_param.perm = BSA_GATT_PERM_READ;
    ble_addchar_param.property = BSA_GATT_CHAR_PROP_BIT_READ;

    app_ble_cb.ble_server[server_num].attr[char_attr_num].wait_flag = TRUE;
    status = BSA_BleSeAddChar(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddChar failed status = %d", status);
        return -1;
    }

    /* save all information */
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.len = 2;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.uu.uuid16 = char_uuid;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].prop = BSA_GATT_CHAR_PROP_BIT_READ;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_type = BSA_GATTC_ATTR_TYPE_CHAR;
    usleep(delay_ms * 1000);

    //9. start service
    status = BSA_BleSeStartServiceInit(&ble_start_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeStartServiceInit failed status = %d", status);
        return -1;
    }

    ble_start_param.service_id = app_ble_cb.ble_server[server_num].attr[srvc_attr_num].service_id;
    ble_start_param.sup_transport = BSA_BLE_GATT_TRANSPORT_LE;

    APP_INFO1("service_id:%d, num:%d", ble_start_param.service_id, srvc_attr_num);

    status = BSA_BleSeStartService(&ble_start_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeStartService failed status = %d", status);
        return -1;
    }

    s_is_device_info_service_started = TRUE;

    return 0;
}

/*******************************************************************************
 **
 ** Function        app_ble_server_start_device_info_service
 **
 ** Description     Send indication to client
 **
 ** Parameters      None
 **
 ** Returns         status: 0 if success / -1 otherwise
 **
 *******************************************************************************/
int app_ble_server_start_hogp_device_service(void)
{
    tBSA_STATUS status;
    tBSA_BLE_SE_REGISTER ble_register_param;
    UINT16 server_app_uuid = 0x8112;               //server app uuid
    tBSA_BLE_SE_CREATE ble_create_param;
    UINT16 service_uuid = BSA_BLE_UUID_SERVCLASS_HUMAN_INTERFACE_DEVICE;    //HID Interface Device service uuid
#if (defined(HOGP_BOOT_PROTOCOL_MODE_SUPPORTED) && (HOGP_BOOT_PROTOCOL_MODE_SUPPORTED == TRUE))
    UINT16 num_handle = 17;
#else
    UINT16 num_handle = 11;
#endif
    BOOLEAN  is_primary_service = TRUE;
    UINT16 char_uuid = BSA_BLE_GATT_UUID_HID_INFORMATION;                   //HID Information uuid
    int characteristic_property = 0x3A;
    int server_num, srvc_attr_num, char_attr_num;
    tBSA_BLE_SE_ADDCHAR ble_addchar_param;
    tBSA_BLE_SE_START ble_start_param;
    UINT16 delay_ms = 100;
    static BOOLEAN s_is_hogp_device_service_started = FALSE;
    tBSA_DM_BLE_ADV_CONFIG adv_conf;
    tBSA_DM_BLE_ADV_PARAM adv_param;

    //hogp device must include a battery service and device information device
    //scan parameters service is optional
    app_ble_server_start_battery_service();
    app_ble_server_start_device_info_service();

    if (s_is_hogp_device_service_started)
    {
        APP_ERROR1("%s device information service is started already!", __func__);
        return 0;
    }

    //1.  register a server app
    server_num = app_ble_server_find_free_server();
    if (server_num < 0)
    {
        APP_ERROR0("No more spaces!!");
        return -1;
    }

    status = BSA_BleSeAppRegisterInit(&ble_register_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAppRegisterInit failed status = %d", status);
        return -1;
    }

    ble_register_param.uuid.len = 2;
    ble_register_param.uuid.uu.uuid16 = server_app_uuid;

    ble_register_param.p_cback = app_ble_server_profile_cback;

    ble_register_param.sec_act = BTM_BLE_SEC_NONE;

    status = BSA_BleSeAppRegister(&ble_register_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAppRegister failed status = %d", status);
        return -1;
    }
    app_ble_cb.ble_server[server_num].enabled = TRUE;
    app_ble_cb.ble_server[server_num].server_if = ble_register_param.server_if;
    APP_INFO1("enabled:%d, server_if:%d", app_ble_cb.ble_server[server_num].enabled,
                    app_ble_cb.ble_server[server_num].server_if);
    usleep(delay_ms * 1000);

    //2. create a HID interface device service 0x1812
    if ((server_num < 0) || (server_num >= BSA_BLE_SERVER_MAX))
    {
        APP_ERROR1("Wrong server number! = %d", server_num);
        return -1;
    }

    srvc_attr_num = app_ble_server_find_free_attr(server_num);
    if (srvc_attr_num < 0)
    {
        APP_ERROR1("Wrong attr number! = %d", srvc_attr_num);
        return -1;
    }
    status = BSA_BleSeCreateServiceInit(&ble_create_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeCreateServiceInit failed status = %d", status);
        return -1;
    }

    ble_create_param.service_uuid.uu.uuid16 = service_uuid;
    ble_create_param.service_uuid.len = 2;
    ble_create_param.server_if = app_ble_cb.ble_server[server_num].server_if;
    ble_create_param.num_handle = num_handle;
    ble_create_param.is_primary = is_primary_service;

    app_ble_cb.ble_server[server_num].attr[srvc_attr_num].wait_flag = TRUE;

    status = BSA_BleSeCreateService(&ble_create_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeCreateService failed status = %d", status);
        app_ble_cb.ble_server[server_num].attr[srvc_attr_num].wait_flag = FALSE;
        return -1;
    }

    /* store information on control block */
    app_ble_cb.ble_server[server_num].attr[srvc_attr_num].attr_UUID.len = 2;
    app_ble_cb.ble_server[server_num].attr[srvc_attr_num].attr_UUID.uu.uuid16 = service_uuid;
    app_ble_cb.ble_server[server_num].attr[srvc_attr_num].is_pri = ble_create_param.is_primary;
    app_ble_cb.ble_server[server_num].attr[srvc_attr_num].attr_type = BSA_GATTC_ATTR_TYPE_SRVC;
    usleep(delay_ms * 1000);

    //3. add HID information characteristic 0x2A4A
    char_uuid = BSA_BLE_GATT_UUID_HID_INFORMATION;
    char_attr_num = app_ble_server_find_free_attr(server_num);
    app_ble_server_add_uuid_index(char_uuid, char_attr_num, server_num);

    status = BSA_BleSeAddCharInit(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddCharInit failed status = %d", status);
        return -1;
    }
    ble_addchar_param.service_id = app_ble_cb.ble_server[server_num].attr[srvc_attr_num].service_id;
    ble_addchar_param.char_uuid.len = 2;
    ble_addchar_param.char_uuid.uu.uuid16 = char_uuid;

    ble_addchar_param.is_descr = FALSE;
    ble_addchar_param.perm = BSA_GATT_PERM_READ;
    ble_addchar_param.property = BSA_GATT_CHAR_PROP_BIT_READ;

    app_ble_cb.ble_server[server_num].attr[char_attr_num].wait_flag = TRUE;
    status = BSA_BleSeAddChar(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddChar failed status = %d", status);
        return -1;
    }

    /* save all information */
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.len = 2;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.uu.uuid16 = char_uuid;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].prop = BSA_GATT_CHAR_PROP_BIT_READ;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_type = BSA_GATTC_ATTR_TYPE_CHAR;
    usleep(delay_ms * 1000);

    //4. add report map characteristic 0x2A4B
    char_attr_num = app_ble_server_find_free_attr(server_num);
    char_uuid = BSA_BLE_GATT_UUID_HID_REPORT_MAP;
    app_ble_server_add_uuid_index(char_uuid, char_attr_num, server_num);

    status = BSA_BleSeAddCharInit(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddCharInit failed status = %d", status);
        return -1;
    }
    ble_addchar_param.service_id = app_ble_cb.ble_server[server_num].attr[srvc_attr_num].service_id;
    ble_addchar_param.char_uuid.len = 2;
    ble_addchar_param.char_uuid.uu.uuid16 = char_uuid;

    ble_addchar_param.is_descr = FALSE;
    ble_addchar_param.perm = BSA_GATT_PERM_READ;
    ble_addchar_param.property = BSA_GATT_CHAR_PROP_BIT_READ;

    app_ble_cb.ble_server[server_num].attr[char_attr_num].wait_flag = TRUE;
    status = BSA_BleSeAddChar(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddChar failed status = %d", status);
        return -1;
    }

    /* save all information */
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.len = 2;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.uu.uuid16 = char_uuid;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].prop = BSA_GATT_CHAR_PROP_BIT_READ;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_type = BSA_GATTC_ATTR_TYPE_CHAR;
    usleep(delay_ms * 1000);

    //5. add report characteristic 0x2A4D
    char_attr_num = app_ble_server_find_free_attr(server_num);
    char_uuid = BSA_BLE_GATT_UUID_HID_REPORT;
    app_ble_server_add_uuid_index(char_uuid, char_attr_num, server_num);

    status = BSA_BleSeAddCharInit(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddCharInit failed status = %d", status);
        return -1;
    }
    ble_addchar_param.service_id = app_ble_cb.ble_server[server_num].attr[srvc_attr_num].service_id;
    ble_addchar_param.char_uuid.len = 2;
    ble_addchar_param.char_uuid.uu.uuid16 = char_uuid;

    ble_addchar_param.is_descr = FALSE;
    ble_addchar_param.perm = BSA_GATT_PERM_READ;
    ble_addchar_param.property = BSA_GATT_CHAR_PROP_BIT_READ | BSA_GATT_CHAR_PROP_BIT_NOTIFY;

    app_ble_cb.ble_server[server_num].attr[char_attr_num].wait_flag = TRUE;
    status = BSA_BleSeAddChar(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddChar failed status = %d", status);
        return -1;
    }

    /* save all information */
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.len = 2;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.uu.uuid16 = char_uuid;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].prop = BSA_GATT_CHAR_PROP_BIT_READ | BSA_GATT_CHAR_PROP_BIT_NOTIFY;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_type = BSA_GATTC_ATTR_TYPE_CHAR;
    usleep(delay_ms * 1000);

    //6. add report characteristic descriptor 0x2902
    char_attr_num = app_ble_server_find_free_attr(server_num);
    char_uuid = BSA_BLE_GATT_UUID_CHAR_CLIENT_CONFIG;
    app_ble_server_add_uuid_index(char_uuid, char_attr_num, server_num);

    status = BSA_BleSeAddCharInit(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddCharInit failed status = %d", status);
        return -1;
    }
    ble_addchar_param.service_id = app_ble_cb.ble_server[server_num].attr[srvc_attr_num].service_id;
    ble_addchar_param.char_uuid.len = 2;
    ble_addchar_param.char_uuid.uu.uuid16 = char_uuid;

    ble_addchar_param.is_descr = TRUE;
    ble_addchar_param.perm = BSA_GATT_PERM_READ | BSA_GATT_PERM_WRITE;

    app_ble_cb.ble_server[server_num].attr[char_attr_num].wait_flag = TRUE;
    status = BSA_BleSeAddChar(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddChar failed status = %d", status);
        return -1;
    }

    /* save all information */
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.len = 2;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.uu.uuid16 = char_uuid;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_type = BSA_GATTC_ATTR_TYPE_CHAR_DESCR;
    usleep(delay_ms * 1000);

    //7. add report reference characteristic descriptor 0x2908
    char_attr_num = app_ble_server_find_free_attr(server_num);
    char_uuid = BSA_BLE_GATT_UUID_REPORT_REFERENCE;
    app_ble_server_add_uuid_index(char_uuid, char_attr_num, server_num);

    status = BSA_BleSeAddCharInit(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddCharInit failed status = %d", status);
        return -1;
    }
    ble_addchar_param.service_id = app_ble_cb.ble_server[server_num].attr[srvc_attr_num].service_id;
    ble_addchar_param.char_uuid.len = 2;
    ble_addchar_param.char_uuid.uu.uuid16 = char_uuid;

    ble_addchar_param.is_descr = TRUE;
    ble_addchar_param.perm = BSA_GATT_PERM_READ;

    app_ble_cb.ble_server[server_num].attr[char_attr_num].wait_flag = TRUE;
    status = BSA_BleSeAddChar(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddChar failed status = %d", status);
        return -1;
    }

    /* save all information */
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.len = 2;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.uu.uuid16 = char_uuid;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_type = BSA_GATTC_ATTR_TYPE_CHAR_DESCR;
    usleep(delay_ms * 1000);

    //8. add protocol mode characteristic 0x2A4E
    char_attr_num = app_ble_server_find_free_attr(server_num);
    char_uuid = BSA_BLE_GATT_UUID_HID_PROTO_MODE;
    app_ble_server_add_uuid_index(char_uuid, char_attr_num, server_num);

    status = BSA_BleSeAddCharInit(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddCharInit failed status = %d", status);
        return -1;
    }
    ble_addchar_param.service_id = app_ble_cb.ble_server[server_num].attr[srvc_attr_num].service_id;
    ble_addchar_param.char_uuid.len = 2;
    ble_addchar_param.char_uuid.uu.uuid16 = char_uuid;

    ble_addchar_param.is_descr = FALSE;
    ble_addchar_param.perm = BSA_GATT_PERM_READ | BSA_GATT_PERM_WRITE;
    ble_addchar_param.property = BSA_GATT_CHAR_PROP_BIT_READ | BSA_GATT_CHAR_PROP_BIT_WRITE_NR;

    app_ble_cb.ble_server[server_num].attr[char_attr_num].wait_flag = TRUE;
    status = BSA_BleSeAddChar(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddChar failed status = %d", status);
        return -1;
    }

    /* save all information */
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.len = 2;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.uu.uuid16 = char_uuid;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].prop = BSA_GATT_CHAR_PROP_BIT_READ | BSA_GATT_CHAR_PROP_BIT_WRITE_NR;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_type = BSA_GATTC_ATTR_TYPE_CHAR;
    usleep(delay_ms * 1000);

#if (defined(HOGP_BOOT_PROTOCOL_MODE_SUPPORTED) && (HOGP_BOOT_PROTOCOL_MODE_SUPPORTED == TRUE))
    //x. add Boot Keyboard Input Report characteristic 0x2A22
    char_attr_num = app_ble_server_find_free_attr(server_num);
    char_uuid = BSA_BLE_GATT_UUID_HID_BT_KB_INPUT;
    app_ble_server_add_uuid_index(char_uuid, char_attr_num, server_num);

    status = BSA_BleSeAddCharInit(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddCharInit failed status = %d", status);
        return -1;
    }
    ble_addchar_param.service_id = app_ble_cb.ble_server[server_num].attr[srvc_attr_num].service_id;
    ble_addchar_param.char_uuid.len = 2;
    ble_addchar_param.char_uuid.uu.uuid16 = char_uuid;

    ble_addchar_param.is_descr = FALSE;
    ble_addchar_param.perm = BSA_GATT_PERM_READ;
    ble_addchar_param.property = BSA_GATT_CHAR_PROP_BIT_READ | BSA_GATT_CHAR_PROP_BIT_NOTIFY;

    app_ble_cb.ble_server[server_num].attr[char_attr_num].wait_flag = TRUE;
    status = BSA_BleSeAddChar(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddChar failed status = %d", status);
        return -1;
    }

    /* save all information */
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.len = 2;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.uu.uuid16 = char_uuid;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].prop = BSA_GATT_CHAR_PROP_BIT_READ | BSA_GATT_CHAR_PROP_BIT_NOTIFY;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_type = BSA_GATTC_ATTR_TYPE_CHAR;
    usleep(delay_ms * 1000);

    //x. add Boot Keyboard Output Report 0x2A32
    char_attr_num = app_ble_server_find_free_attr(server_num);
    char_uuid = BSA_BLE_GATT_UUID_HID_BT_KB_OUTPUT;
    app_ble_server_add_uuid_index(char_uuid, char_attr_num, server_num);

    status = BSA_BleSeAddCharInit(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddCharInit failed status = %d", status);
        return -1;
    }
    ble_addchar_param.service_id = app_ble_cb.ble_server[server_num].attr[srvc_attr_num].service_id;
    ble_addchar_param.char_uuid.len = 2;
    ble_addchar_param.char_uuid.uu.uuid16 = char_uuid;

    ble_addchar_param.is_descr = FALSE;
    ble_addchar_param.perm = BSA_GATT_PERM_READ | BSA_GATT_PERM_WRITE;
    ble_addchar_param.property = BSA_GATT_CHAR_PROP_BIT_READ | BSA_GATT_CHAR_PROP_BIT_WRITE | BSA_GATT_CHAR_PROP_BIT_WRITE_NR;

    app_ble_cb.ble_server[server_num].attr[char_attr_num].wait_flag = TRUE;
    status = BSA_BleSeAddChar(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddChar failed status = %d", status);
        return -1;
    }

    /* save all information */
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.len = 2;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.uu.uuid16 = char_uuid;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].prop = BSA_GATT_CHAR_PROP_BIT_READ | BSA_GATT_CHAR_PROP_BIT_WRITE | BSA_GATT_CHAR_PROP_BIT_WRITE_NR;;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_type = BSA_GATTC_ATTR_TYPE_CHAR;
    usleep(delay_ms * 1000);

    //x. add Boot Mouse Input Report characteristic 0x2A33
    char_attr_num = app_ble_server_find_free_attr(server_num);
    char_uuid = BSA_BLE_GATT_UUID_HID_BT_MOUSE_INPUT;
    app_ble_server_add_uuid_index(char_uuid, char_attr_num, server_num);

    status = BSA_BleSeAddCharInit(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddCharInit failed status = %d", status);
        return -1;
    }
    ble_addchar_param.service_id = app_ble_cb.ble_server[server_num].attr[srvc_attr_num].service_id;
    ble_addchar_param.char_uuid.len = 2;
    ble_addchar_param.char_uuid.uu.uuid16 = char_uuid;

    ble_addchar_param.is_descr = FALSE;
    ble_addchar_param.perm = BSA_GATT_PERM_READ;
    ble_addchar_param.property = BSA_GATT_CHAR_PROP_BIT_READ | BSA_GATT_CHAR_PROP_BIT_NOTIFY;

    app_ble_cb.ble_server[server_num].attr[char_attr_num].wait_flag = TRUE;
    status = BSA_BleSeAddChar(&ble_addchar_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeAddChar failed status = %d", status);
        return -1;
    }

    /* save all information */
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.len = 2;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_UUID.uu.uuid16 = char_uuid;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].prop = BSA_GATT_CHAR_PROP_BIT_READ | BSA_GATT_CHAR_PROP_BIT_NOTIFY;
    app_ble_cb.ble_server[server_num].attr[char_attr_num].attr_type = BSA_GATTC_ATTR_TYPE_CHAR;
    usleep(delay_ms * 1000);
#endif

    //9. start service
    status = BSA_BleSeStartServiceInit(&ble_start_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeStartServiceInit failed status = %d", status);
        return -1;
    }

    ble_start_param.service_id = app_ble_cb.ble_server[server_num].attr[srvc_attr_num].service_id;
    ble_start_param.sup_transport = BSA_BLE_GATT_TRANSPORT_LE;

    APP_INFO1("service_id:%d, num:%d", ble_start_param.service_id, srvc_attr_num);

    status = BSA_BleSeStartService(&ble_start_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeStartService failed status = %d", status);
        return -1;
    }
    usleep(delay_ms * 1000);

    //set LE adv parameters and data, then start LE advd
    memset(&adv_param, 0, sizeof(tBSA_DM_BLE_ADV_PARAM));
    adv_param.adv_int_min = 64;        //64x0.625=40ms
    adv_param.adv_int_max = 64;        //64x0.625=40ms
    app_dm_set_ble_adv_param(&adv_param);
    usleep(delay_ms * 1000);

    memset(&adv_conf, 0, sizeof(tBSA_DM_BLE_ADV_CONFIG));
    adv_conf.flag = BSA_DM_BLE_LIMIT_DISC_FLAG | BSA_DM_BLE_BREDR_NOT_SPT;
    adv_conf.adv_data_mask = BSA_DM_BLE_AD_BIT_FLAGS | BSA_DM_BLE_AD_BIT_SERVICE
        | BSA_DM_BLE_AD_BIT_TX_PWR | BSA_DM_BLE_AD_BIT_DEV_NAME | BSA_DM_BLE_AD_BIT_APPEARANCE;
    adv_conf.tx_power = 5;
    adv_conf.appearance_data = 0x0180;    //0x0180: Generic Remote Control, 0x03c1: HID keyboard, 0x03c2: HID mouse
    adv_conf.num_service = 1;
    adv_conf.uuid_val[0] = BSA_BLE_UUID_SERVCLASS_HUMAN_INTERFACE_DEVICE;        //HID service
    adv_conf.is_scan_rsp = 0;
    app_dm_set_ble_adv_data(&adv_conf);
    usleep(delay_ms * 1000);

    app_dm_set_ble_visibility(TRUE, TRUE);
    usleep(delay_ms * 1000);

    s_is_hogp_device_service_started = TRUE;

    return 0;
}


/*******************************************************************************
 **
 ** Function        app_ble_server_send_key_by_hogp
 **
 ** Description     Send indication to client
 **
 ** Parameters      None
 **
 ** Returns         status: 0 if success / -1 otherwise
 **
 *******************************************************************************/
int app_ble_server_send_key_by_hogp(void)
{
    tBSA_STATUS status;
    tBSA_BLE_SE_SENDIND ble_sendind_param;
    int num, attr_num;
    int c;

    APP_INFO0("Please select Hogp device(uuid:0x1812) server's num:");
    app_ble_server_display();
    num = app_get_choice("Select");
    if ((num < 0) || (num >= BSA_BLE_SERVER_MAX))
    {
        APP_ERROR1("Wrong server number! = %d", num);
        return -1;
    }
    if (app_ble_cb.ble_server[num].enabled != TRUE)
    {
        APP_ERROR1("Server was not enabled! = %d", num);
        return -1;
    }
    if(app_ble_cb.ble_server[num].congested)
    {
        APP_ERROR1("fail : congested(%d)!", app_ble_cb.ble_server[num].congested);
        return -1;
    }

    status = BSA_BleSeSendIndInit(&ble_sendind_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeSendIndInit failed status = %d", status);
        return -1;
    }

    ble_sendind_param.conn_id = app_ble_cb.ble_server[num].conn_id;
    //ble_sendind_param.attr_id = app_ble_cb.ble_server[num].attr[attr_num].attr_id;
    ble_sendind_param.attr_id = app_ble_server_find_handle_by_uuid(BSA_BLE_GATT_UUID_HID_REPORT);
    if (ble_sendind_param.attr_id == 0)
    {
        APP_INFO0("Please select char 0x2A4D's number :");
        if (-1 == (attr_num = app_get_choice("Select")))
            return -1;
    }

    ble_sendind_param.data_len = 8;

    APP_INFO0("You could input one key of 0~9, a~z:");
    c =getchar();
    if (c == '0')
    {
        ble_sendind_param.value[2] = 0x27;
    }
    else if (c >= '1' && c <= '9')
    {
        ble_sendind_param.value[2] = 0x1E + c -'1';
    }
    else if (c >= 'a' && c <= 'z')
    {
        ble_sendind_param.value[2] = 0x04 + c -'a';
    }
    else
    {
        APP_ERROR0("app_ble doesn't support other key value input!");
    }

    ble_sendind_param.need_confirm = FALSE;

    //send key down
    status = BSA_BleSeSendInd(&ble_sendind_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeSendInd failed status = %d", status);
        return -1;
    }

    //send key up
    memset(ble_sendind_param.value, 0, sizeof(ble_sendind_param.value));
    status = BSA_BleSeSendInd(&ble_sendind_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeSendInd failed status = %d", status);
        return -1;
    }

    return 0;
}


/*******************************************************************************
**
** Function         app_ble_server_profile_cback
**
** Description      BLE Server Profile callback.
**                  
** Returns          void
**
*******************************************************************************/
void app_ble_server_profile_cback(tBSA_BLE_EVT event,  tBSA_BLE_MSG *p_data)
{
    int num, attr_index;
    int status;
    tBSA_BLE_SE_SENDRSP send_server_resp;
    UINT8 attribute_value[BSA_BLE_MAX_ATTR_LEN]={0x11,0x22,0x33,0x44};
    UINT16 char_uuid = 0;
    UINT16 char_hndl = 0;

    UINT16 report_cfg_size = 0;
    //static UINT16 s_report_map_count = 0;

    report_cfg_size = sizeof(app_hogp_device_cfg_report);
    //s_report_map_count = report_cfg_size/22 + (report_cfg_size%22?1:0);

    APP_DEBUG1("%s event = %d", __func__, event);

    switch (event)
    {
    case BSA_BLE_SE_DEREGISTER_EVT:
        APP_INFO1("BSA_BLE_SE_DEREGISTER_EVT server_if:%d status:%d", 
            p_data->ser_deregister.server_if, p_data->ser_deregister.status);
        num = app_ble_server_find_index_by_interface(p_data->ser_deregister.server_if);
        if(num < 0)
        {
            APP_ERROR0("no deregister pending!!");
            break;
        }

        app_ble_cb.ble_server[num].server_if = BSA_BLE_INVALID_IF;
        app_ble_cb.ble_server[num].enabled = FALSE;
        for (attr_index = 0 ; attr_index < BSA_BLE_ATTRIBUTE_MAX ; attr_index++)
        {
            memset(&app_ble_cb.ble_server[num].attr[attr_index], 0, sizeof(tAPP_BLE_ATTRIBUTE));
        }

        break;

    case BSA_BLE_SE_CREATE_EVT:
        APP_INFO1("BSA_BLE_SE_CREATE_EVT server_if:%d status:%d service_id:%d",
            p_data->ser_create.server_if, p_data->ser_create.status, p_data->ser_create.service_id);

        num = app_ble_server_find_index_by_interface(p_data->ser_create.server_if);

        /* search interface number */
        if(num < 0)
        {
            APP_ERROR0("no interface!!");
            break;
        }

        /* search attribute number */
        for (attr_index = 0 ; attr_index < BSA_BLE_ATTRIBUTE_MAX ; attr_index++)
        {
            if (app_ble_cb.ble_server[num].attr[attr_index].wait_flag == TRUE)
            {
                APP_INFO1("BSA_BLE_SE_CREATE_EVT if_num:%d, attr_num:%d", num, attr_index);
                if (p_data->ser_create.status == BSA_SUCCESS)
                {
                    app_ble_cb.ble_server[num].attr[attr_index].service_id = p_data->ser_create.service_id;
                    app_ble_cb.ble_server[num].attr[attr_index].wait_flag = FALSE;
                    break;
                }
                else  /* if CREATE fail */
                {
                    memset(&app_ble_cb.ble_server[num].attr[attr_index], 0, sizeof(tAPP_BLE_ATTRIBUTE));
                    break;
                }
            }
        }
        if (attr_index >= BSA_BLE_ATTRIBUTE_MAX)
        {
            APP_ERROR0("BSA_BLE_SE_CREATE_EVT no waiting!!");
            break;
        }
        break;

    case BSA_BLE_SE_ADDCHAR_EVT:
        APP_INFO1("BSA_BLE_SE_ADDCHAR_EVT status:%d", p_data->ser_addchar.status);
        APP_INFO1("BSA_BLE_SE_ADDCHAR_EVT attr_id:%d", p_data->ser_addchar.attr_id);
        APP_INFO1("BSA_BLE_SE_ADDCHAR_EVT is_discr:%d", p_data->ser_addchar.is_discr);
        APP_INFO1("BSA_BLE_SE_ADDCHAR_EVT service_id:%d", p_data->ser_addchar.service_id);
        num = app_ble_server_find_index_by_interface(p_data->ser_addchar.server_if);

        /* search interface number */
        if(num < 0)
        {
            APP_ERROR0("no interface!!");
            break;
        }

        for (attr_index = 0 ; attr_index < BSA_BLE_ATTRIBUTE_MAX ; attr_index++)
        {
            if (app_ble_cb.ble_server[num].attr[attr_index].wait_flag == TRUE)
            {
                APP_INFO1("if_num:%d, attr_num:%d", num, attr_index);
                if (p_data->ser_addchar.status == BSA_SUCCESS)
                {
                    app_ble_server_add_hanle_by_index(p_data->ser_addchar.attr_id, attr_index, num);
                    app_ble_cb.ble_server[num].attr[attr_index].service_id = p_data->ser_addchar.service_id;
                    app_ble_cb.ble_server[num].attr[attr_index].attr_id = p_data->ser_addchar.attr_id;
                    app_ble_cb.ble_server[num].attr[attr_index].wait_flag = FALSE;
                    break;
                }
                else  /* if CREATE fail */
                {
                    memset(&app_ble_cb.ble_server[num].attr[attr_index], 0, sizeof(tAPP_BLE_ATTRIBUTE));
                    break;
                }
            }
        }
        if (attr_index >= BSA_BLE_ATTRIBUTE_MAX)
        {
            APP_ERROR0("BSA_BLE_SE_ADDCHAR_EVT no waiting!!");
            break;
        }
        break;

    case BSA_BLE_SE_START_EVT:
        APP_INFO1("BSA_BLE_SE_START_EVT status:%d", p_data->ser_start.status);
        break;

    case BSA_BLE_SE_STOP_EVT:
        APP_INFO1("BSA_BLE_SE_STOP_EVT status:%d", p_data->ser_stop.status);
        app_ble_server_clear_uuid_handle_record();
        break;

    case BSA_BLE_SE_READ_EVT:
        APP_INFO1("BSA_BLE_SE_READ_EVT status:%d", p_data->ser_read.status);
        BSA_BleSeSendRspInit(&send_server_resp);
        send_server_resp.conn_id = p_data->ser_read.conn_id;
        send_server_resp.trans_id = p_data->ser_read.trans_id;
        send_server_resp.status = p_data->ser_read.status;
        send_server_resp.handle = p_data->ser_read.handle;
        send_server_resp.offset = p_data->ser_read.offset;
        char_uuid = app_ble_server_find_uuid_by_handle(p_data->ser_read.handle);
        switch (char_uuid)
        {
        case BSA_BLE_GATT_UUID_MANU_NAME:  //manufactuer name
            send_server_resp.len = strlen("Synaptics BSA")+1;
            memcpy(send_server_resp.value, "Synaptics BSA", send_server_resp.len);
            break;
        case BSA_BLE_GATT_UUID_MODEL_NUMBER_STR:  //modle number
            send_server_resp.len = strlen("Syna Product")+1;
            memcpy(send_server_resp.value, "Syna Product", send_server_resp.len);
            break;
        case BSA_BLE_GATT_UUID_SERIAL_NUMBER_STR:  //serial number
            send_server_resp.len = strlen("123456789")+1;
            memcpy(send_server_resp.value, "123456789", send_server_resp.len);
            break;
        case BSA_BLE_GATT_UUID_FW_VERSION_STR:  //firmware revision
            send_server_resp.len = strlen("0325.001")+1;
            memcpy(send_server_resp.value, "0325.001", send_server_resp.len);
            break;
        case BSA_BLE_GATT_UUID_SW_VERSION_STR:  //software revision
            send_server_resp.len = strlen("1.0.1")+1;
            memcpy(send_server_resp.value, "1.0.1", send_server_resp.len);
            break;
        case BSA_BLE_GATT_UUID_SYSTEM_ID:  //system id
            send_server_resp.len = strlen("none")+1;
            memcpy(send_server_resp.value, "none", send_server_resp.len);
            break;
        case BSA_BLE_GATT_UUID_PNP_ID:  //PnP id
            send_server_resp.len = strlen("none")+1;
            memcpy(send_server_resp.value, "none", send_server_resp.len);
            break;
        //battery level service related chars
        case BSA_BLE_GATT_UUID_BATTERY_LEVEL:
            send_server_resp.len = 1;
            send_server_resp.value[0] = 80;   //battery level value
            break;
        case BSA_BLE_GATT_UUID_CHAR_DESCRIPTION:  //battery level
            send_server_resp.len = strlen("battery level pecentage 0-100")+1;
            memcpy(send_server_resp.value, "battery level pecentage 0-100", send_server_resp.len);
            break;
        case BSA_BLE_GATT_UUID_CHAR_CLIENT_CONFIG:  //indication enable or disable
            send_server_resp.len = 2;
            send_server_resp.value[0] = 0x01;
            break;
        //hid device service related chars
        case BSA_BLE_GATT_UUID_HID_PROTO_MODE:  //protocol mode
            send_server_resp.len = 1;
            send_server_resp.value[0] = 0x01;   //default report protocol mode
            break;
        case BSA_BLE_GATT_UUID_HID_INFORMATION:  //HID information
            send_server_resp.len = 4;
            send_server_resp.value[0] = 0x01;   //HID version number
            send_server_resp.value[1] = 0x00;   //HID version number
            send_server_resp.value[2] = 0x00;   //HID country code
            send_server_resp.value[3] = 0x02;   //HID bit 1: remote wake, bit 2: normally connectable
            break;
        case BSA_BLE_GATT_UUID_HID_REPORT_MAP:  //HID report map, send 22 bytes each time
            if (p_data->ser_read.offset == 0)
            {
                send_server_resp.len = report_cfg_size;
                memcpy(send_server_resp.value, app_hogp_device_cfg_report, report_cfg_size);
            }
            else if (p_data->ser_read.offset < report_cfg_size)
            {
                if ((report_cfg_size - p_data->ser_read.offset) >= 22)
                {
                    send_server_resp.len = 22;
                    memcpy(send_server_resp.value, &app_hogp_device_cfg_report[p_data->ser_read.offset], 22);
                }
                else
                {
                    send_server_resp.len = report_cfg_size - p_data->ser_read.offset;
                    memcpy(send_server_resp.value, &app_hogp_device_cfg_report[p_data->ser_read.offset], send_server_resp.len);
                }
            }
            else
            {
                send_server_resp.len = 1;
                send_server_resp.value[0] = 0xC0;
            }
            break;
        case BSA_BLE_GATT_UUID_HID_REPORT:  //HID report
            send_server_resp.len = 7;
            char_hndl = app_ble_server_find_handle_by_uuid(char_uuid);
            //char handle ocupies 2 bytes
            send_server_resp.value[0] = char_hndl & 0xFF;
            send_server_resp.value[1] = (char_hndl>>8) & 0xFF;
            //properties 1 byte
            send_server_resp.value[2] = BSA_GATT_CHAR_PROP_BIT_READ | BSA_GATT_CHAR_PROP_BIT_NOTIFY;
            //char handle ocupies 2 bytes
            send_server_resp.value[3] = char_hndl & 0xFF;
            send_server_resp.value[4] = (char_hndl>>8) & 0xFF;
            //char uuid 2 bytes
            send_server_resp.value[5] = char_uuid & 0xFF;
            send_server_resp.value[6] = (char_uuid>>8) & 0xFF;
            break;
        case BSA_BLE_GATT_UUID_REPORT_REFERENCE:  //report reference characteristic descriptor
            send_server_resp.len = 2;
            send_server_resp.value[0] = BTA_HD_REPT_ID_KBD;   //report ID
            send_server_resp.value[1] = 0x01;   //report type
            break;
        case BSA_BLE_GATT_UUID_HID_BT_KB_INPUT:  //boot keyboard input report
            break;
        case BSA_BLE_GATT_UUID_HID_BT_KB_OUTPUT:  //boot keyboard output report
            break;
        case BSA_BLE_GATT_UUID_HID_BT_MOUSE_INPUT:  //boot mouse output report
            break;
        default:
            send_server_resp.len = 4;
            memcpy(send_server_resp.value, attribute_value, BSA_BLE_MAX_ATTR_LEN);
            break;
        }
        send_server_resp.auth_req = GATT_AUTH_REQ_NONE;
        APP_INFO1("BSA_BLE_SE_READ_EVT: send_server_resp.conn_id:%d, send_server_resp.trans_id:%d", send_server_resp.conn_id, send_server_resp.trans_id, send_server_resp.status);
        APP_INFO1("BSA_BLE_SE_READ_EVT: send_server_resp.status:%d,send_server_resp.auth_req:%d", send_server_resp.status,send_server_resp.auth_req);
        APP_INFO1("BSA_BLE_SE_READ_EVT: send_server_resp.handle:%d, send_server_resp.offset:%d, send_server_resp.len:%d", send_server_resp.handle,send_server_resp.offset,send_server_resp.len );
        BSA_BleSeSendRsp(&send_server_resp);
        break;

    case BSA_BLE_SE_WRITE_EVT:
        APP_INFO1("BSA_BLE_SE_WRITE_EVT status:%d", p_data->ser_write.status);
        APP_DUMP("Write value", p_data->ser_write.value, p_data->ser_write.len);
        APP_INFO1("BSA_BLE_SE_WRITE_EVT trans_id:%d, conn_id:%d, handle:%d, is_prep:%d, offset:%d",
            p_data->ser_write.trans_id, p_data->ser_write.conn_id, p_data->ser_write.handle,
            p_data->ser_write.is_prep, p_data->ser_write.offset);

        if (p_data->ser_write.need_rsp)
        {
            BSA_BleSeSendRspInit(&send_server_resp);
            send_server_resp.conn_id = p_data->ser_write.conn_id;
            send_server_resp.trans_id = p_data->ser_write.trans_id;
            send_server_resp.status = p_data->ser_write.status;
            send_server_resp.handle = p_data->ser_write.handle;
            if(p_data->ser_write.is_prep)
            {
                send_server_resp.offset = p_data->ser_write.offset;
                send_server_resp.len = p_data->ser_write.len;
                memcpy(send_server_resp.value, p_data->ser_write.value, send_server_resp.len);
            }
            else
                send_server_resp.len = 0;
            APP_INFO1("BSA_BLE_SE_WRITE_EVT: send_server_resp.conn_id:%d, send_server_resp.trans_id:%d", send_server_resp.conn_id, send_server_resp.trans_id, send_server_resp.status);
            APP_INFO1("BSA_BLE_SE_WRITE_EVT: send_server_resp.status:%d,send_server_resp.auth_req:%d", send_server_resp.status,send_server_resp.auth_req);
            APP_INFO1("BSA_BLE_SE_WRITE_EVT: send_server_resp.handle:%d, send_server_resp.offset:%d, send_server_resp.len:%d", send_server_resp.handle,send_server_resp.offset,send_server_resp.len );
            BSA_BleSeSendRsp(&send_server_resp);
        }
        break;

    case BSA_BLE_SE_EXEC_WRITE_EVT:
        APP_INFO1("BSA_BLE_SE_EXEC_WRITE_EVT status:%d", p_data->ser_exec_write.status);
        APP_INFO1("BSA_BLE_SE_WRITE_EVT trans_id:%d, conn_id:%d, exec_write:%d",
            p_data->ser_exec_write.trans_id, p_data->ser_exec_write.conn_id, p_data->ser_exec_write.exec_write);

        BSA_BleSeSendRspInit(&send_server_resp);
        send_server_resp.conn_id = p_data->ser_exec_write.conn_id;
        send_server_resp.trans_id = p_data->ser_exec_write.trans_id;
        send_server_resp.status = p_data->ser_exec_write.status;
        send_server_resp.handle = 0;
        send_server_resp.len = 0;
        APP_INFO1("BSA_BLE_SE_WRITE_EVT: send_server_resp.conn_id:%d, send_server_resp.trans_id:%d", send_server_resp.conn_id, send_server_resp.trans_id, send_server_resp.status);
        APP_INFO1("BSA_BLE_SE_WRITE_EVT: send_server_resp.status:%d", send_server_resp.status);
        BSA_BleSeSendRsp(&send_server_resp);

        break;

    case BSA_BLE_SE_OPEN_EVT:
        APP_INFO1("BSA_BLE_SE_OPEN_EVT status:%d", p_data->ser_open.reason);
        if (p_data->ser_open.reason == BSA_SUCCESS)
        {
            APP_INFO1("conn_id:0x%x", p_data->ser_open.conn_id);
            num = app_ble_server_find_index_by_interface(p_data->ser_open.server_if);
            /* search interface number */
            if(num < 0)
            {
                APP_ERROR0("no interface!!");
                break;
            }
            app_ble_cb.ble_server[num].conn_id = p_data->ser_open.conn_id;

            /* XML Database update */
            app_read_xml_remote_devices();
            /* Add BLE service for this devices in XML database */
            app_xml_add_trusted_services_db(app_xml_remote_devices_db,
                    APP_NUM_ELEMENTS(app_xml_remote_devices_db), p_data->ser_open.remote_bda,
                    BSA_BLE_SERVICE_MASK);

            status = app_write_xml_remote_devices();
            if (status < 0)
            {
                APP_ERROR1("app_ble_write_remote_devices failed: %d", status);
            }
        }
        break;

    case BSA_BLE_SE_CONGEST_EVT:
        APP_INFO1("BSA_BLE_SE_CONGEST_EVT  :conn_id:0x%x, congested:%d",
            p_data->ser_congest.conn_id, p_data->ser_congest.congested);
        num = app_ble_server_find_index_by_conn_id(p_data->ser_congest.conn_id);
        if (num >= 0)
        {
            app_ble_cb.ble_server[num].congested = p_data->ser_congest.congested;
        }
        break;

    case BSA_BLE_SE_CLOSE_EVT:
        APP_INFO1("BSA_BLE_SE_CLOSE_EVT status:%d", p_data->ser_close.reason);
        APP_INFO1("conn_id:0x%x", p_data->ser_close.conn_id);
        num = app_ble_server_find_index_by_interface(p_data->ser_close.server_if);
        /* search interface number */
        if(num < 0)
        {
            APP_ERROR0("no interface!!");
            break;
        }
        app_ble_cb.ble_server[num].conn_id = BSA_BLE_INVALID_CONN;
        app_ble_cb.ble_server[num].congested = 0;
        break;

    case BSA_BLE_SE_CONF_EVT:
        APP_INFO1("BSA_BLE_SE_CONF_EVT status:%d", p_data->ser_conf.status);
        APP_INFO1("conn_id:0x%x", p_data->ser_conf.conn_id);
        break;

    case BSA_BLE_SE_MTU_EVT:
        APP_INFO1("BSA_BLE_SE_MTU_EVT conn_id:0x%x, mtu:%d",
                    p_data->ser_mtu.conn_id, p_data->ser_mtu.mtu);
        break;

    default:
        break;
    }
}


/*******************************************************************************
 **
 ** Function        app_ble_server_open
 **
 ** Description     This is the ble open connection to ble client
 **
 ** Parameters      None
 **
 ** Returns         status: 0 if success / -1 otherwise
 **
 *******************************************************************************/
int app_ble_server_open(void)
{
    tBSA_STATUS status;
    tBSA_BLE_SE_OPEN ble_open_param;
    int device_index;
    BD_ADDR bd_addr;
    int server_num;
    int direct;

    APP_INFO0("Bluetooth BLE connect menu:");
    APP_INFO0("    0 Device from XML database (already paired)");
    APP_INFO0("    1 Device found in last discovery");
    device_index = app_get_choice("Select source");
    /* Devices from XML database */
    if (device_index == 0)
    {
        /* Read the XML file which contains all the bonded devices */
        app_read_xml_remote_devices();

        app_xml_display_devices(app_xml_remote_devices_db,
                APP_NUM_ELEMENTS(app_xml_remote_devices_db));
        device_index = app_get_choice("Select device");
        if ((device_index >= 0) &&
            (device_index < APP_NUM_ELEMENTS(app_xml_remote_devices_db)) &&
            (app_xml_remote_devices_db[device_index].in_use != FALSE))
        {
            bdcpy(bd_addr, app_xml_remote_devices_db[device_index].bd_addr);
        }
        else
        {
            APP_ERROR1("Bad Device Index:%d\n", device_index);
            return -1;
        }

    }
    /* Devices from Discovery */
    else if (device_index == 1)
    {
        app_disc_display_devices();
        device_index = app_get_choice("Select device");
        if ((device_index >= 0) &&
            (device_index < APP_DISC_NB_DEVICES) &&
            (app_discovery_cb.devs[device_index].in_use != FALSE))
        {
            bdcpy(bd_addr, app_discovery_cb.devs[device_index].device.bd_addr);
        }
    }
    else
    {
        APP_ERROR0("Bad choice [XML(0) or Disc(1) only]");
        return -1;
    }

    APP_INFO0("Select Server:");
    app_ble_server_display();
    server_num = app_get_choice("Select");

    if((server_num < 0) ||
       (server_num >= BSA_BLE_SERVER_MAX) ||
       (app_ble_cb.ble_server[server_num].enabled == FALSE))
    {
        APP_ERROR1("Wrong server number! = %d", server_num);
        return -1;
    }

    if (app_ble_cb.ble_server[server_num].conn_id != BSA_BLE_INVALID_CONN)
    {
        APP_ERROR1("Connection already exist, conn_id = %d",
                app_ble_cb.ble_server[server_num].conn_id );
        return -1;
    }

    status = BSA_BleSeConnectInit(&ble_open_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeConnectInit failed status = %d", status);
        return -1;
    }

    ble_open_param.server_if = app_ble_cb.ble_server[server_num].server_if;
    direct = app_get_choice("Direct connection:1, Background connection:0");
    if(direct == 1)
    {
        ble_open_param.is_direct = TRUE;
    }
    else if(direct == 0)
    {
        ble_open_param.is_direct = FALSE;
    }
    else
    {
        APP_ERROR1("Wrong selection! = %d", direct);
        return -1;
    }
    bdcpy(ble_open_param.bd_addr, bd_addr);

    status = BSA_BleSeConnect(&ble_open_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeConnect failed status = %d", status);
        return -1;
    }

    return 0;
}

/*******************************************************************************
 **
 ** Function        app_ble_server_close
 **
 ** Description     This is the ble close connection
 **
 ** Parameters      None
 **
 ** Returns         status: 0 if success / -1 otherwise
 **
 *******************************************************************************/
int app_ble_server_close(void)
{
    tBSA_STATUS status;
    tBSA_BLE_SE_CLOSE ble_close_param;
    int server_num;

    APP_INFO0("Select Server:");
    app_ble_server_display();
    server_num = app_get_choice("Select");

    if((server_num < 0) ||
       (server_num >= BSA_BLE_SERVER_MAX) ||
       (app_ble_cb.ble_server[server_num].enabled == FALSE))
    {
        APP_ERROR1("Wrong server number! = %d", server_num);
        return -1;
    }
    status = BSA_BleSeCloseInit(&ble_close_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeCloseInit failed status = %d", status);
        return -1;
    }
    ble_close_param.conn_id = app_ble_cb.ble_server[server_num].conn_id;
    status = BSA_BleSeClose(&ble_close_param);
    if (status != BSA_SUCCESS)
    {
        APP_ERROR1("BSA_BleSeClose failed status = %d", status);
        return -1;
    }

    return 0;
}

