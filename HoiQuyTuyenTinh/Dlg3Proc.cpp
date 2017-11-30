#include "HoiQuyTuyenTinh.h"
#include "resource.h"
BOOL CALLBACK Dlg3Proc(HWND wd, UINT id, WPARAM w, LPARAM l)
{
	switch (id)
	{
	case WM_INITDIALOG:
	{
		Button_SetCheck(GetDlgItem(wd, IDC_RADIO1), 1);
		return 0;
	}
	case WM_PAINT:
	{
		DrawBmp(wd, MAKEINTRESOURCE(IDB_BITMAP3), 0, 0);
		return 0;
	}
	case WM_CTLCOLORSTATIC:
	{
		SetTextColor((HDC)w, RGB(240, 240, 240));
		SetBkColor((HDC)w, RGB(100, 120, 110));
		return (INT_PTR)CreateSolidBrush(RGB(100, 120, 110));
	}
	case WM_COMMAND:
	{
		if (LOWORD(w) == IDC_RADIO1)
		{
			XuatTSX();
		}
		else
		{
			XuatTSY();
		}
		return 0;
	}
	case WM_TINHTHONGSO:
	{
		int size = dulieu.size();
		//Tính cho X
		//Trị trung bình
		double sum = 0;
		for (int i = 0; i < size; i++)
		{
			sum += dulieu[i].x;
		}
		ex = sum / size;
		//Phương sai
		if (size == 1)
		{
			phuongsaix = 0;
		}
		else
		{
			sum = 0;
			for (int i = 0; i < size; i++)
			{
				sum += pow((dulieu[i].x - ex), 2);
			}
			phuongsaix = sum / (size - 1);
		}
		//Độ lệch chuẩn
		dlcx = pow(phuongsaix, 0.5);
		// Mod 
		modx = TinhModX();

		//
		//Tính cho Y
		//Trị trung bình
		sum = 0;
		for (int i = 0; i < size; i++)
		{
			sum += dulieu[i].y;
		}
		ey = sum / size;
		//Phương sai
		if (size == 1)
		{
			phuongsaiy = 0;
		}
		else
		{
			sum = 0;
			for (int i = 0; i < size; i++)
			{
				sum += pow((dulieu[i].y - ey), 2);
			}
			phuongsaiy = sum / (size - 1);
		}
		//Độ lệch chuẩn
		dlcy = pow(phuongsaiy, 0.5);
		//Mod
		mody = TinhModY();

		//Xuất
		if (Button_GetCheck(GetDlgItem(wd, IDC_RADIO1)) == 1)
		{
			XuatTSX();
		}
		else
		{
			XuatTSY();
		}
		return 0;
	}
	}
	return 0;
}