#include <GL/glut.h>
#include <ctime>
#include <cstdio>

// dimensiuni segmente
float segLength = 0.08f;
float segWidth = 0.018f;

// configurare cifre (a,b,c,d,e,f,g)
// 7 linii care pot forma orice cifra, ca la ceasul elecronic
int digits[10][7] = {
    {1,1,1,1,1,1,0}, // 0
    {0,1,1,0,0,0,0}, // 1
    {1,1,0,1,1,0,1}, // 2
    {1,1,1,1,0,0,1}, // 3
    {0,1,1,0,0,1,1}, // 4
    {1,0,1,1,0,1,1}, // 5
    {1,0,1,1,1,1,1}, // 6
    {1,1,1,0,0,0,0}, // 7
    {1,1,1,1,1,1,1}, // 8
    {1,1,1,1,0,1,1}  // 9
};

// segment orizontal
void drawHSegment(float x, float y) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + segLength, y);
    glVertex2f(x + segLength, y + segWidth);
    glVertex2f(x, y + segWidth);
    glEnd();
}

// segment vertical
void drawVSegment(float x, float y) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + segWidth, y);
    glVertex2f(x + segWidth, y + segLength);
    glVertex2f(x, y + segLength);
    glEnd();
}

// cifra din segmente
void drawDigit(int num, float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);

    if (digits[num][0]) drawHSegment(0, segLength * 2);       // a
    if (digits[num][1]) drawVSegment(segLength, segLength); // b
    if (digits[num][2]) drawVSegment(segLength, 0);         // c
    if (digits[num][3]) drawHSegment(0, 0);                 // d
    if (digits[num][4]) drawVSegment(0, 0);                 // e
    if (digits[num][5]) drawVSegment(0, segLength);         // f
    if (digits[num][6]) drawHSegment(0, segLength);         // g

    glPopMatrix();
}

// separator „/” oblic 
void drawSlash(float x, float y) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + segWidth, y);
    glVertex2f(x + segLength * 0.8f, y + segLength * 2.5f);
    glVertex2f(x + segLength * 0.8f - segWidth, y + segLength * 2.5f);
    glEnd();
}

// functia de afisare
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.5f, 0.5f);  // teal


    // Ddata curenta
    time_t t = time(nullptr);
    struct tm now;
    localtime_s(&now, &t);

    int zi = now.tm_mday;
    int luna = now.tm_mon + 1;
    int an = now.tm_year + 1900;

    char buffer[12];
    sprintf_s(buffer, sizeof(buffer), "%02d/%02d/%04d", zi, luna, an);

    // centrare pe ecran
    int len = 0;
    for (int i = 0; buffer[i] != '\0'; i++) len++;
    float totalWidth = len * 0.23f;
    float startX = -totalWidth / 2.0f;
    float y = -0.05f;

    // se deseneaza fiecare caracter
    float x = startX;
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '/') {
            drawSlash(x + 0.05f, y); // separator „/” oblic 
            x += 0.15f;
        }
        else {
            int num = buffer[i] - '0';
            drawDigit(num, x, y);
            x += 0.23f;
        }
    }

    glutSwapBuffers();
}

// se actualizeaza periodic
void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000, timer, 0);
}

// redimensionare proportionala
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)w / (float)h;
    if (aspect >= 1.0f)
        gluOrtho2D(-aspect, aspect, -1.0, 1.0);
    else
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
}

void init() {
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.8, 1.8, -1, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 300);
    glutCreateWindow("Data curenta");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
