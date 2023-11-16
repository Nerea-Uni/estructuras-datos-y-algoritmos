/*
 * Title:   Fichero colaprio.hpp de la práctica 3 de la asignatura 
 *          de Estructuras de Datos y Algoritmos.
 * Authors: Ana Langa Ibáñez(839811) y Nerea Salamero Labara (820632)
 * Date:    november 2022
 */
#ifndef Colaprio_HPP
#define Colaprio_HPP
#include "cola.hpp"

// Interfaz del TAD. Pre-declaraciones:
template <typename T> struct Colaprio;

template <typename T> void crear(Colaprio<T>& c);
template <typename T> void enColaprior(Colaprio<T>& c, const T& dato, bool prioritario);
template <typename T> void desenColaprior(Colaprio<T>& c);
template <typename T> void primero(const Colaprio<T>& c, T& dato, bool& error);
template <typename T> bool esVaciaC(const Colaprio<T>& c);
template <typename T> int longitud(const Colaprio<T>& c);
template <typename T> void iniciarIterador(Colaprio<T>& c);
template <typename T> bool existeSiguiente(const Colaprio<T>& c);
template <typename T> void siguiente(Colaprio<T>& c, T& e);
template <typename T> void avanza (Colaprio<T>& c);


//Declaración
template <typename T> 
struct Colaprio{
    friend void crear<T>(Colaprio<T>& c);
    friend bool esVaciaC<T>(const Colaprio<T>& c);
    friend void enColaprior<T>(Colaprio<T>& c, const T& dato, bool prioritario);
    friend void desenColaprior<T>(Colaprio<T>& c);
    friend void primero<T>(const Colaprio<T>& c, T& dato, bool& error);
    friend int  longitud<T>(const Colaprio<T>& c);
    friend void iniciarIterador<T>(Colaprio<T>& c);
    friend bool existeSiguiente<T>(const Colaprio<T>& c);
    friend void siguiente<T>(Colaprio<T>& c, T& e);
    friend void avanza<T>(Colaprio<T>& c);

//Representación de los valores del TAD
private:
    Cola<T> prio;
    Cola<T> noPrio;
    int iter;
    bool prioritario;
};


// Implementación de las operaciones.

//Devuelve en c la Colaprio vacía, sin Ts.
template<typename T> 
void crear (Colaprio<T>& c) {
    vacia(c.prio);
    vacia(c.noPrio);
}

//Devuelve en c la Colaprio resultante de añadir e a c.
template <typename T> 
void enColaprior(Colaprio<T>& c, const T& e, bool prioritario) {
    //falta implementar la prioridad ¿?
    if(prioritario){
        encolar(c.prio, e);
    }
    else{
        encolar(c.noPrio, e);
    }
}

/*
 * Si c es no vacía, devuelve en c la Colaprio resultante de eliminar de c el 
 * primer T que fue añadido. Si c es vacía, la deja igual.
 */
template <typename T> 
void desenColaprior(Colaprio<T>& c){
    if(!esVacia(c)){      //la cola no está vacía.
        if(esVacia(c.noPrio)){
            //si no hay datos en la cola noPrio, entonces desencolamos de la cola prio.
            desencolar(c.prio);
        }
        else {
            desencolar(c.noPrio);
        }
    }
}


/* 
 * Si c es no vacía, devuelve en e el primer T añadido a c y error=falso.
 * Si c es vacía, devuelve error=verdad y e queda indefinido.
 */
template <typename T> 
void primero(const Colaprio<T>& c, T& dato, bool& error){
    if (esVacia(c)) {
        error = true;
    }
    else if (esVacia(c.prio)) {
        error = false;
        primero(c.noPrio,dato,error);
    }
    else {
        error = false;
        primero(c.prio,dato,error);
    }
}

//Devuelve verdad si y sólo si c no tiene Ts
template <typename T> 
bool esVaciaC(const Colaprio<T> &c){
    return (esVacia(c.prio)) && (esVacia(c.noPrio));
}

//Devuelve el número de Ts de c.
template <typename T> 
int longitud (const Colaprio<T> &c){
    return longitud(c.prio) + longitud(c.noPrio);
}

template <typename T>
int longDet (const Colaprio<T> &c, bool prioritario) {
    if (prioritario) {
        return longitud(c.prio);
    }
    else {
        return longitud(c.noPrio);
    }
}


/*
 * Prepara el iterador para que el siguiente T a visitar sea el primero de la
 * cola c (entendido según la operación primero(c) especificada antes), si es que existe
 * (i.e., situación de no haber visitado ningún T).
 */
template <typename T> 
void iniciarIterador(Colaprio<T>& c){
    iniciarIterador(c.prio);
    iniciarIterador(c.noPrio);
}


/*
 * Devuelve falso si ya se han visitado todos los Ts de c; devuelve cierto en
 * caso contrario.
 */
template <typename T> 
bool existeSiguiente (const Colaprio<T>& c){
    return (existeSiguiente(c.prio) || existeSiguiente(c.noPrio));
}

/*
 * Devuelve el siguiente T prioritario de c que fue encolado, si lo hay; si por el
 * contrario ya no hay más Ts prioritarios en c pendientes de visitar, devuelve el
 * siguiente T no prioritario de c que fue encolado, si lo hay.
 * Parcial: la operación no está definida si no existeSiguiente(c).
 */
template <typename T> 
void siguiente (Colaprio<T>& c, T& e){
    if(existeSiguiente(c.prio)) {
        siguiente(c.prio, e);
    }
    else if(existeSiguiente(c.noPrio)){
        siguiente(c.noPrio, e);
    }
}

#endif