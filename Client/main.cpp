#include "pch.h"
#include "Client.h"
#include "CEngine.h"

#include "CEventMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND      g_hWnd;                    // MainWindow 핸들
WCHAR szTitle[100];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[100];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// SAL
int APIENTRY wWinMain(HINSTANCE hInstance, // 프로그램 시작 주소
                      HINSTANCE hPrevInstance,
                      LPWSTR    lpCmdLine,
                      int       nCmdShow)    
{
    // 동적할당 정보 저장
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // _CrtSetBreakAlloc(65962);

    // 윈도우 기본 세팅 추가
    MyRegisterClass(hInstance);
        

    // 등록한 윈도우 세팅으로 윈도우 생성
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }


    // Engine 초기화
    CEngine::GetInst()->init(g_hWnd, 1028, 768);


    // 단축키
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));
       
    MSG msg = {};

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        else
        {
            // FPS
            // 게임 실행
            CEngine::GetInst()->tick();
        }
    }
  
    CSceneMgr::GetInst()->GetCurScene()->DeleteAllObject();
    CEventMgr::GetInst()->tick();
    CEventMgr::GetInst()->tick();

    return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr; //MAKEINTRESOURCEW(IDC_CLIENT);
    wcex.lpszClassName  = L"abcd";//szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   g_hWnd = CreateWindowW(L"abcd", L"Focus", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, false);
   UpdateWindow(g_hWnd);

   return TRUE;
}

#include "CSceneMgr.h"
#include "CScene_Tool.h"

INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK TileSelectProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            //case IDM_ABOUT:
            //    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            //    break;
            /* case IDM_EXIT:
                DestroyWindow(hWnd);
                break;*/
            case ID_TILECOUNT:
            {
                int iReturn = (int)DialogBox(hInst, MAKEINTRESOURCE(DLG_TILECOUNT), hWnd, TileCountProc);
            }
                break;

            case ID_TILESELECT:
            {
                int iReturn = (int)DialogBox(hInst, MAKEINTRESOURCE(DLG_TILESELECT), hWnd, TileSelectProc);
            }
            break;

            case ID_TILESAVE:
            {
                CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(CSceneMgr::GetInst()->GetCurScene());
                if (nullptr != pToolScene)
                    pToolScene->TileSave();
            }                
                break;

            

            case ID_TILELOAD:
            {
                CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(CSceneMgr::GetInst()->GetCurScene());
                if (nullptr != pToolScene)
                    pToolScene->TileLoad();
            }                
                break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            EndPaint(hWnd, &ps);
        }
        break;


    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
