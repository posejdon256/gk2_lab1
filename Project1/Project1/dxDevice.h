#pragma once

#include "../dxptr.h"
#include "../window.h"
#include <d3d11.h>
using namespace mini;

class DxDevice {
public:
	explicit DxDevice(const Window& window);
	const dx_ptr<ID3D11DeviceContext>& context() const
	{
		return m_context;
	}
	const dx_ptr<IDXGISwapChain>& swapChain() const
	{
		return m_swapChain;
	}
	ID3D11Device* operator->() const { return m_device.get(); }
	dx_ptr<ID3D11RenderTargetView> CreateRenderTargetView(const dx_ptr<ID3D11Texture2D>& texture) const;

private:
	dx_ptr<ID3D11Device> m_device;
	dx_ptr<ID3D11DeviceContext> m_context;
	dx_ptr<IDXGISwapChain> m_swapChain;
};