#define window_size_w 800
#define window_size_d 800
#define MAX_NUM 100
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "resource1.h"

typedef struct BOX {
	int x1, y1, x2, y2;
	int R, G, B;
} box;

int line_w = (window_size_w - 40) / 40, line_d = (window_size_d - 40) / 40, location = 0;

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming Lab";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	HMENU hMymenu;
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
	hMymenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU2));
	SetMenu(hWnd, hMymenu);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static int on = 0, now = 0;
	static int mx = 0, my = 0, start_x = 0, start_y = 0, end_x = 0, end_y = 0;
	static BOOL selection = FALSE;
	static box boxes[MAX_NUM];
	PAINTSTRUCT ps;
	HDC hdc;
	SYSTEMTIME curTime;
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;

	srand(time(NULL));

	switch (uMsg) {
	case WM_CREATE:

		break;
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_BORDER_ON:

			break;
		case ID_BORDER_OFF:

			break;
		case ID_COLOR_R:
			boxes[now].R = 255;
			boxes[now].G = 0;
			boxes[now].B = 0;
			break;
		case ID_COLOR_GREEN:
			boxes[now].R = 0;
			boxes[now].G = 255;
			boxes[now].B = 0;
			break;
		case ID_COLOR_BLUE:
			boxes[now].R = 0;
			boxes[now].G = 0;
			boxes[now].B = 255;
			break;
		case ID_COLOR_CYAN:
			boxes[now].R = 0;
			boxes[now].G = 255;
			boxes[now].B = 255;
			break;
		case ID_COLOR_PINK:
			boxes[now].R = 255;
			boxes[now].G = 0;
			boxes[now].B = 255;
			break;
		case ID_COLOR_YELLO:
			boxes[now].R = 255;
			boxes[now].G = 255;
			boxes[now].B = 0;
			break;
		default:
			break;
		}
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		start_x = mx; start_y = my;
		on = 1;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_RBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_MOUSEMOVE:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_LBUTTONUP:
		end_x = mx; end_y = my;
		on = 0;
		boxes[now].x1 = (start_x / 20) * 20;
		boxes[now].y1 = (start_y / 20) * 20;
		boxes[now].x2 = ((end_x / 20) + 1) * 20;
		boxes[now].y2 = ((end_y / 20) + 1) * 20;
		++now;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_RBUTTONUP:
		selection = FALSE;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);

		boxes[now-1].R = 255;
		boxes[now-1].G = 255;
		boxes[now-1].B = 255;

		for (int i = 0; i < 25+1; i++)
		{
			for (int j = 0; j < 25+1; j++)
			{
				MoveToEx(hdc, 100 + (20 * i), 100, NULL);
				LineTo(hdc, 100 + (20 * i), 600);
				MoveToEx(hdc, 100, 100 + (20 * i), NULL);
				LineTo(hdc, 600, 100 + (20 * i));
			}
		}
		struct a {
			int xa, ya, xb, yb;
		}alpha;

		if (start_x < mx && start_y < my) 
			{ alpha.xa = start_x; alpha.ya = start_y; alpha.xb = mx; alpha.yb = my; }
		else if (start_x > mx && start_y > my) 
			{ alpha.xa = mx; alpha.ya = my; alpha.xb = start_x; alpha.yb = start_y; }
		else if (start_x > mx && start_y < my) 
			{ alpha.xa = mx; alpha.ya = start_y; alpha.xb = start_x; alpha.yb = my; }
		else if (start_x < mx && start_y > my) 
			{ alpha.xa = start_x; alpha.ya = my; alpha.xb = mx; alpha.yb = start_y; }
		if(on == 1) FrameRect(hdc, &alpha, RGB(255,0,0));
			
		hBrush = CreateSolidBrush(RGB(boxes[now-1].R,boxes[now-1].G,boxes[now-1].B));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);	

		for (int i = 0; i < now; i++)
		{
			Rectangle(hdc, boxes[i].x1, boxes[i].y1, boxes[i].x2, boxes[i].y2);
		}

		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}