#include "dxDevice.h"
#include "../exceptions.h"
#include "../window.h"
#include "dxStructures.h"

using namespace mini;

DxDevice::DxDevice(const Window& window) {
	SwapChainDescription desc
	{
		window.getHandle(), window.getClientSize()
	};
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* ctx = nullptr;
	IDXGISwapChain* swChain = nullptr;
	auto hr = D3D11CreateDeviceAndSwapChain(nullptr,
		D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
		D3D11_SDK_VERSION, &desc, &swChain, &device,
		nullptr, &ctx);
	m_device.reset(device);
	m_swapChain.reset(swChain);
	m_context.reset(ctx);
	if (FAILED(hr)) THROW_WINAPI;
}
dx_ptr<ID3D11RenderTargetView> DxDevice::CreateRenderTargetView(const dx_ptr<ID3D11Texture2D>& texture) const {
	ID3D11RenderTargetView* temp;
	auto hr = m_device->CreateRenderTargetView(texture.get(),
		nullptr, &temp);
	dx_ptr<ID3D11RenderTargetView> result(temp);
	if (FAILED(hr)) THROW_WINAPI;
	return result;
}