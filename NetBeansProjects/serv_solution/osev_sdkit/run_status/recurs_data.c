#include "commo_header.h"

#include "rstr_utili.h"
#include "recurs_data.h"

//
int is_class(char *file_name) {
    char *tok = strrchr(file_name, '.');
    if (!tok) return 0x00;
    if (strcmp(".class", tok)) return 0x00;
    return 0x01;
}

// xfs have not, ext4 have.
// #define  HAVE_DIRENT_DTYPE    0x01
#ifdef HAVE_DIRENT_DTYPE

int recur_scaner(char *clas_decl, char **clas, char *dirpath, int *inde) {
    DIR *dires;
    struct dirent *dirp;
    char subdir[MAX_PATH * 3];
    char *last_txt = clas_decl;
    //
    if (!(dires = opendir(dirpath))) return -1;
    const char *last_str = lsprif(subdir, "%s/", dirpath);
    while (NULL != (dirp = readdir(dires))) {
        if (DT_UNKNOWN == dirp->d_type || DT_REG == dirp->d_type) {
            if (is_class(subdir)) {
                lscpy_o(clas[(*inde)++], subdir, last_txt);
                last_txt = lscpy(last_txt, dirp->d_name);
            }
        } else if (DT_DIR == dirp->d_type) {
            if (!strcmp(".", dirp->d_name) || !strcmp("..", dirp->d_name))
                continue;
            strcpy((char *) last_str, dirp->d_name);
            if (recur_scaner(last_txt, clas, subdir, inde)) {
                closedir(dires);
                return -1;
            }
        }
    }
    closedir(dires);
    //
    return 0x00;
}
#else

int recur_scaner(char *clas_decl, char **clas, char *dirpath, int *inde) {
    DIR *dires;
    struct dirent *dirp;
    struct stat64 statb;
    char subdir[MAX_PATH * 3];
    char *last_txt = clas_decl;
    //
    if (!(dires = opendir(dirpath))) return -1;
    char *last_str = lsprif(subdir, "%s/", dirpath);
    while (NULL != (dirp = readdir(dires))) {
        strcpy(last_str, dirp->d_name);
        if (stat64(subdir, &statb) < 0) {
            closedir(dires);
            _LOG_WARN("stat errno:%d", errno);
            return -1;
        }
        if (S_ISLNK(statb.st_mode) || S_ISREG(statb.st_mode)) {
            if (is_class(subdir)) {
                last_txt = lscpy(last_txt, subdir);
                last_txt = lccpy(last_txt, '\n');
            }
        } else if (S_ISDIR(statb.st_mode)) {
            if (!strcmp(".", dirp->d_name) || !strcmp("..", dirp->d_name))
                continue;
            if (recur_scaner(last_txt, clas, subdir, inde)) {
                closedir(dires);
                return -1;
            }
        }
    }
    closedir(dires);
    //
    return 0x00;
}
#endif

int list_clasn(char *clas_decl, char **clas, char *clas_path) {
    MKZERO(clas_decl);
    memset(clas, '\0', sizeof (char *) * MAX_OSDB_NUMB);
    int inde = 0x00;
    recur_scaner(clas_decl, clas, clas_path, &inde);
    return 0x00;
}

//
#ifdef HAVE_DIRENT_DTYPE

int list_scaner(char *clas_decl, char **osds, char *dirpath) {
    DIR *dires;
    struct dirent *dirp;
    char *last_txt = clas_decl;
    //
    if (!(dires = opendir(dirpath))) return -1;
    int inde = 0x00;
    while (NULL != (dirp = readdir(dires))) {
        if (DT_DIR == dirp->d_type) {
            if (!strcmp(".", dirp->d_name) || !strcmp("..", dirp->d_name))
                continue;
            lscpy_o(osds[inde++], dirp->d_name, last_txt);
        }
    }
    closedir(dires);
    //
    return 0x00;
}
#else

int list_scaner(char *clas_decl, char **osds, char *dirpath) {
    DIR *dires;
    struct dirent *dirp;
    struct stat64 statb;
    char *last_txt = clas_decl;
    //
    if (!(dires = opendir(dirpath))) return -1;
    int inde = 0x00;
    while (NULL != (dirp = readdir(dires))) {
        if (stat64(dirpath, &statb) < 0) {
            closedir(dires);
            _LOG_WARN("stat errno:%d", errno);
            return -1;
        }
        if (S_ISDIR(statb.st_mode)) {
            if (!strcmp(".", dirp->d_name) || !strcmp("..", dirp->d_name))
                continue;
            lscpy_o(osds[inde++], dirp->d_name, last_txt);
        }
    }
    closedir(dires);
    //
    return 0x00;
}
#endif

int list_osdb(char *osdb_txt, char **osds, char *data_path) {
    MKZERO(osdb_txt);
    memset(osds, '\0', sizeof (char *) * MAX_OSDB_NUMB);
    list_scaner(osdb_txt, osds, data_path);
    return 0x00;
}