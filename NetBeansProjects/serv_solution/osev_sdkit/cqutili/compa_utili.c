

#include "stora_handl.h"
#include "compa_utili.h"
#include "dyli_list.h"
#include "conte_resou.h"

// not equal

int lid_text_noteq(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, char *stri_valu) {
    printf("lid_text_noteq\n");
    const char *value;
    osv_oid_i obje_id;
    //
    mapid_unique(&obje_id);
    while (!stora_ha->next_curso(lidcu)) {
        stora_ha->get_key(lidcu, &obje_id.stoid);
        stora_ha->get_value(lidcu, &value);
        //
        if (strcmp(stri_valu, value)) {
            if (0x00 >= APPEND_DATAS(resul, &obje_id, sizeof (osv_oid_i))) return -1;
        }
    }
    //
    return 0x00;
}

int lid_lolo_noteq(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, long long lolo_valu) {
    printf("lid_lolo_noteq\n");
    int value;
    osv_oid_i obje_id;
    //
    mapid_unique(&obje_id);
    while (!stora_ha->next_curso(lidcu)) {
        stora_ha->get_key(lidcu, &obje_id.stoid);
        stora_ha->get_value(lidcu, &value);
        // printf("value:%d\n", value);
        if (value != lolo_valu) {
            if (0x00 >= APPEND_DATAS(resul, &obje_id, sizeof (osv_oid_i))) return -1;
        }
    }
    //
    return 0x00;
}

int lid_doub_noteq(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, double doub_valu) {
    printf("lid_doub_noteq\n");
    double value;
    osv_oid_i obje_id;
    //
    mapid_unique(&obje_id);
    while (!stora_ha->next_curso(lidcu)) {
        stora_ha->get_key(lidcu, &obje_id.stoid);
        stora_ha->get_value(lidcu, &value);
        // printf("value:%d\n", value);
        if (value != doub_valu) {
            if (0x00 >= APPEND_DATAS(resul, &obje_id, sizeof (osv_oid_i))) return -1;
        }
    }
    //
    return 0x00;
}

// equal

int lid_text_equal(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, char *stri_valu) {
    printf("lid_text_equal\n");
    const char *value;
    osv_oid_i obje_id;
    //
    mapid_unique(&obje_id);
    while (!stora_ha->next_curso(lidcu)) {
        stora_ha->get_key(lidcu, &obje_id.stoid);
        stora_ha->get_value(lidcu, &value);
        //
        if (!strcmp(stri_valu, value)) {
            if (0x00 >= APPEND_DATAS(resul, &obje_id, sizeof (osv_oid_i))) return -1;
        }
    }
    //
    return 0x00;
}

//

int lid_lolo_equal(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, long long lolo_valu) {
    printf("lid_lolo_equal\n");
    int value;
    osv_oid_i obje_id;
    //
    mapid_unique(&obje_id);
    while (!stora_ha->next_curso(lidcu)) {
        stora_ha->get_key(lidcu, &obje_id.stoid);
        stora_ha->get_value(lidcu, &value);
        // printf("value:%d\n", value);
        if (value == lolo_valu) {
            if (0x00 >= APPEND_DATAS(resul, &obje_id, sizeof (osv_oid_i))) return -1;
        }
    }
    //
    return 0x00;
}
//

int lid_doub_equal(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, double doub_valu) {
    printf("lid_doub_equal\n");
    double value;
    osv_oid_i obje_id;
    //
    mapid_unique(&obje_id);
    while (!stora_ha->next_curso(lidcu)) {
        stora_ha->get_key(lidcu, &obje_id.stoid);
        stora_ha->get_value(lidcu, &value);
        // printf("value:%d\n", value);
        if (value == doub_valu) {
            if (0x00 >= APPEND_DATAS(resul, &obje_id, sizeof (osv_oid_i))) return -1;
        }
    }
    //
    return 0x00;
}

int lid_rid_equal(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, char *rid_valu) {
    printf("lid_rid_equal\n");

    //
    return 0x00;
}

// great

int lid_text_great(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, char *stri_valu) {
    printf("lid_text_great\n");
    const char *value;
    osv_oid_i obje_id;
    //
    mapid_unique(&obje_id);
    while (!stora_ha->next_curso(lidcu)) {
        stora_ha->get_key(lidcu, &obje_id.stoid);
        stora_ha->get_value(lidcu, &value);
        //
        if (0x00 > strcmp(stri_valu, value)) {
            if (0x00 >= APPEND_DATAS(resul, &obje_id, sizeof (osv_oid_i))) return -1;
        }
    }
    //
    return 0x00;
}

int lid_lolo_great(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, long long lolo_valu) {
    printf("lid_lolo_great, lolo_valu:%lld\n", lolo_valu);
    int value;
    osv_oid_i obje_id;
    //
    mapid_unique(&obje_id);
    // printf("osev_unique:|%08x|\n", obje_id.stoidosev_unique);
    while (!stora_ha->next_curso(lidcu)) {
        stora_ha->get_key(lidcu, &obje_id.stoid);
        stora_ha->get_value(lidcu, &value);
        // printf("value:%d\n", value);
        if (value > lolo_valu) {
            if (0x00 >= APPEND_DATAS(resul, &obje_id, sizeof (osv_oid_i))) return -1;
        }
    }
    //
    return 0x00;
}

int lid_doub_great(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, double doub_valu) {
    printf("lid_doub_great\n");
    double value;
    osv_oid_i obje_id;
    //
    mapid_unique(&obje_id);
    while (!stora_ha->next_curso(lidcu)) {
        stora_ha->get_key(lidcu, &obje_id.stoid);
        stora_ha->get_value(lidcu, &value);
        // printf("value:%d\n", value);
        if (value > doub_valu) {
            if (0x00 >= APPEND_DATAS(resul, &obje_id, sizeof (osv_oid_i))) return -1;
        }
    }
    //
    return 0x00;
}

