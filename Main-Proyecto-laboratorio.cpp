//Semestre 2019 - 1
//************************************************************//
//************************************************************//
//************** Alumno (s): *********************************//
//*************											******//
//*************											******//
//************************************************************//

#include "texture.h"
#include "figuras.h"
#include "Camera.h"

#include "cmodel/CModel.h"
//Solo para Visual Studio 2015
#if (_MSC_VER >= 1900)
#   pragma comment( lib, "legacy_stdio_definitions.lib" )
#endif

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
static GLuint ciudad_display_list;	//Display List for the Monito


//NEW// Keyframes
float posX = 0, posY = 2.5, posZ = -3.5, rotRodIzq = 0;
float giroMonito = 0;
float movBrazoDer = 0.0;

#define MAX_FRAMES 9
int i_max_steps = 90;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float rotRodIzq;
	float rotInc;
	float giroMonito;
	float giroMonitoInc;
	float movBrazoDer;
	float movBrazoDerInc;


}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 5;			//introducir datos
bool play = false;
int playIndex = 0;
//variable para animacion
bool puertaabrida = false;
float angulopuerta, alagiro, alagiro2;
bool ventanaabrida = false;
float ventanadeslizada;
bool aleteo = false;
bool banderaala = false;


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int w = 500, h = 500;
int frame = 0, time, timebase = 0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font = (int)GLUT_BITMAP_HELVETICA_18;

//Otras opciones son:
/*GLUT_BITMAP_8_BY_13
GLUT_BITMAP_9_BY_15
GLUT_BITMAP_TIMES_ROMAN_10
GLUT_BITMAP_TIMES_ROMAN_24
GLUT_BITMAP_HELVETICA_10
GLUT_BITMAP_HELVETICA_12
GLUT_BITMAP_HELVETICA_18*/



//GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[] = { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[] = { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = { 18 };

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s2[] = { 22 };

CTexture text1;
CTexture text2;
CTexture text3;	//Flecha
CTexture text4;	//Pavimento
CTexture text5;	//Pasto01
CTexture text6;	//Casa01

CTexture tree;

////depa/////
CTexture ParedSala;
CTexture PisoAzul;
CTexture terxturapared1;
CTexture texturatecho;
CTexture texturapared3;
CTexture texturapared4;
CTexture paredexterior;
CTexture Textura_Madera;
CTexture azulejos;
CTexture cgarrafon;
CTexture cajontarja;
CTexture colorceniza;
CTexture contenidorefri;
CTexture metal;
CTexture paredestucada1;
CTexture puerta;
CTexture puertarefri;
CTexture rustic;
CTexture tarja;
CTexture tarjabase;
CTexture tgarrafon;
CTexture toprefri;
CTexture ventana;
CTexture bienve;




///depa//////

CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;
CFiguras fig7;	//Para crear Monito


CFiguras Librero;
CFiguras Cajonera;
CFiguras Mesa;
CFiguras banco;
CFiguras lavabo;
CFiguras garrafon;
CFiguras refri;
CFiguras ventanas;
CFiguras ovsi;



//Figuras de 3D Studio


//Animaci�n del coche
float angRot = 0.0;
float movKitX = 0.0;
float movKitZ = 0.0;
float rotKit = 180.0;
float rotTires = 0.0;
bool g_fanimacion = false;
bool g_avanza = false;

bool circuito = false;
bool recorrido1 = false;
bool recorrido2 = false;
bool recorrido3 = false;
bool recorrido4 = false;
bool recorrido5 = true;


void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
	KeyFrame[FrameIndex].giroMonito = giroMonito;
	KeyFrame[FrameIndex].movBrazoDer = movBrazoDer;

	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotRodIzq = KeyFrame[0].rotRodIzq;
	giroMonito = KeyFrame[0].giroMonito;
	movBrazoDer = KeyFrame[0].movBrazoDer;

}

void interpolation(void)
{
	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;
	KeyFrame[playIndex].giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;
	KeyFrame[playIndex].movBrazoDerInc = (KeyFrame[playIndex + 1].movBrazoDer - KeyFrame[playIndex].movBrazoDer) / i_max_steps;

}

void ciudad()
{

	glPushMatrix(); //Camino1
	glTranslatef(23.5, 0.0, 0.0);
	glScalef(40, 0.1, 7);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Camino2
	glTranslatef(-23.5, 0.0, 0.0);
	glScalef(40, 0.1, 7);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Camino3  lateral derecho
	glTranslatef(47, 0.0, -19);
	glRotatef(90, 0, 1, 0);
	//glScalef(40,0.1,7);
	glScalef(45, 0.1, 7);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Camino4  fondo derecho
	glTranslatef(21.75, 0.0, -38);
	//glScalef(40,0.1,7);
	glScalef(43.5, 0.1, 7);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Camino5  fondo izquierdo
	glTranslatef(-21.75, 0.0, -38);
	//glScalef(40,0.1,7);
	glScalef(43.5, 0.1, 7);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Camino6 lateral izquierdo
	glTranslatef(-47, 0.0, -19);
	glRotatef(90, 0, 1, 0);
	//glScalef(40,0.1,7);
	glScalef(45, 0.1, 7);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();


	glPushMatrix(); //Pasto
	glTranslatef(0.0, 0.0, -4.0);
	glScalef(87, 0.1, 1);
	glDisable(GL_LIGHTING);
	fig4.prisma2(text5.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Pasto
	glTranslatef(0.0, 0.0, 4.0);
	glScalef(87, 0.1, 1);
	glDisable(GL_LIGHTING);
	fig4.prisma2(text5.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Casa01
	glTranslatef(0.0, 3.0, 7.0);
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 0, 1);
	glScalef(6, 5.0, 6);
	glDisable(GL_LIGHTING);
	fig5.prisma2(text6.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Casa01
	glTranslatef(0.0, 3.0, -7.0);
	glRotatef(90, 1, 0, 0);
	//glRotatef(180,0,0,1);
	glScalef(6, 5.0, 6);
	glDisable(GL_LIGHTING);
	fig5.prisma2(text6.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();



}

void arbol_alpha()
{
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		glBindTexture(GL_TEXTURE_2D, tree.GLindex);
		glBegin(GL_QUADS); //plano
		glColor3f(1.0, 1.0, 1.0);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
		glEnd();

	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_LIGHTING);

	glPopMatrix();
}

void arbol_blend()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);     // Turn Blending On
	//glDisable(GL_DEPTH_TEST);   // Turn Depth Testing Off
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, tree.GLindex);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);        // Turn Blending Off
	//glEnable(GL_DEPTH_TEST);    // Turn Depth Testing On
	glEnable(GL_LIGHTING);
}

