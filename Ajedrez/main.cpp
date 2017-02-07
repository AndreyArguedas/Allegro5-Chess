//Universidad Nacional 
//Proyecto #2 de Programacion 2


#include "Control.h"

/*
	*Instances the control and starts the game
*/

void main(){
	FreeConsole(); //Dont show the cmd 
	Control * c=new Control;
	c->iniciarJuego();
	delete c;
}