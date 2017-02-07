#include "Pieza.h"


Pieza::Pieza(int f, int c, bool bw){
	tipo="|";  //Tipo indefinido
	this->f=f;
	this->c=c;
	estado=true;  //Al crearse la ficha esta viva
	blackorWhite=bw;
}

void Pieza::setTipo(string t){ tipo = t; }

void Pieza::setFila(int f){ this->f=f; }

void Pieza::setColumna(int c){ this->c=c; }

void Pieza::setXY(int f,int c){setFila(f);setColumna(c);}

void Pieza::setEstado(){ estado= false; } //Equivalente a "matar" a la ficha


string Pieza::getTipo(){ return tipo; }

int Pieza::getFila(){ return f; }

int Pieza::getColumna(){ return c; } 

bool Pieza::getEstado(){ return estado; }

bool Pieza::getColor(){ return blackorWhite; }

void Pieza::guardar(ofstream & salida,bool c,string cA){
	if(c && cA!=""){ //Si hubo comida de un peon marcamos con una x 
		salida<<"\t"<<cA<<tipo<<'x'<<convertirColumnaAletra()<<8-f;
	}
	else if(c){
		salida<<"\t"<<tipo<<'x'<<convertirColumnaAletra()<<8-f;
	}
	else if (!c){ //Sino hubo comidad guardamos solo el movimiento
				salida<<"\t"<<tipo<<convertirColumnaAletra()<<8-f;
	}
}

char Pieza::convertirColumnaAletra(){  ///Este metodo es para que los archivos sean guardados bajo la notacion algebraica
	switch(this->c){
	case 0: return 'a';break;
	case 1: return 'b';break;
	case 2: return 'c';break;
	case 3: return 'd';break;
	case 4: return 'e';break;
	case 5: return 'f';break;
	case 6: return 'g';break;
	case 7: return 'h';break;
	default:break;
	}
}


Pieza::~Pieza(void)
{
}
