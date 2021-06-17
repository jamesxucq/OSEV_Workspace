
/* 
 * File:   conv_utili.h
 * Author: Administrator
 *
 * Created on 2018.3.27, PM 3:01
 */

#ifndef CONV_UTILI_H
#define CONV_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct paras_node {
        const char *stri;
        char *value;
    };

#define PARAS_VALUE(STRI, TABLE) { \
    struct paras_node *item; \
    for(item = (struct paras_node *)TABLE; item->stri; ++item) \
        if(!strcmp(item->stri, STRI)) break; \
    strcpy(STRI, item->value); \
}

//
    int sconv_statu_para(char **paras);
    int sconv_stati_para(char **paras);

    //
    int sconv_echo_styl(char **paras, char *obje_iden);
    int sconv_open_styl(char **paras, char *obje_iden);
    int sconv_close_styl(char **paras, char *obje_iden, char *sline);
    int sconv_statu_styl(char **paras, char *obje_iden);
    int sconv_stati_styl(char **paras, char *obje_iden);
    
    //
    void pconv_list_para(char **paras);
    int pconv_role_para(char **paras, char *obje_iden);
    void pconv_user_para(char **paras);

    //
    int lconv_foup_para(unsigned int mvalu, char **paras);


#ifdef __cplusplus
}
#endif

#endif /* CONV_UTILI_H */

