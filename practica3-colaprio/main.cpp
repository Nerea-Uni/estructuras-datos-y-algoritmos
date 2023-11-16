/*
 * Ana Langa Ibáñez 839811
 * Nerea Salamero Labara 820632
 */

#include <iostream>
#include <fstream>
#include <string.h>

#include "colaprio.hpp"



using namespace std;

/* Programa de prueba del módulo colaprio.hpp que crea una cola vacía de strings y luego lee un fichero "entrada.txt" 
 * con operaciones a realizar con esa cola con la siguiente sintaxis y escribe en un fichero "salida.txt" lo indicado 
 * en cada opción:
 * EP -> encola el string incluido en la siguiente línea como prioritario y escribe en una nueva línea en salida "ENCOLADO PRIO string"
 * EN -> encola el string incluido en la siguiente línea como no prioritario y escribe en una nueva línea en salida "ENCOLADO NO PRIO string"
 * P  -> escribe en una nueva línea en salida "PRIMERO " seguido del string primero de la cola, si existe; si no, escribe en una nueva línea en salida "NO HAY"
 * D  -> desencola y escribe en una nueva línea en salida "DESENCOLADO"
 * L  -> escribe en una nueva línea en salida la longitud (L) con formato "LONGITUD L"
 * LP -> escribe en una nueva línea en salida la longitud de los prioritarios (L) con formato "LONGPRI L"
 * LN -> escribe en una nueva línea en salida la longitud de los no prioritarios (L) con formato "LONGNOPRI L"
 * M  -> escribe en salida el listado de todos los strings de la cola (un string por línea), antecedido el listado por una línea con "--- LISTADO ---"
 *       y seguido por otra línea con "---". 
 * */
int main() {

	colaprio <string> c;
    crear(c); //inicializamos colaprio<string> c

	ifstream inf;
	inf.open("entrada.txt");
	ofstream outf;
	outf.open("salida.txt");

	string instruccion;
	string salto;
	string separador = "---";

	while (inf >> instruccion) {
		getline(inf, salto);
		if (instruccion == "EP") {
			string elemento;
			getline(inf,elemento);
				
			bool prio = true;
			encolar(c, elemento, prio);

			outf << "ENCOLADO PRIO " << elemento << endl;
			
		}
		else if (instruccion == "EN") {
			string elemento;
			getline(inf,elemento);
				
			bool prio = false;
			encolar(c, elemento, prio);
				
			outf << "ENCOLADO NO PRIO " << elemento << endl;
		} 
		else if (instruccion == "P") {
			string elemento;
			bool error;
				
			primero(c, elemento, error);
				
			if (error) {
				outf << "NO HAY" << endl;
			}
			else {
				outf << "PRIMERO " << elemento << endl;
			}
			
		} 
		else if (instruccion == "D") {
				
			desencolar(c);
				
			outf << "DESENCOLADO" << endl;
		}
		else if (instruccion == "L") {
			int longi;
				
			longi = longitud(c);
				
			outf << "LONGITUD " << longi << endl;
		}
		else if (instruccion == "LP") {
			int longi;
			bool prio = true;
			
			longi = longClase(c,prio);
				
			outf << "LONGPRI " << longi << endl;
		} else if (instruccion == "LN") {
			int longi;
			bool prio = false;
			
			longi = longClase(c,prio);
				
			outf << "LONGNOPRI " << longi << endl;
		} else if (instruccion == "M") {
				
			outf <<"--- LISTADO ---"<<endl;
			
			//if(longitud(c)>0) {

				iniciarIterador(c);
				string dato;
				while (existeSiguiente(c)) { //si existe siguiente, lo muestro
					siguiente(c,dato);
				    outf << dato << endl;
				}
			//}
        }
            outf <<"---"<<endl;
				
	}
	outf.close();
	inf.close();
	
	return 0;
	
}
	    

