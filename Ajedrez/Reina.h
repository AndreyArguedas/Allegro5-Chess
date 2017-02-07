//Universidad Nacional 
//Proyecto #2 de Programacion 2
//Desarrollado por Andrey Arguedas Espinoza y Derian Sibaja Chavarria

#pragma once
#include "Pieza.h"

/*
	*Simula a la ficha reina, cuyos movimientos son libres en cualquier direccion, creada el 06 mayo 2016
*/

class Reina:public Pieza //Hereda de pieza
{
public:
	Reina(int,int, bool); //Constructor

	string toString();//Muestra

	bool movimiento(Pieza***,int, int, bool);

	///////////////////////////////////////////////////////Validaciones///////////////////////////////////////////////////////////////////////
	bool validarMovimientoFilas(Pieza***,int, int, bool); //Se encarga de velar porque no hayan piezas bloqueando el camino
	bool validarMovimientoColumnas(Pieza***,int, int, bool);
	bool movDiagonalSuperiorDerecho(Pieza***,int,int,bool);
	bool movDiagonalInferiorDerecho(Pieza***,int,int,bool);
	bool movDiagonalSuperiorIzquierdo(Pieza***,int,int,bool);
	bool movDiagonalInferiorIzquierdo(Pieza***,int,int,bool);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual ~Reina(void);

};

