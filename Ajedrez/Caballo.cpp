#include "Caballo.h"


Caballo::Caballo(int x, int y, bool bw):Pieza(x,y,bw) //Constructor
{
	tipo="C";
}

string Caballo::toString(){  //Muestra a la pieza
	stringstream s;
	s<<tipo;
	ALLEGRO_BITMAP * pieza = al_load_bitmap("Pieces.png");
	if(blackorWhite){
		al_draw_bitmap_region(pieza,192,0,64,64,c*60,f*58.5,NULL);
	}
	else{
		al_draw_bitmap_region(pieza,192,64,64,64,c*60,f*60,NULL);
	}
	al_flip_display();
	return s.str();
}

bool Caballo::movimiento(Pieza*** tablero,int x, int y, bool c) //Realiza un movimiento
{
	return validarDiagonales(tablero,x,y,c);
}

////////////////////////////////////////Valida diagonales////////////////////////////////////////////

bool Caballo::validarDiagonales(Pieza*** tablero,int f, int col, bool c){
	if(this->f==f-2 && this->c==col+1)return true;
	else if(this->f==f-2 && this->c==col-1)return true;
	else if(this->f==f+2 && this->c==col-1)return true;
	else if(this->f==f+2 && this->c==col+1)return true;
	else if(this->f==f-1 && this->c==col-2)return true; 
	else if(this->f==f-1 && this->c==col+2)return true; 
	else if(this->f==f+1 && this->c==col-2)return true; 
	else if(this->f==f+1 && this->c==col+2)return true;
	else return false;
}

Caballo::~Caballo(void)
{
}
