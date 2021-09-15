#ifndef PAINTB_H
#define PAINTB_H
#define COMP_KEY 4826
#include <windows.h>
#include <string>

class canvas;
class canvasCRS;

enum funcType { voidPtr, cnvVoidPtr};
struct func {
	union {
		void (*voidFunc) ();
		void (canvasCRS::*cnvFunc) (); 
	};
	funcType type;
};

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
		~canvas();
		void setBlock(int row, int col, int key);
		void print_fs(); // innefficient print function
};

class canvasCRS: public canvas {
	private:
		HANDLE cohan; // console output handle
		DWORD consoleMode_prev; // to restore in the destructor
		COORD topLeft;
		CONSOLE_CURSOR_INFO cci; // console cursor infor to set
		CONSOLE_FONT_INFOEX cfi_prev; // to restore in the destructor
		CONSOLE_FONT_INFOEX cfi; // console font info to set
		// for console manipulation

		bool mouseInput;
		HANDLE cihan; // console input handle
		unsigned char block;
		// for mouse input

		unsigned char *display;
		bool focusedMode;
		COORD jumpTo;
		COORD jumpBack;
		// for fast display refreshing (focused mode)

		void redrawConsole();

	public:
		canvasCRS(int rows, int cols);
		~canvasCRS();
		void cls();
		void print();
		void maximize();
		void setFocusedMode(bool state);
		void setMouseInput(bool state); // TODO: Finish mouse funnctions
		void inputLoop(unsigned char ExitKey);
		void zoomIn();
		void zoomOut();
		int loadCanvas(std::string fileName);
		int saveCanvas(std::string fileName);
		int saveCanvasForce(std::string fileName);
};

#endif

