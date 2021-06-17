#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include "dyli_list.h"

//
#define DYLIST_PREPEND(head, add) { \
    add->next = head; \
    head = add; \
}

#define DYLIST_DELETE(head,del) { \
    LDECLTYPE(head) _tmp; \
    if ((head) == (del)) (head)=(head)->next; \
    else { \
        _tmp = head; \
        while (_tmp->next && (_tmp->next != (del))) _tmp = _tmp->next; \
        if (_tmp->next) _tmp->next = ((del)->next); \
    } \
}

//

struct dyli_hand *new_dyha() {
    struct dyli_hand *dyha = (struct dyli_hand *) malloc(sizeof (struct dyli_hand));
    if (!dyha) return NULL;
    memset(dyha, '\0', sizeof (struct dyli_hand));
    //
    return dyha;
}

void free_dyha(struct dyli_hand *dyha) {
    if (dyha) free(dyha);
}

//

static struct dyli_hand *find_dyha(struct dyli_hand *dyha, char *lib_path) {
    struct dyli_hand *dytmp = dyha;
    for (; dytmp; dytmp = dytmp->next) {
        if (!strcmp(lib_path, dyha->lib_path))
            break;
    }
    //
    return dytmp;
}

static struct dyli_hand *dyha_appn(struct dyli_hand **dylsth) {
    struct dyli_hand *dytmp = (struct dyli_hand *) malloc(sizeof (struct dyli_hand));
    if (!dytmp) return NULL;
    memset(dytmp, '\0', sizeof (struct dyli_hand));
    DYLIST_PREPEND(*dylsth, dytmp);
    //
    return dytmp;
}

struct dyli_hand *open_dyhand(struct dyli_hand **dylsth, char *lib_path) {
    struct dyli_hand *dyha = find_dyha(*dylsth, lib_path);
    if (dyha) {
        dyha->refer_inde++;
        // printf("open_dyhand found. dyha->refer_inde:%d\n", dyha->refer_inde);
        return dyha;
    }
    dyha = dyha_appn(dylsth);
    if (dyha) {
        dyha->handle = dlopen(lib_path, RTLD_LAZY);
        if (!dyha->handle) {
            free_dyha(dyha);
            return NULL;
        }
        strcpy(dyha->lib_path, lib_path);
        dyha->refer_inde++;
        // printf("lib_path:%s\n", lib_path);
    }
    //    
    return dyha;
}

void close_dyhand(struct dyli_hand **dylsth, void *lib_hand) {
    struct dyli_hand *dytmp = *dylsth;
    for (; dytmp; dytmp = dytmp->next) {
        if (lib_hand == dytmp->handle) {
            dytmp->refer_inde--;
            if (!dytmp->refer_inde) {
                DYLIST_DELETE(*dylsth, dytmp)
                free_dyha(dytmp);
            }
            break;
        }
    }
}

//

inline void dyhand_dele(struct dyli_hand *dyha) {
    struct dyli_hand *dylitmp;
    while (dyha) {
        dylitmp = dyha;
        dyha = dyha->next;
        free(dylitmp);
    }
}

//

dyli_meth *new_dyme() {
    dyli_meth *dyme = (dyli_meth *) malloc(sizeof (dyli_meth));
    if (!dyme) return NULL;
    memset(dyme, '\0', sizeof (dyli_meth));
    //
    return dyme;
}

void free_dyme(void *dyme) {
    if (dyme) free(dyme);
}

//

dyli_data *new_dyda() {
    dyli_data *dyda = (dyli_data *) malloc(sizeof (dyli_data));
    if (!dyda) return NULL;
    memset(dyda, '\0', sizeof (dyli_data));
    //
    return dyda;
}

void free_dyda(void *dyda) {
    if (dyda) free(dyda);
}
