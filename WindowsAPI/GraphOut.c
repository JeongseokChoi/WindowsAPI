#include <Windows.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR   lpszClass = TEXT("Graph Out");


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

    return (int)Message.wParam;
}


LRESULT CALLBACK WndProc(HWND   hWnd,
                         UINT   iMessage,
                         WPARAM wParam,
                         LPARAM lParam)
{
    HDC         hdc;
    PAINTSTRUCT ps;

    switch (iMessage)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        /* (10, 10) 위치에 빨간색 점을 찍는다. */
        SetPixel(hdc, 10, 10, RGB(255, 0, 0));

        /* 점을 (50, 50)으로 옮기고 (300, 90)까지 선을 긋는다. */
        MoveToEx(hdc, 50, 50, NULL);
        LineTo(hdc, 300, 90);

        /* (50, 100)을 왼쪽 위 꼭지점으로 갖고 (200, 180)을
           오른쪽 아래 꼭지점으로 갖는 직사각형을 그린다.     */
        Rectangle(hdc, 50, 100, 200, 180);

        /* (220, 100)을 왼쪽 위 꼭지점으로 갖고 (400, 200)을
           오른쪽 아래 꼭지점으로 갖는 직사각형에 내접하는 타원을 그린다.*/
        Ellipse(hdc, 220, 100, 400, 200);

        EndPaint(hWnd, &ps);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
