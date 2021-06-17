
/* 
 * File:   metaob.h
 * Author: James Xu
 *
 * Created on 2017.2.13, AM 9:05
 */

#ifndef METAOB_H
#define METAOB_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif
    
//
#ifndef INVA_INDE_VALU
#define INVA_INDE_VALU      ((unsigned int)-1)
#endif

//
int creat_oattr(char *osdb);
int open_oattr(char *clasn, char *mepan, char *library, char *osdb);
int dele_oattr(char *clasn, char *mepan, char *osdb);

//
typedef struct {
    FILE *attrp;
    //
    char clasn[CLASS_LENGTH];
    char mepan[HAND_LENGTH];
    char library[MAX_PATH];
} oconte;

unsigned int open_oconte(oconte *ocont, char *osdb);
void close_oconte(oconte *ocont);
unsigned int read_oattr(oconte *ocont, unsigned int ainde);


#ifdef __cplusplus
}
#endif

#endif /* METAOB_H */

