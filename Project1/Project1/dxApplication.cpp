#include "dxApplication.h"

using namespace mini;

DxApplication::DxApplication(HINSTANCE hInstance)
	: WindowApplication(hInstance), m_device(m_window) { 
	ID3D11Texture2D *temp;
	dx_ptr<ID3D11Texture2D> backTexture;
	m_device.swapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D),
		reinterpret_cast<void**>(&temp));
	backTexture.reset(temp);
	m_backBuffer = m_device.CreateRenderTargetView(backTexture);
}
int DxApplication::MainLoop() {
	MSG msg;
	ZeroMemory(&msg, sizeof msg);
	do {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
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
void DxApplication::Update() {}
void DxApplication::Render() {
	float clearColor[] = { 0.5f, 0.5f, 1.0f, 1.0f };
	m_device.context()->ClearRenderTargetView(
		m_backBuffer.get(), clearColor
	);
}