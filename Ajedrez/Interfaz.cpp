//Universidad Nacional 
//Proyecto #1 de Programacion 2
//Desarrollado por Andrey Arguedas Espinoza y Derian Sibaja Chavarria
#include "Interfaz.h"

//Clase encargada de mostrar toda la parte grafica

Interfaz::Interfaz(void)
{
}

Interfaz::~Interfaz(void)
{
}

void Interfaz::musica(){
	ALLEGRO_SAMPLE * song = al_load_sample("Medieval.wav");
	al_reserve_samples(1);
	ALLEGRO_SAMPLE_INSTANCE * songInstance = al_create_sample_instance(song);
	al_set_sample_instance_playmode(songInstance,ALLEGRO_PLAYMODE_ONCE);
	al_attach_sample_instance_to_mixer(songInstance,al_get_default_mixer());
	al_play_sample_instance(songInstance);
}


void Interfaz::imagPiezas()  //Muestra piezas en codigo ASCII
{
	ALLEGRO_BITMAP * warrior = al_load_bitmap("Warrior.png");
	limpiarPantalla();
	al_draw_bitmap(warrior,35,230,NULL);
	al_flip_display();
}



void Interfaz::titulo(){
ALLEGRO_FONT * font = al_load_font("Prince Valiant.ttf",48,NULL);
ALLEGRO_FONT * font_24 = al_load_font("Prince Valiant.ttf",24,NULL);
al_clear_to_color(al_map_rgb(0,0,0));
al_draw_text(font,al_map_rgb(155,200,120),240,40,ALLEGRO_ALIGN_CENTRE,"MEDIEVAL CHESS");
al_draw_text(font,al_map_rgb(155,200,120),240,110,ALLEGRO_ALIGN_CENTRE,"ANDREY ARGUEDAS");
al_draw_text(font,al_map_rgb(155,200,120),240,170,ALLEGRO_ALIGN_CENTRE,"DERIAN SIBAJA");
ALLEGRO_BITMAP * shield = al_load_bitmap("Shield.png");
al_draw_bitmap(shield,0,230,NULL);
al_draw_text(font_24,al_map_rgb(155,200,120),470,340,ALLEGRO_ALIGN_RIGHT,"PRESS ENTER TO START");
al_draw_text(font_24,al_map_rgb(155,200,120),470,380,ALLEGRO_ALIGN_RIGHT,"PRESS SPACE TO LOAD MATCH");
al_flip_display();
}


void Interfaz::limpiarPantalla(){ 
	al_clear_to_color(al_map_rgb(0,0,0));
}

void Interfaz::impTablero(Tablero<Pieza>*t)
{
	ALLEGRO_BITMAP * tablero = al_load_bitmap("tablero.jpg");
	al_draw_bitmap(tablero,0,0,NULL);
	al_flip_display();
		for(int i=0;i<t->getFila();i++){
				for(int j=0;j<t->getColuma();j++){
					if(t->obtenerPieza(i,j)){
						t->obtenerPieza(i,j)->toString();//Muestra la pieza
					}
				}
			}
}


void Interfaz::datoInvalido(string s)
{
	ALLEGRO_FONT * font_24 = al_load_font("Black.ttf",48,NULL);
	al_draw_text(font_24,al_map_rgb(0,0,0),230,190,ALLEGRO_ALIGN_CENTRE,"INVALID PIECE");
	al_flip_display();
	al_rest(2.4);
}

void Interfaz::whoStarts(bool c){
	ALLEGRO_FONT * font_48 = al_load_font("Black.ttf",48,NULL);
	limpiarPantalla();
	if(c){
	al_draw_text(font_48,al_map_rgb(212,175,55),230,210,ALLEGRO_ALIGN_CENTRE,"GOLD STARTS");
	al_flip_display();
	al_rest(0.9);
	}
	else{
	al_draw_text(font_48,al_map_rgb(212,175,55),230,210,ALLEGRO_ALIGN_CENTRE,"SILVER STARTS");
	al_flip_display();
	al_rest(0.9);
	}
	al_destroy_font(font_48);
	limpiarPantalla();
}

void Interfaz::pedirNombrePartida(){
	
	ALLEGRO_FONT * font_24 = al_load_font("Prince Valiant.ttf",24,NULL);
	al_draw_text(font_24,al_map_rgb(155,200,120),230,30,ALLEGRO_ALIGN_CENTRE,"TYPE A NAME FOR THIS MATCH");
	al_draw_text(font_24,al_map_rgb(155,200,120),230,200,ALLEGRO_ALIGN_CENTRE,"PRESS ENTER TO START");
	al_flip_display();
}

void Interfaz::recuperarPartida(){
	ALLEGRO_FONT * font_24 = al_load_font("Prince Valiant.ttf",24,NULL);
	al_draw_text(font_24,al_map_rgb(155,200,120),240,30,ALLEGRO_ALIGN_CENTRE,"WHICH MATCH WOULD YOU LIKE TO LOAD");
	al_draw_text(font_24,al_map_rgb(155,200,120),230,200,ALLEGRO_ALIGN_CENTRE,"PRESS ENTER TO START");
	al_flip_display();
}

void Interfaz::errorCargarPartida(string arc){
	limpiarPantalla();
	imagPiezas();
	ALLEGRO_FONT * font_24 = al_load_font("BLACK.ttf",36,NULL);
	al_draw_text(font_24,al_map_rgb(155,200,120),240,120,ALLEGRO_ALIGN_CENTRE,"THAT MATCH");
	al_draw_text(font_24,al_map_rgb(155,200,120),230,160,ALLEGRO_ALIGN_CENTRE,"DOES NOT EXIST");
	al_flip_display();
	al_rest(2.4);
	al_destroy_font(font_24);
}

void Interfaz::jaque(bool c)
{
	ALLEGRO_FONT * font_24 = al_load_font("Black.ttf",48,NULL);
	al_draw_text(font_24,al_map_rgb(0,0,0),230,190,ALLEGRO_ALIGN_CENTRE,"CHECK");
	al_flip_display();
	al_rest(2.4);
	al_destroy_font(font_24);
}

void Interfaz::jaqueMate(bool c)
{

	ALLEGRO_FONT * font_24 = al_load_font("Black.ttf",48,NULL);
	al_draw_text(font_24,al_map_rgb(0,0,0),230,190,ALLEGRO_ALIGN_CENTRE,"CHECK MATE");
	al_flip_display();
	if(c){
	ALLEGRO_FONT * font_24 = al_load_font("Black.ttf",48,NULL);
	al_draw_text(font_24,al_map_rgb(0,0,0),230,250,ALLEGRO_ALIGN_CENTRE,"SILVER WINS");
	al_flip_display();
	al_rest(2.4);
	al_destroy_font(font_24);
	}
	else{
	ALLEGRO_FONT * font_24 = al_load_font("Black.ttf",48,NULL);
	al_draw_text(font_24,al_map_rgb(0,0,0),230,250,ALLEGRO_ALIGN_CENTRE,"GOLD WINS");
	al_flip_display();
	al_rest(2.4);
	al_destroy_font(font_24);
	}
}