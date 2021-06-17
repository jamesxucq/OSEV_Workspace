#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <dlfcn.h>
#include <wait.h>

#include "commo_header.h"
#include "mstri_utili.h"
#include "mfile_utili.h"
#include "conoda.h"
#include "dyli_list.h"

//

int save_clang_file(char *clan_path, char *clang_txt) {
    // printf("save_clang_file.\n");
    FILE *data_fp = fopen64(clan_path, "ab+");
    if (!data_fp) {
        _LOG_ERROR("open file error! %s", clan_path);
        return -1;
    }
    if (0 >= fwrite(clang_txt, strlen(clang_txt), 0x01, data_fp)) {
        fclose(data_fp);
        _LOG_ERROR("fwrite file error! %s", clan_path);
        return -1;
    }
    fclose(data_fp);
    //
    return 0x00;
}

//
#define MAX_PARAM_CNT   256
#define GCC_COMPI_TOK     "gcc"
#define GCC_COMPI_LABLE "gcc compiling"
//

static void print_paras(char *label, char *param[]) {
    char text_buff[PATH_MAX * 0x02];
    char *last_str = text_buff;
    //
    last_str = lscpy(last_str, label);
    last_str = lccpy(last_str, '\n');
    write(STDERR_FILENO, text_buff, strlen(text_buff));
    //
    last_str = text_buff;
    int inde;
    for (inde = 0x00; param[inde]; inde++) {
        last_str = lscpy(last_str, param[inde]);
        last_str = lccpy(last_str, ' ');
    }
    last_str = lccpy(last_str, '\n');
    write(STDERR_FILENO, text_buff, strlen(text_buff));
}

//
#define LIBWT_TOK    "-lwiredtiger"

#define BUILD_CLANG_PARAM(LINE_TXT, COMPI_TOK, OBJE_FILE, CLAN_FILE) \
    LINE_TXT[0x00] = COMPI_TOK; LINE_TXT[0x01] = "-Wall"; \
    LINE_TXT[0x02] = "-fPIC"; LINE_TXT[0x03] = "-O2"; \
    LINE_TXT[0x04] = "-shared"; LINE_TXT[0x05] = "-o"; \
    LINE_TXT[0x06] = OBJE_FILE; LINE_TXT[0x07] = CLAN_FILE; \
    LINE_TXT[0x08] = LIBWT_TOK; LINE_TXT[0x08] = NULL;
//

#define RBUF_LENG      0x1000  // 4K

static int clang_compile(char *obje_file, char *clan_file, char *comp_mesg) {
    char *para_line[MAX_PARAM_CNT];
    int errfd[0x02];
    if (pipe(errfd)) return -1;
    //
    pid_t pid = vfork();
    if (0x00 > pid) {
        close(errfd[0x00]);
        close(errfd[0x01]);
        printf("fork gcc error!\n");
        return -1;
    } else if (!pid) {
        close(errfd[0x00]);
        if (-1 == dup2(errfd[0x01], STDERR_FILENO)) return -1;
        close(errfd[0x01]);
        //
        BUILD_CLANG_PARAM(para_line, GCC_COMPI_TOK, obje_file, clan_file)
#ifdef _DEBUG
                print_paras(GCC_COMPI_LABLE, para_line);
#endif
        execvp(para_line[0x00], para_line);
        printf("gcc compile error.\n");
        exit(-1);
    }
    //
    int rlen;
    char rbuf[RBUF_LENG];
    char *last_posi = comp_mesg;
    close(errfd[0x01]);
    while (0x00 < (rlen = read(errfd[0x00], rbuf, RBUF_LENG))) {
        memcpy(last_posi, rbuf, rlen);
        last_posi += rlen;
        // printf("loop rlen:%d\n", rlen);
    }
    // printf("finish rlen:%d\n", rlen);
    last_posi[0x00] = '\0';
    close(errfd[0x00]);
    //
    wait(NULL);
    return 0x00;
}

int compi_clang_file(char *obje_path, char *clan_path, BYTE *comp_mesg) {
    // printf("compi_clang_file.\n");
    // printf("obje_path:%s\n", obje_path);
    // printf("clan_path:%s\n", clan_path);
    if (clang_compile(obje_path, clan_path, (char *) comp_mesg)) return -1; // fix me 20170116
    // printf("comp_mesg:|%s|\n", comp_mesg);
    printf("unlink clan_path:%s\n", clan_path);
    unlink(clan_path);
    if (FILE_EXIST(obje_path)) return -1;
    //
    printf("Creat obje file OK!\n");
    return 0x00;
}

//

/*
void *obje_data;
int (*parser)(char **);
void (*method)(void *);
void (*create)(void *);
 */
