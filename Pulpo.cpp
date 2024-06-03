#define PROYECTO "Pulpo"

#include <iostream>	
#include <codebase.h>
#include <GL\freeglut.h>
#include <sstream> // Biblioteca de manejo de strings
#include <cmath> // Biblioteca matematica de C

using namespace std;
using namespace cb;

static const int tasaFPS = 40; // tasa que se quiere como maximo
static const double EulerConstant = std::exp(1.0);
static const int armLen = 20;
static const int armMaxDegree = 30;
static const int forearmMaxDegree = -20;
static const float handLen = 0.65f;
static const float platformRadius = 5.5f;
static const int pulpoRad = 10;
static const int artiRad = 5;
static const float platformHeigth = 2.5f;
static const int initTentacleHeigth = 7;
static const int pulpoSec = 25;
static const int huecoEscalera = 3;
static const int escaleraLen = (artiRad * 2) + platformHeigth + initTentacleHeigth;
static const float escaleraWidth = 1.5f;
static const int maquinaFundRad = 75;
static const int numBarandilla = 40;
static const int heigthBarandulla = 5;
static const int streetLen = 200;
static const int streetWidth = 40;
static const int streetLamp = 7;
static const int lamparaHeigth = 15;
static const int sombreroRadius = 15;
static const int sombreroHeigth = 20;
static const int sombreroDef = 25;
static int camType = 0;
static float pulpoScale = pulpoRad * 1.1f;


//el radio para el punto pulpoY[i] = pulpoRad - pulpoR[i]
static const float pulpoR[85] = {0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.04f, 0.08f, 0.20f, 0.48f, 0.68f, 1.30f, 1.67f, 2.11f, 2.59f, 3.04f, 3.39f, 3.75f, 3.90f, 4.06f, 4.07f, 4.09f, 4.08f,  4.11f,  4.10f,  4.09f,  4.07f, 4.072f,  4.05f,  4.01f,  3.95f,  3.89f,  3.83f,  3.73f,  3.65f,  3.58f,  3.51f,  3.51f,  3.56f,  3.72f,  3.83f,  4.00f,  4.16f,  4.35f,  4.52f,  4.65f,  4.83f,  5.00f,  5.25f,  5.44f,  5.62f,  5.84f,  6.06f,  6.33f,  6.66f,  7.00f,  7.30f,  7.55f,  7.83f,  8.14f,  8.60f,  8.99f,  9.24f,  9.50f,  9.76f, 10.00f};
static const float pulpoY[85] = {0.00f, 1.00f, 1.50f, 2.50f, 3.00f, 3.36f, 3.68f, 4.09f, 4.39f, 4.66f, 5.34f, 5.74f, 6.19f, 6.70f, 7.13f, 7.41f, 7.80f, 8.24f, 8.96f, 9.32f, 9.59f, 9.81f, 10.12f, 10.39f, 10.67f, 10.95f, 11.18f, 11.42f, 11.63f, 11.99f, 12.20f, 12.52f, 12.89f, 13.22f, 13.51f, 13.87f, 14.26f, 14.65f, 15.02f, 15.43f, 15.82f, 16.12f, 16.44f, 16.71f, 16.92f, 17.19f, 17.43f, 17.66f, 17.88f, 18.08f, 18.27f, 18.41f, 18.61f, 18.79f, 19.00f, 19.17f, 19.34f, 19.45f, 19.55f, 19.72f, 19.83f, 19.90f, 19.97f, 19.97f, 20.00f};

static GLuint estrella, esferaEstrella, cieloTop, cieloFrontBack, cieloLeftRight;
static GLuint pulpo, brazo, arti, tentaculo, escena, lampara, street, banco;
static GLuint mano, plataforma, vagon, ojo, escalera, maquina;


///////////////////////////VARAIBLES PARA ANIMAICONES///////////////////////////
//**********************************escalera**********************************//
//los FPS por el tiempo que dura la anim en sec
static const int escaleraInterval = tasaFPS * 5;
static float escaleraRotacion = 0.0f;

//*********************************plataforma*********************************//
static const float plataformaRotInc = 0.005f;
static int timeInterval = 4;
static float plataformaRotacion = 0.0f;
static float incRotacion = 0;

