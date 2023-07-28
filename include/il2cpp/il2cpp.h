#pragma once

#include <unordered_map>
#include <vector>

#include <src/memory/memory.h>
#include <src/util/util.h>

#include "klass/klass.h"

struct Il2CppImage;
struct Il2CppAssemblyName
{
public:
	char* name;
};

struct Il2CppAssembly
{
public:
	Il2CppImage* image; 
	uint32_t token; 
	int32_t referenced_assembly_start; 
	int32_t referenced_assembly_count; 
	char buffer[ 4 ];
	Il2CppAssemblyName assembly_name; 
};

struct Il2CppImage
{
public:
	char* extension_name;
	char* name;
	Il2CppAssembly* assembly;
	int32_t class_count;
};

namespace il2cpp
{
	struct image_data;
	using classes_t = std::vector<Il2CppClass*>;
	using images_t = std::vector<image_data>;

	struct image_data
	{
		std::string name;
		int32_t class_count{ };
		classes_t classes{ };
	};
	images_t images{ };
	uintptr_t classes = 0x3126930; // GetTypefromTypeDefinitionIndex last function call (change to signature scanning)
	uintptr_t assemblies = 0x3126650; // il2cpp_domain_get_assemblines -> first func -> lea rax, imm/64
	bool initalized{ };

	Il2CppClass* find_class( const char* image_name, const char* class_name );
	bool init( );
}

Il2CppClass* il2cpp::find_class( const char* image_name, const char* class_name )
{
	for ( const auto& image : images )
	{
		if ( _stricmp( image.name.c_str( ), image_name ) != 0 )
			continue;

		for ( const auto& klass : image.classes )
		{
			if ( !_stricmp( klass->get_name( ).c_str( ), class_name ) )
				return klass;
		}
	}
	return nullptr;
}

// Must be called before il2cpp::find_class or it will fail
bool il2cpp::init( )
{
	// Il2CPP logic is stored in GameAssembly.dll
	const auto game_assembly = util::get_module_base( L"GameAssembly.dll" );

	// We need to fetch the Il2CppClass and Il2CppAssembly tables
	const auto classes = memory::read<uintptr_t>( game_assembly + il2cpp::classes );
	const auto assemblies = memory::read<uintptr_t>( game_assembly + il2cpp::assemblies ); // il2cpp_domain_get_assemblines -> first func -> lea rax, imm/64

	size_t offset{ };
	int count = memory::read<int>( memory::resolve( assemblies, { 0x10 } ) );
	for ( int i = 0; i < count; ++i )
	{
		il2cpp::image_data data{ };

		// Image is stored inside of the assembly
		const auto assembly = memory::read<Il2CppAssembly>( memory::resolve( assemblies + ( i * 0x8 ), { 0x0 } ) );
		const auto image = memory::read<Il2CppImage>( uintptr_t( assembly.image ) );

		for ( int j = 0; j < image.class_count; ++j )
		{
			// We have to do pointer math (so index by 0x8) and we offset by the amount of classes we've already traversed in past images
			auto klass = memory::read<Il2CppClass*>( classes + offset + ( j * 0x8 ) );

			// Only add to the list if the class exists (obviously)...
			if ( klass )
				data.classes.push_back( klass );

		}
		data.name = memory::read_string<std::string>( uintptr_t( assembly.assembly_name.name ), 255 );
		data.class_count = image.class_count;
		il2cpp::images.push_back( data );

		// Don't want to traverse the same list of classes again
		offset += image.class_count;
	}

	// I can't really check if anything has gone wrong (and much really can) so let's just check if no images were parsed
	initalized = il2cpp::images.size( ) > 0;
	return initalized;
}

