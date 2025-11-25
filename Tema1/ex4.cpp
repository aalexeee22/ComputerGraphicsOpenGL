#include <windows.h>
#include <gl/freeglut.h>
#include <string.h>

// functie pentru desenarea textului pe ecran
void drawText(const char* text, float x, float y)
{
    glRasterPos2f(x, y);
    for (int i = 0; i < strlen(text); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
}
// initializare fereastra si sistem de coordonate
void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);
}

void desen(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // coordonatele cubului 2D proiectat
    int bx = 120, by = 220;
    int size = 120;

    // vectori cu pozitiile celor 8 varfuri ale cubului
    float x[8] = {
        bx, bx + size, bx + size, bx,
        bx + 40, bx + size + 40, bx + size + 40, bx + 40
    };

    float y[8] = {
        by, by, by - size, by - size,
        by + 40, by + 40, by - size + 40, by - size + 40
    };

    // culori RGB pentru fiecare varf al cubului
    float r[8], g[8], b[8];

    r[0] = 0; g[0] = 1; b[0] = 1; // Cyan
    r[1] = 1; g[1] = 1; b[1] = 1; // White
    r[2] = 1; g[2] = 1; b[2] = 0; // Yellow
    r[3] = 0; g[3] = 1; b[3] = 0; // Green
    r[4] = 0; g[4] = 0; b[4] = 1; // Blue
    r[5] = 1; g[5] = 0; b[5] = 1; // Magenta
    r[6] = 1; g[6] = 0; b[6] = 0; // Red
    r[7] = 0; g[7] = 0; b[7] = 0; // Black

    // desenarea fetelor cublui cu triunghiuri
    glBegin(GL_TRIANGLES);

    // fata din spate
    glColor3f(r[0], g[0], b[0]); glVertex2f(x[0], y[0]);
    glColor3f(r[1], g[1], b[1]); glVertex2f(x[1], y[1]);
    glColor3f(r[2], g[2], b[2]); glVertex2f(x[2], y[2]);

    glColor3f(r[0], g[0], b[0]); glVertex2f(x[0], y[0]);
    glColor3f(r[2], g[2], b[2]); glVertex2f(x[2], y[2]);
    glColor3f(r[3], g[3], b[3]); glVertex2f(x[3], y[3]);

    // fata din fata
    glColor3f(r[4], g[4], b[4]); glVertex2f(x[4], y[4]);
    glColor3f(r[5], g[5], b[5]); glVertex2f(x[5], y[5]);
    glColor3f(r[6], g[6], b[6]); glVertex2f(x[6], y[6]);

    glColor3f(r[4], g[4], b[4]); glVertex2f(x[4], y[4]);
    glColor3f(r[6], g[6], b[6]); glVertex2f(x[6], y[6]);
    glColor3f(r[7], g[7], b[7]); glVertex2f(x[7], y[7]);

    // fata din stanga
    glColor3f(r[0], g[0], b[0]); glVertex2f(x[0], y[0]);
    glColor3f(r[3], g[3], b[3]); glVertex2f(x[3], y[3]);
    glColor3f(r[7], g[7], b[7]); glVertex2f(x[7], y[7]);

    glColor3f(r[0], g[0], b[0]); glVertex2f(x[0], y[0]);
    glColor3f(r[7], g[7], b[7]); glVertex2f(x[7], y[7]);
    glColor3f(r[4], g[4], b[4]); glVertex2f(x[4], y[4]);

    // fata din dreapta
    glColor3f(r[1], g[1], b[1]); glVertex2f(x[1], y[1]);
    glColor3f(r[2], g[2], b[2]); glVertex2f(x[2], y[2]);
    glColor3f(r[6], g[6], b[6]); glVertex2f(x[6], y[6]);

    glColor3f(r[1], g[1], b[1]); glVertex2f(x[1], y[1]);
    glColor3f(r[6], g[6], b[6]); glVertex2f(x[6], y[6]);
    glColor3f(r[5], g[5], b[5]); glVertex2f(x[5], y[5]);

    // fata de jos
    glColor3f(r[3], g[3], b[3]); glVertex2f(x[3], y[3]); 
    glColor3f(r[7], g[7], b[7]); glVertex2f(x[7], y[7]); 
    glColor3f(r[2], g[2], b[2]); glVertex2f(x[2], y[2]); 

    glColor3f(r[2], g[2], b[2]); glVertex2f(x[2], y[2]); 
    glColor3f(r[7], g[7], b[7]); glVertex2f(x[7], y[7]); 
    glColor3f(r[6], g[6], b[6]); glVertex2f(x[6], y[6]); 

    // fata de sus
    glColor3f(r[0], g[0], b[0]); glVertex2f(x[0], y[0]);
    glColor3f(r[1], g[1], b[1]); glVertex2f(x[1], y[1]);
    glColor3f(r[5], g[5], b[5]); glVertex2f(x[5], y[5]);

    glColor3f(r[0], g[0], b[0]); glVertex2f(x[0], y[0]);
    glColor3f(r[5], g[5], b[5]); glVertex2f(x[5], y[5]);
    glColor3f(r[4], g[4], b[4]); glVertex2f(x[4], y[4]);

    glEnd();

    // muchiile cubuluui
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);

    // spate
    glVertex2f(x[0], y[0]); glVertex2f(x[1], y[1]);
    glVertex2f(x[1], y[1]); glVertex2f(x[2], y[2]);
    glVertex2f(x[2], y[2]); glVertex2f(x[3], y[3]);
    glVertex2f(x[3], y[3]); glVertex2f(x[0], y[0]);

    // fata
    glVertex2f(x[4], y[4]); glVertex2f(x[5], y[5]);
    glVertex2f(x[5], y[5]); glVertex2f(x[6], y[6]);
    glVertex2f(x[6], y[6]); glVertex2f(x[7], y[7]);
    glVertex2f(x[7], y[7]); glVertex2f(x[4], y[4]);

    // muchii laterale
    glVertex2f(x[0], y[0]); glVertex2f(x[4], y[4]);
    glVertex2f(x[1], y[1]); glVertex2f(x[5], y[5]);
    glVertex2f(x[2], y[2]); glVertex2f(x[6], y[6]);
    glVertex2f(x[3], y[3]); glVertex2f(x[7], y[7]);

    glEnd();

    // etichete varfuri
    glColor3f(0, 0, 0);
    drawText("Cyan", x[0] - 30, y[0] - 10);
    drawText("White", x[1] + 10, y[1] - 10);
    drawText("Yellow", x[2] + 10, y[2] - 15);
    drawText("Green", x[3] - 40, y[3] - 15);
    drawText("Blue", x[4] - 30, y[4] + 10);
    drawText("Magenta", x[5] + 10, y[5] + 10);
    drawText("Red", x[6] + 10, y[6] - 10);
    drawText("Black", x[7] - 30, y[7] - 10);

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cub RGB 2D");
    init();
    glutDisplayFunc(desen);
    glutMainLoop();
    return 0;
}
