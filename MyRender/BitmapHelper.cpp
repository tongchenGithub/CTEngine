#include "BitmapHelper.h"
#include <windows.h>
#include <gdiplus.h>

#include <iostream>
#include <fstream>
#include <sstream>

#pragma comment(lib, "gdiplus.lib")
using namespace std;
using namespace Gdiplus;

int* LoadBitmapFromFile(wstring filePath)
{
	GdiplusStartupInput gdiplusstartupinput;
	ULONG_PTR gdiplustoken;
	GdiplusStartup(&gdiplustoken, &gdiplusstartupinput, nullptr);

	Bitmap* bmp = new Bitmap(filePath.c_str());
	if (!bmp)
	{
		delete bmp;
		GdiplusShutdown(gdiplustoken);
		return 0;
	}
	else
	{
		UINT height = bmp->GetHeight();
		UINT width = bmp->GetWidth();
		int *tex = (int*)malloc(width * height * sizeof(int)); // 本项目中提供的图片大小最好是100*100

		Color color;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				bmp->GetPixel(x, y, &color);
				tex[y * height + x] = color.GetValue();
			}
		}
			
		delete bmp;
		GdiplusShutdown(gdiplustoken);
		return tex;
	}
}