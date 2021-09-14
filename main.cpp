#include <iostream>
#include <conio.h>
#include "paintb.h"

int main(void) {
	canvasCRS cnv(100, 300);
	cnv.setFocusedMode(true);
	cnv.setMouseInput(true);

	cnv.maximize();
	
	unsigned char key = 0;
	
	while(key != 'c') {	
		cnv.inputLoop('m');
		key = getch();
		switch(key) {
			case 'i':
				cnv.zoomIn();
				break;
			case 'o':
				cnv.zoomOut();
				break;
		}
	}
}

