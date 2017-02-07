#include "Control.h"


Control::Control(void)
{
	game_inits();
	tablero=new Tablero <Pieza>();  //Se crea un tablero de 8*8
	i=new Interfaz;
	display = al_create_display(485,485);
	set_Display_Properties();
}

void Control::game_inits(){
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	al_install_keyboard();
	al_install_audio();
	al_init_acodec_addon();
}

void Control::set_Display_Properties(){
	al_set_window_title(display,"MEDIEVAL CHESS");
}

void Control::colocarPiezas(){
	 //INSERTAR PEONES
	for(int i=0;i<8;i++){  
	tablero->insertar(new Peon(1,i,false),1,i);
	tablero->insertar(new Peon(6,i,true),6,i);
	}
	///////INSERTAR TORRES///////////
	tablero->insertar(new Torre(0,0,false),0,0);
	tablero->insertar(new Torre(0,7,false),0,7);
	tablero->insertar(new Torre(7,0,true),7,0);
	tablero->insertar(new Torre(7,7,true),7,7);
	/////INSERTAR CABALLO////////////
	tablero->insertar(new Caballo(0,1,false),0,1);
	tablero->insertar(new Caballo(0,6,false),0,6);
	tablero->insertar(new Caballo(7,1,true),7,1);
	tablero->insertar(new Caballo(7,6,true),7,6);
	////INSERTAR ALFIL/////////////////
	tablero->insertar(new Alfil(0,2,false),0,2);
	tablero->insertar(new Alfil(0,5,false),0,5);
	tablero->insertar(new Alfil(7,2,true),7,2);
	tablero->insertar(new Alfil(7,5,true),7,5);
	////INSERTAR REYES Y REINAS///////
	tablero->insertar(new Reina(0,3,false),0,3);
	tablero->insertar(new Rey(0,4,false),0,4);
	tablero->insertar(new Rey(7,4,true),7,4);
	tablero->insertar(new Reina(7,3,true),7,3);
}

void Control::mostrarJuego(){
	i->impTablero(tablero);
}

void Control::iniciarJuego(){
	int opcion=0;
	i->titulo();
	i->musica();
	bool quit =false;
	ALLEGRO_EVENT_QUEUE * event = NULL;
	event = al_create_event_queue();
	al_register_event_source(event,al_get_display_event_source(display));
	al_register_event_source(event,al_get_keyboard_event_source()); //Le digo al evento que voy a usar el teclado
		while(!quit){
			ALLEGRO_EVENT ev;
			al_wait_for_event(event,&ev);
				if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
					quit=true;
				}
				else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
					switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_ENTER:opcion=1;quit=true;break;
				case ALLEGRO_KEY_SPACE:opcion=2;quit=true;break;
					}
				}
		}
	al_destroy_event_queue(event);
	if(opcion==1){
		subMenu1();
		tablero=new Tablero<Pieza>;
		colocarPiezas();
		juego(user_keyboard());

	}
	else if(opcion==2)
	{
		subMenu2();
		tablero=new Tablero<Pieza>;
		colocarPiezas();
		cargarJuego(user_keyboard());
	}

}

void Control::subMenu1(){ //Submenu para la opcion de comenzar una partida
	i->imagPiezas();
	i->pedirNombrePartida();
}

void Control::subMenu2(){
	i->imagPiezas();
	i->recuperarPartida();
}

void Control::cargarJuego(string arc){ //Carga una partida guardada
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	string space;string movimiento;int fila;string columna;bool c=true;string extension=".txt"; //Algunas variables auxiliares
	string folder;
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    string::size_type pos = string( buffer ).find_last_of( "\\/" );
    folder = string( buffer ).substr( 0, pos);
	string separador = "\\/";
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Pieza * aux; //Una pieza auxiliar
	ifstream archivo(folder+separador+arc.c_str()+extension,ios::in); //Abrimos la partida anterios
	if(archivo){
	while(!archivo.eof()){ //Mientras hayan jugadas...
	i->limpiarPantalla();
	archivo>>movimiento; //Substrae la primera jugada
	mostrarJuego();  //Muestra el tablero ya con piezas.

	if(movimiento.length()==2){ //Si lo que se movio fue un peon
		columna=movimiento[0];
		fila=(int)(movimiento[1]-48);
	}

	else if(movimiento.length()==3){  //Si es un movimiento normal de cualquier pieza
		columna=movimiento[1];
		fila=(int)(movimiento[2]-48);
	}
	
	aux = tablero->obtenerPieza(convertidorFila(fila)-1,pasarLetraANumeros(columna)); 

	if(aux){
		archivo>>movimiento; //Substraemos el movimiento realizado
			if(movimiento.length()==2){ //Si lo que se movio fue un peon
				columna=movimiento[0];
				fila=(int)(movimiento[1]-48);
			}
			else if(movimiento.length()==3){  //Si es un movimiento normal de cualquier pieza
				columna=movimiento[1];
				fila=(int)(movimiento[2]-48);
			}
			else if(movimiento.length()>=4){ //Cuando hubo comidas o comentarios especiales de las jugadas
				columna=movimiento[2];
				fila=(int)(movimiento[3]-48);
			}
		tablero->mover(aux,convertidorFila(fila)-1,pasarLetraANumeros(columna));// retorna true si el movimiento se realizo correctamente
		c=cambiarTurno(c); //Pasa el turno al siguiente usuario
		Sleep(1900); //Una pausa de 2 segundos para que los movimientos se aprecien mejor
		}
	}
	mostrarJuego();
	juego(arc,!c); //Como la partida carga debemos setear el turno, ya que ella solo guarda el ultimo
}
	else{
		i->errorCargarPartida(arc); //Envia un mensaje de error al usuario para avisarle que la partida no esta en el sistema
	}
}

