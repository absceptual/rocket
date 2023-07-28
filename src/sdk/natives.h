#pragma once

#include <cstdint>
#include <src/memory/memory.h>



struct String
{
	char padding[ 0x10 ];
	int32_t length;
	wchar_t buffer[255]; // could be higher than 255 in practice
};

class Phrase
{
public:
	String token( )
	{
		return memory::read<String>(
			memory::read<uintptr_t>( uintptr_t( this ) + 0x10 )
		);
	}

	String text( )
	{
		return memory::read<String>( 
			memory::read<uintptr_t>( uintptr_t( this ) + 0x18 )
		);
	}

};

class List
{
public:
	uintptr_t get( const size_t index ) const
	{
		return memory::read<uintptr_t>(
			memory::read<uintptr_t>( ( uintptr_t( this ) + 0x10 ) ) + 0x20 + ( index * 0x8 )
		);
	}

	int32_t count( ) const
	{
		return memory::read<int32_t>( uintptr_t( this ) + 0x18 );
	}
};

class BufferList
{
private:
	uintptr_t m_instance{ };

public:
	uintptr_t get( const size_t index ) const
	{
		return memory::read<uintptr_t>(
			memory::read<uintptr_t>( ( uintptr_t( this ) + 0x18 )  ) + 0x20 + ( index * 0x8 )
		);
	}

	int32_t count( ) const
	{
		return memory::read<int32_t>( uintptr_t( this ) + 0x10 );
	}
};

class ListDictionary
{
private:
	char padding[ 0x20 ];
	BufferList* keys;
	BufferList* values;

public:
	uintptr_t key( const size_t index ) const
	{
		return keys->get( index );
	}

	size_t key_count( ) const
	{
		return keys->count( );
	}

	uintptr_t value( const size_t index ) const
	{
		return values->get(index);
	}

	int32_t value_count( ) const
	{
		return values->count( );
	}

};