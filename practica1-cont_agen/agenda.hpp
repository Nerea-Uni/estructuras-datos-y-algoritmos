/*
 * File:    agenda.hpp
 * Author:  Nerea Salamero Labara (820632)
 * Date:    september 2023
 * Comms:   Fichero de especificación "agenda.hpp" de la Práctica 1 de la asignatura de Estructuras
 *          de Datos y Algoritmos, del 3º cuatrimestre del grado en Ingeniería 
 *          Informática de la Universidad de Zaragoza.
 */
#ifndef AGENDA_HPP
#define AGENDA_HPP

#include "contacto.hpp"

// PREDECLARACIÓN DEL TAD agenda

const int MAX = 40;

/* Los valores del TAD agenda representan colecciones de contactos a las 
   que se pueden añadir elementos de tipo contacto, y de las que se pueden eliminar 
   sus contactos de uno en uno, eliminándose siempre el último contacto añadido de 
   todos los que contenga la agenda.
   Dado que la implementación es estática, se impone una máxima capacidad de la
   agenda igual al valor de la constante MAX.
 */
struct agenda;

/*
 * Devuelve una agenda vacía en a, sin contactos.
 */
void iniciar(agenda& a);

/*
 * Si la agenda a no está llena (numero de contactos almacenados menor que MAX),
 * la función devuelve verdad y añade el contacto c a la agenda a.
 * Si la agenda está llena, la función devuelve falso y la agenda a no se modifica.
 */
bool anyadir(agenda& a, const contacto& c);

/*
 * Devuelve verdad si y sólo si la agenda a está vacía. 
 */
bool vacia(const agenda& a);

/*
 * Si a no está vacía, la función devuelve verdad y de la agenda a se elimina el último contacto 
 * añadido a ella. Si a está vacía, la función devuelve falso y la agenda no se modifica.
 */
bool borrarUltimo(agenda& a);

/*
 * Dada una agenda a y un contacto c, devuelve verdad si y sólo si en 
 * a hay algún contacto igual a c (en el sentido de la función == del TAD contacto), 
 * falso en caso contrario.
 */
bool esta(const agenda& a, const contacto& c);

//COMPLETAR
void imprimirAgenda(const agenda& a);

//OPERACIONES ITERADOR

/* 
 * Prepara el cursor del contenedor c para que el elemento señalado sea el primero
 * del contenedor (situación de no haber visitado antes ningún elemento)
 */
void iniciarIterador(agenda& a);

/* 
 * Devuelve falso si ya se ha visitado el último elemento del contenedor
 * (el cursor no señala a ningún elemento), devuelve cierto en caso contrario
 */
bool existeSiguiente(agenda& a);

/*
 * Si no existeSiguente(c) entonces devuelve el valor verdad en el parámetro error;
 * En caso contrario:
 *  1. devuelve falso en el parámetro error;
 *  2. devuelve el valor del elemento señalado por el cursor en el parámetro e;
 *  3. avanza el cursor para señalar a otro elemento del contenedor que todavía no se haya
 *     visitado
 */
bool siguiente(agenda& a, contacto& c);

// DECLARACIÓN DEL TAD agenda

struct agenda{
	friend void iniciar(agenda& a);
	friend bool anyadir(agenda& a, const contacto& c);
	friend bool vacia(const agenda& a);
	friend bool borrarUltimo(agenda& a);
	friend bool esta(const agenda& a, const contacto& c);
	friend void imprimirAgenda(const agenda& a);
	
	//OPERACIONES ITERADOR
	friend void iniciarIterador(agenda& a);
	friend bool existeSiguiente(agenda& a);
	friend bool siguiente(agenda& a, contacto& c);
private: 
	//campos
	contacto datos[MAX];
	int total;
	//CAMPOS ITERADOR
	int iter;
};

#endif //fin de agenda.hpp

