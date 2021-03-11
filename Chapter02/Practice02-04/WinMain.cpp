#include <Windows.h>
#include <tchar.h>


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
    WndClass.lpszMenuName = NULL;
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

    switch (iMsg)
    {
    case WM_CREATE:
        break;
    case WM_KEYDOWN:
        hdc = GetDC(hwnd);
        TextOut(hdc, 0, 40, _T("WM_KEYDOWN �޽����� ���޵Ǿ����ϴ�."), lstrlen(_T("WM_KEYDOWN �޽����� ���޵Ǿ����ϴ�.")));
        ReleaseDC(hwnd, hdc);
        break;
    case WM_KEYUP:
        hdc = GetDC(hwnd);
        TextOut(hdc, 0, 80, _T("WM_KEYUP �޽����� ���޵Ǿ����ϴ�."), lstrlen(_T("WM_KEYUP �޽����� ���޵Ǿ����ϴ�.")));
        ReleaseDC(hwnd, hdc);
        break;
    case WM_CHAR:
        hdc = GetDC(hwnd);
        TextOut(hdc, 0, 0, _T("� Ű�� ���� �� �� ������ ���̳���?"), lstrlen(_T("� Ű�� ���� �� �� ������ ���̳���?")));
        ReleaseDC(hwnd, hdc);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}