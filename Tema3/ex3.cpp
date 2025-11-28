#include <windows.h>
#include <GL/freeglut.h>
#include <math.h>

// liste de display
GLuint disp_star;
GLuint disp_planet;
GLuint disp_moon;

// unghiurile de rotatie
float rot_planet = 0.0f;
float rot_moon = 0.0f;

// initializare obiecte in liste de display
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // lista pentru stea (un disc simplu)
    disp_star = glGenLists(1);
    glNewList(disp_star, GL_COMPILE);
    glColor3f(1.0, 1.0, 0.0);    
    glBegin(GL_POLYGON);
    for (int i = 0; i < 40; i++)
    {
        float a = i * 2 * 3.14159 / 40;
        glVertex2f(30 * cos(a), 30 * sin(a));
    }
    glEnd();
    glEndList();

    // lista pentru planeta (disc albastru)
    disp_planet = glGenLists(1);
    glNewList(disp_planet, GL_COMPILE);
    glColor3f(0.2, 0.4, 1.0);   
    glBegin(GL_POLYGON);
    for (int i = 0; i < 40; i++)
    {
        float a = i * 2 * 3.14159 / 40;
        glVertex2f(20 * cos(a), 20 * sin(a));
    }
    glEnd();
    glEndList();

    // lista pentru satelit (disc gri mic)
    disp_moon = glGenLists(1);
    glNewList(disp_moon, GL_COMPILE);
    glColor3f(0.6, 0.6, 0.6);  
    glBegin(GL_POLYGON);
    for (int i = 0; i < 40; i++)
    {
        float a = i * 2 * 3.14159 / 40;
        glVertex2f(8 * cos(a), 8 * sin(a));
    }
    glEnd();
    glEndList();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300, 300, -300, 300);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // steaua (centrul sistemului)
    glPushMatrix();
    glCallList(disp_star); // steaua ramane fixa
    glPopMatrix();

    // planeta care orbiteaza steaua
    glPushMatrix();
    glRotatef(rot_planet, 0, 0, 1);  // rotatie in jurul stelei
    glTranslatef(150, 0, 0);         // raza orbitei planetei
    glCallList(disp_planet);

    // satelitul care orbiteaza planeta
    glPushMatrix();
    glRotatef(rot_moon, 0, 0, 1);  // rotatie in jurul planetei
    glTranslatef(40, 0, 0);        // raza orbitei satelitului
    glCallList(disp_moon);
    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

void idle(void)
{
    // miscare continua
    rot_planet += 0.015f;
    rot_moon += 0.015f;

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Minisistem solar");

    init();

    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}
