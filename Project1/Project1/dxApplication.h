#pragma once
#include "../windowApplication.h"
#include "dxDevice.h"

using namespace mini;

class DxApplication : public WindowApplication {
public:
	explicit DxApplication(HINSTANCE hInstance);
protected:
	int MainLoop() override;
private:
	void Render();
	void Update();

	DxDevice m_device;
	dx_ptr<ID3D11RenderTargetView> m_backBuffer;
};