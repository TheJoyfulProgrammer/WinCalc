/*
    WinCalc

    Created By:  Walter Whitman
                 The Joyful Programmer

    Created on:  July 14th, 2021

    Description: Windows-Only Calculator.


    COMPILING WITH G++

    g++.exe -O3 -Wall -m64 -std=c++2a -c "Calc_Global.cpp" -o Calc_Global.o
    g++.exe -O3 -Wall -m64 -std=c++2a -c "Calc_Window.cpp" -o Calc_Window.o
    g++.exe -O3 -Wall -m64 -std=c++2a -c "Calc_WindowProcedure.cpp" -o Calc_WindowProcedure.o
    g++.exe -O3 -Wall -m64 -std=c++2a -c "WinCalc.cpp" -o oWinCalc.o
    g++.exe  -o WinCalc.exe Calc_Global.o Calc_Window.o Calc_WindowProcedure.o WinCalc.o  -static-libstdc++ -m64 -lgdi32 -lgdiplus   -mwindows


    Currently, this project is setup in the Code::Blocks IDE for those beginners
    who wishes to use that IDE to compile the project. To open this project in
    Code::Blocks, simply open the WinCalc.cbp file in Code::Blocks.
*/

#include <windows.h>
#include <string>
#include <cwchar>
#include "Calc_Global.hpp"
#include "Calc_Window.hpp"


//  IN MICROSOFT WINDOWS, THE MAIN FUNCTION FOR GRAPHICAL WINDOWS IS CALLED
//  "WinMain".
//  WINMAIN:  https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-winmain
int WINAPI WinMain(HINSTANCE AppInstanceHandle,
                   HINSTANCE AppPreviousInstanceHandle,
                   LPSTR     CommandLineString,
                   int       CommandShow
)
{
  //  SAVE THE WINMAIN PARAMETERS FOR LATER USAGE
  win::AppInstanceHandle = AppInstanceHandle;
  win::CommandLineString = CommandLineString;
  win::CommandShow = CommandShow;

  //  CALL OUR "WINDOW" FUNCTION DEFINED IN THE CALC_WINDOW.CPP CODE FILE.
  //  WHEN THIS FUNCTION IS CALLED, A NEW GUI WINDOW IS CREATED AND CONTOL
  //  IS THEN PASSED TO THE "WINDOWPROCEDURE FUNCTION DEFINED IN THE
  //  WINDOW CLASS USED TO CREATE THE WINDOW. THE WINDOW PROCEDURE (FUNCTION)
  //  IS WHERE ALL WINDOW EVENTS ARE HANDLE. SEE THE WINDOW PROCEDURE
  //  FUNCTION FOR MORE INFORMATION.
  win::Window(-400, -500, 770, 408);

  //  WHILE YOU CAN HANDLE THE CLOSING AND SHUTTING DOWN OF THE WINDOW ALL
  //  IN THE WINDOW PROCEDURE, YOU CAN ALSO DO SOME FINIALIZATION HERE. YOU
  //  CAN NOT CREATE A NEW WINDOW WITH THE ABOVE FUNCTION AS IT WILL FAIL.
  //  TRY IT TO FIND OUT! JUST UNCOMMENT THE CODE BELOW THIS LINE.
  //win::Window(-1, -1, 800, 600);


  return 0;
}
