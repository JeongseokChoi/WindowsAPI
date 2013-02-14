#include <Windows.h>


/* 윈도우 프로시저(Window Procedure) 함수를 선언한다. */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/* 외부에서도 인스턴스를 사용하도록 전역변수를 선언해 둔다. */
HINSTANCE g_hInst;

/* 윈도우의 이름을 전역변수로 저장한다. */
LPCTSTR lpszClass = TEXT("First");


/* WinMain은 프로그램의 엔트리포인트이다.
   콘솔 어플리케이션에서의 main과 같다고 보면 된다.
   화면 출력이 주 목적이며,
   윈도우 프로시저로 메세지를 전달하는 역할을 한다. */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszCmdParam,
                     int nCmdShow)
{
    HWND hWnd;
    MSG Message;
    WNDCLASS WndClass;
    g_hInst = hInstance;

    /* 화면 출력 정보를 담는 구조체 WndClass를 세팅한다. */
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

    /* 화면 출력을 위해 WndClass를 등록한다. */
    RegisterClass(&WndClass);

    /* 출력할 윈도우를 생성한다. */
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

    /* 윈도우를 화면에 출력한다. */
    ShowWindow(hWnd, nCmdShow);

    /* 메세지를 처리한다. */
    while (GetMessage(&Message, NULL, 0, 0))
    {
        /* 키보드 입력 메세지를 사용하기 쉽게 처리한다. */
        TranslateMessage(&Message);

        /* 메세지를 윈도우 프로시저로 넘겨준다. */
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
    /* Alt+F4를 누를 경우 프로그램이 정상적으로 종료되도록 해준다. */
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    /* 프로그래머가 작성한 코드에 의해 처리되지 않은 메세지를
       시스템의 기본(default) 설정에 의해 처리되도록 해준다. */
    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
