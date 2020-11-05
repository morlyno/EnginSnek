#pragma once

#include "Drawable.h"

class Tile : public Drawable
{
public:
	Tile( Graphics& gfx,float x,float y,int index );
	void Update( float dt ) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
	DirectX::XMFLOAT4 GetColorXM() const noexcept override;
	bool SpawnControlWindow() noexcept override;
	std::string GetType() const noexcept override;
	void SetPos( float x,float y ) noexcept;
private:
	float x;
	float y;
	float width = 1.0f;
	float height = 1.0f;
	int index;
};