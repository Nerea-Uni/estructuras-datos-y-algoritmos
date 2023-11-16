/*
 * File:    agenda.cpp
 * Author:  Nerea Salamero Labara (820632)
 * Date:    september 2023
 * Comms:   Fichero de implementación "agenda.cpp" de la Práctica 1 de la asignatura de Estructuras
 *          de Datos y Algoritmos, del 3º cuatrimestre del grado en Ingeniería 
 *          Informática de la Universidad de Zaragoza.
 */
#include "agenda.hpp"

/*
 * Devuelve una agenda vacía en a, sin contactos.
 */
void iniciar(agenda& a) {
    a.total = 0;
}

/*
 * Si la agenda a no está llena (numero de contactos almacenados menor que MAX),
 * la función devuelve verdad y añade el contacto c a la agenda a.
 * Si la agenda está llena, la función devuelve falso y la agenda a no se modifica.
 */
bool anyadir(agenda& a, const contacto& c) {
    bool sePuede = a.total < MAX;

    if (sePuede && (!esta(a,c))) {
        a.datos[a.total] = c;
        a.total++;
        cout << "Se ha añadido el usuario." << endl;
    }
    else if (esta(a,c)) {
        sePuede = false;
        cout << "Ya existe un contacto con este nombre." << endl;
    }
    return sePuede;
}

/*
 * Devuelve verdad si y sólo si la agenda a está vacía. 
 */
bool vacia(const agenda& a) {
    return a.total == 0;
}

/*
 * Si a no está vacía, la función devuelve verdad y de la agenda a se elimina el último contacto 
 * añadido a ella. Si a está vacía, la función devuelve falso y la agenda no se modifica.
 */
bool borrarUltimo(agenda& a) {
    if (!vacia(a)){
        a.total--;
        return true;
    }
    else {
        return false;
    }
}

/*
 * Dada una agenda a y un contacto c, devuelve verdad si y sólo si en 
 * a hay algún contacto igual a c (en el sentido de la función == del TAD contacto), 
 * falso en caso contrario.
 */
bool esta(const agenda& a, const contacto& c) {
    bool siEsta = false;
    int i = 0;
    while ((i < a.total) && !siEsta){
        siEsta = operator==(a.datos[i], c);
        i++;
    }
    return siEsta;
}

//COMPLETAR
void imprimirAgenda(const agenda& a){
    for (int i = 0; i < a.total; i++){
        mostrarContacto(a.datos[i]);
    }
}

//OPERACIONES ITERADOR:

/* 
 * Prepara el cursor del contenedor c para que el elemento señalado sea el primero
 * del contenedor (situación de no haber visitado antes ningún elemento)
 */
void iniciarIterador(agenda& a) {
    a.iter = 0;
}

/* 
 * Devuelve falso si ya se ha visitado el último elemento del contenedor
 * (el cursor no señala a ningún elemento), devuelve cierto en caso contrario
 */
bool existeSiguiente(agenda& a) {
    return a.iter < a.total;
}

/*
 * Si no existeSiguente(c) entonces devuelve falso. En caso contrario devuelve true, el valor
 * del elemento señalado por el cursor en el parámetro c y avanza el cursor para señalar al 
 * siguiente elemento de la agenda que no se haya visitado con anterioridad.
 */
bool siguiente(agenda& a, contacto& c) {
    if (existeSiguiente(a)) {
        c = a.datos[a.iter];
        a.iter++;
        return true;
    }
    else {
        return false;
    }
}