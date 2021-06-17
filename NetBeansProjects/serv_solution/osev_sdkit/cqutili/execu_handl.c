#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "opera_utili.h"
#include "compa_utili.h"
#include "execu_handl.h"

// NOT IS MATCH LIKE_KW BETWEEN IN NOT_EQUAL EQUAL 
// GREAT_THAN LESS_EQUAL LESS_THAN GREAT_EQUAL ESCAPE PLUS MINUS

static int hand_not() {
    printf("hand_not\n");
    //
    return 0x00;
}

static int hand_is() {
    printf("hand_is\n");
    //
    return 0x00;
}

static int hand_match() {
    printf("hand_match\n");
    //
    return 0x00;
}

static int hand_like_kw() {
    printf("hand_like_kw\n");
    //
    return 0x00;
}

static int hand_between() {
    printf("hand_between\n");
    //
    return 0x00;
}

static int hand_in() {
    printf("hand_in\n");
    //
    return 0x00;
}

static int hand_not_equal(plan_node *quer_plan, physi_conte *phy_con, rive_ha *stora_ha) {
    int hand_valu = 0x00;
    printf("hand_not_equal\n");
    //
    printf("--- create tmpfile64.\n");
    quer_plan->result_set = tmpfile64();
    if (!quer_plan->result_set) return -1;
    riv_curso_t *lidcu = creat_curso(stora_ha, phy_con, quer_plan->cont_name, quer_plan->source_str);
    if (!lidcu) return -1;
    //
    switch (VALU_CODE(quer_plan->acti_oper)) {
        case TEXT_VALU:
            hand_valu = lid_text_noteq(quer_plan->result_set, lidcu, stora_ha, quer_plan->stri_valu);
            break;
        case LOLO_NUMB_VALU:
            hand_valu = lid_lolo_noteq(quer_plan->result_set, lidcu, stora_ha, quer_plan->lolo_valu);
            break;
        case DOUB_NUMB_VALU:
            hand_valu = lid_doub_noteq(quer_plan->result_set, lidcu, stora_ha, quer_plan->doub_valu);
            break;
        case ID_VALU:
            hand_valu = -1;
            break;
    }
    CLOSE_CURSO(stora_ha, lidcu);
    //
    return hand_valu;
}

static int hand_equal(plan_node *quer_plan, physi_conte *phy_con, rive_ha *stora_ha) {
    int hand_valu = 0x00;
    printf("hand_equal\n");
    //
    printf("--- create tmpfile64.\n");
    quer_plan->result_set = tmpfile64();
    if (!quer_plan->result_set) return -1;
    riv_curso_t *lidcu = creat_curso(stora_ha, phy_con, quer_plan->cont_name, quer_plan->source_str);
    if (!lidcu) return -1;
    //
    switch (VALU_CODE(quer_plan->acti_oper)) {
        case TEXT_VALU:
            hand_valu = lid_text_equal(quer_plan->result_set, lidcu, stora_ha, quer_plan->stri_valu);
            break;
        case LOLO_NUMB_VALU:
            hand_valu = lid_lolo_equal(quer_plan->result_set, lidcu, stora_ha, quer_plan->lolo_valu);
            break;
        case DOUB_NUMB_VALU:
            hand_valu = lid_doub_equal(quer_plan->result_set, lidcu, stora_ha, quer_plan->doub_valu);
            break;
        case ID_VALU:
            hand_valu = lid_rid_equal(quer_plan->result_set, lidcu, stora_ha, quer_plan->source_str);
            break;
    }
    CLOSE_CURSO(stora_ha, lidcu);
    //
    return hand_valu;
}

static int hand_great_than(plan_node *quer_plan, physi_conte *phy_con, rive_ha *stora_ha) {
    int hand_valu = 0x00;
    printf("hand_great_than\n");
    //
    printf("--- create tmpfile64.\n");
    quer_plan->result_set = tmpfile64();
    if (!quer_plan->result_set) return -1;
    riv_curso_t *lidcu = creat_curso(stora_ha, phy_con, quer_plan->cont_name, quer_plan->source_str);
    if (!lidcu) return -1;
    //
    switch (VALU_CODE(quer_plan->acti_oper)) {
        case TEXT_VALU:
            hand_valu = lid_text_great(quer_plan->result_set, lidcu, stora_ha, quer_plan->stri_valu);
            break;
        case LOLO_NUMB_VALU:
            hand_valu = lid_lolo_great(quer_plan->result_set, lidcu, stora_ha, quer_plan->lolo_valu);
            break;
        case DOUB_NUMB_VALU:
            hand_valu = lid_doub_great(quer_plan->result_set, lidcu, stora_ha, quer_plan->doub_valu);
            break;
        case ID_VALU:
            hand_valu = -1;
            break;
    }
    CLOSE_CURSO(stora_ha, lidcu);
    //
    printf("hand_great_than end.\n");
    return hand_valu;
}

