#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "elang.h"

//

static int build_result_conte(shel_resu *resu, char *resu_txt) {
    int colen = strlen(resu_txt);
    if (RESP_DATA_SIZE < colen) {
        if (lseek64(resu->res_fde, 0x00, SEEK_SET)) return -1;
        int wlen = write(resu->res_fde, resu_txt, resu->res_len);
        if (resu->res_len != wlen) return -1;
        resu->resu_type = 0x01;
    } else {
        memcpy(resu->resu_data, resu_txt, colen);
        resu->resu_type = 0x00;
    }
    resu->res_len = colen;
    //
    return 0x00;
}


//

static char *echo_class_head(char *clang_str, char *clasn, char *osdb) {
    char head_macro[MID_TEXT_LEN];
    char *last_str = lscpy(head_macro, clasn);
    lscpy(last_str, "_H");
    strupr(head_macro);
    //
    last_str = lsprif(clang_str, "#ifndef %s\n#define %s \n\n", head_macro, head_macro);
    last_str = lscpy(last_str, "#include \"osev_clie_cpp.h\" \n\n");
    last_str = lsprif(last_str, "namespace %s { \n", osdb);
    //
    return last_str;
}

static char *echo_class_tail(char *clang_str, char *clasn) {
    char head_macro[MID_TEXT_LEN];
    char *last_str = lscpy(head_macro, clasn);
    lscpy(last_str, "_H");
    strupr(head_macro);
    //
    last_str = lsprif(clang_str, "} \n\n");
    last_str = lsprif(last_str, "#endif /* %s */ \n\n", head_macro);
    //
    return last_str;
}

int echo_class_conte(shel_resu *resu, char *clang_str, char *clasn, char *osdb) {
    char resu_txt[ADVAN_OBJE_SIZE];
    MKZERO(resu_txt);
    //
    char *last_str = echo_class_head(resu_txt, clasn, osdb);
    last_str = lscpy(last_str, clang_str);
    last_str = echo_class_tail(last_str, clasn);
    //
    return build_result_conte(resu, resu_txt);
}

//

static char *echo_metho_head(char *clang_str, char *clasn, char *osdb) {
    char head_file[MID_TEXT_LEN];
    char *last_str = lscpy(head_file, clasn);
    lscpy(last_str, ".h");
    //
    last_str = lscpy(clang_str, "#include <string.h> \n");
    last_str = lsprif(last_str, "#include \"%s\" \n", head_file);
    last_str = lsprif(last_str, "using namespace %s; \n", osdb);
    //
    return last_str;
}

int echo_metho_conte(shel_resu *resu, char *clang_str, char *clasn, char *osdb) {
    char resu_txt[ADVAN_OBJE_SIZE];
    MKZERO(resu_txt);
    //
    char *last_str = echo_metho_head(resu_txt, clasn, osdb);
    last_str = lscpy(last_str, clang_str);
    //
    return build_result_conte(resu, resu_txt);
}

//

char *build_class_stru(char *clang_str, char *clasn, char *osdb, char clas_data[CDATNO_NUMB][PARAM_LENGTH]) {
    char *last_str = lsprif(clang_str, "namespace %s { \n", osdb);
    last_str = lscpy(last_str, "#pragma pack(1) \nstruct _");
    last_str = lscpy(last_str, clasn);
    last_str = lscpy(last_str, "_ { \n");
    last_str = lscpy(last_str, "osv_oid_t obje_oid; \n");
    int inde;
    for (inde = 0x00; '\0' != clas_data[inde][0x00]; inde++) {
        last_str = lscpy(last_str, clas_data[inde]);
        last_str = lscpy(last_str, "; \n");
    }
    last_str = lscpy(last_str, "};\n#pragma pack() \n");
    last_str = lscpy(last_str, "} \n");
    //
    return last_str;
}

//