void monito()
{
	//glNewList(1, GL_COMPILE);
	glPushMatrix();//Pecho
	glScalef(0.5, 0.5, 0.5);
	fig7.prisma(2.0, 2.0, 1, text2.GLindex);

	glPushMatrix();//Cuello
	glTranslatef(0, 1.0, 0.0);
	fig7.cilindro(0.25, 0.25, 15, 0);
	glPushMatrix();//Cabeza
	glTranslatef(0, 1.0, 0);
	fig7.esfera(0.75, 15, 15, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //Brazo derecho-->
	glTranslatef(1.25, 0.65, 0);
	fig7.esfera(0.5, 12, 12, 0);
	glPushMatrix();
	glTranslatef(0.25, 0, 0);
	glRotatef(movBrazoDer, 0.0, 0.0, 1.0);
	glRotatef(-45, 0, 1, 0);
	glTranslatef(0.75, 0, 0);
	fig7.prisma(0.7, 1.5, 0.7, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //Brazo izquierdo <--
	glTranslatef(-1.25, 0.65, 0);
	fig7.esfera(0.5, 12, 12, 0);
	glPushMatrix();
	glTranslatef(-0.25, 0, 0);
	glRotatef(45, 0, 1, 0);
	glRotatef(25, 0, 0, 1);
	glRotatef(25, 1, 0, 0);
	glTranslatef(-0.75, 0, 0);
	fig7.prisma(0.7, 1.5, 0.7, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();//Cintura
	glColor3f(0, 0, 1);
	glTranslatef(0, -1.5, 0);
	fig7.prisma(1, 2, 1, 0);

	glPushMatrix(); //Pie Derecho -->
	glTranslatef(0.75, -0.5, 0);
	glRotatef(-15, 1, 0, 0);
	glTranslatef(0, -0.5, 0);
	fig7.prisma(1.0, 0.5, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	glRotatef(15, 1, 0, 0);
	glTranslatef(0, -0.75, 0);
	fig7.prisma(1.5, 0.5, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.75, 0.3);
	fig7.prisma(0.2, 1.2, 1.5, 0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix(); //Pie Izquierdo -->
	glTranslatef(-0.75, -0.5, 0);
	glRotatef(-5, 1, 0, 0);
	glTranslatef(0, -0.5, 0);
	fig7.prisma(1.0, 0.5, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	glRotatef(15 + rotRodIzq, 1, 0, 0);
	glTranslatef(0, -0.75, 0);
	fig7.prisma(1.5, 0.5, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.75, 0.3);
	fig7.prisma(0.2, 1.2, 1.5, 0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPopMatrix();


	glColor3f(1, 1, 1);
	glPopMatrix();
	//glEndList();
}

void depa()//////////////////////////////////////////////////depa
{
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//muro largo
			glColor3f(1.0, 0.0, 1.0);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.0);
			glTexCoord2f(2.0f, 0.0f); glVertex3f(5, 0, 0.0);
			glTexCoord2f(2.0f, 2.0f);glVertex3f(5, 3, 0.0);
			glTexCoord2f(0.0f, 2.0f);glVertex3f(0, 3, 0.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, paredexterior.GLindex);
		glBegin(GL_QUADS);//muro largo reverse
			glColor3f(1.0, 0.0, 1.0);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, -0.001);
			glTexCoord2f(3.0f, 0.0f); glVertex3f(5, 0, -0.001);
			glTexCoord2f(3.0f, 3.0f);glVertex3f(5, 3, -0.001);
			glTexCoord2f(0.0f, 3.0f);glVertex3f(0, 3, -0.001);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, puerta.GLindex);
		glBegin(GL_QUADS);//cppuerta
		glColor3f(1.0, 0.0, 0.0);
		glNormal3f(-1.0, 0.0f, 0.0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(5.0, 0.0, 0.001);
		glTexCoord2f(1.0, 0.0f); glVertex3f(5.0, 0.0, 0.801);
		glTexCoord2f(1.0, 1.0); glVertex3f(5.0, 3, 0.801);
		glTexCoord2f(0.0f, 1.0); glVertex3f(5.0, 3, 0.001);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//muro puerta cuarto
			glColor3f(1.0, 0.0, 1.0);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(5.0, 0.0, 0.8);
			glTexCoord2f(1.0, 0.0f); glVertex3f(5, 0, 1.8);
			glTexCoord2f(1.0, 1.0); glVertex3f(5, 3, 1.8);
			glTexCoord2f(0.0f, 1.0); glVertex3f(5.0, 3, 0.8);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, paredexterior.GLindex);
		glBegin(GL_QUADS);//muro puerta cuarto reverse
			glColor3f(1.0, 0.0, 1.0);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(5.001, 0.0, 0.0);
			glTexCoord2f(2.0, 0.0f); glVertex3f(5.001, 0, 1.8);
			glTexCoord2f(2.0, 2.0); glVertex3f(5.001, 3, 1.8);
			glTexCoord2f(0.0f, 2.0); glVertex3f(5.001, 3, 0.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//contra puerta entrada
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(5.0, 0.0, 1.8);
			glTexCoord2f(1.0, 0.0f); glVertex3f(6.2, 0, 1.8);
			glTexCoord2f(1.0, 1.0); glVertex3f(6.2, 3, 1.8);
			glTexCoord2f(0.0f, 1.0); glVertex3f(5.0, 3, 1.8);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, paredexterior.GLindex);
		glBegin(GL_QUADS);//contra puerta entrada reverse
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(5.0, 0.0, 1.799);
			glTexCoord2f(1.0, 0.0f); glVertex3f(6.2, 0, 1.799);
			glTexCoord2f(1.0, 2.0); glVertex3f(6.2, 3, 1.799);
			glTexCoord2f(0.0f, 2.0); glVertex3f(5.0, 3, 1.799);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//adyacente puerta entrada
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(6.2, 0.0, 1.8);
			glTexCoord2f(1.0, 0.0f); glVertex3f(6.2, 0, 3.0);
			glTexCoord2f(1.0, 1.0); glVertex3f(6.2, 3, 3.0);
			glTexCoord2f(0.0, 1.0); glVertex3f(6.2, 3, 1.8);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, paredexterior.GLindex);
		glBegin(GL_QUADS);//adyacente puerta entrada reverse
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(6.201, 0.0, 1.8);
			glTexCoord2f(1.0, 0.0f); glVertex3f(6.201, 0, 3.0);
			glTexCoord2f(1.0, 2.0); glVertex3f(6.201, 3, 3.0);
			glTexCoord2f(0.0, 2.0); glVertex3f(6.201, 3, 1.8);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, puerta.GLindex);
		glBegin(GL_QUADS);//puerta entrada
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(6.2, 0.0, 3.0);
			glTexCoord2f(1.0, 0.0f); glVertex3f(5.4, 0, 3.0);
			glTexCoord2f(1.0, 1.0); glVertex3f(5.4, 3, 3.0);
			glTexCoord2f(0.0f, 1.0); glVertex3f(6.2, 3, 3.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, puerta.GLindex);
		glBegin(GL_QUADS);//puerta entrada reverse
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(6.2, 0.0, 3.001);
			glTexCoord2f(1.0, 0.0f);  glVertex3f(5.4, 0, 3.001);
			glTexCoord2f(1.0, 1.0); glVertex3f(5.4, 3, 3.001);
			glTexCoord2f(0.0f, 1.0); glVertex3f(6.2, 3, 3.001);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//entre puertas
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(5.4, 0.0, 3.0);
			glTexCoord2f(1.0, 0.0f);  glVertex3f(4.9, 0, 3.0);
			glTexCoord2f(1.0, 1.0); glVertex3f(4.9, 3, 3.0);
			glTexCoord2f(0.0f, 1.0); glVertex3f(5.4, 3, 3.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, paredexterior.GLindex);
		glBegin(GL_QUADS);//entre puertas reverse
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(5.4, 0.0, 3.001);
			glTexCoord2f(1.0, 0.0f); glVertex3f(4.9, 0, 3.001);
			glTexCoord2f(1.0, 2.0); glVertex3f(4.9, 3, 3.001);
			glTexCoord2f(0.0f, 2.0); glVertex3f(5.4, 3, 3.001);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, puerta.GLindex);
		glBegin(GL_QUADS);//puerta b
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(4.9, 0.0, 3.0);
			glTexCoord2f(1.0, 0.0f); glVertex3f(4.1, 0, 3.0);
			glTexCoord2f(1.0, 1.0); glVertex3f(4.1, 3, 3.0);
			glTexCoord2f(0.0f, 1.0); glVertex3f(4.9, 3, 3.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, paredexterior.GLindex);
		glBegin(GL_QUADS);//puerta b reverse
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(4.9, 0.0, 3.001);
			glTexCoord2f(1.0, 0.0f); glVertex3f(4.1, 0, 3.001);
			glTexCoord2f(1.0, 2.0); glVertex3f(4.1, 3, 3.001);
			glTexCoord2f(0.0f, 2.0); glVertex3f(4.9, 3, 3.001);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//muro peque�o
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(4.1, 0.0, 3.0);
			glTexCoord2f(1.0, 0.0f); glVertex3f(2.9, 0, 3.0);
			glTexCoord2f(1.0, 1.0); glVertex3f(2.9, 3, 3.0);
			glTexCoord2f(0.0f, 1.0); glVertex3f(4.1, 3, 3.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, paredexterior.GLindex);
		glBegin(GL_QUADS);//muro peque�o reverse
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(4.1, 0.0, 3.001);
			glTexCoord2f(1.0, 0.0f); glVertex3f(2.9, 0, 3.001);
			glTexCoord2f(1.0, 2.0); glVertex3f(2.9, 3, 3.001);
			glTexCoord2f(0.0f, 2.0); glVertex3f(4.1, 3, 3.001);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//muro adyacente cocina
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(-1.0, 0.0f, 0.0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(2.9, 0.0, 3.0);
			glTexCoord2f(1.0, 0.0f); glVertex3f(2.9, 0.0, 4.4);
			glTexCoord2f(1.0, 2.0); glVertex3f(2.9, 3, 4.4);
			glTexCoord2f(0.0f, 2.0); glVertex3f(2.9, 3, 3.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, paredexterior.GLindex);
		glBegin(GL_QUADS);//muro adyacente cocina reverse
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(-1.0, 0.0f, 0.0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(2.901, 0.0, 3.0);
			glTexCoord2f(1.0, 0.0f); glVertex3f(2.901, 0.0, 4.4);
			glTexCoord2f(1.0, 2.0); glVertex3f(2.901, 3, 4.4);
			glTexCoord2f(0.0f, 2.0);  glVertex3f(2.901, 3, 3.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//contra muro cocina
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0, 0.0f, -1.0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(2.9, 0.0, 4.4);
			glTexCoord2f(1.0, 0.0f); glVertex3f(0.0, 0.0, 4.4);
			glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 3, 4.4);
			glTexCoord2f(0.0f, 1.0); glVertex3f(2.9, 3, 4.4);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, paredexterior.GLindex);
		glBegin(GL_QUADS);//contra muro cocina reverse
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0, 0.0f, -1.0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(2.9, 0.0, 4.401);
			glTexCoord2f(1.0, 0.0f); glVertex3f(0.0, 0.0, 4.401);
			glTexCoord2f(1.0, 2.0); glVertex3f(0.0, 3, 4.401);
			glTexCoord2f(0.0f, 2.0); glVertex3f(2.9, 3, 4.401);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//base ventana cocina
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(1.0, 0.0f, 0.0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 4.4);
			glTexCoord2f(1.0, 0.0f); glVertex3f(0.0, 0.0, 3.0);
			glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.2, 3.0);
			glTexCoord2f(0.0f, 1.0); glVertex3f(0.0, 1.2, 4.4);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, paredexterior.GLindex);
		glBegin(GL_QUADS);//base ventana cocina reverse
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(1.0, 0.0f, 0.0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.001, 0.0, 4.4);
			glTexCoord2f(2.0, 0.0f); glVertex3f(-0.001, 0.0, 3.0);
			glTexCoord2f(2.0, 1.0); glVertex3f(-0.001, 1.2, 3.0);
			glTexCoord2f(0.0f, 1.0); glVertex3f(-0.001, 1.2, 4.4);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//ventana cocina izquierda
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(1.0, 0.0f, 0.0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 1.2, 4.4);
			glTexCoord2f(1.0, 0.0f); glVertex3f(0.0, 1.2, 3.9);
			glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 3.0, 3.9);
			glTexCoord2f(0.0f, 1.0); glVertex3f(0.0, 3.0, 4.4);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, paredexterior.GLindex);
		glBegin(GL_QUADS);//ventana cocina izquierda reverse
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(1.0, 0.0f, 0.0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.001, 1.2, 4.4);
			glTexCoord2f(1.0, 0.0f); glVertex3f(-0.001, 1.2, 3.9);
			glTexCoord2f(1.0, 1.0); glVertex3f(-0.001, 3.0, 3.9);
			glTexCoord2f(0.0f, 1.0); glVertex3f(-0.001, 3.0, 4.4);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//ventana cocina top
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(1.0, 0.0f, 0.0);
			glTexCoord2f(0.0f, 0.0f);  glVertex3f(0.0, 2.7, 4.4);
			glTexCoord2f(1.0, 0.0f);  glVertex3f(0.0, 2.7, 3.0);
			glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 3.0, 3.0);
			glTexCoord2f(0.0f, 1.0); glVertex3f(0.0, 3.0, 4.4);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, paredexterior.GLindex);
		glBegin(GL_QUADS);//ventana cocina top reverse
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(1.0, 0.0f, 0.0);
			glTexCoord2f(0.0f, 0.0f);  glVertex3f(-0.001, 2.7, 4.4);
			glTexCoord2f(0.5, 0.0f);  glVertex3f(-0.001, 2.7, 3.0);
			glTexCoord2f(0.5, 0.5); glVertex3f(-0.001, 3.0, 3.0);
			glTexCoord2f(0.0f, 0.5); glVertex3f(-0.001, 3.0, 4.4);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//cadena up
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(2.9, 2.75, 3.0);
			glTexCoord2f(1.0, 0.0f); glVertex3f(2.1, 2.75, 3.0);
			glTexCoord2f(1.0, 1.0); glVertex3f(2.1, 3, 3.0);
			glTexCoord2f(0.0f, 1.0); glVertex3f(2.9, 3, 3.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//cadena up reverse
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(2.9, 2.75, 3.15);
			glTexCoord2f(1.0, 0.0f); glVertex3f(2.1, 2.75, 3.15);
			glTexCoord2f(1.0, 1.0); glVertex3f(2.1, 3, 3.15);
			glTexCoord2f(0.0f, 1.0); glVertex3f(2.9, 3, 3.15);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//cadena up-down
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(2.9, 2.75, 3.15);
			glTexCoord2f(1.0, 0.0f); glVertex3f(2.1, 2.75, 3.15);
			glTexCoord2f(1.0, 1.0); glVertex3f(2.1, 2.75, 3.0);
			glTexCoord2f(0.0f, 1.0); glVertex3f(2.9, 2.75, 3.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//cadena down
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(2.9, 0.0, 3.0);
			glTexCoord2f(1.0, 0.0f); glVertex3f(2.1, 0.0, 3.0);
			glTexCoord2f(1.0, 1.0); glVertex3f(2.1, 0.25, 3.0);
			glTexCoord2f(0.0f, 1.0); glVertex3f(2.9, 0.25, 3.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//muro1cocinabloque
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(2.1, 0.0, 3.0);
			glTexCoord2f(1.0, 0.0f); glVertex3f(1.4, 0.0, 3.0);
			glTexCoord2f(1.0, 1.0); glVertex3f(1.4, 3.0, 3.0);
			glTexCoord2f(0.0f, 1.0); glVertex3f(2.1, 3.0, 3.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//muro1cocinabloque reverse
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(2.1, 0.25, 3.15);
			glTexCoord2f(1.0, 0.0f); glVertex3f(1.4, 0.25, 3.15);
			glTexCoord2f(1.0, 1.0); glVertex3f(1.4, 3.0, 3.15);
			glTexCoord2f(0.0f, 1.0); glVertex3f(2.1, 3.0, 3.15);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//lateral muro puerta cocina
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(-1.0, 0.0f, 0.0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(2.1, 0.25, 3.0);
			glTexCoord2f(1.0, 0.0f); glVertex3f(2.1, 0.25, 3.15);
			glTexCoord2f(1.0, 1.0); glVertex3f(2.1, 2.75, 3.15);
			glTexCoord2f(0.0f, 1.0); glVertex3f(2.1, 3.0, 3.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//base barra
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(1.4, 0.0, 3.0);
			glTexCoord2f(1.0, 0.0f); glVertex3f(0.7, 0.0, 3.0);
			glTexCoord2f(1.0, 1.0); glVertex3f(0.7, 1.2, 3.0);
			glTexCoord2f(0.0f, 1.0); glVertex3f(1.4, 1.2, 3.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//base barra reverse
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(1.4, 0.25, 3.15);
			glTexCoord2f(1.0, 0.0f); glVertex3f(0.7, 0.25, 3.15);
			glTexCoord2f(1.0, 1.0); glVertex3f(0.7, 1.2, 3.15);
			glTexCoord2f(0.0f, 1.0); glVertex3f(1.4, 1.2, 3.15);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//top barra
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(1.4, 3.0, 3.0);
			glTexCoord2f(1.0, 0.0f); glVertex3f(1.4, 2.6, 3.0);
			glTexCoord2f(1.0, 1.0); glVertex3f(0.7, 2.6, 3.0);
			glTexCoord2f(0.0f, 1.0); glVertex3f(0.7, 3.0, 3.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//top barra reverse
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(1.4, 3.0, 3.15);
			glTexCoord2f(1.0, 0.0f); glVertex3f(1.4, 2.6, 3.15);
			glTexCoord2f(1.0, 1.0); glVertex3f(0.7, 2.6, 3.15);
			glTexCoord2f(0.0f, 1.0); glVertex3f(0.7, 3.0, 3.15);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_TRIANGLES);//barra triangulo izquierda
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(1.4, 2.6, 3.0);
			glTexCoord2f(1.0, 0.0f); glVertex3f(1.4, 2.2, 3.0);
			glTexCoord2f(1.0, 1.0);glVertex3f(1.15, 2.6, 3.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//barra triangulo izquierda lateral
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(-0.4, -0.25, 0.0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(1.4, 2.2, 3.0);
			glTexCoord2f(1.0, 0.0f); glVertex3f(1.4, 2.2, 3.15);
			glTexCoord2f(1.0, 1.0); glVertex3f(1.15, 2.6, 3.15);
			glTexCoord2f(0.0f, 1.0); glVertex3f(1.15, 2.6, 3.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_TRIANGLES);//barra triangulo izquierda reverse
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(1.4, 2.6, 3.15);
			glTexCoord2f(1.0, 0.0f); glVertex3f(1.4, 2.2, 3.15);
			glTexCoord2f(1.0, 1.0); glVertex3f(1.15, 2.6, 3.15);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_TRIANGLES);//barra triangulo derecha
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f);  glVertex3f(0.7, 2.6, 3.0);
			glTexCoord2f(1.0, 0.0f); glVertex3f(0.95, 2.6, 3.0);
			glTexCoord2f(1.0, 1.0); glVertex3f(0.7, 2.2, 3.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//barra triangulo derecha lateral
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.4, 0.25, 0.0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.7, 2.2, 3.0);
			glTexCoord2f(1.0, 0.0f); glVertex3f(0.7, 2.2, 3.15);
			glTexCoord2f(1.0, 1.0); glVertex3f(0.95, 2.6, 3.15);
			glTexCoord2f(0.0f, 1.0); glVertex3f(0.95, 2.6, 3.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_TRIANGLES);//barra triangulo derecha reverse
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.7, 2.6, 3.15);
			glTexCoord2f(1.0, 0.0f); glVertex3f(0.95, 2.6, 3.15);
			glTexCoord2f(1.0, 1.0);glVertex3f(0.7, 2.2, 3.15);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);// lateral derecha
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(-1.0f, 0.0f, 0.0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.7, 1.2, 3.0);
			glTexCoord2f(1.0, 0.0f); glVertex3f(0.7, 1.2, 3.15);
			glTexCoord2f(1.0, 1.0); glVertex3f(0.7, 2.2, 3.15);
			glTexCoord2f(0.0f, 1.0);  glVertex3f(0.7, 2.2, 3.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);// lateral izquierda
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(-1.0, 0.0f, 0.0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(1.4, 1.2, 3.0);
			glTexCoord2f(1.0, 0.0f); glVertex3f(1.4, 1.2, 3.15);
			glTexCoord2f(1.0, 1.0); glVertex3f(1.4, 2.2, 3.15);
			glTexCoord2f(0.0f, 1.0); glVertex3f(1.4, 2.2, 3.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);// top barra lateral
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0, 1.0f, 0.0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.95, 2.6, 3.0);
			glTexCoord2f(1.0, 0.0f); glVertex3f(0.95, 2.6, 3.15);
			glTexCoord2f(1.0, 1.0); glVertex3f(1.15, 2.6, 3.15);
			glTexCoord2f(0.0f, 1.0); glVertex3f(1.15, 2.6, 3.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);// barra down
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0, 1.0f, 0.0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.7, 1.2, 2.75);
			glTexCoord2f(1.0, 0.0f); glVertex3f(0.7, 1.2, 3.35);
			glTexCoord2f(1.0, 1.0); glVertex3f(1.4, 1.2, 3.35);
			glTexCoord2f(0.0f, 1.0); glVertex3f(1.4, 1.2, 2.75);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);// barra up
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0, 1.0f, 0.0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.7, 1.3, 2.75);
			glTexCoord2f(1.0, 0.0f); glVertex3f(0.7, 1.3, 3.35);
			glTexCoord2f(1.0, 1.0); glVertex3f(1.4, 1.3, 3.35);
			glTexCoord2f(0.0f, 1.0); glVertex3f(1.4, 1.3, 2.75);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);// barra lateral
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(-1.0, 0.0, 0.0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.7, 1.2, 2.75);
			glTexCoord2f(1.0, 0.0f); glVertex3f(0.7, 1.2, 3.35);
			glTexCoord2f(1.0, 1.0);  glVertex3f(0.7, 1.3, 3.35);
			glTexCoord2f(0.0f, 1.0); glVertex3f(0.7, 1.3, 2.75);
		glEnd();

		glBegin(GL_QUADS);// barra lateral izq
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(-1.0, 0.0, 0.0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(1.4, 1.2, 2.75);
			glTexCoord2f(1.0, 0.0f); glVertex3f(1.4, 1.2, 3.35);
			glTexCoord2f(1.0, 1.0); glVertex3f(1.4, 1.3, 3.35);
			glTexCoord2f(0.0f, 1.0); glVertex3f(1.4, 1.3, 2.75);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);// barra frontal
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(0.0f, 0.0f);  glVertex3f(0.7, 1.2, 3.35);
			glTexCoord2f(1.0, 0.0f); glVertex3f(1.4, 1.2, 3.35);
			glTexCoord2f(1.0, 1.0); glVertex3f(1.4, 1.3, 3.35);
			glTexCoord2f(0.0f, 1.0); glVertex3f(0.7, 1.3, 3.35);
		glEnd();

		glBegin(GL_QUADS);// barra trasera
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.7, 1.2, 2.75);
			glTexCoord2f(1.0, 0.0f); glVertex3f(1.4, 1.2, 2.75);
			glTexCoord2f(1.0, 1.0); glVertex3f(1.4, 1.3, 2.75);
			glTexCoord2f(0.0f, 1.0); glVertex3f(0.7, 1.3, 2.75);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//muro2cocinabloque
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.7, 0.0, 3.0);
			glTexCoord2f(1.0, 0.0f); glVertex3f(0.0, 0.0, 3.0);
			glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 3.0, 3.0);
			glTexCoord2f(0.0f, 1.0); glVertex3f(0.7, 3.0, 3.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//muro2cocinabloque reverse
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.7, 0.25, 3.15);
			glTexCoord2f(1.0, 0.0f); glVertex3f(0.0, 0.25, 3.15);
			glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 3.0, 3.15);
			glTexCoord2f(0.0f, 1.0); glVertex3f(0.7, 3.0, 3.15);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);//base ventana principal
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 3.0);
			glTexCoord2f(1.0, 0.0f); glVertex3f(0.0, 0.0, 0.0);
			glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.2, 0.0);
			glTexCoord2f(0.0f, 1.0); glVertex3f(0.0, 1.2, 3.0);
		glEnd();
	glPopMatrix();



	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, paredexterior.GLindex);
		glBegin(GL_QUADS);//base ventana principal -0.1
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.001, 0.0, 3.0);
			glTexCoord2f(2.0, 0.0f); glVertex3f(-0.001, 0.0, 0.0);
			glTexCoord2f(2.0, 1.0); glVertex3f(-0.001, 1.2, 0.0);
			glTexCoord2f(0.0f, 1.0); glVertex3f(-0.001, 1.2, 3.0);
		glEnd();
	glPopMatrix();




	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);// ventana principal derecha
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 1.2, 0.6);
			glTexCoord2f(1.0, 0.0f); glVertex3f(0.0, 1.2, 0.0);
			glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 3.0, 0.0);
			glTexCoord2f(0.0f, 1.0); glVertex3f(0.0, 3.0, 0.6);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, paredexterior.GLindex);
		glBegin(GL_QUADS);// ventana principal derecha reverse
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.001, 1.2, 0.6);
			glTexCoord2f(1.0, 0.0f); glVertex3f(-0.001, 1.2, 0.0);
			glTexCoord2f(1.0, 1.0);  glVertex3f(-0.001, 3.0, 0.0);
			glTexCoord2f(0.0f, 1.0); glVertex3f(-0.001, 3.0, 0.6);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);// ventana principal izquierda
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 1.2, 3.0);
			glTexCoord2f(1.0, 0.0f); glVertex3f(0.0, 1.2, 2.4);
			glTexCoord2f(1.0, 1.0);  glVertex3f(0.0, 3.0, 2.4);
			glTexCoord2f(0.0f, 1.0); glVertex3f(0.0, 3.0, 3.0);
		glEnd();
	
		
		
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, paredexterior.GLindex);
		glBegin(GL_QUADS);// ventana principal izquierda reverse
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0, 0.0); glVertex3f(-0.001, 1.2, 3.15);
			glTexCoord2f(2.0, 0.0); glVertex3f(-0.001, 1.2, 2.4);
			glTexCoord2f(2.0, 2.0); glVertex3f(-0.001, 3.0, 2.4);
			glTexCoord2f(0.0, 2.0); glVertex3f(-0.001, 3.0, 3.15);
		glEnd();
	glPopMatrix();

	

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rustic.GLindex);
		glBegin(GL_QUADS);// ventana principal top
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 2.7, 2.4);
			glTexCoord2f(2.0, 0.0); glVertex3f(0.0, 2.7, 0.6);
			glTexCoord2f(2.0, 2.0); glVertex3f(0.0, 3.0, 0.6);
			glTexCoord2f(0.0, 2.0); glVertex3f(0.0, 3.0, 2.4);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, paredexterior.GLindex);
		glBegin(GL_QUADS);// ventana principal top reverse
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0, 0.0); glVertex3f(-0.001, 2.7, 2.4);
			glTexCoord2f(0.5, 0.0); glVertex3f(-0.001, 2.7, 0.6);
			glTexCoord2f(0.5, 0.5); glVertex3f(-0.001, 3.0, 0.6);
			glTexCoord2f(0.0, 0.5); glVertex3f(-0.001, 3.0, 2.4);
		glEnd();
	glPopMatrix();

	/////Suelos

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, PisoAzul.GLindex);
		glBegin(GL_QUADS);//piso mayor
			glColor3f(1.0, 0.0, 1.0);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.0);
			glTexCoord2f(3.0, 0.0f); glVertex3f(0.0, 0, 3.0);
			glTexCoord2f(3.0, 5.0);glVertex3f(5.0, 0.0, 3.0);
			glTexCoord2f(0.0f, 5.0);glVertex3f(5.0, 0.0, 0.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, PisoAzul.GLindex);
		glBegin(GL_QUADS);//piso cocina
			glColor3f(1.0, 0.0, 1.0);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0, 0.0); glVertex3f(2.9, 0.25, 3.0);
			glTexCoord2f(3.0, 0.0); glVertex3f(0.0, 0.25, 3.0);
			glTexCoord2f(3.0, 5.0); glVertex3f(0.0, 0.25, 4.4);
			glTexCoord2f(0.0, 5.0); glVertex3f(2.9, 0.25, 4.4);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, PisoAzul.GLindex);
		glBegin(GL_QUADS);// piso puerta entrada
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(5.0, 0.0, 1.8);
			glTexCoord2f(2.2, 0.0f); glVertex3f(5.0, 0.0, 3.0);
			glTexCoord2f(2.2, 2.2); glVertex3f(6.2, 0.0, 3.0);
			glTexCoord2f(0.0f, 2.2);glVertex3f(6.2, 0.0, 1.8);
		glEnd();
	glPopMatrix();



	//////techos

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texturapared4.GLindex);
		glBegin(GL_QUADS);// techo puerta entrada
			glColor3f(1.0, 0.0, 0.0);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(5.0, 3.0, 1.8);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0, 3.0, 3.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(6.2, 3.0, 3.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(6.2, 3.0, 1.8);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texturatecho.GLindex);
		glBegin(GL_QUADS);// techo puerta entrada reverse
		glColor3f(1.0, 0.0, 0.0);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(5.0, 3.001, 1.8);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0, 3.001, 3.0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(6.2, 3.001, 3.0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(6.2, 3.001, 1.8);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texturapared3.GLindex);
		glBegin(GL_QUADS);//techo mayor
			glColor3f(1.0, 0.0, 1.0);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 3.0, 0.0);
			glTexCoord2f(10.0f, 0.0f); glVertex3f(0.0, 3.0, 3.0);
			glTexCoord2f(10.0f, 10.0f);glVertex3f(5.0, 3.0, 3.0);
			glTexCoord2f(0.0f, 10.0f);glVertex3f(5.0, 3.0, 0.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texturatecho.GLindex);
		glBegin(GL_QUADS);//techo mayor reverse
			glColor3f(1.0, 0.0, 1.0);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 3.001, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0, 3.001, 3.0);
			glTexCoord2f(1.0f, 1.0f);glVertex3f(5.0, 3.001, 3.0);
			glTexCoord2f(0.0f, 1.0f);glVertex3f(5.0, 3.001, 0.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texturapared4.GLindex);
		glBegin(GL_QUADS);//techo cocina 
			glColor3f(1.0, 0.0, 1.0);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 3.0, 3.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0, 3.0, 4.4);
			glTexCoord2f(1.0f, 1.0f);glVertex3f(2.9, 3.0, 4.4);
			glTexCoord2f(0.0f, 1.0f);glVertex3f(2.9, 3.0, 3.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texturatecho.GLindex);
		glBegin(GL_QUADS);//techo cocina reverse
		glColor3f(1.0, 0.0, 1.0);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 3.001, 3.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0, 3.001, 4.4);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(2.9, 3.001, 4.4);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(2.9, 3.001, 3.0);
		glEnd();
	glPopMatrix();



}

