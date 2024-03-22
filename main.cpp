#include "init.cpp"
#include "render.cpp"

void kbControl(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		obj3.translate(0, 10);
		break;
	case 'a':
		obj3.translate(-10, 0);
		break;
	case 's':
		obj3.translate(0, -10);
		break;
	case 'd':
		obj3.translate(10, 0);
		break;
	case 'q':
		obj3.rotate(1);
		break;
	case 'e':
		obj3.rotate(-1);
		break;
	case 'r':
		obj3.scale(0.1);
		break;
	case 'f':
		obj3.scale(-0.1);
		break;
	case 27: // Escape key
		exit(0);
		break;
	}
}
int main()
{
	init();								   // Load settings.
	glutDisplayFunc(renderMaster);		   // Load render function.
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF); // Disable key repeat.
	glutKeyboardFunc(kbControl);
	glutMainLoop(); // Loop frame forever.

	system("PAUSE");
	return 0;
}