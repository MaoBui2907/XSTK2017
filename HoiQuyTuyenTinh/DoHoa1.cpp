#include "HoiQuyTuyenTinh.h"
#include "resource.h"


void DrawBmp(HWND wd, LPCWSTR id_bmp)
{
	PAINTSTRUCT     ps;
	HDC             hdc;
	BITMAP          bitmap;
	HDC             hdcMem;
	HGDIOBJ         oldBitmap;
	HBITMAP hBitmap = (HBITMAP)LoadImage(GetModuleHandle(0), id_bmp, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	hdc = BeginPaint(wd, &ps);
	hdcMem = CreateCompatibleDC(hdc);
	oldBitmap = SelectObject(hdcMem, hBitmap);
	GetObject(hBitmap, sizeof(bitmap), &bitmap);
	BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
	SelectObject(hdcMem, oldBitmap);
	DeleteDC(hdcMem);
	EndPaint(wd, &ps);
}
void KichThuoc(HWND wd)
{
	RECT s;
	GetWindowRect(wd, &s);
	char text[100];
	wsprintfA(text, "%d %d", s.right - s.left, s.bottom - s.top);
	MessageBoxA(wd, text, "", MB_OK);
}
void VeOxy(HWND wd, POINT tam)
{
	HDC dc = GetDC(wd);
	Rectangle(dc, 0, 44, 488, 492);
	/*SelectObject(dc, GetStockObject(BLACK_BRUSH));
	Ellipse(dc, tam.x - 3, tam.y - 3, tam.x + 3, tam.y + 3);*/
	//Vẽ Ox
	HBRUSH redbrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldbrush = (HBRUSH)SelectObject(dc, redbrush);
	SelectObject(dc, GetStockObject(NULL_PEN));
	Rectangle(dc, 0, tam.y - 1, 488, tam.y + 1);
	SelectObject(dc, oldbrush);
	DeleteObject(redbrush);
	//Vẽ Oy
	HBRUSH greenbrush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH goldbrush = (HBRUSH)SelectObject(dc, greenbrush);
	Rectangle(dc, tam.x - 1, 45, tam.x + 1, 492);
	SelectObject(dc, goldbrush);
	DeleteObject(greenbrush);
	ReleaseDC(wd, dc);

	// kí hiệu 1 vài điểm trên các trục:
	float maxX, maxY, minX, minY;
	minX = (0 - tam.x) / gPixel;
	minY = -(448 + 44 - tam.y) / gPixel;
	maxX = (488 - tam.x) / gPixel;
	maxY = -(44 - tam.y) / gPixel;
	for (int i = minX; i <= maxX; i++) 
	{
		drawPoint(wd, i, 0, tam, RGB(0, 255, 250));
		drawPoint(wd, 0, i, tam, RGB(178, 0, 255));
	}
	//vẽ gốc tọa độ:
	drawPoint(wd, 0, 0, tam, RGB(0, 0, 0));
}

// Set số pixel cho 1 đơn vị:
float setPixelGlobal(int s) {
	float out;
	out = 35.0 - s*0.3;
	return out;
}

// tạo point đơn vị pixel:
POINT initPoint(long a, long b) {
	POINT temp;
	temp.x = a;
	temp.y = b;
	return temp;
}
//trả về vị trí so với tâm của điểm (x,y):
POINT getLocateFromCoord(POINT tam, float x, float y) {
	POINT A;
	A.x = x * gPixel + tam.x;
	A.y = -y * gPixel + tam.y;
	return A;
}
//vẽ điểm:
void drawPoint(HWND wd, float x, float y, POINT tam, COLORREF C) {
	POINT A = getLocateFromCoord(tam, x, y);
	HDC dc = GetDC(wd);

	for (int i = -3; i < 2; i++) {
		for (int j = -3; j < 2; j++) {
			SetPixel(dc, A.x + i, A.y + j, C);
		}
	}
	ReleaseDC(wd,dc);
}
// vẽ y=ax+b:
void drawLine(HWND wd, float a, float b, POINT tam) {
	POINT A, B;
	float maxX, maxY, minX, minY;
	minX = (0 - tam.x) / gPixel;
	minY = -(448 + 44 - tam.y) / gPixel;
	maxX = (488 - tam.x) / gPixel;
	maxY = -(44 - tam.y) / gPixel;
	if (a >= 0) {
		if (minY > (a*minX + b)) {
			float temp = (minY - b) / a;
			A = getLocateFromCoord(tam, temp, minY);
		}
		else {
			float temp = minX * a + b;
			A = getLocateFromCoord(tam, minX, temp);
		}
		if (maxY > (a*maxX + b)) {
			float temp = maxX * a + b;
			B = getLocateFromCoord(tam, maxX, temp);
		}
		else {
			float temp = (maxY - b) / a;
			B = getLocateFromCoord(tam, temp, maxY);
		}
	}
	else {
		if (minY > (a*maxX + b)) {
			float temp = (minY - b) / a;
			A = getLocateFromCoord(tam, temp, minY);
		}
		else {
			float temp = maxX * a + b;
			A = getLocateFromCoord(tam, maxX, temp);
		}
		if (maxY > (a*minX + b)) {
			float temp = minX * a + b;
			B = getLocateFromCoord(tam, minX, temp);
		}
		else {
			float temp = (maxY - b) / a;
			B = getLocateFromCoord(tam, temp, maxY);
		}
	}
	HDC dc = GetDC(wd);
	HPEN oldPen, currentPen;
	currentPen = CreatePen(PS_SOLID, 3, RGB(224, 2, 2));
	oldPen = (HPEN)SelectObject(dc, currentPen);
	MoveToEx(dc, A.x, A.y, NULL);
	LineTo(dc, B.x, B.y);
	DeleteObject(currentPen);
}
// vẽ y=ax2+bx+c:
//void drawParabol(HWND wd, float a, float b, float c, POINT tam) {
//	float maxX, maxY, minX, minY;
//	minX = (0 - tam.x) / gPixel;
//	minY = -(448 + 44 - tam.y) / gPixel;
//	maxX = (488 - tam.x) / gPixel;
//	maxY = -(44 - tam.y) / gPixel;
//	for (float i = minX; i <= maxX; i += 0.025) {
//		float temp = a*i*i + b*i + c;
//		if (temp > maxY || temp < minY) {
//			continue;
//		}
//		drawPoint(wd, i, temp, tam, RGB(0, 0, 0));
//	}
//}
// trả về vị trí con trỏ:
POINT getPointMouse(POINT tam, float gPixel) {
	POINT p,q;
	GetCursorPos(&p);
	q.x = (p.x - tam.x) / gPixel;
	q.y = (tam.y - p.y) / gPixel;
	return q;
}