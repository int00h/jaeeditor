#include "General.h"
#include <Windows.h>
#include <string>

using namespace std;

ReadingIniFile::ReadingIniFile(void)
{
	char path[MAX_PATH] = {0};
	GetModuleFileName(NULL, path, MAX_PATH); /* Получаем полный путь к исполняемому файлу, т.к. в той же папке лежит prototype.h */
	path_to_the_jaeeditor = path; /* Полученный путь заносим в string, что бы проще было получить только путь, без .exe */
	int posit = path_to_the_jaeeditor.rfind("\\");
	path_to_the_jaeeditor.erase(posit + 1,path_to_the_jaeeditor.length());
	path_to_the_jaeeditor += "settings.ini";	
	memset(path_to_the_ini, 0, 255);
	strcpy(path_to_the_ini, path_to_the_jaeeditor.c_str());
}

COLORREF ReadingIniFile::GetRGBValueFromIni(string key) 
{
	char str[MAX_PATH] = {0};
	strcpy(str, key.c_str());

	char m[MAX_PATH] = {0};
	GetPrivateProfileString("colors", str, 0, m, MAX_PATH, path_to_the_ini);
	string rgb_value = m; 
	memset(rgb, 0, 3);
	int pos1 = rgb_value.find(","), pos2 = rgb_value.rfind(",");
	rgb[0] = stoi(rgb_value.substr(0, pos1+1));
	rgb[1] = stoi(rgb_value.substr(pos1+1, pos2-1));
	rgb[2] = stoi(rgb_value.substr(pos2+1, rgb_value.length()));

	return RGB(rgb[0], rgb[1], rgb[2]);
}

string ReadingIniFile::GetOpenedFile(string key) 
{
	char str[MAX_PATH] = {0};
	strcpy(str, key.c_str());

	char m[MAX_PATH] = {0};
	GetPrivateProfileString("opened", str, 0, m, MAX_PATH, path_to_the_ini);

	return m;
}

void ReadingIniFile::SaveOpenedFile(string key, string number) 
{
	char str[MAX_PATH] = {0};
	strcpy(str, key.c_str());

	char str_n[MAX_PATH] = {0};
	strcpy(str_n, number.c_str());

	WritePrivateProfileString("opened", str_n, str, path_to_the_ini);
}

int ReadingIniFile::GetSectionSize(string section)
{
	int size = 0;
	char str[MAX_PATH] = {0};
	strcpy(str, section.c_str());

	char m[MAX_PATH] = {0};
	GetPrivateProfileString(str, 0, 0, m, MAX_PATH, path_to_the_ini);
	
	for (int i = 0; i < MAX_PATH; i ++) {
		if (m[i] == '\0') 
		{
		  size ++;
		  if (m[i + 1] == '\0') break;                
		}
	}    

	return size;
}

void ReadingIniFile::ClearSection(string section)
{
	WritePrivateProfileSection(section.c_str(), "", path_to_the_ini);
}

ReadingIniFile::~ReadingIniFile(void)
{
}
