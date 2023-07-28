/*
#pragma once

#include <src/sdk/entitylist.h>
#include <src/sdk/constants.h>
#include <src/sdk/vector.h>

#define MAX_PLAYER_NAME 32

class CSPlayer
{
public:
	CSPlayer( ) = default;

	static CSPlayer* GetLocalPlayer( )
	{
		auto player = memory::read<CSPlayer*>( util::get_module_base( L"client.dll" ) + offsets::localplayer );
		// auto p = memory::read<CSPlayer*>( util::get_module_base( L"client.dll" ) + offsets::localplayer );
		return player;
	}

	operator uintptr_t() const
	{
		return reinterpret_cast< uintptr_t >( this );
	}

	int health( ) const
	{
		return memory::read<int>( uintptr_t( this ) + offsets::health );
	}

	Vector3 position( ) const
	{
		return memory::read<Vector3>( uintptr_t( this ) + offsets::position );
	}

	int team( ) const
	{
		return memory::read<int>( uintptr_t( this ) + offsets::team );
	}

	bool dormant( ) const
	{
		return memory::read<bool>( uintptr_t( this ) + offsets::dormant );
	}
	bool alive( ) const
	{
		return memory::read<int>( uintptr_t( this ) + offsets::lifestate );
	}

	bool is_valid( ) const
	{
		if ( !this )
			return false;

		if ( !!alive( ) )
			return false;

		if ( dormant( ) )
			return false;

		int team = this->team( );
		if ( team != 2 && team != 3 )
			return false;

		return true;
	}


	Vector3 get_bone( size_t idx ) const
	{
		const uintptr_t bones = memory::read<uintptr_t>( uintptr_t( this ) + offsets::bonematrix );

		return Vector3(
			memory::read<float>( bones + 0x30 * 8 + 0xC ),
			memory::read<float>( bones + 0x30 * 8 + 0x1C ),
			memory::read<float>( bones + 0x30 * 8 + 0x2C )
		);
	}
};

class CClientState
{
public:
	struct player_info_t
	{
	public:
		char pad_0000[ 16 ];
		char name[ 32 ];
		char pad_0030[ 100 ];
		char steam_id[ 20 ];
		char pad_00A8[ 16 ];
		int32_t id;
	};

public:
	CClientState( ) = default;

	static uintptr_t Get( )
	{
		static auto clientstate = memory::read<uintptr_t>( util::get_module_base( L"engine.dll" ) + offsets::clientstate );
		return clientstate;
	}

	static int GetMaxPlayers( )
	{
		static auto clientstate = CClientState::Get( );

		return memory::read<int>( clientstate + offsets::max_players );
	}

	static player_info_t GetPlayerInfo( size_t idx )
	{
		assert( idx >= 0 && "CClientState::GetPlayerInfo called with negative index" );

		static uintptr_t clientstate = CClientState::Get( );

		uintptr_t playerinfo = memory::read<uintptr_t>( clientstate + offsets::playerinfo );
		playerinfo = memory::read<uintptr_t>( playerinfo + 0x40 );
		playerinfo = memory::read<uintptr_t>( playerinfo + 0xC );
		playerinfo = memory::read<uintptr_t>( ( playerinfo + 0x28 ) + ( idx * 0x34 ) );

		return memory::read<player_info_t>( playerinfo );
	}

	static Vector3 GetViewAngles( )
	{
		static auto clientstate = CClientState::Get( );

		return memory::read<Vector3>( clientstate + offsets::angles );
	}
};
*/