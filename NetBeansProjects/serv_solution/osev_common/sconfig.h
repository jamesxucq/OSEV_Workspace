
/* 
 * File:   sconfig.h
 * Author: James Xu
 *
 * Created on 2016.12.28, AM 10:41
 */

#ifndef SCONFIG_H
#define SCONFIG_H

#include "commo_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        char logfile[MAX_PATH * 3];
        log_lvl_t debug_level;
    } log_config;

    struct serv_config {
        // system info
        char user_name[_USERN_LENGTH_];
        char group_name[GROUPN_LENGTH];
        uid_t _user_id_;
        gid_t _group_id_;
        int worker_processes;
        char lock_file[MAX_PATH * 3];
        char pid_file[MAX_PATH * 3];
        // server info
        char data_directory[MAX_PATH * 3];
        // network info
        char serv_address[SERVN_LENGTH];
        short bind_port;
        int max_connecting;
        int seion_timeout;
        // log config
        log_config runtime_log;
        log_config access_log;
    };


#ifdef __cplusplus
}
#endif

#endif /* SCONFIG_H */

