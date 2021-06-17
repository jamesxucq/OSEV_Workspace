
/* 
 * File:   comdi_bzl.h
 * Author: James Xu
 *
 * Created on 2016.12.21, PM 11:13
 */
// comd_interpret

#ifndef COMDI_BZL_H
#define COMDI_BZL_H

#include "commo_header.h"
#include "inte_authe.h"
#include "inte_statu.h"
#include "inte_privi.h"
#include "inte_invok.h"
#include "inte_colle.h"
#include "inte_const.h"
#include "inte_query.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
//    int cmdibzl_create(char *data_directory);
//    int cmdibzl_destroy();

    //
    int inte_authen_bzl(inte_value *inval, struct authe_ine *auth, char *requ_data);
#define hand_authen_bzl(sresp, seion, sctrl, inval) hand_authen(sresp, seion, sctrl, inval)
#define hand_noauth_bzl(sresp, seion, sctrl, inval) hand_noauth(sresp, seion, sctrl, inval)
    //
    int inte_kalive_bzl(inte_value *inval);
    //
    int inte_status_bzl(inte_value *inval, statu_ine *statu, char *requ_data);
#define hand_ostatu_bzl(svalue, sresp, paras) hand_ostatu_tab[svalue](sresp, paras)
#define hand_dstatu_bzl(svalue, sresp, paras) hand_dstatu_tab[svalue](sresp, paras)
    //
    int inte_privile_bzl(inte_value *inval, privi_ine *privi, char *requ_data);
#define hand_oprivi_bzl(svalue, sresp, paras) hand_oprivi_tab[svalue](sresp, paras)
#define hand_dprivi_bzl(svalue, sresp, paras) hand_dprivi_tab[svalue](sresp, paras)
    //
    int inte_invoke_bzl(inte_value *inval, invok_ine *invok, char *requ_data);
#define hand_invok_bzl(sentry, sresp, hando, handa, osdb, paras) hand_invok_tab[sentry](sresp, hando, handa, osdb, paras)
    
    int inte_colle_bzl(inte_value *inval, colle_ine *colle, char *requ_data);
#define hand_colle_bzl(svalue, sresp, hando, handa, osdb, paras) hand_colle_tab[svalue](sresp, hando, handa, osdb, paras)
    //
    int inte_const_bzl(inte_value *inval, const_ine *constr, char *requ_data);
#define hand_const_bzl(svalue, sresp, coval, oid, paras) hand_const_tab[svalue](sresp, coval, oid, paras)
    //
    int inte_query_bzl(inte_value *inval,query_ine *query, char *requ_data);
#define hand_query_bzl(svalue, sresp, coval, paras) hand_query_tab[svalue](sresp, coval, paras)
    //
    int inte_done_bzl(inte_value *inval);


#ifdef __cplusplus
}
#endif

#endif /* COMDI_BZL_H */

