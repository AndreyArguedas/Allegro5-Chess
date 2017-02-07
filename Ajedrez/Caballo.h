//Universidad Nacional 
//Proyecto #2 de Programacion 2
//Desarrollado por Andrey Arguedas Espinoza y Derian Sibaja Chavarria
#pragma once
#include "Pieza.h"

/*
	*	Esta clase representa a la ficha caballo cuyos movimientos son en L por cada 3 espacios creada el 06 mayo 2016
*/

class Caballo:public Pieza  //Hija de pieza
{
public:
	Caballo(int,int,bool);
	string toString();
	bool movimiento(Pieza***,int, int, bool);
	bool validarDiagonales(Pieza***,int, int, bool); //Validaciones de los posibles movimientos de un caballo
	virtual ~Caballo(void);
};

