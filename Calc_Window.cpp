#include <windows.h>
#include <string>
#include <cwchar>
#include "Calc_WindowProcedure.hpp"
#include "Calc_Global.hpp"

namespace win
{

  //  SINCE THIS IS A SINGLE WINDOW APP, WE WILL ONLY WORRY ABOUT A SINGLE GUI WINDOW
  //  OBJECT. AS SUCH, WE WILL HARD CODE THE INFO FOR THE PRIMARY WINDOW.

  const std::string WindowClassName{"WinCalc 1.0"};
  const std::string WindowTitle{"WinCalc 1.0 - 64-Bit"};

  int Window(int WinXPos, int WinYPos, int WinWidth, int WinHeight)
  {
    //  WNDCLASSEXA:
    //  https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassexa

    WNDCLASSEXA WindowClass;

    WindowClass.cbSize         = sizeof(WNDCLASSEX);
    WindowClass.style          = CS_HREDRAW | CS_VREDRAW;
    WindowClass.lpfnWndProc    = win::WindowProcedure;
    WindowClass.cbClsExtra     = 0;
    WindowClass.cbWndExtra     = 0;
    WindowClass.hInstance      = win::AppInstanceHandle;
    WindowClass.hIcon          = LoadIcon(win::AppInstanceHandle, IDI_APPLICATION);
    WindowClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    WindowClass.hbrBackground  = (HBRUSH) (COLOR_WINDOW + 1);
    WindowClass.lpszMenuName   = NULL;
    WindowClass.lpszClassName  = win::WindowClassName.c_str();
    WindowClass.hIconSm        = LoadIcon(win::AppInstanceHandle, IDI_APPLICATION);

    //  DETECT ANY ERRORS WHEN REGISTERING THE WINDOWS CLASS. IF ANY ERRORS ARE
    //  FOUND, THEN EXIT APP.
    if (!RegisterClassEx(&WindowClass))
    {
      //  MESSAGEBOX:
      //  https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox
      MessageBox (NULL, "ERROR: Registering window failed!", "ERROR", MB_OK);

      return 1;
    }

    //  typedef struct tagRECT {LONG left; LONG top; LONG right; LONG bottom;} RECT;
    //  IF THE WINXPOS AND WINYPOS VARIABLES HAVE A VALUE LESS THEN ZERO THEN WE CLIP IT AT ZERO.
    //  NEGATIVE VALUES CAN BE USED FOR LATER SCREEN POSITIONING PURPOSES.
    RECT  WindowRect{WinXPos >= 0 ? WinXPos : 0, WinYPos >= 0 ? WinYPos : 0, WinWidth, WinHeight};
    DWORD WindowExtendedStyle{WS_EX_OVERLAPPEDWINDOW | WS_EX_COMPOSITED | WS_EX_TRANSPARENT};
    DWORD WindowStyle{WS_OVERLAPPEDWINDOW};

    // SAVE THE CLIENT AREA SIZE FOR LATER USAGE
    win::WindowClientAreaSize = WindowRect;

    //  THE CREATEWINDOWEX FUNCTION CREATES THE ENTIRE WINDOW, INCLUDING THE NON-CLIENT AREA,
    //  THE SIZE THAT IS REQUESTED. TO CREATE A WINDOW WHOSE CLIENT AREA IS THE REQUESTED SIZE,
    //  WE NEED TO ADD THE NON-CLIENT AREA SIZE INFORMATION. THAT IS EXACTLY WHAT THE
    //  ADJUSTWINDOWRECTEX FUNCTION DOES.
    //  ADJUSTWINDOWRECTEX:
    //  https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-adjustwindowrectex
    AdjustWindowRectEx(&WindowRect, WindowStyle, FALSE, WindowExtendedStyle);

    // SAVE THE TOTAL WINDOW SIZE FOR LATER USAGE
    win::WindowTotalSize = WindowRect;

    //  CREATEWINDOWEX:
    //  https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa
    win::WindowHandle = CreateWindowEx(
      WindowExtendedStyle,                     // DWORD      dwExStyle
      //  THE WIN32 API USES C-STYLE STRINGS AS INPUT, AND SINCE WE WANT TO USE C++ STRINGS IN OUR
      //  APP, WE NEED TO CONVERT THEM TO C-STYLE STRINGS. THANKFULLY, C++ OFFERS AN EXTREMELY
      //  EASY WAY TO CONVERT C++ STRINGS TO C-STYLE STRINGS, IN THE FORM OF A FUNCTION, CALLED
      //  C_STR().
      win::WindowClassName.c_str(),            // LPCSTR     lpClassName
      win::WindowTitle.c_str(),                // LPCSTR     lpWindowName
      WindowStyle,                             // DWORD      dwStyle
      //  IF WINXPOS IS NEGATIVE, THEN WE TELL WINDOWS TO POSITION THE APPS WINDOW IN THE
      //  DEFAULT HORIZONTAL POSITION THAT WINDOWS CHOOSES (DECLARED BY THE CW_USEDEFAULT VALUE).
      //  IF THE VALUE IS POSITIVE, THEN WE POSITION THE WINDOW TO THE DEVELOPER'S DEFINED SCREEN
      //  X-COORDINATE.
      WinXPos >= 0 ? WinXPos : CW_USEDEFAULT,  // int        X
      //  IF WINYPOS IS NEGATIVE, THEN WE TELL WINDOWS TO POSITION THE APPS WINDOW IN THE
      //  DEFAULT VERTICAL POSITION THAT WINDOWS CHOOSES (DECLARED BY THE CW_USEDEFAULT VALUE).
      //  IF THE VALUE IS POSITIVE, THEN WE POSITION THE WINDOW TO THE DEVELOPER'S DEFINED SCREEN
      //  Y-COORDINATE.
      WinYPos >= 0 ? WinYPos : CW_USEDEFAULT,  // int        Y
      //  ADJUST THE OVERALL WINDOW SIZE TO MAKE SURE THE CLIENT AREA IS THE EXACT SIZE THE
      //  DEVELOPER REQUESTED. THE OVERALL SIZE CAN BE CALCULATED WITH SIMPLE MATHEMATICS.
      WindowRect.right - WindowRect.left,      // int        nWidth
      WindowRect.bottom - WindowRect.top,      // int        nHeight
      //  THE WINDOW WE ARE CREATING IS THE PARENT WINDOW, SO WE ALWAYS SET THE FOLLOWING PARAMETER
      //  TO NULL.
      NULL,                                    // HWND       hWndParent
      //  THE FOLLOWING HMENU PARAMETER ALLOWS US TO DEFINE THE MENU LAYOUT IN OUR RESOURCE FILE,
      //  BUT FOR EDUCATIONAL PURPOSES, WE WILL CREATE THE WINDOW MENU LATER USING WIN32 API. SO,
      //  WE NEED TO SET THIS VALUE TO NULL AS WELL.
      NULL,                                    // HMENU      hMenu
      win::AppInstanceHandle,                  // HINSTANCE  hInstance
      NULL                                     // LPVOID     lpParam
    );

    //  CHECK FOR ERRORS
    if (!WindowHandle)
    {
      MessageBox (NULL, "ERROR: Creating window failed!", "ERROR", MB_OK);

      return 1;
    }

    //  SHOWWINDOW:
    //  https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow
    ShowWindow(win::WindowHandle, win::CommandShow);
    //  UPDATEWINDOW:
    //  https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-updatewindow
    UpdateWindow(win::WindowHandle);

    //  DEFINE THE EVENT MESSAGE VARIABLE HERE. THIS HELPS WITH THE INTERNAL
    //  STRUCTURE OF THE DATA, WHICH IN TURNS HELPS SPEED UP THE APP THTOUGH
    //  DATA CACHE (ON THE PROCESSOR) OPTIIZATIONS.
    MSG EventMessage;

    //  TO KEEP THE WINDOW FROM CLOSING IN WINDOW'S GRAPHICAL WINDOWS, WE MUST
    //  USE AN "EVENT LOOP", WHICH IS SIMILAR TO A "GAME LOOP"
    //  GETMESSAGE:
    //  https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmessage
    while (GetMessage(&EventMessage, NULL, 0, 0))
    {
      //  TRANSLATE VIRTUAL-KEY MESSAGES TO CHARACTER MESSAGES AND POST TO THE
      //  CALLING THREAD'S MESSAGE QUEUE (Pronounced: Q).
      //  TRANSLATEMESSAGE:
      //  https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-translatemessage
      TranslateMessage(&EventMessage);
      //  DISPATCH MESSAGE TO THE WINDOW PROCEDURE SO THE FUNCTION CAN DO
      //  SOMETHING WITH IT.
      //  DISPATCHMESSAGE:
      //  https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-dispatchmessage
      DispatchMessage(&EventMessage);
    }

    //  RETURN THE EVENT MESSAGE INT VALUE FROM THE WPARAM PARAMTER. THIS ALLOWS
    //  THE APP TO RETURN EITHER THE NON-ERROR MESSAGE (0), OR THE ERROR MESSAGE
    //  INT VALUE.
    return (int) EventMessage.wParam;
  }
}
