#include "HoiQuyTuyenTinh.h"
#include "resource.h"
BOOL CALLBACK Dlg7Proc(HWND wd, UINT id, WPARAM w, LPARAM l)
{
	switch (id)
	{
	case WM_INITDIALOG:
	{
		ComboBox_AddString(GetDlgItem(wd, IDC_COMBO1), L"Trung bình của tồng thể");
		ComboBox_AddString(GetDlgItem(wd, IDC_COMBO1), L"Tỉ lệ của tổng thể");
		ComboBox_AddString(GetDlgItem(wd, IDC_COMBO1), L"Phương sai của tổng thể");
		ComboBox_AddString(GetDlgItem(wd, IDC_COMBO1), L"Hệ số a của đường hồi quy");
		return 0;
	}
	case WM_PAINT :
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(wd, &ps);
		
		EndPaint(wd, &ps);
		return 0;
	}
	case WM_COMMAND:
	{
		if (LOWORD(w) == IDC_BUTTON1)
		{
			EndDialog(wd, 0);
		}
		return 0;
	}
	}
	return 0;
}