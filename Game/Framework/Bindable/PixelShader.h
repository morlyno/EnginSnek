#pragma once

#include "Bindable.h"
#include "../ErrorHandle/Macros/GraphicsThrowMacros.h"
#include <memory>

namespace Bind
{

	class PixelShader : public Bindable
	{
	public:
		PixelShader( Graphics& gfx,const std::string& path );
		void Bind( Graphics& gfx ) noexcept override;
		static std::shared_ptr<PixelShader> Resolve( Graphics& gfx,const std::string& path ) noexcept;
		static std::string GenerateKey( const std::string& path ) noexcept;
		std::string GetKey() const noexcept override;
	private:
		Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
		std::string path;
	};

}