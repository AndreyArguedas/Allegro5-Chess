//Universidad Nacional 
//Proyecto #2 de Programacion 2
//Desarrollado por Andrey Arguedas Espinoza y Derian Sibaja Chavarria

#pragma once
#include "Pieza.h"

/*
	* Esta clase representa al alfil el cual posee movimientos diagonales, creada el 05 mayo del 2016
*/

class Alfil:public Pieza  //Hereda de la clase pieza
{
public:
	Alfil(int,int, bool);  //Constructor
	string toString();  //Metodo que debe de ser implementado
	bool movimiento(Pieza***,int,int,bool);
	
	///////////////////////////Validacion para cada diagonal///////////////////////////////

	bool movDiagonalSuperiorDerecho(Pieza***,int,int,bool);
	bool movDiagonalInferiorDerecho(Pieza***,int,int,bool);
	bool movDiagonalSuperiorIzquierdo(Pieza***,int,int,bool);
	bool movDiagonalInferiorIzquierdo(Pieza***,int,int,bool);

	/////////////////////////Destructor//////////////////////////////////////////////
	virtual ~Alfil(void);
};

