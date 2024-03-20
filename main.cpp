#include "init.cpp"
#include "render.cpp"

int main()
{
	init(); // Load settings.

	glutDisplayFunc(renderMaster); // Load render function.
	glutMainLoop();				   // Loop frame forever.

	system("PAUSE");
	return 0;
}