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
	snprintf(buff, sizeof(buff), "%.2f", modx);
	SetWindowTextA(GetDlgItem(Dlg[2], IDC_STATICMOD), buff);
	snprintf(buff, sizeof(buff), "%d", dulieu.size());
	SetWindowTextA(GetDlgItem(Dlg[2], IDC_STATICN), buff);
	snprintf(buff, sizeof(buff), "%.2f", cov);
	SetWindowTextA(GetDlgItem(Dlg[2], IDC_STATICCOV), buff);
	snprintf(buff, sizeof(buff), "%.2f", corr);
	SetWindowTextA(GetDlgItem(Dlg[2], IDC_STATICCORR), buff);
	snprintf(buff, sizeof(buff), "%.0f%%", hsbt*100);
	SetWindowTextA(GetDlgItem(Dlg[2], IDC_STATICBT), buff);
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
	snprintf(buff, sizeof(buff), "%d", dulieu.size());
	SetWindowTextA(GetDlgItem(Dlg[2], IDC_STATICN), buff);
	snprintf(buff, sizeof(buff), "%.2f", mody);
	SetWindowTextA(GetDlgItem(Dlg[2], IDC_STATICMOD), buff);
	snprintf(buff, sizeof(buff), "%.2f", cov);
	SetWindowTextA(GetDlgItem(Dlg[2], IDC_STATICCOV), buff);
	snprintf(buff, sizeof(buff), "%.2f", corr);
	SetWindowTextA(GetDlgItem(Dlg[2], IDC_STATICCORR), buff);
	snprintf(buff, sizeof(buff), "%.0f%%", hsbt*100);
	SetWindowTextA(GetDlgItem(Dlg[2], IDC_STATICBT), buff);
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
	double *dbTempX;
	dbTempX = new double[dulieu.size()];
	for (int i = 0; i < dulieu.size(); i++) {
		dbTempX[i] = dulieu[i].x;
	}
	for (int i = 0; i < dulieu.size() - 1; i++) {
		for (int j = i + 1; j < dulieu.size(); j++) {
			if (dbTempX[i] > dbTempX[j]) {
				double temp = dbTempX[i];
				dbTempX[i] = dbTempX[j];
				dbTempX[j] = temp;
			}
		}
	}
	if (dulieu.size() % 2 == 0) {
		return 0.5*(dbTempX[dulieu.size() / 2 - 1] + dbTempX[dulieu.size() / 2]);
	}
	else {
		return dbTempX[(dulieu.size() + 1) / 2 - 1];
	}
}
double TinhModY() {
	double *dbTempX;
	dbTempX = new double[dulieu.size()];
	for (int i = 0; i < dulieu.size(); i++) {
		dbTempX[i] = dulieu[i].y;
	}
	for (int i = 0; i < dulieu.size() - 1; i++) {
		for (int j = i + 1; j < dulieu.size(); j++) {
			if (dbTempX[i] > dbTempX[j]) {
				double temp = dbTempX[i];
				dbTempX[i] = dbTempX[j];
				dbTempX[j] = temp;
			}
		}
	}
	if (dulieu.size() % 2 == 0) {
		return 0.5*(dbTempX[dulieu.size() / 2 - 1] + dbTempX[dulieu.size() / 2]);
	}
	else {
		return dbTempX[(dulieu.size() + 1) / 2 - 1];
	}
}
double TinhHiepPhuongSai() {
	double temp = 0;
	for (int i = 0; i < dulieu.size(); i++) {
		temp += (dulieu[i].x - ex)*(dulieu[i].y - ey);
	}
	return temp / (dulieu.size() - 1);
}

