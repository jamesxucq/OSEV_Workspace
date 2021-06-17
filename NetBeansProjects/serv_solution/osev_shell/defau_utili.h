
/* 
 * File:   defau_utili.h
 * Author: Administrator
 *
 * Created on 2018.4.25, AM 9:17
 */

#ifndef DEFAU_UTILI_H
#define DEFAU_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int defva_stat_echo(char **paras, char *obje_iden, char *sline);
    int defva_stat_open(char **paras, char *obje_iden, char *sline);
    void defva_stat_statu(char **paras, char *sline);
    void defva_stat_stati(char **paras, char *sline);

    //
    void defva_priv_role(char **paras, char *obje_iden);


#ifdef __cplusplus
}
#endif

#endif /* DEFAU_UTILI_H */

