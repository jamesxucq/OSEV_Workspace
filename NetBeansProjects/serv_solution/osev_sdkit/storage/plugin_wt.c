#include "commo_header.h"

#include "stora_engine.h"
#include "third_party.h"
#include "sess_list.h"
#include "plugin_wt.h"

//

// #define	CONNE_CONFIG "create,cache_size=128MB,log=(archive=false,enabled=true)"
// #define	CONNE_CONFIG "create"
#define CONNE_CONFIG "create,\
                    cache_size=1G,\
                    session_max=2000,\
                    eviction=(threads_max=4),\
                    log=(enabled=true,archive=true,path=journal),\
                    checkpoint=(wait=60,log_size=2G)"

#define JOURNAL_PATH "journal"
#define DISABLE_LOG ",log=(enabled=false)"

int wt_open_conne(riv_conne_t **conne, char *osdb, int durab) {
    char journal_path[MAX_PATH];
    char contain_home[MAX_PATH];
    ENGINE_CONTAIN_FILE(WTIGER_ENAME, journal_path, osdb, JOURNAL_PATH)
    CREAT_CONTAIN_PATH(WTIGER_ENAME, contain_home, osdb)
            char config_str[CONF_LENGTH];
    strcpy(config_str, CONNE_CONFIG);
    //
    if (durab) {
        DIRECTORY_EXISTS(journal_path)
        if (TRUE != S_ISDIR(statb.st_mode)) {
            if (mkdir(journal_path, 0755))
                _LOG_WARN("mkdir errno:%d", errno);
            _LOG_WARN("mkdir:%s", journal_path);
        }
    }
    //
    printf("wt_open_conne creat, osdb:%s\n", osdb);
    printf("contain_home:%s\n", contain_home);
    if (!durab) {
        DIRECTORY_EXISTS(journal_path)
        if (TRUE == S_ISDIR(statb.st_mode)) {
            int ret = wiredtiger_open(contain_home, NULL, config_str, (WT_CONNECTION **) conne);
            if (ret == EINVAL) {
                _LOG_WARN("wiredtiger_open result EINVAL.");
            } else if (ret != 0) {
                _LOG_WARN("wiredtiger_open result error.");
            }
            ((WT_CONNECTION *) conne[0x00])->close((conne[0x00]), NULL);
        }
        strcat(config_str, DISABLE_LOG);
    }
    //
    return wiredtiger_open(contain_home, NULL, config_str, (WT_CONNECTION **) conne);
}

int wt_close_conne(riv_conne_t *conne) {
    return ((WT_CONNECTION *) conne)->close(conne, NULL);
}

//

int wt_open_sess(rive_conne *conne, riv_sessi_t **sessi) {
    return ((WT_CONNECTION *) conne)->open_session((WT_CONNECTION *) conne, NULL, "isolation=snapshot", (WT_SESSION**) sessi);
}

int wt_close_sess(riv_sessi_t *sessi) {
    return ((WT_SESSION *) sessi)->close(sessi, NULL);
}

int wt_log_flush(riv_sessi_t *sessi) {
    return ((WT_SESSION *) sessi)->log_flush(sessi, "sync=on");
}

int wt_begin_transa_sess(riv_sessi_t *sessi) {
    return ((WT_SESSION *) sessi)->begin_transaction(sessi, NULL);
}

int wt_commit_transa_sess(riv_sessi_t *sessi) {
    return ((WT_SESSION *) sessi)->commit_transaction(sessi, NULL);
}

int wt_reset_sess(riv_sessi_t *sessi) {
    return ((WT_SESSION *) sessi)->reset(sessi);
}


//

int wt_open_curso(riv_curso_t **curso, riv_sessi_t *sessi, char *uri, char *config) {
    return ((WT_SESSION *) sessi)->open_cursor(sessi, uri, NULL, config, (WT_CURSOR **) curso);
}

int wt_open_table(riv_curso_t **curso, riv_sessi_t *sessi, char *table, char *config) {
    char taburi[MAX_PATH];
    lscpy(lscpy(taburi, "table:"), table);
    printf("wt_open_table, taburi:%s\n", taburi);
    return ((WT_SESSION *) sessi)->open_cursor(sessi, taburi, NULL, config, (WT_CURSOR **) curso);
}

int wt_open_group(riv_curso_t **curso, riv_sessi_t *sessi, char *group, char *config) {
    char grouri[MAX_PATH];
    lscpy(lscpy(grouri, "colgroup:"), group);
    printf("wt_open_group, grouri:%s\n", grouri);
    return ((WT_SESSION *) sessi)->open_cursor(sessi, grouri, NULL, config, (WT_CURSOR **) curso);
}

int wt_open_index(riv_curso_t **curso, riv_sessi_t *sessi, char *index, char *config) {
    char induri[MAX_PATH];
    lscpy(lscpy(induri, "index:"), index);
    printf("wt_open_index, induri:%s\n", induri);
    return ((WT_SESSION *) sessi)->open_cursor(sessi, induri, NULL, config, (WT_CURSOR **) curso);
}

int wt_close_curso(riv_curso_t *curso) {
    return ((WT_CURSOR *) curso)->close(curso);
}

int wt_inser_curso(riv_curso_t *curso) {
    return ((WT_CURSOR *) curso)->insert(curso);
}

int wt_reset_curso(riv_curso_t *curso) {
    return ((WT_CURSOR *) curso)->reset(curso);
}

int wt_next_curso(riv_curso_t *curso) {
    return ((WT_CURSOR *) curso)->next(curso);
}

int wt_prev_curso(riv_curso_t *curso) {
    return ((WT_CURSOR *) curso)->prev(curso);
}

int wt_sear_curso(riv_curso_t *curso) {
    return ((WT_CURSOR *) curso)->search(curso);
}

int wt_searn_curso(riv_curso_t *curso, int *exactp) {
    return ((WT_CURSOR *) curso)->search_near(curso, exactp);
}

int wt_update_curso(riv_curso_t *curso) {
    return ((WT_CURSOR *) curso)->update(curso);
}

int wt_remove_curso(riv_curso_t *curso) {
    return ((WT_CURSOR *) curso)->remove(curso);
}

int wt_reconf_curso(riv_curso_t *curso, char *config) {
    return ((WT_CURSOR *) curso)->reconfigure(curso, config);
}

void set_key_wt(riv_curso_t *curso, unsigned long long key) {
    ((WT_CURSOR *) curso)->set_key(curso, key);
}

void set_value_wt(riv_curso_t *curso, void *value) {
    ((WT_CURSOR *) curso)->set_value(curso, value);
}

int get_key_wt(riv_curso_t *curso, void *value) {
    return ((WT_CURSOR *) curso)->get_key(curso, value);
}

int get_value_wt(riv_curso_t *curso, void *value) {
    return ((WT_CURSOR *) curso)->get_value(curso, value);
}

//

int wt_creat_tab(riv_sessi_t *sessi, char *table, char *forma) {
    char taburi[MAX_PATH];
    char *last_str = lscpy(taburi, "table:");
    lscpy(last_str, table);
    return ((WT_SESSION *) sessi)->create(sessi, taburi, forma);
}

//

int wt_dorp_tab(riv_sessi_t *sessi, char *table) {
    char taburi[MAX_PATH];
    char *last_str = lscpy(taburi, "table:");
    lscpy(last_str, table);
    return ((WT_SESSION *) sessi)->drop(sessi, taburi, NULL);
}

//

int wt_rename_tab(riv_sessi_t *sessi, char *old_tab, char *new_tab) {
    return ((WT_SESSION *) sessi)->rename(sessi, old_tab, new_tab, NULL);
}

//