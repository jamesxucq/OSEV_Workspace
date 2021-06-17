#include "istri_utili.h"

#include "quer_bzl.h"
#include "conoda.h"
#include "inte_query.h"

//
// odb:echo();
// odb:create();
// odb:drop();
// odb:find();
// odb:invoke();
// odb:factory();

static char *query_echo(char *data_line, char **paras, char *requ_data) {
    printf("parse query_echo\n");
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

static char *query_creat(char *data_line, char **paras, char *requ_data) {
    printf("parse query_creat\n");
    char *parse_tok = requ_data;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    char *last_str = decode_general(data_line, paras, parse_tok, req_len);
    if (!last_str) {
        paras[0x00] = NULL;
        return NULL;
    }
    // printf("paras[0x00]:|%s| paras[0x01]:|%s| paras[0x02]:|%s|\n", paras[0x00], paras[0x01], paras[0x02]);
    return last_str;
}

static char *query_drop(char *data_line, char **paras, char *requ_data) {
    printf("parse query_drop\n");
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

static char *query_updat(char *data_line, char **paras, char *requ_data) {
    printf("parse query_updat\n");
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

static char *query_inser(char *data_line, char **paras, char *requ_data) {
    printf("parse query_inser\n");
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

static char *query_find(char *data_line, char **paras, char *requ_data) {
    printf("parse query_find\n");
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

static char *query_invok(char *data_line, char **paras, char *requ_data) {
    printf("parse query_invok\n");
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

static char *query_facto(char *data_line, char **paras, char *requ_data) {
    printf("parse query_facto\n");
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

char* (*parse_query_tab[])(char *, char **, char *) = {
    query_echo,
    query_creat,
    query_drop,
    query_updat,
    query_inser,
    query_find,
    query_invok,
    query_facto
};

//

int valid_query() {
    return 0x00;
}

// query

static int echo_query(prod_data *sresp, void *coval, char **paras) {
    printf("echo_query\n");
    if (!paras[0x00]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    contain *conta = (contain *) action_value(paras[0x00], ((conoda *) coval)->conda.contn_hm);
    if (conta) {
        printf("contain:%s\n", paras[0x00]);
        quer_echo_bzl(sresp, conta);
    } else {
        printf("not found:%s\n", paras[0x00]);
        PDAT_EXCEP_TAIL(sresp, NOT_FOUND_CONTA)
        return -1;
    }
    //
    return 0x00;
}

// odb:create("mycon", "rive", "test");
static int creat_query(prod_data *sresp, void *coval, char **paras) {
    printf("creat_query\n");
    printf("paras[0x00]:%s paras[0x02]:%s\n", paras[0x00], paras[0x02]);
    printf("((uint32 *) paras[0x01])[0x00]:%u\n", ((uint32 *) paras[0x01])[0x00]);
    if (!paras[0x00]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    contain *conta = (contain *) action_value(paras[0x00], ((conoda *) coval)->conda.contn_hm);
    if (conta) {
        printf("Contain exists!\n");
        PDAT_EXCEP_TAIL(sresp, CONTA_EXIST_EXCE)
        return -1;
    }
    //
    if (quer_creat_bzl(((conoda *) coval)->rvcon, ((conoda *) coval)->osdb_name, paras)) {
        printf("Create contain execep!\n");
        PDAT_EXCEP_TAIL(sresp, CREAT_CONTA_EXCE)
        return -1;
    }
    //
    conta = creat_conta_bzl(((conoda *) coval)->osdb_name, paras[0x00], ((uint32 *) paras[0x01])[0x00]);
    if (!conta) {
        printf("Create contain execep!\n");
        PDAT_EXCEP_TAIL(sresp, CREAT_CONTA_EXCE)
        return -1;
    }
    cache_insert(&conta->oid, (void *) conta, ((conoda *) coval)->conda.conto_hm);
    action_insert(conta->cont_name, (void *) conta, ((conoda *) coval)->conda.contn_hm);
    printf("Create contain OK! %s\n", paras[0x00]);
    //
    PDAT_NONE_TAIL(sresp)
    return 0x00;
}

// :drop(obje_oid);
// :drop("xx()>0x00");

static int drop_query(prod_data *sresp, void *coval, char **paras) {
    printf("drop_query\n");
    if (!paras[0x00]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    contain *conta = (contain *) action_value(paras[0x00], ((conoda *) coval)->conda.contn_hm);
    if (conta) {
        printf("contain:%s\n", paras[0x00]);
        if (quer_drop_bzl(((conoda *) coval)->rvcon, conta->stora_ha, ((conoda *) coval)->osdb_name, paras)) {
            printf("Drop object execep!\n");
            PDAT_EXCEP_TAIL(sresp, DROP_OBJE_EXCE)
            return -1;
        }
        cache_remove(&conta->oid, ((conoda *) coval)->conda.conto_hm);
        action_remove(conta->cont_name, ((conoda *) coval)->conda.contn_hm);
    } else {
        printf("not found:%s\n", paras[0x00]);
        PDAT_EXCEP_TAIL(sresp, NOT_FOUND_CONTA)
        return -1;
    }
    //
    PDAT_NONE_TAIL(sresp)
    return 0x00;
}

static int updat_query(prod_data *sresp, void *coval, char **paras) {
    printf("updat_query\n");
    if (!paras[0x00]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
     printf("CREATE_QREQU\n");
    CREATE_QREQU(coval, (paras))
    if (quer_find_bzl(sresp, &qrequ)) {
        printf("Create object execep!\n");
        PDAT_EXCEP_TAIL(sresp, CREAT_OBJE_EXCE)
        return -1;
    }
    //
    return 0x00;
}

static int inser_query(prod_data *sresp, void *coval, char **paras) {
    printf("inser_query\n");
    if (!paras[0x00]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
     printf("CREATE_QREQU\n");
    CREATE_QREQU(coval, (paras))
    if (quer_find_bzl(sresp, &qrequ)) {
        printf("Create object execep!\n");
        PDAT_EXCEP_TAIL(sresp, CREAT_OBJE_EXCE)
        return -1;
    }
    //
    return 0x00;
}

// 创建对象引用,写/排它锁
// odb:find("clasn", "conobje", "obje:numb() > 0x00");
// :find("cobje", conobje", "obje:numb() > 0x00");
// :find("cobje", "conobje1, conobje2", "conobje1:obje:numb() > 0x00 AND conobje2:obje:numb() > 0x00");
// odb:find("cobje", "conobje");

static int find_query(prod_data *sresp, void *coval, char **paras) {
    printf("find_query\n");
    if (!paras[0x00]) {
        FDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
     printf("CREATE_QREQU\n");
    CREATE_QREQU(coval, (paras))
    if (quer_find_bzl(sresp, &qrequ)) {
        printf("Create object execep!\n");
        FDAT_EXCEP_TAIL(sresp, CREAT_OBJE_EXCE)
        return -1;
    }
    //
    return 0x00;
}

// 创建对象实体,读/共享锁
// odb:factory("clasn", "conobje", "obje:numb() > 0x00");
// :factory("clasn", conobje", "obje:numb() > 0x00");
// :factory("clasn", conobje1, conobje2", "conobje1:obje:numb() > 0x00 AND conobje2:obje:numb() > 0x00");
// odb:factory("clasn", "conobje");

static int facto_query(prod_data *sresp, void *coval, char **paras) {
    printf("facto_query\n");
    if (!paras[0x00]) {
        FDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    CREATE_QREQU(coval, (paras))
    if (quer_facto_bzl(sresp, &qrequ)) {
        printf("Facto query execep!\n");
        FDAT_EXCEP_TAIL(sresp, FACT_QUER_EXCE)
        return -1;
    }
    //
    return 0x00;
}

// odb:each("xxx:meth(conta1:obje, conta2:obje, 55)", "conta1,conta2");
// odb:each("xxx:meth(conta1:obje, 55)", "conta1");
// odb:each("xxx:meth(conta1:obje, 55)", "conta1", "conta1:obje:tst(xxx) > 0x00");

static int invok_query(prod_data *sresp, void *coval, char **paras) {
    printf("invok_query\n");
    if (!paras[0x00]) {
        FDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    contain *conta = (contain *) action_value(paras[0x00], ((conoda *) coval)->conda.contn_hm);
    if (conta) {
        printf("contain:%s\n", paras[0x00]);
        if (quer_invok_bzl(sresp, conta, &((conoda *) coval)->handa, ((conoda *) coval)->rvcon, paras + 0x01)) {
            printf("Drop object execep!\n");
            FDAT_EXCEP_TAIL(sresp, DROP_OBJE_EXCE)
            return -1;
        }
    } else {
        printf("not found:%s\n", paras[0x00]);
        FDAT_EXCEP_TAIL(sresp, NOT_FOUND_CONTA)
        return -1;
    }
    //
    return 0x00;
}

int (*hand_query_tab[])(prod_data *, void *, char **) = {
    echo_query,
    creat_query,
    drop_query,
    updat_query,
    inser_query,
    find_query,
    invok_query,
    facto_query
};
//
