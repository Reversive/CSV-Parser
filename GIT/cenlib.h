#ifndef CENLIB_H
#define CENLIB_H

typedef struct Country * countryADT;
typedef struct Inhabitant * inhabitantADT;

/* Devuelve una instancia vacía de un censo que debe mantenerse en memoria en tanto se desee  
** conservar los datos cargados. 
**  Ejemplo de invocación: paisADT p = nuevoPais();
*/
countryADT newCountry(void);

/* Devuelve una instancia inhabitantADT llena por los parametros dados.
**  Ejemplo de invocacion: inhabitantADT h = newInhabitant(condition, homeID, apName, provName, c);
*/
inhabitantADT newInhabitant(char condition, unsigned long homeID, char* apName, char* provName, 
    const countryADT c);

/* Agrega un habitante a la instancia del censo en memoria.
**  Ejemplo de invocacion: addInhabitant(c, h);
*/
void addInhabitant(countryADT c, inhabitantADT h);

/* Escribe el archivo Pais.csv en el directorio de ejecución del programa,
** basado en los datos contenidos en la instancia de censo c recibida.
**  Ejemplo de invocación: makeCountry(c);
*/
void makeCountry(const countryADT c);

/* Dependiendo del flag, escribe el archivo Provincia.csv o Departamento.csv 
** en el directorio de ejecución del programa, basado en los datos contenidos 
** en la instancia de censo c recibida. Se opto por hacer una sola funcion ya que
** para la creacion tanto de Provincia.csv como Departamento.csv se tienen que recorrer
** todas las provincias.
**  Ejemplo de invocación: makeProvince(c, "Provincia.csv");
*/
void makeFlag(const countryADT c, char * name);

/* Recibe una instancia de censo c y libera toda la memoria que se reservó para la misma. La
** instancia, una vez liberada, no debe usarse como parámetro de ninguna de las funciones anteriores.
**  Ejemplo de invocación: freeCountry(c); 
*/
void freeCountry(const countryADT c);

/* Recibe una instancia de habitante h y libera toda la memoria que se reservó para la misma. La
** instancia, una vez liberada, no debe usarse como parámetro de ninguna de las funciones anteriores.
**  Ejemplo de invocación: freeInhabitant(h); 
*/
void freeInhabitant(inhabitantADT h);

#endif