#ifndef _SERVER_MACRO_H_
#define	_SERVER_MACRO_H_

#ifdef	__cplusplus
extern "C" {
#endif
//

//
#define DEFAULT_HOST_PORT 8888
#define DEFAULT_CONTENT_LENGTH (100 * 1024) /* bytes */
#define DEFAULT_KEEP_ALIVE 5 /* seconds */
#define DEFAULT_MAX_CONNECTION_AGE 300 /* seconds */
#define BUG_REPORT_EMAIL "james.xucq@gmail.com"

#define OBJE_SERV_DEFAULT "objserv.xml"
#define OSEV_LOCK_DEFAULT "objserv.lock"
#define OSEV_PID_DEFAULT "objserv.pid"
#define OSEV_LOG_DEFAULT "objserv.log"
#define OSEV_ACCESS_DEFAULT "osev_access.log"
#define OSEV_USER_DEFAULT "nobody"
#define OSEV_GROUP_DEFAULT "nobody"

#define VERSION 	"1.0"
#define COPYRIGHT 	"Copyright (C) 2012 Pu Shan"
#define DISCLAIMER      "This is not free software.  "
#define FUNCTION	"sync server" 
#define USAGE		"Usage: %s [options] <input>\n"
#define PROGRAM_NAME	"osev_serv_t"

//
#define LOOP_STOP                       0x00000000 // stop
#define LOOP_CONTINUE                   0x00000001 // continue
#define HAND_FINISH                     LOOP_STOP // stop
#define HAND_UNDONE                     LOOP_CONTINUE // continue
// #define HAND_EXCEPT                     -1 // exception
//
#define SEND_SUCCESS                    0x0000ffff
#define SEND_CONTINUE                   0x00010000
//
    
#ifdef	__cplusplus
}
#endif
    
#endif	/* _SERVER_MACRO_H_ */

