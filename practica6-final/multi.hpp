/**********************************************************************
 * Title:	Fichero multi2.hpp de la práctica 5 de la asignatura
 *		Estructuras de Datos y Algoritmos. Universidad de Zaragoza.
 * Authors:	Ana Langa Ibáñez (839811) y Nerea Salamero Labara (820632).
 * Date:	december 2022
 * Comms:	compilar mediante
 * 				gcc -std=c++11 main.cpp -o main
 * 			ejecutar mediante
 * 				./main
 *********************************************************************/
#ifndef MULTI_HPP
#define MULTI_HPP
#include "pila.hpp"

//Pre-declaraciones.
template <typename T> struct Multi;

template <typename T> void crear(Multi<T>& m);
template <typename T> void anyadir(Multi<T>& m, const T& e);
template <typename T> void buscar(Multi<T>& m, const T& e, bool& encontrado, int& mult);
template <typename T> void quitar(Multi<T>& m, T& e, bool& borrado);
template <typename T> int  multiplicidad(Multi<T>& m, const T& e);
template <typename T> int  cardinal(Multi<T>& m);
template <typename T> bool esVacio(Multi<T>& m);
template <typename T> void liberar(Multi<T>& m);
template <typename T> void iniciarIterador(Multi<T>& m);
template <typename T> bool existeSiguiente(const Multi<T>& m);
template <typename T> void siguiente(Multi<T>& m, T& dato, int& mult, bool& error);

//funciones recursivas
template <typename T> void anyadirRec(typename Multi<T>::nodo*& p, const T& e, int& cardinal, bool& nuevo);
template <typename T> void buscarRec(typename Multi<T>::nodo*& p, const T& e, bool& encontrado, int& mult);
template <typename T> void borrarMaximo(typename Multi<T>::nodo*& p, T& e);
template <typename T> void quitarRec(typename Multi<T>::nodo*& p, T& e, int& cardinal, bool& quitado);
template <typename T> void liberarRec(typename Multi<T>::nodo*& p);

//Declaración.
template <typename T>
struct Multi {
	friend void crear<T>(Multi<T>& m);
	friend void anyadir<T>(Multi<T>& m, const T& e);
	friend void buscar<T>(Multi<T>& m, const T& e, bool& encontrado, int& mult);
	friend void quitar<T>(Multi<T>& m, T& e, bool& borrado);
	friend int  multiplicidad<T>(Multi<T>& m, const T& e);
	friend int  cardinal<T>(Multi<T>& m);
	friend bool esVacio<T>(Multi<T>& m);
	friend void liberar<T>(Multi<T>& m);
	friend void iniciarIterador<T>(Multi<T>& m);
	friend bool existeSiguiente<T>(const Multi<T>& m);
	friend void siguiente<T>(Multi<T>& m, T& dato, int& mult, bool& error);

private:
	struct nodo{
		T elemento;			//dato que contiene
		int multiplicidad;	//multiplicidad del nodo actual
		nodo* izq;			//hijo izquierdo del nodo actual
		nodo* der;			//hijo derecho del nodo actual
	};
	
	nodo* raiz;				//raíz del árbol
	int cardinal;
	Pila<nodo*> iter;		//iterador

	//funciones recursivas
	friend void anyadirRec<T>(nodo*& p, const T& e, int& cardinal, bool& nuevo);
	friend void buscarRec<T>(nodo*& p, const T& e, bool& encontrado, int& mult);
	friend void borrarMaximo<T>(nodo*& p, T& e);
	friend void quitarRec<T>(nodo*& p, T& e, int& cardinal, bool& quitado);
	friend void liberarRec<T>(nodo*& p);
};

/*
 * Devuelve un multiconjunto vacío, sin elementos
 */
template <typename T> 
void crear(Multi<T>& m){
	m.raiz = nullptr;
	m.cardinal = 0;
}

/*
 * Función auxiliar para el procedimiento de anyadir
 */
