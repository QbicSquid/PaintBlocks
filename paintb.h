#ifndef PAINTB_H
#define PAINTB_H
#define COMP_KEY 4826
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
		HANDLE cohan; // console output handle
		DWORD prevConsoleMode; // to restore in the destructor
		COORD topLeft;
		CONSOLE_CURSOR_INFO cci;
		// for console manipulation

		bool mouseInput;
		HANDLE cihan; // console input handle
		INPUT_RECORD inputRecord;
		// for mouse input

		unsigned char *display;
		bool focusedMode;
		COORD jumpTo;
		COORD jumpBack;
		char out[3];
		// for fast display refreshing (focused mode)

		bool cursor;
		int cursorRow;
		int cursorCol;
		unsigned char cursorMem;
		// for cursor functionality

	public:
		canvasCRS(int rows, int cols);
		~canvasCRS();
		void setCursor(bool state);
		void setFocusedMode(bool state);
		void cls();
		void cursorMov(int key);
		void print();
		int getCRow();
		int getCCol();
		void setMouseInput(bool state); // TODO: Finish mouse funnctions
		void focusedMouseLoop();
		int loadCanvas(std::string fileName);
		int saveCanvas(std::string fileName);
		int saveCanvasForce(std::string fileName);
};

#endif

