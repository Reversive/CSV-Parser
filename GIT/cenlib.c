#include "cenlib.h"
#include "auxlib.h"

struct Inhabitant {
    unsigned char condition;
    unsigned long homeID;
    char apName[MAXLINE], provName[MAXLINE];
};

struct Apartment {
    char * apName;
    unsigned long aptQuantity;
    unsigned long status[4];
    struct Apartment * next;
};

struct Province {
    char * provName;
    unsigned long prvQuantity;
    unsigned long status[4];
    struct Apartment * first;
    struct Province * next;
};

struct Country {
    unsigned long ctyQuantity;
    unsigned long status[4];
    struct Province * firstProv;
};

static struct Apartment * addOrEditApt(struct Apartment * a, struct Inhabitant h, countryADT c);
static struct Province * addOrEditProv(struct Province * p, struct Inhabitant h, countryADT c);
static void freeProvince(struct Province * p);
static void freeApartments(struct Apartment * apt);
static void * reserveMemory(size_t bytes, countryADT c);
static FILE * openFile(char * path, char * action, const countryADT c);

void freeCountry(const countryADT c) {
    if(c == NULL) return;
    freeProvince(c->firstProv);
    free(c);
}

static void freeProvince(struct Province * p) {
    if(p == NULL) return;
    freeProvince(p->next);
    freeApartments(p->first);
    free(p->provName);
    free(p);
}

static void freeApartments(struct Apartment * apt) {
    if(apt == NULL) return;
    freeApartments(apt->next);
    free(apt->apName);
    free(apt);
}

void freeInhabitant(inhabitantADT h) {
    if(h == NULL) return;
    free(h);
}
         
static void * reserveMemory(size_t bytes, countryADT c) {
    void * r = calloc(1, bytes);
    if(r == NULL) {
        fprintf(stderr, "ERROR:::No se pudo reservar memoria.");
        freeCountry(c);
        exit(1);
    }
    return r;
}

static FILE * openFile(char * path, char * action, const countryADT c) {
    FILE * f = fopen(path, action);
    if(f == NULL) {
        fprintf(stderr, "ERROR:::No se pudo abrir el archivo.");
        freeCountry(c);
        exit(-1);
    }
    return f;
}
 
inhabitantADT 
newInhabitant(char condition, unsigned long homeID, char* apName, char* provName,const countryADT c) {
    inhabitantADT h = reserveMemory(sizeof(*h), c);
    h->condition = condition;
    h->homeID = homeID;
    strcpy(h->apName,apName);
    strcpy(h->provName,provName);
    return h;
}


void addInhabitant(countryADT c, inhabitantADT h) {
    c->ctyQuantity++;
    c->status[charToInt(h->condition)]++;
    c->firstProv = addOrEditProv(c->firstProv, *h, c);
}


countryADT newCountry(void) {
    countryADT c = reserveMemory(sizeof(*c), NULL);
    return c;
}


static struct Province * addOrEditProv(struct Province * p, struct Inhabitant h, countryADT c) {
    if(p == NULL || (strcmp(h.provName, p->provName) < 0)) {
        struct Province * aux = reserveMemory(sizeof(*aux), c);
        aux->provName = malloc(strlen(h.provName)+1);
        strcpy(aux->provName, h.provName);
        aux->prvQuantity = aux->status[charToInt(h.condition)] = 1;
        aux->next = p;
        aux->first = addOrEditApt(aux->first, h, c);
        return aux;
    } else if(strcmp(h.provName, p->provName) == 0) {
        p->prvQuantity++;
        p->status[charToInt(h.condition)]++;
        p->first = addOrEditApt(p->first, h, c);
        return p;
    }
    p->next = addOrEditProv(p->next, h, c);
    return p;
}


static struct Apartment * addOrEditApt(struct Apartment * a, struct Inhabitant h, countryADT c) {
    if(a == NULL || (strcmp(h.apName, a->apName) < 0)) {
        struct Apartment * aux = reserveMemory(sizeof(*aux), c);
        aux->apName = malloc(strlen(h.apName) + 1);
        strcpy(aux->apName, h.apName);
        aux->aptQuantity = aux->status[charToInt(h.condition)] = 1;
        aux->next = a;
        return aux;
    } else if(strcmp(h.apName, a->apName) == 0) {
        a->aptQuantity++;
        a->status[charToInt(h.condition)]++;
        return a;
    }
    a->next = addOrEditApt(a->next, h, c);
    return a;
}


void makeCountry(const countryADT c) {
    if(c == NULL) return;
    FILE * f = openFile("Pais.csv", "w", c);
    int ocupados = c->status[1], desocupados = c->status[2];
    fprintf(f, "%lu,%.2f\n", c->ctyQuantity, CZERODIV(desocupados, ocupados+desocupados));
    fclose(f);
}


void makeFlag(const countryADT c, char * name) {
    if(c == NULL) return;
    FILE * f = openFile(name, "w", c);
    struct Province * iter = c->firstProv;
    int flag = 0;
    if(strcmp("Departamento.csv", name) == 0) flag = 1;
    while(iter != NULL) {
        if(flag == 0) {
            int ocupados = iter->status[1], desocupados = iter->status[2];
            fprintf(f, "%s,%lu,%.2f\n", iter->provName, iter->prvQuantity,
                        CZERODIV(desocupados, ocupados+desocupados));
        } else {
            struct Apartment * it = iter->first;
            while(it != NULL) {
                int ocupados = it->status[1], desocupados = it->status[2];
                fprintf(f,"%s,%s,%lu,%.2f\n", iter->provName, it->apName, it->aptQuantity, 
                                            CZERODIV(desocupados, ocupados+desocupados));
                it = it->next;
            }
        }
        iter = iter->next;
    }
    fclose(f);
}


