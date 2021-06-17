#include "commo_header.h"
#include "stat_utili.h"
#include "conve_rstat.h"

///

static char *conve_osdb_opened(char *statu_txt, char *osdb) {
    char *last_str = statu_txt;
    last_str = lscpy(last_str, osdb);
    last_str = lscpy(last_str, " running.\n");
    //
    return last_str;
}

static char *conve_osdb_closed(char *statu_txt, char *osdb) {
    char *last_str = statu_txt;
    last_str = lscpy(last_str, osdb);
    last_str = lscpy(last_str, " stoped.\n");
    //
    return last_str;
}

static char *conve_osdb_clean(char *statu_txt, char *osdb) {
    char *last_str = statu_txt;
    last_str = lscpy(last_str, osdb);
    last_str = lscpy(last_str, " is clean.\n");
    //
    return last_str;
}

int conve_osdb_all(prod_data *sresp, char **osds) {
    char *last_str = (char *) sresp->sebuf;
    char **osdn = osds;
    for (; osdn[0x00]; osdn++) {
        if (valid_osdb_opened(osdn[0x00]))
            last_str = conve_osdb_closed(last_str, osdn[0x00]);
        else {
            last_str = conve_osdb_opened(last_str, osdn[0x00]);
            if (!valid_osdb_clean(osdn[0x00]))
                last_str = conve_osdb_clean(last_str, osdn[0x00]);
        }
    }
    //
    (sresp->colen)[0x00] = strlen((char *) sresp->sebuf);
    return 0x00;
}

//

char *conve_osdb_name(prod_data *sresp, char *osdb) {
    char *last_str = (char *) sresp->sebuf;
    if (valid_osdb_opened(osdb))
        last_str = conve_osdb_closed(last_str, osdb);
    else {
        last_str = conve_osdb_opened(last_str, osdb);
        if (!valid_osdb_clean(osdb))
            last_str = conve_osdb_clean(last_str, osdb);
    }
    //
    (sresp->colen)[0x00] = strlen((char *) sresp->sebuf);
    return last_str;
}


//

void conve_obje_id(prod_data *sresp, osv_oid_t *oid) {
    memcpy(sresp->sebuf, oid, sizeof (osv_oid_t));
    (sresp->colen)[0x00] = sizeof (osv_oid_t);
}