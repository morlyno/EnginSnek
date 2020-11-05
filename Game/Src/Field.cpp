#include "Field.h"
#include "../Framework/Utility/MorMath.h"

Field::Field( Graphics& gfx,float fieldtopleftX,float fieldtopleftY,unsigned int width,unsigned int height ) noexcept
	:
	width( width ),
	height( height ),
	TopLeftX( fieldtopleftX ),
	TopLeftY( fieldtopleftY )
{
	for ( unsigned int x = 0; x <= width; ++x )
	{
		Cells.push_back( std::make_unique<Line>( gfx,(int)Cells.size(),(float)x,0.0f,(float)width,Mor::Math::PIOver2 ) );
	}
	for ( unsigned int y = 0; y <= height; ++y )
	{
		Cells.push_back( std::make_unique<Line>( gfx,(int)Cells.size(),0.0f,(float)y,(float)height,0.0f ) );
	}
	SetTransformXM( DirectX::XMMatrixTranslation( -0.5f,-0.5f,0.0f ) );
}

void Field::Draw( Graphics& gfx ) const noexcept(!IS_DEBUG)
{
	for ( auto& c : Cells )
	{
		c->Draw( gfx );
	}
}

void Field::SetTransformXM( DirectX::FXMMATRIX matrix ) noexcept
{
	for ( auto& c : Cells )
	{
		c->SetParentTransform( matrix );
	}
}
