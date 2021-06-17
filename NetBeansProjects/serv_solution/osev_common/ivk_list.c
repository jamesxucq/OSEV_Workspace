#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ivk_list.h"

//
#define IVKLIST_APPEND(head, add) { \
    LDECLTYPE(head) _tmp; \
    add->next = NULL; \
    if (head) { \
        _tmp = head; \
        while (_tmp->next) _tmp = _tmp->next; \
        _tmp->next = add; \
    } else head = add; \
}

struct ivk_list *appe_ivklist_new(struct ivk_list **ivklsth) {
    struct ivk_list *ilistmp = (struct ivk_list *) malloc(sizeof (struct ivk_list));
    if (!ilistmp) return NULL;
    memset(ilistmp, '\0', sizeof (struct ivk_list));
    //
    IVKLIST_APPEND(*ivklsth, ilistmp);
    return ilistmp;
}

inline void ivklist_dele(struct ivk_list *ivklist) {
    struct ivk_list *ilistmp;
    while (ivklist) {
        ilistmp = ivklist;
        ivklist = ivklist->next;
        free(ilistmp);
    }
}
