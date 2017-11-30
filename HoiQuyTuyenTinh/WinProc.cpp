#include "HoiQuyTuyenTinh.h"
#include "resource.h"
LRESULT CALLBACK WinProc(HWND wd, UINT id, WPARAM w, LPARAM l)
{
	static RECT dlg_size;
	static HCURSOR chuot = LoadCursor(GetModuleHandle(0), MAKEINTRESOURCE(IDC_CURSOR1));
	switch (id)
	{
	case WM_CREATE:
	{
		Dlg[0] = CreateDialog(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG1), wd, Dlg1Proc);
		GetWindowRect(Dlg[0], &dlg_size);
		PlaySound(MAKEINTRESOURCE(IDR_WAVE1), GetModuleHandle(0), SND_RESOURCE | SND_ASYNC);
		return 0;
	}
	case WM_SIZE:
	{
		RECT s,s1, s2;
		int A, B;
		GetWindowRect(wd, &s1);
		GetClientRect(wd, &s2);
		A = s1.right - s1.left - (s2.right - s2.left);
		B = s1.bottom - s1.top - (s2.bottom - s2.top);
		GetWindowRect(GetDesktopWindow(), &s);
		int Dx = s.right - s.left;
		int Dy = s.bottom - s.top;
		int dx = dlg_size.right - dlg_size.left + A;
		int dy = dlg_size.bottom - dlg_size.top + B;
		int xo = (Dx - dx) / 2;
		int yo = (Dy - dy) / 2;
		MoveWindow(wd, xo, yo, dx, dy, TRUE);
		return 0;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_SETCURSOR:
	{
		SetCursor(chuot);
		return 1;
	}
	}
	return DefWindowProc(wd, id, w, l);
}