#define Case 12

#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

struct RECT
{
	int left;
	int top;
	int right;
	int bottom;
	int center;
};

struct SIZE
{
	LONG cx;
	LONG cy;
};

void first(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void second(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void third(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void forth(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void fifth(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void sixth(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void seventh(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void eighth(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ninth(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void tenth(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void eleventh(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void twelfth(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int	x = 0, y = 0, n = 0;
static int count = 0, c = 0, r = 0;
static SIZE size;
static TCHAR str[800];
static int yPos = 0;
TCHAR lpOut[100];
int window_size_w = 800, window_size_d = 600;

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming Lab";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, window_size_w, window_size_d, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	srand(time(NULL));
	
	int lp[100];
	//memset(lpOut, NULL, sizeof(lpOut));
	memset(lp, NULL, sizeof(lp));

#if Case == 1
	first(hWnd, uMsg, wParam, lParam);
#elif Case == 2
	second(hWnd, uMsg, wParam, lParam);
#elif Case == 3
	third(hWnd, uMsg, wParam, lParam);
#elif Case == 4
	forth(hWnd, uMsg, wParam, lParam);
#elif Case == 5
	fifth(hWnd, uMsg, wParam, lParam);
#elif Case == 6
	sixth(hWnd, uMsg, wParam, lParam);
#elif Case == 7
	seventh(hWnd, uMsg, wParam, lParam);
#elif Case == 8
	eighth(hWnd, uMsg, wParam, lParam);
#elif Case == 9
	ninth(hWnd, uMsg, wParam, lParam);
#elif Case == 10
	tenth(hWnd, uMsg, wParam, lParam);
#elif Case == 11
	eleventh(hWnd, uMsg, wParam, lParam);
#elif Case == 12
	twelfth(hWnd, uMsg, wParam, lParam);

#endif eixt(-1);

	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void first(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	RECT rect;

	switch (uMsg) {
	case WM_CREATE:
		count = 0;
		break;
	case WM_CHAR:
		if (wParam == VK_BACK) count--;
		else if (wParam == VK_RETURN) {
			count = 0;
			yPos = yPos + 20;
		}
		else if (wParam == '0') exit(-1);
		else str[count++] = wParam;

		if (count >= 30) count = 0;

		str[count] = '\0';
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		GetTextExtentPoint32(hDC, str, lstrlen(str), &size);
		rect.left = 0;
		rect.top = 0;
		rect.right = 600;
		rect.bottom = 500;

		{
			wsprintf(lpOut, L"Left-Top (%d, %d)", rect.left, rect.top);
			TextOut(hDC, rect.left, rect.top, lpOut, lstrlen(lpOut));
			wsprintf(lpOut, L"Right-Top (%d, %d)", rect.right, rect.top);
			TextOut(hDC, rect.right, rect.top, lpOut, lstrlen(lpOut));
			wsprintf(lpOut, L"Left-Bottom (%d, %d)", rect.left, rect.bottom);
			TextOut(hDC, rect.left, rect.bottom, lpOut, lstrlen(lpOut));
			wsprintf(lpOut, L"Right-Bottom (%d, %d)", rect.right, rect.bottom);
			TextOut(hDC, rect.right, rect.bottom, lpOut, lstrlen(lpOut));
			wsprintf(lpOut, L"Center (%d, %d)", (rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2);
			TextOut(hDC, (rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2, lpOut, lstrlen(lpOut));
		}

	}
}

void second(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	RECT rect;

	COLORREF text_color;
	COLORREF BG_color;

	switch (uMsg) {
	case WM_CREATE:
		count = 0;
		break;
	case WM_CHAR:
		if (wParam == VK_BACK) count--;
		else if (wParam == VK_RETURN) {
			count = 0;
			yPos = yPos + 20;
		}
		else if (wParam == '0') exit(-1);
		else str[count++] = wParam;

		if (count >= 30) count = 0;

		str[count] = '\0';
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		GetTextExtentPoint32(hDC, str, lstrlen(str), &size);
		rect.left = 0;
		rect.top = 0;
		rect.right = 120;
		rect.bottom = 100;

		wsprintf(str, L"ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ");

		rect.left = 0;
		rect.top = 0;
		rect.right = 120;
		rect.bottom = 100;
		text_color = RGB(rand() % 255, rand() % 255, rand() % 255);
		BG_color = RGB(rand() % 255, rand() % 255, rand() % 255);
		SetTextColor(hDC, text_color);
		SetBkColor(hDC, BG_color);
		DrawText(hDC, str, _tcsclen(str), &rect, DT_LEFT | DT_VCENTER | DT_WORDBREAK | DT_EDITCONTROL);

		rect.left = 60;
		rect.top = 50;
		rect.right = 120;
		rect.bottom = 100;
		text_color = RGB(rand() % 255, rand() % 255, rand() % 255);
		BG_color = RGB(rand() % 255, rand() % 255, rand() % 255);
		SetTextColor(hDC, text_color);
		SetBkColor(hDC, BG_color);
		DrawText(hDC, str, _tcsclen(str), &rect, DT_LEFT | DT_VCENTER | DT_WORDBREAK | DT_EDITCONTROL);

		rect.left = 0;
		rect.top = 50;
		rect.right = 60;
		rect.bottom = 100;
		text_color = RGB(rand() % 255, rand() % 255, rand() % 255);
		BG_color = RGB(rand() % 255, rand() % 255, rand() % 255);
		SetTextColor(hDC, text_color);
		SetBkColor(hDC, BG_color);
		DrawText(hDC, str, _tcsclen(str), &rect, DT_LEFT | DT_VCENTER | DT_WORDBREAK | DT_EDITCONTROL);

		rect.left = 60;
		rect.top = 0;
		rect.right = 120;
		rect.bottom = 50;
		text_color = RGB(rand() % 255, rand() % 255, rand() % 255);
		BG_color = RGB(rand() % 255, rand() % 255, rand() % 255);
		SetTextColor(hDC, text_color);
		SetBkColor(hDC, BG_color);
		DrawText(hDC, str, _tcsclen(str), &rect, DT_LEFT | DT_VCENTER | DT_WORDBREAK | DT_EDITCONTROL);

	}
}

void third(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	RECT rect;

	COLORREF text_color;
	COLORREF BG_color;

	switch (uMsg) {
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd);
		count = 0;
		break;
	case WM_CHAR:
		if (wParam == VK_BACK) count--;
		else if (wParam == VK_RETURN) {
			count = 0;
			yPos = yPos + 20;
		}
		else if (wParam == '0') exit(-1);
		else str[count++] = wParam;

		if (count >= 30) count = 0;

		str[count] = '\0';
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		GetTextExtentPoint32(hDC, str, lstrlen(str), &size);
		rect.left = 0;
		rect.top = 0;
		rect.right = 600;
		rect.bottom = 500;

		x = rand() % 700; y = rand() % 500; count = rand() % 80 + 20; n = rand() % 9 + 1;
		text_color = RGB(rand() % 255, rand() % 255, rand() % 255);
		BG_color = RGB(rand() % 255, rand() % 255, rand() % 255);
		SetTextColor(hDC, text_color);
		SetBkColor(hDC, BG_color);
		GetTextExtentPoint32(hDC, str, lstrlen(str), &size);
		rect.left = x; rect.top = y; rect.right = x + 100;
		char tem = NULL;

		for (int i = 0; i < count; ++i) {
			tem = n + '0';
			str[i] = tem;
		}

		DrawText(hDC, str, _tcsclen(str) - 1, &rect, DT_CENTER | DT_VCENTER | DT_WORDBREAK | DT_EDITCONTROL);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		PostQuitMessage(0);
		break;
	}
}

void forth(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	RECT rect;
	
	x = 100, y = 200;

	switch (uMsg) {
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd);
		count = 0;
		break;
	case WM_CHAR:
		if (wParam == VK_BACK) count--;
		else if (wParam == VK_RETURN) {
			count = 0;
			y = y + size.cy;
		}
		else if (wParam == '0') exit(-1);
		else str[count++] = wParam;

		if (count >= 30) count = 0;

		str[count] = '\0';
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		GetTextExtentPoint32(hDC, str, lstrlen(str), &size);
		rect.left = 0;
		rect.top = 0;
		rect.right = 600;
		rect.bottom = 500;

		int table = 2, tem = 0;
		static TCHAR TimeTable[19];

		for (int i = 0; i < 20; i++)
		{
			GetTextExtentPoint32(hDC, str, lstrlen(str), &size);
			TimeTable[i] = table * i;
			wsprintf(str, L"%d\t", TimeTable[i]);
			TextOut(hDC, x, y, str, lstrlen(str));
			x += size.cx;
		}
		size.cx = x;
		SetCaretPos(size.cx, 0);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		PostQuitMessage(0);
		break;
	}
}
// 입력 받는 것이 안됨
void fifth(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	RECT rect;
	static TCHAR raw[10][31];

	switch (uMsg) {
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd);
		count = 0;
		break;
	case WM_CHAR:
		if (wParam == VK_BACK) {
			raw[r][count % 30] = '\0';
			if (count > 0) count--;
			//if (count % 30 == 0 && y > 0) y -= size.cy;
		}
		else if (wParam == VK_RETURN) {
			count = 0;
			++r;
			y += size.cy;
		}
		else if (wParam == '0') exit(-1);
		else str[count] = wParam;
		str[count+1] = '\0';
		count++;
		
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		GetTextExtentPoint32(hDC, raw, lstrlen(raw[r]), &size);
		//GetTextExtentPoint32(hDC, str, lstrlen(str), &size);
		if (count % 30 > 0) raw[r][count % 30 - 1] = str[count - 1];
		else if (count % 30 == 0) {
			raw[r][29] = str[count - 1];
			raw[r][30] = '\0';
		}

		if (count >= 300 - 1)
		{
			count = 0; size.cx = 0; size.cy = 0; r = 0;
		}
		else if (count % 30 == 0 && count != 0) {
			y += size.cy;
			++r;
		}

		for (int i = 0; i < r+1; i++)
		{
			TextOut(hDC, 0, size.cy * i, raw[i], lstrlen(raw[i]));
		}

		SetCaretPos(size.cx, y);

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		PostQuitMessage(0);
		break;
	}
}

void sixth(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	RECT rect;	

	//int w_num = (rand() % 8 + 2), d_num = (rand() % 8 + 2), now = 0;
	int w_num = 4, d_num = 3, now = 0;
	int width = (int)(window_size_w / w_num), depth = (int)(window_size_d / d_num);
	memset(lpOut, NULL, sizeof(lpOut));
	char tem[100];

	switch (uMsg) {
	case WM_CREATE:
		count = 0;
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		while (now != w_num*d_num)
		{
			int random_case = rand() % 6;
			count = 0;
			switch (random_case)
			{
			case 0:
				for (int i = 0; i < (int)(depth / 16); i++)
				{
					for (int j = 0; j < (int)(width / 16); j++)
					{

					}
				}
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			default:
				break;
			}
			rect.left = width * (now % w_num); rect.right = width * (now % w_num + 1);
			rect.top = depth * (now / w_num); rect.bottom = depth * (now / w_num + 1);

			wsprintf(lpOut, L"1234567890123456789012345");

			DrawText(hDC, lpOut, lstrlen(lpOut), &rect, DT_CENTER | DT_EDITCONTROL);
			++now;
		}

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
}

void seventh(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	RECT rect;
	static TCHAR raw[10][31];

	switch (uMsg) {
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd);
		count = 0;
		break;
	case WM_CHAR:
		if (wParam == VK_BACK) {
			raw[r][count % 30] = '\0';
			if (count > 0) count--;
			//if (count % 30 == 0 && y > 0) y -= size.cy;
		}
		else if (wParam == VK_RETURN) {
			count = 0;
			++r;
			y += size.cy;
		}
		else if (wParam == '0') exit(-1);
		else str[count] = wParam;
		str[count + 1] = '\0';
		count++;

		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		GetTextExtentPoint32(hDC, raw, lstrlen(raw[r]), &size);
		//GetTextExtentPoint32(hDC, str, lstrlen(str), &size);
		if (count % 30 > 0) raw[r][count % 30 - 1] = str[count - 1];
		else if (count % 30 == 0) {
			raw[r][29] = str[count - 1];
			raw[r][30] = '\0';
		}

		if (count >= 300 - 1)
		{
			count = 0; size.cx = 0; size.cy = 0; r = 0;
		}
		else if (count % 30 == 0 && count != 0) {
			y += size.cy;
			++r;
		}

		for (int i = 0; i < r + 1; i++)
		{
			TextOut(hDC, 0, size.cy * i, raw[i], lstrlen(raw[i]));
		}

		SetCaretPos(size.cx, y);

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		PostQuitMessage(0);
		break;
	}
}

void eighth(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	RECT rect;

	switch (uMsg) {
	case WM_CREATE:
		count = 0;
		break;
	case WM_CHAR:

		break;
	case WM_PAINT:

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
}

void ninth(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	RECT rect;

	switch (uMsg) {
	case WM_CREATE:

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
}

int kind_shape = 0, shape_x1 = 0, shape_y1 = 0, shape_x2 = 0, shape_y2 = 0, thick = 0;

void tenth(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	RECT rect;
	int tem[6]; char c[10];
	static int blank_n;

	switch (uMsg) {
	case WM_CREATE:
		count = 0;
		blank_n = 0;
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case '+':

			break;
		case '-':

			break;
		case VK_LEFT:

			break;
		case VK_UP:

			break;
		case VK_RIGHT:

			break;
		case VK_DOWN:

			break;
		default:
			break;
		}
		break;
	case WM_CHAR:
		if (isdigit(wParam))
		{
			lpOut[count] = wParam;
			lpOut[++count] = '\0';
		}
		else if (wParam == ' ')
		{
			lpOut[count] = wParam;
			lpOut[++count] = '\0';
			++blank_n;
		}
		{/*switch (wParam)
		{
		case 49:
		case 50:
		case 51:
		case 52:
		case 53:
		case 54:
		case 55:
		case 56:
		case 57:
		case 48:
			lpOut[count] = wParam;
			lpOut[++count] = '\0';
			break;
		case ' ':
			++blank_count;
			lpOut[count] = wParam;
			lpOut[++count] = '\0';
			break;
		default:
			break;
		}*/
		}

		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		//if (wParam == ' ') ++blank_count;

		if (blank_n != 5)
		{
			TextOut(hDC, 0, 540, lpOut, lstrlen(lpOut));
		}
		else if (blank_n >= 5)
		{
			char* temp = strtok(lpOut, " ");
			shape_x1 = atoi(temp);
			//shape_y1 = atoi(strtok(lpOut, ' '));
			//shape_x2 = atoi(strtok(lpOut, ' '));
			//shape_y2 = atoi(strtok(lpOut, ' '));
			//thick = atoi(strtok(lpOut, ' '));
		}

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
}
int board_square = 40, select_num = 0, shape[10] = { 0, };
typedef struct LOCATE {
	int x1; int x2; int y1; int y2;
}locate;
void eleventh(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	RECT rect;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	static COLORREF ecolor, rcolor, tcolor, lcolor;
	static locate locates[10];

	int line_w = (int)((window_size_w) / board_square);
	int line_d = (int)((window_size_d) / board_square);
	
	if (count > 10) count = 0;

	switch (uMsg) {
	case WM_CREATE:
		count = 0;
		
		break;
	case WM_KEYDOWN:
		if (wParam == VK_LEFT)
		{
			
		}
		else if (wParam == VK_RIGHT)
		{

		}
		else if (wParam == VK_UP)
		{

		}
		else if (wParam == VK_DOWN)
		{

		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_CHAR:
		switch (wParam)
		{
		case '1':
			select_num = 0;
			break;
		case '2':
			select_num = 1;
			break;
		case '3':
			select_num = 2;
			break;
		case '4':
			select_num = 3;
			break;
		case '5':
			select_num = 4;
			break;
		case '6':
			select_num = 5;
			break;
		case '7':
			select_num = 6;
			break;
		case '8':
			select_num = 7;
			break;
		case '9':
			select_num = 8;
			break;
		case '0':
			select_num = 9;
			break;
		case '+':
			if (locates[select_num].x2 < window_size_w && locates[select_num].y2 < window_size_d) {
				locates[select_num].x2 += line_w;
				locates[select_num].y2 += line_d;
			}
			break;
		case '-':
			if (locates[select_num].x2 != locates[select_num].x1+ line_w) {
				locates[select_num].x2 -= line_w;
				locates[select_num].y2 -= line_d;
			}
			break;
		case 's':
			board_square = 30;
			break;
		case 'm':
			board_square = 40;
			break;
		case 'l':
			board_square = 50;
			break;
		case 'e':
			shape[count] = 1;
			locates[count].x1 = line_w * (rand() % (board_square));
			locates[count].x2 = locates[count].x1 + line_w;
			locates[count].y1 = line_d * (rand() % (board_square));
			locates[count++].y2 = line_d + locates[count].y1;
			break;
		case 't':
			shape[count] = 2;
			locates[count].x1 = line_w * (rand() % (board_square));
			locates[count].x2 = locates[count].x1 + line_w;
			locates[count].y1 = line_d * (rand() % (board_square));
			locates[count++].y2 = line_d + locates[count].y1;
			break;
		case 'r':
			shape[count] = 3;
			locates[count].x1 = line_w * (rand() % (board_square));
			locates[count].x2 = locates[count].x1 + line_w;
			locates[count].y1 = line_d * (rand() % (board_square));
			locates[count++].y2 = line_d + locates[count].y1;
			break;
		case 'c':
			ecolor = RGB(rand() % 255, rand() % 255, rand() % 255);
			tcolor = RGB(rand() % 255, rand() % 255, rand() % 255);
			rcolor = RGB(rand() % 255, rand() % 255, rand() % 255);
			break;
		case 'd':
			shape[select_num-1] = 0;
			for (int i = select_num-1; i < 9; i++)
			{
				shape[i] = shape[i + 1];
			}
			break;
		case 'p':
			for (int i = 0; i < 10; i++) shape[i] = 0;
			break;
		case 'q':
			exit(-1);
			break;
		default:
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		ecolor = RGB(rand() % 255, rand() % 255, rand() % 255);
		tcolor = RGB(rand() % 255, rand() % 255, rand() % 255);
		rcolor = RGB(rand() % 255, rand() % 255, rand() % 255);
		
		hPen = CreatePen(PS_DOT, 1, lcolor);
		oldPen = (HPEN)SelectObject(hDC, hPen);

		for (int i = 0; i < board_square+1; i++)
		{
			MoveToEx(hDC, line_w * i, 0, NULL);
			LineTo(hDC, line_w * i, window_size_d);
			MoveToEx(hDC, 0, line_d * i, NULL);
			LineTo(hDC, window_size_w, line_d * i);
		}
		
		for (int i = 0; i < 10; i++)
		{
			shape_x1 = locates[i].x1;
			shape_x2 = locates[i].x2;
			shape_y1 = locates[i].y1;
			shape_y2 = locates[i].y2;

			if (shape[i] == 1)
			{
				hBrush = CreateSolidBrush(ecolor);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

				Ellipse(hDC, shape_x1, shape_y1, shape_x2, shape_y2);

				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}
			else if (shape[i] == 2)
			{
				hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				typedef struct aPOINT {
					LONG x; LONG y;
				}POINT;
				POINT point[3] = { {shape_x1,shape_y2},{(shape_x1 + shape_x2) / 2,shape_y1},{shape_x2,shape_y2} };
				
				Polygon(hDC, point, 3);

				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}
			else if (shape[i] == 3)
			{
				hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				
				Rectangle(hDC, shape_x1, shape_y1, shape_x2, shape_y2);

				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}
			else
			{
				shape_x1 = locates[select_num].x1;
				shape_x2 = locates[select_num].x2;
				shape_y1 = locates[select_num].y1;
				shape_y2 = locates[select_num].y2;

				if (shape[select_num] == 1)
				{
					hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
					oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

					Ellipse(hDC, shape_x1, shape_y1, shape_x2, shape_y2);

					SelectObject(hDC, oldBrush);
					DeleteObject(hBrush);
				}
				else if (shape[select_num] == 2)
				{
					hBrush = CreateSolidBrush(tcolor);
					oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
					typedef struct aPOINT {
						LONG x; LONG y;
					}POINT;
					POINT point[3] = { {shape_x1,shape_y2},{(shape_x1 + shape_x2) / 2,shape_y1},{shape_x2,shape_y2} };

					Polygon(hDC, point, 3);

					SelectObject(hDC, oldBrush);
					DeleteObject(hBrush);
				}
				else if (shape[select_num] == 3)
				{
					hBrush = CreateSolidBrush(rcolor);
					oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

					Rectangle(hDC, shape_x1, shape_y1, shape_x2, shape_y2);

					SelectObject(hDC, oldBrush);
					DeleteObject(hBrush);
				}
			}
		}

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
}

void twelfth(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	RECT rect;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	static char words[10], c[10];
	static int word_len, error;

	switch (uMsg) {
	case WM_CREATE:
		memset(c, NULL, (char*)sizeof(c));
		strcpy(words, "apple");
		word_len = 5;
		count = 0;
		break;
	case WM_CHAR:
		for (int i = 0; i < 10; i++)
		{
			if (words[i] == wParam)
			{
				c[i] = wParam;
			}
			else if (i == 9) ++count;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		
		hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 255));
		oldPen = (HPEN)SelectObject(hDC, hPen);
		
		MoveToEx(hDC, 70, 100, NULL);
		LineTo(hDC, 220, 100);
		MoveToEx(hDC, 70, 100, NULL);
		LineTo(hDC, 70, 400);
		MoveToEx(hDC, 150, 100, NULL);
		LineTo(hDC, 150, 150);

		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		Rectangle(hDC, 50, 400, 250, 450);

		{
			Ellipse(hDC, 130, 150, 170, 190);
			if (count > 1) {
				MoveToEx(hDC, 150, 190, NULL);
				LineTo(hDC, 150, 300);
			}
			if (count > 2) {
				MoveToEx(hDC, 150, 200, NULL);
				LineTo(hDC, 100, 210);
			}
			if (count > 3) {
				MoveToEx(hDC, 150, 200, NULL);
				LineTo(hDC, 200, 210);
			}
			if (count > 4) {
				MoveToEx(hDC, 150, 300, NULL);
				LineTo(hDC, 120, 380);
			}
			if (count > 5) {
				MoveToEx(hDC, 150, 300, NULL);
				LineTo(hDC, 180, 380);
				
			}
		}
		
		for (int i = 1; i < word_len+1; i++)
		{
			TextOut(hDC, 300 + (i * 30), 420, c[i], sizeof(char));
			MoveToEx(hDC, 300 + (i * 30), 420, NULL);
			LineTo(hDC, 320 + (i * 30), 420);
		}

		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		
		break;
	case WM_DESTROY:
		free(words);
		PostQuitMessage(0);
		break;
	}
}