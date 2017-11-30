#include "HoiQuyTuyenTinh.h"
#include "resource.h"
int trang = 0;
BOOL CALLBACK Dlg2Proc(HWND wd, UINT id, WPARAM w, LPARAM l)
{
	static HICON toi = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON2));
	static HICON lui = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON3));
	static HICON sua = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON4));
	static HICON xoa = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON5));
	switch (id)
	{
	case WM_INITDIALOG:
	{
		SendMessage(GetDlgItem(wd, IDC_BUTTON5), BM_SETIMAGE, IMAGE_ICON, (LPARAM)toi);
		SendMessage(GetDlgItem(wd, IDC_BUTTON1), BM_SETIMAGE, IMAGE_ICON, (LPARAM)lui);
		SendMessage(GetDlgItem(wd, IDC_BUTTON11), BM_SETIMAGE, IMAGE_ICON, (LPARAM)sua);
		SendMessage(GetDlgItem(wd, IDC_BUTTON15), BM_SETIMAGE, IMAGE_ICON, (LPARAM)xoa);
		return 0;
	}
	case WM_PAINT:
	{
		DrawBmp(wd, MAKEINTRESOURCE(IDB_BITMAP2), 0, 0);
		return 0;
	}
	case WM_THEMDIEM:
	{
		ListBox_ResetContent(GetDlgItem(wd, IDC_LIST1));
		for (int i = 0; i < dulieu.size(); i++)
		{
			wchar_t text[50];
			_snwprintf_s(text, sizeof(text), L"(%.2f; %.2f)", dulieu[i].x, dulieu[i].y);
			ListBox_InsertString(GetDlgItem(wd, IDC_LIST1), i, text);
		}
		return 0;
	}
	case WM_COMMAND:
	{
		if (LOWORD(w) == IDC_BUTTON15)//X¨®a
		{
			int index = ListBox_GetCurSel(GetDlgItem(wd, IDC_LIST1));
			dulieu.erase(dulieu.begin() + index);
			ListBox_DeleteString(GetDlgItem(wd, IDC_LIST1), index);
			VeOxy(Dlg[3]);
			VeCham(Dlg[3]);
		}
		if (LOWORD(w) == IDC_BUTTON11)
		{
			int index = ListBox_GetCurSel(GetDlgItem(wd, IDC_LIST1));
			if (index >= 0)
			{
				change = dulieu[index];
				DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG6), wd, Dlg6Proc);
				dulieu[index].x = change.x;
				dulieu[index].y = change.y;
				SendMessage(wd, WM_THEMDIEM, NULL, NULL);
			}
		}
		return 0;
	}
	}
	return 0;
}