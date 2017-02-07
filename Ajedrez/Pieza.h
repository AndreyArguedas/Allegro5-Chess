//Universidad Nacional 
//Proyecto #2 de Programacion 2
//Desarrollado por Andrey Arguedas Espinoza y Derian Sibaja Chavarria

#pragma once
#include "Librerias.h"

/*
	*La estructura basica de esta clase fue creada el 05 de mayo 2016

	*Los metodos de guardar fueron creados el 20 de mayo 2016
*/

class Pieza
{
protected:
	string tipo; //El tipo de pieza que es

	int f;  //Posicion fila en el tablero

	int c;  //Posicion columna en le tablero

	bool estado; //La pieza ha sido comida o no...

	bool blackorWhite; //Define si es una ficha blanca o negra

public:
	Pieza(int, int, bool);

	virtual string toString()=0; // Virtual puro

	virtual bool movimiento(Pieza***, int x, int y, bool c)=0;//recibe el tablero para efectuar el movimiento, y  la posicines a movilizarse, el bool determina el jugador a jugar

	///////////////////////////////////////////////////////////////Metodos set///////////////////////////////////////////////////////////////////
	void setTipo(string);
	void setFila(int);
	void setColumna(int);
	void setXY(int,int);
	void setEstado();  //No recibira nada por parametro ya que cuando se haga el set solamente se cambiara su estado por el contrario estado que posee
	/////////////////////////////////////////////////////////////Metodos get/////////////////////////////////////////////////////////////////////
	string getTipo();
	int getFila();
	int getColumna();
	bool getEstado();
	bool getColor();// devuelve si es blanca o negra (atributo blackorwhite)

	virtual void guardar(ofstream &,bool=false,string=""); //Guarda bajo el sistema algebraico
	
	char convertirColumnaAletra(); //Metodo para los archivos

	virtual ~Pieza(void);
};

