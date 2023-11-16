/*
 * File:    producto.cpp
 * Author:  Nerea Salamero Labara (820632)
 * Date:    september 2023
 * Comms:   Fichero de implementación "producto.cpp" de la Práctica 2 de la asignatura de Estructuras
 *          de Datos y Algoritmos, del 3º cuatrimestre del grado en Ingeniería 
 *          Informática de la Universidad de Zaragoza.
 */
#include <iostream>
#include <string>
#include "producto.hpp"
using namespace std;

/* 
 * Dada una cadena nom y un entero c, se obtiene un producto de nombre nom y con 
 * cantidad de producto c.
 */
void crear(string nom, int cant, producto& p) {
    p.nombre = nom;
    p.cantidad = cant;
}

/* 
 * Dado un producto p, se obtiene la cadena correspondiente al nombre de ese producto.
 */
string nombre(const producto& p) {
    return p.nombre;
}

/* 
 * Dado un producto p, se obtiene el entero que corresponde a la cantidad de p.
 */
int cantidad(const producto& p) {
    return p.cantidad;
}

/* 
 * Devuelve verdad si y sólo los productos p1 y p2 tienen el mismo nombre.
 */
bool operator==(const producto& p1, const producto& p2){
    return p1.nombre == p2.nombre;
}