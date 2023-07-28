#include "util.h"

DWORD util::get_process_id( const std::wstring_view process_name )
{
	DWORD pid{ 0 };

	auto handle = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL );
	if ( handle == INVALID_HANDLE_VALUE )
		return pid;

	PROCESSENTRY32 pe{ };
	pe.dwSize = sizeof( PROCESSENTRY32 );

	if ( Process32First( handle, &pe ) )
	{
		do
		{
			if ( !process_name.compare( pe.szExeFile ) )
			{
				pid = pe.th32ProcessID;
				break;
			}
		}
		while ( Process32Next( handle, &pe ) );
	}

	CloseHandle( handle );
	return pid;
}

uintptr_t util::get_module_base( const std::wstring_view module_name ) 
{
	using module_t = _LDR_DATA_TABLE_ENTRY;
	using query_t = NTSTATUS( WINAPI* )( HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG );

	VALIDATE_CONSTANT( constants::handle )
		auto query_information_process = reinterpret_cast< query_t >(
			GetProcAddress( GetModuleHandle( L"ntdll.dll" ), "NtQueryInformationProcess" )
			);

	_PROCESS_BASIC_INFORMATION pbi{ };
	auto status = query_information_process(
		constants::handle,
		ProcessBasicInformation,
		&pbi,
		sizeof( pbi ),
		nullptr
	);
	if ( NT_ERROR( status ) )
		return 0x0;

	PEB peb{ };
	peb = memory::read<PEB>( ( uintptr_t )pbi.PebBaseAddress );

	auto modules = memory::read<LIST_ENTRY>( ( uintptr_t )&peb.Ldr->InMemoryOrderModuleList );
	for ( auto mod = modules; &mod != &peb.Ldr->InMemoryOrderModuleList; mod = memory::read<LIST_ENTRY>( ( uintptr_t )mod.Flink ) )
	{
		UNICODE_STRING string{ };
	#ifdef _WIN64
		string = memory::read<UNICODE_STRING>( ( uintptr_t )( mod.Flink ) + 0x48 );
	#else
		string = memory::read<UNICODE_STRING>( ( uintptr_t )( mod.Flink ) + 0x24 );
	#endif
		auto length = string.MaximumLength;
		if ( !length )
			continue;

		auto data = memory::read<wchar_t>( ( uintptr_t )string.Buffer, length );
		if ( !module_name.compare( data.data( ) ) )
		#ifdef _WIN64
			return memory::read<uintptr_t>( ( uintptr_t )( mod.Flink ) + 0x20 );
	#else
			return memory::read<uintptr_t>( ( uintptr_t )( mod.Flink ) + 0x10 );
	#endif

	}
	return 0;
}

bool util::attach( const std::wstring_view process_name )
{
	constants::pid = util::get_process_id( process_name );
	VALIDATE_CONSTANT( constants::pid );

	constants::handle = OpenProcess( PROCESS_ALL_ACCESS, FALSE, constants::pid );
	VALIDATE_CONSTANT( constants::handle );

	std::wcout << L"[+] attached to " << process_name << "\n";
	return true;
}
