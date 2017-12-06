#include "cenlib.h"
#include "auxlib.h"


int main(void) {
    char line[MAXLINE], apName[MAXLINE], provName[MAXLINE];
    char condition;
    unsigned long homeID;
    inhabitantADT inhabitant;
    countryADT c = newCountry();

    while((getline(line,MAXLINE)) != EOF) {
    	sscanf(line,"%c,%lu,%[^,],%[^\n]", &condition, &homeID, apName, provName);
        inhabitant = newInhabitant(condition, homeID, apName, provName, c);
	    addInhabitant(c,inhabitant);
	    freeInhabitant(inhabitant);
    }

    makeCountry(c);
    makeProvince(c);
    makeApartment(c);
    freeCountry(c);
    return 0;
}