void Ventanas() {
	glPushMatrix();//ventanas
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		ventanas.prisma(1.5, 0.9, 0.01, ventana.GLindex);
		
		glTranslatef(0.9, 0.0, -0.001);
		glTranslatef(ventanadeslizada - 0.8, 0.0, -0.001);
		
		ventanas.prisma(1.5, 0.9, 0.01, ventana.GLindex);
		glDisable(GL_ALPHA_TEST);
	glPopMatrix();
}
void librero()
{
	glPushMatrix();
		Librero.prisma(0.2,3.8,0.5, Textura_Madera.GLindex);//librero base piso 0
		glPushMatrix();
			glTranslatef(-2.0, 0.4, 0.0);
			Librero.prisma(1.0, 0.2, 0.5, Textura_Madera.GLindex);//librero piso 1 
			glTranslatef(1.0, 0.1, 0.0);
			Librero.prisma(0.8, 0.2, 0.5, Textura_Madera.GLindex);//librero piso 2
			glTranslatef(1.0, 0.0, 0.0);
			Librero.prisma(0.8, 0.2, 0.5, Textura_Madera.GLindex);//librero piso 3
			glTranslatef(1.0, 0.0, 0.0);
			Librero.prisma(0.8, 0.2, 0.5, Textura_Madera.GLindex);//librero piso 4
			glTranslatef(1.0, -0.1, 0.0);
			Librero.prisma(1.0, 0.2, 0.5, Textura_Madera.GLindex);//librero piso 5
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.1, 1.0, 0.0);
			Librero.prisma(0.2, 4.0, 0.5, Textura_Madera.GLindex);//librero base piso 1
			glPushMatrix();
				glTranslatef(-0.9, 0.5, 0.0);
				Librero.prisma(0.8, 0.2, 0.5, Textura_Madera.GLindex);//librero piso 1 
				glTranslatef(1.0, 0.0, 0.0);
				Librero.prisma(0.8, 0.2, 0.5, Textura_Madera.GLindex);//librero piso 2
				glTranslatef(1.0, 0.0, 0.0);
				Librero.prisma(0.8, 0.2, 0.5, Textura_Madera.GLindex);//librero piso 3
				glTranslatef(1.0, -0.1, 0.0);
				Librero.prisma(1.0, 0.2, 0.5, Textura_Madera.GLindex);//librero piso 4
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.4, 2.0, 0.0);
			Librero.prisma(0.2, 3.0, 0.5, Textura_Madera.GLindex);//librero base piso 2
			glPushMatrix();
				glTranslatef(-0.4, 0.5, 0.0);
				Librero.prisma(0.8, 0.2, 0.5, Textura_Madera.GLindex);//librero piso 1 
				glTranslatef(1.0, 0.0, 0.0);
				Librero.prisma(0.8, 0.2, 0.5, Textura_Madera.GLindex);//librero piso 2
				glTranslatef(1.0, -0.1, 0.0);
				Librero.prisma(1.0, 0.2, 0.5, Textura_Madera.GLindex);//librero piso 3
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.9, 3.0, 0.0);
			Librero.prisma(0.2, 2.0, 0.5, Textura_Madera.GLindex);//librero base piso 3
			glPushMatrix();
				glTranslatef(0.1, 0.5, 0.0);
				Librero.prisma(0.8, 0.2, 0.5, Textura_Madera.GLindex);//librero piso 1 
				glTranslatef(1.0, -0.1, 0.0);
				Librero.prisma(1.0, 0.2, 0.5, Textura_Madera.GLindex);//librero piso 2
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(1.5, 4.0, 0.0);
		Librero.prisma(0.2, 1.2, 0.5, Textura_Madera.GLindex);//librero base piso 3
		glPopMatrix();
	glPopMatrix();
}

