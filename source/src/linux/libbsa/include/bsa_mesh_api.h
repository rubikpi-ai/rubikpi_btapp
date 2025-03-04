/*****************************************************************************
 **
 **  Name:          bsa_ble_api.h
 **
 **  Description:   This is the public interface file for BLE part of
 **                 the Bluetooth simplified API
 **
 **  Copyright (c) 2015-2016, Broadcom Corp., All Rights Reserved.
 **  Broadcom Bluetooth Core. Proprietary and confidential.
 **
 *****************************************************************************/
#ifndef BSA_MESH_API_H
#define BSA_MESH_API_H

/* for tBSA_STATUS */
#include "bsa_status.h"
#include "bta_gatt_api.h"
#include "bsa_dm_api.h"
#include "bta_gattc_ci.h"
#include "bsa_disc_api.h"

/*****************************************************************************
 **  Constants and Type Definitions
 *****************************************************************************/
#ifndef BSA_MESH_DEBUG
#define BSA_MESH_DEBUG TRUE
#endif

typedef tGATT_IF                   tBSA_MESH_IF;
typedef tBTA_GATTC_CHAR_ID         tBSA_MESH_CL_CHAR_ID;
typedef tBTA_GATTC_CHAR_DESCR_ID   tBSA_MESH_CL_CHAR_DESCR_ID;
typedef tBTA_GATT_ID               tBSA_MESH_ID;
typedef tBTA_GATT_READ_VAL         tBSA_MESH_READ_VAL;
typedef tBTA_GATT_REASON           tBSA_MESH_REASON;
typedef tBTA_GATT_PERM             tBSA_MESH_PERM;
typedef tBTA_GATT_CHAR_PROP        tBSA_MESH_CHAR_PROP;
typedef tBTA_GATT_TRANSPORT        tBSA_MESH_TRANSPORT;
typedef tBTA_GATTC_WRITE_TYPE      tBSA_MESH_WRITE_TYPE;

#if 0  //same with bsa_ble_api.h
/* Attribute permissions
*/
#define BSA_GATT_PERM_READ              BTA_GATT_PERM_READ              /* bit 0 -  0x0001 */
#define BSA_GATT_PERM_READ_ENCRYPTED    BTA_GATT_PERM_READ_ENCRYPTED    /* bit 1 -  0x0002 */
#define BSA_GATT_PERM_READ_ENC_MITM     BTA_GATT_PERM_READ_ENC_MITM     /* bit 2 -  0x0004 */
#define BSA_GATT_PERM_WRITE             BTA_GATT_PERM_WRITE             /* bit 4 -  0x0010 */
#define BSA_GATT_PERM_WRITE_ENCRYPTED   BTA_GATT_PERM_WRITE_ENCRYPTED   /* bit 5 -  0x0020 */
#define BSA_GATT_PERM_WRITE_ENC_MITM    BTA_GATT_PERM_WRITE_ENC_MITM    /* bit 6 -  0x0040 */
#define BSA_GATT_PERM_WRITE_SIGNED      BTA_GATT_PERM_WRITE_SIGNED      /* bit 7 -  0x0080 */
#define BSA_GATT_PERM_WRITE_SIGNED_MITM BTA_GATT_PERM_WRITE_SIGNED_MITM /* bit 8 -  0x0100 */

/* definition of characteristic properties */
#define BSA_GATT_CHAR_PROP_BIT_BROADCAST    BTA_GATT_CHAR_PROP_BIT_BROADCAST   /* 0x01 */
#define BSA_GATT_CHAR_PROP_BIT_READ         BTA_GATT_CHAR_PROP_BIT_READ        /* 0x02 */
#define BSA_GATT_CHAR_PROP_BIT_WRITE_NR     BTA_GATT_CHAR_PROP_BIT_WRITE_NR    /* 0x04 */
#define BSA_GATT_CHAR_PROP_BIT_WRITE        BTA_GATT_CHAR_PROP_BIT_WRITE       /* 0x08 */
#define BSA_GATT_CHAR_PROP_BIT_NOTIFY       BTA_GATT_CHAR_PROP_BIT_NOTIFY      /* 0x10 */
#define BSA_GATT_CHAR_PROP_BIT_INDICATE     BTA_GATT_CHAR_PROP_BIT_INDICATE    /* 0x20 */
#define BSA_GATT_CHAR_PROP_BIT_AUTH         BTA_GATT_CHAR_PROP_BIT_AUTH        /* 0x40 */
#define BSA_GATT_CHAR_PROP_BIT_EXT_PROP     BTA_GATT_CHAR_PROP_BIT_EXT_PROP    /* 0x80 */




#define BSA_GATTC_ATTR_TYPE_INCL_SRVC   BTA_GATTC_ATTR_TYPE_INCL_SRVC
#define BSA_GATTC_ATTR_TYPE_CHAR        BTA_GATTC_ATTR_TYPE_CHAR
#define BSA_GATTC_ATTR_TYPE_CHAR_DESCR  BTA_GATTC_ATTR_TYPE_CHAR_DESCR
#define BSA_GATTC_ATTR_TYPE_SRVC        BTA_GATTC_ATTR_TYPE_SRVC
typedef tBTA_GATTC_ATTR_TYPE            tBSA_GATTC_ATTR_TYPE;
#endif

