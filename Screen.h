#ifndef __Screen_H__
#define __Screen_H__
// �������
#include <windows.h>

class Screen
{
public:
	int init(int width, int height, LPCTSTR title); // ��ʼ������
	void update(unsigned long long deltaTime); // ����
	void dispatch(); // �ɷ���Ϣ
	unsigned long long GetCurTime();
	void close(); // �ر�
	int isKeyPressed(int key); // ���Ƿ񱻰���
	int getKeyUpEvent(int key);
	int isExit(); // �Ƿ�ر�
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