string Control::aux_archive(int col){
	stringstream out;
	string aux;
	out<<col;
	aux=out.str();
	aux=pasarNumALetra(aux);
	return aux;
}

void Control::mover(bool c,string arc) // Movimientos en el tablero, el bool define el turno 
{
	Pieza * aux;
	int cont=0; //cuenta si es la primera vez que recorre el ciclo
	do{
	mostrarJuego();
	cont++;
	bool quit = false;
	int fila = 0;int columna = 0;
	ALLEGRO_EVENT_QUEUE *evento =al_create_event_queue();
	al_register_event_source(evento,al_get_mouse_event_source());
	al_register_event_source(evento,al_get_keyboard_event_source());
	al_register_event_source(evento,al_get_display_event_source(display));
	ALLEGRO_MOUSE_STATE mouseState;
	while(!quit){
	ALLEGRO_EVENT e;
	al_wait_for_event(evento,&e);
		if(e.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			if(e.mouse.button&1){
				fila=e.mouse.x;
				columna=e.mouse.y;
				convertidor_mouse(fila,columna);
				if(fila != -1 && columna != -1){quit = true;}
			}
		}
		else if(e.type==ALLEGRO_EVENT_DISPLAY_CLOSE){exit(0);}
	}
	quit = false;
	aux = tablero->obtenerPieza(fila,columna);
	if(aux) //Si una pieza fue retornada con exito
	{
	if(aux->getColor()!=c)  // checkea si escogia la ficha le pertence al jugador
	{
		i->datoInvalido("INVALID PIECE");
	}
	else{
		while(!quit){
		ALLEGRO_EVENT e;
		al_wait_for_event(evento,&e);
			if(e.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
				if(e.mouse.button&1){
				//quit=true;
				fila=e.mouse.x;
				columna=e.mouse.y;
				convertidor_mouse(fila,columna);
				if(fila != -1 && columna != -1){quit = true;}
				}
			}
			else if(e.type==ALLEGRO_EVENT_DISPLAY_CLOSE){exit(0);}
		}
	if(aux->movimiento(tablero->getTablero(),fila,columna,c)){
		int cuentaFichas=tablero->cantidadPiezas(); //Cuenta cuantas fichas hay antes del movimiento
		guardarMovimiento(aux,arc);//Guardamos el estado anterior de la pieza
		bool b=tablero->mover(aux,fila,columna);// retorna true si el movimiento se realizo correctamente
		if(b)
		{
		if(cuentaFichas>tablero->cantidadPiezas()&& aux->getTipo()==""){ //Si un peon realizo una comida hay que hacer un tratamiento especial
		
			guardarMovimiento(aux,arc,b,aux_archive(columna));///Apenas se mueva la pieza la guardaremos, si hubo comida marcamos con
		}
		else if(cuentaFichas>tablero->cantidadPiezas()){ 
			guardarMovimiento(aux,arc,b);///Apenas se mueva la pieza la guardaremos, si hubo comida marcamos con x
		}
		else{
			guardarMovimiento(aux,arc); //Si no hubo comida solo registramos el movimiento
		}
		
		aux=NULL;//sale del ciclo
		}
		else
		{
		i->datoInvalido("INVALID PIECE");
		}
	  }
    }
   }	
	else
	{
	aux=new Peon(-1,-1,false);
	}
  }
	while(aux!=NULL );
}

