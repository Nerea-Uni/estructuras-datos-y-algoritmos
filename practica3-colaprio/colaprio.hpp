/*
 * Ana Langa Ibáñez 839811
 * Nerea Salamero Labara 820632
 */



#ifndef COLAPRIO_HPP
#define COLAPRIO_HPP

#include "cola.hpp"


/* COMPLETAR CON LA ESPECIFICACIÓN DEL DOMINIO DE VALORES DEL TAD colaprio
   Y CON LAS CONDICIONES QUE SE LE EXIGEN AL PARÁMETRO DE TIPO T.
*/
template<typename T> struct colaprio;

/* devuelve en c una colaprio vacía, sin Ts
*/
template<typename T> void crear(colaprio<T>& c);

/*  Devuelve una cola igual a la resultante de añadir elem a c como T prioritario si 
 *  prio es verdad o como no prioritario en caso contrario.}
 */
template<typename T> void encolar (colaprio<T>& c, const T& dato, const bool prio);

/*Devuelve verdad si y sólo si c no tiene Ts. */
template<typename T> bool esVacia (const colaprio<T>& c);

/*  Devuelve el primer T encolado como prioritario de los que hay en c.
*   Si no hay    ningún T prioritario, devuelve el primer T encolado como no prioritario.    
*   Parcial: la operación no está definida si c es vacía.
*/
template<typename T> void primero(const colaprio<T>& c, T& dato, bool& error);

/*  Si esVacía(c), devuelve la cola vacía. En caso contrario, devuelve una cola igual a la    
*   resultante de eliminar de c su T primero, es decir, si en c hay Ts  prioritarios 
*   elimina el primero de ellos que fue encolado; si no los hay, elimina el     primero de los no prioritarios que fue encolado.
*/
template<typename T> void desencolar(colaprio<T>& c);

//  Devuelve el número de Ts de c
template<typename T> int longitud(const colaprio<T>& c);


/*  Si prio es verdad, devuelve el número de Ts prioritarios de c; en caso  contrario, 
*   devuelve el número de Ts no prioritarios de c.
*/
template<typename T> int longClase(const colaprio<T>& c,const bool prio); 

//COMPLETAR OPERACIONES ITERADOR
// Dada una agrupación c, prepara el iterador para que el próximo T a visitar sea el primero
template<typename T> void iniciarIterador(colaprio<T>& c);
//devuelve false si se han visitado todos los Ts de c, y true en caso contrario.
template<typename T> bool existeSiguiente(const colaprio<T>& c);
// devuelve el siguiente T c visitar
template<typename T> void siguiente(colaprio<T>& c, T& dato);
//avanza el iterador
//template<typename T> void avanza(colaprio<T>& c);

// DECLARACIÓN DEL TAD GENÉRICO colaprio

template<typename T>
    struct colaprio{
    friend void crear<T>(colaprio<T>& c);
    friend void encolar<T>(colaprio<T>& c, const T& dato, const bool prio);
    friend bool esVacia<T>(const colaprio<T>& c);
    friend void primero<T>(const colaprio<T>& c, T& dato, bool& error);
    friend void desencolar<T>(colaprio<T>& c);
    friend int longitud<T>(const colaprio<T>& c);
    friend int longClase<T>(const colaprio<T>& c,const bool prio); 
    //OPERACIONES ITERADOR
    friend void iniciarIterador<T>(colaprio<T>& c);
    friend bool existeSiguiente<T>(const colaprio<T>& c);
    friend void siguiente<T>(colaprio<T> & c, T& dato);

	private:
		Cola<T> prio;
		Cola<T> noprio;
};

template<typename T> 
void crear(colaprio<T>& c){
	vacia(c.prio);
	vacia(c.noprio);
}

template<typename T> 
void encolar (colaprio<T>& c,const T& dato, const bool prio){
	if (prio){
		encolar(c.prio, dato);
	}
	else{
		encolar(c.noprio,dato);
	}
}

template<typename T>
void desencolar(colaprio<T>& c){

	if (!esVacia(c.prio)){
		desencolar(c.prio);
	}
	else if(!esVacia(c.noprio)){
		desencolar(c.noprio);
	}
}

template<typename T> 
bool esVacia (const colaprio<T>& c){
	return (esVacia(c.prio) && esVacia(c.noprio));
}

template<typename T> 
void primero(const colaprio <T>& c, T& dato, bool& error){
	error = esVacia(c.prio);
    if(!error){
        primero(c.prio,dato,error);
    }
    else {
        error = esVacia(c.noprio);
        if (!error){
            primero(c.noprio,dato,error);
        }
    }
}


template<typename T> 
int longitud(const colaprio<T>& c){ // Se puede poner todo junto
	
	return (longitud(c.prio)+longitud(c.noprio));
}

template<typename T>
int longClase(const colaprio<T>& c, const bool prio){
	if (prio){
		return longitud(c.prio);	
	}
	else{
		return longitud(c.noprio);
	}
}

template<typename T>
void iniciarIterador(colaprio<T>& c){
	iniciarIterador(c.prio);
    iniciarIterador(c.noprio);
}


template<typename T> 
bool existeSiguiente(const colaprio<T>& c){

	return (existeSiguiente(c.prio)||existeSiguiente(c.noprio));
}

template<typename T> 
void siguiente(colaprio<T>& c, T& dato){
	if(existeSiguiente(c.prio)){ 
        siguiente(c.prio,dato);
    }
    else if (existeSiguiente(c.noprio)){
        siguiente(c.noprio,dato);
    }
}


#endif
