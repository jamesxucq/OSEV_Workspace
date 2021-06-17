
/* 
 * File:   cstri_utili.h
 * Author: james
 *
 * Created on 2021.4.26, PM1:51
 */

#ifndef CSTRI_UTILI_H
#define CSTRI_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    char *qeach_paras(char *each_line, char **paras, char *para_str);
    char *split_qeach(char *obje_ide, char *meth_str, char *para_str, char *meth_line);

    //
    char *build_query_handn(char *handn, char *clasn, char *metnm, char **paras);
  
    //
    char *crea_proj_uri(char *prou, char *cont_name, char *data);

#ifdef __cplusplus
}
#endif

#endif /* CSTRI_UTILI_H */

