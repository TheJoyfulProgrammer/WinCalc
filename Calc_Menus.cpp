#include <windows.h>
#include <string>
#include <cwchar>
#include "Calc_Menus.hpp"

namespace win
{
  //  SINCE C++ DOES NOT ALLOW DEFINITIONS IN HEADER FILES, WE PLACE THESE HERE.

  const std::wstring MSG_CalcProgrammer = L"Programmer";
  const std::wstring MSG_DigitGrouping  = L"Digit Grouping\tCtrl-D";
  const std::wstring MSG_View           = L"View";
  const std::wstring MSG_Copy           = L"Copy\tCtrl-C";
  const std::wstring MSG_Paste          = L"Paste\tCtrl-P";
  const std::wstring MSG_Edit           = L"Edit";
  const std::wstring MSG_HelpTopics     = L"Help Topics\tCtrl-H";
  const std::wstring MSG_AboutWinCalc   = L"About WinCalc\tCtrl-A";
  const std::wstring MSG_Help           = L"Help";

  const uint32_t STYLE_CalcProgrammer   {MF_STRING | MF_CHECKED}; // | MF_OWNERDRAW};
  const uint32_t STYLE_DigitGrouping    {MF_STRING | MF_CHECKED};
  const uint32_t STYLE_View             {MF_POPUP}; //  | MF_OWNERDRAW};
  const uint32_t STYLE_Copy             {MF_STRING};
  const uint32_t STYLE_Paste            {MF_STRING};
  const uint32_t STYLE_Edit             {MF_POPUP};
  const uint32_t STYLE_HelpTopics       {MF_STRING};
  const uint32_t STYLE_AboutWinCalc     {MF_STRING};
  const uint32_t STYLE_Help             {MF_POPUP};



  void CreateMainWindowMenu(HWND MainWindowHandle)
  {
    //  CREATEMENU:
    //  https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createmenu

    HMENU MainMenubarHandle = CreateMenu();
    HMENU TempMenuHandle = CreateMenu();

    AppendMenuW(TempMenuHandle, STYLE_CalcProgrammer, IDM_CalcProgrammer, MSG_CalcProgrammer.c_str());
    AppendMenuW(TempMenuHandle, STYLE_DigitGrouping,  IDM_DigitGrouping,  MSG_DigitGrouping.c_str());

    AppendMenuW(MainMenubarHandle, STYLE_View, (UINT_PTR) TempMenuHandle, MSG_View.c_str());

    //  EMPTY TEMPORARY MENU VARIABLE SO WE CAN KEEP USING THE SAME VARIABLE.
    TempMenuHandle = CreateMenu();

    AppendMenuW(TempMenuHandle, STYLE_Copy,  IDM_Copy,  MSG_Copy.c_str());
    AppendMenuW(TempMenuHandle, STYLE_Paste, IDM_Paste, MSG_Paste.c_str());

    AppendMenuW(MainMenubarHandle, STYLE_Edit, (UINT_PTR) TempMenuHandle, MSG_Edit.c_str());

    TempMenuHandle = CreateMenu();

    AppendMenuW(TempMenuHandle, STYLE_HelpTopics,   IDM_HelpTopics,   MSG_HelpTopics.c_str());
    AppendMenuW(TempMenuHandle, STYLE_AboutWinCalc, IDM_AboutWinCalc, MSG_AboutWinCalc.c_str());

    AppendMenuW(MainMenubarHandle, STYLE_Help, (UINT_PTR) TempMenuHandle, MSG_Help.c_str());

    SetMenu(MainWindowHandle, MainMenubarHandle);
  }
}
