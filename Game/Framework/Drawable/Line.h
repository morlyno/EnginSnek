#pragma once

#include "Drawable.h"

class Line : public Drawable
{
public:
	Line( Graphics& gfx,int index,float x0,float y0,float length,float angle );
	void Update( float dt ) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
	DirectX::XMFLOAT4 GetColorXM() const noexcept override;
	std::string GetType() const noexcept override;
	void SetParentTransform( DirectX::FXMMATRIX matrix ) noexcept;
private:
	float x0;
	float y0;
	float length;
	float angle;
	int index;
	DirectX::XMMATRIX parentTransform = DirectX::XMMatrixIdentity();
};