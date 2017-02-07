//Universidad Nacional 
//Proyecto #2 de Programacion 2
//Desarrollado por Andrey Arguedas Espinoza y Derian Sibaja Chavarria
#pragma once
#include "Pieza.h"
/*
	*Esta clase simula a una torre cuyos movimientos son verticales o horizontales, creada el 06 mayo 2016
*/

class Torre:public Pieza
{
public:
	Torre(int,int, bool); //Constructor

	string toString();//Muestra a la pieza

	///////////////////////////////////////////////////////Validaciones//////////////////////////////////////////////////////////////////

	bool movimiento(Pieza***,int, int, bool);

	bool movimientoNormal(Pieza***,int, int, bool);

	bool validarMovimientoFilas(Pieza***,int, int, bool); //Se encarga de velar porque no hayan piezas bloqueando el camino

	bool validarMovimientoColumnas(Pieza***,int, int, bool);//Se encarga de velar porque no hayan piezas bloqueando el camino

	virtual ~Torre(void);
};

