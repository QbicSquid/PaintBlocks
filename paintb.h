#ifndef PAINTB_H_   /* Include guard */
#define PAINTB_H_

#ifndef COMPKEY
#define COMPKEY 1548
#endif

typedef struct FRAMEDATA{
	unsigned char *frameStringPTR; // need to check if this works
	int rows;
	int cols;
	int cursorRow;
	int cursorCol;
	unsigned char cursorMem;
}FRAMEDATA;

//paintb.c
void initNewCanvas(FRAMEDATA *fData);
void blockEdit(FRAMEDATA *fData, int blockRow, int blockCol, int key);
void cursorMove(FRAMEDATA *fData, int key);
void cursorAdd(FRAMEDATA *fData);
void cursorRem(FRAMEDATA *fData);
void pause();
int loadFile(FRAMEDATA *fData, char fileName[]);
int saveFile(FRAMEDATA *fData, char fileName[]);

//image_edit.c
void paint(FRAMEDATA *fData);

#endif
