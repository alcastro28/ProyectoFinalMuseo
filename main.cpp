#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include "stdafx.h"
#include <stdlib.h>
#include <windows.h>
#include "glm.h"
#include "Texture.h"
#include "Camera.h"
#include <iomanip>
#include "texture2.h"
#include "timer.h"
#include "md2.h"
#include <mmsystem.h>
using namespace std;
GLUquadricObj* p = gluNewQuadric();
Camera g_camera;
GLMmodel* Cielo = NULL;
GLMmodel* Suelo = NULL;
GLMmodel* PisoMuseo = NULL;
GLMmodel* ParedesMuseo = NULL;
GLMmodel* TechoMuseo = NULL;
GLMmodel* MesasMuseoNazca = NULL;
GLMmodel* MesasMuseoMoche = NULL;
GLMmodel* MesasMuseoChimu = NULL;
GLMmodel* EstatuasExterior = NULL;
GLMmodel* CuadrosPrincipales = NULL;
GLMmodel* CuadrosSecundarios = NULL;
GLMmodel* CuadrosTercearios = NULL;
GLMmodel* PlanoCuadro1 = NULL;
GLMmodel* PlanoCuadro2 = NULL;
GLMmodel* PlanoCuadro3 = NULL;
GLMmodel* PlanoCuadro4 = NULL;
GLMmodel* PlanoCuadro5 = NULL;
GLMmodel* Lampara1 = NULL;
GLMmodel* Lampara2 = NULL;
GLMmodel* Lampara3 = NULL;
GLMmodel* Huaco1MocheRep1 = NULL;
GLMmodel* Huaco1MocheRep2 = NULL;
GLMmodel* Huaco1MocheRep3 = NULL;
GLMmodel* Huaco1MocheRep4 = NULL;
GLMmodel* MarcoPuertaPrincipal = NULL;
GLMmodel* PuertaPrincipalDerecha = NULL;
GLMmodel* PuertaPrincipalIzquierda = NULL;
GLMmodel* MarcoPuertaMoche = NULL;
GLMmodel* PuertaMoche = NULL;
GLMmodel* MarcoPuertaChimu = NULL;
GLMmodel* PuertaChimu = NULL;
GLMmodel* GuiaNazca1 = NULL;
GLMmodel* GuiaNazca2 = NULL;
GLMmodel* GuiaChimu1 = NULL;
GLMmodel* GuiaChimu2 = NULL;
GLMmodel* GuiaMoche1 = NULL;
GLMmodel* GuiaMoche2 = NULL;
GLuint	texture;
Texture	PisoCielo[2];
Texture	Museo[3];
Texture	Cuadros[6];
Texture	Lamparas[2];
Texture	Puerta[2];
Texture	Moche[10];
Texture	Nazca[2];
Texture	Chimu[2];
Texture	Guia[2];
int g_viewport_width = 700;
int g_viewport_height = 500;
float camaraX = 5;
float camaraY = 20;
float camaraZ = -15;
double Puerta1 = 0;
double Puerta2 = 0;
double Puerta4 = 0;
double Puerta3 = 0;
double TempCol = 5.8;
bool MovimientoPuertaNazca = false;
bool MovimientoPuertaMohe = false;
bool MovimientoPuertaChimu = false;
bool AnimacionGuia = false;
bool ActivarTextura = false;
bool ActivarObj = false;
bool ActivarExterior = false;
bool g_key[256];
bool g_shift_down = false;
bool g_fps_mode = false;
bool g_mouse_left_down = false;
bool g_mouse_right_down = false;
bool rapido=false;
const float g_translation_speed = 1;
const float g_rotation_speed = M_PI/180*1;
static float ypoz = 0, zpoz = 0;
bool			bTextured	= true;
bool			bLighGL		= false;
bool			bAnimated	= true;
float			angle		= 0.0;
extern float	g_angle;
void redimencionar( int width, int height ){
	if( height == 0 )
		height = 1;
	glViewport( 0, 0, width, height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 45, (float)width/(float)height, 0.1, 10000 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}
bool CargarTgaPisoCielo(){
	int i;
	if (LoadTGA(&PisoCielo[0], "mods/TGA/CieloGod.tga") &&
        LoadTGA(&PisoCielo[1], "mods/TGA/grass.tga")
        ){
		for (i = 0; i<2; i++){
			glGenTextures(1, &PisoCielo[i].texID);
			glBindTexture(GL_TEXTURE_2D, PisoCielo[i].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, PisoCielo[i].bpp / 8, PisoCielo[i].width,
            PisoCielo[i].height, 0, PisoCielo[i].type, GL_UNSIGNED_BYTE, PisoCielo[i].imageData);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
			if (PisoCielo[i].imageData)
			{
				free(PisoCielo[i].imageData);
			}
		}
		return true;
	}
	else{
		return false;
	}
}
bool CargarTgaMuseo(){
	int i;
	if (LoadTGA(&Museo[0], "mods/TGA/piso.tga") &&
        LoadTGA(&Museo[1], "mods/TGA/MaderaClara.tga") &&
        LoadTGA(&Museo[2], "mods/TGA/TPierdra.tga")
        ){
		for (i = 0; i<3; i++){
			glGenTextures(1, &Museo[i].texID);
			glBindTexture(GL_TEXTURE_2D, Museo[i].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, Museo[i].bpp / 8, Museo[i].width,
            Museo[i].height, 0, Museo[i].type, GL_UNSIGNED_BYTE, Museo[i].imageData);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
			if (Museo[i].imageData)
			{
				free(Museo[i].imageData);
			}
		}
		return true;
	}
	else{
		return false;
	}
}
bool CargarTgaLamparas(){
	int i;
	if (LoadTGA(&Lamparas[0], "mods/TGA/MetalDorado.tga")
        ){
		for (i = 0; i<2; i++){
			glGenTextures(1, &Lamparas[i].texID);
			glBindTexture(GL_TEXTURE_2D, Lamparas[i].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, Lamparas[i].bpp / 8, Lamparas[i].width,
            Lamparas[i].height, 0, Lamparas[i].type, GL_UNSIGNED_BYTE, Lamparas[i].imageData);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
			if (Lamparas[i].imageData)
			{
				free(Lamparas[i].imageData);
			}
		}
		return true;
	}
	else{
		return false;
	}
}
bool CargarTgaHuacosMoche(){
	int i;
	if (LoadTGA(&Moche[0], "mods/TGA/Huaco3moche.tga")
        ){
		for (i = 0; i<2; i++){
			glGenTextures(1, &Moche[i].texID);
			glBindTexture(GL_TEXTURE_2D, Moche[i].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, Moche[i].bpp / 8, Moche[i].width,
            Moche[i].height, 0, Moche[i].type, GL_UNSIGNED_BYTE, Moche[i].imageData);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
			if (Moche[i].imageData)
			{
				free(Moche[i].imageData);
			}
		}
		return true;
	}
	else{
		return false;
	}
}
bool CargarTgaHuacosNazca(){
	int i;
	if (LoadTGA(&Nazca[0], "mods/TGA/Cultura_Nazca2.0.tga")
        ){
		for (i = 0; i<2; i++){
			glGenTextures(1, &Nazca[i].texID);
			glBindTexture(GL_TEXTURE_2D, Nazca[i].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, Nazca[i].bpp / 8, Nazca[i].width,
            Nazca[i].height, 0, Nazca[i].type, GL_UNSIGNED_BYTE, Nazca[i].imageData);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
			if (Nazca[i].imageData)
			{
				free(Nazca[i].imageData);
			}
		}
		return true;
	}
	else{
		return false;
	}
}
bool CargarTgaHuacosChimu(){
	int i;
	if (LoadTGA(&Chimu[0], "mods/TGA/IMG_A.tga")
        ){
		for (i = 0; i<2; i++){
			glGenTextures(1, &Chimu[i].texID);
			glBindTexture(GL_TEXTURE_2D, Chimu[i].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, Chimu[i].bpp / 8, Chimu[i].width,
            Chimu[i].height, 0, Chimu[i].type, GL_UNSIGNED_BYTE, Chimu[i].imageData);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
			if (Chimu[i].imageData)
			{
				free(Chimu[i].imageData);
			}
		}
		return true;
	}
	else{
		return false;
	}
}
bool CargarTgaCuadros(){
	int i;
	if (LoadTGA(&Cuadros[0], "mods/TGA/MapaMoche.tga") &&
        LoadTGA(&Cuadros[1], "mods/TGA/Chimu.tga") &&
        LoadTGA(&Cuadros[2], "mods/TGA/culturanazca.tga") &&
        LoadTGA(&Cuadros[3], "mods/TGA/LineadeNazca.tga") &&
        LoadTGA(&Cuadros[4], "mods/TGA/DescripcionNazca.tga")
        ){
		for (i = 0; i<5; i++){
			glGenTextures(1, &Cuadros[i].texID);
			glBindTexture(GL_TEXTURE_2D, Cuadros[i].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, Cuadros[i].bpp / 8, Cuadros[i].width,
            Cuadros[i].height, 0, Cuadros[i].type, GL_UNSIGNED_BYTE, Cuadros[i].imageData);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
			if (Cuadros[i].imageData)
			{
				free(Cuadros[i].imageData);
			}
		}
		return true;
	}
	else{
		return false;
	}
}
bool CargarTgaPuertas(){
	int i;
	if (LoadTGA(&Puerta[0], "mods/TGA/Puerta.tga")
        ){
		for (i = 0; i<2; i++){
			glGenTextures(1, &Puerta[i].texID);
			glBindTexture(GL_TEXTURE_2D, Puerta[i].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, Puerta[i].bpp / 8, Puerta[i].width,
            Puerta[i].height, 0, Puerta[i].type, GL_UNSIGNED_BYTE, Puerta[i].imageData);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
			if (Puerta[i].imageData)
			{
				free(Puerta[i].imageData);
			}
		}
		return true;
	}
	else{
		return false;
	}
}
bool CargarTgaFuia(){
	int i;
	if (LoadTGA(&Guia[0], "mods/TGA/Guias.tga")
        ){
		for (i = 0; i<2; i++){
			glGenTextures(1, &Guia[i].texID);
			glBindTexture(GL_TEXTURE_2D, Guia[i].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, Guia[i].bpp / 8, Guia[i].width,
            Guia[i].height, 0, Guia[i].type, GL_UNSIGNED_BYTE, Guia[i].imageData);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
			if (Guia[i].imageData)
			{
				free(Guia[i].imageData);
			}
		}
		return true;
	}
	else{
		return false;
	}
}
void inicializar() {
    glClearColor(0, 0, 0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    gluQuadricDrawStyle(p, GLU_FILL);
}
void activarLuz() {
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
}
void desactivarLuz() {
	glDisable(GL_LIGHT0);
	glDisable(GL_NORMALIZE);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
}
void iniciarlizarLuces() {
	const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat light_position[] = { camaraX, camaraY, camaraZ, 0.0f };
	const GLfloat mat_ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	const GLfloat mat_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat high_shininess[] = { 100.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}
/***Cielo  y Piso***/
void TCielo(){
    glBindTexture(GL_TEXTURE_2D, PisoCielo[0].texID);
	glmDraw(Cielo, GLM_SMOOTH | GLM_TEXTURE);
}
void TSuelo(){
    glBindTexture(GL_TEXTURE_2D, PisoCielo[1].texID);
	glmDraw(Suelo, GLM_SMOOTH | GLM_TEXTURE);
}
/***   Museo   ***/
void TMuseo(){
    glBindTexture(GL_TEXTURE_2D, Museo[2].texID);
    glmDraw(PisoMuseo, GLM_SMOOTH | GLM_TEXTURE);
    glmDraw(ParedesMuseo, GLM_SMOOTH | GLM_TEXTURE);
    glmDraw(TechoMuseo, GLM_SMOOTH | GLM_TEXTURE);
}
/***   Esculturas    ***/
void TEstatuasExterior(){
    glBindTexture(GL_TEXTURE_2D, Museo[0].texID);
	glmDraw(EstatuasExterior, GLM_SMOOTH | GLM_TEXTURE);
}
/*** Puerta Nazca   ***/
void TPuertaPrincipalMarco(){
    glBindTexture(GL_TEXTURE_2D, Puerta[0].texID);
	glmDraw(MarcoPuertaPrincipal, GLM_SMOOTH | GLM_TEXTURE);
}
void TPuertaPrincipalPuertaIzquierda(){
    glTranslated(0,0,Puerta1);
    glBindTexture(GL_TEXTURE_2D, Puerta[0].texID);
	glmDraw(PuertaPrincipalIzquierda, GLM_SMOOTH | GLM_TEXTURE);
}
void TPuertaPrincipalPuertaDerecha(){
    glTranslated(0,0,Puerta2);
    glBindTexture(GL_TEXTURE_2D, Puerta[0].texID);
	glmDraw(PuertaPrincipalDerecha, GLM_SMOOTH | GLM_TEXTURE);
}
/*** Puerta Moche   ***/
void TMarcoPuertaMoche(){
    glBindTexture(GL_TEXTURE_2D, Puerta[0].texID);
	glmDraw(MarcoPuertaMoche, GLM_SMOOTH | GLM_TEXTURE);
}
void TPuertaMoche(){
    glTranslated(Puerta3,0,0);
    glBindTexture(GL_TEXTURE_2D, Puerta[0].texID);
	glmDraw(PuertaMoche, GLM_SMOOTH | GLM_TEXTURE);
}
/*** Puerta Chimu   ***/
void TMarcoPuertaChimu(){
    glBindTexture(GL_TEXTURE_2D, Puerta[0].texID);
	glmDraw(MarcoPuertaChimu, GLM_SMOOTH | GLM_TEXTURE);
}
void TPuertaChimu(){
    glTranslated(Puerta4,0,0);
    glBindTexture(GL_TEXTURE_2D, Puerta[0].texID);
	glmDraw(PuertaChimu, GLM_SMOOTH | GLM_TEXTURE);
}
/*** Cuarto Moche  ***/
void TCuartoMoche(){
    if(MovimientoPuertaMohe ==true){
        glBindTexture(GL_TEXTURE_2D, Moche[0].texID);
        glmDraw(Huaco1MocheRep1, GLM_SMOOTH | GLM_TEXTURE);
    }
    if(MovimientoPuertaMohe ==true){
        glBindTexture(GL_TEXTURE_2D, Museo[1].texID);
        glmDraw(MesasMuseoMoche, GLM_SMOOTH | GLM_TEXTURE);
    }
    if(MovimientoPuertaMohe ==true){
        glBindTexture(GL_TEXTURE_2D, Lamparas[0].texID);
        glmDraw(Lampara1, GLM_SMOOTH | GLM_TEXTURE);
    }
    if(MovimientoPuertaMohe ==true){
        glBindTexture(GL_TEXTURE_2D, Museo[1].texID);
        glmDraw(CuadrosPrincipales, GLM_SMOOTH | GLM_TEXTURE);
    }
    if(MovimientoPuertaMohe ==true){
        glBindTexture(GL_TEXTURE_2D, Cuadros[0].texID);
        glmDraw(PlanoCuadro1, GLM_SMOOTH | GLM_TEXTURE);
    }
        /***ColisionPuertaMoche***/
    if(MovimientoPuertaMohe ==true){
               g_camera.colision(105,195,41, 51,0, 40);
    }
        if(MovimientoPuertaMohe ==false){
                g_camera.colision(105,224,41,51,0, 40);
    }
    /***Guia***/
    if(MovimientoPuertaMohe ==true){
        if(AnimacionGuia == false){
            glBindTexture(GL_TEXTURE_2D, Guia[0].texID);
            glmDraw(GuiaMoche1, GLM_SMOOTH | GLM_TEXTURE);
        }
        if(AnimacionGuia == true){
            glBindTexture(GL_TEXTURE_2D, Guia[0].texID);
            glmDraw(GuiaMoche2, GLM_SMOOTH | GLM_TEXTURE);
        }
    }
}
/*** Cuarto Chimu ***/
void TCuartoChimu(){
    if(MovimientoPuertaChimu ==true){
        glBindTexture(GL_TEXTURE_2D, Lamparas[0].texID);
        glmDraw(Lampara2, GLM_SMOOTH | GLM_TEXTURE);
    }
    if(MovimientoPuertaChimu ==true){
        glBindTexture(GL_TEXTURE_2D, Museo[1].texID);
        glmDraw(CuadrosSecundarios, GLM_SMOOTH | GLM_TEXTURE);
    }
    if(MovimientoPuertaChimu ==true){
        glBindTexture(GL_TEXTURE_2D, Cuadros[1].texID);
        glmDraw(PlanoCuadro2, GLM_SMOOTH | GLM_TEXTURE);
    }
    if(MovimientoPuertaChimu ==true){
        glBindTexture(GL_TEXTURE_2D, Museo[1].texID);
        glmDraw(MesasMuseoChimu, GLM_SMOOTH | GLM_TEXTURE);
    }
    if(MovimientoPuertaChimu ==true){
        glBindTexture(GL_TEXTURE_2D, Chimu[0].texID);
        glmDraw(Huaco1MocheRep4, GLM_SMOOTH | GLM_TEXTURE);
    }
    /***ColisionPuertaChimu***/
    if(MovimientoPuertaChimu ==true){
               g_camera.colision(105,189,-32, -20,0, 40);
    }
        if(MovimientoPuertaChimu ==false){
                g_camera.colision(105,226,-32, -20,0, 40);
    }

    /***Guia***/
    if(MovimientoPuertaChimu ==true){
        if(AnimacionGuia == false){
            glBindTexture(GL_TEXTURE_2D, Guia[0].texID);
            glmDraw(GuiaChimu1, GLM_SMOOTH | GLM_TEXTURE);
        }
        if(AnimacionGuia == true){
            glBindTexture(GL_TEXTURE_2D, Guia[0].texID);
            glmDraw(GuiaChimu2, GLM_SMOOTH | GLM_TEXTURE);
        }
    }
}
void TCuartoNazca(){
    if(MovimientoPuertaNazca ==true){
        glBindTexture(GL_TEXTURE_2D, Cuadros[4].texID);
        glmDraw(PlanoCuadro3, GLM_SMOOTH | GLM_TEXTURE);
    }
    if(MovimientoPuertaNazca ==true){
        glBindTexture(GL_TEXTURE_2D, Cuadros[3].texID);
        glmDraw(PlanoCuadro4, GLM_SMOOTH | GLM_TEXTURE);
    }
    if(MovimientoPuertaNazca ==true){
        glBindTexture(GL_TEXTURE_2D, Cuadros[2].texID);
        glmDraw(PlanoCuadro5, GLM_SMOOTH | GLM_TEXTURE);
    }
    if(MovimientoPuertaNazca ==true){
        glBindTexture(GL_TEXTURE_2D, Museo[1].texID);
        glmDraw(CuadrosTercearios, GLM_SMOOTH | GLM_TEXTURE);
    }
    if(MovimientoPuertaNazca ==true){
        glBindTexture(GL_TEXTURE_2D, Museo[1].texID);
        glmDraw(MesasMuseoNazca, GLM_SMOOTH | GLM_TEXTURE);
    }
    if(MovimientoPuertaNazca ==true){
        glBindTexture(GL_TEXTURE_2D, Lamparas[0].texID);
        glmDraw(Lampara3, GLM_SMOOTH | GLM_TEXTURE);
    }
    if(MovimientoPuertaNazca ==true){
        glBindTexture(GL_TEXTURE_2D, Nazca[0].texID);
        glmDraw(Huaco1MocheRep3, GLM_SMOOTH | GLM_TEXTURE);
    }
                /***ColisionPuertaNazca***/
    if(MovimientoPuertaNazca ==true){
               g_camera.colision(226,237,-80, -10,0, 40);
    }
        if(MovimientoPuertaNazca ==false){
                g_camera.colision(226,237,-80, 42,0, 40);
    }
    /**Guia**/
    if(MovimientoPuertaNazca ==true){
        if(AnimacionGuia == false){
            glBindTexture(GL_TEXTURE_2D, Guia[0].texID);
            glmDraw(GuiaNazca1, GLM_SMOOTH | GLM_TEXTURE);
        }
        if(AnimacionGuia == true){
            glBindTexture(GL_TEXTURE_2D, Guia[0].texID);
            glmDraw(GuiaNazca2, GLM_SMOOTH | GLM_TEXTURE);
        }
    }
}

void ObjPisoCielo(){
    Cielo                    = glmReadOBJ("mods/Cielo/Cielo.obj");
    Suelo                    = glmReadOBJ("mods/PisoMundo/PisoMundo.obj");
}
void ObjMuseo(){
    PisoMuseo                = glmReadOBJ("mods/PisoMuseo/PisoMuseo.obj");
    ParedesMuseo             = glmReadOBJ("mods/CuerpoMuseo/CuerpoMuseo.obj");
    TechoMuseo               = glmReadOBJ("mods/TechoMuseo/TechoMuseo.obj");
    MesasMuseoNazca          = glmReadOBJ("mods/MesasMuseo/MesaNazca.obj");
    MesasMuseoMoche          = glmReadOBJ("mods/MesasMuseo/MesaMoche.obj");
    MesasMuseoChimu          = glmReadOBJ("mods/MesasMuseo/MesaChimu.obj");
    EstatuasExterior         = glmReadOBJ("mods/EstatuasExterior/EstatuasExterior.obj");
}
void ObjCuadros(){
    CuadrosPrincipales       = glmReadOBJ("mods/CuadrosPrincipales/CuadrosPrincipales.obj");
    CuadrosSecundarios       = glmReadOBJ("mods/CuadrosSecundarios/CuadrosSecundarrios.obj");
    CuadrosTercearios        = glmReadOBJ("mods/CuadrosTercearios/CuadrosTercearios.obj");
}
void ObjPlanos(){
    PlanoCuadro1             = glmReadOBJ("mods/PlanosCuadros/Plano1.obj");
    PlanoCuadro2             = glmReadOBJ("mods/PlanosCuadros/Plano2.obj");
    PlanoCuadro3             = glmReadOBJ("mods/PlanosCuadros/Plano3.obj");
    PlanoCuadro4             = glmReadOBJ("mods/PlanosCuadros/Plano4.obj");
    PlanoCuadro5             = glmReadOBJ("mods/PlanosCuadros/Plano5.obj");
}
void ObjLamparas(){
    Lampara1                 = glmReadOBJ("mods/Lampara1/Lamparas1.obj");
    Lampara2                 = glmReadOBJ("mods/Lampara2/Lamparas1.obj");
    Lampara3                 = glmReadOBJ("mods/Lampara3/Lamparas3.obj");
}
void ObjHuacoMoche(){
    Huaco1MocheRep1          = glmReadOBJ("mods/Huaco1/HuacosR1.obj");
}
void ObjHuacosNazca(){
    Huaco1MocheRep3          = glmReadOBJ("mods/Huaco2/CulturaNazca.obj");
}
void ObjHuacosChimu(){
    Huaco1MocheRep4          = glmReadOBJ("mods/Huaco3/HuacoChimu.obj");
}
void ObjPuertas(){
    MarcoPuertaPrincipal     = glmReadOBJ("mods/Puertas/PuertaPrincipal/MarcoPrincipal.obj");
    PuertaPrincipalDerecha   = glmReadOBJ("mods/Puertas/PuertaPrincipal/PuertaDerechaP.obj");
    PuertaPrincipalIzquierda = glmReadOBJ("mods/Puertas/PuertaPrincipal/PuertaIzquierdaP.obj");
    MarcoPuertaMoche         = glmReadOBJ("mods/Puertas/PuertaMoche/MarcoPuertaMoche.obj");
    PuertaMoche              = glmReadOBJ("mods/Puertas/PuertaMoche/PuertaMoche.obj");
    MarcoPuertaChimu         = glmReadOBJ("mods/Puertas/PuertaChimu/MarcoPuertaChimu.obj");
    PuertaChimu              = glmReadOBJ("mods/Puertas/PuertaChimu/PuertaChimu.obj");
}
void ObjGuia(){
    GuiaNazca1                = glmReadOBJ("mods/Guia/GuiaNazca/GuiaNazca1.obj");
    GuiaNazca2                = glmReadOBJ("mods/Guia/GuiaNazca/GuiaNazca2.obj");
    GuiaChimu1                = glmReadOBJ("mods/Guia/GuiaChimu/GuiaChimu1.obj");
    GuiaChimu2                = glmReadOBJ("mods/Guia/GuiaChimu/GuiaChimu2.obj");
    GuiaMoche1                = glmReadOBJ("mods/Guia/GuiaMoche/GuiaMoche1.obj");
    GuiaMoche2                = glmReadOBJ("mods/Guia/GuiaMoche/GuiaMoche2.obj");
}
void CargaMuseo(){
    TMuseo();
}
void CargaCieloPiso(){
    TCielo();
    TSuelo();
}
void CargaEstatuas(){
    TEstatuasExterior();
}
void CargaPuerta(){
    TPuertaPrincipalMarco();
    TMarcoPuertaMoche();
    TMarcoPuertaChimu();
    /*** Nazca ***/
    glPushMatrix();
        TPuertaPrincipalPuertaIzquierda();
    glPopMatrix();
    glPushMatrix();
        TPuertaPrincipalPuertaDerecha();
    glPopMatrix();
    /*** Moche ***/
    glPushMatrix();
        TPuertaMoche();
    glPopMatrix();
    /*** Chimu ***/
    glPushMatrix();
        TPuertaChimu();
    glPopMatrix();
}
void graficar() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	g_camera.Refresh();
	glEnable(GL_LIGHTING);
    CargaCieloPiso();
    CargaMuseo();
    CargaEstatuas();
    TCuartoMoche();
    TCuartoChimu();
    TCuartoNazca();
    CargaPuerta();
    //CargarOgro();
	glutSwapBuffers();
}
void animate(int i){
	ypoz += 0.5;
	if (ypoz>360) ypoz = 0;
	glutPostRedisplay();
	glutTimerFunc(2, animate, 1);
}
void Keyboard(unsigned char key, int x, int y){
    if(key == 27) {
        exit(0);
    }
    if(key == ' ') {
        g_fps_mode = !g_fps_mode;

        if(g_fps_mode) {
            glutSetCursor(GLUT_CURSOR_NONE);
            glutWarpPointer(g_viewport_width/2, g_viewport_height/2);
            std::cout<<"Suspender";
        }
        else {
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        }
    }
    if(glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
        g_shift_down = true;
    }
    else {
        g_shift_down = false;
    }
    g_key[key] = true;

    switch(key) {
        case 'e':
            MovimientoPuertaNazca = !MovimientoPuertaNazca;
            break;
        case 'E':
            MovimientoPuertaNazca = !MovimientoPuertaNazca;
            break;
        case 'r':
            MovimientoPuertaMohe = !MovimientoPuertaMohe;
            break;
        case 'R':
            MovimientoPuertaMohe = !MovimientoPuertaMohe;
            break;
        case 'q':
            MovimientoPuertaChimu = !MovimientoPuertaChimu;
            break;
        case 'Q':
            MovimientoPuertaChimu = !MovimientoPuertaChimu;
            break;
        case 'm':
            AnimacionGuia = !AnimacionGuia;
            break;
        case 'M':
            AnimacionGuia = !AnimacionGuia;
            break;
    }
}
void KeyboardUp(unsigned char key, int x, int y){
    g_key[key] = false;
}
void Idle(){
    graficar();
}
void AnimPuertasNazca(){
    if( Puerta1 >= -12 && MovimientoPuertaNazca ==true){
    Puerta1 -= 1.5;
    Puerta2 += 1.5;
    }
    if( Puerta1 <= 0    &&  MovimientoPuertaNazca ==false){
    Puerta1 += 1.5;
    Puerta2 -= 1.5;
    }
}
void AnimPuertasMoche(){
    if( Puerta3 >= -20 && MovimientoPuertaMohe ==true){
    Puerta3 -= 1.5;
     }
    if( Puerta3 <= 0    &&  MovimientoPuertaMohe ==false){
    Puerta3 += 1.5;
    }
}
void AnimPuertasChimu(){
    if( Puerta4 >= -20 && MovimientoPuertaChimu ==true){
    Puerta4 -= 1.5;
     }
    if( Puerta4 <= 0    &&  MovimientoPuertaChimu ==false){
    Puerta4 += 1.5;
    }
}
void MusicaMoche(){
    bool MusicaMocheP=PlaySound(TEXT("Sonidos/CulturaMoche.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
    if(MusicaMocheP==false){
        cout<<"Error"<<endl;
    }else{
        cout<<"Reproduciendo"<<endl;
    }
}
void MusicaChimu(){
    bool MusicaChimuP=PlaySound(TEXT("Sonidos/Chimu.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
    if(MusicaChimuP==false){
        cout<<"Error"<<endl;
    }else{
        cout<<"Reproduciendo"<<endl;
    }
}
void MusicaNazca(){
    bool MusicaNazcaP=PlaySound(TEXT("Sonidos/CulturaNazca.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
    if(MusicaNazcaP==false){
        cout<<"Error"<<endl;
    }else{
        cout<<"Reproduciendo"<<endl;
    }
}
void DesactivarMusica(){
    PlaySound(NULL, NULL, SND_ASYNC);
}
void Timer(int value){
    if(g_fps_mode) {
        if(g_key['w'] || g_key['W']) {
            g_camera.Move(g_translation_speed);
        }
        else if(g_key['s'] || g_key['S']) {
            g_camera.Move(-g_translation_speed);
        }
        else if(g_key['a'] || g_key['A']) {
            g_camera.Strafe(g_translation_speed);
        }
        else if(g_key['d'] || g_key['D']) {
            g_camera.Strafe(-g_translation_speed);
        }
        else if(g_mouse_left_down) {
            g_camera.Fly(-g_translation_speed);
        }
        else if(g_mouse_right_down) {
            g_camera.Fly(g_translation_speed);
        }
        /***Modo rapido***/
        if(g_key['8']) {
            g_camera.Move(g_translation_speed+4);
        }
        else if(g_key['5']) {
            g_camera.Move(-g_translation_speed-4);
        }
        else if(g_key['4']) {
            g_camera.Strafe(g_translation_speed+4);
        }
        else if(g_key['6']) {
            g_camera.Strafe(-g_translation_speed-4);
        }
        /** Musica **/
        else if(g_key['1']) {
            MusicaMoche();
        }
        else if(g_key['2']) {
            MusicaChimu();
        }
        else if(g_key['3']) {
            MusicaNazca();
        }
        /** Luces **/
        else if(g_key['0']) {
            DesactivarMusica();
        }
        else if(g_key['7']) {
             activarLuz();
        }
        else if(g_key['9']) {
             desactivarLuz();
        }
        /**Linterna**/
        else if(g_key['o']) {

        }
        else if(g_key['p']) {

        }
    }
    AnimPuertasNazca();
    AnimPuertasMoche();
    AnimPuertasChimu();
    glutTimerFunc(1, Timer, 0);
}
void Mouse(int button, int state, int x, int y){
    if(state == GLUT_DOWN) {
        if(button == GLUT_LEFT_BUTTON) {
            g_mouse_left_down = true;
        }
        else if(button == GLUT_RIGHT_BUTTON) {
            g_mouse_right_down = true;
        }
    }
    else if(state == GLUT_UP) {
        if(button == GLUT_LEFT_BUTTON) {
            g_mouse_left_down = false;
        }
        else if(button == GLUT_RIGHT_BUTTON) {
            g_mouse_right_down = false;
        }
    }
}
void MouseMotion(int x, int y){
    static bool just_warped = false;
    if(just_warped) {
        just_warped = false;
        return;
    }
    if(g_fps_mode) {
        int dx = x - g_viewport_width/2;
        int dy = y - g_viewport_height/2;

        if(dx) {
            g_camera.RotateYaw(g_rotation_speed*dx);
        }
        if(dy) {
            g_camera.RotatePitch(g_rotation_speed*dy);
        }
        glutWarpPointer(g_viewport_width/2, g_viewport_height/2);
        just_warped = true;
    }
}
void colisiones(){
    /**  Techo **/
    g_camera.colision(-100,500,-100, 100, 17, 40);
    g_camera.colision(-100,500,-100, 100, 0, 16.5);
    /**   Museo Exterior **/
    g_camera.colision(69,105,24, 100, 0, 40);
    g_camera.colision(69,105,-100, -12, 0, 40);
    //Sala Nazca
    g_camera.colision(408,415,-80, 92, 0, 40);
    g_camera.colision(223,240,34, 100, 0, 40);
    //
    g_camera.colision(236,408,84, 92, 0, 40);
    g_camera.colision(236,408,-84, -78 ,0, 40);
    //SalaMoche
    g_camera.colision(105,223,93, 110 ,0, 40);
    g_camera.colision(210,224,41,51,0, 40);
    //SalaChimu
    g_camera.colision(105,223,-100, -82,0, 40);
    g_camera.colision(211,228,-32, -20,0, 40);
    //Huacos
    g_camera.colision(260,315,-74, -32,0, 40);
    g_camera.colision(260,315,42, 79,0, 40);
    g_camera.colision(340,408,-69, 84,0, 40);
    g_camera.colision(111,195,-82, -75,0, 40);
    g_camera.colision(108,192,84, 93,0, 40);
    g_camera.colision(110,119,55,88,0,40);
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(1400, 900);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Proyecto Final");
    inicializar();
    /** Obj **/
    ObjPisoCielo();
    ObjMuseo();
    ObjCuadros();
    ObjPlanos();
    ObjLamparas();
    ObjHuacoMoche();
    ObjHuacosNazca();
    ObjHuacosChimu();
    ObjPuertas();
    ObjGuia();
    /** Tga **/
    CargarTgaPisoCielo();
    CargarTgaMuseo();
    CargarTgaPuertas();
    CargarTgaHuacosMoche();
    CargarTgaHuacosNazca();
    CargarTgaHuacosChimu();
    CargarTgaFuia();
    CargarTgaLamparas();
    CargarTgaCuadros();
	glutDisplayFunc(graficar);
    glutReshapeFunc(redimencionar);
	glutTimerFunc(2, animate, 1);
    glutMouseFunc(Mouse);
    glutMotionFunc(MouseMotion);
    glutPassiveMotionFunc(MouseMotion);
    glutKeyboardFunc(Keyboard);
    glutKeyboardUpFunc(KeyboardUp);
    glutIdleFunc(Idle);
    glutTimerFunc(1, Timer, 0);
    glutIdleFunc(graficar);
    glutIdleFunc(colisiones);
    activarLuz();
	iniciarlizarLuces();
    glutMainLoop();
    return 0;
}


