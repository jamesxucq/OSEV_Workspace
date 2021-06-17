#ifndef SERV_BZL_H_
#define SERV_BZL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "osev_obje.h"

    struct serv_config *servbzl_create(char *xml_config);
    int servbzl_destroy();

    /*Anch operator section*/

    /*Type operator section*/
    struct serv_config *load_serv_config(const char *config_path);
    inline struct serv_config *get_serv_config();

    /*sync server aope*/
#define SET_FATTRIB_BZL(BASE_NAME, INVAL) { \
    char file_name[MAX_PATH * 3]; \
    POOL_PATH(file_name, BASE_NAME, INVAL->file_name); \
    truncate64(file_name, INVAL->file_size); \
    SET_FILE_MODTIME(file_name, INVAL->last_write); \
}

#define SET_MODTIME_BZL(BASE_NAME, INVAL) \
    SET_FILE_MODTIME_EXT(BASE_NAME, (char *)INVAL->data_line, INVAL->last_write)

    /* file list aope */

#ifdef __cplusplus
}
#endif

#endif /* SERV_BZL_H_ */