void cajonera()
{
	glPushMatrix();
		Cajonera.prisma(0.1, 1.8, 0.6, colorceniza.GLindex);//cajonera base
		glPushMatrix();
			glTranslatef(-0.85, 0.55, 0.0);
			Cajonera.prisma(1.0, 0.1, 0.6, colorceniza.GLindex);//lado izquierdo
			glTranslatef(1.7, 0.0, 0.0);
			Cajonera.prisma(1.0, 0.1, 0.6, colorceniza.GLindex);//lado derecho
			glTranslatef(-0.85, 0.0, -0.25);
			Cajonera.prisma(1.0, 1.78, 0.1, colorceniza.GLindex);//lado trasero
			glTranslatef(0.0, 0.55, 0.25);
			Cajonera.prisma(0.1, 2.0, 0.8, colorceniza.GLindex);//tapa
		glPopMatrix();
		glPushMatrix();//cajon base izquierdo
			glTranslatef(-0.4, 0.1, 0.1);
			Cajonera.prisma(0.05, 0.8, 0.5, colorceniza.GLindex);//cAJON BASE
			glTranslatef(-0.4, 0.2, 0.0);
			Cajonera.prisma(0.45, 0.05, 0.5, colorceniza.GLindex);//cAJON lado izquierdo
			glTranslatef(0.8, 0.0, 0.0);
			Cajonera.prisma(0.45, 0.05, 0.5, colorceniza.GLindex);//cAJON lado derecho
			glTranslatef(-0.4, 0.0, -0.25);
			Cajonera.prisma(0.45, 0.8, 0.05, colorceniza.GLindex);//cAJON trasero
			glTranslatef(0.0, 0.0, 0.5);
			glRotatef(90, 1.0, 0.0, 0.0);
			Cajonera.prisma3(0.05, 0.8, 0.45, colorceniza.GLindex,texturapared4.GLindex);//cAJON frente			
		glPopMatrix();

		glPushMatrix();//cajon base derecho
			glTranslatef(0.4, 0.1, 0.1);
			Cajonera.prisma(0.05, 0.8, 0.5, colorceniza.GLindex);//cAJON BASE
			glTranslatef(-0.4, 0.2, 0.0);
			Cajonera.prisma(0.45, 0.05, 0.5, colorceniza.GLindex);//cAJON lado izquierdo
			glTranslatef(0.8, 0.0, 0.0);
			Cajonera.prisma(0.45, 0.05, 0.5, colorceniza.GLindex);//cAJON lado derecho
			glTranslatef(-0.4, 0.0, -0.25);
			Cajonera.prisma(0.45, 0.8, 0.05, colorceniza.GLindex);//cAJON trasero
			glTranslatef(0.0, 0.0, 0.5);
			glRotatef(90, 1.0, 0.0, 0.0);
			Cajonera.prisma3(0.05, 0.8, 0.45, colorceniza.GLindex, texturapared4.GLindex);//cAJON frente			
		glPopMatrix();

		glPushMatrix();//cajon superficie izquierdo
			glTranslatef(-0.4, 0.55, 0.1);
			Cajonera.prisma(0.05, 0.8, 0.5, colorceniza.GLindex);//cAJON BASE
			glTranslatef(-0.4, 0.2, 0.0);
			Cajonera.prisma(0.45, 0.05, 0.5, colorceniza.GLindex);//cAJON lado izquierdo
			glTranslatef(0.8, 0.0, 0.0);
			Cajonera.prisma(0.45, 0.05, 0.5, colorceniza.GLindex);//cAJON lado derecho
			glTranslatef(-0.4, 0.0, -0.25);
			Cajonera.prisma(0.45, 0.8, 0.05, colorceniza.GLindex);//cAJON trasero
			glTranslatef(0.0, 0.0, 0.5);
			glRotatef(90, 1.0, 0.0, 0.0);
			Cajonera.prisma3(0.05, 0.8, 0.45, colorceniza.GLindex, texturapared4.GLindex);//cAJON frente			
		glPopMatrix();

		glPushMatrix();//cajon superficie derecha
			glTranslatef(0.4, 0.55, 0.1);
			Cajonera.prisma(0.05, 0.8, 0.5, colorceniza.GLindex);//cAJON BASE
			glTranslatef(-0.4, 0.2, 0.0);
			Cajonera.prisma(0.45, 0.05, 0.5, colorceniza.GLindex);//cAJON lado izquierdo
			glTranslatef(0.8, 0.0, 0.0);
			Cajonera.prisma(0.45, 0.05, 0.5, colorceniza.GLindex);//cAJON lado derecho
			glTranslatef(-0.4, 0.0, -0.25);
			Cajonera.prisma(0.45, 0.8, 0.05, colorceniza.GLindex);//cAJON trasero
			glTranslatef(0.0, 0.0, 0.5);
			glRotatef(90, 1.0, 0.0, 0.0);
			Cajonera.prisma3(0.05, 0.8, 0.45, colorceniza.GLindex, texturapared4.GLindex);//cAJON frente			
		glPopMatrix();

	glPopMatrix();
}

