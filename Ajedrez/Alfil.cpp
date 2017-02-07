#include "Alfil.h"


Alfil::Alfil(int x, int y, bool bw):Pieza(x,y, bw) //Constructor
{
	tipo="A";
}

string Alfil::toString(){ //Muestra al alfil
	stringstream s;
	s<<tipo;
	ALLEGRO_BITMAP * pieza = al_load_bitmap("Pieces.png");
	if(blackorWhite){
		al_draw_bitmap_region(pieza,256,0,64,64,c*59,f*58.5,NULL);
	}
	else{
		al_draw_bitmap_region(pieza,256,64,64,64,c*59,f*58.5,NULL);
	}
	al_flip_display();
	return s.str();
}

bool Alfil::movimiento(Pieza*** tablero,int fila, int columna, bool c) //Movimiento
{
	if(fila<this->f&&columna>this->c)
	{
		return movDiagonalSuperiorDerecho(tablero,fila,columna,c);
	}
	else if(fila<this->f&&columna<this->c)
	{
		return movDiagonalSuperiorIzquierdo(tablero,fila,columna,c);
	}
	else if(fila>this->f&&columna>this->c)
	{
		return movDiagonalInferiorDerecho(tablero,fila,columna,c);
	}
	else if(fila>this->f&&columna<this->c)
	{
		return movDiagonalInferiorIzquierdo(tablero,fila,columna,c);
	}
	else
	{
	return false;
	}
}


bool Alfil::movDiagonalSuperiorDerecho(Pieza***tablero,int fila,int columna,bool col) //Valida la diagonal derecha superior
{
	for(int i=1;(c+i!=columna)||(f-i!=fila);i++)
{
	if(c+i>columna||f-i<fila)
	{return false;}
	if(tablero[f-i][c+i])
	{
	return false;//existe alguna ficha en esa posicion;
	}
}
	if(tablero[fila][columna]){
	 if(tablero[fila][columna]->getColor()!=col)
	{
	return true;
	}
	else{
		return false;}//hay una piezza del mismo tipo en esa posicion
	}
	return true; //no hay nada en esa posicion
}




bool Alfil::movDiagonalInferiorDerecho(Pieza***tablero,int fila,int columna,bool col)
{
	for(int i=1;(c+i!=columna)||(f+i!=fila);i++)
{
	if(c+i>columna||f+i>fila)
	{
	return false;//sobrepasa la lateral
	}
	if(tablero[f+i][c+i])
	{
	return false;//existe alguna ficha en esa posicion;
	}
}
	if(tablero[fila][columna]){
	 if(tablero[fila][columna]->getColor()!=col)
	{
	return true;
	}
	else{
		return false;}//hay una piezza del mismo tipo en esa posicion
	}
	return true; //no hay nada en esa posicion

}


bool Alfil::movDiagonalSuperiorIzquierdo(Pieza***tablero,int fila,int columna,bool col)
{
	for(int i=1;(c-i!=columna)||(f-i!=fila);i++)
{
	if(c-i<columna||f-i<fila)
	{
	return false;
	}
	if(tablero[f-i][c-i])
	{
	return false;//existe alguna ficha en esa posicion;
	}
}
	if(tablero[fila][columna]){
	 if(tablero[fila][columna]->getColor()!=col)
	{
	return true;
	}
	else{
		return false;}//hay una piezza del mismo tipo en esa posicion
	}
	return true; //no hay nada en esa posicion
}
bool Alfil::movDiagonalInferiorIzquierdo(Pieza***tablero,int fila,int columna,bool col)
{
	for(int i=1;(c-i!=columna)||(f+i!=fila);i++)
{
	if(c-i<columna||f+i>fila)
	{return false;}
	if(tablero[f+i][c-i])
	{
	return false;//existe alguna ficha en esa posicion;
	}
}
	if(tablero[fila][columna]){
	 if(tablero[fila][columna]->getColor()!=col)
	{
	return true;
	}
	else{
		return false;}//hay una piezza del mismo tipo en esa posicion
	}
	return true; //no hay nada en esa posicion
}

Alfil::~Alfil(void)
{
}
