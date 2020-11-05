#pragma once

#include "../Framework/Graphics.h"
#include "../Framework/Drawable/Line.h"

class Field
{
public:
	Field( Graphics& gfx,float fieldtopleftX,float fieldtopleftY,unsigned int width,unsigned int height ) noexcept;
	void Draw( Graphics& gfx ) const noexcept(!IS_DEBUG);
	void SetTransformXM( DirectX::FXMMATRIX matrix ) noexcept;
private:
	const unsigned int width;
	const unsigned int height;
	const float TopLeftX;
	const float TopLeftY;
	std::vector<std::unique_ptr<Line>> Cells;
};