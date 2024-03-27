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
		obj2.translateFlag = !obj2.translateFlag;
		break;
	case 'x':
		obj1.rotateFlag = !obj1.rotateFlag;
		break;
	case 'c':
		obj1.scaleFlag = !obj1.scaleFlag;
		break;
	case 'v':
		obj1.opacityFlag = !obj1.opacityFlag;
		break;
	case 'b':
		obj1.orbitFlag = !obj1.orbitFlag;
		break;
	case 'h':
		obj1.clockWiseFlag = !obj1.clockWiseFlag;
		break;
	case 'n':
		obj2.translateFlag = !obj1.translateFlag;
		obj1.rotateFlag = !obj1.rotateFlag;
		obj1.scaleFlag = !obj1.scaleFlag;
		obj1.opacityFlag = !obj1.opacityFlag;
		obj1.orbitFlag = !obj1.orbitFlag;
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
		obj1.translateTo(100, 100);
	case 'X': // Reset
		obj1.rotateTo(-45);
		break;
	case 'C': // Reset
		obj1.scaleTo(1);
		break;
	case 'V': // Reset
		obj1.opacity = 100;
		break;
	case 'B': // Reset
		obj1.orbitTo(obj1.anchorX, obj1.anchorY, 100, 0);
		break;
	case 'N': // Reset
		obj1.translateTo(100, 100);
		obj1.rotateTo(-45);
		obj1.scaleTo(1);
		obj1.opacity = 100;
		obj1.orbitTo(obj1.anchorX, obj1.anchorY, 100, 0);
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