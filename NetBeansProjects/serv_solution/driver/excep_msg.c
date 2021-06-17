
#include "commo_header.h"
#include "excep_msg.h"

//

typedef struct {
    unsigned int excep_code;
    char *excep_msg;
} excmsg;

static const excmsg excelist[] = {
    {INVA_PARA_EXCE, "Invalid param error!"},
    {NOT_FOUND_CONTA, "Not found contain!"},
    {DROP_OBJE_EXCE, "Drop objec error!"},
    {FACT_QUER_EXCE, "Facto query error!"},
    {CREAT_OBJE_EXCE, "Create object error!"},
    {CREAT_CONTA_EXCE, "Create contain error!"},
    {EINVO_OBJE_EXCE, "Each invoke object error!"},
    {FIND_OBJE_EXCE, "Find object error!"},
    {INSER_OBJE_EXCE, "Insert object error!"},
    {UPDAT_OBJE_EXCE, "Update object error!"},
    {RELOA_CLAS_EXCE, "Reload class error!"},
    {CLAS_INTEG_EXCE, "Class integri error!"},
    {CLAS_INFO_EXCE, "Get class info error!"},
    {DROP_CLAS_EXCE, "Drop class error!"},
    {COMP_CLAS_EXCE, "Compile class error!"},
    {CREAT_CLAS_EXCE, "Create class error!"},
    {CLAS_NOT_FOUND, "Not found class!"},
    {RELOA_METH_EXCE, "Reload method error!"},
    {DROP_METH_EXCE, "Drop method error!"},
    {COMP_METH_EXCE, "Compile method error!"},
    {CREAT_METH_EXCE, "Create method error!"},
    {METH_NOT_FOUND, "Not found method!"},
    {CLOSE_ODB_EXCE, "Close odb error!"},
    {OPEN_ODB_EXCE, "Open odb error!"},
    {SHOW_ODB_EXCE, "Show odb error!"},
    {QUER_ASTAT_EXCE, "Query all odb status error!"},
    {SHOW_AODB_EXCE, "Show all odb error!"},
    {0x00, NULL}
};

//
#define EXCEP_TEXT(TEXT, TABLE, EXCEP) { \
    excmsg *item; \
    for(item = (excmsg *)TABLE; item->excep_code; ++item) \
        if(EXCEP == item->excep_code) break; \
    TEXT = item->excep_msg; \
}

//
#define STACKBUF_LEN 256

static const char *excep_stri(int exce_numb) {
    static char excstr[STACKBUF_LEN];
    char *excep_msg;
    EXCEP_TEXT(excep_msg, excelist, exce_numb)
    if (!excep_msg) {
        sprintf(excstr, "%08X: Unknown exception", exce_numb);
        excep_msg = excstr;
    }
    return excep_msg;
}

void output_except(char *exce_data, int exce_len) {
    if (EXCEP_LENG == exce_len)
        printf("Exception: (%08X)%s\n", ((unsigned int*) exce_data)[0x00], excep_stri(((unsigned int*) exce_data)[0x00]));
    else if (OSEV_ATTACH_EXCE == ((unsigned int*) exce_data)[0x00]) {
        exce_data[exce_len] = '\0';
        printf("Exception: (%08X)%s\n", ((unsigned int*) exce_data)[0x00], exce_data + EXCEP_LENG);
    } else printf("Exception: Unknown exception!\n");
}