
/* 
 * File:   conv_echo.h
 * Author: Administrator
 *
 * Created on 2018.4.18, AM 8:45
 */

#ifndef CONV_ECHO_H
#define CONV_ECHO_H

#ifdef __cplusplus
extern "C" {
#endif

    //

    char *echo_creat_eobje_exte(char *obje_iden, char *comd_meth, char *line_stri);
    char *echo_creat_eobje_redi(char *obje_iden, char *comd_meth, char *line_stri);
    char *echo_creat_cobje(char *obje_iden, char *comd_meth, char *line_stri);

    //

    char *echo_creat_class(char *obje_iden, char *comd_meth, char *line_stri);
    char *echo_creat_metho(char *obje_iden, char *comd_meth, char *line_stri);
    char *echo_creat_metho_exte(char *obje_iden, char *comd_meth, char *line_stri);
    char *echo_osdb_stat(osev_command *oscmd, char *line_stri, unsigned int stat_valu);


#ifdef __cplusplus
}
#endif

#endif /* CONV_ECHO_H */

