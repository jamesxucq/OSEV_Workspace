/* aserv_bzl.c
 * Created on: 2010-3-10
 * Author: Divad
 */

#include "osev_bzl.h"
#include "sconfig.h"

struct serv_config *servbzl_create(char *xml_config) {
    struct serv_config *config = load_serv_config(xml_config);
    if (config) fprintf(stderr, "Load config ok!\n");
    else fprintf(stderr, "Load config failed!\n");
    //
    commo_directory_init(config->data_directory);
    return config; //succ
}

int servbzl_destroy() {
    return ERR_SUCCESS; //succ
}

struct serv_config *load_serv_config(const char *config_path) {
    if (!config_path) return NULL;
    //
    if (serv_config_from_xml(&_serv_config_, config_path)) return NULL;
    find_user_group(_serv_config_.user_name, _serv_config_.group_name, &_serv_config_._user_id_, &_serv_config_._group_id_);
    //
    return &_serv_config_;
}

inline struct serv_config *get_serv_config() {
    return &_serv_config_;
}

//
