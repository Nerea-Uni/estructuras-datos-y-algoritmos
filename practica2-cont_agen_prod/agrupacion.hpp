/*
 * File:    agrupacion.hpp
 * Author:  Nerea Salamero Labara (820632)
 * Date:    september 2023
 * Comms:   Fichero de especificación "agrupacion.hpp" de la Práctica 2 de la asignatura de Estructuras
 *          de Datos y Algoritmos, del 3º cuatrimestre del grado en Ingeniería 
 *          Informática de la Universidad de Zaragoza.
 */
#ifndef AGRUPACION_HPP
#define AGRUPACION_HPP

// PREDECLARACIÓN DEL TAD GENÉRICO agrupacion

const int MAX = 40;

/* COMPLETAR CON LA ESPECIFICACIÓN DEL DOMINIO DE VALORES DEL TAD agrupacion
   Y CON LAS CONDICIONES QUE SE LE EXIGEN AL PARÁMETRO DE TIPO T.
   ---Añadir que el tipo T no puede ser cualquiera, sino que tiene que tener 
   	  las operaciones que he implementado.
*/
template<typename T> struct agrupacion;


/* 
 * Devuelve una agrupación vacía, sin elementos.
 */
template<typename T> void iniciar(agrupacion<T>& a);

/* 
 * Devuelve true si se ha podido añadir el elemento e correctamente, así como una
 * agrupación igual a la resultante de añadir un elemento e en una agrupación a.
 */
template<typename T> bool anyadir(agrupacion<T>& a, const T& e);

/* 
 * Devuelve verdad si y sólo si la agrupación a está vacía.
 */
template<typename T> bool vacia(const agrupacion<T>& a);

/* 
 * Si a no está vacía, devuelve true y la agrupación igual a la resultante de eliminar
 * de a el último elemento añadido a ella. Si a está vacía, devuelve true y la misma 
 * agrupación vacía.
 */
template<typename T> bool borrarUltimo(agrupacion<T>& a);

/* 
 * Dada una agrupación a y un elemento e, devuelve verdad si y sólo si en a hay algún
 * elemento igual a e (en el sentido de la función iguales del parámetro formal elem),
 * falso en caso contrario.
 */
template<typename T> bool esta(const agrupacion<T>& a, const T& e);

//COMPLETAR OPERACIONES ITERADOR
/* 
 * ...
 */
template<typename T> void iniciarIterador (agrupacion<T>& a);

/* 
 * ...
 */
template<typename T> bool existeSiguiente (const agrupacion<T>& a);

/* 
 * ...
 */
template<typename T> bool siguiente (agrupacion<T>& a, T& e);


// DECLARACIÓN DEL TAD GENÉRICO agrupacion
template<typename T>
struct agrupacion{
    friend void iniciar<T>(agrupacion<T>& a);
    friend bool anyadir<T>(agrupacion<T>& a, const T& e);
    friend bool vacia<T>(const agrupacion<T>& a);
    friend bool borrarUltimo<T>(agrupacion<T>& a);
    friend bool esta<T>(const agrupacion<T>& a, const T& e);

    friend void iniciarIterador<T>(agrupacion<T>& a);
    friend bool existeSiguiente<T>(const agrupacion<T>& a);
    friend bool siguiente<T>(agrupacion<T>& a, T& e);
  private: 
    //campos
    T datos[MAX];
    int total;
    int iter;
};


// IMPLEMENTACIÓN DE LAS OPERACIONES DEL TAD GENÉRICO agrupacion
template<typename T>
void iniciar(agrupacion<T>& a) {
	a.total = 0;
}

template<typename T>
bool anyadir(agrupacion<T>& a, const T& e) {
	bool completa = a.total < MAX;
	if (completa) {
		a.datos[a.total] = e;
		a.total++;
	}
	return completa;
}

template<typename T>
bool vacia(const agrupacion<T>& a) {
	return a.total == 0;
}
	
template<typename T>
bool borrarUltimo(agrupacion<T>& a) {
    bool noVacia = !vacia(a);
	if(noVacia) {
		a.total--;
	}
	return noVacia;
}

template<typename T>
bool esta(const agrupacion<T>& a, const T& e) {
    bool encontrado = false;
	for(int i = 0; (i < a.total) && (!encontrado); i++) {
		encontrado = (a.datos[i] == e);
	}
	return encontrado;
}

//IMPLEMENTACION OPERACIONES ITERADOR
template<typename T>
void iniciarIterador (agrupacion<T>& a) {
	a.iter = 0;
}

template<typename T>
bool existeSiguiente (const agrupacion<T>& a) {
	return a.iter < a.total;
}

template<typename T>
bool siguiente (agrupacion<T>& a, T& e) {
	bool noExiste = !existeSiguiente(a);
	if(!noExiste) {
		e = a.datos[a.iter];
		a.iter++;
	}
	return noExiste;
}


#endif //fin de agrupacion.hpp
