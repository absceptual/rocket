#pragma once

#include <include/il2cpp/il2cpp.h>
#include "natives.h"

class EntityRealm : Il2CppClass
{
public:
	static uintptr_t GetEntity( const size_t index )
	{
		static auto base_networkable = il2cpp::find_class( "Assembly-CSharp", "BaseNetworkable" );
		static auto client_entities = base_networkable->get_static_field<uintptr_t>( "clientEntities" );
		static auto entitylist = memory::read<ListDictionary>(
			memory::resolve( client_entities + 0x10, {0x0 } )
		);

		return entitylist.value( index );
	}

	static int32_t GetEntityCount(  )
	{
		static auto base_networkable = il2cpp::find_class( "Assembly-CSharp", "BaseNetworkable" );
		static auto client_entities = base_networkable->get_static_field<uintptr_t>( "clientEntities" );
		static auto entitylist = memory::read<ListDictionary>(
			memory::resolve( client_entities + 0x10, { 0x0 } )
		);

		return entitylist.value_count( );
	}
};




























/*#pragma once
#include <cassert>
#include <cstdint>

#include <src/sdk/constants.h>
#include <src/util/util.h>


class CClientEntityList
{
private:
	struct EntityListEntry
	{
		uintptr_t entity;
		int32_t id;
		EntityListEntry* blink;
		EntityListEntry* flink;
	};

public:
	CClientEntityList() = default;

	template <typename T = uintptr_t>
	static T GetEntity(size_t idx)
	{
		assert(idx >= 0 && "CClientEntityList::GetEntity(size_t) called with a negative index");

		static auto entitylist = util::get_module_base(L"client.dll") + offsets::entitylist;

		auto entity = memory::read<T>(entitylist + (idx * sizeof(EntityListEntry)));
		return entity;
	}
	
};*/