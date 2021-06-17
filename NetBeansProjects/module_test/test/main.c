
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdint.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <netinet/in.h>
#include <time.h>
#include <ctype.h>

#include <unistd.h>
#include <stdarg.h>

/*
 * 
 */

void psizeof() {
    printf("sizeof(short):%d\n", sizeof (short));
    printf("sizeof(int):%d\n", sizeof (int));
    printf("sizeof(long):%d\n", sizeof (long));
    printf("sizeof(long long):%d\n", sizeof (long long));
    printf("sizeof(time_t):%d\n", sizeof (time_t));
    printf("sizeof(size_t):%d\n", sizeof (size_t));
    printf("sizeof(pid_t):%d\n", sizeof (pid_t));
    printf("sizeof(double):%d\n", sizeof (double));
    printf("sizeof(char *):%d\n", sizeof (char *));
}

//

int main(int argc, char** argv) {
    // printf("file_name:%s\n", file_name);
    psizeof();
}

//
////////////////////////////////////////////////////////////////////////////////

