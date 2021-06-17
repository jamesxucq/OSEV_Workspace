
#include "commo_header.h"
#include "quer_plan.h"
#include "conte_resou.h"
#include "physi_execu.h"
#include "execu_handl.h"
#include "dyli_list.h"

//

int execu_physi_find(prod_data *sresp, rive_conne *rvcon, rive_ha *stora_ha, dyli_data *dldap, plan_node *quer_plan) {
    int exec_valu = 0x00;
    plan_node *que_tok = quer_plan;
    physi_conte phy_con;
    memset(&phy_con, '\0', sizeof (physi_conte));
    //
    printf("execu_physi_find start\n");
    for (; que_tok->acti_oper; que_tok++) {
        printf("que_tok->acti_oper:%08X ", que_tok->acti_oper);
        switch (ACTI_CODE(que_tok->acti_oper)) {
            case INIT_QUERY_ACCO:
                printf("INIT_QUERY_ACCO\n");
                break;
            case FINAL_QUDRY_ACCO:
                printf("FINAL_QUDRY_ACCO\n");
                exec_valu = hand_final_find(sresp, quer_plan->child);
                break;
            case OPEN_CONTE_ACCO:
                printf("open cont_name:%s\n", que_tok->cont_name);
                exec_valu = hand_open_conte(&phy_con, rvcon, stora_ha, NULL);
                break;
            case CLOSE_CONTE_ACCO:
                printf("close cont_name:%s\n", que_tok->cont_name);
                exec_valu = hand_close_conte(&phy_con, rvcon, stora_ha);
                break;
            case RESUL_SET_ACCO:
                printf("RESUL_SET_ACCO\n");
                exec_valu = hand_resul_set(que_tok, &phy_con, stora_ha);
                break;
            case OPERA_SET_ACCO:
                printf("OPERA_SET_ACCO\n");
                exec_valu = hand_opera_set(que_tok);
                break;
        }
    }
    //
    printf("execu_physi_find end.\n");
    return exec_valu;
}

//

int execu_physi_drop(rive_conne *rvcon, rive_ha *stora_ha, dyli_data *dldap, plan_node *quer_plan) {
    int exec_valu = 0x00;
    plan_node *que_tok = quer_plan;
    physi_conte phy_con;
    memset(&phy_con, '\0', sizeof (physi_conte));
    //
    printf("execu_physi_drop start\n");
    for (; que_tok->acti_oper; que_tok++) {
        printf("que_tok->acti_oper:%08X ", que_tok->acti_oper);
        switch (ACTI_CODE(que_tok->acti_oper)) {
            case INIT_QUERY_ACCO:
                printf("INIT_QUERY_ACCO\n");
                break;
            case FINAL_QUDRY_ACCO:
                printf("FINAL_QUDRY_ACCO\n");
                exec_valu = hand_final_drop(rvcon, stora_ha, que_tok->cont_name, quer_plan->child);
                break;
            case OPEN_CONTE_ACCO:
                printf("open cont_name:%s\n", que_tok->cont_name);
                exec_valu = hand_open_conte(&phy_con, rvcon, stora_ha, NULL);
                break;
            case CLOSE_CONTE_ACCO:
                printf("close cont_name:%s\n", que_tok->cont_name);
                exec_valu = hand_close_conte(&phy_con, rvcon, stora_ha);
                break;
            case RESUL_SET_ACCO:
                printf("RESUL_SET_ACCO\n");
                exec_valu = hand_resul_set(que_tok, &phy_con, stora_ha);
                break;
            case OPERA_SET_ACCO:
                printf("OPERA_SET_ACCO\n");
                exec_valu = hand_opera_set(que_tok);
                break;
        }
    }
    //
    printf("execu_physi_drop end.\n");
    return exec_valu;
}

//

int execu_physi_each(prod_data *sresp, rive_conne *rvcon, rive_ha *stora_ha, dyli_meth *dlmep, plan_node *quer_plan) {
    int exec_valu = 0x00;
    plan_node *que_tok = quer_plan;
    physi_conte phy_con;
    memset(&phy_con, '\0', sizeof (physi_conte));
    //
    printf("execu_physi_drop start\n");
    for (; que_tok->acti_oper; que_tok++) {
        printf("que_tok->acti_oper:%08X ", que_tok->acti_oper);
        switch (ACTI_CODE(que_tok->acti_oper)) {
            case INIT_QUERY_ACCO:
                printf("INIT_QUERY_ACCO\n");
                break;
            case FINAL_QUDRY_ACCO:
                printf("FINAL_QUDRY_ACCO\n");
                exec_valu = hand_final_each(sresp, rvcon, stora_ha, dlmep, que_tok);
                break;
            case OPEN_CONTE_ACCO:
                printf("open cont_name:%s\n", que_tok->cont_name);
                exec_valu = hand_open_conte(&phy_con, rvcon, stora_ha, NULL);
                break;
            case CLOSE_CONTE_ACCO:
                printf("close cont_name:%s\n", que_tok->cont_name);
                exec_valu = hand_close_conte(&phy_con, rvcon, stora_ha);
                break;
            case RESUL_SET_ACCO:
                printf("RESUL_SET_ACCO\n");
                exec_valu = hand_resul_set(que_tok, &phy_con, stora_ha);
                break;
            case OPERA_SET_ACCO:
                printf("OPERA_SET_ACCO\n");
                exec_valu = hand_opera_set(que_tok);
                break;
        }
    }
    //
    printf("execu_physi_drop end.\n");
    return exec_valu;
}
