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

    typedef enum {
        OSVP_AUTHEN, // authenize initial
        OSVP_KALIVE, // keep alive
        OSVP_STATUS, // set or get osev osdb run status // osev, low-leve
        OSVP_INVOKE, // addi dele modi meth, class // leve-1, leve-2p
        OSVP_CONST,  // leve-3
        OSVP_QUERY, // select object from container // leve-4p invok object method
        OSVP_DONE // end
    } OSEV_METHOD;
    
    //

    typedef enum {
        // Informational
        CONTINUE = 100, // 100 Continue 
        SWITCHINT_PROTOCOLS = 101, // 101 Switching Protocols
        PROCESSING = 102, // * 102 Processing // WebDAV
        // Successful
        OK = 200, // 200 OK
        CREATED = 201, // 201 Created
        ACCEPTED = 202, // 202 Accepted
        // Redirection
        MULTIPLE_CHOICES = 300, // 300 Multiple Choices
        MOVED_PERMANENTLY = 301, // 301 Moved Permanently
        // Client Error
        BAD_REQUEST = 400, // 400 Bad Request
        UNAUTHORIZED = 401, // 401 Unauthenized
        FORBIDDEN = 403, // 403 Forbidden
        // Server Error
        INTERNAL_SERVER_ERROR = 500, // 500 Internal Server Error
        NOT_IMPLEMENTED = 501, // 501 Not Implemented
        BAD_GATEWAY = 502, // 502 Bad Gateway
        SERVICE_UNAVAILABLE = 503, // 503 Service Unavailable
    } STATUS_CODE;    

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

