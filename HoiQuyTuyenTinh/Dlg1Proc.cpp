#include "HoiQuyTuyenTinh.h"
#include "resource.h"
//KT Button: 76 x 48
BOOL CALLBACK Dlg1Proc(HWND wd, UINT id, WPARAM w, LPARAM l)
{
	static HICON nhapbutton = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON6), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
	static HICON mobutton = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON7), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
	static HICON luubutton = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON8), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
	static HICON infobutton = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON9), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
	static HICON dothibutton = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON10), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
	static HICON xulybutton = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON11), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
	switch (id)
	{
	case WM_INITDIALOG:
	{
		Dlg[1] = CreateDialog(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG2), wd, Dlg2Proc);
		Dlg[2] = CreateDialog(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG3), wd, Dlg3Proc);
		Dlg[3] = CreateDialog(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG4), wd, Dlg4Proc);
		SendMessage(GetDlgItem(wd, IDC_BUTTON2), BM_SETIMAGE, IMAGE_ICON, (LPARAM)nhapbutton);
		SendMessage(GetDlgItem(wd, IDC_BUTTON3), BM_SETIMAGE, IMAGE_ICON, (LPARAM)mobutton);
		SendMessage(GetDlgItem(wd, IDC_BUTTON4), BM_SETIMAGE, IMAGE_ICON, (LPARAM)luubutton);
		SendMessage(GetDlgItem(wd, IDC_BUTTON6), BM_SETIMAGE, IMAGE_ICON, (LPARAM)infobutton);
		SendMessage(GetDlgItem(wd, IDC_BUTTON7), BM_SETIMAGE, IMAGE_ICON, (LPARAM)dothibutton);
		SendMessage(GetDlgItem(wd, IDC_BUTTON1), BM_SETIMAGE, IMAGE_ICON, (LPARAM)xulybutton);
		return 0;
	}
	case WM_PAINT:
	{
		DrawBmp(wd, MAKEINTRESOURCE(IDB_BITMAP1), 0, 0);
		return 0;
	}
	case WM_CTLCOLOREDIT:
	{
		HDC hdcStatic = (HDC)w;
		SetTextColor(hdcStatic, RGB(240, 240, 240));
		SetBkColor(hdcStatic, RGB(70, 83, 127));
		return (INT_PTR)CreateSolidBrush(RGB(70, 83, 127));
	}
	case WM_CTLCOLORSTATIC:
	{
		if ((HWND)l == GetDlgItem(wd, IDC_STATICHAM))
		{
			SetTextColor((HDC)w, RGB(0, 0, 0));
			SetBkColor((HDC)w, RGB(0, 0, 0));
			SetBkMode((HDC)w, TRANSPARENT);
			return (INT_PTR)GetStockObject(WHITE_BRUSH);
		}
		SetTextColor((HDC)w, RGB(240, 240, 240));
		SetBkColor((HDC)w, RGB(0, 0, 0));
		SetBkMode((HDC)w, TRANSPARENT);
		return (INT_PTR)GetStockObject(NULL_BRUSH);
	}
	case WM_COMMAND:
	{
		if (LOWORD(w) == IDC_BUTTON2)
		{
			char xtext[20];
			GetWindowTextA(GetDlgItem(wd, IDC_EDIT1), xtext, 19);
			char ytext[20];
			GetWindowTextA(GetDlgItem(wd, IDC_EDIT2), ytext, 19);
			DATA buff;
			buff.x = strtod(xtext, NULL);
			buff.y = strtod(ytext, NULL);
			dulieu.push_back(buff);
			SendMessage(Dlg[3], WM_VECHAM, NULL, NULL);
			SendMessage(Dlg[1], WM_THEMDIEM, NULL, NULL);
			SetWindowTextA(GetDlgItem(wd, IDC_EDIT1), "");
			SetWindowTextA(GetDlgItem(wd, IDC_EDIT2), "");
		}
		if (LOWORD(w) == IDC_BUTTON1)
		{
			if (dulieu.size() > 1)
			{
				k = true;
				TinhTanSuat();
				SendMessage(Dlg[2], WM_TINHTHONGSO, NULL, NULL);
				if (Kiemtra())
				{
					SendMessage(Dlg[3], WM_VEDUONGTHANG, NULL, NULL);
				}
				else
				{
					k = false;
					MessageBox(wd,L"Dữ liệu không chính xác", L"Lỗi", MB_ICONERROR);
				}
			}
			else
			{
				MessageBox(wd, L"Dữ liệu không chính xác", L"Lỗi", MB_ICONERROR);
			}
		}
		if (LOWORD(w) == IDC_BUTTON6)
		{
			DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG5), wd, Dlg5Proc);
		}
		if (LOWORD(w) == IDC_BUTTON8)
		{
			tam.x = 244;
			tam.y = 224 + 44;
			VeOxy(Dlg[3]);
			VeCham(Dlg[3]);
			if (k)
			{
				drawLine(Dlg[3], A.x, A.y);
			}
		}
		if (LOWORD(w) == IDC_BUTTON3)
		{
			OPENFILENAME ofn;
			static wchar_t szFile[100];
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = NULL;
			ofn.lpstrFile = szFile;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.hInstance = GetModuleHandle(0);
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			GetOpenFileName(&ofn);
			FILE* f;
			_wfopen_s(&f, szFile, L"rb");
			if (f == NULL) return 0;
			char buff1[20];
			int i = 0;
			DATA buff;
			while (true)
			{
				buff1[i] = fgetc(f);
				if (buff1[i] == -1) break;
				if (buff1[i] == 32)
				{
					buff1[i] = 0;
					buff.x = strtod(buff1, NULL);
					i = -1;
					ZeroMemory(buff1, strlen(buff1));
				}
				if (buff1[i] == 13)
				{
					buff1[i] = 0;
					buff.y = strtod(buff1, NULL);
					i = -1;
					ZeroMemory(buff1, strlen(buff1));
					dulieu.push_back(buff);
				}
				i++;
			}
			fclose(f);
			SendMessage(Dlg[1], WM_THEMDIEM, NULL, NULL);
			VeCham(Dlg[3]);

		}
		if (LOWORD(w) == IDC_BUTTON4)
		{
			fstream f;
			f.open("output.txt", ios::out);
			for (int i = 0; i < dulieu.size(); i++) {
				f << dulieu[i].x << " " << dulieu[i].y << "\n";
			}
			f.close();
			MessageBox(wd, L"Đã xuất ra file output.txt", L"Thành công", MB_ICONINFORMATION);
		}
		if (LOWORD(w) == IDC_BUTTON9) {
			dulieu.clear();
			SendMessage(Dlg[1], WM_THEMDIEM, NULL, NULL);
			VeOxy(Dlg[3]);
			A.x = A.y = 0;
			SetWindowTextA(GetDlgItem(wd, IDC_STATICHAM), "");
		}
		if (LOWORD(w) == IDC_BUTTON7) {
			DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG7), wd, Dlg7Proc);
		}
		return 0;
		
	}
	}
	return 0;
}