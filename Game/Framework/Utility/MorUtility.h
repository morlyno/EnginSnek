#pragma once

namespace Mor::Utility
{

	template<class Container>
	void erase_by_index( Container& con,size_t index )
	{
		con.erase( con.begin() + index );
	}

	template<class iter>
	void wrap_iterator( const iter begin,const iter end,iter& it )
	{
		if ( it == end )
		{
			it = begin;
		}
	}

	template<typename Ty>
	std::unique_ptr<Ty> Unique_Ptr_Copy( std::unique_ptr<Ty>& src )
	{
		auto&& ref = *src.get();
		return std::make_unique<Ty>( ref );
	}

}