char *build_meta_osize(char *clang_str, char *clasn) {
    char *last_str = lscpy(clang_str, "const int ");
    last_str = lscpy(last_str, clasn);
    last_str = lscpy(last_str, "::seri_length = sizeof(struct _");
    last_str = lscpy(last_str, clasn);
    last_str = lscpy(last_str, "_); \n");
    //
    return last_str;
}

// serialize

char *build_meta_seria(char *clang_str, char *clasn, char clas_data[CDATNO_NUMB][PARAM_LENGTH]) {
    char *last_str = lscpy(clang_str, "char *");
    last_str = lscpy(last_str, clasn);
    last_str = lsprif(last_str, "::serialize(char *data, class %s *obje) { \n", clasn);
    //
    last_str = lsprif(last_str, "memcpy(&((struct _%s_ *)data)->obje_oid, &obje->obje_oid, sizeof(osv_oid_t)); \n", clasn);
    int inde;
    for (inde = 0x00; '\0' != clas_data[inde][0x00]; inde++) {
        last_str = lsprif(last_str, "((struct _%s_ *)data)->%s = obje->%s; \n", clasn, clas_data[inde], clas_data[inde]);
    }
    last_str = lscpy(last_str, "return data + sizeof(struct _");
    last_str = lscpy(last_str, clasn);
    last_str = lscpy(last_str, "_); \n} \n");
    //
    return last_str;
}

// deserialize

char *build_meta_deseri(char *clang_str, char *clasn, char clas_data[CDATNO_NUMB][PARAM_LENGTH]) {
    char *last_str = lscpy(clang_str, "char *");
    last_str = lscpy(last_str, clasn);
    last_str = lsprif(last_str, "::deserialize(class %s *obje, char *data) { \n", clasn);
    //
    last_str = lsprif(last_str, "memcpy(&obje->obje_oid, &((struct _%s_ *)data)->obje_oid, sizeof(osv_oid_t)); \n", clasn);
    int inde;
    for (inde = 0x00; '\0' != clas_data[inde][0x00]; inde++) {
        last_str = lsprif(last_str, "obje->%s = ((struct _%s_ *)data)->%s; \n", clas_data[inde], clasn, clas_data[inde]);
    }
    last_str = lscpy(last_str, "return data + sizeof(struct _");
    last_str = lscpy(last_str, clasn);
    last_str = lscpy(last_str, "_); \n} \n");
    //
    return last_str;
}

//

int build_ointe_comple(char *meth_ointe, char ointe_data[CDATNO_NUMB][PARAM_LENGTH]) {
    char *last_str = lscpy(meth_ointe, "(");
    // printf("conve_ointe_comple\n");
    int inde = 0x00;
    if ('\0' != ointe_data[inde][0x00]) {
        last_str = lscpy(last_str, ointe_data[inde]);
        inde++;
    }
    for (; '\0' != ointe_data[inde][0x00]; inde++) {
        last_str = lscpy(last_str, ", ");
        last_str = lscpy(last_str, ointe_data[inde]);
    }
    last_str = lccpy(last_str, ')');
    //
    return 0x00;
}

//

char *build_lcon_defin(char *clang_str, char *clasn) {
    char *last_str = lscpy(clang_str, clasn);
    last_str = lscpy(last_str, "::");
    last_str = lscpy(last_str, clasn);
    last_str = lscpy(last_str, "(){");
    // last_str = lscpy(last_str, APPEN_OBJE_ID);
    last_str = lscpy(last_str, "} \n");
    //
    return last_str;
}

//
#define APPEN_OBJE_ID "creat_objeid_obj(&this->obje_oid);"

static char *appe_obje_id(char *clang_str, char *meth_body) {
    char *last_body = strchr(meth_body, '{');
    if (!last_body) return clang_str;
    char *last_str = lsncpy(clang_str, meth_body, (++last_body) - meth_body);
    //
    last_str = lscpy(last_str, APPEN_OBJE_ID);
    last_str = lscpy(last_str, last_body);
    //
    return last_str;
}

