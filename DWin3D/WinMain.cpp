#include <Windows.h>
#include "../DWin3DLib/IViewport.h"
#include "../DWin3DLib/DehaxGL.h"

#pragma comment (lib, "DWin3DLib.lib")

#define WIDTH 400
#define HEIGHT 300

HDC gHdc = nullptr;

BITMAPINFO bitmapInfo = {};

int bytesPerLine;

HBITMAP gBitmap = nullptr;

COLORREF color = 0x000000FF;

class Viewport : public IViewport {
public:
	void setPixel(const int &x, const int &y, const ARGB &color)
	{
		if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
			return;
		}

		int ind = 3 * x;
		((BYTE *)pBits)[y * bytesPerLine + ind] = GetBValue(color);
		((BYTE *)pBits)[y * bytesPerLine + ind + 1] = GetGValue(color);
		((BYTE *)pBits)[y * bytesPerLine + ind + 2] = GetRValue(color);
	}

	void setSize(const int &width, const int &height)
	{

	}

	void clear()
	{

	}

	int getWidth() const
	{
		return WIDTH;
	}

	int getHeight() const
	{
		return HEIGHT;
	}

	void *pBits = 0;
};

Viewport *viewport = new Viewport();
DehaxGL dehaxGL = DehaxGL(viewport);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
		case WM_CREATE:
			gHdc = GetDC(hwnd);
			gBitmap = CreateDIBSection(gHdc, &bitmapInfo, DIB_RGB_COLORS, &viewport->pBits, nullptr, 0);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_KEYDOWN:
			dehaxGL.camera().rotate(0.0L, degreeToRadian(5.0L), 0.0L);
			InvalidateRect(hwnd, nullptr, true);
			return 0;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			dehaxGL.render(DehaxGL::RenderMode::Both);
			StretchDIBits(hdc, 0, 0, WIDTH, HEIGHT, 0, 0, WIDTH, HEIGHT, viewport->pBits, &bitmapInfo, DIB_RGB_COLORS, SRCCOPY);

			EndPaint(hwnd, &ps);
			return 0;
		}
		case WM_CLOSE:
			DestroyWindow(hwnd);
			return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfo.bmiHeader.biWidth = WIDTH;
	bitmapInfo.bmiHeader.biHeight = HEIGHT;
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biBitCount = 24;
	bitmapInfo.bmiHeader.biCompression = BI_RGB;

	bytesPerLine = ((WIDTH * bitmapInfo.bmiHeader.biBitCount + 31) / 32) * 4;

	dehaxGL.scene().addModel(ModelsFactory::camera());

	const wchar_t *windowClassName = L"DWin3D";

	WNDCLASSEX windowClass = {};
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.hInstance = hInstance;
	windowClass.lpszClassName = windowClassName;

	RegisterClassExW(&windowClass);

	HWND hwnd = CreateWindowExW(0, windowClassName, L"Dehax WinAPI 3D renderer", WS_OVERLAPPEDWINDOW, 0, 0, WIDTH, HEIGHT, nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hwnd, nCmdShow);

	MSG msg = {};

	while (GetMessageW(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return 0;
}
