#include "commo_header.h"
#include "third_party.h"
#include "oattri.h"

#include "stat_utili.h"

//

struct subpath {
    char *path;
    struct subpath *subp;
};

// container path
#define CONT_IMEMO_HOME "imemo"
#define CONT_LEAP_HOME "leap"
#define CONT_WTIGER_HOME "wiredtiger" // wiredtiger

static struct subpath conta_home_tab[] = {
    {CONT_IMEMO_HOME, NULL}, // imemo
    {CONT_LEAP_HOME, NULL}, // leap
    {CONT_WTIGER_HOME, NULL}, // wiredtiger
    {NULL, NULL}
};

// data root
#define DATA_CACHE_DEFAULT   "cache"
#define DATA_CLASS_DEFAULT    "class"
#define DATA_CONTAIN_DEFAULT    "contain"
#define DATA_OBJECT_DEFAULT   "object"
#define DATA_TEMP_DEFAULT   "temp"

static struct subpath data_subp_tab[] = {
    {DATA_CACHE_DEFAULT, NULL},
    {DATA_CLASS_DEFAULT, NULL},
    {DATA_CONTAIN_DEFAULT, conta_home_tab},
    {DATA_OBJECT_DEFAULT, NULL},
    {DATA_TEMP_DEFAULT, NULL},
    {NULL, NULL}
};

//

int creat_osdb_conte(char *osdb) {
    char data_path[MAX_PATH * 3];
    CREAT_OSDB_PATH(data_path, osdb)
    if (mkdir(data_path, 0755)) {
        _LOG_WARN("mkdir:%s error[%d]:%s", data_path, errno, strerror(errno));
        return -1;
    }
    //
    CREAT_OSDB_SUBPA(data_path, osdb, OSDB_ATTRIB)
    if (creat_osdb_attri(data_path, osdb)) {
        _LOG_WARN("mkdir:%s error[%d]:%s", data_path, errno, strerror(errno));
        return -1;
    }
    //
    char *sub_dire;
    struct subpath *sub_path;
    for (sub_path = data_subp_tab; sub_path->path; sub_path++) {
        CREAT_OSDB_SUBPA_EXT(sub_dire, data_path, osdb, sub_path->path)
        if (mkdir(data_path, 0755)) {
            _LOG_WARN("mkdir:%s error[%d]:%s", data_path, errno, strerror(errno));
            return -1;
        }
        // second level
        if (sub_path->subp) {
            struct subpath *sel_path = sub_path->subp;
            for (; sel_path->path; sel_path++) {
                char *last_str = lccpy(sub_dire, '/');
                last_str = lscpy(last_str, sel_path->path);
                if (mkdir(data_path, 0755)) {
                    _LOG_WARN("mkdir:%s error[%d]:%s", data_path, errno, strerror(errno));
                    return -1;
                }
            }
        }
    }
    //
    return 0x00;
}

//

int load_osdb_rstat(struct osdb_stat *rstat, char *osdb) {
    char running_stat[MAX_PATH * 3];
    CREAT_TEMPO_PATH(running_stat, osdb, OSDB_RUNNING_STAT)
    if (FILE_EXIST(running_stat)) return -1;
    //
    int rstat_fd;
    if ((rstat_fd = open64(running_stat, O_RDONLY, 0666)) == -1) {
        close(rstat_fd);
        _LOG_WARN("can not open file %s", running_stat);
        return -1;
    }
    //
    if (sizeof (struct osdb_stat) != read(rstat_fd, rstat, sizeof (struct osdb_stat))) {
        close(rstat_fd);
        _LOG_WARN("read running stat error!\n");
        return -1;
    }
    //
    close(rstat_fd);
    return 0x00;
}

int open_osdb_flag(char *osdb, uint32 leval) {
    char running_stat[MAX_PATH * 3];
    CREAT_TEMPO_PATH(running_stat, osdb, OSDB_RUNNING_STAT)
    if (!FILE_EXIST(running_stat)) return -1;
    //
    int rstat_fd;
    if ((rstat_fd = open64(running_stat, O_WRONLY | O_CREAT, 0666)) == -1) {
        close(rstat_fd);
        _LOG_WARN("can not open file %s", running_stat);
        return -1;
    }
    //
    struct osdb_stat ostat;
    ostat.leve_valu = leval;
    printf("leval:|%08X|\n", leval);
    if (sizeof (struct osdb_stat) != write(rstat_fd, &ostat, sizeof (struct osdb_stat))) {
        close(rstat_fd);
        _LOG_WARN("write running stat error!\n");
        return -1;
    }
    //
    close(rstat_fd);
    return 0x00;
}

//
// 0x00: exists 0x01:opened 0x02: not exists

int check_osdb_exist(char *osdb) {
    char osdb_path[MAX_PATH * 3];
    CREAT_OSDB_PATH(osdb_path, osdb)
    if (FILE_EXIST(osdb_path)) return 0x02;
    //
    CREAT_TEMPO_PATH(osdb_path, osdb, OSDB_RUNNING_STAT)
    if (!FILE_EXIST(osdb_path)) return 0x01;
    //
    return 0x00;
}

