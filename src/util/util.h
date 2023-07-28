#pragma once

#include <cstdlib>
#include <cstdint>
#include <string_view>
#include <iostream>
#include <type_traits>

#include <Windows.h>
#include <TlHelp32.h>

#include <include/ntdll.h>
#include <src/sdk/constants.h>
#include <src/memory/memory.h>

#define VALIDATE_CONSTANT(expr) if (!expr) { std::cerr << "[!] failed to evaluate constant at line " << __LINE__ << '\n'; std::cout << "[!] press enter to exit... "; std::cin.get(); std::exit(-1); }
		
namespace util
{
	DWORD get_process_id( const std::wstring_view process_name );
	uintptr_t get_module_base( const std::wstring_view module_name );
	bool attach( const std::wstring_view process_name );
}
