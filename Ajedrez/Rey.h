//Universidad Nacional 
//Proyecto #2 de Programacion 2
//Desarrollado por Andrey Arguedas Espinoza y Derian Sibaja Chavarria
#pragma once
#include "Pieza.h"
/*
	*Simula a la ficha rey, cuyos movimientos son de una posicion, creada el 06 mayo 2016
*/
class Rey:public Pieza //Hereda de pieza
{
public:
	Rey(int,int, bool);

	string toString();

	//////////////////////////////////////////////////////Validaciones///////////////////////////////////////////////////////////////
	bool movimiento(Pieza***,int, int, bool );
	bool movimientoNormal(Pieza***,int, int, bool );
	bool validarFilas(Pieza***,int, int, bool);
	bool validarColumnas(Pieza***,int, int, bool);
	bool validarDiagonales(Pieza***,int, int, bool);




	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual ~Rey(void);
};