//*********************************tentaculos*********************************//
static const float antebrazoRotInc = 0.1;
static const int antebrazoMaxDegree = -20;
static float antebrazoRotacion[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

static const float brazoRotInc = 0.05;
static const int brazoMaxDegree = 30;
static float brazoRotacion[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

//**********************************maquinas**********************************//
static const float maquinaRotInc = 0.01;
static const float maquinaRotScale = 2;
static float maquinaRotacion = 0.0f;

//************************************ojo************************************//
static const float ojoRotScale = 0.1f;
static const float ojoRotInc = 0.01f;
static float ojoRotacion = 0.0f;

//********************************camara Init********************************//
static const float sombreroIncTra = 0.1f;
static const float sombreroRest = 15;
static float sombreroTra = 0.0f;

//********************************camara Rotacion********************************//
static const float velocidadElevacion = 4.0 / 1000; //4u en 1 ms
static const float velocidadRotacion = 10.0 / 1000; //4u en 1 ms
static const float radioRotacion = 175;
static const float iniCameraPosY = 10;
static const float R1 = 350;
static const float R2 = 200;
static const float d = 40;
static float camPos[3] = { 0.0f, 100, 300 };

//*******************************camara Perspectiva*******************************//
static float temp[3] = {0,0,0};
static float temp2[3] = { 0,0,0 };
static int initPos= 0;

//*******************************Camara Abrir y Carrar Apertura*******************************//
static const float camDegInterval = 5 * 1000;
static const float timeInCamType0 = 15 * 1000;
static const float timeInCamType1 = 10 * 1000;
static float camOpenDegree = 45;
static float razon = 0;

//**********************************Funciones**********************************//

float* traslationCam(float traX, float traY, float traZ, float fromX, float fromY, float fromZ) {
	float aux[3];
	aux[0] = fromX + traX;
	aux[1] = fromY + traY;
	aux[2] = fromZ + traZ;
	//cout << aux[0] << "  " << aux[1] << "  " << aux[2] << "  cam " << endl;
	return aux;
}

float* rotationXCam(float degree, float fromX, float fromY, float fromZ) {
	float d = (2 * PI * degree) / 360;
	float matrix[3][3] = {
		{1,0,0},
		{0,cos(d), -sin(d)},
		{0,sin(d), cos(d)}
	};
	float aux[3];

	aux[0] = matrix[0][0] * fromX +
		matrix[0][1] * fromY +
		matrix[0][2] * fromZ;

	aux[1] = matrix[1][0] * fromX +
		matrix[1][1] * fromY +
		matrix[1][2] * fromZ;

	aux[2] = matrix[2][0] * fromX +
		matrix[2][1] * fromY +
		matrix[2][2] * fromZ;

	return aux;
}

float* rotationYCam(float degree, float fromX, float fromY, float fromZ) {
	float d = (2 * PI * degree) / 360;
	float matrix[3][3] = {
		{cos(d),  0,sin(d)},
		{0,       1,     0},
		{-sin(d), 0, cos(d)}
	};
	float aux[3];

	aux[0] = matrix[0][0] * fromX +
		matrix[0][1] * fromY +
		matrix[0][2] * fromZ;

	aux[1] = matrix[1][0] * fromX +
		matrix[1][1] * fromY +
		matrix[1][2] * fromZ;

	aux[2] = matrix[2][0] * fromX +
		matrix[2][1] * fromY +
		matrix[2][2] * fromZ;
	//cout << aux[0] << "  " << aux[1] << "  " << aux[2] << "  cam " << endl;

	return aux;
}

float* rotationZCam(float degree, float fromX, float fromY, float fromZ) {
	float d = (2 * PI * degree) / 360;
	float matrix[3][3] = {
		{cos(d), -sin(d),0},
		{sin(d), cos(d),0},
		{0,0,1}
	};
	float aux[3];

	aux[0] = matrix[0][0] * fromX +
		matrix[0][1] * fromY +
		matrix[0][2] * fromZ;

	aux[1] = matrix[1][0] * fromX +
		matrix[1][1] * fromY +
		matrix[1][2] * fromZ;

	aux[2] = matrix[2][0] * fromX +
		matrix[2][1] * fromY +
		matrix[2][2] * fromZ;

	return aux;
}

float* scaleCam(float scaX, float scaY, float scaZ, float fromX, float fromY, float fromZ) {
	float matrix[3][3] = {
		{scaX,0,0},
		{0,scaY,0},
		{0,0,scaZ},
	};
	float aux[3];

	aux[0] = matrix[0][0] * fromX;
	aux[1] = matrix[1][1] * fromY;
	aux[2] = matrix[2][2] * fromZ;

	return aux;
}

float Sigmoid(float x) {
	float temp = 1.0 / (1 + pow(EulerConstant, -x));
	///cout << x << "   " << temp << endl;
	return temp;
}

float SombreroPolynomio(float x) {
	float poly[8] = { 8.5227947672478, -11.7565956129502,  5.1496165086278,  -1.0170900852501, 0.1073799433864, -0.006296245976, 0.0001931391537, -0.0000024142394 };
	if (x < 3 || x>20) {
		return 0;
	}
	float aux = x;
	float res = 0;
	for (int i = 0; i < 8; i++) {
		res += poly[i]*aux;
		aux *= x;
	}
	//cout << x << ": " << res << endl;

	return res;
}

float* EspirogramaFunction(float t) {
	//la formula esta en wikipedia
	float cord[2];
	cord[0] = (R1 - R2) * cos(t) + d * cos((R1 - R2) / R2 * t);
	cord[1] = (R1 - R2) * sin(t) - d * sin((R1 - R2) / R2 * t);
	return cord;
}

void muestraFPS()
// Calcula la frecuencia y la muestra en el título de la ventana
// cada segundo
{
	int ahora, tiempo_transcurrido;
	static int antes = 0;
	static int FPS = 0;
	stringstream titulo;
	//Cuenta de llamadas a esta función en el último segundo
	FPS++;
	ahora = glutGet(GLUT_ELAPSED_TIME); //Tiempo transcurrido desde el inicio
	tiempo_transcurrido = ahora - antes; //Tiempo transcurrido desde antes
	if (tiempo_transcurrido > 1000) { //Acaba de rebasar el segundo
		titulo << "FPS: " << FPS; //Se muestra una vez por segundo
		glutSetWindowTitle(titulo.str().c_str());
		antes = ahora; //Ahora ya es antes
		FPS = 0; //Reset del conteo
	}
}

void calCamPos() {
	float* camCord;
	float* pivCord;

	camCord = traslationCam((platformRadius * 2 * cos(0 * 2 * PI / 4 + 3 * PI / 2)),
		(platformHeigth)+6, (platformRadius * 2 * sin(0 * 2 * PI / 4 + 3 * PI / 2)), 0, 0, 0);
	pivCord = traslationCam((0), (platformHeigth)+6, (0), 0, 0, 0);

	camCord = rotationYCam(plataformaRotacion, camCord[0], camCord[1], camCord[2]);
	pivCord = rotationYCam(plataformaRotacion, pivCord[0], pivCord[1], pivCord[2]);

	camCord = traslationCam(0, artiRad, 0, camCord[0], camCord[1], camCord[2]);
	pivCord = traslationCam(0, artiRad, 0, pivCord[0], pivCord[1], pivCord[2]);

	camCord = traslationCam(armLen, 0, 0, camCord[0], camCord[1], camCord[2]);
	pivCord = traslationCam(armLen, 0, 0, pivCord[0], pivCord[1], pivCord[2]);

	camCord = rotationYCam(((1 + cos(antebrazoRotacion[0] - PI / 2)) * antebrazoMaxDegree / 2), camCord[0], camCord[1], camCord[2]);
	pivCord = rotationYCam(((1 + cos(antebrazoRotacion[0] - PI / 2)) * antebrazoMaxDegree / 2), pivCord[0], pivCord[1], pivCord[2]);

	camCord = rotationZCam(15 - ((1 + sin(antebrazoRotacion[0] - PI / 2)) * antebrazoMaxDegree / 2), camCord[0], camCord[1], camCord[2]);
	pivCord = rotationZCam(15 - ((1 + sin(antebrazoRotacion[0] - PI / 2)) * antebrazoMaxDegree / 2), pivCord[0], pivCord[1], pivCord[2]);

	camCord = traslationCam(armLen, 0, 0, camCord[0], camCord[1], camCord[2]);
	pivCord = traslationCam(armLen, 0, 0, pivCord[0], pivCord[1], pivCord[2]);

	camCord = rotationYCam(((1 + cos(antebrazoRotacion[0] - PI / 2)) * antebrazoMaxDegree / 2), camCord[0], camCord[1], camCord[2]);
	pivCord = rotationYCam(((1 + cos(antebrazoRotacion[0] - PI / 2)) * antebrazoMaxDegree / 2), pivCord[0], pivCord[1], pivCord[2]);

	camCord = rotationZCam(-30 + ((1 + sin(antebrazoRotacion[0] - PI / 2)) * antebrazoMaxDegree / 2), camCord[0], camCord[1], camCord[2]);
	pivCord = rotationZCam(-30 + ((1 + sin(antebrazoRotacion[0] - PI / 2)) * antebrazoMaxDegree / 2), pivCord[0], pivCord[1], pivCord[2]);

	camCord = traslationCam(armLen, 0, 0, camCord[0], camCord[1], camCord[2]);
	pivCord = traslationCam(armLen, 0, 0, pivCord[0], pivCord[1], pivCord[2]);

	camCord = rotationYCam(((1 + cos(brazoRotacion[0] - PI / 2)) * brazoMaxDegree / 6), camCord[0], camCord[1], camCord[2]);
	pivCord = rotationYCam(((1 + cos(brazoRotacion[0] - PI / 2)) * brazoMaxDegree / 6), pivCord[0], pivCord[1], pivCord[2]);

	camCord = rotationZCam(15 + ((1 + sin(brazoRotacion[0] - PI / 2)) * brazoMaxDegree / 2), camCord[0], camCord[1], camCord[2]);
	pivCord = rotationZCam(15 + ((1 + sin(brazoRotacion[0] - PI / 2)) * brazoMaxDegree / 2), pivCord[0], pivCord[1], pivCord[2]);

	camCord = traslationCam(((pulpoScale - 2) * 2 * cos(0 * 2 * PI / 8)), initTentacleHeigth,
		((pulpoScale - 2) * 2 * sin(0 * 2 * PI / 8)), camCord[0], camCord[1], camCord[2]);
	pivCord = traslationCam(((pulpoScale - 2) * 2 * cos(0 * 2 * PI / 8)), initTentacleHeigth,
		((pulpoScale - 2) * 2 * sin(0 * 2 * PI / 8)), pivCord[0], pivCord[1], pivCord[2]);

	camCord = scaleCam(0.75, 0.75, 0.75, camCord[0], camCord[1], camCord[2]);
	pivCord = scaleCam(0.75, 0.75, 0.75, pivCord[0], pivCord[1], pivCord[2]);

	camCord = rotationYCam(maquinaRotacion, camCord[0], camCord[1], camCord[2]);
	pivCord = rotationYCam(maquinaRotacion, pivCord[0], pivCord[1], pivCord[2]);

	temp[0] = camCord[0];
	temp[1] = camCord[1];
	temp[2] = camCord[2];

	temp2[0] = pivCord[0];
	temp2[1] = pivCord[1];
	temp2[2] = pivCord[2];
}

void cieloObject(float numX, float numY, float numZ, float lenX, float lenY, float lenZ) {

	float cieloIncY = 1.0 * lenY / numY;
	float cieloIncX = 1.0 * lenX / numX;
	float cieloIncZ = 1.0 * lenZ / numZ;

	glPushMatrix();

	glTranslatef(-lenX / 2.0, 0, -lenZ / 2.0);
	glPushMatrix();
	for (int y = 0; y < numY; y++) {
		for (int x = 0; x < numX; x++) {
			for (int z = 0; z < numZ; z++) {
				glPushMatrix();
				glTranslatef(
					(cieloIncX * x) + (float)(rand()) / ((float)(RAND_MAX / (cieloIncX * (x + 1) - (cieloIncX * (x))))),
					(cieloIncY * y) + (float)(rand()) / ((float)(RAND_MAX / (cieloIncY * (y + 1) - (cieloIncY * (y))))),
					(cieloIncZ * z) + (float)(rand()) / ((float)(RAND_MAX / (cieloIncZ * (z + 1) - (cieloIncZ * (z)))))
				);

				/*glTranslatef(
					(cieloIncX * x),
					(cieloIncY * y),
					(cieloIncZ * z)
				);*/
				glColor3f(1, 1, 1);
				glutSolidSphere(1, 20, 20);
				glPopMatrix();
			}
		}
	}
	glPopMatrix();
	glPopMatrix();
}

void init()
{
	cout << glGetString(GL_VERSION) << endl;

	//banco
	banco = glGenLists(1);
	glNewList(banco, GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 2);
	glScalef(13, 1, 2);
	glColor3f(0.50, 0.16, 0.00);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 5);
	glScalef(13, 1, 2);
	glColor3f(0.50, 0.16, 0.00);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2, 0.5);
	glRotatef(-90, 1, 0, 0);
	glScalef(13, 1, 1.5);
	glColor3f(0.50, 0.16, 0.00);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 4, 0.5);
	glRotatef(-90, 1, 0, 0);
	glScalef(13, 1, 1.5);
	glColor3f(0.50, 0.16, 0.00);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 6, 0.5);
	glRotatef(-90, 1, 0, 0);
	glScalef(13, 1, 1.5);
	glColor3f(0.50, 0.16, 0.00);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3, -1, 3);
	glScalef(1, 1, 6);
	glColor3f(0,0,0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3, -1, 3);
	glScalef(1, 1, 6);
	glColor3f(0,0,0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3, 2.9, -0.5);
	glScalef(1, 8.75, 1);
	glColor3f(0,0,0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3, 2.9, -0.5);
	glScalef(1, 8.75, 1);
	glColor3f(0,0,0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5,-2,2.25);
	glScalef(1.5, 3, 1.5);
	glColor3f(0.50, 0.16, 0.00);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, -2, 5.25);
	glScalef(1.5, 3, 1.5);
	glColor3f(0.50, 0.16, 0.00);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, -2, 2.25);
	glScalef(1.5, 3, 1.5);
	glColor3f(0.50, 0.16, 0.00);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, -2, 5.25);
	glScalef(1.5, 3, 1.5);
	glColor3f(0.50, 0.16, 0.00);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();
	glPopAttrib();
	glEndList();

	//cieloTop
	cieloTop = glGenLists(1);
	glNewList(cieloTop, GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	cieloObject(17, 3, 17, 1000, 50, 1000);
	glPopMatrix();
	glPopAttrib();
	glEndList();

	//cieloFrontBack
	cieloFrontBack = glGenLists(1);
	glNewList(cieloFrontBack, GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	cieloObject(17, 3, 5, 1000, 50, 300);
	glPopMatrix();
	glPopAttrib();
	glEndList();

	//cieloLeftRight
	cieloLeftRight = glGenLists(1);
	glNewList(cieloLeftRight, GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	cieloObject(5, 3, 17, 300, 50, 950);
	glPopMatrix();
	glPopAttrib();
	glEndList();

	//estrella esfera (Pract 4)
	estrella = glGenLists(1);
	glNewList(estrella, GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 3; i++) {
		glVertex3f((1.5f * cos(i * 2 * PI / 3 + PI / 2)), (1.5f * sin(i * 2 * PI / 3 + PI / 2)), 0);
		glVertex3f((1.5f * 0.7 * cos(i * 2 * PI / 3 + PI / 2)), (1.5f * 0.7 * sin(i * 2 * PI / 3 + PI / 2)), 0);
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 3; i++) {
		glVertex3f((1.5f * cos(i * 2 * PI / 3 + 3 * PI / 2)), (1.5f * sin(i * 2 * PI / 3 + 3 * PI / 2)), 0);
		glVertex3f((1.5f * 0.7 * cos(i * 2 * PI / 3 + 3 * PI / 2)), (1.5f * 0.7 * sin(i * 2 * PI / 3 + 3 * PI / 2)), 0);
	}
	glEnd();
	glPopMatrix();
	glPopAttrib();
	glEndList();

	//estrella dentro de la esfera
	esferaEstrella = glGenLists(1);
	glNewList(esferaEstrella, GL_COMPILE);
	glPushAttrib(GL_CURRENT_BIT);

	glPushMatrix();
	glColor3f(1,1,1);
	glutWireSphere(1.75f, 10, 10); // Dibuja la esfera

	glPushMatrix();
	glRotatef(0, 0, 1, 0);
	glColor3f(0.1f, 0.435f, 0.97f);
	glCallList(estrella);
	glPopMatrix();

	glPushMatrix();
	glRotatef(30, 0, 1, 0);
	glColor3f(0.152f, 0.733f, 0.878f);
	glCallList(estrella);
	glPopMatrix();

	glPushMatrix();
	glRotatef(60, 0, 1, 0);
	glColor3f(0.192f, 0.858f, 0.572f);
	glCallList(estrella);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glColor3f(0.105f, 0.945f, 0.094f);
	glCallList(estrella);
	glPopMatrix();

	glPushMatrix();
	glRotatef(120, 0, 1, 0);
	glColor3f(0.607f, 0.980f, 0.141f);
	glCallList(estrella);
	glPopMatrix();

	glPushMatrix();
	glRotatef(150, 0, 1, 0);
	glColor3f(1, 0.96f, 0.125f);
	glCallList(estrella);
	glPopMatrix();

	glPopMatrix();
	glPopAttrib();
	glEndList();

	//lampara
	lampara = glGenLists(1);
	glNewList(lampara, GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();

	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glColor3f(0.46, 0.46, 0.46);
	glutSolidCylinder(1, lamparaHeigth, 15, 5);


	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, lamparaHeigth, 2);
	glScalef(4, 1, 8);
	glColor3f(0.14, 0.15, 0.15);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, lamparaHeigth-2, 4);
	glCallList(esferaEstrella);
	glPopMatrix();


	glPopMatrix();
	glPopAttrib();
	glEndList();

	//street
	street = glGenLists(1);
	glNewList(street, GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();

	glPushMatrix();
	glScalef(streetWidth, 2, streetLen);
	glColor3f(0.55, 0.37, 0.23);
	glutSolidCube(1);
	glPopMatrix();

	for (int i = 0; i < streetLen; i += (streetLen * 1.0 / streetLamp)) {
		glPushMatrix();
		glTranslatef(
			((streetWidth / 2) - 2.5f),
			(1),
			(((streetLen / 2) - 5) - i)
		);
		glColor3f(1, 1, 1);
		glRotatef(-90, 0, 1, 0);
		glCallList(lampara);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(
			((-streetWidth / 2) + 2.5f),
			(1),
			(((streetLen / 2) - 5) - i)
		);
		glRotatef(90, 0, 1, 0);
		glColor3f(1, 1, 1);
		glCallList(lampara);
		glPopMatrix();

	}

	glPushMatrix();
	glTranslatef(-15, 5, -3);
	glRotatef(90, 0,1, 0);
	glCallList(banco);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, 5, -3);
	glRotatef(-90, 0, 1, 0);
	glCallList(banco);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 5, -61);
	glRotatef(90, 0, 1, 0);
	glCallList(banco);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, 5, -61);
	glRotatef(-90, 0, 1, 0);
	glCallList(banco);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 5, 55);
	glRotatef(90, 0, 1, 0);
	glCallList(banco);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, 5, 55);
	glRotatef(-90, 0, 1, 0);
	glCallList(banco);
	glPopMatrix();

	glPopMatrix();
	glPopAttrib();
	glEndList();

	//pulpo
	pulpo = glGenLists(1);
	glClear(GL_COLOR_BUFFER_BIT);
	glNewList(pulpo, GL_COMPILE);
	glPushAttrib(GL_ALL_ATTRIB_BITS);	

	glPushMatrix();
	glScalef(1.25f, 1.5, 1.25f);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.3f, ((3.0 + rand()) / (RAND_MAX / 3.01 - 3)) / 10, 1);
	glVertex3f(
		((pulpoRad) * sin(0 * 2 * PI / pulpoSec + PI / 2)),
		(0),
		((pulpoRad) * cos(0 * 2 * PI / pulpoSec + PI / 2))
	);
	int i;
	for (i = 0; i <= (pulpoSec - 1) / 2; i ++) {
		glColor3f(0.3f, ((3.0 + rand()) / (RAND_MAX / 3.01 - 3)) / 10, 1);
		glVertex3f(
			((pulpoRad) * sin(i * 2 * PI / pulpoSec + PI / 2)),
			(0),
			((pulpoRad) * cos(i * 2 * PI / pulpoSec + PI / 2))
		);
		glColor3f(0.3f, ((3.0 + rand()) / (RAND_MAX / 3.01 - 3)) / 10, 1);
		glVertex3f(
			((pulpoRad)*sin((pulpoSec - i) * 2 * PI / pulpoSec + PI / 2)),
			(0),
			((pulpoRad)*cos((pulpoSec - i) * 2 * PI / pulpoSec + PI / 2))
		);
	}
	if (pulpoSec/i * 1.0 == 2) {
		glColor3f(0.3f, ((3.0 + rand()) / (RAND_MAX / 3.01 - 3)) / 10, 1);
		glVertex3f(
			((pulpoRad)*sin(i * 2 * PI / pulpoSec + PI / 2)),
			(0),
			((pulpoRad)*cos(i * 2 * PI / pulpoSec + PI / 2))
		);
	}		
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	for (int y = 0; y < (sizeof(pulpoY) / sizeof(*pulpoY)) -1; y++) {
		for (int i = 0; i < pulpoSec; i++) {
			for (int p = 0; p < 2; p++) {
				glColor3f(0.3f, ((3.0 + rand()) / (RAND_MAX / 3.01 - 3)) / 10, 1);
				glVertex3f(
					((pulpoRad - pulpoR[y + p]) * sin(i * 2 * PI / pulpoSec + PI / 2)),
					(pulpoY[y + p]),
					((pulpoRad - pulpoR[y + p]) * cos(i * 2 * PI / pulpoSec + PI / 2))
				);
			}
		}
	}
	glEnd();
	glPopMatrix();

	glPopAttrib();
	glEndList();

	//vagon
	vagon = glGenLists(1);
	glNewList(vagon, GL_COMPILE);
	glPushAttrib(GL_CURRENT_BIT);

	glPushMatrix();
	glScalef(1, 1.5f, 1);

	glPushMatrix();
	glColor3f(0, 0, 0.4f);
	glScalef(1, 0.05f, 0.5f);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0.5f);
	glTranslatef(0, 1, 2);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 0.1f, 0.2f);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0.5f);
	glTranslatef(4.5f, 1, 0);
	glRotatef(90, 0, 0, 1);
	glScalef(0.2f, 0.1f, 0.5f);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0.5f);
	glTranslatef(-4.5f, 1, 0);
	glRotatef(90, 0, 0, 1);
	glScalef(0.2f, 0.1f, 0.5f);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0.5f);
	glTranslatef(-1.5f, 1, -2);
	glRotatef(90, 1, 0, 0);
	glScalef(0.7f, 0.1f, 0.2f);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-3.5f, 0.5f, 0.5f);
	glScalef(0.1f, 0.05f, 0.2f);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-1.5f, 0.5f, 0.5f);
	glScalef(0.1f, 0.05f, 0.2f);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0.5f, 0.5f, 0.5f);
	glScalef(0.1f, 0.05f, 0.2f);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(2.5f, 0.5f, 0.5f);
	glScalef(0.1f, 0.05f, 0.2f);
	glutSolidCube(10);
	glPopMatrix();


	glPopMatrix();
	glPopAttrib();
	glEndList();

	//brazo
	brazo = glGenLists(1);
	glNewList(brazo, GL_COMPILE);
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glColor3f(0, 0, 1);
	glutSolidCylinder(5, armLen, 20, 5);
	glPopMatrix();
	glPopAttrib();
	glEndList();

	//articulacion
	arti = glGenLists(1);
	glNewList(arti, GL_COMPILE);
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	glColor3f(0, 1, 0);
	glutSolidSphere(artiRad, 20, 20);
	glPopMatrix();
	glPopAttrib();
	glEndList();

}

