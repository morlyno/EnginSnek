#pragma once

#include "Bindable.h"
#include "../ErrorHandle/Macros/GraphicsThrowMacros.h"

namespace Bind
{

	class IndexBuffer : public Bindable
	{
	public:
		IndexBuffer( Graphics& gfx,std::vector<unsigned short> indices );
		void Bind( Graphics& gfx ) noexcept override;
		UINT GetCount() const;
	private:
		const UINT count;
		Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
	};

}