#include "commo_header.h"
#include "session.h"
#include "ostp_utili.h"


//

void build_authen_send(struct evdata *evdat, uchar status_code, inte_value *inval) {
    resp_tyle_t authen;
    authen.status = status_code;
    authen.length = inval->content_length;
    memcpy((char *) evdat->type_ptr, &authen, sizeof (resp_tyle_t));
    //
    evdat->hlen = sizeof (resp_tyle_t);
    evdat->value_ptr = evdat->type_ptr + sizeof (resp_tyle_t);
    evdat->blen = EVD_SOCKET_BUFF - sizeof (resp_tyle_t);
}

void build_status_send(struct evdata *evdat, uchar status_code, inte_value *inval) {
    resp_tyle_t status;
    status.status = status_code;
    status.length = inval->content_length;
    memcpy((char *) evdat->type_ptr, &status, sizeof (resp_tyle_t));
    //
    evdat->hlen = sizeof (resp_tyle_t);
    evdat->value_ptr = evdat->type_ptr + sizeof (resp_tyle_t);
    evdat->blen = EVD_SOCKET_BUFF - sizeof (resp_tyle_t);
}

void build_privile_send(struct evdata *evdat, uchar status_code, inte_value *inval) {
    resp_tyle_t privi;
    privi.status = status_code;
    privi.length = inval->content_length;
    memcpy((char *) evdat->type_ptr, &privi, sizeof (resp_tyle_t));
    //
    evdat->hlen = sizeof (resp_tyle_t);
    evdat->value_ptr = evdat->type_ptr + sizeof (resp_tyle_t);
    evdat->blen = EVD_SOCKET_BUFF - sizeof (resp_tyle_t);
}

void build_invoke_send(struct evdata *evdat, uchar status_code, inte_value *inval) {
    resp_tyle_t invok;
    invok.status = status_code;
    invok.length = inval->content_length;
    memcpy((char *) evdat->type_ptr, &invok, sizeof (resp_tyle_t));
    //
    evdat->hlen = sizeof (resp_tyle_t);
    evdat->value_ptr = evdat->type_ptr + sizeof (resp_tyle_t);
    evdat->blen = EVD_SOCKET_BUFF - sizeof (resp_tyle_t);
}

void build_colle_send(struct evdata *evdat, uchar status_code, inte_value *inval) {
    resp_tyle_t colle;
    colle.status = status_code;
    colle.length = inval->content_length;
    memcpy((char *) evdat->type_ptr, &colle, sizeof (resp_tyle_t));
    //
    evdat->hlen = sizeof (resp_tyle_t);
    evdat->value_ptr = evdat->type_ptr + sizeof (resp_tyle_t);
    evdat->blen = EVD_SOCKET_BUFF - sizeof (resp_tyle_t);
}


void build_const_send(struct evdata *evdat, uchar status_code, inte_value *inval) {
    resp_tyle_t constr;
    constr.status = status_code;
    constr.length = inval->content_length;
    memcpy((char *) evdat->type_ptr, &constr, sizeof (resp_tyle_t));
    //
    evdat->hlen = sizeof (resp_tyle_t);
    evdat->value_ptr = evdat->type_ptr + sizeof (resp_tyle_t);
    evdat->blen = EVD_SOCKET_BUFF - sizeof (resp_tyle_t);
}

void build_query_send(struct evdata *evdat, uchar status_code, inte_value *inval) {
    resp_tyle_t query;
    query.status = status_code;
    query.length = inval->content_length;
    memcpy((char *) evdat->type_ptr, &query, sizeof (resp_tyle_t));
    //
    evdat->hlen = sizeof (resp_tyle_t);
    evdat->value_ptr = evdat->type_ptr + sizeof (resp_tyle_t);
    evdat->blen = EVD_SOCKET_BUFF - sizeof (resp_tyle_t);
}