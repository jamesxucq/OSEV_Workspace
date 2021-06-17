
#include "osev_common/commo_header.h"
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
    {RELOA_CLAS_OK, "Reload class OK!"},
    {RELOA_CLAS_EXCE, "Reload class error!"},
    {CLAS_INTEG_EXCE, "Class integri error!"},
    {CLAS_INTEG_OK, "Class integri pass!"},
    {CLAS_INFO_EXCE, "Get class info error!"},
    {DROP_CLAS_OK, "Drop class OK!"},
    {DROP_CLAS_EXCE, "Drop class error!"},
    {CREAT_CLAS_OK, "Create class OK!"},
    {COMP_CLAS_EXCE, "Compile class error!"},
    {CREAT_CLAS_EXCE, "Create class error!"},
    {CLAS_NOT_FOUND, "Not found class!"},
    {RELOA_METH_OK, "Reload method OK!"},
    {RELOA_METH_EXCE, "Reload method error!"},
    {DROP_METH_OK, "Drop method OK!"},
    {DROP_METH_EXCE, "Drop method error!"},
    {CREAT_METH_OK, "Create method OK!"},
    {COMP_METH_EXCE, "Compile method error!"},
    {CREAT_METH_EXCE, "Create method error!"},
    {METH_NOT_FOUND, "Not found method!"},
    {QUER_OSTAT_EXCE, "Query odb status error!"},
    {CLOSE_ODB_OK, "Close odb OK!"},
    {CLOSE_ODB_EXCE, "Close odb error!"},
    {OPEN_ODB_OK, "Open odb OK!"},
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

const char *excep_stri(int exc_num) {
    static char excstr[STACKBUF_LEN];
    char *excep_msg;
    EXCEP_TEXT(excep_msg, excelist, exc_num)
    if (!excep_msg) {
        sprintf(excstr, "%08X: Unknown exception", exc_num);
        excep_msg = excstr;
    }
    return excep_msg;
}

void excep_echo(char *exce_data, int exce_len) {
    if (sizeof (unsigned int) == exce_len)
        printf("Exception: %s\n", excep_stri(((unsigned int*) exce_data)[0x00]));
    else printf("Unknown exception!\n");
}