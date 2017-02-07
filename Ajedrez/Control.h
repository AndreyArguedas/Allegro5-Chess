
//Universidad Nacional 
//Proyecto #2 de Programacion 2
//Desarrollado por Andrey Arguedas Espinoza y Derian Sibaja Chavarria
#pragma once
#include "Tablero.h"
#include "Interfaz.h"

/*
*	ESTA CLASE SE ENCARGARA DE LLEVAR EL CONTROL DEL JUEGO, CREADA EL 07 MAYO 2016
*/

/*
  *El dia 8 de mayo se agregan los metodos basicos como mostrarJuego,colocar piezas e iniciar Juego.
	
  *El dia 10 de mayo se agregan metodos mas importantes como mover y cambiar Turno.

  *El 16 de mayo se comienzan a agregar validaciones de filas y columnas digitadas por el usuario

  *Del 20 al 25 de mayo se trabaja en el modo de juego "cargar partida", el 26 de mayo se finaliza con la estructura basica del control,
   los siguientes dias se realizan pequeños cambios de estetica y encapsulacion de codigo
*/

class Control
{
private:
	Tablero<Pieza> * tablero; //Tablero de 8*8
	Interfaz * i; //Utilizaremos la interfaz para comunicacion con el usuario
	ALLEGRO_DISPLAY * display;
public:
	Control(void);

	void set_Display_Properties();

	void colocarPiezas(); //Se encarga de colocar las piezas en el tablero

	void mostrarJuego(); //Muestra cada cambio realizado en el tablero

	void iniciarJuego(); //Comienza el juego, ya sea normal o por una partida guardada

	void mover(bool,string); //Recibe un bool para determinar cual jugador juega, simplemente mueve una ficha y retorna si el movimiento fue exitoso

	void juego(string,bool=false); //Controla el juego, tanto el pedir filas y columnas, el string sera el nombre del archivo en el que se guardara

	bool cambiarTurno(bool); //Controla que jugador lleva el turno

	int validarDatoX(string); //Valida los datos dados por el usuario

	int validarDatoY(string); //Valida los datos de las columnas los cuales son letras y los convertira en numeros

	int pasarLetraANumeros(string); //En las columnas el usuario digitara letras, este metodo se encargara de convertirlas a numeros

	bool letraColumna(string); //Nos dira si esa letra es de las de la columna

	int menuInicial(); //Llama al menu de la interfaz y retorna la opcion escogida por el usuario

	void guardarMovimiento(Pieza *,string,bool=false,string=""); //Se encarga de ir guardando movimiento por movimiento, guarda la pieza, si hubo comida y la columna anterior si es un peon

	void cargarJuego(string); //Carga una partida anterior y al terminar de cargar continua la partida,el string es la partida que cargara

	void subMenu1(); //Submenu de la opcion 1

	void subMenu2(); //Submenu de la opcion 2

	string pasarNumALetra(string); //Pasa un numero a letra, esto es un metodo auxiliar

	Pieza * encuentraRey(bool);

	bool Detectajaque(bool);

	int convertidorFila(int);//Convierte una fila del numero del tablero al verdadero numero que usa en la matriz

	void convertidor_mouse(int &,int&);
	
	int convertidor_axe_y(int);

	string aux_archive(int);

	void game_inits();

	string user_keyboard(); //Si me sirve pasarlo a una clase 

	~Control(void);  //Destructor
};


