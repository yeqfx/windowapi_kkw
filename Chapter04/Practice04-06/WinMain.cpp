#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <stdio.h>
#include "../resource.h"


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM IParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hwnd;
    MSG msg;
    WNDCLASS WndClass;
    WndClass.style = CS_HREDRAW | CS_VREDRAW;
    WndClass.lpfnWndProc = WndProc;
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hInstance = hInstance;
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU4_4);
    WndClass.lpszClassName = _T("Window Class Name");
    //WndClass.hIconSm = LoadIcon(WndClass.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    RegisterClass(&WndClass);

    hwnd = CreateWindow(L"Window Class Name",
        _T("Window Title Name"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    OPENFILENAME SFN;
    TCHAR str[100], lpstrFile[100] = _T("");
    TCHAR filter[] = _T("Every File(*.*) \0*.*\0Text File\0*.txt;*.doc\0");
    int answer;

    switch (iMsg)
    {
    case WM_CREATE:
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_FILESAVE:
            memset(&SFN, 0, sizeof(OPENFILENAME));
            SFN.lStructSize = sizeof(OPENFILENAME);
            SFN.hwndOwner = hwnd;
            SFN.lpstrFilter = filter;
            SFN.lpstrFile = lpstrFile;
            SFN.nMaxFile = 256;
            SFN.lpstrInitialDir = _T(".");
            if (GetSaveFileName(&SFN) != 0)
            {
                _stprintf_s(str, _T("%s ���Ϸ� �����ϰڽ��ϱ�?"), SFN.lpstrFile);
                MessageBox(hwnd, str, _T("�����ϱ� ����"), MB_OK);
            }
            break;
        case ID_EXIT:
            answer = MessageBox(hwnd, _T("������ �����ϰ� �����ڽ��ϱ�?"), _T("������ ����"), MB_YESNOCANCEL);
            if (answer == IDYES || answer == IDNO) PostQuitMessage(0);
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}