#define BSA_MESH_MAX_ATTR_LEN  GATT_MAX_ATTR_LEN

/* max client application BSA BLE Client can support */
#ifndef BSA_MESH_CLIENT_MAX
#define BSA_MESH_CLIENT_MAX              3
#endif

/* max server application BSA BLE Server can support */
#define BSA_MESH_SERVER_MAX              4
#define BSA_MESH_ATTRIBUTE_MAX           50

#ifndef BSA_MESH_SERVER_SECURITY
#define BSA_MESH_SERVER_SECURITY         BTA_DM_BLE_SEC_NONE
#endif

#ifndef BSA_MESH_CLIENT_SECURITY
#define BSA_MESH_CLIENT_SECURITY         BTA_DM_BLE_SEC_NONE
#endif

#define BSA_MESH_INVALID_IF              0xFF
#define BSA_MESH_INVALID_CONN            0xFFFF


#define BSA_MESH_UUID_SERVCLASS_GAP_SERVER                   UUID_SERVCLASS_GAP_SERVER
#define BSA_MESH_UUID_SERVCLASS_GATT_SERVER                  UUID_SERVCLASS_GATT_SERVER
#define BSA_MESH_UUID_SERVCLASS_IMMEDIATE_ALERT              UUID_SERVCLASS_IMMEDIATE_ALERT
#define BSA_MESH_UUID_SERVCLASS_LINKLOSS                     UUID_SERVCLASS_LINKLOSS
#define BSA_MESH_UUID_SERVCLASS_TX_POWER                     UUID_SERVCLASS_TX_POWER
#define BSA_MESH_UUID_SERVCLASS_CURRENT_TIME                 UUID_SERVCLASS_CURRENT_TIME
#define BSA_MESH_UUID_SERVCLASS_DST_CHG                      UUID_SERVCLASS_DST_CHG
#define BSA_MESH_UUID_SERVCLASS_REF_TIME_UPD                 UUID_SERVCLASS_REF_TIME_UPD
#define BSA_MESH_UUID_SERVCLASS_GLUCOSE                      UUID_SERVCLASS_GLUCOSE
#define BSA_MESH_UUID_SERVCLASS_HEALTH_THERMOMETER           UUID_SERVCLASS_THERMOMETER
#define BSA_MESH_UUID_SERVCLASS_DEVICE_INFORMATION           UUID_SERVCLASS_DEVICE_INFO
#define BSA_MESH_UUID_SERVCLASS_NWA                          UUID_SERVCLASS_NWA
#define BSA_MESH_UUID_SERVCLASS_PHALERT                      UUID_SERVCLASS_PHALERT
#define BSA_MESH_UUID_SERVCLASS_HEART_RATE                   UUID_SERVCLASS_HEART_RATE
#define BSA_MESH_UUID_SERVCLASS_BATTERY_SERVICE              UUID_SERVCLASS_BATTERY
#define BSA_MESH_UUID_SERVCLASS_BLOOD_PRESSURE               UUID_SERVCLASS_BPM
#define BSA_MESH_UUID_SERVCLASS_ALERT_NOTIFICATION_SERVICE   UUID_SERVCLASS_ALERT_NOTIFICATION
#define BSA_MESH_UUID_SERVCLASS_HUMAN_INTERFACE_DEVICE       UUID_SERVCLASS_LE_HID
#define BSA_MESH_UUID_SERVCLASS_SCAN_PARAMETERS              UUID_SERVCLASS_SCAN_PARAM
#define BSA_MESH_UUID_SERVCLASS_RUNNING_SPEED_AND_CADENCE    UUID_SERVCLASS_RSC
#define BSA_MESH_UUID_SERVCLASS_CYCLING_SPEED_AND_CADENCE    UUID_SERVCLASS_CSC
#define BSA_MESH_UUID_SERVCLASS_TEST_SERVER                  UUID_SERVCLASS_TEST_SERVER

#define BSA_MESH_GATT_UUID_PRI_SERVICE                       GATT_UUID_PRI_SERVICE
#define BSA_MESH_GATT_UUID_SEC_SERVICE                       GATT_UUID_SEC_SERVICE
#define BSA_MESH_GATT_UUID_INCLUDE_SERVICE                   GATT_UUID_INCLUDE_SERVICE
#define BSA_MESH_GATT_UUID_CHAR_DECLARE                      GATT_UUID_CHAR_DECLARE            /*  Characteristic Declaration*/
#define BSA_MESH_GATT_UUID_CHAR_EXT_PROP                     GATT_UUID_CHAR_EXT_PROP           /*  Characteristic Extended Properties */
#define BSA_MESH_GATT_UUID_CHAR_DESCRIPTION                  GATT_UUID_CHAR_DESCRIPTION        /*  Characteristic User Description*/
#define BSA_MESH_GATT_UUID_CHAR_CLIENT_CONFIG                GATT_UUID_CHAR_CLIENT_CONFIG      /*  Client Characteristic Configuration */
#define BSA_MESH_GATT_UUID_CHAR_VALID_RANGE                  GATT_UUID_CHAR_VALID_RANGE        /*  Characteristic Valid Range */

