#include <GL/glut.h>
#include <string>

void drawText(float x, float y, float z, const char* text)
{
    glRasterPos3f(x, y, z);
    while (*text)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text++);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // TRIUNGHIUL ABC – fata
  
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);

    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 0.8f, 0.2f);
    glVertex3f(-0.6f, -0.3f, 0.0f);  // A
    glVertex3f(-0.1f, -0.3f, 0.0f);  // B
    glVertex3f(-0.35f, 0.3f, 0.0f);  // C
    glEnd();

    glColor3f(0, 0, 0);

    // etichete ABC
    drawText(-0.62f, -0.35f, 0.0f, "A");   // sub varf
    drawText(-0.12f, -0.35f, 0.0f, "B");   // sub varf
    drawText(-0.37f, 0.35f, 0.0f, "C");   // deasupra varf

    // TRIUNGHIUL DEF – spate

    glPolygonMode(GL_FRONT, GL_LINE);
    glPolygonMode(GL_BACK, GL_FILL);

    glBegin(GL_TRIANGLES);
    glColor3f(0.8f, 0.3f, 0.3f);
    glVertex3f(0.6f, -0.3f, 0.0f);   // D
    glVertex3f(0.35f, 0.3f, 0.0f);   // E
    glVertex3f(0.1f, -0.3f, 0.0f);   // F
    glEnd();

    glColor3f(0, 0, 0);

    // etichete DEF
    drawText(0.62f, -0.35f, 0.0f, "D");
    drawText(0.33f, 0.35f, 0.0f, "E");
    drawText(0.08f, -0.35f, 0.0f, "F");

    glutSwapBuffers();
}

void init()
{
    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Triunghiuri vazute din fata(ABC) si din spate(DEF)");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
