#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//
#include "valtok.h"
#include "expre_utili.h"
#include "exptoke.h"
#include "synta_tree.h"
#include "lexic_analy.h"
#include "gramm_analy.h"
#include "optim_synta.h"
#include "quer_plan.h"

//

static int parse_line(valu_toke vtsta[STACK_SIZE], char *line_txt) {
    char *last_str = line_txt;
    //
    valu_toke *valtok = vtsta;
    int inde = 0x00;
    for (; (last_str = get_valu_toke(valtok, last_str)); inde++, valtok++) {
        if (STACK_SIZE == inde) return -1;
        if (INVA_TOKE == valtok->vtok_kind) break;
        if (ALPHA_TOKE == valtok->vtok_kind) valtok->vtok_kind = get_alpha_toke(valtok->stri_valu);
        // printf("inde:%d kind:|%u|, str:|%s|\n", inde, valtok->vtok_kind, valtok->stri_valu);
    }
    valtok->vtok_kind = INVA_TOKE;
    // printf("inde:%d kind:|%u|\n", inde, valtok->vtok_kind);
    return 0x00;
}

//

int build_query_synta(oper_node **synt_head, char *erro_msg, char *line_txt) {
    valu_toke vtsta[STACK_SIZE];
    printf("build_query_synta\n");
    if (parse_line(vtsta, line_txt)) {
        strcpy(erro_msg, "parse line error!");
        return -1;
    }
    //
    printf("gramm_analy_synta\n");
    if (gramm_analy_synta(erro_msg, synt_head, vtsta)) return -1;
    // optimize synta tree
    printf("optim_synta_tree\n");
    if (optim_synta_tree(synt_head[0x00])) return -1;
    //
    return 0x00;
}