static int hand_less_equal(plan_node *quer_plan, physi_conte *phy_con, rive_ha *stora_ha) {
    int hand_valu = 0x00;
    printf("hand_less_equal\n");
    //
    printf("--- create tmpfile64.\n");
    quer_plan->result_set = tmpfile64();
    if (!quer_plan->result_set) return -1;
    riv_curso_t *lidcu = creat_curso(stora_ha, phy_con, quer_plan->cont_name, quer_plan->source_str);
    if (!lidcu) return -1;
    //
    switch (VALU_CODE(quer_plan->acti_oper)) {
        case TEXT_VALU:
            hand_valu = lid_text_leseq(quer_plan->result_set, lidcu, stora_ha, quer_plan->stri_valu);
            break;
        case LOLO_NUMB_VALU:
            hand_valu = lid_lolo_leseq(quer_plan->result_set, lidcu, stora_ha, quer_plan->lolo_valu);
            break;
        case DOUB_NUMB_VALU:
            hand_valu = lid_doub_leseq(quer_plan->result_set, lidcu, stora_ha, quer_plan->doub_valu);
            break;
        case ID_VALU:
            hand_valu = -1;
            break;
    }
    CLOSE_CURSO(stora_ha, lidcu);
    //
    return hand_valu;
}

static int hand_less_than(plan_node *quer_plan, physi_conte *phy_con, rive_ha *stora_ha) {
    int hand_valu = 0x00;
    printf("hand_less_than\n");
    //
    printf("--- create tmpfile64.\n");
    quer_plan->result_set = tmpfile64();
    if (!quer_plan->result_set) return -1;
    riv_curso_t *lidcu = creat_curso(stora_ha, phy_con, quer_plan->cont_name, quer_plan->source_str);
    if (!lidcu) return -1;
    //
    switch (VALU_CODE(quer_plan->acti_oper)) {
        case TEXT_VALU:
            hand_valu = lid_text_less(quer_plan->result_set, lidcu, stora_ha, quer_plan->stri_valu);
            break;
        case LOLO_NUMB_VALU:
            hand_valu = lid_lolo_less(quer_plan->result_set, lidcu, stora_ha, quer_plan->lolo_valu);
            break;
        case DOUB_NUMB_VALU:
            hand_valu = lid_doub_less(quer_plan->result_set, lidcu, stora_ha, quer_plan->doub_valu);
            break;
        case ID_VALU:
            hand_valu = -1;
            break;
    }
    CLOSE_CURSO(stora_ha, lidcu);
    //
    return hand_valu;
}

static int hand_great_equal(plan_node *quer_plan, physi_conte *phy_con, rive_ha *stora_ha) {
    int hand_valu = 0x00;
    printf("hand_great_equal\n");
    //
    printf("--- create tmpfile64.\n");
    quer_plan->result_set = tmpfile64();
    if (!quer_plan->result_set) return -1;
    riv_curso_t *lidcu = creat_curso(stora_ha, phy_con, quer_plan->cont_name, quer_plan->source_str);
    if (!lidcu) return -1;
    //
    switch (VALU_CODE(quer_plan->acti_oper)) {
        case TEXT_VALU:
            hand_valu = lid_text_greeq(quer_plan->result_set, lidcu, stora_ha, quer_plan->stri_valu);
            break;
        case LOLO_NUMB_VALU:
            hand_valu = lid_lolo_greeq(quer_plan->result_set, lidcu, stora_ha, quer_plan->lolo_valu);
            break;
        case DOUB_NUMB_VALU:
            hand_valu = lid_doub_greeq(quer_plan->result_set, lidcu, stora_ha, quer_plan->doub_valu);
            break;
        case ID_VALU:
            hand_valu = -1;
            break;
    }
    CLOSE_CURSO(stora_ha, lidcu);
    //
    return hand_valu;
}

static int hand_escape() {
    printf("hand_escape\n");
    //
    return 0x00;
}

static int hand_plus() {
    printf("hand_plus\n");
    //
    return 0x00;
}

static int hand_minus() {
    printf("hand_minus\n");
    //
    return 0x00;
}

//

