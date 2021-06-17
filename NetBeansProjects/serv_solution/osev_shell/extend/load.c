#include "commo_header.h"

#include "load.h"

//
#define BUFF_SIZE                        0x2000

int load_stre(int stre, char *file_name) {
    unsigned char buffer[BUFF_SIZE];
    int rlen;
    // printf("load stre\n");
    if (lseek64(stre, 0x00, SEEK_SET)) return -1;
    int from = open64(file_name, O_RDONLY);
    if (-1 == from) {
        printf("open file error! %s\n", file_name);
        return -1;
    }
    if (lseek64(from, 0x00, SEEK_SET)) {
        close(from);
        return -1;
    }
    //
    while (0 != (rlen = read(from, buffer, BUFF_SIZE))) {
        if (write(stre, buffer, rlen) != rlen)
            printf("write error!\n");
    }
    //        
    close(from);
    return 0x00;
}

int load_memo(char *memo, char *file_name) {
    int rlen;
    // printf("load memo\n");
    int from = open64(file_name, O_RDONLY);
    if (-1 == from) {
        printf("open file error! %s\n", file_name);
        return -1;
    }
    //
    if (!(rlen = read(from, memo, RESP_DATA_SIZE))) {
        printf("read file error! %s\n", file_name);
        close(from);
        return -1;
    }
    //        
    close(from);
    return 0x00;
}

//

int check_load_type(uint64 *file_len, char *file_name, int bulen) {
    struct stat64 statb;
    if (stat64(file_name, &statb) == -1) {
        printf("can not get info of %s", file_name);
        return -1;
    }
    *file_len = statb.st_size;
    if (bulen < statb.st_size) return 0x01;
    return 0x00;
}

// 0x00:OK -1:error

int hand_load(char **parae, shel_resu *resu) {
    int load_valu = 0x00;
    //
    uint64 file_len;
    quote_decode(parae[0x00]);
    int load_type = check_load_type(&file_len, parae[0x00], RESP_DATA_SIZE);
    switch (load_type) {
        case 0x00:
            load_valu = load_memo(resu->resu_data, parae[0x00]);
            resu->res_len = file_len;
            resu->resu_type = 0x00;
            break;
        case 0x01:
            load_valu = load_stre(resu->res_fde, parae[0x00]);
            resu->res_len = file_len;
            resu->resu_type = 0x01;
            break;
        case -1:
            load_valu = -1;
            break;
    }
    //
    return load_valu;
}