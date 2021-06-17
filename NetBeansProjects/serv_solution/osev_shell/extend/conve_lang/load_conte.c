#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "pcattr.h"
#include "load_conte.h"
//

char *load_conte(char *data, int conte_size, shel_resu *resu) {
    if (resu->resu_type) {
        if (conte_size < resu->res_len) return NULL;
        if (lseek64(resu->res_fde, 0x00, SEEK_SET)) return NULL;
        ssize_t rlen = read(resu->res_fde, data, resu->res_len);
        if (resu->res_len != rlen) return NULL;
    } else memcpy(data, resu->resu_data, resu->res_len);
    //
    return data;
}

