/*
 * File:    producto.hpp
 * Author:  Nerea Salamero Labara (820632)
 * Date:    september 2023
 * Comms:   Fichero de especificación "producto.hpp" de la Práctica 2 de la asignatura de Estructuras
 *          de Datos y Algoritmos, del 3º cuatrimestre del grado en Ingeniería 
 *          Informática de la Universidad de Zaragoza.
 */
#ifndef PRODUCTO_HPP
#define PRODUCTO_HPP

#include <iostream>
using namespace std;

// PREDECLARACIÓN DEL TAD producto

/*
 * Los valores del TAD productos representan productos para los
 * que se tiene información de su nombre y cantidad.
 */
struct producto;

/* 
 * Dada una cadena nom y un entero c, se obtiene un producto de nombre nom y con 
 * cantidad de producto c.
 */
void crear(string nom, int cant, producto& p);

/* 
 * Dado un producto p, se obtiene la cadena correspondiente al nombre de ese producto.
 */
string nombre(const producto& p);

/* 
 * Dado un producto p, se obtiene el entero que corresponde a la cantidad de p.
 */
int cantidad(const producto& p);

/* 
 * Devuelve verdad si y sólo los productos p1 y p2 tienen el mismo nombre.
 */
bool operator==(const producto& p1, const producto& p2);


// DECLARACIÓN DEL TAD producto
struct producto {
    friend void crear(string nom, int cant, producto& p);
    friend string nombre(const producto& p);
    friend int cantidad(const producto& p);
    friend bool operator==(const producto& p1, const producto& p2);
private: 
    //campos
    string nombre;
    int cantidad;
};

#endif //fin de producto.hpp