void abrirOjos(int x) {
	float incOpen = 45.0 / ((camDegInterval * tasaFPS) / 1000);

	camOpenDegree += incOpen;
	if (camOpenDegree < 45) {
		glutTimerFunc(1000 / tasaFPS, abrirOjos, 0);
	}
	else {
		camOpenDegree = 45;
	}
	//cout << "a " << camOpenDegree << endl;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(camOpenDegree, razon, 1, 1000);
	glutPostRedisplay();
}

void cerrarOjos(int x) {
	float incOpen = 45.0 / ((camDegInterval*tasaFPS) / 1000);

	camOpenDegree -= incOpen;
	if (camOpenDegree > 0) {
		glutTimerFunc(1000 / tasaFPS, cerrarOjos, 0);
	}
	else {
		camOpenDegree = 0;
		camType = 1 - camType;
	}
	//cout << "c " << camOpenDegree << endl;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(camOpenDegree, razon, 1, 1000);
	glutPostRedisplay();
}

void camaraRotAnim(int x) {
	static int t = 0;
	t += 1;

	float dist = velocidadRotacion * t;
	float* aux = EspirogramaFunction(((PI / 2) + 0.08) + dist);
	camPos[0] = aux[0];
	camPos[1] = 10 + 45 * (1 + sin(((PI / 2)+0.25) + dist));
	camPos[2] = aux[1];
	//cout << camPos[0] << " --> " << camPos[1] << " --> " << camPos[2] << endl;

	glutTimerFunc(1000 / tasaFPS, camaraRotAnim, 0);
	glutPostRedisplay();
}

