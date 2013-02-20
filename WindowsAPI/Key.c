#include <Windows.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR   lpszClass = TEXT("Key");


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpszCmdParam,
                     int       nCmdShow)
{
    HWND hWnd;
    MSG Message;
    WNDCLASS WndClass;

    g_hInst = hInstance;

    WndClass.cbClsExtra    = 0;
    WndClass.cbWndExtra    = 0;
    WndClass.hbrBackground = GetStockObject(WHITE_BRUSH);
    WndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    WndClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    WndClass.hInstance     = hInstance;
    WndClass.lpfnWndProc   = WndProc;
    WndClass.lpszClassName = lpszClass;
    WndClass.lpszMenuName  = NULL;
    WndClass.style         = CS_HREDRAW|CS_VREDRAW;

    RegisterClass(&WndClass);

    hWnd = CreateWindow(lpszClass,
                        lpszClass,
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        NULL,
                        (HMENU)NULL,
                        hInstance,
                        NULL);

    ShowWindow(hWnd, nCmdShow);

    while (GetMessage(&Message, NULL, 0, 0))
    {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }

    return (int)Message.wParam;
}


LRESULT CALLBACK WndProc(HWND   hWnd,
                         UINT   iMessage,
                         WPARAM wParam,
                         LPARAM lParam)
{
    HDC          hdc;
    PAINTSTRUCT  ps;
    static TCHAR str[256];
    int          len;

    switch (iMessage)
    {
    case WM_CHAR:
        /* 키보드 입력을 받을 때마다 문자열의 끝에
           문자를 하나씩 더하는 형태로 문자열을 이어나간다. */
        len = lstrlen(str);
        str[len] = (TCHAR)wParam;
        str[len + 1] = '\0';

        /* 윈도우를 강제로 무효화 시켜 화면을 다시 출력하게 만든다. */
        InvalidateRect(hWnd, NULL, FALSE);

        return 0;

    case WM_PAINT:
        /* DC를 이용해 문자열을 화면에 출력한다. */
        hdc = BeginPaint(hWnd, &ps);
        TextOut(hdc, 100, 100, str, lstrlen(str));
        EndPaint(hWnd, &ps);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
