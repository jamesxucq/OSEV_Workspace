#ifndef _SHEL_MACRO_H_
#define _SHEL_MACRO_H_

#ifdef __cplusplus
extern "C" {
#endif

    //
#define DEFAULT_HOST_PORT 8888
#define DEFAULT_CONTENT_LENGTH (100 * 1024) /* bytes */
#define DEFAULT_KEEP_ALIVE 5 /* seconds */
#define DEFAULT_MAX_CONNECTION_AGE 300 /* seconds */
#define BUG_REPORT_EMAIL "james.xucq@gmail.com"

#define VERSION 	"1.0"
#define COPYRIGHT 	"Copyright (C) 2012 Pu Shan"
#define DISCLAIMER      "This is not free software.  "
#define FUNCTION	"osev shell" 
#define USAGE		"Usage: %s [options] <input>\n"
#define PROGRAM_NAME	"osev_shell"


    //
#define CLIE_DEFAULT_VALUE  "clie"
#define OSEV_PRIVILE_VALUE  "osev:privile"
#define OSDB_PRIVILE_VALUE  "odb:privile"
    
    //
#define OSEV_DEFAULT_VALUE  "osev"
#define OSDB_DEFAULT_VALUE  "odb"

#ifdef __cplusplus
}
#endif

#endif /* _SHEL_MACRO_H_ */

