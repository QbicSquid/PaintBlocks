#ifndef PAINTB_H
#define PAINTB_H
#include <windows.h>
#include <string>

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

		int rawPos(int row, int col);
		int logRow(int rawPos);
		int logCol(int rawPos);

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
		// for cursor functionality

	public:
		canvasCRS(int rows, int cols);
		void toggleCursor();
		void toggleFocusedMode();
		void cls();
		void cursorMov(int key);
		void print();
		int saveCanvas(std::string fileName);
		int loadCanvas(std::string fileName);
};

#endif