void camControler(int x) {
	//cout << "==================" << x << "==================" << endl;
	if (x == 0) {
		glutTimerFunc(timeInCamType0 + 1000, camControler, 1);
	}
	else if (x == 1) {
		glutTimerFunc(1, cerrarOjos, 0);
		glutTimerFunc(camDegInterval + 1000, camControler, 2);
	}
	else if (x == 2) {
		glutTimerFunc(1, abrirOjos, 0);
		glutTimerFunc(camDegInterval + 1000, camControler, 3);
	}
	else if (x == 3) {
		glutTimerFunc(timeInCamType1 + 1000, camControler, 4);
	}
	else if (x == 4) {
		glutTimerFunc(1, cerrarOjos, 0);
		glutTimerFunc(camDegInterval + 1000, camControler, 5);
	}
	else if (x == 5) {
		glutTimerFunc(1, abrirOjos, 0);
		glutTimerFunc(camDegInterval + 1000, camControler, 0);
	}
	glutPostRedisplay();

}

void camaraInitAnim(int x) {
	static int t = 0;
	float dist = velocidadElevacion * t;
	float aux = (90* Sigmoid(-10 + t / 20.0)) + iniCameraPosY;
    camPos[2] -= dist;
	camPos[1] = aux;
	t += 1;

	//cout << camPos[0] << " --> " << camPos[1] << " --> " << camPos[2] << endl;

	if (aux < 99.55) {
		glutTimerFunc(1000 / tasaFPS, camaraInitAnim, 0);
	}else {	
		glutTimerFunc(1000 / tasaFPS, camControler, 0);
		glutTimerFunc(1000 / tasaFPS, camaraRotAnim, 0);
	}
	glutPostRedisplay();
}