char *build_const_defin(char *clang_str, parse_metho *metho) {
    // print_metho(metho); // for test
    char *last_str = lscpy(clang_str, metho->ointe_type);
    last_str = lccpy(last_str, ' ');
    last_str = lscpy(last_str, metho->clasn);
    last_str = lscpy(last_str, "::");
    last_str = lscpy(last_str, "Create");
    // last_str = lscpy(last_str, metho->metnm);
    last_str = lscpy(last_str, metho->meth_ointe);
    // last_str = lscpy(last_str, metho->meth_body);
    last_str = appe_obje_id(last_str, metho->meth_body);
    last_str = lccpy(last_str, '\n');
    //
    return last_str;
}

//

char *build_metho_defin(char *clang_str, parse_metho *metho) {
    // print_metho(metho); // for test
    char *last_str = lscpy(clang_str, metho->ointe_type);
    last_str = lccpy(last_str, ' ');
    last_str = lscpy(last_str, metho->clasn);
    last_str = lscpy(last_str, "::");
    last_str = lscpy(last_str, metho->metnm);
    last_str = lscpy(last_str, metho->meth_ointe);
    last_str = lscpy(last_str, metho->meth_body);
    last_str = lccpy(last_str, '\n');
    //
    return last_str;
}

//

char *build_const_decla(char *clang_str, parse_metho *metho) {
    // print_metho(metho); // for test
    char *last_str = lscpy(clang_str, metho->ointe_type);
    last_str = lccpy(last_str, ' ');
    last_str = lscpy(last_str, "Create");
    // last_str = lscpy(last_str, metho->metnm);
    last_str = lscpy(last_str, metho->meth_ointe);
    last_str = lscpy(last_str, "; \n");
    //
    return last_str;
}

//

char *build_metho_decla(char *clang_str, parse_metho *metho) {
    // print_metho(metho); // for test
    char *last_str = lscpy(clang_str, metho->ointe_type);
    last_str = lccpy(last_str, ' ');
    last_str = lscpy(last_str, metho->metnm);
    last_str = lscpy(last_str, metho->meth_ointe);
    last_str = lscpy(last_str, "; \n");
    //
    return last_str;
}

//

char *build_eclas_head(char *clang_str, char *clasn) {
    return lsprif(clang_str, "class %s { \n", clasn);
}

char *build_eclas_tail(char *clang_str) {
    return lsprif(clang_str, "}; \n");
}

char *build_eclas_decla(char *clang_str, char clas_data[CDATNO_NUMB][PARAM_LENGTH]) {
    char *last_str = lscpy(clang_str, "public: \n");
    last_str = lscpy(last_str, "osv_oid_t obje_oid; \n");
    //
    int inde;
    for (inde = 0x00; '\0' != clas_data[inde][0x00]; inde++) {
        last_str = lscpy(last_str, clas_data[inde]);
        last_str = lscpy(last_str, "; \n");
    }
    //
    return last_str;
}

//
#define INCL_META_OBJE_DECLA "static class OSVBase meta_obje; \n"
#define INCL_SERIALIZE_DECLA "static char *serialize(char *data, class %s *obje); \n"
#define INCL_DESERIA_DECLA "static char *deserialize(class %s *obje, char *data); \n"
#define INCL_SERI_LENG_DECLA "static const int seri_length; \n"

char *build_meta_decla(char *clang_str, char *clasn) {
    char *last_str = lscpy(clang_str, "public:  // class meta \n");
    last_str = lscpy(last_str, INCL_META_OBJE_DECLA);
    last_str = lsprif(last_str, INCL_SERIALIZE_DECLA, clasn);
    last_str = lsprif(last_str, INCL_DESERIA_DECLA, clasn);
    last_str = lscpy(last_str, INCL_SERI_LENG_DECLA);
    return last_str;
}

//
char *build_lcon_decla(char *clang_str, char *clasn) {
    char *last_str = lscpy(clang_str, "public:  // construct \n");
    last_str = lsprif(last_str, "%s(); \n", clasn);
    return last_str;
}

//