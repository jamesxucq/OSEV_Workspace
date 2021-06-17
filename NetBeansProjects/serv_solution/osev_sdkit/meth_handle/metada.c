#include "metada.h"

//
#define DATA_ATTRIB        "data_attri.sdo"

//

struct data_attri {
    char clasn[CLASS_LENGTH];
    char library[MAX_PATH];

    union {
        unsigned int sibling;
        unsigned int recycle;
    };
};

#define INIT_DATA_ATTR(dattr) \
        memset(&dattr, '\0', sizeof(struct data_attri)); \
        dattr.sibling = INVA_INDE_VALU;

//

static FILE *creat_dadat(char *osdb) {
    char file_name[MAX_PATH];
    CREAT_OBJECT_PATH(file_name, osdb, DATA_ATTRIB)
    //
    FILE *attrp = fopen64(file_name, "wb+");
    if (!attrp) {
        _LOG_ERROR("creat file error! %s", file_name);
        return NULL;
    }
    //
    return attrp;
}

static FILE *open_dadat(char *osdb) {
    char file_name[MAX_PATH];
    CREAT_OBJECT_PATH(file_name, osdb, DATA_ATTRIB)
    //
    FILE *attrp = fopen64(file_name, "rb+");
    if (!attrp) {
        _LOG_ERROR("open file error! %s", file_name);
        return NULL;
    }
    //
    return attrp;
}
#define close_dattr(attrp) if(attrp) fclose(attrp)

//

