#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "load_conte.h"
#include "clas_list.h"
#include "parse.h"
#include "conver.h"
#include "elang.h"
#include "conv_gcc_cpp.h"

//
// odb:echo()|extend:convert(GCC); // fix me
// odb:echo()|extend:convert("test.cla", GCC); // fix me
// 0x00:OK -1:error

#define RETU_DELE(CLASM, RET_VAL) { \
        CLAM_STRU_DELE(CLASM) \
        return RET_VAL; \
    }

int conve_gcc_cpp(char **parae, shel_resu *resu, char *osdb) {
    printf("conve_gcc_cpp, resu->resu_type:%d name:|%s|\n", resu->resu_type, parae[0x00]);
    char load_data[ADVAN_OBJE_SIZE];
    if (!load_conte(load_data, ADVAN_OBJE_SIZE, resu)) return -1;
    //
    printf("1\n");
    class_meta clasm;
    memset(&clasm, '\0', sizeof (class_meta));
    clasm.conte_type = conv_conte_type(load_data);
    printf("clasm.conte_type:%u\n", clasm.conte_type);
    if (!clasm.conte_type) return -1;
    if (!parse_class_conte(&clasm, load_data)) RETU_DELE(clasm, -1)
        //
    printf("2\n");
    char clang_txt[ADVAN_OBJE_SIZE];
    MKZERO(clang_txt);
    if (CTYPE_CLAS_CONTE & clasm.conte_type) {
        if (!conve_class_conte(clang_txt, &clasm)) RETU_DELE(clasm, -1)
        echo_class_conte(resu, clang_txt, clasm.clasn, osdb);
    } else if (CTYPE_METH_CONTE & clasm.conte_type) {
        if (!conve_metho_conte(clang_txt, &clasm, osdb)) RETU_DELE(clasm, -1)
        echo_metho_conte(resu, clang_txt, clasm.clasn, osdb);
    }
    //
    printf("3\n");
    CLAM_STRU_DELE(clasm)
    return 0x00;
}
