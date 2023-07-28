#include "klass.h"

uintptr_t* Il2CppClass::get_image( ) const
{
	auto image = memory::read<uintptr_t*>( uintptr_t( this ) ); // 0x0
	return image;
}

std::string Il2CppClass::get_name( ) const
{
	auto name = memory::read_string<std::string>( memory::read<uintptr_t>( uintptr_t( this ) + 0x10 ), 255 ); 
	return name;
}

std::string Il2CppClass::get_namespace( ) const
{
	auto namespaze = memory::read_string < std::string >( memory::read<uintptr_t>( uintptr_t( this ) + 0x18 ), 255 ); 
	return namespaze;
}

uintptr_t Il2CppClass::get_instance( ) const
{
	return uintptr_t( this );
}

size_t Il2CppClass::get_field_count( ) const
{
	return memory::read<uint16_t>( uintptr_t( this ) + 0x120 );
}

size_t Il2CppClass::get_nested_type_count( ) const
{
	return memory::read<uint16_t>( uintptr_t( this ) + 0x124 );
}

size_t Il2CppClass::get_field_offset( const char* field_name ) const
{
	for ( int i = 0; i < get_field_count( ); ++i )
	{
		// Index into the class fields array
		auto field = memory::read<FieldInfo>(
			memory::resolve( uintptr_t( this ) + 0x80, { i * sizeof( FieldInfo ) } )
		);

		auto name = memory::read_string<std::string>( uintptr_t( field.name ), 255 );
		if ( !_stricmp( name.c_str( ), field_name ) )
			return field.offset;
	}
	return -1;
}

uintptr_t Il2CppClass::get_field_ptr( const char* field_name ) const
{
	size_t offset = get_field_offset( field_name );
	if ( !offset )
		return 0x0;

	return uintptr_t( this ) + offset;
}

uintptr_t Il2CppClass::get_static_field_ptr( const char* field_name ) const
{
	size_t offset = get_field_offset( field_name );
	if ( offset == -1 )
		return 0x0;

	return memory::resolve( uintptr_t( this ) + 0xB8, { offset } );
}

Il2CppClass* Il2CppClass::get_nested_type( const char* klass_name ) const
{
	for ( int i = 0; i < get_nested_type_count( ); ++i )
	{
		auto type = memory::read<Il2CppClass*>( memory::read<uintptr_t>( uintptr_t( this ) + 0xA0 ) + ( i * 0x8 ) );
		auto name = type->get_name( );

		if ( !_stricmp( name.c_str( ), klass_name ) )
			return type;
	}
	return nullptr;
}

