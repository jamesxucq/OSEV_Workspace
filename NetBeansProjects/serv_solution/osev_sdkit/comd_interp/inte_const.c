#include "commo_header.h"
#include "istri_utili.h"

#include "cons_bzl.h"
#include "conoda.h"
#include "inte_const.h"

// xxx:echo();
// xxx:create();
// xxx:drop();
// xxx:rplace();
// xxx:insert();
// xxx:find();
// xxx:invoke();

static char *obje_echo(char *data_line, char **paras, char *requ_data) {
    printf("parse obje_echo\n");
    char *parse_tok = requ_data;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    char *last_str = parse_stri(data_line, paras, parse_tok);
    if (!last_str) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    return last_str;
}

static char *obje_creat(char *data_line, char **paras, char *requ_data) {
    printf("parse obje_creat\n");
    char *parse_tok = requ_data;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    printf("req_len:%d\n", req_len);
    //
    char *last_str = decode_object(data_line, paras, parse_tok, req_len);
    if (!last_str) {
        paras[0x00] = NULL;
        return NULL;
    }
    // printf("paras, [0]:|%d| [1]:|%d|\n", ((int_entry*) paras[0x00])->data, ((int_entry*) paras[0x01])->data);
    return last_str;
}

static char *obje_drop(char *data_line, char **paras, char *requ_data) {
    printf("parse obje_drop\n");
    char *parse_tok = requ_data;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    char *last_str = parse_stri(data_line, paras, parse_tok);
    if (!last_str) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    return last_str;
}

#pragma pack(1) 

struct _test_ {
    osv_oid_t obje_oid;
    int xx;
    int ax;
    int cx;
};
#pragma pack() 

static char *obje_updat(char *data_line, char **paras, char *requ_data) {
    printf("parse obje_updat\n");
    char *parse_tok = requ_data;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    char *last_str = parse_obje(data_line, paras, parse_tok);
    if (!last_str) {
        paras[0x00] = NULL;
        return NULL;
    }
    /*
        struct _test_ *test = paras[0x00];
        char temp[33];
        printf("|%s|%d|%d|%d|\n", oidstr(temp, &test->obje_oid), test->xx, test->ax, test->cx);
     */
    //
    return last_str;
}

static char *obje_inser(char *data_line, char **paras, char *requ_data) {
    printf("parse obje_inser\n");
    char *parse_tok = requ_data;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    char *last_str = parse_obje(data_line, paras, parse_tok);
    if (!last_str) {
        paras[0x00] = NULL;
        return NULL;
    }
    /*
        struct _test_ *test = paras[0x00];
        char temp[33];
        printf("|%s|%d|%d|%d|\n", oidstr(temp, &test->obje_oid), test->xx, test->ax, test->cx);
     */
    //
    return last_str;
}

static char *obje_find(char *data_line, char **paras, char *requ_data) {
    printf("parse obje_find\n");
    char *parse_tok = requ_data;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    char *last_str = decode_string(data_line, paras, parse_tok, req_len);
    if (!last_str) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    return last_str;
}

static char *obje_invok(char *data_line, char **paras, char *requ_data) {
    printf("parse obje_invok\n");
    char *parse_tok = requ_data;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    char *last_str = decode_const_invok(data_line, paras, parse_tok, req_len);
    if (!last_str) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    return last_str;
}

char* (*parse_const_tab[])(char *, char **, char *) = {
    obje_echo,
    obje_creat,
    obje_drop,
    obje_updat,
    obje_inser,
    obje_find,
    obje_invok
};

//

int valid_const() {
    return 0x00;
}


// const

static int echo_obje(prod_data *sresp, void *coval, osv_oid_t *oid, char **paras) {
    printf("echo_obje\n");
    contain *conta = (contain *) cache_value(oid, ((conoda *) coval)->conda.conto_hm);
    if (conta) {
        char oid_stri[OID_LINE_LEN];
        printf("contain:|%s|\n", oidstr(oid_stri, oid));
        cons_echo_bzl(sresp, conta);
    } else {
        char oid_stri[OID_LINE_LEN];
        printf("not found:|%s|\n", oidstr(oid_stri, oid));
        PDAT_EXCEP_TAIL(sresp, NOT_FOUND_CONTA)
        return -1;
    }
    //
    return 0x00;
}

static int creat_obje(prod_data *sresp, void *coval, osv_oid_t *oid, char **paras) {
    printf("creat_obje\n");
    contain *conta = (contain *) cache_value(oid, ((conoda *) coval)->conda.conto_hm);
    if (!conta) {
        char oid_stri[OID_LINE_LEN];
        printf("not find contain:|%s|\n", oidstr(oid_stri, oid));
        PDAT_EXCEP_TAIL(sresp, NOT_FOUND_CONTA)
        return -1;
    }
    //
    printf("cons_creat_bzl\n");
    int cons_valu = cons_creat_bzl(sresp, conta, &((conoda *) coval)->hando, &((conoda *) coval)->rvcon[conta->stora_ha->storage_type], paras);
    if (cons_valu) {
        printf("create object execep!\n");
        PDAT_EXCEP_TAIL(sresp, CREAT_OBJE_EXCE)
        return -1;
    }
    //
    return 0x00;
}

// obje::drop(obje_oid);
// obje::drop("xx()>0x00");

