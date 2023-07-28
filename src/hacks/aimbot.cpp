#include "aimbot.h"


void aimbot::Run( )
{
	/*
	float cdist = INT_MAX;
	int cplayer{ };

	for ( int i = 1; i < CClientState::GetMaxPlayers( ); ++i )
	{
		const auto entity = CClientEntityList::GetEntity< CSPlayer* >( i );
		if ( !entity->is_valid( ) || entity->team( ) == globals::localplayer->team( ) )
			continue;
		
		const auto position = entity->position( );
		const auto distance = ( position - globals::localplayer->position( ) ).magnitude( );

		if ( distance < cdist )
		{
			cdist = distance;
			cplayer = i;
		}
	}

	if ( cplayer )
	{
		// const auto info = CClientState::GetPlayerInfo( cplayer );
		const auto entity = CClientEntityList::GetEntity< CSPlayer* >( cplayer );

		const auto viewangles = CClientState::GetViewAngles( );
		const auto aimpunch = memory::read<Vector3>( uintptr_t(globals::localplayer) + offsets::aimpunch ) * 2;

		const auto player_head = entity->get_bone( 8 );
		const auto head = globals::localplayer->position( ) + memory::read< Vector3 >( uintptr_t( globals::localplayer ) + offsets::view_offset );

		const auto origin = player_head - head;

		const auto yaw = atan2f( origin.y, origin.x ) * ( 180 / std::numbers::pi_v< float > );
		const auto pitch = atan2f( -origin.z, std::hypot( origin.x, origin.y ) ) * ( 180 / std::numbers::pi_v< float > );

		memory::write< Vector3 >( CClientState::Get( ) + offsets::angles, Vector3( pitch, yaw, 0.f ) - aimpunch );
		//std::cout << pitch << '\n';
		//std::cout << "Closest entity: " << info.name << '\n' << "Health: " << CClientEntityList::GetEntity<CSPlayer>(cplayer).health() << '\n';
	}
	*/
}