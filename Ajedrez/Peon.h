//Universidad Nacional 
//Proyecto #2 de Programacion 2
//Desarrollado por Andrey Arguedas Espinoza y Derian Sibaja Chavarria
#pragma once
#include "Pieza.h"

/*
	*Simula el peon el cual posee movimientos de una casilla o 2 en el primer turno creado el 06 mayo 2016
*/

class Peon:public Pieza  //Hereda de pieza
{
private:
	bool primerTurno; //Lleva el control del primerTurno, ya que en el primer turno el peon puede moverse de distinto en el primer turno

public:

	Peon(int, int, bool); //Constructor

	string toString(); //Metodo que muestra al peon

	void setPrimerTurno();

	bool getPrimerTurno();
	//////////////////////////////////////////////////////////////////Validaciones///////////////////////////////////////////////////////
	bool primerMovimiento(Pieza***,int, int , bool);

	bool movimientoNormal(Pieza***,int, int , bool);

	bool movimientoAtaque(Pieza***,int, int , bool);

	bool existePiezaAAtacar(Pieza***,int, int , bool);

	bool movimiento(Pieza***,int, int , bool);
	
	virtual ~Peon(void);
};

