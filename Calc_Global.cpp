#include <windows.h>

//  USING GLOBAL VARIABLES CAN CAUSE GLOBAL NAMESPACE POLLUTION AND
//  COULD CAUSE NAMEING CONFLICTS.
namespace win
{
  //  THESE ARE THE DECLARATIONS/DEFINITIONS THAT ARE POINTED TO BY
  //  THE "EXTERN" DECLARATIONS IN THE HEADER FILE. IF THESE ARE NOT
  //  DECLARED IN THE HEADER FILE, THE COMPILER WILL IGNORE THEM AND
  //  YOU MAY GET "UNDEFINED" TYPE ERRORS.

  HINSTANCE AppInstanceHandle;
  HWND      WindowHandle;
  int       CommandShow;
  LPSTR     CommandLineString;
  RECT      WindowClientAreaSize;
  RECT      WindowTotalSize;
}