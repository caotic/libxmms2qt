/* This header contains defines that will be used if libxmms2qt is compiled
 * against xmms2 DrL or older. It is only used internally and can change at
 * any time.
 */

#include <xmmsc/xmmsc_idnumbers.h>

#ifdef HAVE_XMMSV
#undef
#define HAVE_XMMSV 1
#else
#define HAVE_XMMSV (XMMS_IPC_PROTOCOL_VERSION >= 13)
#endif


#if HAVE_XMMSV
#include <xmmsc/xmmsv.h>
#else
// #define XMMSV_TYPE_NONE
// #define XMMSV_TYPE_ERROR
#define XMMSV_TYPE_UINT32  XMMS_OBJECT_CMD_ARG_UINT32
#define XMMSV_TYPE_INT32   XMMS_OBJECT_CMD_ARG_INT32
#define XMMSV_TYPE_STRING  XMMS_OBJECT_CMD_ARG_STRING
#define XMMSV_TYPE_COLL    XMMS_OBJECT_CMD_ARG_COLL
#define XMMSV_TYPE_BIN     XMMS_OBJECT_CMD_ARG_BIN
#define XMMSV_TYPE_LIST    XMMS_OBJECT_CMD_ARG_LIST
#define XMMSV_TYPE_DICT    XMMS_OBJECT_CMD_ARG_DICT

#endif
