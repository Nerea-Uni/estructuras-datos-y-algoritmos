/*
 * Title:   Fichero cola.hpp de la práctica 3 de la asignatura 
 *          de Estructuras de Datos y Algoritmos.
 * Authors: Ana Langa Ibáñez(839811) y Nerea Salamero Labara (820632)
 * Date:    november 2022
 */

// Interfaz del TAD. Pre-declaraciones:
template <typename Elemento> struct Cola;

template <typename Elemento> void vacia(Cola<Elemento>& c);
template <typename Elemento> void encolar(Cola<Elemento>& c, const Elemento& dato);
template <typename Elemento> void desencolar(Cola<Elemento>& c);
template <typename Elemento> void primero(const Cola<Elemento>& c, Elemento& dato, bool& error);
template <typename Elemento> bool esVacia(const Cola<Elemento>& c);
template <typename Elemento> int longitud(const Cola<Elemento>& c);
template <typename Elemento> void iniciarIterador(Cola<Elemento>& c);
template <typename Elemento> bool existeSiguiente(const Cola<Elemento>& c);
template <typename Elemento> bool siguiente(Cola<Elemento>& c, Elemento& dato);


//Declaración
template <typename Elemento> 
struct Cola{
    friend void vacia<Elemento>(Cola<Elemento>& c);
    friend void encolar<Elemento>(Cola<Elemento>& c, const Elemento& dato);
    friend void desencolar<Elemento>(Cola<Elemento>& c);
    friend void primero<Elemento>(const Cola<Elemento>& c, Elemento& dato, bool& error);
    friend bool esVacia<Elemento>(const Cola<Elemento>& c);
    friend int longitud<Elemento>(const Cola<Elemento>& c);
    friend void iniciarIterador<Elemento>(Cola<Elemento>& c);
    friend bool existeSiguiente<Elemento>(const Cola<Elemento>& c);
    friend bool siguiente<Elemento>(Cola<Elemento>& c, Elemento& dato);

//Representación de los valores del TAD
private:
    struct unDato {
        Elemento dato;
        unDato* sig;
    };
    unDato* pri;
    unDato* ult;
    int longi;
    unDato* iter;
};


// Implementación de las operaciones.

//Devuelve en c la cola vacía, sin elementos.
template<typename Elemento> 
void vacia(Cola<Elemento>& c) {
    c.longi = 0;
    c.pri = nullptr;
    c.ult = nullptr;
}

//Devuelve una cola igual a la resultante de añadir elem a c como elemento prioritario si
//prio es verdad o como no prioritario en caso contrario.
template <typename Elemento> 
void encolar(Cola<Elemento>& c, const Elemento& e) {
    if (c.longi == 0) {
        c.ult = new typename Cola<Elemento>::unDato;
        c.pri = c.ult;
    } 
    else {
        c.ult->sig = new typename Cola<Elemento>::unDato;
        c.ult = c.ult->sig;
    }
    c.ult->dato = e;
    c.ult->sig = nullptr;
    c.longi = c.longi + 1;
}

/*
 * Si c es no vacía, devuelve en c la cola resultante de eliminar de c el 
 * primer elemento que fue añadido. Si c es vacía, la deja igual.
 */
template <typename Elemento> 
void desencolar(Cola<Elemento>& c){
    typename Cola<Elemento>::unDato *aux = nullptr;
    if(!esVacia(c)){
        aux = c.pri;
        c.pri = c.pri->sig;
        delete aux;
        c.longi = c.longi - 1;
        if (c.longi == 0){
            c.ult = nullptr;
        }
    }
}


/* 
 * Si c es no vacía, devuelve en e el primer elemento añadido a c y error=falso.
 * Si c es vacía, devuelve error=verdad y e queda indefinido.
 */
template <typename Elemento> 
void primero (const Cola<Elemento>& c, Elemento& dato, bool& error){
    if (esVacia(c)){
        error = true;
    }
    else{
        error = false;
        dato = c.pri->dato;
    }
}

//Devuelve verdad si y sólo si c no tiene elementos.
template <typename Elemento> 
bool esVacia(Cola<Elemento> c){
    return c.pri == nullptr;
}

//Devuelve el número de elementos de c.
template <typename Elemento> 
int longitud (Cola<Elemento> c){
    return c.longi;
}

/*
 * Prepara el iterador para que el siguiente elemento a visitar sea un primer
 * elemento de c, si existe (situación de no haber visitado ningún elemento).
 */
template <typename Elemento> 
void iniciarIterador (Cola<Elemento>& c){
    c.iter = c.pri;
}

/*
 * Devuelve falso si ya se han visitado todos los elementos de c; devuelve cierto en
 * caso contrario.
 */
template <typename Elemento> 
bool existeSiguiente (const Cola<Elemento>& c){
    return (c.iter != nullptr);
}

/*
 * Si existe algún elemento de c pendiente de visitar, devuelve en e el siguiente
 * elemento a visitar y error=falso, y además avanza el iterador para que a
 * continuación se pueda visitar otro elemento de c. Si no quedan elementos pendientes
 * de visitar devuelve error=verdad y e queda indefinido.
 */
template <typename Elemento> 
bool siguiente (Cola<Elemento>& c, Elemento& dato){
    if(existeSiguiente(c)){
        dato = c.iter->dato;
        c.iter = c.iter->sig;
        return true;
    }
    else {
        return false;
    }
}