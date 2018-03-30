#include <windows.h>

#define internal static
#define local_persist static
#define global_variable static

// TODO: this is a global for now.
global_variable bool Running;

internal void
ResizeDIBSection(int Width, int Height)
{
}

LRESULT CALLBACK 
MainWindowCallback(HWND Window, UINT Message,WPARAM WParam, LPARAM LParam)
{
	LRESULT result = 0;
	switch(Message)
	{
		case WM_SIZE: 
		{
			RECT ClientRect;
			GetClientRect(Window, &ClientRect);
			int Height = ClientRect.bottom - ClientRect.top;
			int Width = ClientRect.right - ClientRect.left;
			ResizeDIBSection(Width, Height);
			OutputDebugStringA("WM_SIZE\n");
		} break;
		case WM_CLOSE: 
		{
			// TODO: handle this with a message to the user?
			Running = false;
			OutputDebugStringA("WM_CLOSE\n");
		} break;
		case WM_ACTIVATEAPP: 
		{
			OutputDebugStringA("WM_ACTIVATEAPP\n");
		} break;
		case WM_DESTROY: 
		{
			//TODO: Handle this as an error - recreate window?
			Running = false;
			OutputDebugStringA("WM_DESTROY\n");
		} break;
		case WM_PAINT:
		{
			OutputDebugStringA("WM_PAINT\n");
			PAINTSTRUCT Paint;
			HDC DeviceContext = BeginPaint(Window, &Paint);
			Win32UpdateWindow();
			int x = Paint.rcPaint.left;
			int y = Paint.rcPaint.top;
			int height = Paint.rcPaint.bottom - Paint.rcPaint.top;
			int width = Paint.rcPaint.right - Paint.rcPaint.left;
			local_persist DWORD Operation = BLACKNESS;
			PatBlt(DeviceContext,x,y,width, height, Operation);
			if (Operation == BLACKNESS) 
			{
				Operation = WHITENESS;
			}
			else
			{
				Operation = BLACKNESS;
			}
			EndPaint(Window, &Paint);
			
		} break;
		default: 
		{
			return DefWindowProc(Window, Message, WParam, LParam);
		} break;
	}
	return result;
}

int CALLBACK 
WinMain (HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CmdLine,int CmdShow)
{
	WNDCLASS WindowClass = {};
	WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
	WindowClass.lpfnWndProc = MainWindowCallback;	
	WindowClass.hInstance = Instance;
	// WindowClass.hIcon = ;
	WindowClass.lpszClassName = LPCTSTR("HandmadeHeroWindowClass");  

	if (RegisterClass(&WindowClass))
	{
		HWND WindowHandle = CreateWindowEx (

			0,
			WindowClass.lpszClassName,
			LPCTSTR("Handmade Hero"),
			WS_OVERLAPPEDWINDOW|WS_VISIBLE,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			0,
			0,
			WindowClass.hInstance,
			0
		);

		if (WindowHandle) 
		{
			Running = true;
			while (Running)
			{
				MSG Message;
				BOOL MessageResult = GetMessage(&Message, 0,0,0);
				if (MessageResult > 0)
				{
					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			// TODO: Logging
		}
	}
	else
	{
		// TODO: Logging
	}
}