#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Comctl32.lib")
#include <windows.h> 
#include <commctrl.h>
#include <stdio.h>
#include <stdlib.h>
#include <windowsx.h>
#include <vector>
#include <math.h>
using namespace std;
//Cấu trúc
struct DATA
{
	double x;
	double y;
};
struct TANSUAT
{
	DATA giatri;
	int tansuat;
};
//Khai báo biến chung
extern HWND Dlg[4];
extern bool k;
extern POINT tam;
extern POINT diem;
extern float gPixel;
extern vector<DATA> dulieu;
extern DATA A;
extern double ex;
extern double ey;
extern double phuongsaix;
extern double modx;
extern double mody;
extern double phuongsaiy;
extern double dlcx;
extern double dlcy;
extern double cov;
extern double corr;
extern vector<TANSUAT> tansuat;
extern POINT c;
extern HWND cs;
extern DATA change;
//Khai báo macro
#define TEN_UNG_DUNG L"SXTK"
//Khai báo hàm
LRESULT CALLBACK WinProc(HWND wd, UINT id, WPARAM w, LPARAM l);
BOOL CALLBACK Dlg1Proc(HWND wd, UINT id, WPARAM w, LPARAM l);
BOOL CALLBACK Dlg2Proc(HWND wd, UINT id, WPARAM w, LPARAM l);
BOOL CALLBACK Dlg3Proc(HWND wd, UINT id, WPARAM w, LPARAM l);
BOOL CALLBACK Dlg4Proc(HWND wd, UINT id, WPARAM w, LPARAM l);
BOOL CALLBACK Dlg5Proc(HWND wd, UINT id, WPARAM w, LPARAM l);
BOOL CALLBACK Dlg6Proc(HWND wd, UINT id, WPARAM w, LPARAM l);
void DrawBmp(HWND wd, LPCWSTR id_bmp, int x, int y);
void KichThuoc(HWND wd);
void VeOxy(HWND wd);
float setPixelGlobal(int s);
POINT initPoint(long a, long b);
POINT getLocateFromCoord(float x, float y);
void drawPoint(HDC dc, float x, float y, COLORREF C);
void drawLine(HWND wd, float a, float b);
void VeCham(HWND wd);
void XuatTSX();
void XuatTSY();
void timAB();
void TinhTanSuat();
bool Kiemtra();
void veBang(HWND wd);
double TinhModX();
double TinhModY();
double TinhHiepPhuongSai();
double TinhHeSoTuongQuan();
//1008x636
//Tin nhắn riêng
#define WM_VECHAM WM_USER
#define WM_THEMDIEM (WM_USER + 1)
#define WM_TINHTHONGSO (WM_USER + 2)
#define WM_VEDUONGTHANG (WM_USER + 3)