static int drop_obje(prod_data *sresp, void *coval, osv_oid_t *oid, char **paras) {
    printf("drop_obje\n");
    char oid_stri[OID_LINE_LEN];
    if (!paras[0x00]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    contain *conta = (contain *) cache_value(oid, ((conoda *) coval)->conda.conto_hm);
    if (!conta) {
        printf("not found:|%s|\n", oidstr(oid_stri, oid));
        PDAT_EXCEP_TAIL(sresp, NOT_FOUND_CONTA)
        return -1;
    }
    //
    printf("contain:|%s|\n", oidstr(oid_stri, oid));
    int cons_valu = cons_drop_bzl(sresp, conta, &((conoda *) coval)->handa, &((conoda *) coval)->rvcon[conta->stora_ha->storage_type], paras);
    if (cons_valu) {
        printf("drop object execep!\n");
        PDAT_EXCEP_TAIL(sresp, DROP_OBJE_EXCE)
        return -1;
    }
    //
    return 0x00;
}

// obje::updat("test:test(xx, dfa, adf)", obje_oid);
// obje::updat("test:test(xx, dfa, adf)", "xx()>0x00");

static int updat_obje(prod_data *sresp, void *coval, osv_oid_t *oid, char **paras) {
    printf("updat_obje\n");
    if (!(paras)[0x00]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    contain *conta = (contain *) cache_value(oid, ((conoda *) coval)->conda.conto_hm);
    if (!conta) {
        printf("not find contain !\n");
        PDAT_EXCEP_TAIL(sresp, NOT_FOUND_CONTA)
        return -1;
    }
    //
    int cons_valu = cons_updat_bzl(sresp, conta, &((conoda *) coval)->handa, &((conoda *) coval)->rvcon[conta->stora_ha->storage_type], paras);
    if (cons_valu) {
        printf("update object execep!\n");
        PDAT_EXCEP_TAIL(sresp, UPDAT_OBJE_EXCE)
        return -1;
    }
    //
    return 0x00;
}

// obje::insert("test:test(xx, dfa, adf)");

static int inser_obje(prod_data *sresp, void *coval, osv_oid_t *oid, char **paras) {
    printf("inser_obje\n");
    if (!paras[0x00]) {
        FDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    contain *conta = (contain *) cache_value(oid, ((conoda *) coval)->conda.conto_hm);
    if (!conta) {
        char oid_stri[OID_LINE_LEN];
        printf("not find contain:|%s|\n", oidstr(oid_stri, oid));
        FDAT_EXCEP_TAIL(sresp, NOT_FOUND_CONTA)
        return -1;
    }
    //
    printf("cons_inser_bzl\n");
    int cons_valu = cons_inser_bzl(sresp, conta, &((conoda *) coval)->handa, &((conoda *) coval)->rvcon[conta->stora_ha->storage_type], paras);
    if (cons_valu) {
        printf("insert object execep!\n");
        FDAT_EXCEP_TAIL(sresp, INSER_OBJE_EXCE)
        return -1;
    }
    //
    return 0x00;
}

// obje:find();
// obje::find("xx()>0x00");

static int find_obje(prod_data *sresp, void *coval, osv_oid_t *oid, char **paras) {
    char oid_stri[OID_LINE_LEN];
    printf("find_obje, find contain:|%s|\n", oidstr(oid_stri, oid));
    contain *conta = (contain *) cache_value(oid, ((conoda *) coval)->conda.conto_hm);
    if (!conta) {
        printf("not find contain!\n");
        FDAT_EXCEP_TAIL(sresp, NOT_FOUND_CONTA)
        return -1;
    }
    //
    int cons_valu = cons_find_bzl(sresp, conta, &((conoda *) coval)->handa, &((conoda *) coval)->rvcon[conta->stora_ha->storage_type], coval, paras);
    if (cons_valu) {
        printf("find object execep!\n");
        FDAT_EXCEP_TAIL(sresp, FIND_OBJE_EXCE)
        return -1;
    }
    //
    return 0x00;
}

// obje::each("metho(122)", obje:is_class("test"));
// obje::each("metho(122)", "obje:numb() > 0x00");

static int invok_obje(prod_data *sresp, void *coval, osv_oid_t *oid, char **paras) {
    printf("invok_obje\n");
    if (!paras[0x00]) {
        FDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    contain *conta = (contain *) cache_value(oid, ((conoda *) coval)->conda.conto_hm);
    if (!conta) {
        char oid_stri[OID_LINE_LEN];
        printf("not find contain:|%s|\n", oidstr(oid_stri, oid));
        FDAT_EXCEP_TAIL(sresp, NOT_FOUND_CONTA)
        return -1;
    }
    //
    int cons_valu = cons_each_bzl(sresp, conta, &((conoda *) coval)->hando, &((conoda *) coval)->rvcon[conta->stora_ha->storage_type], paras);
    if (cons_valu) {
        printf("each invoke object execep!\n");
        FDAT_EXCEP_TAIL(sresp, EINVO_OBJE_EXCE)
        return -1;
    }
    //
    return 0x00;
}

int (*hand_const_tab[])(prod_data *, void *, osv_oid_t *, char **) = {
    echo_obje,
    creat_obje,
    drop_obje,
    updat_obje,
    inser_obje,
    find_obje,
    invok_obje
};
