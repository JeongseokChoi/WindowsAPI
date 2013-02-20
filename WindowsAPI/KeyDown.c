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

    /* �ʱ���ġ�� (100, 100)���� �����Ѵ�. */
    static int  x = 100;
    static int  y = 100;

    switch (iMessage)
    {
    /* Ű���尡 ������ ��츦 ó���Ѵ�. */
    case WM_KEYDOWN:
        /* ����Ű�� ������ ���⿡ ���� ��ġ�� �����Ѵ�. */
        switch(wParam)
        {
        case VK_LEFT : x -= 8; break;
        case VK_RIGHT: x += 8; break;
        case VK_UP   : y -= 8; break;
        case VK_DOWN : y += 8; break;
        }
        /* ȭ���� ������ ��ȿȭ���� WM_PAINT �޼����� �߻���Ų��.
           �� �� �Լ��� ������ ���ڰ� TRUE�̱� ������ ȭ���� �����
           �ٽ� �׸���. ���� FALSE��� ȭ���� ������ �ʰ� ������ �׸���. */
        InvalidateRect(hWnd, NULL, TRUE);
        return 0;

    /* ȭ���� �׷��� �ϴ� ��츦 ó���Ѵ�. */
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        TextOut(hdc, x, y, TEXT("A"), 1);
        EndPaint(hWnd, &ps);
        return 0;

    /* Alt+F4�� ���� ��츦 ó���Ѵ�. */
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