void sombreroAnim(int x) {
	static float t = -sombreroRest;
	sombreroTra = SombreroPolynomio(t);
	t += sombreroIncTra;
	if (t < 20+ sombreroRest) {
		glutTimerFunc(1000 / tasaFPS, sombreroAnim, 0);
	}else {
		t = 0;
		glutTimerFunc(1000 / tasaFPS, sombreroAnim, 0);
	}
	glutPostRedisplay();
}

void ojoAnim(int x){
	static float a = 0;

	ojoRotacion += ojoRotScale * (1.01+sin(a-PI/2));

	a += ojoRotInc;

	glutTimerFunc(1000 / tasaFPS, ojoAnim, 0);
	glutPostRedisplay();
}

void maquinaAnim(int x) {
	static float a = 0;

	maquinaRotacion += maquinaRotScale * (1+sin(a-PI/2));

	a += maquinaRotInc;

	glutTimerFunc(1000 / tasaFPS, maquinaAnim, 0);
	glutPostRedisplay();
}

void tentaculoAnim(int x) {
	static int t = 0;


	brazoRotacion[2] += brazoRotInc;
	antebrazoRotacion[2] += antebrazoRotInc;
	if (t > 15*1) {
		brazoRotacion[3] += brazoRotInc;
		antebrazoRotacion[3] += antebrazoRotInc;
	}
	if (t > 15*2) {
		brazoRotacion[4] += brazoRotInc;
		antebrazoRotacion[4] += antebrazoRotInc;
	}
	if (t > 15*3) {
		brazoRotacion[5] += brazoRotInc;
		antebrazoRotacion[5] += antebrazoRotInc;
	}
	if (t > 15*4) {
		brazoRotacion[6] += brazoRotInc;
		antebrazoRotacion[6] += antebrazoRotInc;
	}
	if (t > 15*5) {
		brazoRotacion[7] += brazoRotInc;
		antebrazoRotacion[7] += antebrazoRotInc;
	}
	if (t > 15*6) {
		brazoRotacion[0] += brazoRotInc;
		antebrazoRotacion[0] += antebrazoRotInc;
	}
	if (t > 15*7) {
		brazoRotacion[1] += brazoRotInc;
		antebrazoRotacion[1] += antebrazoRotInc;
	}

	t += 1;

	glutTimerFunc(1000 / tasaFPS, tentaculoAnim, 1);
	glutPostRedisplay();
}

