#define window_size_w 800
#define window_size_d 800
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "resource.h"

int collision_check_x(int box_x1, int box_y1, int box_x2, int box_y2, int cir_x1, int cir_y1, int cir_x2, int cir_y2);
int collision_check_y(int box_x1, int box_y1, int box_x2, int box_y2, int cir_x1, int cir_y1, int cir_x2, int cir_y2);

void CALLBACK TimerProcA(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
void CALLBACK TimerProcB(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
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
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, window_size_w, window_size_d, NULL, LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1)), hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
typedef struct {
	int left; int top; int right; int bottom; int b;
} sq;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static int Timer1Count = 0, Timer2Count = 0, on = 0, vx = 1, vy = 1, v = 1, t = 0, box_num = 3, cir_size = 3;
	static int bar_x = 0, bar_y = 0, mx = 0, my = 0, cir_x = 0, cir_y = 0, color = 0;
	static BOOL select;
	static TCHAR str[100];
	static sq box[50];
	

	PAINTSTRUCT ps;
	HDC hdc;
	SYSTEMTIME curTime;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;

	srand(time(NULL));

	switch (uMsg) {
	case WM_CREATE:
		select = FALSE;
		bar_x = 350; bar_y = 600;
		cir_x = 385; cir_y = 570;

		memset(box, NULL, (sq*)sizeof(box));
		vx = -5; vy = -5;
		for (int i = 0; i < 50; i++)
		{
			box[i].b = TRUE;
		}
		break;
	case WM_TIMER:
		// Movement
		if (on == 1) {
			Timer1Count++;
			cir_x += vx * v;
			cir_y += vy * v;

			for (int i = 0; i < 10*box_num; i++)
			{
				if (box[i].b)
				{
					box[i].left = 150 + (50 * (i % 10));
					box[i].top = 50 + (30 * (i / 10));
					box[i].right = 200 + (50 * (i % 10));
					box[i].bottom = 80 + (30 * (i / 10));
				}
			}

			if (cir_x <= 0) vx *= -1;
			else if (cir_x + (10 * cir_size) >= 780) vx *= -1;
			else if (cir_y <= 0) vy *= -1;
			else if (cir_y + (10 * cir_size) > 750) { cir_y = 570; vy *= -1; }
			else if (cir_x > bar_x && cir_x + (10 * cir_size) < bar_x + 100 && cir_y + (10 * cir_size) >= bar_y && cir_y <= bar_y) vy *= -1;
			else
			{
				for (int i = 0; i < 10*box_num; i++)
				{
					if (box[i].b == 1 && box[i].right > cir_x && box[i].left < (cir_x + (10 * cir_size)) && box[i].bottom > cir_y && box[i].top < (cir_y + (10 * cir_size)))
					{
						switch (collision_check_x(box[i].left, box[i].top, box[i].right, box[i].bottom, cir_x, cir_y, cir_x + (10 * cir_size), cir_y + (10 * cir_size)))
						{
						case 1:
						case 2:
							vx *= -1;
							cir_x += vx;
							box[i].b = FALSE;
							break;
						default:
							break;
						}
						switch (collision_check_y(box[i].left, box[i].top, box[i].right, box[i].bottom, cir_x, cir_y, cir_x + (10 * cir_size), cir_y + (10 * cir_size)))
						{
						case 3:
						case 4:
							vy *= -1;
							cir_y += vy;
							box[i].b = FALSE;
							break;
						default:
							break;
						}
						if (box[i].b == FALSE) break;
					}
				}
			}
			// check crash
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_GAME_START:
			SetTimer(hWnd, 1, 100, NULL);
			on = 1;
			break;
		case ID_GAME_RESET:
			select = FALSE;
			bar_x = 350; bar_y = 600;
			cir_x = 385; cir_y = 570;
			vx = -5; vy = -5;
			for (int i = 0; i < 30; i++) box[i].b = TRUE;
			on = 0;
			break;
		case ID_GAME_PAUSE:
			on = 0;
			break;
		case ID_GAME_END:
			exit(-1);
			break;
		case ID_SPEED_FASTER:
			v = 6;
			break;
		case ID_SPEED_MEDIUM:
			v = 5;
			break;
		case ID_SPEED_SLOWER:
			v = 3;
			break;
		case ID_SIZE_BIG:
			cir_size = 3;
			break;
		case ID_SIZE_SMALL:
			cir_size = 2;
			break;
		case ID_COLOR_RED:
			color = 1;
			break;
		case ID_COLOR_GREEN:
			color = 2;
			break;
		case ID_COLOR_BLUE:
			color = 3;
			break;
		case ID_BLOCK_3:
			box_num = 3;
			break;
		case ID_BLOCK_4:
			box_num = 4;
			break;
		case ID_BLOCK_5:
			box_num = 5;
			break;
		default:
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (bar_x < mx && bar_x + 100 > mx && bar_y < my && bar_y + 30 > my) select = TRUE;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_LBUTTONUP:
		select = FALSE;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_MOUSEMOVE:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (select)
		{
			bar_x = mx - 50;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
		if (color == 1) hBrush = CreateSolidBrush(RGB(255, 0, 0));
		else if (color == 2) hBrush = CreateSolidBrush(RGB(0, 255, 0));
		else if (color == 3) hBrush = CreateSolidBrush(RGB(0, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	

		for (int i = 0; i < 10*box_num; i++)
		{
			if (box[i].b)
				Rectangle(hdc, box[i].left, box[i].top, box[i].right, box[i].bottom);
		}

		hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);	
		Ellipse(hdc, cir_x, cir_y, cir_x + (10 * cir_size), cir_y + (10 * cir_size));
		Rectangle(hdc, bar_x, bar_y, bar_x + 100, bar_y + 30);

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

void CALLBACK TimerProcA(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;

	hdc = BeginPaint(hWnd, &ps);

	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	oldPen = (HPEN)SelectObject(hdc, hPen);
	Ellipse(hdc, line_w * (location % 40), line_d * (location / 40), line_w * (location % 40) + line_w, line_w * (location / 40) + line_d);

	EndPaint(hWnd, &ps);
}

int collision_check_x(int box_x1, int box_y1, int box_x2, int box_y2, int cir_x1, int cir_y1, int cir_x2, int cir_y2)
{
	if (box_x1 < cir_x2 && box_y1 < cir_y2 && box_y2 > cir_y1)
	{
		return 1; // left
	}
	else if (box_x2 > cir_x1 && box_y1 < cir_y2 && box_y2 > cir_y1)
	{
		return 2; // right
	}
}
int collision_check_y(int box_x1, int box_y1, int box_x2, int box_y2, int cir_x1, int cir_y1, int cir_x2, int cir_y2)
{
	if (box_x1 < cir_x2 && box_x2 > cir_x1 && box_y1 < cir_y2)
	{
		return 3; // top
	}
	else if (box_x1 < cir_x2 && box_x2 > cir_x1 && box_y2 > cir_y1)
	{
		return 4; // bottom
	}
}