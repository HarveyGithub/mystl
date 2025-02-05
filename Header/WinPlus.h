//----WinPlus Header----
//!!!!!!!!!!!!!!!!!!!!! The file's code is UTF-8 !!!!!!!!!!!!!!!!!!!!!!!!!
#include <bits/stdc++.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <windows.h>
#include <sys/stat.h>

using namespace std;

#define eventKey(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 				//检测指定按键或鼠标是否被按下
#define SetColor(COLOR) \
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | COLOR); //设置文字颜色
#define RED FOREGROUND_RED 																//红色
#define GREEN FOREGROUND_GREEN 															//绿色
#define BLUE FOREGROUND_BLUE 															//蓝色
#define YELLOW FOREGROUND_RED | FOREGROUND_GREEN 										//黄色
#define WHITE FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED 						//白色
#define Click(events) mouse_event(events, 0, 0, 0, 0 ) 									//鼠标点击
#define LeftClick MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP								//鼠标左击
#define RightClick MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP 							//鼠标右击
#define v vector 																		//vector简写

typedef void vfunc(void); 																//函数类型

void SetTitle(const char* Title); 														//设置标题
void SetWinSize(int wide, int high); 													//设置窗口大小
void clears(bool flag); 																//清屏
void HideCursor(); 																		//隐藏光标（不是鼠标
void ShowCursor();																		//显示光标
void SetPos(int x, int y); 																//设置光标在控制台上的相对坐标
template<typename _Tstr> void print(_Tstr text);										//在光标位置输出文字
template<typename _Tstr> void print(_Tstr text, int PosX, int PosY);					//在控制台的某个坐标输出文字
template<typename _Tstr> void print(_Tstr text, WORD colors, int PosX, int PosY);		//在控制台的某个坐标输出指定颜色的文字
template<typename _Tstr> void print(_Tstr text, WORD colors); 							//在光标位置输出指定颜色的文字
void eventLoop(vector<WORD> event, vector<vfunc*> handle);								//事件循环函数
void sleep_cout(string cout_str, double sleep_time);									//间隔时间逐个输出字符

void bubblsort(int* target, int len);													//指针式冒泡排序（已弃用）
size_t getFileSize(const char* fileName);												//获取文件大小（已弃用）


void SetTitle(const char* Title)//设置标题
{
	char command[100];
	sprintf(command, "title %s", Title);
	system(command);
}
void SetWinSize(int wide, int high)
{
	char command[100];
	sprintf(command, "mode con:cols=%d lines=%d", wide, high);
	system(command);
}

void clears(bool flag = 3) {//清空屏幕 
	if (flag == 1) {//双缓冲
		HANDLE hStdOut; CONSOLE_SCREEN_BUFFER_INFO csbi; DWORD count; DWORD cellCount; COORD homeCoords = { 0, 0 };
		hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hStdOut == INVALID_HANDLE_VALUE) return;
		if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
		cellCount = csbi.dwSize.X * csbi.dwSize.Y;
		if (!FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', cellCount, homeCoords, &count)) return;
		if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)) return;
		SetConsoleCursorPosition(hStdOut, homeCoords);
	}
	else if (flag == 0) {//单缓冲
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD coordScreen = { 0, 0 };
		SetConsoleCursorPosition(hConsole, coordScreen);
	}
	else {
		system("cls");
	}


}
void HideCursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(handle, &CursorInfo);
}
void ShowCursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = true;
	SetConsoleCursorInfo(handle, &CursorInfo);
}
void SetPos(int x, int y)
{
	HANDLE hout;
	COORD coord;
	coord.X = x;
	coord.Y = y;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout, coord);
}
template<typename _Tstr> void print(_Tstr text)
{
	cout << text;
}
template<typename _Tstr> void print(_Tstr text, int PosX, int PosY)
{
	SetPos(PosX, PosY);
	print(text);
}
template<typename _Tstr> void print(_Tstr text, WORD colors, int PosX, int PosY)
{
	SetPos(PosX, PosY);
	print(text, colors);
}
template<typename _Tstr> void print(_Tstr text, WORD colors)
{
	SetColor(colors);
	print(text);
	SetColor(WHITE);
}


void eventLoop(vector<WORD> event, vector<vfunc*> handle)
{
	while (1)
	{
		for (int i = 0; i < event.size(); i++)
		{
			if (eventKey(event[i]))
			{
				(*handle[i])();
				while (eventKey(event[i]));
			}
		}
	}
}

void bubblsort(int* target, int len)
{
	for (int i = 0; !(i == len - 1); i++)
	{
		for (int j = 0; !(j == len - i - 1); j++)
		{
			if (*(target + j) > *(target + j + 1))
			{
				int temp = *(target + j);
				*(target + j) = *(target + j + 1);
				*(target + j + 1) = temp;
			}
		}
	}
}

void sleep_cout(string cout_str, double sleep_time = 20)
{
	string str = cout_str;
	if (0 == str.length()) { return; }
	for (int i = 0; i < str.length(); i++)
	{
		cout << str[i];
		Sleep(sleep_time);
	}
}

size_t getFileSize(const char* fileName) {

	if (fileName == NULL) {
		return -1;
	}

	struct stat statbuf;
	stat(fileName, &statbuf);
	size_t filesize = statbuf.st_size;

	return filesize;
}

