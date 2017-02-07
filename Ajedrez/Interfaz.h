//Universidad Nacional 
//Proyecto #1 de Programacion 2
//Desarrollado por Andrey Arguedas Espinoza y Derian Sibaja Chavarria

/*
	*ESTA CLASE SE ENCARGARA DE LLEVAR LA INTERFAZ DEL JUEGO, TANTO MENUS COMO ADVERTENCIAS Y DEMAS

	*Funciones del gotoxy y menus principales fueron creadas el 07 mayo 2016

	*Solicitudes de datos y adevertencias fueron agregadas el 10 mayo 2016
*/

#pragma once
#include "Librerias.h"
#include "Tablero.h"

class Interfaz
{
public:
	Interfaz(void);	//Constructor
	
	void imagPiezas(); 

	void titulo();//Muestra un banner en codigo ASCII

	void limpiarPantalla(); //Un simple "cls"

	void impTablero(Tablero<Pieza>*);//Imprime el tablero

	void datoInvalido(string);//el string funciona para extender el mensaje, asi reutilizamo codigo
	
	void pedirNombrePartida(); //Pide un nombre para trabajar las partidas

	void recuperarPartida(); //Pide el nombre de un archivo para ver si se encuentra en el sistema

	void errorCargarPartida(string); //Le avisa al usuario que la partida no se encuentra en el sistema

	void jaque(bool);

	void jaqueMate(bool);

	void musica();

	void whoStarts(bool); //Shows which player starts the match


	~Interfaz(void); //Destructor
};