#define BSA_MESH_GATT_UUID_CHAR_CLIENT_CONFIG_ENABLE_NOTI    0x01    /* Enable Notification of Client Characteristic Configuration, defined at bluetooth org */
#define BSA_MESH_GATT_UUID_CHAR_CLIENT_CONFIG_ENABLE_INDI    0x02    /* Enable Indication of Client Characteristic Configuration, defined at bluetooth org */

#define BSA_MESH_GATT_UUID_CHAR_SRVR_CONFIG                  GATT_UUID_CHAR_SRVR_CONFIG        /*  Server Characteristic Configuration */
#define BSA_MESH_GATT_UUID_CHAR_PRESENT_FORMAT               GATT_UUID_CHAR_PRESENT_FORMAT     /*  Characteristic Presentation Format*/
#define BSA_MESH_GATT_UUID_CHAR_AGG_FORMAT                   GATT_UUID_CHAR_AGG_FORMAT         /*  Characteristic Aggregate Format*/
#define BSA_MESH_GATT_UUID_CHAR_VALID_RANGE                  GATT_UUID_CHAR_VALID_RANGE        /*  Characteristic Valid Range */




#define BSA_MESH_GATT_TRANSPORT_LE                           GATT_TRANSPORT_LE
#define BSA_MESH_GATT_TRANSPORT_BR_EDR                       GATT_TRANSPORT_BR_EDR
#define BSA_MESH_GATT_TRANSPORT_LE_BR_EDR                    GATT_TRANSPORT_LE_BR_EDR

#define BSA_MESH_MAX_PDU_LENGTH                              251

typedef enum
{
    /* BLE Client events */
    BSA_MESH_CL_DEREGISTER_EVT,    /* BLE client is registered. */
    BSA_MESH_CL_OPEN_EVT,          /* BLE open request status  event */
    BSA_MESH_CL_READ_EVT,          /* BLE read characteristic/descriptor event */
    BSA_MESH_CL_WRITE_EVT,         /* BLE write characteristic/descriptor event */
    BSA_MESH_CL_CLOSE_EVT,         /* GATTC  close request status event */
    BSA_MESH_CL_SEARCH_CMPL_EVT,   /* GATT discovery complete event */
    BSA_MESH_CL_SEARCH_RES_EVT,    /* GATT discovery result event */
    BSA_MESH_CL_OBSERVE_EVT,
    BSA_MESH_CL_NOTIF_EVT,         /* GATT attribute notification event */
    BSA_MESH_CL_CONGEST_EVT,       /* GATT congestion/uncongestion event */
    BSA_MESH_CL_CACHE_SAVE_EVT,
    BSA_MESH_CL_CACHE_LOAD_EVT,
    BSA_MESH_CL_GET_ADV_EVT,
    BSA_MESH_CL_CFG_MTU_EVT,       /* configure MTU complete event */

} tBSA_MESH_EVT;



/* BSA BLE Client Host callback events */
/* Client callback function events */

/* callback event data for BSA_MESH_CL_OPEN_EVT event */
typedef struct
{
    tBSA_STATUS         status; /* operation status */
    UINT16              conn_id;
    tBSA_MESH_IF         client_if; /* Client interface ID */
    BD_ADDR             bd_addr;
    UINT8                elem_idx;
    UINT16               elem_unicast;
} tBSA_MESH_CL_OPEN_MSG;

/* callback event data for BSA_MESH_CL_CLOSE_EVT event */
typedef struct
{
    tBSA_STATUS         status;
    UINT16              conn_id;
    tBSA_MESH_IF         client_if;
    BD_ADDR             remote_bda;
    tBSA_MESH_REASON     reason;         /* disconnect reason code, not useful when connect event is reported */
} tBSA_MESH_CL_CLOSE_MSG;

/* callback event data for BSA_MESH_CL_DEREGISTER_EVT event */
typedef struct
{
    tBSA_STATUS         status; /* operation status */
    tBSA_MESH_IF         client_if; /* Client interface ID */
} tBSA_MESH_CL_DEREGISTER_MSG;

/* callback event data for BSA_MESH_CL_SEARCH_RES_EVT event */
typedef struct
{
    BD_ADDR             bd_addr;
    INT8   rssi;
    UINT16 oob;
    UINT8 dev_uuid[16];

} tBSA_MESH_CL_SEARCH_RES_MSG;

/* callback event data for BSA_MESH_CL_SEARCH_RES_EVT event */
typedef struct
{
    UINT8 p_eir_data[BSA_EIR_DATA_LENGTH] ;

} tBSA_MESH_CL_BEACON_MSG;

