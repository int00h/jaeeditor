#include "WndClass.h"
#include "resource.h"
#include <vector>
using std::vector;

Wnd::Wnd(DWORD dwEXstyle, 
		 LPCTSTR classname, 
		 LPCTSTR windowname, 
		 DWORD dwstyle, 
		 int rx, 
		 int ry, 
		 int nx,
		 int ny, 
		 HWND ParenthWnd, 
		 HMENU hmenu, 
		 WNDPROC WndProc)
{
	WNDCLASSEX wcex;
	HMODULE hMod = GetModuleHandle(NULL);
	if(lstrcmpi(classname,"FRM_TEXTEDIT")==0)
	{   
		ZeroMemory(&wcex, sizeof(wcex)); 
		wcex.cbSize			= sizeof(WNDCLASSEX); 
		wcex.style          = 0;
		wcex.lpfnWndProc    = WndProc;
		wcex.cbClsExtra     = NULL;
		wcex.cbWndExtra     = NULL;
		wcex.hInstance		= NULL;
		wcex.hIcon          = LoadIcon(hMod,(LPCSTR)IDI_ICON1);
		wcex.hCursor        = LoadCursorA(NULL, IDC_ARROW);
		wcex.hbrBackground  = (HBRUSH)CreateSolidBrush(RGB(238,238,238));
		wcex.lpszMenuName   = NULL;
		wcex.lpszClassName  = classname;
		wcex.hIconSm        = LoadIcon(hMod,(LPCSTR)IDI_ICON1);	

		if (RegisterClassExA(&wcex))
		{
			hWnd = CreateWindowExA(dwEXstyle, 
								   classname, 
								   windowname, 
								   dwstyle, 
								   rx,ry,nx,ny,
								   NULL,NULL,
								   hMod,WndProc);
			if (hWnd!=0)
			{
				ShowWindow(hWnd, SW_SHOWNORMAL);
				UpdateWindow(hWnd);
				this->Menu();
				this->FileOpen();
			}
		}			

	}
	else
	{
		hWnd = CreateWindowExA(dwEXstyle, 
							   classname, 
							   windowname, 
							   dwstyle, 
							   rx,ry,nx,ny, 
							   ParenthWnd, 
							   NULL, 
							   hMod, 
							   NULL);
		if (hWnd)
		{
			ShowWindow(hWnd, SW_SHOWNORMAL);
			UpdateWindow(hWnd);
		}
	}

}