void mesa() {
	glPushMatrix();
		Mesa.prisma3(0.15, 1.5, 1.0, colorceniza.GLindex, azulejos.GLindex);//base
		glPushMatrix();
			glTranslatef(-0.55, -0.475, 0.3);
			Mesa.prisma(0.8, 0.2, 0.2, colorceniza.GLindex);//pataizquierda
			glTranslatef(1.1, 0.0, 0.0);
			Mesa.prisma(0.8, 0.2, 0.2, colorceniza.GLindex);//pata derecha
			glTranslatef(0.0, 0.0, -0.7);
			Mesa.prisma(0.8, 0.2, 0.2, colorceniza.GLindex);//pata derecha trasera
			glTranslatef(-1.1, 0.0, 0.0);
			Mesa.prisma(0.8, 0.2, 0.2, colorceniza.GLindex);//pata izquierda trasera
		glPopMatrix();
	glPopMatrix();
}

void Banco() {
	glPushMatrix();
		Mesa.prisma3(0.1, 1.0, 0.5, colorceniza.GLindex, texturapared4.GLindex);//base
		glPushMatrix();
			glTranslatef(-0.4, -0.25, 0.15);
			Mesa.prisma(0.4, 0.1, 0.1, colorceniza.GLindex);//pataizquierda
			glTranslatef(0.8, 0.0, 0.0);
			Mesa.prisma(0.4, 0.1, 0.1, colorceniza.GLindex);//pata derecha
			glTranslatef(0.0, 0.0, -0.3);
			Mesa.prisma(0.4, 0.1, 0.1, colorceniza.GLindex);//pata derecha trasera
			glTranslatef(-0.8, 0.0, 0.0);
			Mesa.prisma(0.4, 0.1, 0.1, colorceniza.GLindex);//pata izquierda trasera
		glPopMatrix();
	glPopMatrix();
}

