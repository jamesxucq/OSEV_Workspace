
/* 
 * File:   OSVBase.h
 * Author: Administrator
 *
 * Created on 2017.9.10
 */

#ifndef OSVBASE_H
#define OSVBASE_H

//
#include "osev_common/commo_header.h"
#include "clie_macro.h"

//

class OSVBase {
public:
    OSVBase();
    OSVBase(const OSVBase& orig);
    virtual ~OSVBase();
protected:
    osv_oid_t obje_id;
    char clasn[CLASS_LENGTH];
    unsigned long version; // 0x00:disable >0x00:is version
    int integrity; // 0x01:true 0x00:false
    int check_value; // 0x01:true 0x00:false
public:
    int pass_versi();
    int check_versi();
};

#endif /* OSVBASE_H */

