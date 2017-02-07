#include "Rey.h"


Rey::Rey(int x,int y, bool bw):Pieza(x,y,bw)
{
	tipo="R";
}

string Rey::toString(){
	stringstream s;
	s<<tipo;
	ALLEGRO_BITMAP * pieza = al_load_bitmap("Pieces.png");
	if(blackorWhite){
		al_draw_bitmap_region(pieza,0,0,64,64,c*59,f*58.5,NULL);
	}
	else{
		al_draw_bitmap_region(pieza,0,64,64,128,c*59,f*58.5,NULL);
	}
	al_flip_display();
	return s.str();
}
/*
 * El siguiente metodo se encarga de enviarle el mensaje a control de que esta ficha efectivamente puede ser enviada
 * Creado el 10/05/2016
*/
bool Rey::movimiento(Pieza*** tablero,int f, int col, bool c)
{
	return movimientoNormal(tablero,f,col,c);
}

/*
 * Control de los movimientos validos para un rey, este metodo cuenta con buen uso de encapsulacion
 * Creado el 18/05/2016
*/

bool Rey::movimientoNormal(Pieza*** tablero,int f, int col, bool c ){
	if(this->f==f){  //Si se desea un deseo lateral
		return validarColumnas(tablero,f,col,c);
	}
	else if(this->c==col){ //Si se desea mover horizontalemente
		return validarFilas(tablero,f,col,c);
	}

	else{  //Si es un movimiento lateral
		validarDiagonales(tablero,f,col,c);
	}
}

/*
 * Validacion de movimientos horizontales
 * Creado el 18/05/2016
*/

bool Rey::validarFilas(Pieza*** tablero,int f, int col, bool c){
	if(this->f==f-1){  
		return true;
	}
	else if(this->f==f+1){
		return true;
	}
	else{
		return false;
	}
}

/*
 * Validacion de movimientos verticales
 * Creado el 18/05/2016
*/
	
bool Rey::validarColumnas(Pieza*** tablero,int f, int col, bool c){
	if(this->c==col-1){  
		return true;
	}
	else if(this->c==col+1){
		return true;
	}
	else{
		return false;
	}
}

/*
 * Validacion de movimientos diagonales
 * Creado el 18/05/2016
*/

bool Rey::validarDiagonales(Pieza*** tablero,int f, int col, bool c){
	if(this->f==f-1 && this->c==col+1)return true;
	else if(this->f==f-1 && this->c==col-1)return true;
	else if(this->f==f+1 && this->c==col-1)return true;
	else if(this->f==f+1 && this->c==col+1)return true;
	else return false;
}






Rey::~Rey(void)
{
}
