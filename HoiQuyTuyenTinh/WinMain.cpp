#include "HoiQuyTuyenTinh.h"
#include "resource.h"
HWND Dlg[4];
HWND cs;
bool k = false;
POINT tam;
POINT diem;
float gPixel;
vector<DATA> dulieu;
DATA A;
double ex;
double ey;
double phuongsaix;
double phuongsaiy;
double modx;
double mody;
double dlcx;
double dlcy;
double cov;
double corr;
POINT c;
DATA change;
vector<TANSUAT> tansuat;
int WINAPI WinMain(HINSTANCE a, HINSTANCE b, LPSTR c, int d)
{
	WNDCLASS lcs;
	MSG td;
	lcs.style = 0;
	lcs.hIcon = LoadIcon(a, MAKEINTRESOURCE(IDI_ICON1));
	lcs.cbWndExtra = lcs.cbClsExtra = 0;
	lcs.hCursor = LoadCursor(NULL, IDC_ARROW);
	lcs.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);
	lcs.hInstance = a;
	lcs.lpszClassName = L"LCS";
	lcs.lpfnWndProc = WinProc;
	lcs.lpszMenuName = NULL;
	RegisterClass(&lcs);
	cs = CreateWindow(L"LCS", TEN_UNG_DUNG, WS_OVERLAPPED|WS_BORDER|WS_MINIMIZEBOX|WS_CAPTION|WS_SYSMENU, 100, 100, 1000, 800, HWND_DESKTOP, NULL, a, NULL);
	ShowWindow(cs, d);
	UpdateWindow(cs);
	while (GetMessage(&td, NULL, 0, 0) > 0)
	{
		TranslateMessage(&td);
		DispatchMessage(&td);
	}
	return 0;
}