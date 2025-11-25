#include <windows.h>  // sunt mentionate fisiere (biblioteci) care urmeaza sa fie incluse 
#include <gl/freeglut.h> // nu trebuie uitat freeglut.h (sau glut.h sau gl.h & glu.h)

void init(void)  // initializare fereastra de vizualizare
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare
	glMatrixMode(GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D(0.0, 400.0, 0.0, 300.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}

void desen(void) // procedura desenare  
{
	glClear(GL_COLOR_BUFFER_BIT); // curata fereastra de vizualizare
	
	glColor3f(0.0, 0.8, 0.2);// culoarea triunghiului: verde

	// se reprezinta un triunghi
	glBegin(GL_TRIANGLES);
	glVertex2i(100, 50);
	glVertex2i(300, 50);
	glVertex2i(200, 200);
	glEnd();

	glFlush(); // proceseaza procedurile OpenGL cat mai rapid
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv); // initializare GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)

	// modificare: pozitia si dimensiunea ferestrei de vizualizare
	glutInitWindowPosition(200, 150); // pozitia initiala a ferestrei (in coordonate ecran)
	glutInitWindowSize(900, 700); // dimensiunile ferestrei (largime, inaltime)

	glutCreateWindow("Triunghi verde"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara
	init(); // executa procedura de initializare
	glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
	glutDisplayFunc(desen); // procedura desen este invocata ori de cate ori este nevoie
	glutMainLoop(); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
}
