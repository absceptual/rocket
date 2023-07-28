#pragma once

#include <include/il2cpp/il2cpp.h>
#include "natives.h"

class Item
{
	class Definition
	{
	public:
		String shortname( )
		{
			static auto klass = il2cpp::find_class( "Assembly-CSharp", "ItemDefinition" );
			static auto offset = klass->get_field_offset( "shortname" );
			return memory::read<String>(
				memory::read<uintptr_t>( uintptr_t( this ) + offset )
			);

		}

		Phrase* name( )
		{
			static auto klass = il2cpp::find_class( "Assembly-CSharp", "ItemDefinition" );
			static auto offset = klass->get_field_offset( "displayName" );
			return reinterpret_cast< Phrase* >(
				memory::read<uintptr_t>( uintptr_t( this ) + offset )
			);

		}

		Phrase* description( )
		{
			static auto klass = il2cpp::find_class( "Assembly-CSharp", "ItemDefinition" );
			static auto offset = klass->get_field_offset( "displayDescription" );
			return reinterpret_cast< Phrase* >(
				memory::read<uintptr_t>( uintptr_t( this ) + offset )
			);
		}
	};

public:

	Definition* definition( )
	{
		static auto klass = il2cpp::find_class( "Assembly-CSharp", "Item" );
		static auto offset = klass->get_field_offset( "info" );
		return reinterpret_cast< Definition*>(
			memory::read<uintptr_t>( uintptr_t( this ) + offset )
		);
	}

	uint64_t id( )
	{
		static auto klass = il2cpp::find_class( "Assembly-CSharp", "Item" );
		static auto offset = klass->get_field_offset( "uid" );
		return memory::read<uint64_t>( uintptr_t( this ) + offset );
	}

	String shortname( )
	{
		return definition( )->shortname( );
	}

	String name( )
	{
		return definition( )->name( )->text( );
	}

	String description( )
	{
		return definition( )->description( )->text( );
	}

public:
};



class ItemContainer
{
public:
	int capacity( )
	{
		static auto klass = il2cpp::find_class( "Assembly-CSharp", "ItemContainer" );
		static auto offset = klass->get_field_offset( "capacity" );

		return memory::read<int>( uintptr_t( this ) + offset );
	}

	List* item_list( ) const
	{
		static auto klass = il2cpp::find_class( "Assembly-CSharp", "ItemContainer" );
		static auto offset = klass->get_field_offset( "itemList" );

		return reinterpret_cast< List* >( 
			memory::read<uintptr_t>( uintptr_t( this ) + offset )
		);
	}

	Item* item( const size_t index )
	{
		const auto items = item_list( );
		return reinterpret_cast< Item* >( items->get( index ) );
	}
};
class PlayerInventory
{
public:
	ItemContainer* belt( )
	{
		static auto klass = il2cpp::find_class( "Assembly-CSharp", "PlayerInventory" );
		static auto offset = klass->get_field_offset( "containerBelt" );

		return reinterpret_cast<ItemContainer*>(
			memory::read<uintptr_t>( uintptr_t( this ) + offset )
		);
	}

	ItemContainer* main( )
	{
		static auto klass = il2cpp::find_class( "Assembly-CSharp", "PlayerInventory" );
		static auto offset = klass->get_field_offset( "containerMain" );

		return reinterpret_cast< ItemContainer* >( 
			memory::read<ItemContainer*>( uintptr_t( this ) + offset )
		);
	}
	
	ItemContainer* wear( )
	{
		static auto klass = il2cpp::find_class( "Assembly-CSharp", "PlayerInventory" );
		static auto offset = klass->get_field_offset( "containerWear" );

		return reinterpret_cast< ItemContainer* >( 
			memory::read<ItemContainer*>( uintptr_t( this ) + offset )
		);
	}
};

class BaseEntity;
class EntityRef : Il2CppClass
{
public:
	BaseEntity* ent( ) const
	{
		static auto klass = il2cpp::find_class( "Assembly-CSharp", "EntityRef" );
		return memory::read<BaseEntity*>(
			memory::resolve( uintptr_t( this ) + klass->get_field_offset( "ent_cached" ), { 0x0 } )
		);
	}
};

class BaseNetworkable : Il2CppClass
{
public:
	String raw_prefab_name( ) const
	{
		static auto klass = il2cpp::find_class( "Assembly-CSharp", "BaseNetworkable" );
		static auto offset = klass->get_field_offset( "_prefabName" );
		return memory::read<String>( 
			memory::resolve( uintptr_t( this ) + offset, {0x0 }  )
		);
	}

