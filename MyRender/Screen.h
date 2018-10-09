#ifndef __Screen_H__
#define __Screen_H__
// 窗口相关
#include <windows.h>

class Screen
{
public:
	int init(int width, int height, LPCTSTR title); // 初始化窗口
	void update(unsigned long long deltaTime); // 更新
	void dispatch(); // 派发消息
	unsigned long long GetCurTime();
	void close(); // 关闭
	int isKeyPressed(int key); // 键是否被按下
	int getKeyUpEvent(int key);
	int isExit(); // 是否关闭
	LPVOID getFrameBuffer();

private:
	HWND wndHandle;
	HDC wndDc;
	HBITMAP wndHb;
	HBITMAP wndOb;
	LPVOID wndFramebuffer; // framebuffer
	int width;
	int height;
};
#endif