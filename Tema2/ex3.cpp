/* 
   elemente: casa, acoperis, fereastra, copac, soare rotativ + raze, horn cu fum.
   fiecare obiect este desenat intr-o lista de display pentru eficienta
   animatia include rotatia soarelui si miscarea fumului
*/

#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <GL/freeglut.h>

/* variabile globale pentru id-urile listelor de display */
GLuint casaDL, acoperisDL, fereastraDL, copacDL, soareDL, hornDL, fumDL;

/* variabile pentru animatie */
GLfloat rotSun = 0.0f;    // unghiul de rotatie al soarelui
GLfloat fumOffset = 0.0f; // cat de sus s-a ridicat fumul

/* constanta pentru cercuri */
const double TWO_PI = 6.2831853;

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);

    /* lista pentru corpul casei - un dreptunghi simplu            */
    casaDL = glGenLists(1);       
    glNewList(casaDL, GL_COMPILE); 

    glColor3f(0.8, 0.5, 0.2); 
    glBegin(GL_POLYGON);      // dreptunghiul casei
    glVertex2i(-100, -50);
    glVertex2i(100, -50);
    glVertex2i(100, 100);
    glVertex2i(-100, 100);
    glEnd();

    glEndList(); 

    /* lista pentru acoperis - un triunghi                         */
    acoperisDL = glGenLists(1);
    glNewList(acoperisDL, GL_COMPILE);

    glColor3f(0.7, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2i(-120, 100);
    glVertex2i(120, 100);
    glVertex2i(0, 180);   // varful acoperisului
    glEnd();

    glEndList();

    /* lista pentru fereastra - un dreptunghi albastru             */
    fereastraDL = glGenLists(1);
    glNewList(fereastraDL, GL_COMPILE);

    glColor3f(0.2, 0.7, 1.0); 
    glBegin(GL_POLYGON);
    glVertex2i(-30, 10);
    glVertex2i(30, 10);
    glVertex2i(30, 60);
    glVertex2i(-30, 60);
    glEnd();

    glEndList();

    /* lista pentru copac (trunchi + coronament circular)          */
    copacDL = glGenLists(1);
    glNewList(copacDL, GL_COMPILE);

    /* trunchiul copacului - un dreptunghi maro */
    glColor3f(0.5, 0.2, 0.0);
    glBegin(GL_POLYGON);
    glVertex2i(-15, -50);
    glVertex2i(15, -50);
    glVertex2i(15, 40);
    glVertex2i(-15, 40);
    glEnd();

    /* coroana copacului - un cerc (triangle fan) */
    glColor3f(0.0, 0.6, 0.0); 
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(0, 100);  // centrul cercului
    for (int k = 0; k <= 20; k++)
    {
        float angle = TWO_PI * k / 20;
        glVertex2i(60 * cos(angle), 60 * sin(angle) + 40);
    }
    glEnd();

    glEndList();

    /* lista pentru soare - cerc + raze                           */
    soareDL = glGenLists(1);
    glNewList(soareDL, GL_COMPILE);

    /* cercul central al soarelui */
    glColor3f(1.0, 0.8, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(0, 0);   // centru
    for (int k = 0; k <= 40; k++)
    {
        float angle = TWO_PI * k / 40;
        glVertex2f(40 * cos(angle), 40 * sin(angle));
    }
    glEnd();

    /* razele soarelui - linii din centrul cercului spre exterior */
    glBegin(GL_LINES);
    glColor3f(1.0, 0.7, 0.0); 
    for (int k = 0; k < 16; k++)
    {
        float angle = TWO_PI * k / 16;
        float x = cos(angle);
        float y = sin(angle);

        glVertex2f(x * 45, y * 45); // inceput raza
        glVertex2f(x * 70, y * 70); // final raza
    }
    glEnd();

    glEndList();

    /* lista pentru hornul casei - dreptunghi                      */
    hornDL = glGenLists(1);
    glNewList(hornDL, GL_COMPILE);

    glColor3f(0.4, 0.2, 0.1);
    glBegin(GL_POLYGON);
    glVertex2i(60, 100);
    glVertex2i(90, 100);
    glVertex2i(90, 150);
    glVertex2i(60, 150);
    glEnd();

    glEndList();

    /* lista pentru o bulina de fum                               */
    fumDL = glGenLists(1);
    glNewList(fumDL, GL_COMPILE);

    glColor3f(0.7, 0.7, 0.7); 
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(0, 0);
    for (int k = 0; k <= 20; k++)
    {
        float angle = TWO_PI * k / 20;
        glVertex2f(20 * cos(angle), 20 * sin(angle));
    }
    glEnd();

    glEndList();
}

void displayFcn(void)
{
    /* golim ecranul */
    glClear(GL_COLOR_BUFFER_BIT);

    /* desenam casa bucata cu bucata */
    glCallList(casaDL);
    glCallList(acoperisDL);
    glCallList(fereastraDL);
    glCallList(hornDL);

    /* desenam copacul la stanga casei folosind transformari */
    glPushMatrix();
    glTranslatef(-200, -30, 0); // mutam copacul la stanga
    glCallList(copacDL);
    glPopMatrix();

    /* desenam soarele rotind intreaga lista */
    glPushMatrix();
    glTranslatef(200, 200, 0); // pozitia soarelui
    glRotatef(rotSun, 0, 0, 1); // rotire in jurul axei z
    glCallList(soareDL);
    glPopMatrix();

    /* desenam fumul care iese din horn prin 3 buline animate */
    glPushMatrix();
    glTranslatef(75, 150, 0); // punctul de plecare al fumului

    /* prima bulina - cea mai mare */
    glPushMatrix();
    glTranslatef(0, fumOffset, 0);
    glCallList(fumDL);
    glPopMatrix();

    /* a doua bulina - mai mica si mai sus */
    glPushMatrix();
    glTranslatef(10, fumOffset + 30, 0);
    glScalef(0.8, 0.8, 1);
    glCallList(fumDL);
    glPopMatrix();

    /* a treia bulina - cea mai mica si cea mai sus */
    glPushMatrix();
    glTranslatef(-10, fumOffset + 60, 0);
    glScalef(0.6, 0.6, 1);
    glCallList(fumDL);
    glPopMatrix();

    glPopMatrix();

    glFlush(); // afisare pe ecran
}

void timerFcn(int value)
{
    /* rotirea continua a soarelui */
    rotSun += 1.0f;
    if (rotSun >= 360.0f)
        rotSun -= 360.0f;

    /* animatie pentru fum - se ridica in sus */
    fumOffset += 0.5f;
    if (fumOffset > 120)
        fumOffset = 0;

    /* fortam redesenarea si reprogramam timer-ul */
    glutPostRedisplay();
    glutTimerFunc(16, timerFcn, 1);
}

void reshapeFcn(int w, int h)
{
    /* viewport-ul acopera toata fereastra */
    glViewport(0, 0, w, h);

    /* setam proiectia pentru coordonate 2d */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-350, 350, -350, 350);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Casa mea");

    init();

    glutDisplayFunc(displayFcn);
    glutReshapeFunc(reshapeFcn);
    glutTimerFunc(16, timerFcn, 1); // timer pentru animatie

    /* bucla principala */
    glutMainLoop();
    return 0;
}