void plataformaAnim(int x) {
	static int t = 0;
	static float a = 0.0f;
	//cout << t << endl;
	
	a += plataformaRotInc;
	t += timeInterval;
	float time = t / 1000.0;
	incRotacion = (1.0 / 2) * cos(a) * 2 * time;


	plataformaRotacion += incRotacion;

	if (t >= 1750) {
		timeInterval *= -1;
		glutTimerFunc(1000 / tasaFPS, plataformaAnim, 1);
	}
	else if (t < 1750 && x == 0) {
		glutTimerFunc(1000 / tasaFPS, plataformaAnim, 0);
	}
	else if (t <= 750 && x == 1) {
		timeInterval *= -1;
		glutTimerFunc(1000 / tasaFPS, plataformaAnim, 1);
	}
	else{
		glutTimerFunc(1000 / tasaFPS, plataformaAnim, 1);
	}
	glutPostRedisplay();
}

void escaleraAnim(int a) {
	float incRotacion = 90.0 / escaleraInterval;

	escaleraRotacion += incRotacion;

	if (escaleraRotacion < 90-0.002) {
		glutTimerFunc(1000 / tasaFPS, escaleraAnim, 0);
	}
	else {
		glutTimerFunc(1000 / tasaFPS, plataformaAnim, 0);
		glutTimerFunc(1000 / tasaFPS, tentaculoAnim, 0);
		glutTimerFunc(1000 / tasaFPS, maquinaAnim, 0);
		glutTimerFunc(1000 / tasaFPS, sombreroAnim, 0);
		glutTimerFunc(1000 / tasaFPS, ojoAnim, 0); 
	}
	glutPostRedisplay();
}