typedef struct
{
    BD_ADDR             bd_addr;
    INT8            rssi;
    BOOLEAN         eir_flag;                   /* EIR flag */
    UINT8 p_eir[BSA_EIR_DATA_LENGTH] ;

} tBSA_MESH_CL_OBSERVE_MSG;



/* callback event data for BSA_MESH_CL_SEARCH_CMPL_EVT event */
typedef struct
{
    tBSA_STATUS         status; /* operation status */
    //UINT16              conn_id;
} tBSA_MESH_CL_SEARCH_CMPL_MSG;

#define MAX_READ_LEN 100
/* callback event data for BSA_MESH_CL_READ_EVT event */
typedef struct
{
    tBSA_STATUS         status;
    UINT16              conn_id;
    tBTA_GATT_SRVC_ID   srvc_id;
    tBSA_MESH_ID         char_id;
    tBTA_GATT_ID        descr_type;
    UINT16              len;
    UINT8               value[MAX_READ_LEN];
    UINT32              mesh_opid;
    UINT16              mesh_addr;
} tBSA_MESH_CL_READ_MSG;

/* callback event data for BSA_MESH_CL_WRITE_EVT event */
typedef struct
{
    UINT16              conn_id;
    tBSA_STATUS         status;
    tBTA_GATT_SRVC_ID   srvc_id;
    tBSA_MESH_ID         char_id;
    tBTA_GATT_ID        descr_type;
} tBSA_MESH_CL_WRITE_MSG;


/* callback event data for BSA_MESH_CL_NOTIF_EVT event */
typedef struct
{
    UINT16              conn_id;
    tBSA_STATUS         status;
    BD_ADDR             bda;
    tBTA_GATTC_CHAR_ID  char_id;
    tBTA_GATT_ID        descr_type;
    UINT16              len;
    UINT8               value[BSA_MESH_MAX_ATTR_LEN];
    UINT32              mesh_opid;
    UINT16              mesh_addr;
    UINT16              unicast;
    UINT32              dst;
    BOOLEAN             is_notify;
} tBSA_MESH_CL_NOTIF_MSG;

typedef struct
{
    UINT16              conn_id;
    BOOLEAN             congested; /* congestion indicator */
}tBSA_MESH_CL_CONGEST_MSG;

#define BSA_MESH_CL_NV_LOAD_MAX   BTA_GATTC_NV_LOAD_MAX
/* callback event data for BSA_MESH_CL_CACHE_SAVE_EVT event */
/* attributes in one service */
typedef struct
{
    UINT16               evt;
    UINT16               num_attr;
    UINT16               attr_index;
    UINT16               conn_id;
    BD_ADDR              bd_addr;
    tBTA_GATTC_NV_ATTR   attr[BSA_MESH_CL_NV_LOAD_MAX];
} tBSA_MESH_CL_CACHE_SAVE_MSG;

/* callback event data for BSA_MESH_CL_CACHE_LOAD_EVT event */
typedef struct
{
    UINT16              conn_id;
    tBSA_STATUS         status;
    BD_ADDR             bd_addr;
} tBSA_MESH_CL_CACHE_LOAD_MSG;

typedef struct {
  UINT8    adv_inst_max;
  UINT8    rpa_offloading;
  UINT16   tot_scan_results_strg;
  UINT8    max_irk_list_sz;
  UINT8    filter_support;
  UINT8    max_filter;
  UINT8    energy_support;
  UINT16   version_supported;
  UINT16   total_trackable_advertisers;
  UINT8    extended_scan_support;
  UINT8    debug_logging_supported;
} tBSA_MESH_CL_CFG_ADV_ID_MSG;

/* callback event data for BSA_MESH_CL_CFG_MTU_EVT event */
typedef struct
{
    tBSA_STATUS         status;
    UINT16              conn_id;
    UINT16              mtu;
} tBSA_MESH_CL_CFG_MTU_MSG;

