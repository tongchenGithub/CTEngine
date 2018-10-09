#include "Screen.h"
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>

int ScreenKeys[512]; // 记录键盘状态
int ScreenUpKeys[512]; // 记录键盘是否被放开
int Exit = 0;

static LRESULT WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	switch (uMsg) {
	case WM_CLOSE:Exit = 1; break;
	case WM_KEYDOWN:ScreenKeys[wParam & 511] = 1; break;
	case WM_KEYUP:ScreenKeys[wParam & 511] = 0; ScreenUpKeys[wParam & 511] = 1; break;
	default:return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

int Screen::init(int width, int height, LPCTSTR title)
{
	WNDCLASS wc = { CS_BYTEALIGNCLIENT, (WNDPROC)WndProc, 0, 0, 0, NULL, NULL, NULL, NULL, _T("SCREEN") };
	// -height 表示 top-down
	BITMAPINFO bi = { { sizeof(BITMAPINFOHEADER), width, -height, 1, 32, BI_RGB, width * height * 4, 0, 0, 0, 0 } };
	RECT rect = { 0, 0, width, height };

	this->close();

	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hInstance = GetModuleHandle(NULL);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	if (!RegisterClass(&wc)) return -1;

	wndHandle = CreateWindow(_T("SCREEN"), title, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 0, 0, 0, 0, NULL, NULL, wc.hInstance, NULL);
	if (wndHandle == NULL) return -2;

	HDC hDC = GetDC(wndHandle);
	wndDc = CreateCompatibleDC(hDC);
	ReleaseDC(wndHandle, hDC);

	wndHb = CreateDIBSection(wndDc, &bi, DIB_RGB_COLORS, &wndFramebuffer, 0, 0);
	if (wndHb == NULL) return -3;

	wndOb = (HBITMAP)SelectObject(wndDc, wndHb);
	this->width = width;
	this->height = height;

	AdjustWindowRect(&rect, GetWindowLong(wndHandle, GWL_STYLE), 0);
	int wx = rect.right - rect.left;
	int wy = rect.bottom - rect.top;
	int sx = (GetSystemMetrics(SM_CXSCREEN) - wx) / 2;
	int sy = (GetSystemMetrics(SM_CYSCREEN) - wy) / 2;
	if (sy < 0) sy = 0;
	SetWindowPos(wndHandle, NULL, sx, sy, wx, wy, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));
	SetForegroundWindow(wndHandle);

	ShowWindow(wndHandle, SW_NORMAL);
	dispatch();

	memset(wndFramebuffer, 0, width * height * 4);
	memset(ScreenKeys, 0, sizeof(int) * 512);

	return 0;
}

void Screen::update(unsigned long long deltaTime)
{
	HDC hDC = GetDC(wndHandle);

	HFONT hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"微软雅黑");  //创建一种字体
	SelectObject(wndDc, hFont);  //将字体选入设备环境中
	SetBkMode(wndDc, TRANSPARENT);    //设置输出文字背景色为透明
									  //定义三段文字
	wchar_t text1[] = _T("key left/right rotation");
	wchar_t text2[] = _T("key up/down near/far");
	wchar_t text3[] = _T("key WASD change position");
	wchar_t text4[] = _T("key space change module");
	wchar_t text7[] = _T("key enter change model");
	wchar_t text5[] = _T("1 change interp");
	wchar_t text6[] = _T("2 cullback");
	wchar_t text8[] = _T("3 light on/off");
	wchar_t text9[] = _T("4 draw bmp");

	SetTextColor(wndDc, RGB(50, 50, 255));
	TextOut(wndDc, 10, 0, text1, wcslen(text1));
	SetTextColor(wndDc, RGB(50, 50, 255));
	TextOut(wndDc, 10, 20, text2, wcslen(text2));
	SetTextColor(wndDc, RGB(50, 50, 255));
	TextOut(wndDc, 10, 40, text3, wcslen(text3));
	SetTextColor(wndDc, RGB(255, 150, 50));
	TextOut(wndDc, 10, 60, text4, wcslen(text4));
	SetTextColor(wndDc, RGB(255, 150, 50));
	TextOut(wndDc, 10, 80, text7, wcslen(text7));
	SetTextColor(wndDc, RGB(255, 150, 50));
	TextOut(wndDc, 10, 100, text5, wcslen(text5));
	SetTextColor(wndDc, RGB(255, 150, 50));
	TextOut(wndDc, 10, 120, text6, wcslen(text6));
	SetTextColor(wndDc, RGB(255, 150, 50));
	TextOut(wndDc, 10, 140, text8, wcslen(text8));
	SetTextColor(wndDc, RGB(255, 150, 50));
	TextOut(wndDc, 10, 160, text9, wcslen(text9));

	int fps = static_cast<int>(1000.f / deltaTime);

	wchar_t FPS[10];
	swprintf(FPS, 10, L"FPS：%d", fps);

	//设置文字颜色并输出FPS
	SetTextColor(wndDc, RGB(255, 255, 50));
	TextOut(wndDc, 700, 10, FPS, wcslen(FPS));

	DeleteObject(hFont);//释放字体对象
	BitBlt(hDC, 0, 0, width, height, wndDc, 0, 0, SRCCOPY);
	ReleaseDC(wndHandle, hDC);
	dispatch();
}

unsigned long long Screen::GetCurTime()
{
	SYSTEMTIME  systime;        //时间结构声明，这个结构是系统的，  
	::GetLocalTime(&systime);
	time_t curr_t = time(NULL);
	unsigned long long tld = (unsigned long long)curr_t;
	unsigned long millSec = (unsigned long)(systime.wMilliseconds);
	return tld * 1000 + millSec; // return ms
}

void Screen::dispatch()
{
	MSG msg;
	while (1) {
		if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) break;
		if (!GetMessage(&msg, NULL, 0, 0)) break;
		DispatchMessage(&msg);
	}
}

void Screen::close()
{
	if (wndDc) {
		if (wndOb) {
			SelectObject(wndDc, wndOb);
			wndOb = NULL;
		}
		DeleteDC(wndDc);
		wndDc = NULL;
	}

	if (wndHb) {
		DeleteObject(wndHb);
		wndHb = NULL;
	}

	if (wndHandle) {
		CloseWindow(wndHandle);
		wndHandle = NULL;
	}
}

int Screen::isKeyPressed(int key)
{
	return ScreenKeys[key & 511];
}

int Screen::getKeyUpEvent(int key)
{
	int r = ScreenUpKeys[key];
	ScreenUpKeys[key] = 0;
	return r;
}

int Screen::isExit()
{
	return Exit;
}

LPVOID Screen::getFrameBuffer()
{
	return wndFramebuffer;
}