double TinhHeSoTuongQuan() {
	return TinhHiepPhuongSai() / (dlcx*dlcy);
}
double TinhHeSoBienThien() {
	timAB();
	double temp1 = 0, temp2 = 0;
	for (int i = 0; i < dulieu.size(); i++) {
		temp1 += pow((A.x * dulieu[i].x + A.y - ey), 2);
		temp2 += pow(dulieu[i].y - ey, 2);
	}
	return temp1 / temp2;
}
double DaoHambeta(double x, double y,double t) {
	return (x - 1)*pow(t, x - 2)*pow(1 - t, y - 1) - pow(t, x - 1)*(y - 1)*pow(1 - t, y - 2);
}
double Beta(double x, double y,double a) {
	return pow(a, x - 1)*pow(1 - a, y - 1);
}
double TichPhanBeta(double a, double b) {
	/*if (abs(DaoHambeta(1 / 2, (dulieu.size() - 1) / 2, a) - DaoHambeta(1 / 2, (dulieu.size() - 1) / 2, b)) < 10) {
		return (abs(b - a)*(Beta(1 / 2, (dulieu.size() - 1) / 2, a) + Beta(1 / 2, (dulieu.size() - 1) / 2, b)))/2;
	}*/
	if (abs(b-a)<0.5) {
		return (abs(b - a)*(Beta(1 / 2, (dulieu.size() - 1) / 2, a) + Beta(1 / 2, (dulieu.size() - 1) / 2, b))) / 2;
	}
	double s1 = TichPhanBeta(a, (a + b) / 2);
	double s2 = TichPhanBeta((a + b) / 2, b);
	return s1 + s2;
}
DATA ChuyenDoi(double a) {
	DATA dtTemp;
		if (a == 0.25) {
			dtTemp.x = 0;
			dtTemp.y = 0;
		}
		else {
			if (a == 0.2) {
				dtTemp.x = 1;
				dtTemp.y = 1;
			}
			else {
				if (a == 0.15) {
					dtTemp.x = 2;
					dtTemp.y = 2;
				}
				else {
					if (a == 0.1) {
						dtTemp.x = 3;
						dtTemp.y = 3;
					}
					else {
						if (a == 0.05) {
							dtTemp.x = 4;
							dtTemp.y = 4;
						}
						else {
							if (a == 0.025) {
								dtTemp.x = 5;
								dtTemp.y = 5;
							}
							else {
								if (a == 0.02) {
									dtTemp.x = 6;
									dtTemp.y = 6;
								}
								else {
									if (a == 0.01) {
										dtTemp.x = 7;
										dtTemp.y = 7;
									}
									else {
										if (a == 0.005) {
											dtTemp.x = 8;
											dtTemp.y = 8;
										}
										else {
											if (a == 0.0025) {
												dtTemp.x = 9;
												dtTemp.y = 9;
											}
											else {
												if (a == 0.001) {
													dtTemp.x = 10;
													dtTemp.y = 10;
												}
												else {
													if (a == 0.0005) {
														dtTemp.x = 11;
														dtTemp.y = 11;
													}
													else {
														if (a > 0.25&&a < 0.0005) {
															dtTemp.x = -1;
															dtTemp.y = -1;
														}
														else {
															if (a < 0.25 && a> 0.2) {
																dtTemp.x = 0;
																dtTemp.y = 1;
															}
															else
															{
																if (a < 0.2 && a> 0.15) {
																	dtTemp.x = 1;
																	dtTemp.y = 2;
																}
																else
																{
																	if (a < 0.15 && a> 0.1) {
																		dtTemp.x = 2;
																		dtTemp.y = 3;
																	}
																	else
																	{
																		if (a < 0.1 && a> 0.05) {
																			dtTemp.x = 3;
																			dtTemp.y = 4;
																		}
																		else
																		{
																			if (a < 0.05 && a> 0.025) {
																				dtTemp.x = 4;
																				dtTemp.y = 5;
																			}
																			else
																			{
																				if (a < 0.025 && a> 0.02) {
																					dtTemp.x = 5;
																					dtTemp.y = 6;
																				}
																				else
																				{
																					if (a < 0.02 && a> 0.01) {
																						dtTemp.x = 6;
																						dtTemp.y = 7;
																					}
																					else
																					{
																						if (a < 0.01 && a> 0.005) {
																							dtTemp.x = 7;
																							dtTemp.y = 8;
																						}
																						else
																						{
																							if (a < 0.005 && a> 0.0025) {
																								dtTemp.x = 8;
																								dtTemp.y = 9;
																							}
																							else
																							{
																								if (a < 0.0025 && a> 0.001) {
																									dtTemp.x = 9;
																									dtTemp.y = 10;
																								}
																								else
																								{
																									if (a < 0.001 && a> 0.0005) {
																										dtTemp.x = 10;
																										dtTemp.y = 11;
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
}

void DocStudent() {
	FILE* f;
	fopen_s(&f, "student.txt", "rb");
	if (f == NULL)
	{
		MessageBox(NULL, L"Mất student.txt", L"Lỗi", MB_ICONERROR);
	}
	else
	{
		char buff1[20];
		int i = 0;
		int j = 0;
		while (true)
		{
			buff1[i] = fgetc(f);
			if (buff1[i] == -1) break;
			if (buff1[i] == 32)
			{
				buff1[i] = 0;
				student[i][j] = strtod(buff1, NULL);
				i = -1;
				ZeroMemory(buff1, strlen(buff1));
			}
			if (buff1[i] == 13)
			{
				j++;
				i = -1;
			}
			i++;
		}
		fclose(f);
	}
}
void GhiFile() {
	
	char buff[6];
	snprintf(buff, 6, "%5f ", student[0][0]);
	MessageBoxA(NULL, buff, "", MB_OK);
}
