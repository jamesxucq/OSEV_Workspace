#include <fcntl.h>
#include <unistd.h>

#include "clie_struct.h"

//

int resu_initial(shel_resu *resu) {
    resu->resu_type = 0x00;
    resu->res_len = 0x00;
    //
    char result_name[L_tmpnam];
    resu->res_fde = open64(tmpnam(result_name), O_RDWR | O_CREAT, 0666);
    if (-1 == resu->res_fde) return -1;
    unlink(result_name);
    if (lseek64(resu->res_fde, 0x00, SEEK_SET)) return -1;
    printf("result_name:%s\n", result_name);
    //
    return 0x00;
}

//

void reset_result(shel_resu *resu) {
    if (resu->resu_type) {
        lseek64(resu->res_fde, 0x00, SEEK_SET);
    }
    resu->resu_type = 0x00;
    resu->res_len = 0x00;
}

//

void final_result(shel_resu *resu) {
    if (-1 != resu->res_fde) close(resu->res_fde);
}