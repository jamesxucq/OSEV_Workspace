
#include "authen_bzl.h"
#include "finalize.h"

#include "excep.h"

//

void authen_excep(session *seion) {
    auth_epoll_exception(seion->ldata->_action_key_);
    CLOSE_AUTHEN_SE(&seion->sctrl);
}

void kalive_excep(session *seion) {
    auth_epoll_exception(seion->ldata->_action_key_);
    CLOSE_KALIVE_SE(&seion->sctrl);
}

void status_excep(session *seion) {
    auth_epoll_exception(seion->ldata->_action_key_);
    CLOSE_STATUS_SE(&seion->sctrl);
}

void privile_excep(session *seion) {
    auth_epoll_exception(seion->ldata->_action_key_);
    CLOSE_STATUS_SE(&seion->sctrl);
}

void invok_excep(session *seion) {
    auth_epoll_exception(seion->ldata->_action_key_);
    CLOSE_INVOKE_SE(&seion->sctrl);
}

void const_excep(session *seion) {
    auth_epoll_exception(seion->ldata->_action_key_);
    close_const_se[seion->inval.sentry](&seion->sctrl);
}

void query_excep(session *seion) {
    auth_epoll_exception(seion->ldata->_action_key_);
    close_query_se[seion->inval.sentry](&seion->sctrl);
}

void done_excep(session *seion) {
    auth_epoll_exception(seion->ldata->_action_key_);
    CLOSE_DONE_SE(&seion->sctrl);
}

//
void (*exception_tab[])(session*) = {
    authen_excep,
    kalive_excep,
    status_excep,
    privile_excep,
    invok_excep,
    const_excep,
    query_excep,
    done_excep
};