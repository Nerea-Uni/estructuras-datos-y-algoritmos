/*
 * File:    main.cpp
 * Author:  Nerea Salamero Labara (820632)
 * Date:    september 2023
 * Comms:   Fichero "main.cpp" de la Práctica 1 de la asignatura de Estructuras
 *          de Datos y Algoritmos, del 3º cuatrimestre del grado en Ingeniería 
 *          Informática de la Universidad de Zaragoza.
 *          Se ejecuta con:
 *              g++ -std=c++11 main.cpp contacto.cpp agenda.cpp -o MiProg
 */
#include "contacto.hpp"
#include "agenda.hpp"


void mostrarMenu() {
    cout << "MENÚ DE OPERACIONES" << endl;
    cout << "0 - Exit" << endl;
    cout << "1 - Añadir contacto a la agenda." << endl;
    cout << "2 - Mostrar por pantalla los datos de los contactos introducidos." << endl;
    cout << "3 - Borrar el último contacto." << endl;
    cout << "4 - Comprobar si en la agenda hay algún contacto con un nombre concreto." << endl;
}

int main() {
    int operacion = 1;

    agenda a;
    contacto c;
    string nombre;
    bool eliminado;
    iniciar(a);
    while (operacion != 0) {
        mostrarMenu();
        cout << endl << "Seleccione una de las anteriores operaciones: ";
        cin >> operacion;


        if (operacion == 1) {
            crear("Nerea", "Paseo de la Constitución", 123456789, c);
            anyadir(a,c);
        }
        else if (operacion == 2) {
            if (!vacia(a)){
                cout << endl;
                imprimirAgenda(a);
            }
            else {
                cout << "La agenda no tiene ningún contacto añadido." << endl;
            }
        }
        else if (operacion == 3) {
            eliminado = borrarUltimo(a);
            
            if (eliminado){
                cout << "El ultimo contacto ha sido eliminado" << endl << endl;
            }
            else {
                cout << "No se ha podido eliminar el último contacto" << endl;
            }
            imprimirAgenda(a);
        }
        else if (operacion == 4) {
            cout << "Introduzca el nombre de un contacto: ";
            cin >> nombre;
            bool encontrado = false;

            crear(nombre,"",0,c);
            encontrado = esta(a,c);
            
            if (encontrado) {
                cout << "Este contacto existe en la agenda." << endl;
            }
            else {
                cout << "Este contacto no ha sido añadido a la agenda." << endl;
            }
        }
        cout << endl << endl;
    }
}