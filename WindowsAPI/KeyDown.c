#include <Windows.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR   lpszClass = TEXT("KeyDown");


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

LRESULT CALLBACK WndProc(HWND   hWnd,
                         UINT   iMessage,
                         WPARAM wParam,
                         LPARAM lParam)
{
    HDC         hdc;
    PAINTSTRUCT ps;

    /* 초기위치를 (100, 100)으로 설정한다. */
    static int  x = 100;
    static int  y = 100;

    switch (iMessage)
    {
    /* 키보드가 눌리는 경우를 처리한다. */
    case WM_KEYDOWN:
        /* 방향키가 눌리는 방향에 따라 위치를 조정한다. */
        switch(wParam)
        {
        case VK_LEFT : x -= 8; break;
        case VK_RIGHT: x += 8; break;
        case VK_UP   : y -= 8; break;
        case VK_DOWN : y += 8; break;
        }
        /* 화면을 강제로 무효화시켜 WM_PAINT 메세지를 발생시킨다.
           이 때 함수의 마지막 인자가 TRUE이기 때문에 화면을 지우고
           다시 그린다. 만약 FALSE라면 화면을 지우지 않고 덧씌워 그린다. */
        InvalidateRect(hWnd, NULL, TRUE);
        return 0;

    /* 화면을 그려야 하는 경우를 처리한다. */
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        TextOut(hdc, x, y, TEXT("A"), 1);
        EndPaint(hWnd, &ps);
        return 0;

    /* Alt+F4가 눌린 경우를 처리한다. */
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
