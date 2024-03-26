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
		obj1.translate(0, translateStep);
		break;
	case 'a':
		obj1.translate(-translateStep, 0);
		break;
	case 's':
		obj1.translate(0, -translateStep);
		break;
	case 'd':
		obj1.translate(translateStep, 0);
		break;
	case 'q':
		obj1.rotate(rotateStep);
		break;
	case 'e':
		obj1.rotate(-rotateStep);
		break;
	case 'r':
		obj1.scale(scaleStep);
		break;
	case 'f':
		obj1.scale(-scaleStep);
		break;
	case 'z':
		if (obj1.translateFlag == false){
			obj1.translateFlag = true;
		} else {
			obj1.translateFlag = false;
			obj1.animationState = obj1.IDLE;
		}
		break;
	case 'A':
		obj1.translate(-translateStep * 10, 0);
		break;
	case 'D':
		obj1.translate(translateStep * 10, 0);
		break;
	case 'W':
		obj1.translate(0, translateStep * 10);
		break;

	case 'S':
		obj1.translate(0, -translateStep * 10);
		break;
	case 'Q':
		obj1.rotate(rotateStep * 10);
		break;
	case 'E':
		obj1.rotate(-rotateStep * 10);
		break;
	case 'R':
		obj1.scale(scaleStep * 10);
		break;
	case 'F':
		obj1.scale(-scaleStep * 10);
		break;
	case 'Z': // Reset
		obj1.translateTo(0, 0);
		break;
	case 27: // Escape key
		exit(0);
		break;
	}
}

int main()
{
	init();						   // Load settings.
	glutDisplayFunc(renderMaster); // Load render function.
	glutKeyboardFunc(kbControl);
	// glutSpecialFunc(kbControl);
	glutMainLoop(); // Loop frame forever.

	system("PAUSE");
	return 0;
}