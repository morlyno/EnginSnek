#pragma once
#include "Vec2.h"
#include "../Framework/Graphics.h"
#include "../Framework/Drawable/Tile.h"
#include "../Framework/ImGui/imgui.h"
#include "Board.h"

class Snek
{
private:
	class Segment
	{
	public:
		Segment( const Vei2& pos,Graphics& gfx )
			:
			pos( pos ),
			mesh( std::make_unique<Tile>( gfx,0.0f,0.0f,0 ) )
		{}
		void Follow( const Segment& next ) noexcept
		{
			pos = next.pos;
		}
		void MoveTo( const Vei2& nextpos ) noexcept
		{
			pos = nextpos;
		}
		void Draw( Graphics& gfx )
		{
			mesh->SetPos( (float)pos.x,(float)pos.y );
			mesh->Draw( gfx );
		}
		Vei2 GetPos() const noexcept
		{
			return pos;
		}
	private:
		Vei2 pos;
		std::unique_ptr<Tile> mesh;
	};
public:
	Snek( const Vei2& pos,Graphics& gfx )
		:
		gfx( gfx )
	{
		AddSegment( pos );
	}
	bool Move( Board& brd ) noexcept
	{
		for ( size_t i = segs.size() - 1u; i > 0u; --i )
		{
			segs[i].Follow( segs[i - 1u] );
		}
		return MoveHeadAndValidatePosition( dir,brd );
	}
	void SetDir( const Vei2& dir ) noexcept
	{
		this->dir = dir;
	}
	void Draw()
	{
		for ( auto& s : segs )
		{
			s.Draw( gfx );
		}
	}
	void CheckForFrute( Board& brd )
	{
		if ( brd.CheckForEaten( segs.front().GetPos() ) )
		{
			Grow();
		}
	}
	void Reset()
	{
		segs.clear();
		AddSegment( { 2,2 } );
		dir = { 0,0 };
		isFucked = false;
	}
private:
	void Grow()
	{
		AddSegment( segs.back().GetPos() );
	}
	void AddSegment( const Vei2& pos )
	{
		segs.emplace_back( pos,gfx );
	}
	bool MoveHeadAndValidatePosition( const Vei2& dir,const Board& brd ) noexcept
	{
		const auto nextpos = segs.front().GetPos() + dir;
		for ( int i = 1; i < segs.size(); ++i )
		{
			if ( segs[i].GetPos() == nextpos )
			{
				isFucked = true;
				return false;
			}
		}
		if ( !InBounce( nextpos,brd ) )
		{
			isFucked = true;
			return false;
		}
		segs.front().MoveTo( nextpos );
		return true;
	}
	bool InBounce( const Vei2& nextpos,const Board& brd ) const noexcept
	{
		return nextpos.x < brd.GetSize().x&& nextpos.y < brd.GetSize().y&& nextpos.x >= 0 && nextpos.y >= 0;
	}
private:
	Graphics& gfx;
	std::vector<Segment> segs;
	Vei2 dir = { 0,0 };
	bool isFucked = false;
};
