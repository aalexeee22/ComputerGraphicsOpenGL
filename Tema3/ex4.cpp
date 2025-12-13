#include <windows.h>
#include <GL/freeglut.h>

#define TEX_SIZE 64
GLuint texID;

void createTexture()
{
    // creez o textura de carouri in nuante de mov
    unsigned char data[TEX_SIZE][TEX_SIZE][3];

    for (int i = 0; i < TEX_SIZE; ++i)
        for (int j = 0; j < TEX_SIZE; ++j)
        {
            int c = ((i / 8) % 2) ^ ((j / 8) % 2);
            unsigned char col = c ? 255 : 100;
            data[i][j][0] = col;   // rosu
            data[i][j][1] = 50;    // verde
            data[i][j][2] = 150;   // albastru (rezulta mov)
        }

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEX_SIZE, TEX_SIZE,
        0, GL_RGB, GL_UNSIGNED_BYTE, data);
}

void init(void)
{
    // culoarea de fundal
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // setare proiectie ortogonala
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300, 300, -300, 300);

    // textura mov
    createTexture();
}

void drawSquareTextured()
{
    // patrat centrat in origine, latura 30, cu textura mov
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(-15, -15);
    glTexCoord2f(1, 0); glVertex2f(15, -15);
    glTexCoord2f(1, 1); glVertex2f(15, 15);
    glTexCoord2f(0, 1); glVertex2f(-15, 15);
    glEnd();
}

void drawSquarePlain()
{
    // patrat centrat in origine fara textura
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

    // patratul original desenat in negru
    glColor3f(0, 0, 0);
    drawSquarePlain();

    // figura obtinuta aplicand mai intai scalarea si apoi translatie
    // aceasta figura este colorata (foloseste culoarea alba)
    // ordinea apelurilor: scalare apoi translatie
    // ordinea aplicata obiectului: translatie * scalare * v
    glPushMatrix();
    glColor3f(1, 0.6f, 0.0f); // acum este portocaliu real

   
    glTranslatef(100.0f, 100.0f, 0);  // translatie dupa scalare
    glScalef(2.0f, 0.5f, 1.0f);       // scalare in jurul originii

    drawSquarePlain();
    glPopMatrix();

    // figura obtinuta aplicand mai intai translatie si apoi scalarea
    // aceasta figura este texturata (textura mov)
    // ordinea apelurilor: translatie apoi scalare
    // ordinea aplicata obiectului: scalare * translatie * v
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);

    
    glScalef(2.0f, 0.5f, 1.0f);       // scalare care afecteaza si translatie
    glTranslatef(100.0f, 100.0f, 0); // translatie

    drawSquareTextured();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("ordine transformari si texturare");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