static void *open_meth_symb(dyli_meth *dlmep, struct dyli_hand *dyha, char *func_name, char *retyp_name, char *pars_name) {
    strcpy(dlmep->handn, func_name);
    dlmep->lib_hand = dyha->handle;
    //
    // printf("oh retyp_name:|%s|\n", retyp_name);
    caller_type *retype = dlsym(dyha->handle, retyp_name);
    if (dlerror() != NULL) {
        _LOG_FATAL("get_handlers dlsym: %s", dlerror());
        return NULL;
    }
    dlmep->retype = retype[0x00];
    // printf("oh pars_name:|%s|\n", pars_name);
    dlmep->parser = dlsym(dyha->handle, pars_name);
    if (dlerror() != NULL) {
        _LOG_FATAL("get_handlers dlsym: %s", dlerror());
        return NULL;
    }
    // printf("oh func_name:|%s|\n", func_name);
    dlmep->method.meth_void = dlsym(dyha->handle, func_name);
    if (dlerror() != NULL) {
        _LOG_FATAL("get_handlers dlsym: %s", dlerror());

        return NULL;
    }
    //
    return dlmep;
}

static void close_meth_symb(hand_data *hando, dyli_meth * dlmep) {

    close_dyhand(&hando->dyha_list, dlmep->lib_hand);
    // printf("ch dlmep->metnm:|%s|\n", dlmep->handn);
    action_remove(dlmep->handn, hando->ocuse_hm);
}

int open_meth_hand(hand_data *hando, hand_data *handa, char *clasn, char *obje_path, char *handn) {
    char retyn[METH_LENGTH];
    char parsn[METH_LENGTH];
    build_retyp_parse(retyn, parsn, handn);
    // printf("obje_path:%s\n", obje_path);
    dyli_data *dldap = (dyli_data *) action_value(clasn, handa->ocuse_hm);
    if (!dldap) return -1;
    // printf("open_meth_hand. handn:%s parsn:%s\n", handn, parsn);
    struct dyli_hand * dyha = open_dyhand(&hando->dyha_list, obje_path);
    if (!dyha) return -1;
    //
    dyli_meth * dlmep = new_dyme();
    if (!dlmep) return -1;
    open_meth_symb(dlmep, dyha, handn, retyn, parsn);
    dlmep->dldat = dldap;
    _LOG_DEBUG("open_meth_hand insert handn:|%s| dlmep:%lld ocuse_hm:%lld", handn, (long long) dlmep, (long long) hando->ocuse_hm);
    action_insert(dlmep->handn, dlmep, hando->ocuse_hm);
    //

    return 0x00;
}

int dele_meth_hand(char *obje_path) {
    if (unlink(obje_path) < 0x00) return -1;
    return 0x00;
}

//

static void *open_data_symb(dyli_data *dldap, struct dyli_hand *dyha, char *clasn, char *obje_size, char *bind_name, char *solve_name) {
    strcpy(dldap->clasn, clasn);
    dldap->lib_hand = dyha->handle;
    // printf("oh obje_name:|%s|\n", obje_name);
    //    dldap->obje_data = dlsym(dyha->handle, obje_name);
    //    if (dlerror() != NULL) {
    //        _LOG_FATAL("get_handlers dlsym: %s", dlerror());
    //        return NULL;
    //    }
    // printf("oh obje_size:|%s|\n", obje_size);
    int *data_size = dlsym(dyha->handle, obje_size);
    if (dlerror() != NULL) {
        _LOG_FATAL("get_handlers dlsym: %s", dlerror());
        return NULL;
    }
    dldap->data_size = data_size[0x00];
    // printf("oh bind_name:|%s|\n", bind_name);
    dldap->bound = dlsym(dyha->handle, bind_name);
    if (dlerror() != NULL) {
        _LOG_FATAL("get_handlers dlsym: %s", dlerror());
        return NULL;
    }
    // printf("oh solve_name:|%s|\n", solve_name);
    dldap->solve = dlsym(dyha->handle, solve_name);
    if (dlerror() != NULL) {
        _LOG_FATAL("get_handlers dlsym: %s", dlerror());
        return NULL;
    }
    //
    return dldap;
}

static void close_data_symb(hand_data *hando, dyli_meth * dldap) {

    close_dyhand(&hando->dyha_list, dldap->lib_hand);
    // printf("ch dldap->metnm:|%s|\n", dldap->handn);
    action_remove(dldap->handn, hando->ocuse_hm);
}

//

int open_data_hand(hand_data *handa, char *obje_path, char *clasn) {
    char osize[OBJE_LENGTH];
    char bindn[METH_LENGTH];
    char solvn[METH_LENGTH];
    build_obsc_name(osize, bindn, solvn, clasn);
    // printf("open_meth_hand. handn:%s parsn:%s\n", handn, parsn);
    struct dyli_hand *dyha = open_dyhand(&handa->dyha_list, obje_path);
    if (!dyha) return -1;
    //
    dyli_data * dldap = new_dyda();
    if (!dldap) return -1;
    open_data_symb(dldap, dyha, clasn, osize, bindn, solvn);
    _LOG_DEBUG("open_data_hand insert clasn:|%s| dldap:%lld ocuse_hm:%lld", clasn, (long long) dldap, (long long) handa->ocuse_hm);
    action_insert(dldap->clasn, dldap, handa->ocuse_hm);
    //

    return 0x00;
}

//

