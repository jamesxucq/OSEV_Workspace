#include "commo_header.h"

#include "oattri.h"
#include "recurs_data.h"
#include "rstat_obje.h"

//
#define AUTH_HOME_PATH  ""

//

int find_osdb_oid(char *osdb, osv_oid_t *oid) {
    _LOG_TRACE("find_osdb_oid");
    char osds_line[LARGE_TEXT_SIZE];
    char *osds_arra[MAX_OSDB_NUMB];
    if (list_osdb(osds_line, osds_arra, _COMMO_DIRECTORY_)) return -1;
    //
    osv_oid_t obje_oid;
    char **osdn = osds_arra;
    for (; osdn[0x00]; osdn++) {
        parse_osdb_attri(&obje_oid, osdn[0x00]);
        if (oidcmp(oid, &obje_oid)) {
            strcpy(osdb, osdn[0x00]);
            return 0x00;
        }
    }
    //
    return -1;
}



