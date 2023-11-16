/*
 * File:    main2.cpp
 * Author:  Nerea Salamero Labara (820632)
 * Date:    september 2023
 * Comms:   Fichero "main2.cpp" de la Práctica 1 de la asignatura de Estructuras
 *          de Datos y Algoritmos, del 3º cuatrimestre del grado en Ingeniería 
 *          Informática de la Universidad de Zaragoza.
 *          Se ejecuta con:
 *              g++ -std=c++11 main2.cpp contacto.cpp producto.cpp -o MiProg
 */
#include <iostream>
#include "agrupacion.hpp"
#include "contacto.hpp"
#include "producto.hpp"
using namespace std;


int main(){
    contacto c1;
    crear("Pepe", "Calle 1", 987654321, c1);
    contacto c2;
    crear("Ana", "Calle 2", 987654322, c2);
    contacto c3;
    crear("Maria", "Calle 3", 987654323, c3);

    agrupacion<contacto> agenda;
    iniciar(agenda);
    anyadir(agenda, c1);
    cout << "c1 ha sido añadido" << endl;
    anyadir(agenda, c2);
    cout << "c2 ha sido añadido" << endl;

    borrarUltimo(agenda);
    cout << "se ha eliminado el último contacto" << endl;

    anyadir(agenda, c3);
    cout << "c3 ha sido añadido" << endl;

    bool encontrado = esta(agenda, c3);
    if (encontrado) {
        cout << "el contacto c3 está en la agenda" << endl;
    }
    else {
        cout << "el contacto c3 no está en la agenda" << endl;
    }

    encontrado = esta(agenda, c2);
    if (encontrado) {
        cout << "el contacto c2 está en la agenda" << endl;
    }
    else {
        cout << "el contacto c2 no está en la agenda" << endl;
    }

    bool estaVacia = vacia(agenda);
    if (estaVacia) {
        cout << "la agenda está vacía" << endl;
    }
    else {
        cout << "la agenda no está vacía" << endl;
    }

    producto nar;
    crear("naranjas",2,nar);
    producto per;
    crear("peras", 4, per);

    agrupacion<producto> compra;
    iniciar(compra);
    anyadir(compra, nar);
    cout << nombre(nar) << " ha sido añadido y existen " << cantidad(nar) << " unidades." << endl;
    anyadir(compra, per);
    cout << nombre(per) << " ha sido añadido y existen" << cantidad(per) << " unidades." << endl;

    return 0;
}