#include "dxStructures.h"

SwapChainDescription::SwapChainDescription(HWND wndHwnd, SIZE wndSize) {
	ZeroMemory(this, sizeof(SwapChainDescription));
	BufferDesc.Width = wndSize.cx;
	BufferDesc.Height = wndSize.cy;
	BufferDesc.Format = DXGI_FORMAT_R10G10B10A2_UNORM;
	BufferDesc.RefreshRate.Numerator = 120;
	BufferDesc.RefreshRate.Denominator = 1;
	BufferCount = 1;
	BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	OutputWindow = wndHwnd;
	SampleDesc.Quality = 0;
	SampleDesc.Count = 1;
	Windowed = true;
}