void escaleraObject() {
	glPushMatrix();

	glRotatef(escaleraRotacion, 1, 0, 0);
	glPushMatrix();

	glTranslatef(-2, -(escaleraLen / 2.0), 0);
	glPushMatrix();

	glPushMatrix();
	glScalef(1, escaleraLen, escaleraWidth);
	glColor3f(0.5f, 0, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4, 0, 0);
	glScalef(1, escaleraLen, escaleraWidth);
	glColor3f(0.5f, 0, 0);
	glutSolidCube(1);
	glPopMatrix();

	for (int i = 0; i < escaleraLen / huecoEscalera * 1.0; i++) {
		glPushMatrix();
		glTranslatef(2, (-escaleraLen / 2) + ((huecoEscalera * i)) + 2, 0);
		glScalef(3, 1, escaleraWidth);
		glColor3f(0.5f, 0.5f, 0);
		glutSolidCube(1);
		glPopMatrix();
	}
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}

void plataformaObject() {
	glPushMatrix();

	glRotatef(plataformaRotacion, 0, 1, 0);
	glPushMatrix();

	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glColor3f(0.5f, 0, 0);
	glutSolidCylinder(platformRadius * 2, platformHeigth, 20, 2);
	glPopMatrix();

	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glTranslatef(
			(platformRadius * 1.25f * cos(i * 2 * PI / 4 + 3 * PI / 2)),
			(platformHeigth),
			(platformRadius * 1.25f * sin(i * 2 * PI / 4 + 3 * PI / 2))
		);
		glRotatef(180+(i * -90), 0, 1, 0);
		glCallList(vagon);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(
			(platformRadius * 2 * cos(PI / 4 + (i * 2 * PI / 4))),
			(platformHeigth - (escaleraWidth / 2) - 0.5f),
			(platformRadius * 2 * sin(PI / 4 + (i * 2 * PI / 4)))
		);
		glRotatef(45 + (i* -90), 0, 1, 0);
		escaleraObject();
		glPopMatrix();
	}
	glPopMatrix();

	glPopMatrix();
}

void tentaculoObject(int k) {
	glPushMatrix();

	glRotatef(15 + ((1 + sin(brazoRotacion[k] - PI / 2)) * brazoMaxDegree / 2), 0, 0, 1);
	glRotatef(((1 + cos(brazoRotacion[k] - PI / 2)) * brazoMaxDegree / 6), 0, 1, 0);
	glPushMatrix();

	glCallList(arti);				//arti 1
	glCallList(brazo);				//brazo 1

	glTranslatef(armLen, 0, 0);
	glRotatef(-30 + ((1 + sin(antebrazoRotacion[k] - PI / 2)) * antebrazoMaxDegree / 2), 0, 0, 1);
	glRotatef(((1 + cos(antebrazoRotacion[k] - PI / 2)) * antebrazoMaxDegree / 2), 0, 1, 0);
	glPushMatrix();
	glCallList(arti);				//arti 2 
	glCallList(brazo);				//brazo 2

	glTranslatef(armLen, 0, 0);
	glRotatef(15 - ((1 + sin(antebrazoRotacion[k] - PI / 2)) * antebrazoMaxDegree / 2), 0, 0, 1);
	glRotatef(((1 + cos(antebrazoRotacion[k] - PI / 2)) * antebrazoMaxDegree / 2), 0, 1, 0);

	glPushMatrix();

	glPushMatrix();
	glColor3f(0, 1, 1);
	glCallList(arti);				//arti 3
	glScalef(1, handLen, 1);		
	glCallList(brazo);				//brazo 3
	glPopMatrix();

	glTranslatef(armLen, 0, 0);
	glPushMatrix();

	glPushMatrix();
	glCallList(arti);				//arti 4

	glTranslatef(0, artiRad, 0);
	plataformaObject();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
}

void ojoObject() {
	glPushMatrix();

	glPushMatrix();
	glScalef(1, 1.35f, 0.25f);
	glColor3f(1, 1, 1);
	glutSolidSphere(3.5f, 15, 15);
	glPopMatrix();

	glTranslatef(
		(1 * cos(ojoRotacion)),
		(2 * sin(ojoRotacion)),
		(0)
	);
	glPushMatrix();
	glTranslatef(0, 0, 1);
	glColor3f(0, 0, 0);
	glutSolidSphere(2, 15, 15);
	glPopMatrix();

	glPopMatrix();
}

void sombreroObject() {
	glPushMatrix();

	glTranslatef(0, sombreroTra, 0);
	glPushMatrix();

	glRotatef(-90, 1, 0, 0);
	glColor3f(0.52,0,0);
	glutSolidCylinder(sombreroRadius * 0.8, sombreroHeigth, sombreroDef, 5);
	glTranslatef(0,0,-2);
	glColor3f(0, 0, 0);
	glutSolidCylinder(sombreroRadius, 5, sombreroDef, 5);

	glPopMatrix();

	glPopMatrix();
}

