#include "cenlib.h"
#include "auxlib.h"


int main(void) {
    char line[MAXLINE], apName[MAXLINE], provName[MAXLINE];
    char condition;
    unsigned long homeID;
    inhabitantADT inhabitant;
    countryADT c = newCountry();

    while((getline(line,MAXLINE)) != EOF) {
    	if(sscanf(line,"%c,%lu,%[^,],%[^\n]", &condition, &homeID, apName, provName) == 4) {
            inhabitant = newInhabitant(condition, homeID, apName, provName, c);
	        addInhabitant(c,inhabitant);
            freeInhabitant(inhabitant);
        }
    }

    makeCountry(c);
    makeFlag(c, "Provincia.csv");
    makeFlag(c, "Departamento.csv");
    freeCountry(c);
    return 0;
}
