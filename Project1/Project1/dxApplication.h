#pragma once
#include "windowApplication.h"
#include "dxDevice.h"
#if PART >= 4
#include <DirectXMath.h>
#endif

using namespace mini;

class DxApplication : public WindowApplication
{
public:
	explicit DxApplication(HINSTANCE hInstance);
	//static vector<XMFLOAT2> CreateTriangleVertices();

protected:
	int MainLoop() override;

private:
	void Render();
	void Update();

	DxDevice m_device;
	dx_ptr<ID3D11RenderTargetView> m_backBuffer;
	dx_ptr<ID3D11DepthStencilView> m_depthBuffer;
	dx_ptr<ID3D11Buffer> m_vertexBuffer;
	dx_ptr<ID3D11VertexShader> m_vertexShader;
	dx_ptr<ID3D11PixelShader> m_pixelShader;
	dx_ptr<ID3D11InputLayout> m_layout;
};
