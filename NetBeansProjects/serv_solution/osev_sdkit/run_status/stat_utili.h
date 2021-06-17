
/* 
 * File:   stat_utili.h
 * Author: James Xu
 *
 * Created on 2017.1.8, AM 10:14
 */

#ifndef STAT_UTILI_H
#define STAT_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
#define OSDB_RUNNING_STAT   "osdb_running.sta"

#define OSEV_DATA_PATH  "osev"
#define OSEV_AUTHEN_STAT   "osev_authen.sta"

    //

    struct osdb_stat {
        uint32 leve_valu;
    };
    int load_osdb_rstat(struct osdb_stat *rstat, char *osdb);

    //
    int open_osdb_flag(char *osdb, uint32 leval);
    int close_osdb_flag(char *osdb);
    int creat_osdb_conte(char *osdb);
    int drop_osdb_conte(char *osdb);
    //
    // 0x00: exists 0x01:opened 0x02: not exists
#define OSDB_EXISTS 0x00
#define OSDB_OPENED 0x01
#define OSDB_NOEXIS 0x02
    int check_osdb_exist(char *osdb);
    
    //
    int valid_osdb_opened(char *osdb);
    // 0x00:empty 0x01:not empty
    int valid_osdb_clean(char *osdb);

    //
    int find_osdb_attri(osv_oid_t *oid, char *osdb);

    //
//    int enab_authen_flag();
//    int disab_authen_flag();
    // int valid_authen_enab();
    //

#ifdef __cplusplus
}
#endif

#endif /* STAT_UTILI_H */

