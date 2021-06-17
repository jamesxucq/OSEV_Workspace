
/* 
 * File:   osev_clie_cpp.h
 * Author: Administrator
 *
 * Created on 2017.6.28, PM 3:18
 */

#ifndef OSEV_CLIE_CPP_H
#define OSEV_CLIE_CPP_H

#include <string>
using namespace std;

#include <vector>
using std::vector;

//
#include "excep_msg.h"
#include "OSVBase.h"
#include "OSEVContain.h"
#include "OSEVConne.h"

//

class OSEVClient {
private:
    string m_UserName;
    string m_Password;
    string m_Address;
    int m_Port;
public:
    OSEVClient(const string &UserName, const string &Password, const string &Address, int Port);
    virtual ~OSEVClient();
public:
    int getOSEVConne(OSEVConne &ObjeConne, const string &BaseName);
public:
    static int Initial();
    static int Cleanup();
};

//

#endif /* OSEV_CLIE_CPP_H */