static int fill_head(FILE *attrp) {
    if (fseeko64(attrp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    //
    struct data_attri dattr;
    INIT_DATA_ATTR(dattr)
    if (0 >= fwrite(&dattr, sizeof (struct data_attri), 0x01, attrp)) {
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
    struct data_attri iattr;
    INIT_DATA_ATTR(iattr)
    if (0 >= fwrite(&iattr, sizeof (struct data_attri), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

static int read_attri(struct data_attri *dattr, FILE *attrp, unsigned int ainde) {
    if (INVA_INDE_VALU == ainde) return -1;
    if (fseeko64(attrp, (__off64_t) ainde * sizeof (struct data_attri), SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0 >= fread(dattr, sizeof (struct data_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    return 0x00;
}

//

static int modi_sibli(unsigned int sibli, FILE *attrp, unsigned int ainde) {
    __off64_t eose = (__off64_t) ainde * sizeof (struct data_attri);
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    //
    struct data_attri dattr;
    if (0 >= fread(&dattr, sizeof (struct data_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    dattr.sibling = sibli;
    if (0 >= fwrite(&dattr, sizeof (struct data_attri), 0x01, attrp)) {
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
    struct data_attri dattr;
    if (0 >= fread(&dattr, sizeof (struct data_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    modi_sibli(dattr.sibling, attrp, ainde);
    //
    if (fseeko64(attrp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    dattr.sibling = ainde;
    if (0 >= fwrite(&dattr, sizeof (struct data_attri), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

static int repla_attri(char *clasn, char *library, FILE *attrp, unsigned int rinde) {
    __off64_t eose = (__off64_t) rinde * sizeof (struct data_attri);
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    struct data_attri dattr;
    if (0 >= fread(&dattr, sizeof (struct data_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    strcpy(dattr.clasn, clasn);
    strcpy(dattr.library, library);
    if (0 >= fwrite(&dattr, sizeof (struct data_attri), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

static int modi_library(char *library, FILE *attrp, unsigned int ainde) {
    __off64_t eose = (__off64_t) ainde * sizeof (struct data_attri);
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    struct data_attri dattr;
    if (0 >= fread(&dattr, sizeof (struct data_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    strcpy(dattr.library, library);
    if (0 >= fwrite(&dattr, sizeof (struct data_attri), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

static unsigned int get_blank_attr(FILE *attrp) {
    if (fseeko64(attrp, -(__off64_t)sizeof (struct data_attri), SEEK_END)) {
        _LOG_ERROR("seek file error!");
        return INVA_INDE_VALU;
    }
    __off64_t eose = ftello64(attrp);
    //
    struct data_attri iattr;
    if (0 >= fread(&iattr, sizeof (struct data_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return INVA_INDE_VALU;
    }
    //
    unsigned int binde = INVA_INDE_VALU;
    if (INVA_INDE_VALU == iattr.recycle) {
        binde = eose / sizeof (struct data_attri);
        activ_attri(binde, attrp);
        fill_idle(attrp);
    } else {
        binde = iattr.recycle;
        struct data_attri battr;
        if (read_attri(&battr, attrp, binde))
            return INVA_INDE_VALU;
        iattr.recycle = battr.recycle;
        activ_attri(binde, attrp);
        if (fseeko64(attrp, eose, SEEK_SET)) {
            _LOG_ERROR("seek file error!");
            return INVA_INDE_VALU;
        }
        if (0 >= fwrite(&iattr, sizeof (struct data_attri), 0x01, attrp)) {
            _LOG_ERROR("fwrite file error!");
            return INVA_INDE_VALU;
        }
    }
    //
    return binde;
}

static int set_recycled(unsigned int ainde, FILE *attrp) {
    if (fseeko64(attrp, -(__off64_t)sizeof (struct data_attri), SEEK_END)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    __off64_t eose = ftello64(attrp);
    //
    struct data_attri dattr;
    if (0 >= fread(&dattr, sizeof (struct data_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    modi_recycl(dattr.recycle, attrp, ainde);
    dattr.recycle = ainde;
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0 >= fwrite(&dattr, sizeof (struct data_attri), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

int creat_dattr(char *osdb) {
    FILE *attrp = creat_dadat(osdb);
    if (!attrp) return -1;
    fill_head(attrp);
    fill_idle(attrp);
    //
    close_dattr(attrp);
    return 0x00;
}

//

static unsigned int find_inde_name(unsigned int *preind, struct data_attri *dattr, FILE *attrp, unsigned int sibli, char *clasn) {
    struct data_attri danod;
    //
    unsigned int ainde = sibli;
    while (!read_attri(&danod, attrp, ainde)) {
        if (!strcmp(clasn, danod.clasn)) {
            memcpy(dattr, &danod, sizeof (struct data_attri));
            return ainde;
        }
        *preind = ainde;
        ainde = danod.sibling;
    }
    //
    return INVA_INDE_VALU;
}

static unsigned int find_inde_name_ex(FILE *attrp, unsigned int sibli, char *clasn) {
    struct data_attri danod;
    //
    danod.sibling = sibli;
    while (!read_attri(&danod, attrp, danod.sibling)) {
        if (!strcmp(clasn, danod.clasn)) {
            return danod.sibling;
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
    struct data_attri dattr;
    if (0 >= fread(&dattr, sizeof (struct data_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return INVA_INDE_VALU;
    }
    //
    return dattr.sibling;
}

//

int open_dattr(char *clasn, char *library, char *osdb) {
    FILE *attrp = open_dadat(osdb);
    if (!attrp) return -1;
    _LOG_DEBUG("open_dattr clasn:%s library:%s", clasn, library);
    //
    unsigned int sibli = find_sibli(attrp);
    unsigned int ainde = find_inde_name_ex(attrp, sibli, clasn);
    if (INVA_INDE_VALU != ainde) {
        _LOG_DEBUG("move a dattr");
        modi_library(library, attrp, ainde);
    } else {
        _LOG_DEBUG("addi a dattr");
        unsigned int binde = get_blank_attr(attrp);
        repla_attri(clasn, library, attrp, binde);
    }
    //
    close_dattr(attrp);
    return 0x00;
}

//

int dele_dattr(char *clasn, char *osdb) {
    FILE *attrp = open_dadat(osdb);
    if (!attrp) return -1;
    _LOG_DEBUG("dele_dattr clasn:%s", clasn);
    //
    unsigned int sibli = find_sibli(attrp);
    struct data_attri dattr;
    unsigned int preind;
    unsigned int ainde = find_inde_name(&preind, &dattr, attrp, sibli, clasn);
    if (INVA_INDE_VALU != ainde) {
        modi_sibli(dattr.sibling, attrp, preind);
        set_recycled(ainde, attrp);
    }
    //
    close_dattr(attrp);
    return 0x00;
}

//

unsigned int open_dconte(dconte *dcont, char *osdb) {
    dcont->attrp = open_dadat(osdb);
    if (!dcont->attrp) return INVA_INDE_VALU;
    return find_sibli(dcont->attrp);
}

void close_dconte(dconte *dcont) {
    close_dattr(dcont->attrp);
}

unsigned int read_dattr(dconte *dcont, unsigned int ainde) {
    _LOG_DEBUG("read_dattr ainde:%u", ainde);
    struct data_attri danod;
    if (read_attri(&danod, dcont->attrp, ainde)) return INVA_INDE_VALU;
    strcpy(dcont->clasn, danod.clasn);
    strcpy(dcont->library, danod.library);
    //
    return danod.sibling;
}