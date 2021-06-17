#ifndef SESSION_H_
#define SESSION_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "server_macro.h"
// #include "third_party.h"

/* session ctrl */
#define BZERO_SCTRL(SCTRL) \
    memset(SCTRL , '\0', sizeof(seion_ctrl) - (RSBUF_LENGTH * 0x02));

//

#define CREATE_SDRESP(INVAL, SCTRL) \
        prod_data sresp; \
        sresp.colen = &INVAL->content_length; \
        sresp.sedat = SCTRL->resp_data; \
        sresp.sebuf = SCTRL->send_buffer;

//
int open_authen_se(session *seion, seion_ctrl *sctrl, inte_value *inval);
#define CLOSE_AUTHEN_SE(SCTRL) { \
_LOG_TRACE("close authe session."); \
    BZERO_SCTRL(SCTRL) \
}

//
void open_kalive_se(seion_ctrl *sctrl);
#define CLOSE_KALIVE_SE(SCTRL) { \
_LOG_TRACE("close kalive session."); \
    BZERO_SCTRL(SCTRL) \
}
//
int open_status_se(seion_ctrl *sctrl, list_data *ldata, inte_value *inval);
#define CLOSE_STATUS_SE(SCTRL) { \
_LOG_TRACE("close status session."); \
    BZERO_SCTRL(SCTRL) \
}
//
int open_privile_se(seion_ctrl *sctrl, list_data *ldata, inte_value *inval);
#define CLOSE_PRIVILE_SE(SCTRL) { \
_LOG_TRACE("close privile session."); \
    BZERO_SCTRL(SCTRL) \
}
//
int open_invoke_se(seion_ctrl *sctrl, list_data *ldata, conoda *coval, inte_value *inval);
#define CLOSE_INVOKE_SE(SCTRL) { \
_LOG_TRACE("close invoke session."); \
    BZERO_SCTRL(SCTRL) \
}

int open_colle_se(seion_ctrl *sctrl, list_data *ldata, conoda *coval, inte_value *inval);
#define CLOSE_COLLE_SE(SCTRL) { \
_LOG_TRACE("close colle session."); \
    BZERO_SCTRL(SCTRL) \
}

//
int open_const_se(seion_ctrl *sctrl, list_data *ldata, inte_value *inval);
extern void (*close_const_se[]) (seion_ctrl *);

//
#define RESET_CONST_SE(SCTRL) SCTRL->rwrite_tatol = 0x0000;
#define RESET_QUERY_SE(SCTRL) SCTRL->rwrite_tatol = 0x0000;

//
int open_query_se(seion_ctrl *sctrl, list_data *ldata, inte_value *inval);
extern void (*close_query_se[]) (seion_ctrl *);

//
void open_done_se(seion_ctrl *sctrl, list_data *ldata);
#define CLOSE_DONE_SE(SCTRL) { \
_LOG_TRACE("close done session."); \
    BZERO_SCTRL(SCTRL) \
}

//
extern int _seion_loop_;

#endif /* SESSION_H_ */
