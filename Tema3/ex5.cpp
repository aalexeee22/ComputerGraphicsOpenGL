/* casa cu textura pe fum si textura pe coroana copacului
   include soare rotativ si fum animat
*/

#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <GL/freeglut.h>

GLuint casaDL, acoperisDL, fereastraDL, copacDL, copacFrunzeDL;
GLuint soareDL, hornDL, fumDL;

GLuint textureID;        /* textura pentru fum */
GLuint texturaFrunzeID;  /* textura pentru coroana copacului */

GLfloat rotSun = 0.0f;     /* unghi rotatie soare */
GLfloat fumOffset = 0.0f;  /* deplasare fum pe verticala */

float texShift = 0.0f;     /* deplasare textura fum */

const double TWO_PI = 6.2831853;

unsigned char textura[16][16][3];
unsigned char texturaFrunze[16][16][3];

/* generare textura fum (pattern in patrate 16x16) */
void generareTextura()
{
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 16; j++)
        {
            int c = ((i / 4 + j / 4) % 2) * 180;
            textura[i][j][0] = c;
            textura[i][j][1] = 200 - c / 3;
            textura[i][j][2] = 255;
        }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 16, 16, 0,
        GL_RGB, GL_UNSIGNED_BYTE, textura);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

/* generare textura pentru coroana copacului (carouri verzi) */
void generareTexturaFrunze()
{
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 16; j++)
        {
            int c = ((i / 4 + j / 4) % 2);

            if (c == 0)
            {
                texturaFrunze[i][j][0] = 0;
                texturaFrunze[i][j][1] = 160;
                texturaFrunze[i][j][2] = 0;
            }
            else
            {
                texturaFrunze[i][j][0] = 0;
                texturaFrunze[i][j][1] = 80;
                texturaFrunze[i][j][2] = 0;
            }
        }

    glGenTextures(1, &texturaFrunzeID);
    glBindTexture(GL_TEXTURE_2D, texturaFrunzeID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 16, 16, 0,
        GL_RGB, GL_UNSIGNED_BYTE, texturaFrunze);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);

    generareTextura();
    generareTexturaFrunze();

    /* casa */
    casaDL = glGenLists(1);
    glNewList(casaDL, GL_COMPILE);
    glColor3f(0.8, 0.5, 0.2);
    glBegin(GL_POLYGON);
    glVertex2i(-100, -50);
    glVertex2i(100, -50);
    glVertex2i(100, 100);
    glVertex2i(-100, 100);
    glEnd();
    glEndList();

    /* acoperis */
    acoperisDL = glGenLists(1);
    glNewList(acoperisDL, GL_COMPILE);
    glColor3f(0.7, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2i(-120, 100);
    glVertex2i(120, 100);
    glVertex2i(0, 180);
    glEnd();
    glEndList();

    /* fereastra */
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

    /* trunchi copac */
    copacDL = glGenLists(1);
    glNewList(copacDL, GL_COMPILE);
    glColor3f(0.5, 0.2, 0.0);
    glBegin(GL_POLYGON);
    glVertex2i(-15, -50);
    glVertex2i(15, -50);
    glVertex2i(15, 40);
    glVertex2i(-15, 40);
    glEnd();
    glEndList();

    /* coroana copac texturata */
    copacFrunzeDL = glGenLists(1);
    glNewList(copacFrunzeDL, GL_COMPILE);

    glBindTexture(GL_TEXTURE_2D, texturaFrunzeID);

    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5, 0.5);
    glVertex2i(0, 100);

    for (int k = 0; k <= 20; k++)
    {
        float a = TWO_PI * k / 20;
        float x = 60 * cos(a);
        float y = 60 * sin(a) + 40;

        glTexCoord2f((x + 60) / 120.0, (y + 20) / 120.0);
        glVertex2f(x, y);
    }
    glEnd();

    glEndList();

    /* soare */
    soareDL = glGenLists(1);
    glNewList(soareDL, GL_COMPILE);

    glColor3f(1.0, 0.8, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(0, 0);
    for (int k = 0; k <= 40; k++)
    {
        float a = TWO_PI * k / 40;
        glVertex2f(40 * cos(a), 40 * sin(a));
    }
    glEnd();

    glColor3f(1.0, 0.7, 0.0);
    glBegin(GL_LINES);
    for (int k = 0; k < 16; k++)
    {
        float a = TWO_PI * k / 16;
        glVertex2f(45 * cos(a), 45 * sin(a));
        glVertex2f(70 * cos(a), 70 * sin(a));
    }
    glEnd();

    glEndList();

    /* horn */
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

    /* fum texturat */
    fumDL = glGenLists(1);
    glNewList(fumDL, GL_COMPILE);

    glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5, 0.5);
    glVertex2i(0, 0);

    for (int k = 0; k <= 20; k++)
    {
        float a = TWO_PI * k / 20;
        float x = 20 * cos(a);
        float y = 20 * sin(a);

        glTexCoord2f((x + 20) / 40.0, (y + 20) / 40.0);
        glVertex2f(x, y);
    }
    glEnd();

    glEndList();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-350, 350, -350, 350);
}

/* afisare scena */
void displayFcn(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glCallList(casaDL);
    glCallList(acoperisDL);
    glCallList(fereastraDL);
    glCallList(hornDL);

    /* copac cu textura pe coroana */
    glPushMatrix();
    glTranslatef(-200, -30, 0);
    glCallList(copacDL);

    glEnable(GL_TEXTURE_2D);
    glCallList(copacFrunzeDL);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    /* soare */
    glPushMatrix();
    glTranslatef(200, 200, 0);
    glRotatef(rotSun, 0, 0, 1);
    glCallList(soareDL);
    glPopMatrix();

    /* aplicare transformare textura fum */
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glTranslatef(texShift, 0.0f, 0.0f);   /* textura se deplaseaza pe orizontala */
    glMatrixMode(GL_MODELVIEW);

    /* fum texturat animat */
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(75, 150, 0);

    glPushMatrix();
    glTranslatef(0, fumOffset, 0);
    glCallList(fumDL);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, fumOffset + 30, 0);
    glScalef(0.8, 0.8, 1);
    glCallList(fumDL);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10, fumOffset + 60, 0);
    glScalef(0.6, 0.6, 1);
    glCallList(fumDL);
    glPopMatrix();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    /* resetare matrice textura */
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
}

/* actualizare animatie */
void timerFcn(int value)
{
    rotSun += 1.0f;
    if (rotSun >= 360) rotSun = 0;

    fumOffset += 0.5f;
    if (fumOffset > 120) fumOffset = 0;

    texShift += 0.01f;      /* avansare textura fum */
    if (texShift > 1.0f)
        texShift = 0.0f;

    glutPostRedisplay();
    glutTimerFunc(16, timerFcn, 1);
}

void reshapeFcn(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-350, 350, -350, 350);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(700, 700);
    glutCreateWindow("casa cu fum si coroana texturate");

    init();

    glutDisplayFunc(displayFcn);
    glutReshapeFunc(reshapeFcn);
    glutTimerFunc(16, timerFcn, 1);

    glutMainLoop();
    return 0;
}
