#include "metaob.h"

//
#define OBJE_ATTRIB        "obje_attri.sdo"

//

struct obje_attri {
    char clasn[CLASS_LENGTH];
    char mepan[HAND_LENGTH];
    char library[MAX_PATH];

    union {
        unsigned int sibling;
        unsigned int recycle;
    };
};

#define INIT_OBJE_ATTR(oattr) \
        memset(&oattr, '\0', sizeof(struct obje_attri)); \
        oattr.sibling = INVA_INDE_VALU;

//

static FILE *creat_obdat(char *osdb) {
    char file_name[MAX_PATH];
    CREAT_OBJECT_PATH(file_name, osdb, OBJE_ATTRIB)
    //
    FILE *attrp = fopen64(file_name, "wb+");
    if (!attrp) {
        _LOG_ERROR("creat file error! %s", file_name);
        return NULL;
    }
    //
    return attrp;
}

static FILE *open_obdat(char *osdb) {
    char file_name[MAX_PATH];
    CREAT_OBJECT_PATH(file_name, osdb, OBJE_ATTRIB)
    //
    FILE *attrp = fopen64(file_name, "rb+");
    if (!attrp) {
        _LOG_ERROR("open file error! %s", file_name);
        return NULL;
    }
    //
    return attrp;
}
#define close_oattr(attrp) if(attrp) fclose(attrp)

//

