
#include "invo_bzl.h"
#include "conattr.h"

#include "creaq.h"


//

int qcreat_conta_obje(riv_sessi_t *seion, rive_ha *stora_ha, char *osdb, char *cont_name, uint32 stora_type, char *clas_type) {
    // riv_creat_bzl(slist->seion, osdb, paras[0x00], paras[0x01], paras[0x02]);
    char clas_data[CDATNO_NUMB][PARAM_LENGTH];
    char forma_types[TYPES_LENGTH];
    printf("osdb:%s cont_name:%s clas_type:%s\n", osdb, cont_name, clas_type);
    if (parse_cdata_bzl(clas_data, osdb, clas_type)) {
        _LOG_INFO("Can not find class!");
        return -1;
    }
    if (conve_conta_types(forma_types, clas_data)) return -1;
    printf("forma_types:%s\n", forma_types);
    if (stora_ha->creat_conta(seion, cont_name, forma_types)) return -1;
    _LOG_DEBUG("creat contain %s OK!", cont_name);
    addi_cattr(cont_name, stora_type, clas_type, osdb);
    _LOG_DEBUG("addi cattr OK!");
    //
    return 0x00;
}