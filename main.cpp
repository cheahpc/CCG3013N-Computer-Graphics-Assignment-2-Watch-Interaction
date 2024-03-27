#include "init.cpp"
#include "render.cpp"
#include "kbControl.cpp"


int main()
{
	init();						   // Load settings.
	glutDisplayFunc(renderMaster); // Load render function.
	glutKeyboardFunc(kbControl_Debug_Control);
	// glutSpecialFunc(kbControl);
	glutMainLoop(); // Loop frame forever.

	system("PAUSE");
	return 0;
}