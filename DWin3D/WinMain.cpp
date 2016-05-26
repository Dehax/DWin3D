#include <Windows.h>

#define WIDTH 400
#define HEIGHT 300

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			
			BITMAPINFO bitmapInfo = {};
			bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			bitmapInfo.bmiHeader.biWidth = WIDTH;
			bitmapInfo.bmiHeader.biHeight = HEIGHT;
			bitmapInfo.bmiHeader.biPlanes = 1;
			bitmapInfo.bmiHeader.biBitCount = 24;
			bitmapInfo.bmiHeader.biCompression = BI_RGB;

			int bytesPerLine = ((WIDTH * bitmapInfo.bmiHeader.biBitCount + 31) / 32) * 4;

			void *pBits = 0;
			
			HBITMAP hBitmap = CreateDIBSection(hdc, &bitmapInfo, DIB_RGB_COLORS, &pBits, nullptr, 0);

			COLORREF color = 0xFF0000FF;

			for (int i = 0; i < WIDTH; i++) {
				for (int j = 0; j < HEIGHT; j++) {
					int ind = 3 * i;
					((BYTE *)pBits)[j * bytesPerLine + ind] = GetBValue(color);
					((BYTE *)pBits)[j * bytesPerLine + ind + 1] = GetGValue(color);
					((BYTE *)pBits)[j * bytesPerLine + ind + 2] = GetRValue(color);
				}
			}

			StretchDIBits(hdc, 0, 0, WIDTH, HEIGHT, 0, 0, WIDTH, HEIGHT, pBits, &bitmapInfo, DIB_RGB_COLORS, SRCCOPY);

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
