// Clean Vehicle Credit Checker.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Clean Vehicle Credit Checker.h"
#include <iostream>
#include <vector>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
TCHAR year[256], make[256];                     // the currently selected year and make

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Search(HWND, UINT, WPARAM, LPARAM);
std::wstring        Results(LPCWSTR, LPCWSTR);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLEANVEHICLECREDITCHECKER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLEANVEHICLECREDITCHECKER));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLEANVEHICLECREDITCHECKER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLEANVEHICLECREDITCHECKER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

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
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDD_MEOWDYDO:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_MEOWDYDO), hWnd, About);
                break;
            case IDM_SEARCH:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_SEARCHBOX), hWnd, Search);
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
            LPCWSTR test = L"test";
            TextOut(hdc, 25, 25, test, wcslen(test));
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

// Message handler for about box.
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

INT_PTR CALLBACK Search(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    HWND yearDlg, makeDlg;
    yearDlg = GetDlgItem(hDlg, IDC_YEAR);
    makeDlg = GetDlgItem(hDlg, IDC_MAKE);
    switch (message)
    {
    case WM_INITDIALOG:

        SendMessage(yearDlg, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"Select..."));
        SendMessage(yearDlg, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"2023"));
        SendMessage(yearDlg, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"2024"));

        SendMessage(yearDlg, CB_SETCURSEL, 0, 0);


        SendMessage(makeDlg, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"Select..."));
        SendMessage(makeDlg, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"Audi"));
        SendMessage(makeDlg, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"General Motors"));

        SendMessage(makeDlg, CB_SETCURSEL, 0, 0);

        return (INT_PTR)TRUE;


    case WM_COMMAND:
        if (HIWORD(wParam) == CBN_SELCHANGE) 
        {
            // Currently nothing, in the future would add the ability to populate model based on make
            return (INT_PTR)TRUE;
        }
        if (LOWORD(wParam) == IDC_CALCULATE)
        {
            int index;
            // get selected year
            index = SendMessage(yearDlg, CB_GETCURSEL, 0, 0);
            SendMessage(yearDlg, CB_GETLBTEXT, (WPARAM)index, (LPARAM)year);

            // get selected make
            index = SendMessage(makeDlg, CB_GETCURSEL, 0, 0);
            SendMessage(makeDlg, CB_GETLBTEXT, (WPARAM)index, (LPARAM)make);

            // get results based on year and make selection


            // Results(year, make)
            std::wstring test = L"shmoodle";
            MessageBox(hDlg, Results(year, make).c_str(), TEXT("Currently selected make"), MB_OK);
            return (INT_PTR)TRUE;
        }
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

std::wstring Results(LPCWSTR year, LPCWSTR make) {
    // sample data, would eventually be parsed from a .csv file
    std::vector<std::vector<std::wstring>> data = { 
        {
            L"2023", 
            L"Audi", 

            L"Make: Audi\n"
            L"Model: Q5 PHEV 55 TFSI e quattro\n"
            L"Vehicle Model Year: 2023\n"
            L"Applicable MSRP Limit: $80,000\n"
            L"Cridit Amount: $3,750\n\n"
        }, 
        {
            L"2024",
            L"Chevrolet",

            L"Make: Chevrolet\n"
            L"Model: Blazer\n"
            L"Vehicle Model Year: 2024\n"
            L"Applicable MSRP Limit: $80,000\n"
            L"Cridit Amount: $7,500\n\n"
        }
    };

    std::wstring output = L"";
    
    // Filter the results by our search query
    for (std::vector<std::wstring> vec : data) {
        if ((!lstrcmpW(year, vec[0].c_str()) || !lstrcmpW(year, L"Select...")) && (!lstrcmpW(make, vec[1].c_str()) || !lstrcmpW(make, L"Select..."))) {
            //add to return
            output += vec[2];
        }
    }
    if (output == L"") {
        output += L"No results match your query.";
    }
    return output;
}

