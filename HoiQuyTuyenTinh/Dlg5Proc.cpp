#include "HoiQuyTuyenTinh.h"
#include "resource.h"
BOOL CALLBACK Dlg5Proc(HWND wd, UINT id, WPARAM w, LPARAM l)
{
	switch (id)
	{
	case WM_INITDIALOG:
	{
		ShowWindow(cs, 0);
		c.x = c.y = 0;
		SetScrollRange(wd, SB_HORZ, 0, 1000, TRUE);
		SetScrollRange(wd, SB_VERT, 0, 1000, TRUE);
		return 0;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(wd, &ps);
		EndPaint(wd, &ps);
		veBang(wd);
		return 0;
	}
	case WM_CLOSE:
	{
		ShowWindow(cs, 1);
		EndDialog(wd, 0);
		return 0;
	}
	case WM_HSCROLL:
	{
		if (LOWORD(w) == SB_THUMBTRACK)
		{
			SetScrollPos(wd, SB_HORZ, HIWORD(w), TRUE);
			c.x = - HIWORD(w);
			InvalidateRect(wd, NULL, TRUE);
		}
		return 0;
	}
	case WM_VSCROLL:
	{
		if (LOWORD(w) == SB_THUMBTRACK)
		{
			SetScrollPos(wd, SB_VERT, HIWORD(w), TRUE);
			c.y = -HIWORD(w);
			InvalidateRect(wd, NULL, TRUE);
		}
		return 0;
	}
	}
	return 0;
}
