#include <windows.h>

int CALLBACK WinMain (
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPSTR     lpCmdLine,
  int       nCmdShow
)
{

  MessageBoxA(0, "Hello from windows", "my box",
   MB_OK|MB_ICONINFORMATION);


}