void Refri() {
	glPushMatrix();
	refri.prisma3(1.0, 0.6, 0.1, metal.GLindex, toprefri.GLindex);//trasero
	glPushMatrix();
		glTranslatef(0.0, 0.45, 0.35);
		refri.prisma(0.1, 0.6, 0.6, toprefri.GLindex);
		glTranslatef(0.0, -0.9, 0.0);
		refri.prisma(0.1, 0.6, 0.6, metal.GLindex);
		glTranslatef(-0.25, 0.45, 0.0);
		refri.prisma(0.8, 0.1, 0.6, metal.GLindex);
		glTranslatef(0.5, 0.0, 0.0);
		refri.prisma(0.8, 0.1, 0.6, metal.GLindex);
		glPushMatrix();
			glTranslatef(0.0, 0.0, 0.35);
			glRotatef(angulopuerta, 0.0, 1.0, 0.0);
			glTranslatef(-0.25, 0.0, 0.0);//
			refri.prisma(1.0, 0.6, 0.1, puertarefri.GLindex);//puerta refri
			
			
		glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void Lavabo() {
	glPushMatrix();
	lavabo.prisma4(0.9, 1.6, 0.7, cajontarja.GLindex, colorceniza.GLindex, colorceniza.GLindex, colorceniza.GLindex, colorceniza.GLindex, tarja.GLindex);
	glPushMatrix();
		glTranslatef(-0.35, 0.65, 0.0);
		lavabo.prisma3(0.4, 0.9, 0.7, metal.GLindex, metal.GLindex);
		glPushMatrix();
			glTranslatef(1.1, 0.0, 0.0);
			lavabo.prisma3(0.4, 0.1, 0.7, metal.GLindex, metal.GLindex);//lado derecho
			glTranslatef(-0.3, 0.0, -0.3);
			lavabo.prisma3(0.4, 0.7, 0.1, metal.GLindex, metal.GLindex);//lado trasero
			glTranslatef(0.0, 0.0, 0.6);
			lavabo.prisma3(0.4, 0.7, 0.1, metal.GLindex, metal.GLindex);//lado frontal
			glPushMatrix();
				glTranslatef(0.0, 0.225, -0.6);
				lavabo.prisma3(0.05, 0.35, 0.05, metal.GLindex, metal.GLindex);//base perillas
				glTranslatef(0.12, 0.025, -0.0);
				lavabo.cilindro(0.02, 0.015, 10, metal.GLindex);//perilla derecha
				glTranslatef(-0.24, 0.0, -0.0);
				lavabo.cilindro(0.02, 0.015, 10, metal.GLindex);//perilla izquierda
				glTranslatef(0.12, -0.005, -0.0);
				lavabo.cilindro(0.013, 0.1, 10, metal.GLindex);//tubo
				glTranslatef(0.0, 0.1, 0.036);
				glRotatef(-90, 1, 0, 0);
				glRotatef(-90, 0, 0, 1);
				lavabo.toros(0.05, 0.025, 20,20,metal.GLindex);//tubo curvo
			glPopMatrix();
		glPopMatrix();

	glPopMatrix();
	glPopMatrix();
}

void Garrafon() {
	glPushMatrix();
		garrafon.cilindro(0.25, 0.6, 15, tgarrafon.GLindex);
		glTranslatef(0.0, 0.6, 0.0);
		garrafon.cono(0.2, 0.25, 10, cgarrafon.GLindex);
		glTranslatef(0.0, 0.14, 0.0);
		garrafon.cilindro(0.07, 0.15, 10, cgarrafon.GLindex);
	glPopMatrix();
}

void Ovsi() {
	glPushMatrix();
	ovsi.prisma_anun(bienve.GLindex, azulejos.GLindex);
	
	glPopMatrix();
}


GLuint createDL()
{
	GLuint ciudadDL;
	//GLuint cieloDL;

	// Create the id for the list
	ciudadDL = glGenLists(1);
	// start list
	glNewList(ciudadDL, GL_COMPILE);
	// call the function that contains 
	// the rendering commands
	ciudad();
	//monito();
// endList
	glEndList();

	return(ciudadDL);
}

void InitGL(GLvoid)     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);
	//Para construir la figura comentar esto
	//glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, Diffuse);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Position2);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	//glEnable(GL_LIGHT1);

	//glEnable ( GL_COLOR_MATERIAL );
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glPolygonMode(GL_BACK, GL_LINE);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/* setup blending */
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE);			// Set The Blending Function For Translucency
	//glColor4f(1.0f, 1.0f, 1.0f, 0.5); 

	ParedSala.LoadTGA("ParedSala.tga");
	ParedSala.BuildGLTexture();
	ParedSala.ReleaseImage();

	bienve.LoadTGA("bienve.tga");
	bienve.BuildGLTexture();
	bienve.ReleaseImage();

	cajontarja.LoadTGA("cajontarja.tga");
	cajontarja.BuildGLTexture();
	cajontarja.ReleaseImage();


	azulejos.LoadTGA("Azulejos.tga");
	azulejos.BuildGLTexture();
	azulejos.ReleaseImage();

	cgarrafon.LoadTGA("cgarrafon.tga");
	cgarrafon.BuildGLTexture();
	cgarrafon.ReleaseImage();

	colorceniza.LoadTGA("color-ceniza.tga");
	colorceniza.BuildGLTexture();
	colorceniza.ReleaseImage();

	contenidorefri.LoadTGA("contenidorefri.tga");
	contenidorefri.BuildGLTexture();
	contenidorefri.ReleaseImage();

	metal.LoadTGA("metal.tga");
	metal.BuildGLTexture();
	metal.ReleaseImage();

	puerta.LoadTGA("puerta.tga");
	puerta.BuildGLTexture();
	puerta.ReleaseImage();

	puertarefri.LoadTGA("puertarefri.tga");
	puertarefri.BuildGLTexture();
	puertarefri.ReleaseImage();

	rustic.LoadTGA("rustic.tga");
	rustic.BuildGLTexture();
	rustic.ReleaseImage();

	tarja.LoadTGA("tarja.tga");
	tarja.BuildGLTexture();
	tarja.ReleaseImage();

	tarjabase.LoadTGA("tarjabase.tga");
	tarjabase.BuildGLTexture();
	tarjabase.ReleaseImage();

	tgarrafon.LoadTGA("tgarrafon.tga");
	tgarrafon.BuildGLTexture();
	tgarrafon.ReleaseImage();

	toprefri.LoadTGA("toprefri.tga");
	toprefri.BuildGLTexture();
	toprefri.ReleaseImage();

	Textura_Madera.LoadTGA("Textura_Madera.tga");
	Textura_Madera.BuildGLTexture();
	Textura_Madera.ReleaseImage();

	PisoAzul.LoadTGA("PisoAzul.tga");
	PisoAzul.BuildGLTexture();
	PisoAzul.ReleaseImage();

	terxturapared1.LoadTGA("terxturapared1.tga");
	terxturapared1.BuildGLTexture();
	terxturapared1.ReleaseImage();

	texturapared3.LoadTGA("texturapared3.tga");
	texturapared3.BuildGLTexture();
	texturapared3.ReleaseImage();

	texturapared4.LoadTGA("texturapared4.tga");
	texturapared4.BuildGLTexture();
	texturapared4.ReleaseImage();

	paredexterior.LoadTGA("paredexterior.tga");
	paredexterior.BuildGLTexture();
	paredexterior.ReleaseImage();

	texturatecho.LoadTGA("texturatecho.tga");
	texturatecho.BuildGLTexture();
	texturatecho.ReleaseImage();


	ventana.LoadTGA("ventana.tga");
	ventana.BuildGLTexture();
	ventana.ReleaseImage();
	
	text1.LoadBMP("01.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	text2.LoadBMP("logopumas.bmp");
	//text2.LoadBMP("hulkcara.bmp");
	text2.BuildGLTexture();
	text2.ReleaseImage();

	text3.LoadTGA("city/arrow.tga");
	text3.BuildGLTexture();
	text3.ReleaseImage();

	text4.LoadTGA("city/pavimento.tga");
	text4.BuildGLTexture();
	text4.ReleaseImage();

	text5.LoadTGA("city/pasto01.tga");
	text5.BuildGLTexture();
	text5.ReleaseImage();

	text6.LoadTGA("city/casa01.tga");
	text6.BuildGLTexture();
	text6.ReleaseImage();

	tree.LoadTGA("Tree.tga");
	tree.BuildGLTexture();
	tree.ReleaseImage();


	objCamera.Position_Camera(0, 2.5f, 3, 0, 2.5f, 0, 0, 1, 0);

	//NEW Crear una lista de dibujo
	ciudad_display_list = createDL();

	//NEW Iniciar variables de KeyFrames
	/*for(int i=0; i<MAX_FRAMES; i++)
	{
		KeyFrame[i].posX =0;
		KeyFrame[i].posY =0;
		KeyFrame[i].posZ =0;
		KeyFrame[i].incX =0;
		KeyFrame[i].incY =0;
		KeyFrame[i].incZ =0;
		KeyFrame[i].rotRodIzq =0;
		KeyFrame[i].rotInc =0;
		KeyFrame[i].giroMonito =0;
		KeyFrame[i].giroMonitoInc =0;
		KeyFrame[i].giroBrazo =0;
		KeyFrame[i].giroBrazoInc = 0;

	}*/

	KeyFrame[0].posX = 0;
	KeyFrame[0].posY = 2.5;
	KeyFrame[0].posZ = -3.5;
	KeyFrame[0].rotRodIzq = 0;
	KeyFrame[0].giroMonito = 0;
	KeyFrame[0].movBrazoDer = 0;

	KeyFrame[1].posX = 20;
	KeyFrame[1].posY = 2.5;
	KeyFrame[1].posZ = -3.5;
	KeyFrame[1].rotRodIzq = 60;
	KeyFrame[1].giroMonito = -90.0;
	KeyFrame[1].movBrazoDer = 40;

	KeyFrame[2].posX = 20;
	KeyFrame[2].posY = 2.5;
	KeyFrame[2].posZ = 4.0;
	KeyFrame[2].rotRodIzq = -20.0;
	KeyFrame[2].giroMonito = 0;
	KeyFrame[2].movBrazoDer = 0;

	KeyFrame[3].posX = 20;
	KeyFrame[3].posY = 2.5;
	KeyFrame[3].posZ = 4.0;
	KeyFrame[3].rotRodIzq = 40.0;
	KeyFrame[3].giroMonito = 45;
	KeyFrame[3].movBrazoDer = 90;

	KeyFrame[4].posX = 20;
	KeyFrame[4].posY = 2.5;
	KeyFrame[4].posZ = 4.0;
	KeyFrame[4].rotRodIzq = -40.0;
	KeyFrame[4].giroMonito = -45;
	KeyFrame[4].movBrazoDer = -90;
	//NEW//////////////////NEW//////////////////NEW//////////////////

}

