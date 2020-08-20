#include <Windows.h>
#include <Commctrl.h>
#include "resource.h"
#include <vector>
using std::vector;

#pragma comment (lib,"Comctl32.lib")

#ifndef _WINDOW
#define _WINDOW

class Wnd
{
public:

	#define ID_EDIT					4100
	#define ID_FILE_OPEN			4101
	#define ID_FILE_SAVE_AS			4102
	#define ID_EXIT					4103
	#define ID_PRINT				4104
	#define ID_NEW					4105
	#define	ID_FILEFIND				4106
	#define ID_CLOSE				4107
	#define ID_RUN					4109
	#define ID_COMPILE				4110
	#define ID_SAVE					4111
	#define ID_COMPILE_RUN			4112
	#define ID_ADD					4113
	#define ID_DEL					4114
	#define ID_FILE_SAVE_ALL		4115
	#define ID_FILEFINDANDREPLASE	4116
	#define ID_UNDO					4117
	#define ID_REDO					4118
	#define ID_DEC					4119
	#define ID_INC					4120
	#define ID_COMMENT				4121
	#define ID_UNCOMMENT			4122
	#define ID_TOGGLE				4123
	#define ID_PREVIOUS				4124
	#define ID_NEXT					4125
	#define ID_CLEARALL				4126
	#define ID_CLEARALL_CF			4127
	#define ID_GOTO					4128
	#define ID_UPDATE				4129
	#define ID_ABOUT				4130
	#define ID_CLOSEALLBUTTHIS		4131
	#define ID_CLOSELEFT			4132
	#define ID_CLOSERIGHT			4133
	#define ID_OPENFOLDER			4134

	#define ID_Hello_World	500
	#define ID_Hello_World2	501
	#define ID_Hello_World3	502
	#define ID_DDRAW		503
	#define ID_DIALOG		504
	#define ID_DLL			505
	#define ID_MINIPAD		506
	#define ID_MSCOFF		507
	#define ID_OPENGL		508
	#define ID_PEDEMO		509
	#define ID_TEMPLATE		510
	#define ID_USECOM		511
	#define ID_MANDEL		512
	#define ID_OPENGL2		513
	#define ID_PE64DEMO		514
	#define ID_TEMPLATE2	515
	#define ID_USECOM2		516

	OPENFILENAME ofn;
	HICON hIcon;
	char *szText;
	char szFile[260];
	HWND hWnd,HEdit;
	HANDLE hFile;
	HMENU	hMenu,
			hHelpMenu,
			hFileMenu,
			hEditMenu,
			hSearchMenu,
			hRunMenu,
			hBookmarksMenu,
			hExamplesMenu,
			hTabMenu,
			hEmptyTabMenu,
			hTreeViewMenu,
			hCodeVeiwIncludesMenu,
			hCurrentPageIncludesMenu,
			hAllPossibleIncludesMenu;
	int wmId, wmEvent;

	Wnd::Wnd()
	{   
		HEdit		= NULL;
		hFile		= NULL;
		hIcon		= NULL;
		hMenu		= NULL;
		hFileMenu	= NULL;
		hEditMenu	= NULL;
		hSearchMenu	= NULL;
		hTabMenu	= NULL;
	}

