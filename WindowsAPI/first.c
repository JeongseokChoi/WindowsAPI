#include <Windows.h>


/* ������ ���ν���(Window Procedure) �Լ��� �����Ѵ�. */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/* �ܺο����� �ν��Ͻ��� ����ϵ��� ���������� ������ �д�. */
HINSTANCE g_hInst;

/* �������� �̸��� ���������� �����Ѵ�. */
LPCTSTR lpszClass = TEXT("First");


/* WinMain�� ���α׷��� ��Ʈ������Ʈ�̴�.
   �ܼ� ���ø����̼ǿ����� main�� ���ٰ� ���� �ȴ�.
   ȭ�� ����� �� �����̸�,
   ������ ���ν����� �޼����� �����ϴ� ������ �Ѵ�. */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszCmdParam,
                     int nCmdShow)
{
    HWND hWnd;
    MSG Message;
    WNDCLASS WndClass;
    g_hInst = hInstance;

    /* ȭ�� ��� ������ ��� ����ü WndClass�� �����Ѵ�. */
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WndClass.hInstance = hInstance;
    WndClass.lpfnWndProc = WndProc;
    WndClass.lpszClassName = lpszClass;
    WndClass.lpszMenuName = NULL;
    WndClass.style = CS_HREDRAW | CS_VREDRAW;

    /* ȭ�� ����� ���� WndClass�� ����Ѵ�. */
    RegisterClass(&WndClass);

    /* ����� �����츦 �����Ѵ�. */
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

    /* �����츦 ȭ�鿡 ����Ѵ�. */
    ShowWindow(hWnd, nCmdShow);

    /* �޼����� ó���Ѵ�. */
    while (GetMessage(&Message, NULL, 0, 0))
    {
        /* Ű���� �Է� �޼����� ����ϱ� ���� ó���Ѵ�. */
        TranslateMessage(&Message);

        /* �޼����� ������ ���ν����� �Ѱ��ش�. */
        DispatchMessage(&Message);
    }

    return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,
                         UINT iMessage,
                         WPARAM wParam,
                         LPARAM lParam)
{
    switch (iMessage)
    {
    /* Alt+F4�� ���� ��� ���α׷��� ���������� ����ǵ��� ���ش�. */
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    /* ���α׷��Ӱ� �ۼ��� �ڵ忡 ���� ó������ ���� �޼�����
       �ý����� �⺻(default) ������ ���� ó���ǵ��� ���ش�. */
    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
