
#include <sys/stat.h>
#include <unistd.h>

//
#include "sha_common.h"
#include "sha_stru.h"

#include "sha_sutil.h"
#include "shap_utility.h"
#include "creat_shape.h"
#include "shap_entry.h"
#include "shap_cache.h"
//

#include "shape.h"
//

int32 shap_create(sha_live *pliv) {
    if (FILE_EXIST(pliv->file_name)) {
        if (build_shape_enviro(pliv->file_name, pliv->isize))
            return -1;
    }
    return 0x00;
}

int32 shap_destroy(sha_live *pliv) {
    if (destroy_shape_enviro(pliv->file_name)) return -1;
    return 0x00;
}

//

int32 shap_initial(sha_live *pliv) {
    pliv->fpiden = fopen(pliv->file_name, "rb+");
    if (!pliv->fpiden) return -1;
    if (load_entry(&pliv->elist, pliv->fpiden, pliv->isize))
        return -1;
    //
    return 0x00;
}

int32 shap_final(sha_live *pliv) {
    if (pliv->fpiden) fclose(pliv->fpiden);
    save_cache(pliv->elist);
    return 0x00;
}

//

void *shap_insert(sha_live *pliv, char *idata) {
    uint32 einde = find_idle_iden(pliv->fpiden, pliv->isize);
    // printf("shap_insert einde:%u\n", einde);
    if (INVA_INDE_VALU == einde) return NULL;
    if (INVA_INDE_VALU == write_iden_data(pliv->fpiden, einde, idata, pliv->isize))
        return NULL;
    //
    struct shap_list *shap_data;
    appe_shap_list(shap_data, pliv->elist, einde, idata, pliv->isize, NULL)
    return shap_data->idata;
}

//

int32 shap_remove(sha_live *pliv, char *idata) {
    struct shap_list *shap_data = cache_find(pliv->elist, idata);
    if (!shap_data) return 0x01;
    if (addi_idle_iden(pliv->fpiden, shap_data->einde, pliv->isize))
        return -1;
    //
    dele_shap_list(pliv->elist, shap_data)
    return 0x00;
}

int32 shap_remove_ex(sha_live *pliv, struct shap_list *elist) {
    if (addi_idle_iden(pliv->fpiden, elist->einde, pliv->isize))
        return -1;
    //
    dele_shap_list(pliv->elist, elist)
    return 0x00;
}

//

int shap_load(char *idata, sha_live *pliv, uint32 einde) {
    if (INVA_INDE_VALU == read_iden_data(idata, pliv->isize, pliv->fpiden, einde))
        return -1;
    return 0x00;
}

int shap_save(sha_live *pliv, uint32 einde, char *idata) {
    if (INVA_INDE_VALU == write_iden_data(pliv->fpiden, einde, idata, pliv->isize))
        return -1;
    return 0x00;
}

// for test

int32 shap_echo(sha_live *pliv) {
    struct entry_id ident;
    if (fseek(pliv->fpiden, 0x00, SEEK_SET)) return 0x01;
    int line_size = sizeof (struct entry_id)+pliv->isize;
    int inde;
    for (inde = 0x00;; inde++) {
        if (fseek(pliv->fpiden, line_size * inde, SEEK_SET))
            return 0x01;
        if (0 >= fread(&ident, sizeof (struct entry_id), 0x01, pliv->fpiden))
            return 0x01;
        printf("inde:%d prev_sibli:%u next_sibli:%u\n", inde, ident.prev_sibli, ident.next_sibli);
    }
    //
    return 0x00;
}