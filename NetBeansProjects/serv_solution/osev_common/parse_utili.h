
/* 
 * File:   parse_utili.h
 * Author: James Xu
 *
 * Created on 2017.1.23, PM 3:38
 */

#ifndef PARSE_UTILI_H
#define PARSE_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    int check_space_type(char *clasn, char *metnm, char *decla, char *space);
    char *split_space(char *clasn, char *metnm, char *space);
    char *split_space_ex(char *clasn, char *metnm, char *space);
    char *split_metho_ex(char *clasn, char *metnm, char *decla, char *space);
    char *build_retyp_parse(char *retyn, char *parsn, char *handn);
    char *build_obsc_name(char *osize, char *bindn, char *solvn, char *clasn);
    char *split_metn(char *metnm, char *parsn, char *space);
    char *split_clame(char *clame, char *space);

    //


#ifdef __cplusplus
}
#endif

#endif /* PARSE_UTILI_H */

