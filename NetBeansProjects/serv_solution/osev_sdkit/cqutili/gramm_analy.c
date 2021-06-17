#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "exptoke.h"
#include "gramm_analy.h"

//

static void pastat_initi(pastat *state, char *erro_msg) {
    memset(state, 0x00, sizeof (pastat));
    state->accept = PARSE_FAULT;
    state->erro_msg = erro_msg;
}


//
#include "expre_analy.h"
#include "expre_analy.c"

//

int gramm_analy_synta(char *erro_msg, oper_node **synt_head, valu_toke *vtsta) {
    pastat state;
    void *pParser;
    //
    pastat_initi(&state, erro_msg);
    pParser = ExpreParseAlloc(malloc);
    //
    printf("ExpreParse start\n");
    valu_toke *valtok = vtsta;
    int inde = 0x00;
    for (; STACK_SIZE > inde; inde++, valtok++) {
        printf("kind:|%u|", valtok->vtok_kind);
        if (INVA_TOKE == valtok->vtok_kind) break;
        printf("str:|%s|\n", valtok->stri_valu);
        ExpreParse(pParser, valtok->vtok_kind, valtok, &state);
    }
    printf("ExpreParse end.\n");
    ExpreParse(pParser, 0x00, valtok, &state);
    ExpreParseFree(pParser, free);
    //
    if (PARSE_FAULT == state.accept) {
        DESTROY_STREE(state.synt_head);
        return -1;
    }
    // 
    printf("exit gramm_analy_synta\n");
    *synt_head = state.synt_head;
    return 0x00;
}