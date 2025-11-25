#include <windows.h>
#include <gl/freeglut.h>

void init()
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 400, 0, 400);
}

void desen()
{
    glClear(GL_COLOR_BUFFER_BIT);
    // POLIGON CONVEX - gradient intern (prin culori pe varfuri)
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0);     glVertex2f(60, 300);    // rosu
    glColor3f(1, 0.5, 0);   glVertex2f(120, 350);   // portocaliu
	glColor3f(1, 1, 0);     glVertex2f(180, 330);   // galben
	glColor3f(0.5, 1, 0);   glVertex2f(200, 270);   // verde spre galben
    glColor3f(0, 1, 0);     glVertex2f(130, 250);   // verde
    glEnd();

    // POLIGON CONCAV - gradient intern (prin culori pe varfuri)
    // POLIGON CONCAV - gradient ALB -> ALBASTRU
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);   glVertex2f(260, 260);   // alb
    glColor3f(1, 1, 1);   glVertex2f(330, 310);   // alb
    glColor3f(0, 0, 1);   glVertex2f(380, 250);   // albastru
    glColor3f(0, 0, 1);   glVertex2f(330, 230);   // albastru
    glColor3f(0, 0, 1);   glVertex2f(350, 180);   // albastru
    glColor3f(1, 1, 1);   glVertex2f(290, 190);   // alb 
    glEnd();


    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Poligoane cu gradient in interior");
    init();
    glutDisplayFunc(desen);
    glutMainLoop();
    return 0;
}
