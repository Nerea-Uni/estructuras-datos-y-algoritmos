/**********************************************************************
 * Title:	Fichero multi.hpp de la práctica 4 de la asignatura
 *		Estructuras de Datos y Algoritmos. Universidad de Zaragoza.
 * Authors:	Ana Langa Ibáñez (839811) y Nerea Salamero Labara (820632).
 * Date:	november 2022
 * Comms:	
 *********************************************************************/
#ifndef MULTI_HPP
#define MULTI_HPP


//Pre-declaraciones.
template <typename M> struct Multi;

template <typename M> void vacio(Multi<M>& m);
template <typename M> void anyadir(Multi<M>& m, const M& e);
template <typename M> void quitar(Multi<M>& m, const M& e, bool& quitado);
template <typename M> int  multiplicidad(Multi<M>& m, const M& e);
template <typename M> int  cardinal(Multi<M>& m);
template <typename M> void iniciarIterador(Multi<M>& m);
template <typename M> bool existeSiguiente(const Multi<M>& m);
template <typename M> void siguiente(Multi<M>& m, M& dato, int& mult, bool& error);

//Declaración.
template <typename M>
struct Multi {
	friend void vacio<M>(Multi<M>& m);
	friend void anyadir<M>(Multi<M>& m, const M& e);
	friend void quitar<M>(Multi<M>& m, const M& e, bool& quitado);
	friend int  multiplicidad<M>(Multi<M>& m, const M& e);
	friend int  cardinal<M>(Multi<M>& m);
	friend void iniciarIterador<M>(Multi<M>& m);
	friend bool existeSiguiente<M>(const Multi<M>& m);
	friend void siguiente<M>(Multi<M>& m, M& dato, int& mult, bool& error);
private:
	struct celda{
		M dato;             //dato
		int multiplicidad;  //multiplicidad del dato
		celda* sig; 		//siguiente elemento
	};
	celda* pri;     //primer elemento
	int card;       //cardinal: suma de las multiplicidades de las celdas.
	celda* iter;    //iterador
};


/*
 * Devuelve un multiconjunto vacío, sin elementos
 */
template <typename M> 
void vacio(Multi<M>& m){
	m.pri = nullptr;
	m.card = 0;
}


/*
 * Devuelve el multiconjunto igual al resultante de añadir 
 * un ejemplar del elemento e a m
 */
template <typename M> 
void anyadir (Multi<M>& m, const M& e){
	if(m.pri == nullptr){	//m es vacio
		m.pri = new typename Multi<M>::celda;	//creo un nuevo hueco
		m.pri->dato = e;
		m.pri->multiplicidad = 1;
		m.pri->sig = nullptr;
		m.card = 1;
	}
	else if (m.pri->dato > e){	//hay que insetarlo el primero
		typename Multi<M>::celda* primero = new typename Multi<M>::celda;		//creo un nuevo hueco
		primero->dato = e;
		primero->multiplicidad = 1;
		primero->sig = m.pri;
		m.card++;
		m.pri = primero;
	}
	else {		//busco punto de inserción
		typename Multi<M>::celda* aux = m.pri;		//creo un auxiliar
		typename Multi<M>::celda* ant = nullptr;		//creo un auxiliar

		while ((aux != nullptr) && (aux->dato < e)){
			//Buscamos el elemento o el lugar donde insertarlo.
			ant = aux;
			aux = aux->sig;
		}
		if ((aux != nullptr) && (aux->dato == e)){
			//Si el elemento ya existe, incrementamos su multiplicidad.
			aux->multiplicidad++;
			m.card++;
		}
		else{	//Si el elemento no existe, lo insertamos en el lugar adecuado.
			typename Multi<M>::celda* nuevo = new typename Multi<M>::celda;		//creo un nuevo hueco
			nuevo->dato = e;
			nuevo->multiplicidad = 1;
			nuevo->sig = aux;
			m.card++;
			ant->sig = nuevo;
		}
	}
}


/*
 * Devuelve el multiconjunto igual al resultante de extraer un 
 * ejemplar del elemento e de m; si no hay ningún elemento e en m,
 * devuelve un multiconjunto igual a m
 */
template <typename M> 
void quitar(Multi<M>& m, const M& e, bool& quitado){
	if(m.pri != nullptr){
		typename Multi<M>::celda* aux = m.pri;			//creo un auxiliar
		typename Multi<M>::celda* ant = nullptr;		//creo un auxiliar

		while((aux != nullptr) && (aux->dato < e)){
			//mientras que el dato sea < que e, paso al siguiente.
			ant = aux;
			aux = aux->sig;
			quitado = false;
		}
		if((aux != nullptr) && (aux->dato == e)){
			//he encontrado el elemento.
			if(aux->multiplicidad > 1){
				//disminuyo la multiplicidad del elemento.
				aux->multiplicidad--;
				quitado = true;
			}
			else{
				//elimino el elemento
				if(ant == nullptr){
					//si es el primero
					m.pri = aux->sig;
					quitado = true;
					delete aux;
				}
				else{
					//si no es el primero
					ant->sig = aux->sig;
					quitado = true;
					delete aux;
				}
			}
		}
	}
}


/*
 * Devuelve el nº de ejemplares del elemento e que hay en m 
 * (0 si no hay ninguno).
 */
template <typename M> 
int  multiplicidad(Multi<M>& m, const M& e){
	typename Multi<M>::celda* aux = m.pri;			//creo un auxiliar
	while((aux != nullptr) && (aux->dato < e)){
		//mientras que el dato sea < que e, paso al siguiente
		aux = aux->sig;
	}

	if((aux != nullptr) && (aux->dato == e)){ 
		//si el dato existe, devuelvo su multiplicidad
		return aux->multiplicidad;
	}
	else{   //el dato no existe, devuelvo multiplicidad=0
		return 0;
	}
}


/*
 * Devuelve el número total de elementos en m, contando los repetidos
 */
template <typename M> 
int  cardinal(Multi<M>& m){
	return m.card;
}


/*
 * Prepara el iterador para que el siguiente elemento a visitar sea 
 * el menor de todo el multiconjunto m (según la operación menor del 
 * parámetro formal elemento), si existe (i.e., situación de no haber 
 * visitado ningún elemento).
 */
template <typename M> 
void iniciarIterador(Multi<M>& m){
	m.iter = m.pri;
}


/*
 * Devuelve falso si ya se han visitado todos los elementos de m, 
 * devuelve verdad en caso contrario
 */
template <typename M> 
bool existeSiguiente(const Multi<M>& m){
	return (m.iter != nullptr);
}


/*
 * Devuelve el siguiente elemento a visitar de m, su multiplicidad
 * y avanzo el iterador.
 */
template <typename M> 
void siguiente(Multi<M>& m, M& dato, int& mult, bool& error){
	if(existeSiguiente(m)){
		error = false;
		//siguiente elemento distinto a visitar de m
		dato = m.iter->dato;
		//multiplicidad del siguiente elemento distinto a visitar de m
		mult = m.iter->multiplicidad;
		//multiconjunto resultante de avanzar el iterador en m 
		m.iter = m.iter->sig;
	}
	else{
		error = true;
	}
}

#endif