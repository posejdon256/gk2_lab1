#include "dxStructures.h"

SwapChainDescription::SwapChainDescription(HWND wndHwnd, SIZE wndSize)
{
	ZeroMemory(this, sizeof(SwapChainDescription));
	BufferDesc.Width = wndSize.cx;
	BufferDesc.Height = wndSize.cy;
	BufferDesc.RefreshRate.Numerator = 120;
	BufferDesc.RefreshRate.Denominator = 1;
	BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; //0
	//BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; //0
	SampleDesc.Quality = 0;
	SampleDesc.Count = 1;
	BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	BufferCount = 1;
	OutputWindow = wndHwnd;
	Windowed = true;
	//SwapEffect = DXGI_SWAP_EFFECT_DISCARD; //0
	//Flags = 0;
}

Viewport::Viewport(SIZE size)
{
	this->TopLeftX = 0.0f;
	this->TopLeftY = 0.0f;
	this->Width = static_cast<FLOAT>(size.cx);
	this->Height = static_cast<FLOAT>(size.cy);
	this->MinDepth = 0.0f;
	this->MaxDepth = 1.0f;
}

Texture2DDescription::Texture2DDescription(UINT width, UINT height)
{
	ZeroMemory(this, sizeof(Texture2DDescription));
	Width = width;
	Height = height;
	//MipLevels = 0;
	ArraySize = 1;
	Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SampleDesc.Count = 1;
	SampleDesc.Quality = 0;
	Usage = D3D11_USAGE_DEFAULT;
	BindFlags = D3D11_BIND_SHADER_RESOURCE;
	//CPUAccessFlags = 0;
	//MiscFlags = 0;
}

BufferDescription::BufferDescription(UINT bindFlags, size_t byteWidth)
{
	ZeroMemory(this, sizeof(BufferDescription));
	BindFlags = bindFlags;
	ByteWidth = byteWidth;
	Usage = D3D11_USAGE_DEFAULT;
	//CPUAccessFlags = 0;
	//MiscFlags = 0;
	//StructureByteStride = 0;
}
Texture2DDescription
Texture2DDescription::DepthStencilDescription(UINT width,
	UINT height) {
	Texture2DDescription desc(width, height);
	desc.MipLevels = 1;
	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	return desc;
}
BufferDescription
BufferDescription::VertexBufferDescription(size_t byteWidth) {
	return { D3D11_BIND_VERTEX_BUFFER, byteWidth };
}