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
    /* ���콺 ���� ��ư�� ������ �� �� ��ġ�� x, y�� �����ϰ�
       bNowDraw ���� TRUE�� �ٲپ������ν� �׸��⸦ �����ϵ��� �Ѵ�. */
    case WM_LBUTTONDOWN:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        bNowDraw = TRUE;
        return 0;

    /* ���콺�� �����̴� ��츦 ó���Ѵ�. */
    case WM_MOUSEMOVE:
        /* bNowDraw�� TRUE�� ��, �� ���콺 ���� ��ư�� �����ִ� �����̸�,
           ���콺�� ������ ������ �� �ȼ������� ���� �׸��鼭 �����Ѵ�.
           ���� ���콺 ���� Ŭ���� �� ���¿��� Ŀ���� �����̸�
           �������� ���� ���� ��Ÿ�� �׸��� �׸��� �ְ� �Ǵ°��̴�. */
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

    /* Ŭ���� ���� ��� bNowDraw�� FALSE�� �ٲپ� �����ν�
       ���̻��� ���콺�� �����̴��� ȭ�鿡 �׷����� �ʵ��� �Ѵ�. */
    case WM_LBUTTONUP:
        bNowDraw = FALSE;
        return 0;

    /* Alt+F4�� ó���Ѵ�. */
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
