

#include "stora_handl.h"
#include "conte_resou.h"
#include "rive_stru.h"
#include "dyli_list.h"
// #include "wiredtiger/wiredtiger.h"

static void print_oid(void *obje) {
    printf("oid_stri:|%08x%08x%08x|\n"
            , ((osv_oid_t *) obje)->osev_unique
            , ((osv_oid_t *) obje)->time_stamp
            , ((osv_oid_t *) obje)->counter);
}

int load_proj_data(FILE *resul, riv_curso_t *procu, rive_ha *stora_ha, dyli_data *dldap, void *obje_data) {
    // printf("1 --- procu:%016X\n", procu);
    stora_ha->set_key(procu, ((osv_oid_i *) obje_data)->stoid);
    if (stora_ha->sear_curso(procu)) return -1;
    dldap->solve(obje_data, procu);
    //
    if (0x00 >= APPEND_DATAS(resul, obje_data, dldap->data_size))
        return -1;
    //
    print_oid(obje_data);
    return 0x00;
}