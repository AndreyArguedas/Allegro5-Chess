#include "Peon.h"


Peon::Peon(int x, int y, bool bw):Pieza(x,y, bw)
{
	tipo="";  //Dejamos un espacio ya que en el lenguaje algebraico el peon no posee letra
	primerTurno=true;
}

void Peon::setPrimerTurno(){
	primerTurno=!this->primerTurno;
}

bool Peon::getPrimerTurno(){
	return primerTurno;
}

string Peon::toString(){
	stringstream s;
	s<<"P";
	ALLEGRO_BITMAP * pieza = al_load_bitmap("Pieces.png");
	if(blackorWhite){
		al_draw_bitmap_region(pieza,320,0,384,64,c*59,f*58.5,NULL);
	}
	else{
		al_draw_bitmap_region(pieza,320,64,384,128,c*59,f*58.5,NULL);
	}
	al_flip_display();
	return s.str();
}

bool Peon::movimiento(Pieza***tablero,int fila, int columna, bool c) 
{
	if(this->c!=columna)
	{
		return movimientoAtaque(tablero, fila, columna,  c);
	}
	else if(primerTurno)
	{
		return primerMovimiento(tablero, fila, columna,  c);

	}
	else 
	{
		return movimientoNormal(tablero, fila, columna,  c);
	}
}


bool Peon::movimientoNormal(Pieza***tablero,int f, int col, bool c){  //Valida el movimiento normal
	if(c==true && this->f-1==f && this->c==col  && tablero[this->f-1][col] == NULL)
	{return true;}
	else if(c==false && this->f+1 == f && this->c==col && tablero[this->f+1][col] == NULL)return true;
	else return false;
}

bool Peon::primerMovimiento(Pieza***tablero,int f, int col, bool c){//Se encargara de realizar y validar
	if(c==true&&(this->f-1==f||this->f-2==f )&& this->c==col&&tablero[this->f-1][col]==NULL&&tablero[this->f-2][col]==NULL)
	{
	setPrimerTurno();	
	return true;
	}
	else if(c==false&&(this->f+1==f||this->f+2==f )&& this->c==col&&tablero[this->f+1][col]==NULL&&tablero[this->f+2][col]==NULL)
	{	setPrimerTurno();return true;}
	else
	{return false;}
}

bool Peon::movimientoAtaque(Pieza***tablero,int f, int col , bool c)
{
	if(c==true && this->f-1==f && (col==this->c+1||col==this->c-1))
	{
		return existePiezaAAtacar(tablero,f,col,c);
	}
	else if(c==false && this->f+1==f && (col==this->c+1||col==this->c-1))
	{
		return existePiezaAAtacar(tablero,f,col,c);
	
	}
	else return false;
}


	bool Peon::existePiezaAAtacar(Pieza***tablero,int f, int col, bool c){

		if(tablero[f][col]!=NULL && tablero[f][col]->getColor()!=c){
				if(primerTurno) // setea el primer turno y el primer movimiento es un ataque.
				{setPrimerTurno();}
				return true;
		}
		else{
			return false;
		}
	
	}

Peon::~Peon(void)
{
	
}

