
#ifndef STRI_UTIL_H
#define STRI_UTIL_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //    
#define OCLIE_TABLE "    "

    //
    int creat_runcomd_directory(char *comd_dire, char *leve_dire);
    char *runcomd_name(char *file_name);
    char *levecomd_name(char *leve_dire, char *file_name);

    //
    // 0x00:object method 0x01:only method 0x02:command
    int comd_meth_type(char *stri);
    char *method_space(char *name, char *stri);
    char *split_obje_metho(char *obje, char *metho, char *stri);
    char *next_param(char *para_str, char *stri);

    // 0:yes -1:no
    int accep_clie_metho(char *line_stri, char* obje_ide);
    int accep_osev_metho(char *line_stri, char *clie_obje, char *osev_obje);
    int accep_osdb_metho(char *line_stri, char *clie_obje, char *osdb_obje, char *exte_obje);
    int accep_user_metho(char *line_stri);
    // 0:yes -1:no
    int is_defin_class(char *line_stri);
    int is_defin_metho(char *line_stri);
    int is_opera_obje(char *line_stri);
    int is_opera_conta(char *line_stri);

    // 0:finish 0x01:continue -1:error 
    int invok_metho_finis(char *line_stri);
    int class_defin_finis(char *line_stri);
    int metho_defin_finis(char *line_stri);
    int opera_objec_finis(char *line_stri);
    int opera_conta_finis(char *line_stri);

    // 
    char *hide_command(char *line_stri);
    char *have_nspace(char *para_str);

    //
    int have_defa_obje(char *line_stri);
    int creat_class_metho(char *obje, char *metho);
    int check_redirect_obje(char *line_stri);
#define is_creat_obje(obje, metho) strcmp(obje, metho)
    //
    int single_command(char comd_stri[PARAM_NUMB][LARGE_TEXT_SIZE], char *cline_stri);
    int multi_command(char comd_stri[PARAM_NUMB][LARGE_TEXT_SIZE], char *cline_stri);

    //
    char *analy_const_eobje_exte(char *paras_str, char *line_stri);
    char *analy_const_eobje_redi(char *redi_obje, char *paras_str, char *line_stri);
    char *analy_const_cobje(char *redi_obje, char *paras_str, char *line_stri, char *clasn);
    char *analy_statu_open(char *paras_str, char *line_stri, char *obje_iden);
    char *analy_statu_stati(char *paras_str, char *line_stri, char *obje_iden);

    //
    char *find_paras_conte(char *paras, char *coline);

    //

    struct auth_dat {
        char user_name[USERN_LENGTH];
        char pass_word[PASWD_LENGTH];
    };

    typedef struct {
        ;
        char osev_osdb[OSEV_LENGTH];
        serv_addr saddr;
        struct auth_dat auth;
    } svod_auth;

    //
#define URISTR_ILLEGAL  -1
#define HOST_ONLY_URI   0x01
#define USER_HOST_OSDB  0x02
#define HOST_OSDB_URI   0x03
#define USER_HOST_URI   0x04

    int parse_conne_uristr(svod_auth *clie_auth, const char *uri_stri);
    //
    char *split_uristr_osdb(char *osev_osdb, const char *uri_stri);

    //
    void osevPrintError(char *err_labe, int err_num);
    void ocliePrintError(char *err_labe, int err_num);

    //
    char *inser_tail(char **stri, char *posi);

    //

    void comple_osev_iden(char *obje, char *packa);
    int valid_osev_iden(char *obje);

#ifdef __cplusplus
}
#endif

#endif /* STRI_UTIL_H */