/* Union of data associated with HD callback */
typedef union
{
    tBSA_MESH_CL_OPEN_MSG         cli_open;          /* BSA_MESH_CL_OPEN_EVT */
    tBSA_MESH_CL_SEARCH_RES_MSG   cli_search_res;    /* BSA_MESH_CL_SEARCH_RES_EVT */
    tBSA_MESH_CL_SEARCH_CMPL_MSG  cli_search_cmpl;   /* BSA_MESH_CL_SEARCH_CMPL_EVT */
    tBSA_MESH_CL_READ_MSG         cli_read;          /* BSA_MESH_CL_READ_EVT */
    tBSA_MESH_CL_WRITE_MSG        cli_write;         /* BSA_MESH_CL_WRITE_EVT */
    tBSA_MESH_CL_NOTIF_MSG        cli_notif;         /* BSA_MESH_CL_NOTIF_EVT */
    tBSA_MESH_CL_OBSERVE_MSG      cli_observe;       /* BSA_MESH_CL_OBSERVE_EVT */
    //tBSA_MESH_CL_CONGEST_MSG    cli_congest;       /* BSA_MESH_CL_CONGEST_EVT */
    tBSA_MESH_CL_CLOSE_MSG        cli_close;         /* BSA_MESH_CL_CLOSE_EVT */
    tBSA_MESH_CL_DEREGISTER_MSG   cli_deregister;    /* BSA_MESH_CL_DEREGISTER_EVT */
    //tBSA_MESH_CL_CACHE_SAVE_MSG cli_cache_save;    /* BSA_MESH_SE_CACHE_SAVE_EVT */
    //tBSA_MESH_CL_CACHE_LOAD_MSG cli_cache_load;    /* BSA_MESH_SE_CACHE_LOAD_EVT */
    tBSA_MESH_CL_CFG_ADV_ID_MSG   cli_cfg_adv_id;    /* BSA_MESH_CL_GET_ADV_EVT */
    //tBSA_MESH_CL_CFG_MTU_MSG    cli_cfg_mtu;       /* BSA_MESH_CL_CFG_MTU_EVT */
#if 0
    tBSA_MESH_SE_DEREGISTER_MSG   ser_deregister;    /* BSA_MESH_SE_DEREGISTER_EVT */
    tBSA_MESH_SE_CREATE_MSG       ser_create;        /* BSA_MESH_SE_CREATE_EVT */
    tBSA_MESH_SE_ADDCHAR_MSG      ser_addchar;       /* BSA_MESH_SE_ADDCHAR_EVT */
    tBSA_MESH_SE_START_MSG        ser_start;         /* BSA_MESH_SE_START_EVT */
    tBSA_MESH_SE_STOP_MSG         ser_stop;          /* BSA_MESH_SE_STOP_EVT */
    tBSA_MESH_SE_READ_MSG         ser_read;          /* BSA_MESH_SE_READ_EVT */
    tBSA_MESH_SE_WRITE_MSG        ser_write;         /* BSA_MESH_SE_WRITE_EVT */
    tBSA_MESH_SE_OPEN_MSG         ser_open;          /* BSA_MESH_SE_OPEN_EVT */
    tBSA_MESH_SE_EXEC_WRITE_MSG   ser_exec_write;    /* BSA_MESH_SE_EXEC_WRITE_EVT */
    tBSA_MESH_SE_CLOSE_MSG        ser_close;         /* BSA_MESH_SE_CLOSE_EVT */
    tBSA_MESH_SE_CONGEST_MSG      ser_congest;       /* BSA_MESH_CL_CONGEST_EVT */
    tBSA_MESH_SE_CONF_MSG         ser_conf;          /* BSA_MESH_SE_CONF_EVT */
    tBSA_MESH_SE_MTU_MSG          ser_mtu;
 #endif
} tBSA_MESH_MSG;

/* BSA BLE Client callback function */
typedef void (tBSA_MESH_CBACK)(tBSA_MESH_EVT event, tBSA_MESH_MSG *p_data);

/*
 * Structures use to pass parameters to BSA API functions
 */
typedef struct
{
    int                 dummy; /* May be needed for some compilers */
} tBSA_MESH_ENABLE;

typedef struct
{
    int                 dummy; /* May be needed for some compilers */
} tBSA_MESH_DISABLE;

/*
 * Structures use to pass parameters to BSA BLE Clinet API functions
 */
typedef struct
{
    tBT_UUID            uuid;
    tBSA_MESH_IF         client_if; /* Client interface ID given by BSA*/
    tBSA_MESH_CBACK      *p_cback;

   // tBTA_DM_MESH_SEC_ACT sec_act;
    tBTA_DM_BLE_SEC_ACT sec_act;
    UINT8                  bearer_type;
} tBSA_MESH_CL_REGISTER;

typedef struct
{
    tBSA_MESH_IF         client_if;
} tBSA_MESH_CL_DEREGISTER;

typedef struct
{
    tBSA_MESH_IF         client_if;
    BD_ADDR             bd_addr;
    BOOLEAN             is_direct;
    UINT8                  bearer_type;
    UINT8                  dev_uuid[16];
} tBSA_MESH_CL_OPEN;

typedef struct
{
    UINT16              conn_id;
    UINT8                  bearer_type;
} tBSA_MESH_CL_CLOSE;

typedef struct
{
    //UINT16              conn_id;
    //tBT_UUID            uuid;
    UINT8                 bearer_type;
    UINT8                 duration;
    BOOLEAN            is_unprov_device;
    BOOLEAN            observe_abort;
} tBSA_MESH_CL_SEARCH;

typedef struct
{
    UINT16                 obs_interval;
    UINT16                 obs_window;
} tBSA_MESH_CL_SCAN_PARAM;


typedef struct
{
    UINT16              conn_id;
    tBSA_MESH_CL_CHAR_ID char_id;
    tBSA_MESH_CL_CHAR_DESCR_ID   descr_id;
    UINT8               auth_req;
    BOOLEAN             descr;
    UINT8                  bearer_type;
    UINT32            value[8];
    UINT16              cmd_id;
    UINT16            len;
} tBSA_MESH_CL_READ;

