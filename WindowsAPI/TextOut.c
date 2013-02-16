#include <Windows.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("TextOut");


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPCTSTR lpszCmdParam,
                     int nCmdShow)
{
    HWND hWnd;
    MSG Message;
    WNDCLASS WndClass;
    g_hInst = hInstance;

    /* 윈도우클래스의 값을 설정한다. */
    WndClass.cbClsExtra     = 0;
    WndClass.cbWndExtra     = 0;
    WndClass.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    WndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
    WndClass.hInstance      = hInstance;
    WndClass.lpfnWndProc    = WndProc;
    WndClass.lpszClassName  = lpszClass;
    WndClass.lpszMenuName   = NULL;
    WndClass.style = CS_HREDRAW | CS_VREDRAW;

    /* 윈도우클래스를 등록한다. */
    RegisterClass(&WndClass);

    /* 윈도우를 생성한다. */
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

    /* 윈도우를 출력한다 .*/
    ShowWindow(hWnd, nCmdShow);

    /* 메세지를 처리한다. */
    while (GetMessage(&Message, NULL, 0, 0))
    {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }

    return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,
                         UINT iMessage,
                         WPARAM wParam,
                         LPARAM lParam)
{
    HDC hdc;

    switch (iMessage)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    /* 마우스 왼쪽 클릭을 할 경우 "Beautiful Korea"라는 문자열을 출력한다. */
    case WM_LBUTTONDOWN:
        hdc = GetDC(hWnd);
        TextOut(hdc, 100, 100, TEXT("Beautiful Korea"), 15);
        ReleaseDC(hWnd, hdc);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
