/*
 * File:    contacto.hpp
 * Author:  Nerea Salamero Labara (820632)
 * Date:    september 2023
 * Comms:   Fichero de especificación "contacto.hpp" de la Práctica 1 de la asignatura de Estructuras
 *          de Datos y Algoritmos, del 3º cuatrimestre del grado en Ingeniería 
 *          Informática de la Universidad de Zaragoza.
 */
#ifndef CONTACTO_HPP
#define CONTACTO_HPP

#include<iostream>
using namespace std;

// PREDECLARACIÓN DEL TAD contacto

/* Los valores del TAD contacto representan información de personas,
a las que llamamos contactos, para las que se tiene 
información de su nombre, su dirección y su número de teléfono.
Dos contactos se consideran iguales (con el operador ==) si tienen el mismo nombre.
*/
struct contacto;

/* Dada una cadena nombre, una cadena direccion y un entero telefono, 
devuelve un contacto c con esos datos. 
*/
void crear(string nombre, string direccion, int telefono, contacto& c);

/* Dado un contacto c, devuelve la cadena correspondiente al nombre de c. 
*/
string nombre(const contacto& c);

/* Dado un contacto c, devuelve la cadena correspondiente a la direccion de c. 
*/
string direccion(const contacto& c);

/* Dado un contacto c, devuelve el entero correspondiente al telefono de c. 
*/
int telefono(const contacto& c);

/* Devuelve verdad si y sólo si los contactos c1 y c2 tienen el mismo nombre. 
*/
bool operator==(const contacto& c1, const contacto& c2);

//COMPLETAR
void mostrarContacto(const contacto& c);

// DECLARACIÓN DEL TAD contacto

struct contacto {
  friend void crear(string nombre, string direccion, int telefono, contacto& c);
  friend string nombre(const contacto& c);
  friend string direccion(const contacto& c);
  friend int telefono(const contacto& c);
  friend bool operator==(const contacto& c1, const contacto& c2);
  friend void mostrarContacto(const contacto& c);
  private:
   string nombre;
   string direccion;
   int telefono;
};

#endif
