#include <windows.h>
#include <GL/freeglut.h>
#include <math.h>

// pozitia patratului pe axa ox
float x_pos = 50.0f;

// unghiul de rotatie
float angle = 0.0f;

// viteza miscarii 
float speed = 0.08f;

// latura patratului
float side = 50.0f;

// indicator daca animatia a inceput sau nu
bool started = false;

void init(void)
{
    // culoarea de fundal: alb
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void reshape(int w, int h)
{
    // zona de desenare
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0.0, 800.0, 0.0, 600.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // axa care trece prin centrul patratului
    glColor3f(0.0f, 0.0f, 0.0f);   
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 100.0f);   
    glVertex2f(800.0f, 100.0f);
    glEnd();

    glPushMatrix();

    // translatie: mutam patratul pe axa ox
    glTranslatef(x_pos, 100.0f, 0.0f);

    // rotim patratul in jurul centrului
    glRotatef(angle, 0, 0, 1);

    glColor3f(1.0f, 0.0f, 0.0f);

    // desenam patratul
    glBegin(GL_QUADS);
    glVertex2f(-side / 2, -side / 2);
    glVertex2f(side / 2, -side / 2);
    glVertex2f(side / 2, side / 2);
    glVertex2f(-side / 2, side / 2);
    glEnd();

    glPopMatrix();

    glutSwapBuffers();
}

void idle(void)
{
    // daca animatia nu a inceput, nu facem nimic
    if (!started) return;

    // deplasare pe axa ox
    x_pos += speed;

    // daca iese din ecran, revine din partea opusa
    if (x_pos > 850) x_pos = -50;
    if (x_pos < -50) x_pos = 850;

    // rotatia sincronizata cu miscarea
    angle -= speed * (360.0f / (4.0f * side));

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    // actiune doar la apasare
    if (state != GLUT_DOWN) return;

    // primul click porneste animatia spre dreapta
    if (!started)
    {
        started = true;
        speed = fabs(speed);       // directie spre dreapta
        glutIdleFunc(idle);        
    }
    else
    {
        // click-urile urmatoare inverseaza directia
        speed = -speed;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Patrat rostogolit pe axa Ox");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
