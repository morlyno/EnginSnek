#pragma once
#include "MorWin.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <wrl.h>
#include "ErrorHandle/MorExeption.h"
#include "ErrorHandle/DxgiInfoManager.h"
#include <vector>

class Graphics
{
	friend class Bindable;
public:
	class Exception : public MorException
	{
		using MorException::MorException;
	};
	class HrException : public Exception
	{
	public:
		HrException( int line,const char* file,HRESULT hr,std::vector<std::string> infoMsg = {} ) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		std::string GetErrorDesciption() const noexcept;
		static std::string TranslateErrorCode( HRESULT hr ) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorInfo() const noexcept;
	private:
		HRESULT hr;
		std::string info;
	};
	class DeviceRemovedException : public HrException
	{
		using HrException::HrException;
	public:
		const char* GetType() const noexcept override;
	};
	class InfoException : public Exception
	{
	public:
		InfoException( int line,const char* file,std::vector<std::string> infoMsg ) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		std::string GetErrorInfo() const noexcept;
	private:
		std::string info;
	};
public:
	Graphics( UINT width,UINT height,HWND hWnd );
	Graphics( const Graphics& ) = delete;
	Graphics operator=( const Graphics ) = delete;
	~Graphics();
	void EndFrame();
	void ClearBuffer( float red,float green,float blue ) noexcept;
	void DrawIndexed( UINT indexcount ) noexcept( !IS_DEBUG );
	void SetProjection( const DirectX::XMMATRIX& proj ) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;
	void SetCamera( DirectX::CXMMATRIX cam ) noexcept;
	DirectX::XMMATRIX GetCamera() const noexcept;
private:
#ifdef DEBUG
	DxgiInfoManager infoManager;
#endif
	Microsoft::WRL::ComPtr<ID3D11Device>			pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain>			pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>		pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	pRenderTargetView;
	UINT											WindowWidth;
	UINT											WindowHeight;
	HWND											hWnd;
	DirectX::XMMATRIX								projection;
	DirectX::XMMATRIX								camera;
};