//Universidad Nacional 
//Proyecto #2 de Programacion 2
//Desarrollado por Andrey Arguedas Espinoza y Derian Sibaja Chavarria

#pragma once
#include "Librerias.h"  //Aca se encuentran algunas librerias basicas de c++
#include "Piezas.h"     //Aca se encuentran todas la piezas que iran en el tablero

/*
	*La estrucutura basica del tablero fue creada el 4 de mayo 2016

	*Los metodos de movimientos se agregaron el 08 de mayo 2016

*/

template<class T>  //Usaremos plantillas para mayor reutilizacion de codigo en futuros proyectos

class Tablero
{
private:
	T*** tablero;   //TABLERO DINAMICO DE TIPO T
	int fila;
	int columna;
public:
	Tablero();  //Constructor, al inicio no tendra piezas

	Tablero(ifstream &); //Constructor para cargar partidas

	void insertar(T*,int,int); //Inserta una ficha en el tablero, los int se refieren a la posicion esto se puede eliminar mas adelante

    //GETS que usaremos como auxiliares mas adelante

	int getFila(){ return fila; } 

	int getColuma(){ return columna; }

	string mostrarTablero(); //Mostrar tablero con o sin piezas

	void guardar();

	bool mover(T*,int,int);

	T* obtenerPieza(int,int); //Retorna una pieza que se encuentra en cierta posiciom
	
	T*** getTablero(); //Devuelve el tablero

	int cantidadPiezas(); //Metodo auxiliar que nos dira la cantidad de piezas que se encuentran en el tablero

	~Tablero(void); //Destructor
};

template<class T>

Tablero<T>::Tablero(){  //Al construirse el tablero estara completamente vacio
	tablero=new T **[fila=8];
		for(int i=0;i<fila;i++){
			tablero[i]=new T *[columna=8];
		}
	for(int i=0;i<fila;i++){
		for(int j=0;j<columna;j++){
			tablero[i][j]=NULL;
		}
	}
}


template<class T>

string Tablero<T>::mostrarTablero(){
	stringstream s;
	ALLEGRO_BITMAP * trans = al_load_bitmap("Transparencia.png");
	s<<" "; //PARA DAR MAS ESPACIOS A LA CORDENADA (0,0)
	for(int i=0;i<columna;i++){s<<" "<<i;}  //IMPRIME LA PRIMERA LINEA
	s<<endl;
		for(int i=0;i<fila;i++){
			s<<i<<" ";
			for(int j=0;j<columna;j++){
				if(tablero[i][j]){
					s<<tablero[i][j]->toString()<<" ";//Muestra la pieza
				}
				else{
					s<<"X"<<" ";
				}
			}
			s<<endl;
		}
		
	return s.str();
}

template<class T>

Tablero<T>::~Tablero(){
	for(int i=0;i<fila;i++){
		for(int j=0;j<columna;j++){
			if(tablero[i][j]){               //Si hay pieza...
				delete tablero[i][j];        //Se elimina
			}
		}
	}
	for(int i=0;i<fila;i++){
		delete []tablero[i];
	}
	if(tablero){ delete []tablero;}  //Se elimina el tablero vacio
}

template<class T>

void Tablero<T>::insertar(T* x , int f , int c){  //Se inserta un objeto en la posicion f,c donde f es la fila y c la columna
	tablero[f][c]=x;
}

template<class T>

bool Tablero<T>::mover(T* p,int f, int c){ //Mueve una pieza a una determinada posicion
	try{
	if(tablero[f][c]&&p->getColor()!=tablero[f][c]->getColor()||tablero[f][c]==NULL){ //Si es posible un movimiento
	tablero[p->getFila()][p->getColumna()]=NULL; //Elimina lo que esta ahi
	p->setFila(f);  //Setea la fila
	p->setColumna(c); //Setea la columna
	tablero[f][c]=p; //Iguala la nueva posicion a la ficha que se movio
	return true; 
	}
	else{
	throw 'a'; //Si no es posible.....
	}
	
	}
	catch(...)
	{
	return false;
	}
}


template<class T>

T* Tablero<T>::obtenerPieza(int f, int c){ //Retorna una pieza que se encuentra en cierta posicion
	if(f<8 && c<8){
		return tablero[f][c];}
	else{
	cout<<"dato invalido"<<endl;
	return NULL;
	}
}

template<class T>

int Tablero<T>::cantidadPiezas(){ //Retorna la cantidad de piezas que se encuentran en el tablero
	int contador=0;
	for(int i=0;i<fila;i++){
		for(int j=0;j<columna;j++){
			if(tablero[i][j])contador++;
		}
	}
	return contador;
}

template<class T>
T*** Tablero<T>::getTablero() //Retorna al tablero para que pueda ser usado por el control
{  return tablero; }


