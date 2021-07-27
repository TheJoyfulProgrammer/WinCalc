#include <windows.h>
#include <string>
#include <cwchar>
#include "Calc_Menus.hpp"
//#include <iostream>

// Since this demo is for Windows only, we will call the namespace, "win".
namespace win
{
  //  ALL WINDOWS HAVE A DEFAULT PROCEDURE THAT THE OPERATING SYSTEM USES
  //  TO HANDLE ALL EVENT MESSAGES. THE FOLLOWING WINDOW PROCEDURE ALLOWS
  //  US TO PROCESS ANY AND ALL EVENTS MESSAGES WE NEED OR WANT TO.
  //  FOR MORE INFORMATION, PLEASE SEE:
  //  https://docs.microsoft.com/en-us/windows/win32/winmsg/window-procedures
  LRESULT CALLBACK WindowProcedure(HWND WindowHandle,
                                   UINT EventMessage,
                                   WPARAM wParam,
                                   LPARAM lParam)
  {
    PAINTSTRUCT ps;
    HDC DeviceContextHandle;

    std::string greeting{"The Joyful Programmer's future calculator!"};

    switch (EventMessage)
    {
      case WM_CREATE:
        // LET'S CREATE ALL OF THE WINDOW COMMON CONTROLS BEFORE THE WINDOW IS SHOWN ON SCREEN
        win::CreateMainWindowMenu(WindowHandle);

        break;

      case WM_PAINT:
        DeviceContextHandle = BeginPaint(WindowHandle, &ps);
          TextOutA(DeviceContextHandle, 200, 220, greeting.c_str(), greeting.size());
        EndPaint(WindowHandle, &ps);

        break;

      case WM_DESTROY:
        //  POSTQUITEMESSAGE:
        //  https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-postquitmessage
        PostQuitMessage(0);

        break;
      case WM_MEASUREITEM:
        DeviceContextHandle = GetDC(WindowHandle);
        //std::cout << "WM_MEASUREITEM event raised... HDC: " << DeviceContextHandle << "\n";

        break;

      case WM_DRAWITEM:
        //std::cout << "WM_DRAWITEM event raised..." << (rand() % 10000) << "\n";

        break;

      case WM_COMMAND:

        switch(LOWORD(wParam)) {

          case IDM_CalcProgrammer:
            MessageBox (NULL, "CalcProgrammer menu item clicked.", "TESTING...", MB_OK);
            break;

          case IDM_DigitGrouping:
            MessageBox (NULL, "DigitGrouping menu item clicked.", "TESTING...", MB_OK);
            break;

          case IDM_Copy:
            MessageBox (NULL, "Copy menu item clicked", "TESTING...", MB_OK);
            break;

          case IDM_Paste:
            MessageBox (NULL, "Past menu item clicked.", "TESTING...", MB_OK);
            break;

          case IDM_HelpTopics:
            MessageBox (NULL, "HelpTopics menu item clicked.", "TESTING...", MB_OK);
            break;

          case IDM_AboutWinCalc:
            MessageBox (NULL, "AboutWinCalc menu item clicked.", "TESTING...", MB_OK);
            break;
         }

         break;

      default:
        //  DEFWINDOWPROC:
        //  https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-defwindowproca
        return DefWindowProc(WindowHandle, EventMessage, wParam, lParam);

        break;
     }

     return 0;
  }

  void DrawCalcProgrammer()
  {

  }
}

