#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>
#include "resource.h"


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
    WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU4_7);
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
    HDC hdc;
    PAINTSTRUCT ps;
    CHOOSECOLOR COLOR;
    static COLORREF tmp[16], color;
    HBRUSH hBrush, OldBrush;
    int i;

    switch (iMsg)
    {
    case WM_CREATE:
        break;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        hBrush = CreateSolidBrush(color);
        OldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        Ellipse(hdc, 10, 10, 200, 200);
        SelectObject(hdc, OldBrush);
        DeleteObject(hBrush);
        EndPaint(hwnd, &ps);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_COLORDLG:
            for (i = 0; i < 16; i++) tmp[i] = RGB(rand() % 256, rand() % 256, rand() % 256);
            memset(&COLOR, 0, sizeof(CHOOSECOLOR));
            COLOR.lStructSize = sizeof(CHOOSECOLOR);
            COLOR.hwndOwner = hwnd;
            COLOR.lpCustColors = tmp;
            COLOR.Flags = CC_RGBINIT;
            if (ChooseColor(&COLOR) != 0)
            {
                color = COLOR.rgbResult;
                InvalidateRgn(hwnd, NULL, TRUE);
            }
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}