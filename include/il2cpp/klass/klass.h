#pragma once

#include <cstdint>

#include <src/memory/memory.h>

class FieldInfo
{
public:
	char* name;
	void* type;
	class Il2CppClass* parent;
	int32_t offset;
	uint32_t token;
};

class Il2CppClass
{
private:
	uintptr_t m_instance{ };
	using string_t = std::vector<char>;

public:

	// getters
	uintptr_t* get_image( ) const;
	std::string get_name( ) const;
	std::string get_namespace( ) const;
	uintptr_t get_instance( ) const;
	size_t get_field_count( ) const;
	size_t get_nested_type_count( ) const;
	size_t get_field_offset( const char* field_name ) const;
	uintptr_t get_field_ptr( const char* field_name ) const;
	uintptr_t get_static_field_ptr( const char* field_name ) const;
	Il2CppClass* get_nested_type( const char* name ) const;

	operator uintptr_t( ) const
	{
		return uintptr_t( this );
	}

	template <typename T>
	T get_field( const char* field_name ) const
	{
		uintptr_t address = get_field_ptr( field_name );
		if ( !address )
			return { };

		return memory::read< T >( address );
	}

	template <typename T>
	T get_static_field( const char* field_name ) const
	{
		uintptr_t address = get_static_field_ptr( field_name );
		if ( !address )
			return { };

		return memory::read< T >( address );
	}

	// setters
	template <typename T>
	bool set_field( const char* field_name, T value ) const
	{
		uintptr_t address = get_field_ptr( field_name );
		if ( !address )
			return false;

		memory::write< T >( address, value );
		return true;
	}

	template <typename T>
	T set_static_field( const char* field_name, T value ) const
	{
		uintptr_t address = get_static_field_ptr( field_name );
		if ( !address )
			return false;

		memory::write< T >( address, value );
		return true;
	}

};

/*
class Il2CppClass
{
public:
	class Il2CppImage* image; //0x0000
	char pad_0008[ 8 ]; //0x0008
	char* name; //0x0010
	char* namespaze; //0x0018
	class Il2CppType byval_arg; //0x0020
	class Il2CppType this_arg; //0x0030
	class Il2CppClass* element_class; //0x0040
	class Il2CppClass* cast_class; //0x0048
	class Il2CppClass* declaring_type; //0x0050
	class Il2CppClass* parent; //0x0058
	class Il2CppClass* generic_class; //0x0060
	class Il2CppClass* type_definition; //0x0068
	char pad_0070[ 8 ]; //0x0070
	class Il2CppClass* klass; //0x0078
	class FieldsArray* fields; //0x0080
	char pad_0088[ 8 ]; //0x0088
	class PropertiesArray* properties; //0x0090
	class MethodInfoArray* methods; //0x0098
	class N00000500* nested_classes; //0x00A0
	char pad_00A8[ 116 ]; //0x00A8
	uint16_t method_count; //0x011C
	uint16_t property_count; //0x011E
	uint16_t field_count; //0x0120
	uint16_t event_count; //0x0122
	uint16_t nested_type_count; //0x0124
	uint16_t vtable_count; //0x0126
}; //Size: 0x0128
*/




