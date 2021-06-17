#ifndef _PARSECONF_H_
#define _PARSECONF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "commo_header.h"

    //
    extern struct serv_config _serv_config_;
    int serv_config_from_xml(struct serv_config *config, const char *xml_config);
    void serialize(char *sbuf, struct serv_config *config);

#ifdef __cplusplus
}
#endif

#endif /* _PARSECONF_H_ */
