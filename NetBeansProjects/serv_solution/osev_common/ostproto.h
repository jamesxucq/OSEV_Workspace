#ifndef OSTPPROTO_H
#define	OSTPPROTO_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_macro.h"
// #include "requ_conne.h"
    
    // server ostp method
// OSEV_METHOD
#define OSVP_AUTHEN     0x00 // authenize initial
#define OSVP_KALIVE     0x01 // keep alive
#define OSVP_STATUS     0x02 // set or get osev osdb run status // osev, low-leve
#define OSVP_PRIVI      0x03    
#define OSVP_INVOKEx     0x04 // addi dele modi meth // leve-1
#define OSVP_COLLE     0x05 // addi dele modi class // leve-2p
#define OSVP_CONST      0x06 // leve-3
#define OSVP_QUERY      0x07 // select object from container // leve-4p invok object method
#define OSVP_DONE       0x08 // end
    
    //
// STATUS_CODE
        // Informational
#define CONTINUE                0x10 // 100 Continue 
#define SWITCHINT_PROTOCOLS     0x11 // 101 Switching Protocols
#define PROCESSING              0x12 // * 102 Processing // WebDAV
        // Successful
#define OK                      0x20 // 200 OK
#define CREATED                 0x21 // 201 Created
#define ACCEPTED                0x22 // 202 Accepted
        // Redirection
#define MULTIPLE_CHOICES        0x30 // 300 Multiple Choices
#define MOVED_PERMANENTLY       0x31 // 301 Moved Permanently
        // Client Error
#define BAD_REQUEST             0x40 // 400 Bad Request
#define UNAUTHORIZED            0x41 // 401 Unauthenized
#define FORBIDDEN               0x43 // 403 Forbidden
        // Server Error
#define INTERNAL_SERVER_ERROR   0x50 // 500 Internal Server Error
#define NOT_IMPLEMENTED         0x51 // 501 Not Implemented
#define BAD_GATEWAY             0x52 // 502 Bad Gateway
#define SERVICE_UNAVAILABLE     0x53 // 503 Service Unavailable   

//

#define OSTP_EVDAT_HDBD(EVDAT, EVD) { \
    (EVDAT)->type_ptr = (EVD)->buffer; \
    (EVDAT)->hlen = sizeof(requ_tyle_t); \
    (EVDAT)->value_ptr = (EVD)->buffer + sizeof(requ_tyle_t); \
    (EVDAT)->blen = (EVD)->rsleng - sizeof(requ_tyle_t); \
}

#define OSTP_EVDAT_BODY(EVDAT, EVD) { \
    (EVDAT)->value_ptr = (EVD)->buffer; \
    (EVDAT)->blen = (EVD)->rsleng; \
}
    
//
#define OSTP_EVDAT_INIT(EVDAT, EVD) { \
    (EVDAT)->type_ptr = (EVD)->buffer; \
    (EVDAT)->hlen = 0x00; \
    (EVDAT)->value_ptr = (EVD)->buffer; \
    (EVDAT)->blen = EVD_SOCKET_BUFF; \
}
    
#define OSTP_EVDAT_END(EVDAT, EVD) { \
    (EVD)->sleng = 0x00; \
    (EVD)->rsleng = (EVDAT)->hlen + (EVDAT)->blen; \
}
    
    //
#define PROTO_METHOD(METHOD, HEADER) METHOD = ((requ_tyle_t *)HEADER)->method
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* OSTPPROTO_H */