#define BSA_MESH_CL_WRITE_MAX  245

typedef struct
{
    UINT16              conn_id;
    tBSA_MESH_CL_CHAR_ID char_id;
    tBSA_MESH_WRITE_TYPE write_type;
    UINT8                  bearer_type;
    UINT16              cmd_id;
    UINT32            cmd_value[8];
    UINT16              len;
    UINT8               value[BSA_MESH_CL_WRITE_MAX];
    UINT8               auth_req;
    tBSA_MESH_CL_CHAR_DESCR_ID   descr_id;
    BOOLEAN             descr;
} tBSA_MESH_CL_WRITE;

typedef struct
{
    UINT16               conn_id;
    BOOLEAN              adv_start;
    UINT8                bearer_type;
    UINT8                inst_id;
    tBSA_DM_BLE_AD_MASK  adv_mask;
    UINT8                len;
    UINT8                value[BSA_MESH_CL_WRITE_MAX];
} tBSA_MESH_CL_ADV_CONFIG;

typedef struct {
    UINT8 id;
    UINT16 interval;
    UINT8 type;
} tBSA_MESH_CL_ADV_INST_CONFIG;

#if 0
/* Structure associated with tBSA_MESH_OBSERVE_RES */
typedef struct
{
    BD_ADDR         bd_addr;                    /* BD address peer device. */
    //DEV_CLASS       dev_class;                  /* Device class of peer device. */
    //BOOLEAN         remt_name_not_required;     /* Application sets this flag if it already knows the name of the device */
    //                                            /* If the device name is known to application BTA skips the remote name request */
    //BOOLEAN         is_limited;                 /* TRUE, if the limited inquiry bit is set in the CoD */
    //INT8            rssi;                       /* The rssi value */
    UINT8           eir[BSA_EIR_DATA_LENGTH];   /* received EIR */
    BOOLEAN         eir_flag;                   /* EIR flag */
#if (BLE_INCLUDED == TRUE)
    //UINT8               inq_result_type;
    //UINT8               ble_addr_type;
    //tBTM_BLE_EVT_TYPE   ble_evt_type;
    //tBT_DEVICE_TYPE     device_type;
#endif
} tBSA_MESH_OBSERVE_RES;
#endif
/* Discovery callback */
//typedef void ( tBSA_MESH_OBSERVE_CBACK)(tBSA_DISC_EVT event, tBSA_DISC_MSG *p_data);
//typedef void (tBTM_INQ_RESULTS_CB) (tBTM_INQ_RESULTS *p_inq_results, UINT8 *p_eir);
//typedef void (tBTM_CMPL_CB) (void *p1);


/* Inquiry Parameters */
typedef struct
{
    int duration;                       /* Multiple of 1.28 seconds */
    //tBSA_MESH_OBSERVE_CBACK *cback;             /* Callback for new devices found and completion */
    //int nb_devices;                     /* Max number of elements in devices table */
    //tBSA_DM_INQ_FILT filter_type;       /* Filter condition type */
    //tBSA_DM_INQ_COND filter_cond;       /* Filter condition data */
    //tBSA_SERVICE_MASK services;         /* Services to look for */
    //tBSA_DM_INQ_MODE mode;              /* Inquiry mode */
    //BOOLEAN device_info;                /* */
    //tBSA_DISC_BRCM_FILTER brcm_filter;  /* Broadcom specific filters */
    //BOOLEAN skip_name_request;          /* If TRUE, server will not perform any remote name request */
    //tBSA_DISC_UPDATE update;            /* Update mode */
    //INT8 inq_tx_power;                  /* Inquiry transmit power */
} tBSA_MESH_OBSERVE_START;

typedef struct
{
    int dummy; /* May be needed for some compilers */
} tBSA_MESH_OBSERVE_ABORT;




#if 1
typedef struct
{
    tBSA_MESH_IF         client_if;
    tBSA_MESH_CL_CHAR_ID notification_id;
    BD_ADDR             bd_addr;
} tBSA_MESH_CL_NOTIFREG;

typedef tBSA_MESH_CL_NOTIFREG tBSA_MESH_CL_NOTIFDEREG;

typedef struct
{
    UINT16              more;
    UINT16              num_attr;
    UINT16              attr_index;
    UINT16              conn_id;
    BD_ADDR             bd_addr;
    tBTA_GATTC_NV_ATTR  attr[BSA_MESH_CL_NV_LOAD_MAX];
} tBSA_MESH_CL_CACHE_LOAD;

typedef struct
{
    UINT16              conn_id;
    tBSA_MESH_CL_CHAR_ID char_id;
} tBSA_MESH_CL_INDCONF;

typedef struct
{
    UINT16              conn_id;
    UINT16              mtu;
} tBSA_MESH_CL_CFG_MTU;

#endif



typedef void (tMeshScanUnprovCB)(tBSA_MESH_CL_SEARCH_RES_MSG *unprov_device);
typedef void (tMeshMsgEventCB)(tBSA_MESH_EVT event,  tBSA_MESH_MSG *p_data);


