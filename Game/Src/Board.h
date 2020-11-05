#pragma once
#include "Field.h"
#include "Vec2.h"
#include "../Framework/Drawable/Tile.h"
#include <random>
#include <functional>

class Board
{
public:
	Board( Graphics& gfx,const Vec2& topleft,const Vei2& size,std::mt19937 rng )
		:
		gfx( gfx ),
		field( gfx,topleft.x,topleft.y,size.x,size.y ),
		Frute_pos( 5,5 ),
		Frute_mesh( gfx,(float)Frute_pos.x,(float)Frute_pos.y,0 ),
		size( size ),
		DistX( 0,size.x - 1 ),
		DistY( 0,size.y - 1 ),
		r( rng )
	{}
	void Draw()
	{
		field.Draw( gfx );
		Frute_mesh.Draw( gfx );
	}
	bool CheckForEaten( const Vei2& pos ) noexcept
	{
		if ( Frute_pos == pos )
		{
			SetFrute( { DistX( r ),DistY( r ) } );
			return true;
		}
		return false;
	}
	Vei2 GetSize() const noexcept
	{
		return size;
	}
private:
	void SetFrute( const Vei2& pos ) noexcept
	{
		Frute_pos = pos;
		Frute_mesh.SetPos( (float)pos.x,(float)pos.y );
	}
private:
	Graphics& gfx;
	Field field;
	Vei2 Frute_pos;
	Tile Frute_mesh;
	Vei2 size;
	std::uniform_int_distribution<int> DistX;
	std::uniform_int_distribution<int> DistY;
	std::mt19937 r;
};