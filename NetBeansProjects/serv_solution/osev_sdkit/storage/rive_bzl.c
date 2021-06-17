#include "commo_header.h"

#include "plugin_wt.h"
// #include "plugin_sp.h"

#include "rive_bzl.h"

//

int rivbzl_create(char *data_directory) {
    // strcpy(_conta_directory_, data_directory);
    return ERR_SUCCESS; //succ
}
//

int rivbzl_destroy() {
    return ERR_SUCCESS; //succ
}

//
/*
static rive_ha imemo_ha = {
    IMEMO_ENAME,
    ENGINE_IMEMO,
    wt_open_conne,
    wt_close_conne,
    //
    wt_open_sess,
    wt_close_sess,
    wt_log_flush,
    wt_begin_transa_sess,
    wt_commit_transa_sess,
    wt_reset_sess,
    //
    wt_open_curso,
    wt_close_curso,
    wt_inser_curso,
    wt_reset_curso,
    wt_next_curso,
    wt_prev_curso,
    wt_sear_curso,
    wt_searn_curso,
    wt_update_curso,
    wt_remove_curso,
    wt_reconf_curso,
    set_key_wt,
    //
    wt_creat_tab,
    wt_dorp_tab,
    wt_rename_tab
};
 */

//
/*
static rive_ha leap_ha = {
    LEAP_ENAME,
    ENGINE_LEAP,
    wt_open_conne,
    wt_close_conne,
    //
    wt_open_sess,
    wt_close_sess,
    wt_log_flush,
    wt_begin_transa_sess,
    wt_commit_transa_sess,
    wt_reset_sess,
    //
    wt_open_curso,
    wt_close_curso,
    wt_inser_curso,
    wt_reset_curso,
    wt_next_curso,
    wt_prev_curso,
    wt_sear_curso,
    wt_searn_curso,
    wt_update_curso,
    wt_remove_curso,
    wt_reconf_curso,
    set_key_wt,
    //
    wt_creat_tab,
    wt_dorp_tab,
    wt_rename_tab
};
 */

//
static rive_ha wtiger_ha = {
    WTIGER_ENAME,
    ENGINE_WTIGER,
    wt_open_conne,
    wt_close_conne,
    //
    wt_open_sess,
    wt_close_sess,
    wt_log_flush,
    wt_begin_transa_sess,
    wt_commit_transa_sess,
    wt_reset_sess,
    //
    wt_open_curso,
    wt_open_table,
    wt_open_group,
    wt_open_index,
    wt_close_curso,
    wt_inser_curso,
    wt_reset_curso,
    wt_next_curso,
    wt_prev_curso,
    wt_sear_curso,
    wt_searn_curso,
    wt_update_curso,
    wt_remove_curso,
    wt_reconf_curso,
    set_key_wt,
    set_value_wt,
    get_key_wt,
    get_value_wt,
    //
    wt_creat_tab,
    wt_dorp_tab,
    wt_rename_tab
};

//

// rive_ha *_storage_ha_[] = {&imemo_ha, &leap_ha, &wtiger_ha, NULL};
rive_ha *_storage_ha_[] = {&wtiger_ha, NULL};

//

int open_rive_bzl(rive_conne *rvcon, char *osdb) {
    printf("open_rive_bzl open:%s\n", osdb);
    rive_ha **stora_ha = _storage_ha_;
    int inde;
    for (inde = 0x00; stora_ha[0x00]; stora_ha++, inde++) {
        if ((stora_ha[0x00])->open_conne(&(rvcon[inde].conne), osdb, 0x01)) {
            _LOG_WARN("open rive %s error!", (stora_ha[0x00])->storage_name);
            return -1;
        }
    }
    //
    return 0x00;
}

//

int close_rive_bzl(rive_conne *rvcon) {
    int inde;
    rive_ha **stora_ha = _storage_ha_;
    for (inde = 0x00; stora_ha[0x00]; stora_ha++, inde++) {
        if ((stora_ha[0x00])->close_conne(rvcon[inde].conne)) {
            _LOG_WARN("close rive %s error!", (stora_ha[0x00])->storage_name);
            return -1;
        }
        destroy_seion(rvcon[inde].slist, (stora_ha[0x00]));
    }
    //
    return 0x00;
}