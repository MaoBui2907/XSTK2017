#include "HoiQuyTuyenTinh.h"
#include "resource.h"
void XuatTSX()
{
	//Xuất kỳ vọng
	char buff[20];
	snprintf(buff, sizeof(buff), "%.2f", ex);
	SetWindowTextA(GetDlgItem(Dlg[2], IDC_STATICEE), buff);
	snprintf(buff, sizeof(buff), "%.2f", phuongsaix);
	SetWindowTextA(GetDlgItem(Dlg[2], IDC_STATICVAR), buff); 
	snprintf(buff, sizeof(buff), "%.2f", dlcx);
	SetWindowTextA(GetDlgItem(Dlg[2], IDC_STATICDLC), buff);
	
}
void XuatTSY()
{
	//Xuất kỳ vọng
	char buff[20];
	snprintf(buff, sizeof(buff), "%.2f", ey);
	SetWindowTextA(GetDlgItem(Dlg[2], IDC_STATICEE), buff);
	snprintf(buff, sizeof(buff), "%.2f", phuongsaiy);
	SetWindowTextA(GetDlgItem(Dlg[2], IDC_STATICVAR), buff);
	snprintf(buff, sizeof(buff), "%.2f", dlcy);
	SetWindowTextA(GetDlgItem(Dlg[2], IDC_STATICDLC), buff);
}
void timAB()
{
	float eXY = 0;
	float sumX2 = 0;
	for (int i = 0; i < dulieu.size(); i++)
	{
		eXY += dulieu[i].x*dulieu[i].y;
		sumX2 += dulieu[i].x*dulieu[i].x;
	}
	sumX2 /= dulieu.size();
	eXY /= dulieu.size();
	A.x = (eXY - ex*ey) / (sumX2 - ex*ex);
	A.y = ey - A.x*ex;
	char ham[40];
	snprintf(ham, sizeof(ham), "y = %.2fx + %.2f", A.x, A.y);
	SetWindowTextA(GetDlgItem(Dlg[0], IDC_STATICHAM), "");
	SetWindowTextA(GetDlgItem(Dlg[0], IDC_STATICHAM), ham);
}
void TinhTanSuat()
{
	int size = dulieu.size();
	for (int i = 0; i < size; i++)
	{
		if (tansuat.empty())
		{
			TANSUAT buff;
			buff.giatri = dulieu[i];
			buff.tansuat = 1;
			tansuat.push_back(buff);
		}
		else
		{
			bool u = false;
			for (int j = 0; j < tansuat.size(); j++)
			{
				if (dulieu[i].x == tansuat[j].giatri.x && dulieu[i].y == tansuat[j].giatri.y)
				{
					tansuat[j].tansuat++;
					u = true;
				}
			}
			if (!u)
			{
				TANSUAT buff;
				buff.giatri = dulieu[i];
				buff.tansuat = 1;
				tansuat.push_back(buff);
			}
		}
	}
}
bool Kiemtra()
{
	DATA d = dulieu[0];
	for (int i = 1; i < dulieu.size(); i++)
	{
		if (dulieu[i].x != d.x)
		{
			return true;
		}
	}
	return false;
}
double TinhModX() {
	vector<DATA> tansuatx;
	int size = dulieu.size();
	for (int i = 0; i < size; i++)
	{
		if (tansuatx.empty())
		{
			DATA buff;
			buff.x = dulieu[i].x;
			buff.y = 1;
			tansuatx.push_back(buff);
		}
		else
		{
			bool u = false;
			for (int j = 0; j < tansuatx.size(); j++)
			{
				if (dulieu[i].x == tansuatx[j].x)
				{
					tansuatx[j].y++;
					u = true;
				}
			}
			if (!u)
			{
				DATA buff;
				buff.x = dulieu[i].x;
				buff.y = 1;
				tansuatx.push_back(buff);
			}
		}
	}
	DATA flag = tansuatx[0];
	for (int i = 1; i < tansuatx.size(); i++) {
		if (tansuatx[i].y > flag.y) {
			flag = tansuatx[i];
		}
	}
	return flag.x;
}
double TinhModY() {
	vector<DATA> tansuaty;
	int size = dulieu.size();
	for (int i = 0; i < size; i++)
	{
		if (tansuaty.empty())
		{
			DATA buff;
			buff.x = dulieu[i].y;
			buff.y = 1;
			tansuaty.push_back(buff);
		}
		else
		{
			bool u = false;
			for (int j = 0; j < tansuaty.size(); j++)
			{
				if (dulieu[i].y == tansuaty[j].x)
				{
					tansuaty[j].y++;
					u = true;
				}
			}
			if (!u)
			{
				DATA buff;
				buff.x = dulieu[i].y;
				buff.y = 1;
				tansuaty.push_back(buff);
			}
		}
	}
	DATA flag = tansuaty[0];
	for (int i = 1; i < tansuaty.size(); i++) {
		if (tansuaty[i].y > flag.y) {
			flag = tansuaty[i];
		}
	}
	return flag.x;
}