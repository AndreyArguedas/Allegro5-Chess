#include "Reina.h"


Reina::Reina(int x,int y, bool bw):Pieza(x,y,bw)
{
	tipo="D"; 
}

string Reina::toString(){
	stringstream s;
	s<<tipo;
	ALLEGRO_BITMAP * pieza = al_load_bitmap("Pieces.png");
	if(blackorWhite){
		al_draw_bitmap_region(pieza,64,0,64,64,c*59,f*58.5,NULL);
	}
	else{
		al_draw_bitmap_region(pieza,64,64,64,64,c*59,f*58.5,NULL);
	}
	al_flip_display();
	return s.str();
}

bool Reina::movimiento(Pieza*** tablero,int fila, int columna, bool c)
{
	if(this->f==fila){ //Si el usuario desea mover solo en lateral
		return validarMovimientoFilas(tablero,fila,columna,c);
	}
	else if(this->c==columna){   //Si el usuario desea mover solo en lateral
		return validarMovimientoColumnas(tablero,fila,columna,c);
	}
	else if(fila<this->f&&columna>this->c)
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




bool Reina::validarMovimientoFilas(Pieza*** tablero,int f, int col, bool c){
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

bool Reina::validarMovimientoColumnas(Pieza*** tablero,int f, int col, bool c){
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


bool Reina::movDiagonalSuperiorDerecho(Pieza***tablero,int fila,int columna,bool col)
{
	//(fila<this->f&&columna>this->c) se declara en movimiento


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




bool Reina::movDiagonalInferiorDerecho(Pieza***tablero,int fila,int columna,bool col)
{
		//(fila>this->f&&columna>this->c) se declara en movimiento


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


bool Reina::movDiagonalSuperiorIzquierdo(Pieza***tablero,int fila,int columna,bool col)
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
bool Reina::movDiagonalInferiorIzquierdo(Pieza***tablero,int fila,int columna,bool col)
{
//(fila>this->f&&columna<this->c) se declara en movimiento


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



Reina::~Reina(void)
{
}
