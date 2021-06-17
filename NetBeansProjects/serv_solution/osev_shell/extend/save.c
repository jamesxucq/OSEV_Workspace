#include "commo_header.h"

#include "save.h"

//
#define BUFF_SIZE                        0x2000

int save_stre(char *file_name, int stre) {
    unsigned char buffer[BUFF_SIZE];
    int rlen, wlen;
    //
    int desti = open64(file_name, O_WRONLY | O_CREAT, 0666);
    if (-1 == desti) {
        printf("open file error! %s\n", file_name);
        return -1;
    }
    //
    if (lseek64(stre, 0x00, SEEK_SET)) return -1;
    do {
        rlen = read(stre, buffer, BUFF_SIZE);
        if (!rlen) continue;
        //
        if (!(wlen = write(desti, buffer, rlen))) continue;
        if (wlen != rlen) {
            printf("write file error! %s\n", file_name);
            close(desti);
            return -1;
        }
    } while (0 < rlen && 0 < wlen);
    //        
    close(desti);
    return 0x00;
}

int save_memo(char *file_name, char *memo, uint64 slen) {
    int wlen, tatol = 0x00;
    //
    int desti = open64(file_name, O_WRONLY | O_CREAT, 0666);
    if (-1 == desti) {
        printf("open file error! %s\n", file_name);
        return -1;
    }
    //
    do {
        if (!(wlen = write(desti, memo + tatol, slen - tatol))) {
            printf("write file error! %s\n", file_name);
            close(desti);
            return -1;
        }
        tatol += wlen;
    } while (slen > tatol);
    //        
    close(desti);
    return 0x00;
}

// 0x00:OK -1:error

int hand_save(char **parae, shel_resu *resu) {
    quote_decode(parae[0x00]);
    if (resu->resu_type) {
        if (save_stre(parae[0x00], resu->res_fde)) {
            printf("save file %s error!\n", parae[0x00]);
        }
    } else {
        if (save_memo(parae[0x00], resu->resu_data, resu->res_len)) {
            printf("save file %s error!\n", parae[0x00]);
        }
    }
    //
    return 0x00;
}