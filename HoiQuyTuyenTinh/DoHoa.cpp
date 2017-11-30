#include "HoiQuyTuyenTinh.h"
#include "resource.h"
void DrawBmp(HWND wd, LPCWSTR id_bmp, int x, int y)
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
	BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, x, y, SRCCOPY);
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
void VeOxy(HWND wd)
{
	HDC dc = GetDC(wd);
	Rectangle(dc, 0, 44, 488, 492);
	SelectObject(dc, GetStockObject(BLACK_BRUSH));
	//Vẽ Ox
	HBRUSH redbrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldbrush = (HBRUSH)SelectObject(dc, redbrush);
	SelectObject(dc, GetStockObject(NULL_PEN));
	if (tam.y > 45)
	{
		Rectangle(dc, 0, tam.y - 1, 488, tam.y + 1);
	}
	SelectObject(dc, oldbrush);
	DeleteObject(redbrush);
	//Vẽ Oy
	HBRUSH greenbrush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH goldbrush = (HBRUSH)SelectObject(dc, greenbrush);
	Rectangle(dc, tam.x - 1, 45, tam.x + 1, 492);
	SelectObject(dc, goldbrush);
	DeleteObject(greenbrush);
	float maxX, maxY, minX, minY;
	minX = (0 - tam.x) / gPixel;
	minY = -(448 + 44 - tam.y) / gPixel;
	maxX = (488 - tam.x) / gPixel;
	maxY = -(44 - tam.y) / gPixel;
	for (int i = minX; i <= maxX; i++)
	{
		drawPoint(dc, i, 0, RGB(0, 255, 250));
	}
	for (int i = minY; i <= maxY; i++)
	{
		drawPoint(dc, 0, i, RGB(178, 0, 255));
	}
	ReleaseDC(wd, dc);
}
float setPixelGlobal(int s) 
{
	float out;
	out = 35.0 - s*0.3;
	return out;
}

