#include "memory.h"

uintptr_t memory::resolve( uintptr_t address, std::vector<size_t> offsets )
{
	for ( size_t i = 0; i < offsets.size( ); ++i )
	{
		address = read<uintptr_t>( address );
		address += offsets[ i ];
		

	}
	return address;
}