void Control::juego(string archivo,bool turno) // Define el juego y sus moviminetos, usa un archivo donde se guardara
{
	bool c=true;
	i->whoStarts(!turno);
	if(turno){c=cambiarTurno(c);} //Si se le envia por parametro un true le da el turno al otro juagador, esto es a la hora de cargar juego
		while(encuentraRey(c)){
				if(Detectajaque(c)){
					i->jaque(c);
				}
			mover(c,archivo);
			c=cambiarTurno(c);
		}
	i->jaqueMate(c);
}

void Control::guardarMovimiento(Pieza *p,string arc,bool c,string cA){ //Guarda en un archivo especificado
	string extension=".txt";
	string folder;
	string separador = "\\/";
	char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    string::size_type pos = string( buffer ).find_last_of( "\\/" );
    folder = string( buffer ).substr( 0, pos);
	ofstream archivo(folder+separador+arc.c_str()+extension,ios::app);
	p->guardar(archivo,c,cA);
}


bool Control::cambiarTurno(bool c){ //cambia el estado del color , pasa de true a false y viceversa
	return(c==true)?false: true;
}

//Metodo realizado el 19//05/2016

/*
* ------------------------------------------------------------------------------------------------------------------------------------
*	Este metodo se encarga de realizar una conversion de letra a numero, esto para la coumna del tablero, este metodo no pudo ser reducido
*	ya que c++ no soporta el switch con una variable string, por lo anterior este metodo quedo tan extenso
* ------------------------------------------------------------------------------------------------------------------------------------
*/

void Control::convertidor_mouse(int &x,int &y){
	bool quit = false;
	if(y>18 && y<66){y=convertidor_axe_y(x);x=0;quit=true;}
	else if(y>74 && y<125){y=convertidor_axe_y(x);x=1;quit=true;}
	else if(y>131 && y<179){y=convertidor_axe_y(x);x=2;quit=true;}
	else if(y>186 && y<237){y=convertidor_axe_y(x);x=3;quit=true;}
	else if(y>244 && y<292){y=convertidor_axe_y(x);x=4;quit=true;}
	else if(y>299 && y<349){y=convertidor_axe_y(x);x=5;quit=true;}
	else if(y>354 && y<406){y=convertidor_axe_y(x);x=6;quit=true;}
	else if(y>408 && y<462){y=convertidor_axe_y(x);x=7;quit=true;}
	else y = -1;
}

int Control::convertidor_axe_y(int x){
	if(x>19 && x<70)return 0;
	else if(x>76 && x<127)return 1;
	else if(x>132 && x<183)return 2;
	else if(x>189 && x<238)return 3;
	else if(x>245 && x<295)return 4;
	else if(x>300 && x<353)return 5;
	else if(x>357 && x<407)return 6;
	else if(x>412 && x<464)return 7;
	return -1;
}

int Control::pasarLetraANumeros(string letra){ 
	if(letra=="A"||letra=="a") return 0;
	else if(letra=="B"||letra=="b") return 1;
	else if(letra=="C"||letra=="c") return 2;
	else if(letra=="D"||letra=="d") return 3;
	else if(letra=="E"||letra=="e") return 4;
	else if(letra=="F"||letra=="f") return 5;
	else if(letra=="G"||letra=="g") return 6;
	else if(letra=="H"||letra=="h") return 7;
}

string Control::pasarNumALetra(string n){
	if(n=="0") return "a";
	else if(n=="1") return "b";
	else if(n=="2") return "c";
	else if(n=="3") return "d";
	else if(n=="4") return "e";
	else if(n=="5") return "f";
	else if(n=="6") return "g";
	else if(n=="7") return "h";
}

//Metodo realizado el 19//05/2016

/*
* ------------------------------------------------------------------------------------------
*	Este metodo se encarga de decirnos si la letra digitada esta dentro del rango del juego
* -----------------------------------------------------------------------------------------
*/

bool Control::letraColumna(string letra){
	if(letra=="A"||letra=="a"||letra=="B"||letra=="b"||letra=="C"||letra=="c"||letra=="D"||letra=="d"||letra=="E"||letra=="e"||letra=="F"||letra=="f"||letra=="G"||letra=="g"||letra=="H"||letra=="h")	
		return true;
	return false;
}



Pieza *Control::encuentraRey(bool c)
{
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(tablero->obtenerPieza(i,j) && tablero->obtenerPieza(i,j)->getTipo() == "R"&&tablero->obtenerPieza(i,j)->getColor() == c){
			return tablero->obtenerPieza(i,j);
			}
		}
	}
	return NULL;
}