// less equal

int lid_text_leseq(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, char *stri_valu) {
    printf("lid_text_leseq\n");
    const char *value;
    osv_oid_i obje_id;
    //
    mapid_unique(&obje_id);
    while (!stora_ha->next_curso(lidcu)) {
        stora_ha->get_key(lidcu, &obje_id.stoid);
        stora_ha->get_value(lidcu, &value);
        //
        if (0x00 <= strcmp(stri_valu, value)) {
            if (0x00 >= APPEND_DATAS(resul, &obje_id, sizeof (osv_oid_i))) return -1;
        }
    }
    //
    return 0x00;
}

int lid_lolo_leseq(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, long long lolo_valu) {
    printf("lid_lolo_leseq\n");
    int value;
    osv_oid_i obje_id;
    //
    mapid_unique(&obje_id);
    while (!stora_ha->next_curso(lidcu)) {
        stora_ha->get_key(lidcu, &obje_id.stoid);
        stora_ha->get_value(lidcu, &value);
        // printf("value:%d\n", value);
        if (value <= lolo_valu) {
            if (0x00 >= APPEND_DATAS(resul, &obje_id, sizeof (osv_oid_i))) return -1;
        }
    }
    //
    return 0x00;
}

int lid_doub_leseq(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, double doub_valu) {
    printf("lid_doub_leseq\n");
    double value;
    osv_oid_i obje_id;
    //
    mapid_unique(&obje_id);
    while (!stora_ha->next_curso(lidcu)) {
        stora_ha->get_key(lidcu, &obje_id.stoid);
        stora_ha->get_value(lidcu, &value);
        // printf("value:%d\n", value);
        if (value <= doub_valu) {
            if (0x00 >= APPEND_DATAS(resul, &obje_id, sizeof (osv_oid_i))) return -1;
        }
    }
    //
    return 0x00;
}


// less

int lid_text_less(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, char *stri_valu) {
    printf("lid_text_less\n");
    const char *value;
    osv_oid_i obje_id;
    //
    mapid_unique(&obje_id);
    while (!stora_ha->next_curso(lidcu)) {
        stora_ha->get_key(lidcu, &obje_id.stoid);
        stora_ha->get_value(lidcu, &value);
        //
        if (0x00 < strcmp(stri_valu, value)) {
            if (0x00 >= APPEND_DATAS(resul, &obje_id, sizeof (osv_oid_i))) return -1;
        }
    }
    //
    return 0x00;
}

int lid_lolo_less(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, long long lolo_valu) {
    printf("lid_lolo_less\n");
    int value;
    osv_oid_i obje_id;
    //
    mapid_unique(&obje_id);
    while (!stora_ha->next_curso(lidcu)) {
        stora_ha->get_key(lidcu, &obje_id.stoid);
        stora_ha->get_value(lidcu, &value);
        // printf("value:%d\n", value);
        if (value < lolo_valu) {
            if (0x00 >= APPEND_DATAS(resul, &obje_id, sizeof (osv_oid_i))) return -1;
        }
    }
    //
    return 0x00;
}

int lid_doub_less(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, double doub_valu) {
    printf("lid_doub_less\n");
    double value;
    osv_oid_i obje_id;
    //
    mapid_unique(&obje_id);
    while (!stora_ha->next_curso(lidcu)) {
        stora_ha->get_key(lidcu, &obje_id.stoid);
        stora_ha->get_value(lidcu, &value);
        // printf("value:%d\n", value);
        if (value < doub_valu) {
            if (0x00 >= APPEND_DATAS(resul, &obje_id, sizeof (osv_oid_i))) return -1;
        }
    }
    //
    return 0x00;
}


//

int lid_text_greeq(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, char *stri_valu) {
    printf("lid_text_greeq\n");
    const char *value;
    osv_oid_i obje_id;
    //
    mapid_unique(&obje_id);
    while (!stora_ha->next_curso(lidcu)) {
        stora_ha->get_key(lidcu, &obje_id.stoid);
        stora_ha->get_value(lidcu, &value);
        //
        if (0x00 >= strcmp(stri_valu, value)) {
            if (0x00 >= APPEND_DATAS(resul, &obje_id, sizeof (osv_oid_i))) return -1;
        }
    }
    //
    return 0x00;
}

int lid_lolo_greeq(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, long long lolo_valu) {
    printf("lid_lolo_greeq\n");
    int value;
    osv_oid_i obje_id;
    //
    mapid_unique(&obje_id);
    while (!stora_ha->next_curso(lidcu)) {
        stora_ha->get_key(lidcu, &obje_id.stoid);
        stora_ha->get_value(lidcu, &value);
        // printf("value:%d\n", value);
        if (value >= lolo_valu) {
            if (0x00 >= APPEND_DATAS(resul, &obje_id, sizeof (osv_oid_i))) return -1;
        }
    }
    //
    return 0x00;
}

int lid_doub_greeq(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, double doub_valu) {
    printf("lid_doub_greeq\n");
    double value;
    osv_oid_i obje_id;
    //
    mapid_unique(&obje_id);
    while (!stora_ha->next_curso(lidcu)) {
        stora_ha->get_key(lidcu, &obje_id.stoid);
        stora_ha->get_value(lidcu, &value);
        // printf("value:%d\n", value);
        if (value >= doub_valu) {
            if (0x00 >= APPEND_DATAS(resul, &obje_id, sizeof (osv_oid_i))) return -1;
        }
    }
    //
    return 0x00;
}
