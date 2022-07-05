﻿// InhaWinAPIGame.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "GDIPlusManager.h"
#include "InhaWinAPIGame.h"
#include "Game.h"


#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
VOID    CALLBACK    TimerProc( HWND, UINT, WPARAM, DWORD );
BOOL    CALLBACK    StartDialogProc( HWND, UINT, WPARAM, LPARAM );
BOOL    CALLBACK    ResultDialogProc( HWND, UINT, WPARAM, LPARAM );

GDIPlusManager gdi;
Game game;

bool isStartGame = true;
bool isEndGame = false;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_INHAWINAPIGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_INHAWINAPIGAME));

    // Window Process Message
    MSG msg;
    while ( true )
    {
        if ( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
            if ( msg.message == WM_QUIT )
            {
                return false;
            }
        }
        else
        {
            game.UpdateModel();
        }
    }
    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_INHAWINAPIGAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_INHAWINAPIGAME);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if ( game.IsGameFinished() && !isEndGame )
    {
        DialogBox( hInst, MAKEINTRESOURCE( IDD_RESULT ), hWnd, ResultDialogProc );
        isEndGame = true;
    }
    switch (message)
    {
    case WM_CREATE:
        GetClientRect( hWnd, &game.screenRect );
        SetTimer( hWnd, 0, 0, TimerProc );
        if ( game.IsInitialGame() && isStartGame )
        {
            DialogBox( hInst, MAKEINTRESOURCE( IDD_STARTMENU ), hWnd, StartDialogProc );
        }
        break;
    case WM_SIZE:
        GetClientRect( hWnd, &game.screenRect );
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
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
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            
            game.ComposeFrame(hdc);
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

VOID CALLBACK TimerProc( HWND hWnd, UINT, WPARAM, DWORD )
{
    InvalidateRect( hWnd, nullptr, false );
}

BOOL CALLBACK StartDialogProc( HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
    UNREFERENCED_PARAMETER( lParam );
    switch ( iMsg )
    {
    case WM_INITDIALOG:
        {
            HWND hBtn = GetDlgItem( hDlg, IDC_GAMESTART );
            EnableWindow( hBtn, FALSE );
        }
        return TRUE;

    case WM_COMMAND:
        switch ( LOWORD( wParam ) )
        {
        case IDC_BUTTON1:
            {
                wchar_t word[256];
                GetDlgItemText( hDlg, IDC_EDIT1, word, 256 );
                game.SetUserID( word );

                if ( game.GetUserID().size() != 0 )
                {
                    HWND hBtn = GetDlgItem( hDlg, IDC_GAMESTART );
                    EnableWindow( hBtn, TRUE );
                }
                else
                {
                    HWND hBtn = GetDlgItem( hDlg, IDC_GAMESTART );
                    EnableWindow( hBtn, FALSE );
                }
            }
            break;
        case IDC_GAMESTART:
            {
                EndDialog( hDlg, LOWORD( wParam ) );
                game.StartMainGame();
                return TRUE;
            }
            break;
        case IDCANCEL:
            {
                EndDialog( hDlg, LOWORD( wParam ) );
                PostQuitMessage( 0 );
                return FALSE;
            }
            break;

        }
    }
    return FALSE;
}

BOOL CALLBACK ResultDialogProc( HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
    UNREFERENCED_PARAMETER( lParam );
    switch ( iMsg )
    {
    case WM_INITDIALOG:
        {
            auto scoreMap = game.GetScoreMap();

            std::wstring topNames[3];
            std::wstring topScores[3];

            int i = 0;
            for ( auto rIt = scoreMap.rbegin(); i < 3; ++rIt )
            {
                for ( auto str : rIt->second )
                {
                    if ( i >= 3 )
                    {
                        break;
                    }
                    topNames[i] = str;
                    topScores[i] = std::to_wstring( rIt->first );
                    ++i;
                }
            }
            SetDlgItemText( hDlg, IDC_CURPLAYER, game.GetCurUserId().c_str() );
            SetDlgItemText( hDlg, IDC_CURSCORE, std::to_wstring(game.GetCurScore()).c_str() );
            SetDlgItemText( hDlg, IDC_TOPPLAYER, topNames[0].c_str() );
            SetDlgItemText( hDlg, IDC_TOPPLAYER2, topNames[1].c_str() );
            SetDlgItemText( hDlg, IDC_TOPPLAYER3, topNames[2].c_str() );
            SetDlgItemText( hDlg, IDC_TOPSCORE, topScores[0].c_str() );
            SetDlgItemText( hDlg, IDC_TOPSCORE2, topScores[1].c_str() );
            SetDlgItemText( hDlg, IDC_TOPSCORE3, topScores[2].c_str() );
        }
        return TRUE;
    case WM_COMMAND:
        switch ( LOWORD( wParam ) )
        {

        case IDOK:
        case IDCANCEL:
            {
                EndDialog( hDlg, LOWORD( wParam ) );
                game.SaveDataFromScoreMap();
                PostQuitMessage( 0 );
                return FALSE;
            }
            break;
        }
    }
    return FALSE;
}
