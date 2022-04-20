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

void CALLBACK TimerProcA(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
void CALLBACK TimerProcB(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);

typedef struct {
	int x, y;
} element;
typedef struct tail {
	element coor;
	int movement;
} tail_cir;
typedef struct obstacle {
	element coor;
} obstacle;

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
	static int Timer1Count = 0, Timer2Count = 0, on = 0, velocity = 1, v = 10, t = 0;
	PAINTSTRUCT ps;
	HDC hdc;
	SYSTEMTIME curTime;
	HPEN hPen, oldPen;
	static tail_cir tail[MAX_NUM];
	static obstacle ob[MAX_NUM];

	srand(time(NULL));

	switch (uMsg) {
	case WM_CREATE:
		memset(tail, NULL, (tail_cir*)sizeof(tail));
		memset(ob, NULL, (obstacle*)sizeof(ob));
		break;
	case WM_TIMER:
		//if (t % v == 0)
		{
			if (on == 1) {
				switch (wParam)
				{
				case 1:
					Timer1Count++;
					if (location + velocity > 0 && location + velocity < 1600) location = (location + velocity) % 1600;
					else if (location + velocity < 0) location = (location + 1561) % 1600;
					else if (location + velocity > 1600) location = (location - 1559) % 1600;
					break;
				case 2:
					Timer2Count++;

					break;
				}

			}
		}

		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_LBUTTONDOWN:

		break;
	case WM_RBUTTONDOWN:

		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 's':
		case 'S':
			SetTimer(hWnd, 1, 100, NULL);
			SetTimer(hWnd, 2, 2000 * rand() % 8, NULL);
			on = 1;
			break;
		case 109: // -
			if (v > 0 && v < 100) v += 10;
			else break;
			SetTimer(hWnd, 1, 10*v, NULL);
			break;
		case 107: // +
			if (v > 50) v -= 50;
			else v = 5;
			SetTimer(hWnd, 1, 10*v, NULL);
			break;
		case 'j':
		case 'J':

			break;
		case 't':
		case 'T':

			break;
		case 'q':
		case 'Q':
			exit(-1);
			break;
		case VK_LEFT:
			velocity = -1;
			break;
		case VK_RIGHT:
			velocity = 1;
			break;
		case VK_UP:
			velocity = -40;
			break;
		case VK_DOWN:
			velocity = 40;
			break;
		default:
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		hPen = CreatePen(PS_DOT, 1, RGB(0,0,0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		Ellipse(hdc, line_w * (location % 40), line_d * (location / 40), line_w * (location % 40) + line_w, line_w * (location / 40) + line_d);

		for (int i = 0; i < 40 + 1; i++)
		{
			MoveToEx(hdc, line_w * i, 0, NULL);
			LineTo(hdc, line_w * i, window_size_d-40);
			MoveToEx(hdc, 0, line_d * i, NULL);
			LineTo(hdc, window_size_w-40, line_d * i);
		}
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
/*
void CALLBACK TimerProcB(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;

	hdc = BeginPaint(hWnd, &ps);

	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	oldPen = (HPEN)SelectObject(hdc, hPen);
	

	EndPaint(hWnd, &ps);
}*/