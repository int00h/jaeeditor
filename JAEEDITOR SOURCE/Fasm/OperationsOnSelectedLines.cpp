#include "General.h"
#include <D:\Desktop\Fasm\Fasm\scintilla\include\Scintilla.h>

using namespace std;

OperationsOnSelectedLines::OperationsOnSelectedLines(void)
{
}


OperationsOnSelectedLines::~OperationsOnSelectedLines(void)
{
}

void OperationsOnSelectedLines::CommentOutTheSelectedLines(HWND hWndScintilla)
{
	Sci_TextToFind ttf;
	t_l = SendMessage(hWndScintilla, WM_GETTEXTLENGTH, 0, 0);
	int lcounter = SendMessage(hWndScintilla, SCI_GETLINECOUNT, 0, 0);
		t_l=(t_l++)+(++lcounter);
		char *seltext = new char[t_l];
		if(seltext) {
			ZeroMemory(seltext,t_l);
			int sel = SendMessage(hWndScintilla, SCI_GETSELTEXT, 0, (LPARAM)seltext);
			string comment_sel = seltext;
			if(sel != 0) /* если есть выделенный текст */
			{
				int iter = 0;
				if(comment_sel[iter] != '\t') comment_sel.insert(iter, ";");
				else {
					do {
						iter++;
					} while (comment_sel[iter] == '\t');
					comment_sel.insert(iter, ";");
					}
				int tmp_ = 0;
				while ((tmp_ = comment_sel.find('\n',tmp_))!=-1) {
						do {
							tmp_++;	
							if(tmp_>=comment_sel.size()) break; /* если выйдет за диапазон */
						} while (comment_sel[tmp_] == '\t');	
						comment_sel.insert(tmp_, ";");
				} 
				SendMessage(hWndScintilla, SCI_REPLACESEL, 0, (LPARAM)comment_sel.c_str());
			} else { /* если нет выделенного текста, вставляем ; в позицию курсора */
				comment_sel += ";";
				SendMessage(hWndScintilla, SCI_REPLACESEL, 0, (LPARAM)comment_sel.c_str());
			}
			ZeroMemory(seltext,t_l);
			strcpy(seltext,comment_sel.c_str());
			ttf.lpstrText = seltext;
			ttf.chrg.cpMin = 0;
			ttf.chrg.cpMax = t_l;
			SendMessage(hWndScintilla, SCI_FINDTEXT, SCFIND_MATCHCASE, (LPARAM)&ttf);
			SendMessage(hWndScintilla, SCI_SETSEL, ttf.chrgText.cpMin,ttf.chrgText.cpMax);
		}
        delete[] seltext;
}

void OperationsOnSelectedLines::UncommentTheSelectedLines(HWND hWndScintilla)
{
	Sci_TextToFind ttf;
	int t_l = SendMessage(hWndScintilla, WM_GETTEXTLENGTH, 0, 0);
		t_l++;
		char* seltext = new char[t_l];
		if(seltext) {
			ZeroMemory(seltext,t_l);
			int sel = SendMessage(hWndScintilla, SCI_GETSELTEXT, 0, (LPARAM)seltext);
			string comment_sel = seltext;
			if(sel == 0) { /* если нет выделенного текста */
				ZeroMemory(seltext,t_l);
				SendMessage(hWndScintilla, SCI_GETCURLINE, t_l, (LPARAM)seltext);
				string comment_sel = seltext;
				int tmp_ = comment_sel.find(";");
				if(tmp_ != -1) {
					comment_sel.erase(tmp_,1);
					ttf.lpstrText = seltext;
					ttf.chrg.cpMin = 0;
					ttf.chrg.cpMax = t_l;
					SendMessage(hWndScintilla, SCI_FINDTEXT, SCFIND_MATCHCASE, (LPARAM)&ttf);
					SendMessage(hWndScintilla, SCI_SETSEL, ttf.chrgText.cpMin, ttf.chrgText.cpMax);
					SendMessage(hWndScintilla, SCI_REPLACESEL, 0, (LPARAM)comment_sel.c_str());
				}
			} else { /* если текст был выделен */
				int result_find = 0;
				do {
					result_find = comment_sel.find(";",result_find);
					if(result_find != -1) {
						comment_sel.erase(result_find,1);
						result_find = comment_sel.find('\n',result_find);
						if(result_find != -1) result_find++;
					}
				} while (result_find != -1);
				ttf.lpstrText = seltext;
				ttf.chrg.cpMin = 0;
				ttf.chrg.cpMax = t_l;
				SendMessage(hWndScintilla, SCI_FINDTEXT, SCFIND_MATCHCASE, (LPARAM)&ttf);
				SendMessage(hWndScintilla, SCI_SETSEL, ttf.chrgText.cpMin, ttf.chrgText.cpMax);
				SendMessage(hWndScintilla, SCI_REPLACESEL, 0, (LPARAM)comment_sel.c_str());
				ZeroMemory(seltext,t_l);
				strcpy(seltext,comment_sel.c_str());
				ttf.lpstrText = seltext;
				ttf.chrg.cpMin = 0;
				ttf.chrg.cpMax = t_l;
				SendMessage(hWndScintilla, SCI_FINDTEXT, SCFIND_MATCHCASE, (LPARAM)&ttf);
				SendMessage(hWndScintilla, SCI_SETSEL, ttf.chrgText.cpMin, ttf.chrgText.cpMax);
			}
		}
		delete[] seltext;
}