typedef enum {
    MESH_SCAN_UNPROV = 1,
    MESH_SCAN_NETWORK
} tMeshScanType;

typedef struct {
    tMeshScanType scanType;  // controls what mesh devices to find.
    tMeshScanUnprovCB *pUnprovCb;
    tMeshMsgEventCB *pMsgEventCb;
}tMeshScanCb;



/*****************************************************************************
**  External Function Declarations
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 **
 ** Function         BSA_MeshClAppRegisterInit
 **
 ** Description      Initialize structure containing API parameters with default values
 **
 ** Parameters       Pointer on structure containing API parameters
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
tBSA_STATUS BSA_MeshClAppRegisterInit(tBSA_MESH_CL_REGISTER *p_reg);

/*******************************************************************************
 **
 ** Function         BSA_MeshClAppRegister
 **
 ** Description      This function is called to register client application
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
tBSA_STATUS BSA_MeshClAppRegister(tBSA_MESH_CL_REGISTER *p_reg);

/*******************************************************************************
 **
 ** Function         BSA_MeshClConnectInit
 **
 ** Description      Initialize structure containing API parameters with default values
 **
 ** Parameters       Pointer on structure containing API parameters
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
tBSA_STATUS BSA_MeshClConnectInit(tBSA_MESH_CL_OPEN *p_open);

/*******************************************************************************
 **
 ** Function         BSA_MeshClConnect
 **
 ** Description      This function is called to open an BLE connection  to a remote
 **                  device.
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
tBSA_STATUS BSA_MeshClConnect(tBSA_MESH_CL_OPEN *p_open);

/*******************************************************************************
 **
 ** Function         BSA_MeshClSearchInit
 **
 ** Description      Initialize structure containing API parameters with default values
 **
 ** Parameters       Pointer on structure containing API parameters
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
tBSA_STATUS BSA_MeshClSearchInit(tBSA_MESH_CL_SEARCH *p_search);

/*******************************************************************************
 **
 ** Function         BSA_MeshClServiceSearch
 **
 ** Description      This function is called to search service list to a remote
 **                  device.
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
tBSA_STATUS BSA_MeshClSearch(tBSA_MESH_CL_SEARCH *p_search);

/*******************************************************************************
 **
 ** Function         BSA_MeshClReadInit
 **
 ** Description      Initialize structure containing API parameters with default values
 **
 ** Parameters       Pointer on structure containing API parameters
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
tBSA_STATUS BSA_MeshClReadInit(tBSA_MESH_CL_READ *p_read);

/*******************************************************************************
 **
 ** Function         BSA_MeshClRead
 **
 ** Description      This function is called to read a data to a remote
 **                  device.
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
tBSA_STATUS BSA_MeshClRead(tBSA_MESH_CL_READ *p_read);

/*******************************************************************************
 **
 ** Function         BSA_MeshClWriteInit
 **
 ** Description      Initialize structure containing API parameters with default values
 **
 ** Parameters       Pointer on structure containing API parameters
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
tBSA_STATUS BSA_MeshClWriteInit(tBSA_MESH_CL_WRITE *p_write);

/*******************************************************************************
 **
 ** Function         BSA_MeshClWrite
 **
 ** Description      This function is called to read a data to a remote
 **                  device.
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
tBSA_STATUS BSA_MeshClWrite(tBSA_MESH_CL_WRITE *p_write);

/*******************************************************************************
 **
 ** Function         BSA_MeshClNotifRegisterInit
 **
 ** Description      Initialize structure containing API parameters with default values
 **
 ** Parameters       Pointer on structure containing API parameters
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
//tBSA_STATUS BSA_MeshClNotifRegisterInit(tBSA_MESH_CL_NOTIFREG *p_reg);

/*******************************************************************************
 **
 ** Function         BSA_MeshClNotifRegister
 **
 ** Description      This function is called to register a notification
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
//tBSA_STATUS BSA_MeshClNotifRegister(tBSA_MESH_CL_NOTIFREG *p_reg);

/*******************************************************************************
 **
 ** Function         BSA_MeshClCloseInit
 **
 ** Description      Initialize structure containing API parameters with default values
 **
 ** Parameters       Pointer on structure containing API parameters
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
tBSA_STATUS BSA_MeshClCloseInit(tBSA_MESH_CL_CLOSE *p_close);

/*******************************************************************************
 **
 ** Function         BSA_MeshClClose
 **
 ** Description      This function is called to close an BLE connection  to a remote
 **                  device.
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
tBSA_STATUS BSA_MeshClClose(tBSA_MESH_CL_CLOSE *p_close);

/*******************************************************************************
 **
 ** Function         BSA_MeshClAdvertise
 **
 ** Description      This function is called to write a data to a remote
 **                  device.
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
tBSA_STATUS BSA_MeshClAdvertise(tBSA_MESH_CL_ADV_CONFIG *p_adv);
tBSA_STATUS BSA_MeshClAdvertiseInit(tBSA_MESH_CL_ADV_CONFIG *p_adv);

/*******************************************************************************
 **
 ** Function         BSA_MeshClSetAdvertise
 **
 ** Description      This function is called to configure advertise interface.
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
tBSA_STATUS BSA_MeshClSetAdvertise(tBSA_MESH_CL_ADV_INST_CONFIG *p_adv_cfg);

/*******************************************************************************
 **
 ** Function         BSA_MeshClAppDeregisterInit
 **
 ** Description      Initialize structure containing API parameters with default values
 **
 ** Parameters       Pointer on structure containing API parameters
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
tBSA_STATUS BSA_MeshClAppDeregisterInit(tBSA_MESH_CL_DEREGISTER *p_dereg);

/*******************************************************************************
 **
 ** Function         BSA_MeshClAppDeregister
 **
 ** Description      This function is called to deregister app
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
tBSA_STATUS BSA_MeshClAppDeregister(tBSA_MESH_CL_DEREGISTER *p_dereg);

tBSA_STATUS BSA_MeshClConfigScanParamInit(tBSA_MESH_CL_SCAN_PARAM *p_scan);
tBSA_STATUS BSA_MeshClConfigScanParam(tBSA_MESH_CL_SCAN_PARAM *p_scan);
/*******************************************************************************
 **
 ** Function         BSA_MeshClNotifDeregisterInit
 **
 ** Description      Initialize structure containing API parameters with default values
 **
 ** Parameters       Pointer on structure containing API parameters
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
//tBSA_STATUS BSA_MeshClNotifDeregisterInit(tBSA_MESH_CL_NOTIFDEREG *p_dereg);

/*******************************************************************************
 **
 ** Function         BSA_MeshClNotifDeregister
 **
 ** Description      This function is called to deregister app
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
//tBSA_STATUS BSA_MeshClNotifDeregister(tBSA_MESH_CL_NOTIFDEREG *p_dereg);


/*******************************************************************************
 **
 ** Function         BSA_MeshClCacheLoadInit
 **
 ** Description      Initialize structure containing API parameters with default values
 **
 ** Parameters       Pointer on structure containing API parameters
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
//tBSA_STATUS BSA_MeshClCacheLoadInit(tBSA_MESH_CL_CACHE_LOAD *p_load);

/*******************************************************************************
 **
 ** Function         BSA_MeshClCacheLoad
 **
 ** Description      This function is called to load attribute to bsa_server
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
//tBSA_STATUS BSA_MeshClCacheLoad(tBSA_MESH_CL_CACHE_LOAD *p_load);

/*******************************************************************************
 **
 ** Function         BSA_MeshClIndConfInit
 **
 ** Description      Initialize structure containing API parameters with default values
 **
 ** Parameters       Pointer on structure containing API parameters
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
//tBSA_STATUS BSA_MeshClIndConfInit(tBSA_MESH_CL_INDCONF *p_indc);

/*******************************************************************************
 **
 ** Function         BSA_MeshClIndConf
 **
 ** Description      This function is called to send a confirmation to a remote
 **                  device.
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
//tBSA_STATUS BSA_MeshClIndConf(tBSA_MESH_CL_INDCONF *p_indc);

/*******************************************************************************
 **
 ** Function         BSA_MeshClCfgMtuInit
 **
 ** Description      Initialize structure containing API parameters with default values
 **
 ** Parameters       Pointer on structure containing API parameters
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
//tBSA_STATUS BSA_MeshClCfgMtuInit(tBSA_MESH_CL_CFG_MTU *p_cfg);

/*******************************************************************************
 **
 ** Function         BSA_MeshClCfgMtu
 **
 ** Description      This function is called to configure BLE MTU.
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
//tBSA_STATUS BSA_MeshClCfgMtu(tBSA_MESH_CL_CFG_MTU *p_cfg);

/*******************************************************************************
 **
 ** Function         BSA_MeshEnableInit
 **
 ** Description      Initialize structure containing API parameters with default values
 **
 ** Parameters       Pointer on structure containing API parameters
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
tBSA_STATUS BSA_MeshEnableInit(tBSA_MESH_ENABLE *p_enable);

/*******************************************************************************
 **
 ** Function         BSA_MeshEnable
 **
 ** Description      This function enable MESH
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
tBSA_STATUS BSA_MeshEnable(tBSA_MESH_ENABLE *p_enable);

/*******************************************************************************
 **
 ** Function         BSA_MeshDisableInit
 **
 ** Description      Initialize structure containing API parameters with default values
 **
 ** Parameters       Pointer on structure containing API parameters
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
tBSA_STATUS BSA_MeshDisableInit(tBSA_MESH_DISABLE *p_disable);

/*******************************************************************************
 **
 ** Function         BSA_MeshDisable
 **
 ** Description      This function disable MESH
 **
 ** Returns          tBSA_STATUS
 **
 *******************************************************************************/
tBSA_STATUS BSA_MeshDisable(tBSA_MESH_DISABLE *p_disable);

#ifdef __cplusplus
}
#endif

#endif
