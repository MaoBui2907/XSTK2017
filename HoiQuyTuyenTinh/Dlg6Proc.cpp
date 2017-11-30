#include "HoiQuyTuyenTinh.h"
#include "resource.h"
BOOL CALLBACK Dlg6Proc(HWND wd, UINT id, WPARAM w, LPARAM l)
{
	switch (id)
	{
	case WM_COMMAND:
	{
		if (LOWORD(w) == IDC_BUTTON2)
		{
			EndDialog(wd, 0);
		}
		else if (LOWORD(w) == IDC_BUTTON1)
		{
			char xtext[20];
			GetWindowTextA(GetDlgItem(wd, IDC_EDIT1), xtext, 19);
			char ytext[20];
			GetWindowTextA(GetDlgItem(wd, IDC_EDIT3), ytext, 19);
			change.x = strtod(xtext, NULL);
			change.y = strtod(ytext, NULL);
			EndDialog(wd, 0);
		}
		return 0;
	}
	}
	return 0;
}