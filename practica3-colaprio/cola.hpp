/*
 * Ana Langa Ibáñez 839811
 * Nerea Salamero Labara 820632
 */

#ifndef COLA_HPP
#define COLA_HPP

template <typename T> struct Cola;
template <typename T> void vacia(Cola<T>& c);
template <typename T> void encolar(Cola<T>& c, const T& dato);
template <typename T> void desencolar(Cola<T>& c);
template <typename T> void primero(const Cola<T>& c, T& dato, bool& error);
template <typename T> bool esVacia(const Cola<T>& c);
template <typename T> int longitud(const Cola<T>& c);
template <typename T> void iniciarIterador(Cola<T>& c);
template <typename T> bool existeSiguiente(const Cola<T>& c);
template <typename T> bool siguiente(Cola<T>& c, T& dato);

template <typename T>
struct Cola{
	friend void vacia<T>(Cola<T>& c);
	friend void encolar<T>(Cola<T>& c, const T& dato);
	friend void desencolar<T>(Cola<T>& c);
	friend void primero<T>(const Cola<T>& c, T& dato, bool& error);
	friend bool esVacia<T>(const Cola<T>& c);
	friend int longitud<T>(const Cola<T>& c);
	friend void iniciarIterador<T>(Cola<T>& c);
	friend bool existeSiguiente<T>(const Cola<T>& c);
	friend bool siguiente<T>(Cola<T>& c, T& dato);
	
	private: 
		struct unDato {
			T dato;
			unDato* sig;
		};
		unDato* pri ;
		unDato* ult;
		int longi;
		unDato* iter;
};

//IMPLEMENTACIÓN DE LAS OPERACIONES DEL TAD GENERICO COLA

template <typename T> 
void vacia(Cola<T>& c){
	c.longi = 0;
	c.pri = nullptr;
	c.ult = nullptr;

}


template <typename T> 
void encolar(Cola<T>& c, const T& e){
	if(c.longi == 0){
		c.ult = new typename Cola<T>::unDato;
		c.pri = c.ult;
	}
	else{
		c.ult->sig = new typename Cola<T>::unDato;
		c.ult = c.ult->sig;
	}
	
	c.ult->dato = e;
	c.ult->sig=nullptr;
	c.longi=c.longi+1;

}


template <typename T>  
void desencolar(Cola<T>& c){
	typename Cola<T>::unDato *aux;
    if(c.longi!=0){
        aux = c.pri;
        c.pri = c.pri->sig;
        delete aux;
        c.longi--;
    }
}


template <typename T>     
void primero(const Cola<T>& c, T& dato, bool& error){
	if(c.longi==0){
		error = true;
	}
	else{
		error = false;
		dato = c.pri->dato;
	}
	
}


template <typename T> 
bool esVacia(const Cola<T>& c){
	return c.longi==0;
}

template <typename T> 
int longitud(const Cola<T>& c){
	return c.longi;
}


template <typename T> 
void iniciarIterador(Cola<T>& c){    
	c.iter=c.pri;
}


template <typename T> 
bool existeSiguiente(const Cola<T>& c){
	return c.iter!=nullptr;
}


template <typename T> 
bool siguiente(Cola<T>& c, T& dato){
	bool existe = existeSiguiente(c);
    if(existe){
        dato = c.iter->dato;
        c.iter = c.iter->sig; 
    }
    return !existe;
}


#endif //fin de cola.hpp
