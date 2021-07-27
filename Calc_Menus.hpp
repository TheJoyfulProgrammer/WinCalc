#ifndef CALC_MENUS_HPP_INCLUDED
#define CALC_MENUS_HPP_INCLUDED

#include <windows.h>
#include <string>

namespace win
{
  extern void CreateMainWindowMenu(HWND);

  enum
  {
    IDM_CalcProgrammer,
    IDM_DigitGrouping,
    IDM_Copy,
    IDM_Paste,
    IDM_HelpTopics,
    IDM_AboutWinCalc
  };

}

#endif // CALC_MENUS_HPP_INCLUDED
