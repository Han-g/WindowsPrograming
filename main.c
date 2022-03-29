#define Case 5
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
	PAINTSTRUCT ps;
	HDC hDC;
	TCHAR lpOut[100];
	int lp[100];
	memset(lpOut, NULL, sizeof(lpOut));
	memset(lp, NULL, sizeof(lp));
	RECT rect;
	COLORREF text_color;
	COLORREF BG_color;
	int	x = 0, y = 0, n;
	static int count = 0, c = 0;
	static SIZE size;
	static TCHAR str[100]; // = _T("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVYXYZ abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVYXY Zabcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVYXYZ");
	static int yPos = 0;

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
		
#if Case == 1
		{
		wsprintf(lpOut, L"Left-Top (%d, %d)", rect.left, rect.top);
		TextOut(hDC, rect.left, rect.top, lpOut, lstrlen(lpOut));
		wsprintf(lpOut, L"Right-Top (%d, %d)", rect.right, rect.top);
		TextOut(hDC, rect.right, rect.top, lpOut, lstrlen(lpOut));
		wsprintf(lpOut, L"Left-Bottom (%d, %d)", rect.left, rect.bottom);
		TextOut(hDC, rect.left, rect.bottom, lpOut, lstrlen(lpOut));
		wsprintf(lpOut, L"Right-Bottom (%d, %d)", rect.right, rect.bottom);
		TextOut(hDC, rect.right, rect.bottom, lpOut, lstrlen(lpOut));
		wsprintf(lpOut, L"Center (%d, %d)", (rect.left+rect.right)/2, (rect.top+rect.bottom)/2);
		TextOut(hDC, (rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2, lpOut, lstrlen(lpOut));
		}

#elif Case == 2
		wsprintf(str, L"ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ");

		rect.left = 0;
		rect.top = 0;
		rect.right = 300;
		rect.bottom = 250;
		text_color = RGB(rand() % 255, rand() % 255, rand() % 255);
		BG_color = RGB(rand() % 255, rand() % 255, rand() % 255);
		SetTextColor(hDC, text_color);
		SetBkColor(hDC, BG_color);
		DrawText(hDC, str, _tcsclen(str), &rect, DT_LEFT | DT_VCENTER | DT_WORDBREAK | DT_EDITCONTROL);

		rect.left = 300;
		rect.top = 250;
		rect.right = 600;
		rect.bottom = 500;
		text_color = RGB(rand() % 255, rand() % 255, rand() % 255);
		BG_color = RGB(rand() % 255, rand() % 255, rand() % 255);
		SetTextColor(hDC, text_color);
		SetBkColor(hDC, BG_color);
		DrawText(hDC, str, _tcsclen(str), &rect, DT_LEFT | DT_VCENTER | DT_WORDBREAK);

		rect.left = 0;
		rect.top = 250;
		rect.right = 300;
		rect.bottom = 500;
		text_color = RGB(rand() % 255, rand() % 255, rand() % 255);
		BG_color = RGB(rand() % 255, rand() % 255, rand() % 255);
		SetTextColor(hDC, text_color);
		SetBkColor(hDC, BG_color);
		DrawText(hDC, str, _tcsclen(str), &rect, DT_LEFT | DT_VCENTER | DT_WORDBREAK);

		rect.left = 300;
		rect.top = 0;
		rect.right = 600;
		rect.bottom = 250;
		text_color = RGB(rand() % 255, rand() % 255, rand() % 255);
		BG_color = RGB(rand() % 255, rand() % 255, rand() % 255);
		SetTextColor(hDC, text_color);
		SetBkColor(hDC, BG_color);
		DrawText(hDC, str, _tcsclen(str), &rect, DT_LEFT | DT_VCENTER | DT_WORDBREAK);
		
#elif Case == 3
		
		x = rand() % 700; y = rand() % 500; count = rand() % 80 + 20; n = rand() % 9+1;
		text_color = RGB(rand() % 255, rand() % 255, rand() % 255);
		BG_color = RGB(rand() % 255, rand() % 255, rand() % 255);
		SetTextColor(hDC, text_color);
		SetBkColor(hDC, BG_color);
		GetTextExtentPoint32(hDC, str, lstrlen(str), &size);
		rect.left = x; rect.top = y;
		char tem = NULL;
		
		for (int i = 0; i < count; ++i) {
			tem = n + '0';
			str[i] = tem;
		}

		DrawText(hDC, str, _tcsclen(str) - 1, &rect, DT_CENTER | DT_VCENTER | DT_WORDBREAK);
		EndPaint(hWnd, &ps);
		break;
#elif Case == 4
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
#elif Case == 5
		TextOut(hDC, 0, 0, str, lstrlen(str));
		
		SetCaretPos(size.cx, y);

		EndPaint(hWnd, &ps);
		break;
#endif
		break;
	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}