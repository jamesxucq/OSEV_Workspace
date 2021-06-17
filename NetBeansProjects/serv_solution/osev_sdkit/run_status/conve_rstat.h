
/* 
 * File:   conve_rstat.h
 * Author: James Xu
 *
 * Created on 2017.1.5, AM 10:53
 */

#ifndef CONVE_RSTAT_H
#define CONVE_RSTAT_H

#ifdef __cplusplus
extern "C" {
#endif

    //
int conve_osdb_all(prod_data *sresp, char **osds);
char *conve_osdb_name(prod_data *sresp, char *osdb);

//
void conve_obje_id(prod_data *sresp, osv_oid_t *oid);


#ifdef __cplusplus
}
#endif

#endif /* CONVE_RSTAT_H */

