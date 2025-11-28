#include <windows.h>
#include <GL/freeglut.h>

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300, 300, -300, 300);
}

void drawSquare()
{
    // patrat centrat in origine, latura 30
    glBegin(GL_QUADS);
    glVertex2f(-15, -15);
    glVertex2f(15, -15);
    glVertex2f(15, 15);
    glVertex2f(-15, 15);
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // 1. patratul original (negru)
    glColor3f(0.0f, 0.0f, 0.0f);
    drawSquare();

    // 2. Mai intai scalare, apoi translatie
    //    T * S * patrat
    //    culoare: portocaliu
    glPushMatrix();
    glColor3f(1.0f, 0.5f, 0.0f);      
    glScalef(2.0f, 0.5f, 1.0f);       // scalare mai intai
    glTranslatef(100.0f, 100.0f, 0.0f); // apoi translatie
    drawSquare();
    glPopMatrix();


    // 3. Mai intai translatie, apoi scalare
    //    S * T * patrat
    //    culoare: albastra
    glPushMatrix();
    glColor3f(0.0f, 0.5f, 1.0f);        
    glTranslatef(100.0f, -100.0f, 0.0f); // translatie mai intai
    glScalef(2.0f, 0.5f, 1.0f);         // apoi scalare
    drawSquare();
    glPopMatrix();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("ordine transformari");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
