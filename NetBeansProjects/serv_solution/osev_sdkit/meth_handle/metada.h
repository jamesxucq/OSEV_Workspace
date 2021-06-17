
/* 
 * File:   metada.h
 * Author: James Xu
 *
 * Created on 2017.2.13, AM 9:05
 */

#ifndef METADA_H
#define METADA_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif
    
//
#ifndef INVA_INDE_VALU
#define INVA_INDE_VALU      ((unsigned int)-1)
#endif

//
int creat_dattr(char *osdb);
int open_dattr(char *clasn, char *library, char *osdb);
int dele_dattr(char *clasn, char *osdb);

//
typedef struct {
    FILE *attrp;
    //
    char clasn[CLASS_LENGTH];
    char library[MAX_PATH];
} dconte;

unsigned int open_dconte(dconte *dcont, char *osdb);
void close_dconte(dconte *dcont);
unsigned int read_dattr(dconte *dcont, unsigned int ainde);


#ifdef __cplusplus
}
#endif

#endif /* METADA_H */