	/* CreateWindowEx */
	Wnd(DWORD dwEXstyle, 
		LPCTSTR classname, 
		LPCTSTR windowname, 
		DWORD dwstyle, 
		int rx, int ry, 
		int nx, int ny,
		HWND ParenthWnd,
		HMENU hmenu, 
		WNDPROC WndProc);
	
private:
	void Wnd::Menu()
	{ 
		HMODULE hMod = GetModuleHandle(NULL);
		hMenu = CreateMenu();
		/* File */
		hFileMenu = CreatePopupMenu(); 
		AppendMenu(hMenu, MF_STRING|MF_POPUP, (UINT)(LONG_PTR)hFileMenu, "File");
		AppendMenu(hFileMenu, MF_STRING, ID_NEW, "&New\tCtrl+N");
			HBITMAP hbmpNew = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP7);
			SetMenuItemBitmaps(hFileMenu, ID_NEW, MF_BYCOMMAND, hbmpNew, hbmpNew);
		AppendMenu(hFileMenu, MF_STRING, ID_FILE_OPEN, "&Open\tCtrl+O");
			HBITMAP hbmpOpen = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP44);
			SetMenuItemBitmaps(hFileMenu, ID_FILE_OPEN, MF_BYCOMMAND, hbmpOpen, hbmpOpen);
		AppendMenu(hFileMenu, MF_SEPARATOR, 0, 0);
		AppendMenu(hFileMenu, MF_STRING, ID_SAVE, "&Save\tCtrl+S");
			HBITMAP hbmpSave = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP1);
			SetMenuItemBitmaps(hFileMenu, ID_SAVE, MF_BYCOMMAND, hbmpSave, hbmpSave);
		AppendMenu(hFileMenu, MF_STRING, ID_FILE_SAVE_AS, "Save as");
		AppendMenu(hFileMenu, MF_STRING, ID_FILE_SAVE_ALL, "&Save all\tCtrl+Shift+S");
			HBITMAP hbmpSaveAs = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP3);
			SetMenuItemBitmaps(hFileMenu, ID_FILE_SAVE_ALL, MF_BYCOMMAND, hbmpSaveAs, hbmpSaveAs);
		AppendMenu(hFileMenu, MF_SEPARATOR, 0, 0);
		AppendMenu(hFileMenu, MF_STRING, ID_CLOSE, "Close");
		HMENU hFileCloseMore = CreatePopupMenu();
			AppendMenu(hFileMenu, MF_STRING|MF_POPUP, (UINT)(LONG_PTR)hFileCloseMore, "Close more");
			AppendMenu(hFileCloseMore, MF_STRING, ID_CLOSEALLBUTTHIS, "Close all but this");
			AppendMenu(hFileCloseMore, MF_STRING, ID_CLOSELEFT, "Close all to the left");
			AppendMenu(hFileCloseMore, MF_STRING, ID_CLOSERIGHT, "Close all to the right");
		AppendMenu(hFileMenu, MF_SEPARATOR, 0, 0);
		AppendMenu(hFileMenu, MF_STRING, ID_PRINT, "&Print\tCtrl+P");
			HBITMAP hbmpPrint = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP2);
			SetMenuItemBitmaps(hFileMenu, ID_PRINT, MF_BYCOMMAND, hbmpPrint, hbmpPrint);
		AppendMenu(hFileMenu, MF_SEPARATOR, 0, 0);
		AppendMenu(hFileMenu, MF_STRING, ID_EXIT, "&Exit\tAlt+F4");
			HBITMAP hbmpExit = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP6);
			SetMenuItemBitmaps(hFileMenu, ID_EXIT, MF_BYCOMMAND, hbmpExit, hbmpExit);

		/* Edit */
		hEditMenu = CreatePopupMenu(); 
		AppendMenu(hMenu, MF_STRING|MF_POPUP, (UINT)(LONG_PTR)hEditMenu, "Edit");
		AppendMenu(hEditMenu, MF_STRING, ID_UNDO, "&Undo\tCtrl+Z");
		AppendMenu(hEditMenu, MF_STRING, ID_REDO, "&Redo\tCtrl+Y");
			HBITMAP hbmpUndo = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP4);
			SetMenuItemBitmaps(hEditMenu, ID_UNDO, MF_BYCOMMAND, hbmpUndo, hbmpUndo);
			HBITMAP hbmpRedo = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP41);
			SetMenuItemBitmaps(hEditMenu, ID_REDO, MF_BYCOMMAND, hbmpRedo, hbmpRedo);
		AppendMenu(hEditMenu, MF_SEPARATOR, 0, 0);
		AppendMenu(hEditMenu, MF_STRING, WM_CUT, "&Cut\tCtrl+X");
			HBITMAP hbmpCut = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP5);
			SetMenuItemBitmaps(hEditMenu, WM_CUT, MF_BYCOMMAND, hbmpCut, hbmpCut);
		AppendMenu(hEditMenu, MF_STRING, WM_COPY, "&Copy\tCtrl+C");
			HBITMAP hbmpCopy = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP8);
			SetMenuItemBitmaps(hEditMenu, WM_COPY, MF_BYCOMMAND, hbmpCopy, hbmpCopy);
		AppendMenu(hEditMenu, MF_STRING, WM_PASTE, "&Paste\tCtrl+V");
			HBITMAP hbmpPaste = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP9);
			SetMenuItemBitmaps(hEditMenu, WM_PASTE, MF_BYCOMMAND, hbmpPaste, hbmpPaste);
		AppendMenu(hEditMenu, MF_STRING, WM_CLEAR, "&Delete\tDel");
		AppendMenu(hEditMenu, MF_SEPARATOR, 0, 0);
		AppendMenu(hEditMenu, MF_STRING, EM_SETSEL, "&Select all\tCtrl+A");
		AppendMenu(hEditMenu, MF_SEPARATOR, 0, 0);
		AppendMenu(hEditMenu, MF_STRING, ID_DEC, "&Decrease Indent\tShift+Tab");
			HBITMAP hbmpDec = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP56);
			SetMenuItemBitmaps(hEditMenu, ID_DEC, MF_BYCOMMAND, hbmpDec, hbmpDec);
		AppendMenu(hEditMenu, MF_STRING, ID_INC, "&Increase Indent\tCtrl+Shift+Tab");
			HBITMAP hbmpInc = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP57);
			SetMenuItemBitmaps(hEditMenu, ID_INC, MF_BYCOMMAND, hbmpInc, hbmpInc);
		AppendMenu(hEditMenu, MF_SEPARATOR, 0, 0);
		AppendMenu(hEditMenu, MF_STRING, ID_COMMENT, "&Comment out the selected lines\tCtrl+Shift+C");
			HBITMAP hbmpCom = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP52);
			SetMenuItemBitmaps(hEditMenu, ID_COMMENT, MF_BYCOMMAND, hbmpCom, hbmpCom);
		AppendMenu(hEditMenu, MF_STRING, ID_UNCOMMENT, "&Uncomment the selected lines\tCtrl+Shift+X");
			HBITMAP hbmpUnCom = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP53);
			SetMenuItemBitmaps(hEditMenu, ID_UNCOMMENT, MF_BYCOMMAND, hbmpUnCom, hbmpUnCom);
		AppendMenu(hEditMenu, MF_SEPARATOR, 0, 0);
		AppendMenu(hEditMenu, MF_STRING, ID_OPENFOLDER, "Open containing folder in explorer");

		/* Search */
		hSearchMenu = CreatePopupMenu(); 
		AppendMenu(hMenu, MF_STRING|MF_POPUP, (UINT)(LONG_PTR)hSearchMenu, "Search");
		AppendMenu(hSearchMenu, MF_STRING, ID_FILEFIND, "&Find\tCtrl+F");
		AppendMenu(hSearchMenu, MF_STRING, ID_FILEFINDANDREPLASE, "&Find and replace\tCtrl+Shift+F");

		/* Run */
		hRunMenu = CreatePopupMenu(); 
		AppendMenu(hMenu, MF_STRING|MF_POPUP, (UINT)(LONG_PTR)hRunMenu, "Run");
		AppendMenu(hRunMenu, MF_STRING, ID_RUN, "&Run\tF9");
			HBITMAP hbmpRun = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP55);
			SetMenuItemBitmaps(hRunMenu, ID_RUN, MF_BYCOMMAND, hbmpRun, hbmpRun);
		AppendMenu(hRunMenu, MF_STRING, ID_COMPILE, "&Compile\tCtrl+F9");
			HBITMAP hbmpCompile = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP54);
			SetMenuItemBitmaps(hRunMenu, ID_COMPILE, MF_BYCOMMAND, hbmpCompile, hbmpCompile);

		/* Bookmarks */
		hBookmarksMenu = CreatePopupMenu(); 
		AppendMenu(hMenu, MF_STRING|MF_POPUP, (UINT)(LONG_PTR)hBookmarksMenu, "Bookmarks");
		AppendMenu(hBookmarksMenu, MF_STRING, ID_TOGGLE, "Toggle a bookmark on the current line");
				HBITMAP hToggle = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP58);
				SetMenuItemBitmaps(hBookmarksMenu, ID_TOGGLE, MF_BYCOMMAND, hToggle, hToggle);
		AppendMenu(hBookmarksMenu, MF_SEPARATOR, 0, 0);
		AppendMenu(hBookmarksMenu, MF_STRING, ID_PREVIOUS, "Move the caret to the previous bookmark");
				HBITMAP hPrev = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP59);
				SetMenuItemBitmaps(hBookmarksMenu, ID_PREVIOUS, MF_BYCOMMAND, hPrev, hPrev);
		AppendMenu(hBookmarksMenu, MF_STRING, ID_NEXT, "Move the caret to the next bookmark");
				HBITMAP hNext = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP60);
				SetMenuItemBitmaps(hBookmarksMenu, ID_NEXT, MF_BYCOMMAND, hNext, hNext);
		AppendMenu(hBookmarksMenu, MF_SEPARATOR, 0, 0);
		AppendMenu(hBookmarksMenu, MF_STRING, ID_CLEARALL, "Clear all bookmarks in all files");
				HBITMAP hClearAll = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP62);
				SetMenuItemBitmaps(hBookmarksMenu, ID_CLEARALL, MF_BYCOMMAND, hClearAll, hClearAll);
		AppendMenu(hBookmarksMenu, MF_STRING, ID_CLEARALL_CF, "Clear all bookmarks in the current file");
				HBITMAP hClear = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP61);
				SetMenuItemBitmaps(hBookmarksMenu, ID_CLEARALL_CF, MF_BYCOMMAND, hClear, hClear);

		/* Examples */
		hExamplesMenu = CreatePopupMenu(); 
		AppendMenu(hMenu, MF_STRING|MF_POPUP, (UINT)(LONG_PTR)hExamplesMenu, "Examples");
			CreatePopupMenu();
				AppendMenu(hExamplesMenu, MF_STRING, ID_Hello_World, "HELLO WORLD (1)");
				AppendMenu(hExamplesMenu, MF_STRING, ID_Hello_World2, "HELLO WORLD (2)");
				AppendMenu(hExamplesMenu, MF_STRING, ID_Hello_World3, "BEER");
				AppendMenu(hExamplesMenu, MF_STRING, ID_DDRAW, "DDRAW");
				AppendMenu(hExamplesMenu, MF_STRING, ID_DIALOG, "DIALOG");
				AppendMenu(hExamplesMenu, MF_STRING, ID_DLL, "DLL");
				AppendMenu(hExamplesMenu, MF_STRING, ID_MINIPAD, "MINIPAD");
				AppendMenu(hExamplesMenu, MF_STRING, ID_MSCOFF, "MSCOFF");
				AppendMenu(hExamplesMenu, MF_STRING, ID_OPENGL, "OPENGL");
				AppendMenu(hExamplesMenu, MF_STRING, ID_PEDEMO, "PEDEMO");
				AppendMenu(hExamplesMenu, MF_STRING, ID_TEMPLATE, "TEMPLATE");
				AppendMenu(hExamplesMenu, MF_STRING, ID_USECOM, "USECOM");
			HMENU hFile3 = CreatePopupMenu();
			AppendMenu(hExamplesMenu, MF_STRING|MF_POPUP, (UINT)(LONG_PTR)hFile3, "WIN64");
				AppendMenu(hFile3, MF_STRING, ID_MANDEL, "MANDEL");
				AppendMenu(hFile3, MF_STRING, ID_OPENGL2, "OPENGL");
				AppendMenu(hFile3, MF_STRING, ID_PE64DEMO, "PE64DEMO");
				AppendMenu(hFile3, MF_STRING, ID_TEMPLATE2, "TEMPLATE");
				AppendMenu(hFile3, MF_STRING, ID_USECOM2, "USECOM");
		
		/* Help */
		hHelpMenu = CreatePopupMenu();
		AppendMenu(hMenu, MF_STRING|MF_POPUP, (UINT)(LONG_PTR)hHelpMenu, "Help");
		AppendMenu(hHelpMenu, MF_STRING, ID_ABOUT, "About");

		/* TreeViewMenu */
		hTreeViewMenu = CreatePopupMenu(); 
		AppendMenu(hTreeViewMenu, MF_STRING, ID_ADD, "Add to the current page");
			HBITMAP hTreeViewBMP = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP39);
			SetMenuItemBitmaps(hTreeViewMenu, ID_ADD, MF_BYCOMMAND, hTreeViewBMP, hTreeViewBMP);
		hCurrentPageIncludesMenu = CreatePopupMenu();
		AppendMenu(hCurrentPageIncludesMenu, MF_STRING, ID_DEL, "Delete from the current page");
			HBITMAP hTreeViewBMP_2 = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP40);
			SetMenuItemBitmaps(hCurrentPageIncludesMenu, ID_DEL, MF_BYCOMMAND, hTreeViewBMP_2, hTreeViewBMP_2);
		hAllPossibleIncludesMenu = CreatePopupMenu();
			AppendMenu(hAllPossibleIncludesMenu, MF_STRING, ID_GOTO, "Go to");
			HBITMAP hTreeViewBMP_3 = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP68);
			SetMenuItemBitmaps(hAllPossibleIncludesMenu, ID_GOTO, MF_BYCOMMAND, hTreeViewBMP_3, hTreeViewBMP_3);
		hCodeVeiwIncludesMenu = CreatePopupMenu();
			AppendMenu(hCodeVeiwIncludesMenu, MF_STRING, ID_UPDATE, "Update");
			HBITMAP hTreeViewBMP_4 = LoadBitmap(hMod, (LPCSTR)IDB_BITMAP69);
			SetMenuItemBitmaps(hCodeVeiwIncludesMenu, ID_UPDATE, MF_BYCOMMAND, hTreeViewBMP_4, hTreeViewBMP_4);

		/* Empty Tab menu */
		hTabMenu=CreatePopupMenu();
		AppendMenu(hTabMenu, MF_STRING, ID_NEW, "New");
		AppendMenu(hTabMenu, MF_STRING, ID_FILE_OPEN, "Open");

		/* Tab menu */
		hEmptyTabMenu=CreatePopupMenu();
		AppendMenu(hEmptyTabMenu, MF_STRING, ID_SAVE, "Save");
		AppendMenu(hEmptyTabMenu, MF_SEPARATOR, 0, 0);
		AppendMenu(hEmptyTabMenu, MF_STRING, ID_CLOSE, "Close");
		AppendMenu(hEmptyTabMenu, MF_STRING, ID_CLOSEALLBUTTHIS, "Close all but this");
		AppendMenu(hEmptyTabMenu, MF_STRING, ID_CLOSELEFT, "Close all to the left");
		AppendMenu(hEmptyTabMenu, MF_STRING, ID_CLOSERIGHT, "Close all to the right");
		AppendMenu(hEmptyTabMenu, MF_SEPARATOR, 0, 0);
		AppendMenu(hEmptyTabMenu, MF_STRING, ID_OPENFOLDER, "Open containing folder in explorer");
		AppendMenu(hEmptyTabMenu, MF_SEPARATOR, 0, 0);
		AppendMenu(hEmptyTabMenu, MF_STRING, ID_PRINT, "&Print\tCtrl+P");
		
		SetMenu(hWnd, hMenu);
	}

	void Wnd::FileOpen()
	{
		ZeroMemory(&ofn, sizeof(ofn)); 
		ofn.lStructSize		= sizeof(ofn);
		ofn.hwndOwner		= hWnd;
		ofn.lpstrFile		= szFile;
		ofn.lpstrFile[0]	= '\0';
		ofn.nMaxFile		= sizeof(szFile);
		ofn.lpstrFilter		= "All\0*.*\0Text\0*.TXT\0";
		ofn.nFilterIndex	= 1;
		ofn.lpstrFileTitle	= NULL;
		ofn.nMaxFileTitle	= 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags			= OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	}
};
#endif