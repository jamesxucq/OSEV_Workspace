/* 
 * File:   shape.h
 * Author: James Xu
 */

#ifndef SHAPE_H
#define SHAPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sha_common.h"
#include "sha_sutil.h"
#include "sha_stru.h"

////

#ifdef __cplusplus
extern "C" {
#endif

    //
#define SLIVE_INITI_POINT(PLIVE, ISIZE, FNAME) \
    PLIVE->isize = ISIZE; \
    PLIVE->elist = NULL; \
    sha_lscpy(PLIVE->file_name, FNAME);

    //
#define SLIVE_INITI_DATA(SLIVE, ISIZE, FNAME) \
    SLIVE.isize = ISIZE; \
    SLIVE.elist = NULL; \
    sha_lscpy(SLIVE.file_name, FNAME);

    //
    int32 shap_create(sha_live *pliv);
    int32 shap_destroy(sha_live *pliv);
    int32 shap_initial(sha_live *pliv);
    int32 shap_final(sha_live *pliv);
    //
    void *shap_insert(sha_live *pliv, char *idata);
    int32 shap_remove(sha_live *pliv, char *idata);
    int32 shap_remove_ex(sha_live *pliv, struct shap_list *elist);

    //
    int shap_load(char *idata, sha_live *pliv, uint32 einde);
    int shap_save(sha_live *pliv, uint32 einde, char *idata);
    // for test
    int32 shap_echo(sha_live *pliv);
    //
#ifdef __cplusplus
}
#endif

//

#endif /* SHAPE_H */

