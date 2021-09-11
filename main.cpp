#include <iostream>
#include <conio.h>
#include "paintb.h"

int main(void) {
	canvasCRS cnv(100, 300);
	cnv.setFocusedMode(true);
	cnv.setMouseInput(true);

	cnv.maximize();
	cnv.inputLoop('c');
}

