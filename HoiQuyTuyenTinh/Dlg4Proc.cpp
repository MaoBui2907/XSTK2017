#include "HoiQuyTuyenTinh.h"
#include "resource.h"
//KT: 488x492
//X: 0 -> 488
//Y: 44 -> 492
BOOL CALLBACK Dlg4Proc(HWND wd, UINT id, WPARAM w, LPARAM l)
{
	static HBRUSH NENX = CreateSolidBrush(RGB(100, 100, 100));
	static HBRUSH NENY = CreateSolidBrush(RGB(80, 80, 80));
	switch (id)
	{
	case WM_INITDIALOG:
	{
		SendMessage(GetDlgItem(wd, IDC_SLIDER1), TBM_SETPOS, TRUE, 50);
		tam.x = 244;
		tam.y = 224 + 44;
		gPixel = 35;
		return 0;
	}
	case WM_VECHAM:
	{
		VeCham(wd);
		return 0;
	}
	case WM_MOUSEWHEEL:
	{
		int wheel = GET_WHEEL_DELTA_WPARAM(w);
		if (wheel > 0)
		{
			if (gPixel < 200)
			{
				gPixel += 5;
				VeOxy(wd);
				VeCham(wd);
				if (k)
				{
					drawLine(wd, A.x, A.y);
				}
			}
		}
		else
		{
			if (gPixel > 5)
			{
				gPixel -= 5;
				VeOxy(wd);
				VeCham(wd);
				if (k)
				{
					drawLine(wd, A.x, A.y);
				}
			}
		}
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		diem.x = LOWORD(l);
		diem.y = HIWORD(l);
		return 0;
	}
	case WM_VEDUONGTHANG:
	{
		VeOxy(wd);
		VeCham(wd);
		timAB();
		drawLine(wd, A.x, A.y);
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		if (w == MK_LBUTTON && HIWORD(l) > 44)
		{
			int dx = LOWORD(l) - diem.x;
			int dy = HIWORD(l) - diem.y;
			tam.x += dx;
			tam.y += dy;
			VeOxy(wd);
			VeCham(wd);
			if (k)
			{
				drawLine(wd, A.x, A.y);
			}
			diem.x = LOWORD(l);
			diem.y = HIWORD(l);
		}
		if (HIWORD(l) > 44)
		{
			SetWindowTextA(GetDlgItem(wd, IDC_STATICX), "");
			SetWindowTextA(GetDlgItem(wd, IDC_STATICY), "");
			float x = (LOWORD(l) - tam.x) / gPixel;
			float y = (-HIWORD(l) + tam.y) / gPixel;
			char a[20];
			snprintf(a, sizeof(a), "%.2f", x);
			SetWindowTextA(GetDlgItem(wd, IDC_STATICX), a);
			snprintf(a, sizeof(a), "%.2f", y);
			SetWindowTextA(GetDlgItem(wd, IDC_STATICY), a);
		}
		int size = dulieu.size();
		for (int i = 0; i < size; i++)
		{
			DATA k = dulieu[i];
			float x = k.x * gPixel + tam.x;
			float y = -(k.y * gPixel) + tam.y;
			if (x > (LOWORD(l) - 5) && x < (LOWORD(l) + 5) && y < (HIWORD(l) + 5) && y > (HIWORD(l) - 5))
			{
				char textx[20];
				snprintf(textx, sizeof(textx), "%.2f", k.x);
				SetWindowTextA(GetDlgItem(wd, IDC_STATICX2), textx);
				char texty[20];
				snprintf(texty, sizeof(texty), "%.2f", k.y);
				SetWindowTextA(GetDlgItem(wd, IDC_STATICY3), texty);
				break;
			}
		}
		return 0;
	}
	case WM_PAINT:
	{
		DrawBmp(wd, MAKEINTRESOURCE(IDB_BIPMAP4), 0, 0);
		if (k)
		{
			VeOxy(wd);
			VeCham(wd);
			drawLine(wd, A.x, A.y);
		}
		else
		{
			VeOxy(wd);
		}
		return 0;
	}
	case WM_CTLCOLORSTATIC:
	{
		HWND X = GetDlgItem(wd, IDC_STATICX);
		HWND Y = GetDlgItem(wd, IDC_STATICY);
		HWND stt2 = GetDlgItem(wd, IDC_STATICX2);
		HWND stt3 = GetDlgItem(wd, IDC_STATICY3);
		if (X == (HWND)l || stt2 == (HWND)l)
		{
			SetTextColor((HDC)w, RGB(210, 0, 10));
			SetBkColor((HDC)w, RGB(0, 0, 0));
			SetBkMode((HDC)w, TRANSPARENT);
			return (INT_PTR)NENX;
		}
		else if (Y == (HWND)l || stt3 == (HWND)l)
		{
			SetTextColor((HDC)w, RGB(14, 210, 10));
			SetBkColor((HDC)w, RGB(0, 0, 0));
			SetBkMode((HDC)w, TRANSPARENT);
			return (INT_PTR)NENY;
		}
		return 0;
	}
	}
	return 0;
}