void OperationsOnSelectedLines::DecreaseIndent(HWND hWndScintilla)
{
	Sci_TextToFind ttf;
	int t_l = SendMessage(hWndScintilla, WM_GETTEXTLENGTH, 0, 0);
	t_l++;
	char* seltext = new char[t_l];
	if(seltext) 
	{
		ZeroMemory(seltext,t_l);
		int sel = SendMessage(hWndScintilla, SCI_GETSELTEXT, 0, (LPARAM)seltext);
		if(sel == 0) 
		{
			ZeroMemory(seltext,t_l);
			SendMessage(hWndScintilla, SCI_GETCURLINE, t_l, (LPARAM)seltext);
			string comment_sel = seltext;
			int tmp_ = comment_sel.find('\t');
			if(tmp_ != -1) {
				comment_sel.erase(tmp_,1);
				ttf.lpstrText = seltext;
				ttf.chrg.cpMin = 0;
				ttf.chrg.cpMax = t_l;
				SendMessage(hWndScintilla, SCI_FINDTEXT, SCFIND_MATCHCASE, (LPARAM)&ttf);
				SendMessage(hWndScintilla, SCI_SETSEL, ttf.chrgText.cpMin, ttf.chrgText.cpMax);
				SendMessage(hWndScintilla, SCI_REPLACESEL, 0, (LPARAM)comment_sel.c_str());
			}
		}
		else if(sel != 0) 
		{
			string comment_sel = seltext;
			int tab_= 0;
			int result_find = 0;
			do 
			{
				result_find = comment_sel.find('\t',result_find);
				if(result_find != -1) 
				{
					comment_sel.erase(result_find,1);
					tab_++;
					result_find++;
				}
			} while (result_find != -1);
			ttf.lpstrText = seltext;
			ttf.chrg.cpMin = 0;
			ttf.chrg.cpMax = t_l;
			SendMessage(hWndScintilla, SCI_FINDTEXT, SCFIND_MATCHCASE, (LPARAM)&ttf);
			SendMessage(hWndScintilla, SCI_SETSEL, ttf.chrgText.cpMin, ttf.chrgText.cpMax);
			SendMessage(hWndScintilla, SCI_REPLACESEL, 0, (LPARAM)comment_sel.c_str());
			SendMessage(hWndScintilla, SCI_SETSEL, ttf.chrgText.cpMin, ttf.chrgText.cpMax-tab_);
		}
	}
	delete[] seltext;
}

void OperationsOnSelectedLines::IncreaseIndent(HWND hWndScintilla)
{
	Sci_TextToFind ttf;
	int t_l = SendMessage(hWndScintilla, WM_GETTEXTLENGTH, 0, 0);
		int lcounter = SendMessage(hWndScintilla, SCI_GETLINECOUNT, 0, 0);
		t_l=(t_l++)+(++lcounter);
		char* seltext = new char[t_l];
		if(seltext) {
			ZeroMemory(seltext,t_l);
			int sel = SendMessage(hWndScintilla, SCI_GETSELTEXT, 0, (LPARAM)seltext);
			string comment_sel = "\t";
			comment_sel += seltext;
			if(sel == 0) { /* если нет выделенного текста */
				SendMessage(hWndScintilla, SCI_REPLACESEL, 0, (LPARAM)comment_sel.c_str());
			} else { /* если текст был выделен */
				int tab_ = 1;
				int result_find = 0;
				do {
					result_find = comment_sel.find('\n',result_find);
					if(result_find != -1) {
						result_find++;
						comment_sel.insert(result_find,"\t");
						tab_++;
					}
				} while (result_find != -1);
				ttf.lpstrText = seltext;
				ttf.chrg.cpMin = 0;
				ttf.chrg.cpMax = t_l;
				SendMessage(hWndScintilla, SCI_FINDTEXT, SCFIND_MATCHCASE, (LPARAM)&ttf);
				SendMessage(hWndScintilla, SCI_SETSEL, ttf.chrgText.cpMin, ttf.chrgText.cpMax);
				SendMessage(hWndScintilla, SCI_REPLACESEL, 0, (LPARAM)comment_sel.c_str());
				SendMessage(hWndScintilla, SCI_SETSEL, ttf.chrgText.cpMin, ttf.chrgText.cpMax + tab_);
			}
		}
		delete[] seltext;
}