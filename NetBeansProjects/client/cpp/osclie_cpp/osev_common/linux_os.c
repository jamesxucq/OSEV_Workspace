#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <netinet/in.h>

#include "string_utility.h"
#include "linux_os.h"

//

int network_info(char *netw_info) {
    struct ifreq ifr;
    struct ifconf ifc;
    char buf[2048];
    char *last_str = netw_info;
    //
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock == -1) {
        // _LOG_WARN("socket error");
        return -1;
    }
    //
    ifc.ifc_len = sizeof (buf);
    ifc.ifc_buf = buf;
    if (ioctl(sock, SIOCGIFCONF, &ifc) == -1) {
        // _LOG_WARN("ioctl error");
        return -1;
    }
    //
    struct ifreq* it = ifc.ifc_req;
    const struct ifreq * const end = it + (ifc.ifc_len / sizeof (struct ifreq));
    char szMac[64];
    for (; it != end; ++it) {
        strcpy(ifr.ifr_name, it->ifr_name);
        if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0) {
            if (!(ifr.ifr_flags & IFF_LOOPBACK)) { // don't count loopback
                if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0) {
                    unsigned char * ptr;
                    ptr = (unsigned char *) &ifr.ifr_ifru.ifru_hwaddr.sa_data[0x00];
                    snprintf(szMac, 64, "%02X%02X%02X%02X%02X%02X", *ptr, *(ptr + 1), *(ptr + 2), *(ptr + 3), *(ptr + 4), *(ptr + 5));
                    last_str = lscpy(last_str, ifr.ifr_name);
                    last_str = lscpy(last_str, szMac);
                }
            }
        } else {
            // _LOG_WARN("get mac info error");
            return -1;
        }
    }
    //
    return 0x00;
}
