﻿#include <Windows.h>
#include "resource.h"

//#define MESSAGE_BOX

#define MY_BTN 1011

CONST CHAR INVITATION[] = "Введите логин";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{

#ifdef MESSAGE_BOX
	MessageBox(NULL, "Hello World!", "Info",
		MB_YESNOCANCEL | MB_ICONINFORMATION | MB_SYSTEMMODAL | MB_HELP | MB_DEFBUTTON2 |
		MB_RIGHT | MB_SETFOREGROUND
	);
#endif // MESSAGE_BOX

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//hwnd - Handler to Window (окно)
	//uMsg - сообщение
	//wParam, lParam - параметры сообщения
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_SETTEXT, 0, (LPARAM)INVITATION);
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BTN_COPY:
		{
			CONST INT SIZE = 256;
			CHAR buffer[SIZE]{};
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT1);//получаем Handler текстового поля по номеру его ресурса
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)buffer);
			SendMessage(GetDlgItem(hwnd, IDC_EDIT2), WM_SETTEXT, 0, (LPARAM)buffer);
		}
		break;
		case IDOK:MessageBox(NULL, "Была нажата кнопка Ок", "Info", MB_ICONINFORMATION);break;
		case IDCANCEL:EndDialog(hwnd, 0);break;
		case IDC_EDIT1:
		{
			CONST INT SIZE = 256;
			CHAR buffer[SIZE]{};
			SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_GETTEXT, SIZE, (LPARAM)buffer);
			switch (HIWORD(wParam))
			{
			case EN_SETFOCUS:
				if (strcmp(buffer, INVITATION) == 0)
					SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_SETTEXT, 0, (LPARAM)"");
				break;
			case EN_KILLFOCUS:
				//SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_GETTEXT, SIZE, (LPARAM)buffer);
				if (strcmp(buffer, "") == 0)SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_SETTEXT, 0, (LPARAM)INVITATION);
			}
			break;
		}
		}
		break;
	}
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}