#include "cenlib.h"
#include "auxlib.h"

// Evitamos warning para la funcion generica.
typedef int (*cmp_type)(const void *, const void *);
int ordenaDescendente(char * str1, char * str2);

int main(void) {
    char line[MAXLINE], apName[MAXLINE], provName[MAXLINE];
    char condition;
    unsigned long homeID;
    inhabitantADT inhabitant;
    countryADT c = newCountry((cmp_type)ordenaDescendente);
    while(!feof(stdin)) {
        if(fgets(line, MAXLINE, stdin) != NULL) {
            if(sscanf(line,"%c,%lu,%[^,],%[^\n]", &condition, &homeID, apName, provName) == 4) {
                inhabitant = newInhabitant(condition, homeID, apName, provName, c);
                addInhabitant(c,inhabitant);
                freeInhabitant(inhabitant);
            }
        }   
    }
    makeCountry(c);
    makeFlag(c, "Provincia.csv");
    makeFlag(c, "Departamento.csv");
    freeCountry(c);
    return 0;
}

int ordenaDescendente(char * str1, char * str2) {
    return strcmp(str1, str2);
}