// tạo point đơn vị pixel:
POINT initPoint(long a, long b) 
{
	POINT temp;
	temp.x = a;
	temp.y = b;
	return temp;
}
//trả về vị trí so với tâm của điểm (x,y):
POINT getLocateFromCoord(float x, float y) 
{
	POINT A;
	A.x = x * gPixel + tam.x;
	A.y = -y * gPixel + tam.y;
	return A;
}
//vẽ điểm:
void drawPoint(HDC dc, float x, float y, COLORREF C)
{
	POINT A = getLocateFromCoord(x, y);
	if (A.y > 46)
	{
		SelectObject(dc, GetStockObject(NULL_BRUSH));
		SelectObject(dc, GetStockObject(BLACK_PEN));
		Ellipse(dc, A.x - 3, A.y - 3, A.x + 3, A.y + 3);
	}
}
// vẽ y=ax+b:
void drawLine(HWND wd, float a, float b)
{
	POINT A, B;
	float maxX, maxY, minX, minY;
	minX = (0 - tam.x) / gPixel;
	minY = -(448 + 45 - tam.y) / gPixel;
	maxX = (488 - tam.x) / gPixel;
	maxY = -(45 - tam.y) / gPixel;
	if (a >= 0) {
		if (minY > (a*minX + b)) {
			float temp = (minY - b) / a;
			A = getLocateFromCoord(temp, minY);
		}
		else {
			float temp = minX * a + b;
			A = getLocateFromCoord(minX, temp);
		}
		if (maxY > (a*maxX + b)) {
			float temp = maxX * a + b;
			B = getLocateFromCoord(maxX, temp);
		}
		else {
			float temp = (maxY - b) / a;
			B = getLocateFromCoord(temp, maxY);
		}
	}
	else {
		if (minY > (a*maxX + b)) {
			float temp = (minY - b) / a;
			A = getLocateFromCoord(temp, minY);
		}
		else {
			float temp = maxX * a + b;
			A = getLocateFromCoord(maxX, temp);
		}
		if (maxY > (a*minX + b)) {
			float temp = minX * a + b;
			B = getLocateFromCoord(minX, temp);
		}
		else {
			float temp = (maxY - b) / a;
			B = getLocateFromCoord(temp, maxY);
		}
	}
	HDC dc = GetDC(wd);
	HPEN oldPen, currentPen;
	currentPen = CreatePen(PS_SOLID, 3, RGB(8, 2, 230));
	oldPen = (HPEN)SelectObject(dc, currentPen);
	MoveToEx(dc, A.x, A.y, NULL);
	LineTo(dc, B.x, B.y);
	DeleteObject(currentPen);
	ReleaseDC(wd, dc);
}
void VeCham(HWND wd)
{
	
	int kt = dulieu.size();
	HDC hdc = GetDC(wd);
	for (int i = 0; i < kt; i++)
	{
		DATA k = dulieu[i];
		int x = k.x * gPixel + tam.x;
		int y = -(k.y * gPixel) + tam.y;
		SelectObject(hdc, GetStockObject(BLACK_BRUSH));
		if (y > 46)
		{
			Ellipse(hdc, x - 3, y - 3, x + 3, y + 3);
		}
	}
	ReleaseDC(wd, hdc);
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
void veBang(HWND wd) 
{
	vector<double> temp1, temp2;
	for (int i = 0; i < tansuat.size(); i++) {
		if (temp1.empty())
		{
			temp1.push_back(tansuat[i].giatri.x);
		}
		else
		{
			bool c = false;
			for (int j = 0; j < temp1.size(); j++) {
				if (tansuat[i].giatri.x == temp1[j]) {
					c = true;
					break;
				}
			}
			if (!c) {
				temp1.push_back(tansuat[i].giatri.x);
			}
		}
	}
	for (int i = 0; i < tansuat.size(); i++) {
		if (temp2.empty())
		{
			temp2.push_back(tansuat[i].giatri.y);
		}
		else
		{
			bool c = false;
			for (int j = 0; j < temp2.size(); j++) {
				if (tansuat[i].giatri.y == temp2[j]) {
					c = true;
					break;
				}
			}
			if (!c) {
				temp2.push_back(tansuat[i].giatri.y);
			}
		}
	}
	HDC dc = GetDC(wd);
	HPEN oldPen, curPen;
	curPen = CreatePen(PS_SOLID, 3, RGB(8, 2, 230));
	oldPen = (HPEN)SelectObject(dc, curPen);
	for (int i = 0; i <= temp2.size() + 1; i++) {
		for (int j = 0; j <= temp1.size() + 1; j++) {
			Rectangle(dc, c.x + j * 170, c.y + i * 50, c.x + 170 + j * 170, c.y + i * 50 + 50);
			if (i == 0) {
				if (j == 0) {
					char text[20];
					snprintf(text, sizeof(text), "X");
					TextOutA(dc, c.x + 120, c.y + 10, text, strlen(text));
					snprintf(text, sizeof(text), "Y");
					TextOutA(dc, c.x + 50, c.y + 25, text, strlen(text));
				}
				if (j > 0 && j <= temp1.size()) {
					char text[20];
					snprintf(text, sizeof(text), "%.2f", temp1[j - 1]);
					TextOutA(dc, c.x + 85 + j * 170, c.y + 20 + i * 50, text, strlen(text));
				}
				if (j == temp1.size() + 1) {
					char text[20];
					snprintf(text, sizeof(text), "Px");
					TextOutA(dc, c.x + 85 + j * 170, c.y + 20 + i * 50, text, strlen(text));
				}
			}
			else {
				if (j == 0) {
					if (i > 0 && i <= temp2.size()) {
						char text[20];
						snprintf(text, sizeof(text), "%.2f", temp2[i - 1]);
						TextOutA(dc, c.x + 85 + j * 170, c.y + 20 + i * 50, text, strlen(text));
					}
					if (i == temp2.size() + 1) {
						char text[20];
						snprintf(text, sizeof(text), "Py");
						TextOutA(dc, c.x + 85 + j * 170, c.y + 20 + i * 50, text, strlen(text));
					}
				}
				else {
					if (j == temp1.size() + 1 && i == temp2.size() + 1) {
						char text[20];
						snprintf(text, sizeof(text), "Pxy");
						TextOutA(dc, c.x + 85 + j * 170, c.y + 20 + i * 50, text, strlen(text));
					}
					else {
						if (j == temp1.size() + 1) {
							double dd = 0;
							for (int g = 0; g < tansuat.size(); g++) {
								if (temp2[i - 1] == tansuat[g].giatri.y) {
									dd += tansuat[g].tansuat;
								}
							}
							char text[20];
							snprintf(text, sizeof(text), "%.2f", (dd / dulieu.size()));
							TextOutA(dc, c.x + 85 + j * 170, c.y + 20 + i * 50, text, strlen(text));
						}
						else {
							if (i == temp2.size() + 1) {
								double dd = 0;
								for (int g = 0; g < tansuat.size(); g++) {
									if (temp1[j - 1] == tansuat[g].giatri.x) {
										dd += tansuat[g].tansuat;
									}
								}
								char text[20];
								snprintf(text, sizeof(text), "%.2f", (dd / dulieu.size()));
								TextOutA(dc, c.x + 85 + j * 170, c.y + 20 + i * 50, text, strlen(text));
							}
							else {

								double dd = 0;
								for (int g = 0; g < tansuat.size(); g++) {
									if (temp1[j - 1] == tansuat[g].giatri.x && temp2[i - 1] == tansuat[g].giatri.y) {
										dd = tansuat[g].tansuat;
										break;
									}
								}
								char text[20];
								snprintf(text, sizeof(text), "%.2f", (dd / dulieu.size()));
								TextOutA(dc, c.x + 85 + j * 170, c.y + 20 + i * 50, text, strlen(text));
							}
						}
					}
				}
			}
		}
	}
	MoveToEx(dc, c.x, c.y, NULL);
	LineTo(dc, c.x + 170, c.y + 50);
	DeleteObject(curPen);
	ReleaseDC(wd, dc);
}