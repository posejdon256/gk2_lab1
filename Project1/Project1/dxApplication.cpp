#include "dxApplication.h"
#include <DirectXMath.h>;

using namespace mini;
using namespace std;
using namespace DirectX;

vector<XMFLOAT2> CreateTriangleVertices() {
	vector<XMFLOAT2> _vector;
	_vector.push_back(XMFLOAT2(1.0f, 1.0f));
	_vector.push_back(XMFLOAT2(0.9f, 0.0f));
	_vector.push_back(XMFLOAT2(0.7f, 0.7f));
	return _vector;
}

DxApplication::DxApplication(HINSTANCE hInstance)
	: WindowApplication(hInstance), m_device(m_window)
{
	ID3D11Texture2D *temp;
	dx_ptr<ID3D11Texture2D> backTexture;
	m_device.swapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&temp));
	backTexture.reset(temp);

	m_backBuffer = m_device.CreateRenderTargetView(backTexture);

	SIZE wndSize = m_window.getClientSize();
	m_depthBuffer = m_device.CreateDepthStencilView(wndSize);
	auto backBuffer = m_backBuffer.get();
	m_device.context()->OMSetRenderTargets(1,
		&backBuffer, m_depthBuffer.get());
	Viewport viewport{ wndSize };
	m_device.context()->RSSetViewports(1, &viewport);

	vector<XMFLOAT2> vertices = CreateTriangleVertices();
	m_vertexBuffer = m_device.CreateVertexBuffer(vertices);
	auto vsBytes = m_device.LoadByteCode(L"vs.cso");
	auto psBytes = m_device.LoadByteCode(L"ps.cso");
	m_vertexShader = m_device.CreateVertexShader(vsBytes);
	m_pixelShader = m_device.CreatePixelShader(psBytes);
	vector<D3D11_INPUT_ELEMENT_DESC> elements{
		{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0,
		D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	m_layout = m_device.CreateInputLayout(elements, vsBytes);
}
int DxApplication::MainLoop()
{
	MSG msg;
	//PeekMessage doesn't change MSG if there are no messages to be recieved.
	//However unlikely the case may be, that the first call to PeekMessage
	//doesn't find any messages, msg is zeroed out to make sure loop condition
	//isn't reading unitialized values.
	ZeroMemory(&msg, sizeof msg);
	do
	{
		if (PeekMessage(&msg, nullptr, 0,0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Update();
			Render();
			m_device.swapChain()->Present(0, 0);
		}
	} while (msg.message != WM_QUIT);
	return msg.wParam;
}

void DxApplication::Update()
{

}

void DxApplication::Render()
{
	float clearColor[] = { 0.5f, 0.5f, 1.0f, 1.0f };
	m_device.context()->ClearRenderTargetView(m_backBuffer.get(), clearColor);
	m_device.context()->ClearDepthStencilView(
		 m_depthBuffer.get(),
		 D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	 m_device.context()->VSSetShader(
		 m_vertexShader.get(), nullptr, 0);
	 m_device.context()->PSSetShader(
		 m_pixelShader.get(), nullptr, 0);
	 m_device.context()->IASetInputLayout(m_layout.get());
	 ID3D11Buffer* vbs[] = { m_vertexBuffer.get() };
	 UINT strides[] = { sizeof(XMFLOAT2) };
	 UINT offsets[] = { 0 };
	 m_device.context()->IASetPrimitiveTopology(
		 D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	 m_device.context()->IASetVertexBuffers(
		 0, 1, vbs, strides, offsets);
	 m_device.context()->Draw(3, 0);
}