static int fill_head(FILE *attrp) {
    if (fseeko64(attrp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    //
    struct obje_attri oattr;
    INIT_OBJE_ATTR(oattr)
    if (0 >= fwrite(&oattr, sizeof (struct obje_attri), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

static int fill_idle(FILE *attrp) {
    if (fseeko64(attrp, 0x00, SEEK_END)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    //
    struct obje_attri iattr;
    INIT_OBJE_ATTR(iattr)
    if (0 >= fwrite(&iattr, sizeof (struct obje_attri), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

static int read_attri(struct obje_attri *oattr, FILE *attrp, unsigned int ainde) {
    if (INVA_INDE_VALU == ainde) return -1;
    if (fseeko64(attrp, (__off64_t) ainde * sizeof (struct obje_attri), SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0 >= fread(oattr, sizeof (struct obje_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    return 0x00;
}

//

static int modi_sibli(unsigned int sibli, FILE *attrp, unsigned int ainde) {
    __off64_t eose = (__off64_t) ainde * sizeof (struct obje_attri);
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    //
    struct obje_attri oattr;
    if (0 >= fread(&oattr, sizeof (struct obje_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    oattr.sibling = sibli;
    if (0 >= fwrite(&oattr, sizeof (struct obje_attri), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

#define modi_recycl(recycl, attrp, ainde) modi_sibli(recycl, attrp, ainde)

//

static int activ_attri(unsigned int ainde, FILE *attrp) {
    if (fseeko64(attrp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    struct obje_attri oattr;
    if (0 >= fread(&oattr, sizeof (struct obje_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    modi_sibli(oattr.sibling, attrp, ainde);
    //
    if (fseeko64(attrp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    oattr.sibling = ainde;
    if (0 >= fwrite(&oattr, sizeof (struct obje_attri), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

static int repla_attri(char *clasn, char *mepan, char *library, FILE *attrp, unsigned int rinde) {
    __off64_t eose = (__off64_t) rinde * sizeof (struct obje_attri);
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    struct obje_attri oattr;
    if (0 >= fread(&oattr, sizeof (struct obje_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    strcpy(oattr.clasn, clasn);
    strcpy(oattr.mepan, mepan);
    strcpy(oattr.library, library);
    if (0 >= fwrite(&oattr, sizeof (struct obje_attri), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

static int modi_library(char *library, FILE *attrp, unsigned int ainde) {
    __off64_t eose = (__off64_t) ainde * sizeof (struct obje_attri);
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    struct obje_attri oattr;
    if (0 >= fread(&oattr, sizeof (struct obje_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    strcpy(oattr.library, library);
    if (0 >= fwrite(&oattr, sizeof (struct obje_attri), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

static unsigned int get_blank_attr(FILE *attrp) {
    if (fseeko64(attrp, -(__off64_t)sizeof (struct obje_attri), SEEK_END)) {
        _LOG_ERROR("seek file error!");
        return INVA_INDE_VALU;
    }
    __off64_t eose = ftello64(attrp);
    //
    struct obje_attri iattr;
    if (0 >= fread(&iattr, sizeof (struct obje_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return INVA_INDE_VALU;
    }
    //
    unsigned int binde = INVA_INDE_VALU;
    if (INVA_INDE_VALU == iattr.recycle) {
        binde = eose / sizeof (struct obje_attri);
        activ_attri(binde, attrp);
        fill_idle(attrp);
    } else {
        binde = iattr.recycle;
        struct obje_attri battr;
        if (read_attri(&battr, attrp, binde))
            return INVA_INDE_VALU;
        iattr.recycle = battr.recycle;
        activ_attri(binde, attrp);
        if (fseeko64(attrp, eose, SEEK_SET)) {
            _LOG_ERROR("seek file error!");
            return INVA_INDE_VALU;
        }
        if (0 >= fwrite(&iattr, sizeof (struct obje_attri), 0x01, attrp)) {
            _LOG_ERROR("fwrite file error!");
            return INVA_INDE_VALU;
        }
    }
    //
    return binde;
}

static int set_recycled(unsigned int ainde, FILE *attrp) {
    if (fseeko64(attrp, -(__off64_t)sizeof (struct obje_attri), SEEK_END)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    __off64_t eose = ftello64(attrp);
    //
    struct obje_attri oattr;
    if (0 >= fread(&oattr, sizeof (struct obje_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    modi_recycl(oattr.recycle, attrp, ainde);
    oattr.recycle = ainde;
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0 >= fwrite(&oattr, sizeof (struct obje_attri), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

int creat_oattr(char *osdb) {
    FILE *attrp = creat_obdat(osdb);
    if (!attrp) return -1;
    fill_head(attrp);
    fill_idle(attrp);
    //
    close_oattr(attrp);
    return 0x00;
}

//

static unsigned int find_inde_name(unsigned int *preind, struct obje_attri *oattr, FILE *attrp, unsigned int sibli, char *clasn, char *mepan) {
    struct obje_attri oanod;
    //
    unsigned int ainde = sibli;
    while (!read_attri(&oanod, attrp, ainde)) {
        if (!strcmp(clasn, oanod.clasn) && !strcmp(mepan, oanod.mepan)) {
            memcpy(oattr, &oanod, sizeof (struct obje_attri));
            return ainde;
        }
        *preind = ainde;
        ainde = oanod.sibling;
    }
    //
    return INVA_INDE_VALU;
}

static unsigned int find_inde_name_ex(FILE *attrp, unsigned int sibli, char *clasn, char *mepan) {
    struct obje_attri oanod;
    //
    oanod.sibling = sibli;
    while (!read_attri(&oanod, attrp, oanod.sibling)) {
        if (!strcmp(clasn, oanod.clasn) && !strcmp(mepan, oanod.mepan)) {
            return oanod.sibling;
        }
    }
    //
    return INVA_INDE_VALU;
}

//

static unsigned int find_sibli(FILE *attrp) {
    if (fseeko64(attrp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return INVA_INDE_VALU;
    }
    //
    struct obje_attri oattr;
    if (0 >= fread(&oattr, sizeof (struct obje_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return INVA_INDE_VALU;
    }
    //
    return oattr.sibling;
}

//

int open_oattr(char *clasn, char *mepan, char *library, char *osdb) {
    FILE *attrp = open_obdat(osdb);
    if (!attrp) return -1;
    _LOG_DEBUG("open_oattr clasn:%s mepan:%s library:%s", clasn, mepan, library);
    //
    unsigned int sibli = find_sibli(attrp);
    unsigned int ainde = find_inde_name_ex(attrp, sibli, clasn, mepan);
    if (INVA_INDE_VALU != ainde) {
        _LOG_DEBUG("move a oattr");
        modi_library(library, attrp, ainde);
    } else {
        _LOG_DEBUG("addi a oattr");
        unsigned int binde = get_blank_attr(attrp);
        repla_attri(clasn, mepan, library, attrp, binde);
    }
    //
    close_oattr(attrp);
    return 0x00;
}

//

int dele_oattr(char *clasn, char *mepan, char *osdb) {
    FILE *attrp = open_obdat(osdb);
    if (!attrp) return -1;
    _LOG_DEBUG("dele_oattr mepan:%s", mepan);
    //
    unsigned int sibli = find_sibli(attrp);
    struct obje_attri oattr;
    unsigned int preind;
    unsigned int ainde = find_inde_name(&preind, &oattr, attrp, sibli, clasn, mepan);
    if (INVA_INDE_VALU != ainde) {
        modi_sibli(oattr.sibling, attrp, preind);
        set_recycled(ainde, attrp);
    }
    //
    close_oattr(attrp);
    return 0x00;
}

//

unsigned int open_oconte(oconte *ocont, char *osdb) {
    ocont->attrp = open_obdat(osdb);
    if (!ocont->attrp) return INVA_INDE_VALU;
    return find_sibli(ocont->attrp);
}

void close_oconte(oconte *ocont) {
    close_oattr(ocont->attrp);
}

unsigned int read_oattr(oconte *ocont, unsigned int ainde) {
    _LOG_DEBUG("read_oattr ainde:%u", ainde);
    struct obje_attri oanod;
    if (read_attri(&oanod, ocont->attrp, ainde)) return INVA_INDE_VALU;
    strcpy(ocont->clasn, oanod.clasn);
    strcpy(ocont->mepan, oanod.mepan);
    strcpy(ocont->library, oanod.library);
    //
    return oanod.sibling;
}