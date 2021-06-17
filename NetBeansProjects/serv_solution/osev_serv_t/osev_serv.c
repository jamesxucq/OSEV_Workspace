
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <signal.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>

#include "third_party.h"
#include "server_macro.h"

#include "authen_bzl.h"
#include "privile_bzl.h"
#include "invo_bzl.h"
#include "comdi_bzl.h"
#include "hand_bzl.h"
#include "rstat_bzl.h"
// #include "plugin.h"

#include "epoll_serv.h"
#include "process_cycle.h"
#include "parse_conf.h"
#include "osev_bzl.h"
#include "osev_serv.h"
#include "sconfig.h"

//

void STATUS_LOGGER() {
#ifdef _DEBUG
    fprintf(stderr, "debug %s.\n", PROGRAM_NAME);
#else
    fprintf(stderr, "release %s.\n", PROGRAM_NAME);
#endif
    //
#ifdef NOAUTH
    fprintf(stderr, "osev disable authen.\n");
#else
    fprintf(stderr, "osev enable authen.\n");
#endif
    // 
}


//

int main(int argc, char *argv[]) {
    char xml_config[MAX_PATH * 3];
    STATUS_LOGGER();
    //
    if (parse_args(xml_config, argc, argv)) return ERR_FAULT;
    if (FILE_EXIST(xml_config)) {
        fprintf(stderr, "%s configuration file not exist.\n", xml_config);
        return EXIT_FAILURE;
    }
    //    
    struct sigaction sa;
    sa.sa_handler = SIG_IGN; // SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; // 0;
    if (sigaction(SIGABRT, &sa, NULL) < 0) fprintf(stderr, "can't ignore SIGABRT\n");
    //
    if (initialize_serv(xml_config)) {
        fprintf(stderr, "initialize_serv failed!\n");
        return ERR_FAULT;
    }
    fprintf(stderr, "initialize_serv ok!\n");
    struct serv_config *config = get_serv_config();
#ifndef _DEBUG
    if (daemonize(PROGRAM_NAME)) return ERR_FAULT;
#endif
    // init log module
    log_inital(config->runtime_log.logfile, config->runtime_log.debug_level);
    access_inital(config->access_log.logfile);
    //
#ifndef _DEBUG
    master_process_cycle(config);
#else
    _LOG_WARN("debug single mode!");
    single_process_cycle(config);
#endif
    log_final();
    access_final();
    //
    if (finalize_serv()) {
        _LOG_WARN("finalize_serv failed!");
        return ERR_FAULT;
    }
    _LOG_INFO("finalize_serv ok!");
    //
    return ERR_SUCCESS;
}

//

int initialize_serv(char *xml_config) {
    struct serv_config *config = NULL;
    // init serv gui module
    config = servbzl_create(xml_config);
    if (!config) return ERR_FAULT;
    fprintf(stdout, "configuration file name:%s\n", xml_config);
    //
    if (conbzl_create()) {
        fprintf(stdout, "conbzl_create error!\n");
        return ERR_FAULT;
    }
    // Start the dir watcher thread
    if (authbzl_create(config->max_connecting)) {
        fprintf(stdout, "authbzl_create error!\n");
        return ERR_FAULT;
    }
    // init riverfs module
    if (rivbzl_create(config->data_directory)) {
        fprintf(stdout, "rivbzl_create error!\n");
        return ERR_FAULT;
    }
    //
    return ERR_SUCCESS;
}

int finalize_serv() {
    // init riverfs module
    rivbzl_destroy();
    // stop the dir watcher thread
    authbzl_destroy();
    //
    conbzl_destroy();
    // uninit client gui module
    servbzl_destroy();
    //
    return ERR_SUCCESS;
}