void pintaTexto(float x, float y, float z, void *font, char *string)
{

	char *c;     //Almacena los caracteres a escribir
	glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
	//glWindowPos2i(150,100);
	for (c = string; *c != '\0'; c++) //Condicion de fin de cadena
	{
		glutBitmapCharacter(font, *c); //imprime
	}
}

void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();


	glPushMatrix();

	glRotatef(g_lookupdown, 1.0f, 0, 0);

	gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
		objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
		objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);


	glPushMatrix();
	glPushMatrix(); //Creamos cielo
	glDisable(GL_LIGHTING);
	glTranslatef(0, 60, 0);
	fig1.skybox(130.0, 130.0, 130.0, text1.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1, 1, 1);
	glCallList(ciudad_display_list);
	glTranslatef(posX, posY, posZ);
	glRotatef(giroMonito, 0, 1, 0);
	//monito();
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glPushMatrix();

		glPushMatrix();
			glTranslatef(41, 0.2, 11.5);
			glRotatef(180, 0.0, 1.0, 0.0);
			librero();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(45.0, 0.2, 11.0);
			glScalef(1.5, 1.5, 1.5);
			glRotatef(180, 0.0, 1.0, 0.0);
			cajonera();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(50.0, 0.0, 12.0);
			glScalef(2.5, 2.5, 2.5);
			glRotatef(180, 0.0, 1.0, 0.0);
			depa();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(47.0, 1.8, 8.0);
			glScalef(2.0, 2.0, 2.0);
			glRotatef(90, 0.0, 1.0, 0.0);
			mesa();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(48.5, 1.0, 8.0);
			glScalef(2.0, 2.0, 2.0);
			glRotatef(90, 0.0, 1.0, 0.0);
			Banco();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(43.5, 1.45, 1.10);
			glScalef(2.0, 2.0, 2.0);
			Refri();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(48, 1.5, 1.6);
			glScalef(1.5, 2.0, 1.5);
			Lavabo();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(35.5, 6.8, 4.75);
			glScalef(2.0, 1.5, 1.0);
			glRotatef(180, 0.0, 1.0, 0.0);
			glRotatef(90, 1.0, 0.0, 0.0);
			Ovsi();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(49.0, 0.0, 6.0);
			glScalef(1.6, 1.6, 1.6);
			Garrafon();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(50.0, 4.9, 9.35);
			glScalef(0.5, 2.5, 2.5);
			glRotatef(90, 0.0, 1.0, 0.0);
			Ventanas();
		glPopMatrix();

		glPopMatrix();


		glPushMatrix(); //Flecha
			glScalef(7, 0.1, 7);
			glDisable(GL_LIGHTING);
			fig3.prisma_anun(text3.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();


		glPushMatrix();
			glTranslatef(-30, 0, 10);
			arbol_alpha();
			glPopMatrix();

			glColor3f(1.0, 1.0, 1.0);

		glPopMatrix();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 0.0, 0.0);
	pintaTexto(-11, 12.0, -14.0, (void *)font, "Proyecto de Laboratorio");
	//pintaTexto(-11,10.5,-14,(void *)font,"Listas de Dibujo");
	pintaTexto(-11, 8.5, -14, (void *)font, s);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glutSwapBuffers();

}

