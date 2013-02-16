#include <Windows.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR   lpszClass = TEXT("DrawText");


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
    RECT        rt = {100, 100, 400, 300};
    TCHAR      *str = TEXT("님은 갔습니다. 아아 사랑하는 나의 님은 갔습니다.")
                      TEXT("푸른 산빛을 깨치고 단풍나무 숲을 향하여 난 작은 ")
                      TEXT("길을 걸어서 차마 떨치고 갔습니다. 황금의 꽃같이 ")
                      TEXT("굳고 빛나던 옛 맹세는 차디찬 티끌이 되어 한숨의 ")
                      TEXT("미풍에 날아갔습니다.");

    switch (iMessage)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    /* 프로그램 실행 중에 다른 프로그램에 의해 윈도우가 가려지면
       WM_PAINT 메세지가 발생하며, 그 때마다 윈도우를 다시 그린다. */
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        /* 주어진 사각형 틀 안에 가운데정렬과 자동줄바꿈 속성으로 글이 출력된다. */
        DrawText(hdc, str, -1, &rt, DT_CENTER|DT_WORDBREAK);

        EndPaint(hWnd, &ps);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
