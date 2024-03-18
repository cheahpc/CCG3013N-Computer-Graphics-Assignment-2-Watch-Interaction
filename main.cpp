#include <windows.h>
#include <GL/glut.h>

using namespace std;

void render()
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // RGBA
	glClear(GL_COLOR_BUFFER_BIT);
	// Render code here.
	glFlush();	// Clear all GL executions.
	glFinish(); // Block until all GL executions are completed.
}

int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Hello OpenGL!");
	glutDisplayFunc(render);
	glutMainLoop();

	system("PAUSE");
	return 0;
}
