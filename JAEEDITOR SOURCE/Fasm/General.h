#pragma once
#include <Windows.h>
#include <string>

using namespace std;

class ReadingIniFile
{
public:	
	ReadingIniFile(void);
	virtual ~ReadingIniFile(void);
	COLORREF GetRGBValueFromIni(string);
	string GetOpenedFile(string);
	void SaveOpenedFile(string, string);
	int GetSectionSize(string);
	void ClearSection(string);
private:
	string path_to_the_jaeeditor;
	char path_to_the_ini[255];
	int rgb[3];
};

class OperationsOnSelectedLines
{
public:
	OperationsOnSelectedLines(void);
	virtual ~OperationsOnSelectedLines(void);
	void CommentOutTheSelectedLines(HWND hWndScintilla);
	void UncommentTheSelectedLines(HWND hWndScintilla);
	void DecreaseIndent(HWND hWndScintilla);
	void IncreaseIndent(HWND hWndScintilla);
private:
	int t_l;
};