//

int drop_osdb_conte(char *osdb) {
    char data_path[MAX_PATH * 3];
    CREAT_OSDB_PATH(data_path, osdb)
    if (recu_rmdir(data_path)) {
        _LOG_WARN("recu rmdir error, path:%s", data_path);
        return -1;
    }
    //
    return 0x00;
}

int close_osdb_flag(char *osdb) {
    char running_stat[MAX_PATH * 3];
    CREAT_TEMPO_PATH(running_stat, osdb, OSDB_RUNNING_STAT)
    if (FILE_EXIST(running_stat)) return -1;
    //
    if (unlink(running_stat) < 0x00) {
        _LOG_WARN("unlink file error! errno:%d path:%s", errno, running_stat);
        return -1;
    }
    //
    return 0x00;
}

//

int valid_osdb_opened(char *osdb) {
    char running_stat[MAX_PATH * 3];
    CREAT_TEMPO_PATH(running_stat, osdb, OSDB_RUNNING_STAT)
    if (FILE_EXIST(running_stat)) return -1;
    //
    return 0x00;
}

// xfs have not, ext4 have.
// #define  HAVE_DIRENT_DTYPE    0x01
#ifdef HAVE_DIRENT_DTYPE

int empty_directory(char *dirpath) {
    DIR *dires;
    struct dirent *dirp;
    //
    if (!(dires = opendir(dirpath))) return -1;
    while (NULL != (dirp = readdir(dires))) {
        if (DT_UNKNOWN == dirp->d_type || DT_REG == dirp->d_type) {
            closedir(dires);
            return -1;
        } else if (DT_DIR == dirp->d_type) {
            if (!strcmp(".", dirp->d_name) || !strcmp("..", dirp->d_name))
                continue;
            closedir(dires);
            return -1;
        }
    }
    closedir(dires);
    //
    return 0x00;
}
#else

int empty_directory(char *dirpath) {
    DIR *dires;
    struct dirent *dirp;
    struct stat64 statb;
    //
    if (!(dires = opendir(dirpath))) return -1;
    while (NULL != (dirp = readdir(dires))) {
        if (stat64(dirpath, &statb) < 0) {
            closedir(dires);
            _LOG_WARN("stat errno:%d", errno);
            return -1;
        }
        if (S_ISLNK(statb.st_mode) || S_ISREG(statb.st_mode)) {
            closedir(dires);
            return -1;
        } else if (S_ISDIR(statb.st_mode)) {
            if (!strcmp(".", dirp->d_name) || !strcmp("..", dirp->d_name))
                continue;
            closedir(dires);
            return -1;
        }
    }
    closedir(dires);
    //
    return 0x00;
}
#endif

// 0x00:empty -1:not empty

int valid_osdb_clean(char *osdb) {
    char data_path[MAX_PATH * 3];
    CREAT_OSDB_SUBPA(data_path, osdb, DATA_CLASS_DEFAULT)
    if (empty_directory(data_path)) return -1;
    //
    return 0x00;
}


//

int find_osdb_attri(osv_oid_t *oid, char *osdb) {
    osv_oid_t obje_oid;
    if (parse_osdb_attri(&obje_oid, osdb)) return -1;
    memcpy(oid, &obje_oid, sizeof (osv_oid_t));
    //
    return 0x00;
}

//

/*
int enab_authen_flag() {
    char authen_stat[MAX_PATH * 3];
    CREAT_TEMPO_PATH(authen_stat, OSEV_DATA_PATH, OSEV_AUTHEN_STAT)
    if (!FILE_EXIST(authen_stat)) return -1;
    //
    int astat_fd;
    if ((astat_fd = open64(authen_stat, O_WRONLY | O_CREAT, 0666)) == -1) {
        close(astat_fd);
        _LOG_WARN("can not open file %s", authen_stat);
        return -1;
    }
    close(astat_fd);
    //
    return 0x00;
}
*/

//
// 0x00: normal 0x01:opened 0x02: not exists

/*
int disab_authen_flag() {
    char authen_stat[MAX_PATH * 3];
    CREAT_TEMPO_PATH(authen_stat, OSEV_DATA_PATH, OSEV_AUTHEN_STAT)
    if (FILE_EXIST(authen_stat)) return -1;
    //
    if (unlink(authen_stat) < 0x00) {
        _LOG_WARN("unlink file error! errno:%d path:%s", errno, authen_stat);
        return -1;
    }
    //
    return 0x00;
}
*/

/*
int valid_authen_enab() {
    char authen_stat[MAX_PATH * 3];
    CREAT_TEMPO_PATH(authen_stat, OSEV_DATA_PATH, OSEV_AUTHEN_STAT)
    if (FILE_EXIST(authen_stat)) return -1;
    //
    return 0x00;
}
*/