int hand_resul_set(plan_node *quer_plan, physi_conte *phy_con, rive_ha *stora_ha) {
    int hand_valu = 0x00;
    // NOT IS MATCH LIKE_KW BETWEEN IN NOT_EQUAL EQUAL 
    // GREAT_THAN LESS_EQUAL LESS_THAN GREAT_EQUAL ESCAPE PLUS MINUS
    switch (OPER_CODE(quer_plan->acti_oper)) {
        case NOT_OPCO:
            hand_valu = hand_not(); //
            break;
        case IS_OPCO:
            hand_valu = hand_is(); //
            break;
        case MATCH_OPCO:
            hand_valu = hand_match(); //
            break;
        case LIKE_KW_OPCO:
            hand_valu = hand_like_kw(); //
            break;
        case BETWEEN_OPCO:
            hand_valu = hand_between(); //
            break;
        case IN_OPCO:
            hand_valu = hand_in(); //
            break;
        case NOT_EQUAL_OPCO:
            hand_valu = hand_not_equal(quer_plan, phy_con, stora_ha);
            break;
        case EQUAL_OPCO:
            hand_valu = hand_equal(quer_plan, phy_con, stora_ha);
            break;
        case GREAT_THAN_OPCO:
            hand_valu = hand_great_than(quer_plan, phy_con, stora_ha);
            break;
        case LESS_EQUAL_OPCO:
            hand_valu = hand_less_equal(quer_plan, phy_con, stora_ha);
            break;
        case LESS_THAN_OPCO:
            hand_valu = hand_less_than(quer_plan, phy_con, stora_ha);
            break;
        case GREAT_EQUAL_OPCO:
            hand_valu = hand_great_equal(quer_plan, phy_con, stora_ha);
            break;
        case ESCAPE_OPCO:
            hand_valu = hand_escape(); //
            break;
        case PLUS_OPCO:
            hand_valu = hand_plus(); //
            break;
        case MINUS_OPCO:
            hand_valu = hand_minus(); //
            break;
    }
    //
    printf("hand_resul_set end.\n");
    return hand_valu;
}

// OR AND

static int hand_or(plan_node *quer_plan) {
    plan_node *left_chil, *righ_chil;
    printf("hand_or\n");
    //
    left_chil = quer_plan->left_chil;
    righ_chil = quer_plan->righ_chil;
    //
    printf("--- create tmpfile64.\n");
    quer_plan->result_set = tmpfile64();
    if (!quer_plan->result_set) {
        fclose(left_chil->result_set);
        fclose(righ_chil->result_set);
        return -1;
    }
    //
    if (strcmp(left_chil->cont_name, righ_chil->cont_name)) { // difference source
        if (cartesi_product_data(quer_plan->result_set, left_chil->result_set, righ_chil->result_set)) {
            fclose(left_chil->result_set);
            fclose(righ_chil->result_set);
            fclose(quer_plan->result_set);
            return -1;
        }
    } else { // the same source
        if (merge_data_oid(quer_plan->result_set, left_chil->result_set, righ_chil->result_set)) {
            fclose(left_chil->result_set);
            fclose(righ_chil->result_set);
            fclose(quer_plan->result_set);
            return -1;
        }
    }
    fclose(left_chil->result_set);
    fclose(righ_chil->result_set);
    //
    return 0x00;
}

static int hand_and(plan_node *quer_plan) {
    plan_node *left_chil, *righ_chil;
    printf("hand_and\n");
    //
    left_chil = quer_plan->left_chil;
    righ_chil = quer_plan->righ_chil;
    //
    printf("--- create tmpfile64.\n");
    quer_plan->result_set = tmpfile64();
    if (!quer_plan->result_set) {
        fclose(left_chil->result_set);
        fclose(righ_chil->result_set);
        return -1;
    }
    // the same source
    if (shared_data_oid(quer_plan->result_set, left_chil->result_set, righ_chil->result_set)) {
        fclose(left_chil->result_set);
        fclose(righ_chil->result_set);
        fclose(quer_plan->result_set);
        return -1;
    }
    fclose(left_chil->result_set);
    fclose(righ_chil->result_set);
    //
    return 0x00;
}

int hand_opera_set(plan_node *quer_plan) { // OR AND
    printf("hand_opera_set\n");
    int hand_valu = 0x00;
    //
    switch (OPER_CODE(quer_plan->acti_oper)) {
        case OR_OPCO:
            hand_valu = hand_or(quer_plan);
            break;
        case AND_OPCO:
            hand_valu = hand_and(quer_plan);
            break;
    }

    //
    return hand_valu;
}

//

int hand_final_find(prod_data *sresp, plan_node *quep) {
    printf("hand_final_find\n");
    //
    FILE_SIZE_STREAM(((sresp->colen)[0x00]), sresp->sedat)
    rewind(sresp->sedat);
    printf("(sresp->colen)[0x00]:%d\n", (sresp->colen)[0x00]);
    //
    return 0x00;
}

int hand_final_drop(rive_conne *rvcon, rive_ha *stora_ha, char *cont_name, plan_node *quep) {
    printf("hand_final_find\n");
    //

    //
    return 0x00;
}

int hand_final_each(prod_data *sresp, rive_conne *rvcon, rive_ha *stora_ha, dyli_meth *dlmep, plan_node *quep) {
    printf("hand_final_find\n");
    //
    FILE_SIZE_STREAM(((sresp->colen)[0x00]), sresp->sedat)
    rewind(sresp->sedat);
    printf("(sresp->colen)[0x00]:%d\n", (sresp->colen)[0x00]);
    //
    return 0x00;
}