template <typename T> 
void anyadirRec(typename Multi<T>::nodo*& p, const T& e, int& cardinal, bool& nuevo){
	if(p == nullptr){
		//el árbol es vacío o no tiene hojas
		p = new typename Multi<T>::nodo;	//creo un nuevo hueco
		p->elemento = e;
		p->multiplicidad = 1;
		p->izq = nullptr;
		p->der = nullptr;
		cardinal++;
		nuevo = true;
	}
	else{
		if(e < p->elemento){
			//añado el elemento en el subárbol izquierdo de p->elemento
			anyadirRec(p->izq, e, cardinal, nuevo);
		}
		else if(e > p->elemento){
			//añado el elemento en el subárbol derecho de p->elemento
			anyadirRec(p->der, e, cardinal, nuevo);
		}
		else {
			//el dato ya existía: le aumento la multiplicidad
			p->multiplicidad++;
			cardinal++;
			nuevo = false;
		}
	}
}

/*
 * Devuelve el multiconjunto igual al resultante de añadir 
 * un ejemplar del elemento e a m.
 */
template <typename T> 
void anyadir(Multi<T>& m, const T& e){
	bool nuevo;
	anyadirRec(m.raiz, e, m.cardinal, nuevo);
}

/*
 * Función auxiliar para el procedimiento de buscar.
 */
template <typename T> 
void buscarRec(typename Multi<T>::nodo*& p, const T& e, bool& encontrado, int& mult){
	if(p == nullptr){
		//el árbol es vacío o no tiene hojas
		encontrado = false;
	}
	else{
		if(e < p->elemento){
			//busco el elemento en el subárbol izquierdo de p->elemento
			buscarRec(p->izq, e, encontrado, mult);
		}
		else if(e > p->elemento){
			//busco el elemento en el subárbol derecho de p->elemento
			buscarRec(p->der, e, encontrado, mult);
		}
		else {
			//si encuentro el elemento, devuelvo su multiplicidad
			mult = p->multiplicidad;
			encontrado = true;
		}
	}
}

/*
 * Devuelve encontrado = true si en m hay algún elemento igual a e,
 * false en caso contrario. En caso de éxito, además, devuelve en mult
 * el valor asociado a su multiplicidad.
 */
template <typename T> 
void buscar(Multi<T>& m, const T& e, bool& encontrado, int& mult){
	buscarRec(m.raiz, e, encontrado, mult);
}

/*
 * Este procedimiento es auxiliar al de quitarRec.
 * Precondición: p es no vacío.
 */
template <typename T> 
void borrarMaximo(typename Multi<T>::nodo*& p, T& e){
	typename Multi<T>::nodo* aux;			//creo un auxiliar
	if(p->der == nullptr){
		e = p->elemento;
		aux = p;
		p = p->izq;
		delete(aux);
	}
	else{
		borrarMaximo(p->der, e);
	}
}

/*
 * Función auxiliar para el procedimiento de quitar.
 * Si en el árbol de raíz apuntada por p hay un elemento igual a e,
 * lo borra y quitado = true. En caso contrario, p no se modifica
 * y quitado = false
 */
template <typename T> 
void quitarRec(typename Multi<T>::nodo*& p, T& e, int& cardinal, bool& quitado){
	typename Multi<T>::nodo* aux;			//creo un auxiliar
	if(p == nullptr){
		//Si el árbol es vacío o no encuentro el elemento.
		quitado = false;
	}
	else{
		if(e < p->elemento){
			//quito el elemento en el subárbol izquierdo de p->elemento
			quitarRec(p->izq, e, cardinal, quitado);
		}
		else if(e > p->elemento){
			//quito el elemento en el subárbol derecho de p->elemento
			quitarRec(p->der, e, cardinal, quitado);
		}
		else {
			//he encontrado el elemento
			if(p->multiplicidad == 1){
				//elimino el elemento
				if(p->izq == nullptr){
					aux = p;
					p = p->der;
					cardinal--;
					delete(aux);
				}
				else{
					borrarMaximo(p->izq, e);
				}
			}
			if(p->multiplicidad > 1){
				//disminuyo la multiplicidad
				p->multiplicidad--;
				cardinal--;
			}
			quitado = true;
		}
	}
}