	String prefab_name( ) const
	{
		static auto klass = il2cpp::find_class( "Assembly-CSharp", "BaseNetworkable" );
		static auto offset = klass->get_field_offset( "_prefabNameWithoutExtension" );
		return memory::read<String>(
			memory::resolve( uintptr_t( this ) + offset, { 0x0 } )
		);
	}

	uint32_t prefab_id( ) const
	{
		static auto klass = il2cpp::find_class( "Assembly-CSharp", "BaseNetworkable" );
		static auto offset = klass->get_field_offset( "prefabID" );
		return memory::read<uint32_t>(
			uintptr_t( this ) + offset
		);
	}

	List* children( ) const
	{
		static auto klass = il2cpp::find_class( "Assembly-CSharp", "BaseNetworkable" );
		static auto offset = klass->get_field_offset( "children" );
		return memory::read<List*>(
			uintptr_t( this ) + offset
		);
	}
};

class BaseEntity : BaseNetworkable
{
public:
	uintptr_t model( ) const
	{
		return 0x0; //implement
	}

	uint64_t skin_id( ) const
	{
		static auto klass = il2cpp::find_class( "Assembly-CSharp", "BaseEntity" );
		static auto offset = klass->get_field_offset( "skinID" );
		memory::read<uint64_t>( uintptr_t( this ) + offset );
	}

	uint64_t name( ) const
	{
		static auto klass = il2cpp::find_class( "Assembly-CSharp", "BaseEntity" );
		static auto offset = klass->get_field_offset( "_name" );
		memory::read<uint64_t>( uintptr_t( this ) + offset );
	}
};

class BaseCombatEntity : BaseEntity
{
public:
	enum Lifestate
	{
		Alive = 0,
		Dead = 1,

		MAX
	};

	float start_health( ) const
	{
		static auto klass = il2cpp::find_class( "Assembly-CSharp", "BaseCombatEntity" );
		static auto offset = klass->get_field_offset( "startHealth" );
		memory::read<uint64_t>( uintptr_t( this ) + offset );
	}

	float health( ) const
	{
		static auto klass = il2cpp::find_class( "Assembly-CSharp", "BaseCombatEntity" );
		static auto offset = klass->get_field_offset( "_health" );
		memory::read<uint64_t>( uintptr_t( this ) + offset );
	}

	float max_health( ) const
	{
		static auto klass = il2cpp::find_class( "Assembly-CSharp", "BaseCombatEntity" );
		static auto offset = klass->get_field_offset( "_maxHealth" );
		memory::read<uint64_t>( uintptr_t( this ) + offset );
	}
};

class BasePlayer : BaseCombatEntity
{
public:
	uint64_t held_item_id( )
	{
		static auto klass = il2cpp::find_class( "Assembly-CSharp", "BasePlayer" );
		static auto offset = klass->get_field_offset( "clActiveItem" );
		return memory::read<uint64_t>(
			uintptr_t( this ) + offset
		);
	}

	uint64_t team( )
	{
		static auto klass = il2cpp::find_class( "Assembly-CSharp", "BasePlayer" );
		static auto offset = klass->get_field_offset( "currentTeam" );
		return memory::read<uint64_t>(
			uintptr_t( this ) + offset
		);
	}

	String display_name( )
	{
		static auto klass = il2cpp::find_class( "Assembly-CSharp", "BasePlayer" );
		static auto offset = klass->get_field_offset( "_displayName" );

		return memory::read<String>(
			memory::resolve( EntityRealm::GetEntity( 0 ) + offset, { 0x0 } )
		);
	}

	uint64_t user_id( )
	{
		static auto klass = il2cpp::find_class( "Assembly-CSharp", "BasePlayer" );
		static auto offset = klass->get_field_offset( "userID" );

		return memory::read<uint64_t>(
			uintptr_t( this ) + offset
		);
	}

	PlayerInventory* inventory( )
	{
		static auto klass = il2cpp::find_class( "Assembly-CSharp", "BasePlayer" );
		static auto offset = klass->get_field_offset( "inventory" );

		return reinterpret_cast<PlayerInventory*>(
			memory::read<uintptr_t>(uintptr_t( this ) + offset)
		);
	}

	static BasePlayer* GetLocalPlayer( )
	{
		if ( !il2cpp::initalized )
			return nullptr;

		return reinterpret_cast< BasePlayer* >( EntityRealm::GetEntity( 0 ) );
	}
};