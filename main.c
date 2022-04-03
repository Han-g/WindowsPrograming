#define Case 6

#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>
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

int	x = 0, y = 0, n = 0;
static int count = 0, c = 0, r = 0;
static SIZE size;
static TCHAR str[300];
static TCHAR raw[10][30];
static int yPos = 0;
TCHAR lpOut[100];

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
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
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
	memset(lpOut, NULL, sizeof(lpOut));
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

		raw[r][count % 30] = str[count];
		++count;

		if (count >= 300 - 1)
		{
			count = 0; size.cx = 0; size.cy = 0; r = 0;
		}
		else if (count % 30 == 0 && count != 0) {
			y += size.cy;
			++r;
		}		
		
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		GetTextExtentPoint32(hDC, raw, lstrlen(raw[r]), &size);
		//GetTextExtentPoint32(hDC, str, lstrlen(str), &size);
		rect.left = 0;
		rect.top = 0;
		rect.right = 600;
		rect.bottom = 500;

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

	switch (uMsg) {
	case WM_CREATE:
		count = 0;
		int random_num = rand() % 8 + 2;
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

		raw[r][count % 30] = str[count];
		++count;

		if (count >= 300 - 1)
		{
			count = 0; size.cx = 0; size.cy = 0; r = 0;
		}
		else if (count % 30 == 0 && count != 0) {
			y += size.cy;
			++r;
		}

		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		GetTextExtentPoint32(hDC, raw, lstrlen(raw[r]), &size);
		//GetTextExtentPoint32(hDC, str, lstrlen(str), &size);
		rect.left = 0;
		rect.top = 0;
		rect.right = 600;
		rect.bottom = 500;

		for (int i = 0; i < r + 1; i++)
		{
			TextOut(hDC, 0, size.cy * i, raw[i], lstrlen(raw[i]));
		}

		SetCaretPos(size.cx, y);

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

		TextOut(hDC, 0, 0, str, lstrlen(str));

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