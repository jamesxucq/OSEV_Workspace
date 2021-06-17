
#include "commo_header.h"
#include "opera_utili.h"

//

static void print_oid(void *obje) {
    printf("oid_stri:|%08x%08x%08x|\n"
            , ((osv_oid_t *) obje)->osev_unique
            , ((osv_oid_t *) obje)->time_stamp
            , ((osv_oid_t *) obje)->counter);
}

//

static int inse_file_hmd(OIDHMD *ohmd, FILE *fild, FILE *data) {
    printf("inse_data_db\n");
    osv_oid_i obje_id;
    rewind(data);
    while (0x00 < fread(&obje_id, sizeof (osv_oid_i), 0x01, data)) {
        print_oid(&obje_id);
        if (oidhmd_inse(ohmd, (char *) &obje_id))
            return -1;
        if (0x00 >= APPEND_DATAS(fild, &obje_id, sizeof (osv_oid_i)))
            return -1;
    }
    printf("inse_data_db, end!\n");
    return 0x00;
}


//

int merge_data_oid(FILE *filed, FILE *file1, FILE *file2) {
    printf("merge_data_oid\n");
    OIDHMD *ohmd = creat_temp_ohmd();
    if (!ohmd) return -1;
    if (inse_file_hmd(ohmd, filed, file2)) {
        oidhmd_close(ohmd, 0x00);
        oidhmd_dele(ohmd);
        return -1;
    };

    //
    osv_oid_i obje_id;
    rewind(file1);
    while (0x00 < fread(&obje_id, sizeof (osv_oid_i), 0x01, file1)) {
        print_oid(&obje_id);
        if (oidhmd_find(ohmd, (char *) &obje_id)) {
            printf("APPEND_DATAS, ");
            print_oid(&obje_id);
            if (0x00 >= APPEND_DATAS(filed, &obje_id, sizeof (osv_oid_i))) {
                oidhmd_close(ohmd, 0x00);
                oidhmd_dele(ohmd);
                return -1;
            }
        }
    }

    //
    if (oidhmd_close(ohmd, 0x00)) {
        printf("oidhmd_close, error!\n");
        oidhmd_dele(ohmd);
        return -1;
    };
    oidhmd_dele(ohmd);
    printf("merge_data_oid, end.\n");
    return 0x00;
}

//

int cartesi_product_data(FILE *filed, FILE *file1, FILE *file2) {
    printf("cartesi_product_data\n");
    //
    return 0x00;
}

//

static int inse_data_hmd(OIDHMD *ohmd, FILE *data) {
    printf("inse_data_db\n");
    osv_oid_i obje_id;
    rewind(data);
    while (0x00 < fread(&obje_id, sizeof (osv_oid_i), 0x01, data)) {
        print_oid(&obje_id);
        if (oidhmd_inse(ohmd, (char *) &obje_id))
            return -1;
    }
    printf("inse_data_db, end!\n");
    return 0x00;
}

int shared_data_oid(FILE *filed, FILE *file1, FILE *file2) {
    printf("shared_data_oid\n");
    //
    OIDHMD *ohmd = creat_temp_ohmd();
    if (!ohmd) return -1;
    if (inse_data_hmd(ohmd, file2)) {
        oidhmd_close(ohmd, 0x00);
        oidhmd_dele(ohmd);
        return -1;
    };

    //
    osv_oid_i obje_id;
    rewind(file1);
    while (0x00 < fread(&obje_id, sizeof (osv_oid_i), 0x01, file1)) {
        print_oid(&obje_id);
        if (!oidhmd_find(ohmd, (char *) &obje_id)) {
            printf("APPEND_DATAS, ");
            print_oid(&obje_id);
            if (0x00 >= APPEND_DATAS(filed, &obje_id, sizeof (osv_oid_i))) {
                oidhmd_close(ohmd, 0x00);
                oidhmd_dele(ohmd);
                return -1;
            }
        }
    }

    //
    if (oidhmd_close(ohmd, 0x00)) {
        printf("oidhmd_close, error!\n");
        oidhmd_dele(ohmd);
        return -1;
    };
    oidhmd_dele(ohmd);
    printf("shared_data_oid, end.\n");
    return 0x00;
}