bool Control::Detectajaque(bool c)
{
	Pieza* Rey=encuentraRey(c);
	Pieza * aux;
	int cont=0;//lleva la cantidad maxima de fichas, esto para evitar todo el recorrido del tablero
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			aux=tablero->obtenerPieza(i,j);
				if(aux&&aux->getColor()!=c){
					if(Rey && aux->movimiento(tablero->getTablero(),Rey->getFila(),Rey->getColumna(),aux->getColor())){return true;}
					cont++;//verifico una ficha
					if(cont==16){return false;}
				}
		}
	}
	return false;
}

int Control::convertidorFila(int f){
	switch(f){
	case 8:return 1;break;
	case 7:return 2;break;
	case 6:return 3;break;
	case 5:return 4;break;
	case 4:return 5;break;
	case 3:return 6;break;
	case 2:return 7;break;
	case 1:return 8;break;
	default:break;
	}
}

Control::~Control(void)
{
	delete tablero;
	al_destroy_display(display);
}

string Control::user_keyboard(){
	int opcion = 0;
	int x = 0;
	bool quit =false;
	string file;
	ALLEGRO_EVENT_QUEUE * event = NULL;
	ALLEGRO_FONT * font_24 = al_load_font("Prince Valiant.ttf",24,NULL);
	event = al_create_event_queue();
	al_register_event_source(event,al_get_display_event_source(display));
	al_register_event_source(event,al_get_keyboard_event_source()); //Le digo al evento que voy a usar el teclado
		while(!quit){
			ALLEGRO_EVENT ev;
			al_wait_for_event(event,&ev);
				if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
					quit=true;
					exit(0);
				}
				else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
					switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_Q:file.push_back('q');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"Q");break;
				case ALLEGRO_KEY_W:file.push_back('w');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"W");break;
				case ALLEGRO_KEY_E:file.push_back('e');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"E");break;
				case ALLEGRO_KEY_R:file.push_back('r');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"R");break;
				case ALLEGRO_KEY_T:file.push_back('t');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"T");break;
				case ALLEGRO_KEY_Y:file.push_back('y');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"Y");break;
				case ALLEGRO_KEY_U:file.push_back('u');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"U");break;
				case ALLEGRO_KEY_I:file.push_back('i');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"I");break;
				case ALLEGRO_KEY_O:file.push_back('o');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"O");break;
				case ALLEGRO_KEY_P:file.push_back('p');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"P");break;
				case ALLEGRO_KEY_A:file.push_back('a');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"A");break;
				case ALLEGRO_KEY_S:file.push_back('s');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"S");break;
				case ALLEGRO_KEY_D:file.push_back('d');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"D");break;
				case ALLEGRO_KEY_F:file.push_back('f');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"F");break;
				case ALLEGRO_KEY_G:file.push_back('g');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"G");break;
				case ALLEGRO_KEY_H:file.push_back('h');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"H");break;
				case ALLEGRO_KEY_J:file.push_back('j');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"J");break;
				case ALLEGRO_KEY_K:file.push_back('k');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"K");break;
				case ALLEGRO_KEY_L:file.push_back('l');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"L");break;
				case ALLEGRO_KEY_Z:file.push_back('z');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"Z");break;
				case ALLEGRO_KEY_X:file.push_back('x');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"X");break;
				case ALLEGRO_KEY_C:file.push_back('c');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"C");break;
				case ALLEGRO_KEY_V:file.push_back('v');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"V");break;
				case ALLEGRO_KEY_B:file.push_back('b');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"B");break;
				case ALLEGRO_KEY_N:file.push_back('n');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"N");break;
				case ALLEGRO_KEY_M:file.push_back('m');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"M");break;
				case ALLEGRO_KEY_1:file.push_back('1');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"1");break;
				case ALLEGRO_KEY_2:file.push_back('2');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"2");break;
				case ALLEGRO_KEY_3:file.push_back('3');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"3");break;
				case ALLEGRO_KEY_4:file.push_back('4');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"4");break;
				case ALLEGRO_KEY_5:file.push_back('5');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"5");break;
				case ALLEGRO_KEY_6:file.push_back('6');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"6");break;
				case ALLEGRO_KEY_7:file.push_back('7');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"7");break;
				case ALLEGRO_KEY_8:file.push_back('8');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"8");break;
				case ALLEGRO_KEY_9:file.push_back('9');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"9");break;
				case ALLEGRO_KEY_0:file.push_back('0');al_draw_text(font_24,al_map_rgb(155,200,120),x+=20,130,ALLEGRO_ALIGN_CENTRE,"0");break;
				case ALLEGRO_KEY_ENTER:quit=true;break;
				}
				al_flip_display();	
				}

			}
	return file;
}
