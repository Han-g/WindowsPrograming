#define window_size_w 800
#define window_size_d 600

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

int board_square = 40, select_num = 0, shape[10] = { 0, }, shape_x1 = 0, shape_y1 = 0, shape_x2 = 0, shape_y2 = 0, count = 0;
typedef struct LOCATE {
	int x1; int x2; int y1; int y2;
}locate;

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
			if (locates[select_num].x2 != locates[select_num].x1 + line_w) {
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
			shape[select_num - 1] = 0;
			for (int i = select_num - 1; i < 9; i++)
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

		for (int i = 0; i < board_square + 1; i++)
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

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}