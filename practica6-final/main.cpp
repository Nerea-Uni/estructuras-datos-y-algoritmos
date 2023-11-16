/**********************************************************************
 * Title:	Fichero main.cpp de la práctica 4 de la asignatura
 *		Estructuras de Datos y Algoritmos. Universidad de Zaragoza.
 * Authors:	Ana Langa Ibáñez (839811) y Nerea Salamero Labara (820632).
 * Date:	november 2022
 * Comms:	compilar mediante
 * 				gcc -std=c++11 main.cpp -o main
 * 			ejecutar mediante
 * 				./main
 *********************************************************************/
#include <iostream>
#include <fstream>

#include "multi.hpp"        //archivo hpp de la práctica 5
#include "colaprio.hpp"     //archivo hpp de la práctica 3

using namespace std;

struct Elemento{
    string palabra;
    int multiplicidad;
};

int main() {
    Colaprio<Elemento> c;
    crear(c);   //inicializo Colaprio<string> c
	Multi<string> m;
	crear(m);	//inicializamos Multi<string> m
    Elemento dato;
	
	ifstream inf;
	inf.open("entrada.txt");
	ofstream outf;
	outf.open("salida.txt");

    /*
     * Paso 1: Lee de un fichero de texto (“entrada.txt”) una colección de palabras 
     * (almacenada una en cada línea del fichero) y las almacena en una variable del 
     * tipo multiconjunto implementado en la práctica 5.
     */
    string elemento;
    while (getline(inf,elemento)){
        anyadir(m, elemento);
    }

    /*
     * Paso 2: Recorre mediante su iterador las palabras del multiconjunto creado 
     * anteriormente y las introduce (con sus multiplicidades) en una variable del
     * tipo cola de elementos priorizados implementado en la práctica 3 (guardando
     * un elemento por cada palabra distinta del multiconjunto), de forma que: una
     * palabra será priorizada en la cola si y sólo si tiene multiplicidad igual a
     * uno (es decir, aparece una única vez en el fichero de entrada).
     */
    iniciarIterador(m);
    while (existeSiguiente(m)) {
        //si existe siguiente, voy clasificándolo en prio/noPrio
        bool error;

        siguiente(m, dato.palabra, dato.multiplicidad, error);

        if (dato.multiplicidad == 1){
            //Al ser la multiplicidad 1, ponemos que es prioritario
            enColaprior(c, dato, true);
        }
        else{
            //La multiplicidad es mayor que 1, así que no es prioritario
            enColaprior(c, dato, false);
        }
    }

    /*
     * Paso 3: Recorre mediante su iterador las palabras de la cola de elementos 
     * priorizados creada anteriormente y las escribe en un fichero de texto
     * (“salida.txt”) con la siguiente sintaxis: en primer lugar, una línea con cada
     * palabra distinta que aparece una única vez en el fichero de entrada, ordenadas
     * alfabéticamente; y, a continuación, una línea por cada una de las demás palabras,
     * ordenadas alfabéticamente, y seguida cada palabra de su multiplicidad, separada 
     * de la palabra con un espacio blanco.
     */
    iniciarIterador(c);
    while(existeSiguiente(c)){  //si existe siguiente, lo muestro
        siguiente(c, dato);

        if(dato.multiplicidad == 1){
            outf << dato.palabra << endl;
        }
        else{
            outf << dato.palabra << "  " << dato.multiplicidad << endl;
        }
    }

	outf.close();
	inf.close();
	return 0;
}