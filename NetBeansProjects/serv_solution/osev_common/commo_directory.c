#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_macro.h"
#include "commo_directory.h"

//
char _commo_directory_[MAX_PATH * 3];

//

inline char *commo_directory_init(char *directory) {
    strcpy(_commo_directory_, directory);
    _LOG_INFO("Set data directory:%s", directory);
    return _commo_directory_;
}