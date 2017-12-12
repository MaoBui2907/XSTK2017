#include "HoiQuyTuyenTinh.h"
#include "resource.h"
BOOL CALLBACK Dlg7Proc(HWND wd, UINT id, WPARAM w, LPARAM l)
{
	switch (id)
	{
	case WM_INITDIALOG:
	{
		ComboBox_AddString(GetDlgItem(wd, IDC_COMBO1), L"Trung bình của tồng thể X");
		ComboBox_AddString(GetDlgItem(wd, IDC_COMBO1), L"Trung bình của tồng thể Y");
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
		else if (LOWORD(w) == IDC_BUTTON2) {		
			
			if (ComboBox_GetCurSel(GetDlgItem(wd, IDC_COMBO1)) == 0 && dulieu.size()<=30) {
				char temp[10];
				GetWindowTextA(GetDlgItem(wd, IDC_EDIT1), temp, 10);
				double dTemp = atof(temp);
				snprintf(temp, 10, "%g", (1 - dTemp) / 2);
				double out = PhanPhoi("student", dulieu.size() - 1, temp);
				SetWindowTextA(GetDlgItem(wd, IDC_STATIC2), XuatPhanPhoi(out, ex, dlcx));
			}
			else {
				if (ComboBox_GetCurSel(GetDlgItem(wd, IDC_COMBO1)) == 1 && dulieu.size() <= 30) {
					char temp[10];
					GetWindowTextA(GetDlgItem(wd, IDC_EDIT1), temp, 10);
					double dTemp = atof(temp);
					snprintf(temp, 10, "%g", (1 - dTemp) / 2);
					double out = PhanPhoi("student", dulieu.size() - 1, temp);
					SetWindowTextA(GetDlgItem(wd, IDC_STATIC2), XuatPhanPhoi(out,ey, dlcy));
				}
				else {
					if (ComboBox_GetCurSel(GetDlgItem(wd, IDC_COMBO1)) == 0 && dulieu.size() > 30) {
						char temp[10];
						GetWindowTextA(GetDlgItem(wd, IDC_EDIT1), temp, 10);
						double dTemp = atof(temp);
						snprintf(temp, 10, "%g", (1 - dTemp) / 2);
						double out = PhanPhoi("normal", dulieu.size() - 1, temp);
						SetWindowTextA(GetDlgItem(wd, IDC_STATIC2), XuatPhanPhoi(out, ex, dlcx));
					}
					else {
						if (ComboBox_GetCurSel(GetDlgItem(wd, IDC_COMBO1)) == 1 && dulieu.size() > 30) {
							char temp[10];
							GetWindowTextA(GetDlgItem(wd, IDC_EDIT1), temp, 10);
							double dTemp = atof(temp);
							snprintf(temp, 10, "%g", (1 - dTemp) / 2);
							double out = PhanPhoi("normal", dulieu.size() - 1, temp);
							SetWindowTextA(GetDlgItem(wd, IDC_STATIC2), XuatPhanPhoi(out, ey, dlcy));
						}
					}
				}
			}
		}
		return 0;
	}
	}
	return 0;
}