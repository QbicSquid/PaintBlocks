#ifndef PAINTB_H
#define PAINTB_H
#include <windows.h>

class canvas {
	protected:
		typedef struct FS {
			unsigned char *frameString;
			struct FS *next;
			struct FS *prev;
			int index;
		} FS;

		FS *head;
		int rows;
		int cols;

	public:	
		canvas(int rows, int cols);
		void setBlock(int row, int col, int key);

		void print_fs(); // innefficient print function
};

class canvasCRS: public canvas {
	private:
		HANDLE consoleHandle;
		COORD topLeft;
		CONSOLE_CURSOR_INFO info;
		// for console manipulation

		unsigned char *display;
		bool focusedMode;
		COORD jumpTo;
		COORD jumpBack;
		char out[2];
		// for fast display refreshing (focused mode)

		bool cursor;
		int cursorRow;
		int cursorCol;
		unsigned char cursorMem;	

	public:
		canvasCRS(int rows, int cols);
		void toggleCursor();
		void cursorMov(int key);
		void print();
		void toggleFocusedMode();
		void cls();
};

#endif

