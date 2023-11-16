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
#include "multi.hpp"

using namespace std;

/* Programa de prueba del módulo multi.hpp que crea un multiconjunto vacío de strings y luego lee un fichero "entrada.txt" 
 * con operaciones a realizar con ese multiconjunto, indicadas con la siguiente sintaxis, y escribe en un fichero "salida.txt" 
 * lo indicado según cada opción:
 * A -> añade un ejemplar del string incluido en la siguiente línea y escribe en salida "AÑADIDO string"
 * Q -> quita (si existe) un ejemplar del string incluido en la siguiente línea y escribe en salida "QUITADO string"
 *      o "NO QUITADO string", según corresponda
 * M -> escribe en salida la multiplicidad (M) del string incluido en la siguiente línea (0, si no existe) con la
 *      sintaxis: MULTIPLICIDAD DE string = M
 * L -> escribe en salida todos los elementos distintos del multiconjunto (sea C el cardinal), uno por línea y con formato:
 *      "string M" (donde M es la multiplicidad de ese string),   
 *      precedidos por una primera línea con "--- CARDINAL = C", y finalizando con una línea con "---". 
 * */

int main() {
	Multi<string> m;
	vacio(m);	//inicializamos Multi<string> m
	
	ifstream inf;
	inf.open("entrada.txt");
	ofstream outf;
	outf.open("salida.txt");
	
	string instruccion;
	string salto;
	string separador = "---";
	
	while (inf >> instruccion) {
		getline(inf, salto); //leer salto de linea
		if (instruccion == "A") {
			/*
			 * A -> añade un ejemplar del string incluido en la siguiente línea 
			 *      y escribe en salida "AÑADIDO string".
			 */
			string elemento;
			getline(inf, elemento);
			
			anyadir(m, elemento);
			outf << "AÑADIDO " << elemento << endl;
		}
		else if (instruccion == "Q") {
			/*
			 * Q -> quita (si existe) un ejemplar del string incluido en la siguiente 
			 *		línea y escribe en salida "QUITADO string" o "NO QUITADO string", 
			 *		según corresponda
			 */
			string elemento;
			getline(inf,elemento);
			bool borrado;
			
			quitar(m, elemento, borrado);
			
			if (borrado) {
				outf << "QUITADO " << elemento << endl;
			}
			else {
				outf << "NO QUITADO " << elemento << endl;
			}
		}
		else if (instruccion == "M") {
			/*
			 * M -> escribe en salida la multiplicidad (M) del string incluido en la 
			 *		siguiente línea (0, si no existe) con la sintaxis: 
			 *		MULTIPLICIDAD DE string = M
			 */
			string elemento;
			getline(inf, elemento);
			int multipli = multiplicidad(m, elemento);
						
			outf << "MULTIPLICIDAD DE " << elemento << " = " << multipli << endl;
		}
		else if (instruccion == "L") {
			/*
			 * L -> escribe en salida todos los elementos distintos del multiconjunto 
			 *		(sea C el cardinal), uno por línea y con formato:
			 *      "string M" (donde M es la multiplicidad de ese string), precedidos 
			 * 		por una primera línea con "--- CARDINAL = C", y finalizando 
			 * 		con una línea con "---". 
			 */

			int elcardinal = cardinal(m);
			
			outf << separador << " CARDINAL = " << elcardinal << endl;
			
			iniciarIterador(m);
			while (existeSiguiente(m)) { //si existe siguiente, lo muestro
				string dato;
				int mult;
				bool error;
				siguiente(m, dato, mult, error);
				outf << dato << "  " << mult << endl;
			}
			outf << separador << endl;
		}
	}
	outf.close();
	inf.close();
	return 0;
}
