/* 
 * File:   excep.h
 * Author: James Xu
 *
 * Created on
 */

#ifndef EXCEP_H
#define EXCEP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "session.h"

    //
    //void authen_excep(session *seion);
    //void kalive_excep(session *seion);
    //void status_excep(session *seion);
    //void invok_excep(session *seion);
    //void query_excep(session *seion);
    //void done_excep(session *seion);

    extern void(*exception_tab[])(session*);

#ifdef __cplusplus
}
#endif

#endif /* EXCEP_H */

