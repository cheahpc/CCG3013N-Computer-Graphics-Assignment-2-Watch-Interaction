#include "init.cpp"
#include "render.cpp"

void kbControl(unsigned char key, int x, int y)
{
	GLfloat rotateStep, scaleStep, translateStep;

	rotateStep = 10;
	scaleStep = 0.1;
	translateStep = 1;

	switch (key)
	{
	case 'w':
		obj3.translate(0, translateStep);
		break;
	case 'a':
		obj3.translate(-translateStep, 0);
		break;
	case 's':
		obj3.translate(0, -translateStep);
		break;
	case 'd':
		obj3.translate(translateStep, 0);
		break;
	case 'q':
		obj3.rotate(rotateStep);
		break;
	case 'e':
		obj3.rotate(-rotateStep);
		break;
	case 'r':
		obj3.scale(scaleStep);
		break;
	case 'f':
		obj3.scale(-scaleStep);
		break;
	case 'z':

	case 27: // Escape key
		exit(0);
		break;
	}
}
int main()
{
	init();								   // Load settings.
	glutDisplayFunc(renderMaster);		   // Load render function.
	// glutKeyboardFunc(kbControl);
	// glutSpecialFunc(kbControl);
	glutMainLoop(); // Loop frame forever.

	system("PAUSE");
	return 0;
}