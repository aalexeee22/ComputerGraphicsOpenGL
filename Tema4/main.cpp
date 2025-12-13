#include <windows.h>
#include <iostream>
#include <gl/freeglut.h>
#include <math.h>

// punctul de referinta (centrul globului)
float Refx = 0.0f, Refy = 0.0f, Refz = 0.0f;

// unghiurile pentru survol
float alpha = 0.0f, beta = 0.0f;

// distanta observatorului fata de obiect (raza sferei de survolare)
float dist = 15.0f;

// coordonatele observatorului
float Obsx, Obsy, Obsz;

// reshape + proiectie (preluat din 05_04_cub_texturat_survolare.cpp)
void reshapeAndProjection(int w, int h)
{
    if (h == 0)
        h = 1;
    float ratio = (float)w / (float)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(60.0f, ratio, 0.1f, 500.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// obiect 3d: glob de craciun (sfera + cilindru)
void drawGlobe()
{
    glPushMatrix();

    // globul
    glColor3f(1.0f, 0.2f, 0.2f);
    glutSolidSphere(1.5f, 40, 40);    // sfera 

    // capacul (de unde se prinde ata de atarnat in brad)
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.5f);   // deasupra globului
    glColor3f(0.9f, 0.8f, 0.0f);     
    glutSolidCylinder(0.3f, 0.6f, 20, 20); //cilindru
    glPopMatrix();

    glPopMatrix();
}

void init(void)
{
    glClearColor(0.6f, 0.9f, 0.95f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

// desenare scena + camera pe sfera de raza dist
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // calculam pozitia observatorului pe sfera de raza dist
    Obsx = Refx + dist * cos(alpha) * cos(beta);
    Obsy = Refy + dist * cos(alpha) * sin(beta);
    Obsz = Refz + dist * sin(alpha);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // camera se uita spre centrul globului
    gluLookAt(Obsx, Obsy, Obsz,
        Refx, Refy, Refz,
        0.0f, 0.0f, 1.0f);

    drawGlobe();

    glutSwapBuffers();
}

// controleaza unghiurile camerei (survolare) cu sagetile
void processSpecialKeys(int key, int xx, int yy)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        beta -= 0.05f;
        break;
    case GLUT_KEY_RIGHT:
        beta += 0.05f;
        break;
    case GLUT_KEY_UP:
        alpha += 0.05f;
        break;
    case GLUT_KEY_DOWN:
        alpha -= 0.05f;
        break;
    }
    std::cout << "alpha = " << alpha << "   beta = " << beta << std::endl;

    glutPostRedisplay();
}

// controleaza distanta camerei cu tastele +, = si -
void processNormalKeys(unsigned char key, int x, int y)
{
    std::cout << "tasta apasata (cod ASCII) = " << (int)key << std::endl;

    // pe multe tastatura + se obtine cu SHIFT si =,
    // iar GLUT trimite '=' (cod 61), nu '+'
    if (key == '+' || key == '=')
    {
        dist -= 5.0f;            // ZOOM IN 
        if (dist < 3.0f) dist = 3.0f;
    }

    if (key == '-')             // ZOOM OUT
    {
        dist += 5.0f;
        if (dist > 200.0f) dist = 200.0f;
    }

    std::cout << "dist (noua) = " << dist << std::endl;

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Globulet de Craciun");

    init();

    glutReshapeFunc(reshapeAndProjection);
    glutDisplayFunc(display);

    glutSpecialFunc(processSpecialKeys);   // sageti
    glutKeyboardFunc(processNormalKeys);   // +, =, -

    glutMainLoop();
    return 0;
}