/*
 * Devuelve el multiconjunto igual al resultante de quitar 
 * un ejemplar del elemento e a m.
 */
template <typename T> 
void quitar(Multi<T>& m, T& e, bool& borrado){
	quitarRec(m.raiz, e, m.cardinal, borrado);
}

/*
 * Devuelve el nº de ejemplares del elemento e que hay en m 
 * (0 si no hay ninguno).
 */
template <typename T>
int multiplicidad(Multi<T>& m, const T& e){
	bool encontrado;
	int mult;
	buscar(m, e, encontrado, mult);
	if(encontrado){
		//si el dato existe, devuelvo su multiplicidad
		mult = mult;
	}
	else {
		//el dato no existe, devuelvo multiplicidad = 0
		mult = 0;
	}
	return mult;
}

/*
 * Devuelve el número total de elementos en m, contando los repetidos
 */
template <typename T> 
int cardinal(Multi<T>& m){
	return m.cardinal;
}

/*
 * Devuelve verdad si y solo si m no tiene pares
 */
template <typename T> 
bool esVacio(Multi<T>& m){
	return m.raiz == nullptr;
}

/*
 * Procedimiento auxiliar para el de liberar. Libera toda la memoria
 * utilizada por el árbol apuntado por p.
 */
template <typename T> 
void liberarRec(typename Multi<T>::nodo*& p){
	if(p != nullptr){
		liberarRec(p->der);
		liberarRec(p->izq);
		delete(p);
	}
}

/* 
 * Devuelve en m el multiconjunto vacío y además libera la memoria 
 * utilizada previamente por m.
 */
template <typename T> 
void liberar(Multi<T>& m){
	liberarRec(m.raiz);
	m.cardinal = 0;
	m.raiz = nullptr;
}

/*
 * Prepara el iterador para que el siguiente elemento a visitar sea 
 * el menor de todo el multiconjunto m (según la operación menor del 
 * parámetro formal elemento), si existe (i.e., situación de no haber 
 * visitado ningún elemento).
 * Inicializa el iterador para recorrer los pares del diccionario d, de forma
 *	   que el siguiente par a visitar sea el primero que visitamos (situación de 
 *	   no haber visitado ningún par).
 */
template <typename T> 
void iniciarIterador(Multi<T>& m){
	crearVacia(m.iter);
	typename Multi<T>::nodo* aux = m.raiz;			//creo un auxiliar
	while (aux != nullptr){
		apilar(m.iter, aux);	//apila el puntero aux (a un nodo del árbol) en la pila del iterador
		aux = aux->izq;
	}
}

/*
 * Devuelve falso si ya se han visitado todos los elementos de m, 
 * devuelve verdad en caso contrario
 */
template <typename T> 
bool existeSiguiente(const Multi<T>& m){
	return (!esVaciaP(m.iter));
}

/*
 * Si existe algún elemento pendiente de visitar, devuelve en dato el valor del siguiente elemento 
 * a visitar, en mult su multiplicidad y error = false, y además avanza el iterador para que a 
 * continuación pueda visitar otro elemento de m. Si no quedan elementos pendientes de visitar 
 * devuelve error = true, m queda como estaba y dato y mult quedan indefinidos.
 */
template <typename T> 
void siguiente(Multi<T>& m, T& dato, int& mult, bool& error){
	typename Multi<T>::nodo* aux;
	if(existeSiguiente(m)){
		error = false;
		cima(m.iter, aux, error);			//creo un auxiliar
		desapilar(m.iter);
		dato = aux->elemento;
		mult = aux->multiplicidad;
		aux = aux->der;
		while (aux != nullptr){
			apilar(m.iter, aux);
			aux = aux->izq;
		}
	}
	else{
		error = true;
	}
};

#endif