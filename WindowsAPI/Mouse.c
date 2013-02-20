#include <Windows.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR   lpszClass = TEXT("Mouse");


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpszCmdParam,
                     int       nCmdShow)
{
    HWND     hWnd;
    MSG      Message;
    WNDCLASS WndClass;

    g_hInst = hInstance;

    WndClass.cbClsExtra    = 0;
    WndClass.cbWndExtra    = 0;
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
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

    return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,
                         UINT iMessage,
                         WPARAM wParam,
                         LPARAM lParam)
{
    HDC         hdc;
    static int  x, y;
    static BOOL bNowDraw = FALSE;

    switch (iMessage)
    {
    /* 마우스 왼쪽 버튼이 눌리면 그 때 위치를 x, y에 저장하고
       bNowDraw 값을 TRUE로 바꾸어줌으로써 그리기를 시작하도록 한다. */
    case WM_LBUTTONDOWN:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        bNowDraw = TRUE;
        return 0;

    /* 마우스가 움직이는 경우를 처리한다. */
    case WM_MOUSEMOVE:
        /* bNowDraw가 TRUE일 때, 즉 마우스 왼쪽 버튼이 눌려있는 상태이면,
           마우스를 움직일 때마다 그 픽셀까지의 선을 그리면서 진행한다.
           따라서 마우스 왼쪽 클릭을 한 상태에서 커서를 움직이면
           움직임을 따라 선이 나타나 그림을 그릴수 있게 되는것이다. */
        if (bNowDraw == TRUE)
        {
            hdc = GetDC(hWnd);
            MoveToEx(hdc, x, y, NULL);
            x = LOWORD(lParam);
            y = HIWORD(lParam);
            LineTo(hdc, x, y);
            ReleaseDC(hWnd, hdc);
        }
        return 0;

    /* 클릭이 끝난 경우 bNowDraw를 FALSE로 바꾸어 줌으로써
       더이상은 마우스를 움직이더라도 화면에 그려지지 않도록 한다. */
    case WM_LBUTTONUP:
        bNowDraw = FALSE;
        return 0;

    /* Alt+F4를 처리한다. */
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