void maquinaObject(){
	glPushMatrix();

	glRotatef(maquinaRotacion, 0, 1, 0);
	glPushMatrix();

	glScalef(0.75f, 0.75f, 0.75f);
	glPushMatrix();

	glScalef(2,2,2);

	glPushMatrix();
	glTranslatef(-3, 20, pulpoScale * 0.7);
	glRotatef(-15, 0, 1, 0);
	glScalef(0.8f, 0.8f, 0.8f);
	ojoObject();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2, 29, 0);
	glRotatef(-20, 0, 0, 1);
	glScalef(0.2f, 0.2f, 0.2f);
	sombreroObject();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3, 20, pulpoScale * 0.7);
	glRotatef(180, 0, 0, 1);
	glRotatef(-15, 0, 1, 0);
	glScalef(0.8f, 0.8f, 0.8f);
	ojoObject();
	glPopMatrix();

	glCallList(pulpo);
	glPopMatrix();

	for (int i = 0; i < 8; i++) {
		glPushMatrix();
		glTranslatef(
			((pulpoScale - 2) * 2 * cos(i * 2 * PI / 8 )),
			(initTentacleHeigth),
			((pulpoScale - 2) * 2 * sin(i * 2 * PI / 8 ))
		);
		glRotatef(0 - i * 360 / 8, 0, 1, 0);
		tentaculoObject(i);
		glPopMatrix();
	}

	glPopMatrix();
	glPopMatrix();
}

void escenaObject() {
	glPushMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glColor3f(0.55, 0.37, 0.23);
	glutSolidCylinder(maquinaFundRad, 2, numBarandilla, 5);
	glPopMatrix();

	maquinaObject();

	glPushMatrix();
	glTranslatef(0, heigthBarandulla, 0);
	glRotatef(90, 1, 0, 0);
	glColor3f(0.14, 0.15, 0.15);
	glutSolidTorus(1, maquinaFundRad - 1, 10, numBarandilla);
	glPopMatrix();

	for (int i = 0; i < numBarandilla; i++) {
		glPushMatrix();
		glTranslatef(
			((maquinaFundRad - 1) * cos(i * 2 * PI / numBarandilla + 3 * PI / 2)),
			(2.5 + (heigthBarandulla / 2 * 1.0)),
			((maquinaFundRad - 1) * sin(i * 2 * PI / numBarandilla + 3 * PI / 2))
		);
		glRotatef(90, 1, 0, 0);
		glColor3f(0.14, 0.15, 0.15);
		glutSolidCylinder(1, heigthBarandulla, 5, 10);
		glPopMatrix();
	}

	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glRotatef(90 * i, 0, 1, 0);
		glTranslatef(
			0, 
			-1, 
			maquinaFundRad + (streetLen / 2) - 5
		);
		glCallList(street);
		glPopMatrix();
	}

	glPushMatrix();
	glTranslatef(0, -1, maquinaFundRad + (streetLen / 2) - 5);
	glCallList(street);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 150, 0);
	glCallList(cieloTop);
	cieloObject(4,4,4, 1000, 50, 1000);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -475);
	glRotatef(-90, 1, 0, 0);
	glCallList(cieloFrontBack);
	cieloObject(3, 3, 3, 1000, 50, 300);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 0, 475);
	glRotatef(-90, 1, 0, 0);
	glCallList(cieloFrontBack);
	cieloObject(3, 3, 3, 1000, 50, 300);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-475, 0, 0);
	glRotatef(-90, 0, 0, 1);
	glCallList(cieloLeftRight);
	cieloObject(3, 3, 3, 300, 50, 950);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(475, 0, 0);
	glRotatef(-90, 0, 0, 1);
	glCallList(cieloLeftRight);
	cieloObject(3, 3, 3, 300, 50, 950);
	glPopMatrix();

	/*
	
	glPushMatrix();
	glTranslatef(0, 175, 0);
	glScalef(1000, 50, 1000);
	glColor3f(1, 0, 1);
	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -475);
	glRotatef(-90, 1, 0, 0);
	glScalef(1000, 50, 300);
	glColor3f(0, 1, 1);
	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 475);
	glRotatef(-90, 1, 0, 0);
	glScalef(1000, 50, 300);
	glColor3f(0, 1, 1);
	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-475, 0, 0);
	glRotatef(-90, 0, 0, 1);
	glScalef(300, 50, 900);
	glColor3f(0, 0, 1);
	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(475, 0, 0);
	glRotatef(-90, 0, 0, 1);
	glScalef(300, 50, 900);
	glColor3f(0, 0, 1);
	glutWireCube(1);
	glPopMatrix();
	*/

	glPushMatrix();
	glTranslatef(0, -1.5, 0);
	glRotatef(-90, 1, 0, 0);
	glColor3f(0, 0.68, 0);
	glutSolidCylinder(300, 1, 50, 5);
	glPopMatrix();

	glPopMatrix();
}

// Funcion de atencion al evento de dibujo
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);

	if (camType == 1) {
		gluLookAt(temp[0], temp[1], temp[2], temp2[0], temp2[1], temp2[2], 0, 1,0);
	}
	else {
		gluLookAt(camPos[0], camPos[1], camPos[2], 0, 25, 0, 0, 1, 0);
	}
	escenaObject();
	calCamPos();
	muestraFPS();
	glutSwapBuffers();
}

// este es el codigo del seminario
void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	razon = (float)w / h;
	gluPerspective(camOpenDegree, razon, 1, 1000);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);

	glutCreateWindow(PROYECTO);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(1000 / tasaFPS, camaraInitAnim, 0);
	glutTimerFunc(1000 / tasaFPS, escaleraAnim, 0);

	init();
	glutMainLoop();
}
