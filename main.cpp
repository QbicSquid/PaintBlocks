#include <iostream>
#include <conio.h>
#include "paintb.h"
using namespace std;


int main(void) {
	canvasCRS cnv(10, 20);
	cnv.cursorToggle();

	char key;
	cnv.enableFocusedMode();
	while (true) {
		cnv.print();
		key = getch();
		cnv.cursorMov(key);
	}

	return 0;
}

