#pragma once
#include <vector>
#include <cstdint>
#include <iostream>
#include <type_traits>

#include <Windows.h>
#include <Psapi.h>

#include <src/sdk/constants.h>

namespace memory
{
	template <typename T>
	using strip_attributes = typename std::remove_cv_t<std::remove_pointer_t<T>>;
	
	template <typename T>
	/*strip_attributes<T>*/ T read(uintptr_t address)
	{
		using type = strip_attributes<T>;
		if (constants::handle == INVALID_HANDLE_VALUE)
			return {};

		T buffer{ };
		ReadProcessMemory(
			constants::handle,
			reinterpret_cast<const void*>(address),
			&buffer,
			sizeof(type),
			nullptr
		);

		return buffer;
	}

	// Meant to be used to read arbituary arrays and/or strings
	template <typename T>
	std::vector<strip_attributes<T>> read(uintptr_t address, size_t N)
	{
		if (constants::handle == INVALID_HANDLE_VALUE)
			return { };

		std::vector<strip_attributes<T>> buffer{ };
		buffer.reserve(N);

		ReadProcessMemory(
			constants::handle,
			reinterpret_cast<void*>(address),
			buffer.data(),
			N,
			nullptr
		);

		return buffer;
	}

	template <typename T>
	T read_string( uintptr_t address, size_t N )
	{
		if ( constants::handle == INVALID_HANDLE_VALUE )
			return { };

		T buffer{ };
		buffer.reserve( N );

		ReadProcessMemory(
			constants::handle,
			reinterpret_cast< void* >( address ),
			buffer.data( ),
			N,
			nullptr
		);

		return buffer;
	}
	
	template <typename type>
	bool write(uintptr_t address, type data)
	{
		return WriteProcessMemory(
			constants::handle,
			reinterpret_cast<void*>(address),
			&data,
			sizeof(type),
			nullptr
		);
	}

	uintptr_t resolve( uintptr_t address, std::vector<size_t> offsets );
}