void animacion()
{

	if (puertaabrida && angulopuerta < 90) {
		angulopuerta += 0.22;

	}
	else if (!puertaabrida && angulopuerta > 0) {
		angulopuerta -= 0.22;
	}

	if (ventanaabrida && ventanadeslizada < 0.75) {
		ventanadeslizada += 0.1;

	}
	else if (!ventanaabrida && ventanadeslizada > 0) {
		ventanadeslizada -= 0.1;
	}


	fig3.text_izq -= 0.01;
	fig3.text_der -= 0.01;
	if (fig3.text_izq < -1)
		fig3.text_izq = 0;
	if (fig3.text_der < 0)
		fig3.text_der = 1;

	ovsi.text_izq -= 0.001;
	ovsi.text_der -= 0.001;
	if (ovsi.text_izq < 0)
		ovsi.text_izq = 1;
	if (ovsi.text_der < -1)
		ovsi.text_der = 0;


	//Movimiento del coche
	if (g_fanimacion)
	{
		if (g_avanza)
		{
			movKitZ += 1.0;
			rotTires -= 10;
			if (movKitZ > 130)
				g_avanza = false;
		}
		else
		{
			movKitZ -= 1.0;
			rotTires += 10;
			if (movKitZ < 0)
				g_avanza = true;
		}
	}

	if (circuito)
	{
		if (recorrido1)
		{
			rotKit = 180;
			movKitZ--;
			if (movKitZ > 0)
			{
				recorrido1 = false;
				//recorrido5 = true;
			}
		}
		if (recorrido2)
		{
			rotKit = 180;
			movKitX--;
			if (movKitX < 0)
			{
				recorrido2 = false;
				recorrido5 = true;

			}
		}
		if (recorrido3)
		{
			rotKit = -21.96;
			movKitZ++;
			movKitX = movKitX - 0.4;
			if (movKitZ > 155 && movKitX > 0)
			{
				recorrido3 = false;
				recorrido2 = true;
			}
		}
		if (recorrido4)
		{
			rotKit = 90;
			movKitX++;
			if (movKitX > 125)
			{
				recorrido4 = false;
				recorrido3 = true;
			}
		}
		if (recorrido5)
		{
			//rotKit = 0;
			movKitZ--;
			if (movKitZ < -155)
			{
				recorrido5 = false;
				recorrido4 = true;
			}
		}
	}


	//Movimiento del monito
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += KeyFrame[playIndex].incX;
			posY += KeyFrame[playIndex].incY;
			posZ += KeyFrame[playIndex].incZ;

			rotRodIzq += KeyFrame[playIndex].rotInc;
			giroMonito += KeyFrame[playIndex].giroMonitoInc;
			movBrazoDer += KeyFrame[playIndex].movBrazoDerInc;

			i_curr_steps++;
		}

	}

	/*frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(s,"FPS:%4.2f",frame*1000.0/(time-timebase));
		timebase = time;
		frame = 0;
	}*/

	glutPostRedisplay();
}

void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista

	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {

	case 'w':   //Movimientos de camara
	case 'W':
		objCamera.Move_Camera(CAMERASPEED + 0.2);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 0.2));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.4));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 0.4);
		break;

	case 'O':		//  
	case 'o':
		g_fanimacion ^= true; //Activamos/desactivamos la animac�on
		circuito = false;
		break;

	case 'i':		//  
	case 'I':
		circuito ^= true; //Activamos/desactivamos la animac�on
		g_fanimacion = false;
		break;

	case 'k':	
		//
	case 'K':
		puertaabrida = !puertaabrida;

		break;

	case 'p':
		//
	case 'P':
		ventanaabrida= !ventanaabrida;

		break;
	case 'l':
		//
	case 'L':
		aleteo = !aleteo;

		break;

	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;
	}

	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
	case GLUT_KEY_PAGE_UP:
		//pos_camY -= 0.5f;
		//pos_cam.y += 0.5f;
		//eye_cam.y += 0.5f;
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		//pos_camY += 0.5f;
		//pos_cam.y -= 0.5f;
		//eye_cam.y -= 0.5f;
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

	case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

	case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View(CAMERASPEED);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void menuKeyFrame(int id)
{
	switch (id)
	{
	case 0:	//Save KeyFrame
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}
		break;

	case 1:	//Play animation
		if (play == false && FrameIndex > 1)
		{

			resetElements();
			//First Interpolation
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;


	}
}


void menu(int id)
{

}

int main(int argc, char** argv)   // Main Function
{
	int submenu;

	glutInit(&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutInitWindowSize(500, 500);	// Tama�o de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow("Proyecto Laboratorio"); // Nombre de la Ventana
	//glutFullScreen     ( );         // Full Screen
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut funci�n de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut funci�n en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut funci�n de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	glutIdleFunc(animacion);

	submenu = glutCreateMenu(menuKeyFrame);
	glutAddMenuEntry("Guardar KeyFrame", 0);
	glutAddMenuEntry("Reproducir Animacion", 1);
	glutCreateMenu(menu);
	glutAddSubMenu("Animacion Monito", submenu);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();          // 

	return 0;
}
