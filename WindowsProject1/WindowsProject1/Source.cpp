
#include <windows.h> // заголовочный файл, содержащий функции API
#include "stdafx.h"
#include <math.h> 
#include <tchar.h> 
#include <stdio.h> 
#include <conio.h> 
#include <stdlib.h>
#include <iostream>
#include <locale.h>
#include <fstream>
#include <string.h>
#include <string>
// Основная функция - аналог int main() в консольном приложении:
int WINAPI WinMain(HINSTANCE hInstance, // дескриптор экземпляра приложения
	HINSTANCE hPrevInstance, // в Win32 не используется
	LPSTR lpCmdLine, // нужен для запуска окна в режиме командной строки
	int nCmdShow) // режим отображения окна
{
	struct BOOT
	{
		//в комментариях к полям указано смещение в 10 и 16 формате
		BYTE djmp[3];   //0
		BYTE dSystemID[8];   //3
		WORD dBytesPerSector;  //11  b
		BYTE dSectorPerCluster;  //13  d
		BYTE dUnusedA[7];  //14  e
		BYTE dMediaID;  //21  15
		WORD dUnusedB;  //22 16
		WORD dSectorPerTrack; //24 18
		WORD dHeadsCount; // 26 1a
		BYTE dUnusedC[8];  // 28 1c
		BYTE dUsualy[4];   //36 24
		INT64 dNumberOfSectors;  //40 28
		INT64 dLCNofMFT;  //48 30
		INT64 dLCNofMFTMirr;  //56 38
		DWORD ClusterPerMFT;  //64 40
		DWORD ClustersPerIndexes;  //68 44
		BYTE dSerialNumber[8];  //72 48
		BYTE dDataCode[432];
	} METADATABOOT;

	char per[20] = "";
	char buf[512];
	char dump[2048];
	int i = 0, k = 0;

	hFlash= CreateFile(TEXT("E:\\BOOT.bin"),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hFlash == INVALID_HANDLE_VALUE)
	{
		MessageBox(hDlg, L"Не удаётся открыть файл", L"Ошибка", MB_OK);
		return FALSE;
	}

	ReadFile(hFlash, buf, 512, &rd, NULL);

	//------------------------------------------вывод дампа-----------------------------------
	while (i < 512)
	{
		if (i % 16 == 0 && i != 0)
			k += sprintf(dump + k, "\r\n");
		k += sprintf(dump + k, "%02X ", (unsigned char)buf[i]);
		i++;
	}

	SetDlgItemTextA(hDlg, IDC_EDIT18, dump);

	SetFilePointer(hFlash, 3, NULL, FILE_BEGIN);

	//----------------------------------расшифровка структуры---------------------------------
	ReadFile(hFlash, METADATABOOT.dSystemID, sizeof(METADATABOOT.dSystemID), &rd, NULL);
	sprintf_s(per, "%s", METADATABOOT.dSystemID);
	SetDlgItemTextA(hDlg, IDC_EDIT2, per);



	ReadFile(hFlash, &METADATABOOT.dBytesPerSector, sizeof(METADATABOOT.dBytesPerSector), &rd, NULL);
	sprintf_s(per, "%u", METADATABOOT.dBytesPerSector);
	SetDlgItemTextA(hDlg, IDC_EDIT3, per);

	ReadFile(hFlash, &METADATABOOT.dSectorPerCluster, sizeof(METADATABOOT.dSectorPerCluster), &rd, NULL);
	sprintf_s(per, "%u", METADATABOOT.dSectorPerCluster);
	SetDlgItemTextA(hDlg, IDC_EDIT4, per);

	ReadFile(hFlash, &METADATABOOT.dUnusedA, sizeof(METADATABOOT.dUnusedA), &rd, NULL);
	sprintf_s(per, "%u", METADATABOOT.dUnusedA);
	SetDlgItemTextA(hDlg, IDC_EDIT5, per);

	ReadFile(hFlash, &METADATABOOT.dMediaID, sizeof(METADATABOOT.dMediaID), &rd, NULL);
	sprintf_s(per, "%02X", METADATABOOT.dMediaID);
	SetDlgItemTextA(hDlg, IDC_EDIT6, per);

	ReadFile(hFlash, &METADATABOOT.dUnusedB, sizeof(METADATABOOT.dUnusedB), &rd, NULL);
	sprintf_s(per, "%u", METADATABOOT.dUnusedB);
	SetDlgItemTextA(hDlg, IDC_EDIT7, per);

	ReadFile(hFlash, &METADATABOOT.dSectorPerTrack, sizeof(METADATABOOT.dSectorPerTrack), &rd, NULL);
	sprintf_s(per, "%u", METADATABOOT.dSectorPerTrack);
	SetDlgItemTextA(hDlg, IDC_EDIT8, per);

	ReadFile(hFlash, &METADATABOOT.dHeadsCount, sizeof(METADATABOOT.dHeadsCount), &rd, NULL);
	sprintf_s(per, "%u", METADATABOOT.dHeadsCount);
	SetDlgItemTextA(hDlg, IDC_EDIT9, per);

	ReadFile(hFlash, &METADATABOOT.dUnusedC, sizeof(METADATABOOT.dUnusedC), &rd, NULL);
	sprintf_s(per, "%u", METADATABOOT.dUnusedC);
	SetDlgItemTextA(hDlg, IDC_EDIT10, per);

	ReadFile(hFlash, &METADATABOOT.dUsualy, sizeof(METADATABOOT.dUsualy), &rd, NULL);
	sprintf_s(per, "%u", METADATABOOT.dUsualy);
	SetDlgItemTextA(hDlg, IDC_EDIT11, per);

	ReadFile(hFlash, &METADATABOOT.dNumberOfSectors, sizeof(METADATABOOT.dNumberOfSectors), &rd, NULL);
	sprintf_s(per, "%u", METADATABOOT.dNumberOfSectors);
	SetDlgItemTextA(hDlg, IDC_EDIT12, per);

	ReadFile(hFlash, &METADATABOOT.dLCNofMFT, sizeof(METADATABOOT.dLCNofMFT), &rd, NULL);
	sprintf_s(per, "%u", METADATABOOT.dLCNofMFT);
	SetDlgItemTextA(hDlg, IDC_EDIT13, per);

	ReadFile(hFlash, &METADATABOOT.dLCNofMFTMirr, sizeof(METADATABOOT.dLCNofMFTMirr), &rd, NULL);
	sprintf_s(per, "%u", METADATABOOT.dLCNofMFTMirr);
	SetDlgItemTextA(hDlg, IDC_EDIT14, per);

	ReadFile(hFlash, &METADATABOOT.ClusterPerMFT, sizeof(METADATABOOT.ClusterPerMFT), &rd, NULL);
	sprintf_s(per, "%u", METADATABOOT.ClusterPerMFT);
	SetDlgItemTextA(hDlg, IDC_EDIT15, per);

	ReadFile(hFlash, &METADATABOOT.ClustersPerIndexes, sizeof(METADATABOOT.ClustersPerIndexes), &rd, NULL);
	sprintf_s(per, "%u", METADATABOOT.ClustersPerIndexes);
	SetDlgItemTextA(hDlg, IDC_EDIT16, per);

	ReadFile(hFlash, &METADATABOOT.dSerialNumber, sizeof(METADATABOOT.dSerialNumber), &rd, NULL);
	sprintf_s(per, "%X", METADATABOOT.dSerialNumber);
	SetDlgItemTextA(hDlg, IDC_EDIT17, per);


	CloseHandle(hFlash);
	// Функция вывода окна с кнопкой "ОК" на экран (о параметрах позже)
	MessageBox(NULL, L"Привет, мир!!!", L"Оконная процедура", MB_OK);
	return NULL; // возвращаем значение функции
}