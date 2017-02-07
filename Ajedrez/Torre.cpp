#include "Torre.h"


Torre::Torre(int x,int y, bool bw):Pieza(x,y, bw) //Constructor
{
	tipo="T";
}

string Torre::toString(){
	stringstream s;
	s<<tipo;
	ALLEGRO_BITMAP * pieza = al_load_bitmap("Pieces.png");
	if(blackorWhite){
		al_draw_bitmap_region(pieza,128,0,64,64,c*58.5,f*58.5,NULL);
	}
	else{
		al_draw_bitmap_region(pieza,128,64,64,64,c*58.5,f*58.5,NULL);
	}
	al_flip_display();
	return s.str();
}

bool Torre::movimiento(Pieza*** tablero,int f, int col, bool c)
{
	return movimientoNormal(tablero,f,col,c);
}

bool Torre::movimientoNormal(Pieza*** tablero,int f, int col, bool c){
	if(this->f==f){ //Si el usuario desea mover solo en lateral
		return validarMovimientoFilas(tablero,f,col,c);
	}
	else if(this->c==col){   //Si el usuario desea mover solo en lateral
		return validarMovimientoColumnas(tablero,f,col,c);
	}
	else
	{
	return false;
	}
}

bool Torre::validarMovimientoFilas(Pieza*** tablero,int f, int col, bool c){
	if(this->c>col){
			for(int i=this->c-1;i>col;i--){
				if(tablero[f][i])return false;//Si en algunas de los espacios anteriores hay una ficha bloqueanod, retorna false
			}
			return true;
		}
		else if(this->c<col){
			for(int i=this->c+1;i<col;i++){
				if(tablero[f][i])return false;//Si en algunas de los espacios anteriores hay una ficha bloqueanod, retorna false
			}
			return true;
		}
	}

bool Torre::validarMovimientoColumnas(Pieza*** tablero,int f, int col, bool c){
	if(this->f>f){
			for(int i=this->f-1;i>f;i--){
				if(tablero[i][col])return false;//Si en algunas de los espacios anteriores hay una ficha bloqueanod, retorna false
			}
			return true;
		}
		else if(this->f<f){
			for(int i=this->f+1;i<f;i++){
				if(tablero[i][col])return false;//Si en algunas de los espacios anteriores hay una ficha bloqueanod, retorna false
			}
			return true;
		}
	}

Torre::~Torre(void)
{
}
