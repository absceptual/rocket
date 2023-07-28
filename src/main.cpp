#include <chrono>
#include <thread>
#include <numbers>

#include <include/il2cpp/il2cpp.h>

#include <src/sdk/vector.h>
#include <src/sdk/entitylist.h>
#include <src/sdk/entity.h>
#include <src/sdk/natives.h>

// Created with ReClass.NET 1.2 by KN4CK3R
class GameObject;
class BaseObject
{
public:
	char pad_0000[ 8 ]; //0x0000
	class BaseObject* next; //0x0008
	class GameObject* object; //0x0010
}; //Size: 0x0018


class GameObject
{
public:
	char pad_0000[ 84 ]; //0x0000
	uint16_t tag; //0x0054
	char pad_0056[ 18 ]; //0x0056
	char* name; //0x0068
	char pad_0070[ 56 ]; //0x0070
}; //Size: 0x00A8


class GameObjectManager
{
public:
	char pad_0000[ 24 ]; //0x0000
	class BaseObject* TaggedObjects; //0x0018
	void* LastActiveObject; //0x0020
	class BaseObject* ActiveObjects; //0x0028
}; //Size: 0x0030


/*
using vector = Vector3;
vector get_position( uint64_t transform_internal )
{
	transform_internal = memory::read<uint64_t>( transform_internal + 0x10 );
	if ( !transform_internal )
		return vector( );

	auto some_ptr = memory::read<uint64_t>( transform_internal + 0x38 );
	auto index = memory::read<int32_t>( transform_internal + 0x38 + sizeof( uint64_t ) );
	if ( !some_ptr )
		return vector( );

	auto relation_array = memory::read<uint64_t>( some_ptr + 0x18 );
	if ( !relation_array )
		return vector( );

	auto dependency_index_array = memory::read<uint64_t>( some_ptr + 0x20 );
	if ( !dependency_index_array )
		return vector( );

	__m128i temp_0;
	__m128 xmmword_1410D1340 = { -2.f, 2.f, -2.f, 0.f };
	__m128 xmmword_1410D1350 = { 2.f, -2.f, -2.f, 0.f };
	__m128 xmmword_1410D1360 = { -2.f, -2.f, 2.f, 0.f };
	__m128 temp_1;
	__m128 temp_2;
	auto temp_main = memory::read<__m128>( relation_array + index * 48 );
	auto dependency_index = memory::read<int32_t>( dependency_index_array + 4 * index );

	while ( dependency_index >= 0 )
	{
		auto relation_index = 6 * dependency_index;

		temp_0 = memory::read<__m128i>( relation_array + 8 * relation_index + 16 );
		temp_1 = memory::read<__m128>( relation_array + 8 * relation_index + 32 );
		temp_2 = memory::read<__m128>( relation_array + 8 * relation_index );

		__m128 v10 = _mm_mul_ps( temp_1, temp_main );
		__m128 v11 = _mm_castsi128_ps( _mm_shuffle_epi32( temp_0, 0 ) );
		__m128 v12 = _mm_castsi128_ps( _mm_shuffle_epi32( temp_0, 85 ) );
		__m128 v13 = _mm_castsi128_ps( _mm_shuffle_epi32( temp_0, -114 ) );
		__m128 v14 = _mm_castsi128_ps( _mm_shuffle_epi32( temp_0, -37 ) );
		__m128 v15 = _mm_castsi128_ps( _mm_shuffle_epi32( temp_0, -86 ) );
		__m128 v16 = _mm_castsi128_ps( _mm_shuffle_epi32( temp_0, 113 ) );
		__m128 v17 = _mm_add_ps(
			_mm_add_ps(
			_mm_add_ps(
			_mm_mul_ps(
			_mm_sub_ps(
			_mm_mul_ps( _mm_mul_ps( v11, xmmword_1410D1350 ), v13 ),
			_mm_mul_ps( _mm_mul_ps( v12, xmmword_1410D1360 ), v14 ) ),
			_mm_castsi128_ps( _mm_shuffle_epi32( _mm_castps_si128( v10 ), -86 ) ) ),
			_mm_mul_ps(
			_mm_sub_ps(
			_mm_mul_ps( _mm_mul_ps( v15, xmmword_1410D1360 ), v14 ),
			_mm_mul_ps( _mm_mul_ps( v11, xmmword_1410D1340 ), v16 ) ),
			_mm_castsi128_ps( _mm_shuffle_epi32( _mm_castps_si128( v10 ), 85 ) ) ) ),
			_mm_add_ps(
			_mm_mul_ps(
			_mm_sub_ps(
			_mm_mul_ps( _mm_mul_ps( v12, xmmword_1410D1340 ), v16 ),
			_mm_mul_ps( _mm_mul_ps( v15, xmmword_1410D1350 ), v13 ) ),
			_mm_castsi128_ps( _mm_shuffle_epi32( _mm_castps_si128( v10 ), 0 ) ) ),
			v10 ) ),
			temp_2 );

		temp_main = v17;
		dependency_index = memory::read<int32_t>( dependency_index_array + 4 * dependency_index );
	}

	return *reinterpret_cast< vector* >( &temp_main );
}
*/

int main()
{
	util::attach(L"RustClient.exe");
	il2cpp::init( );

	auto base = util::get_module_base(L"GameAssembly.dll");
	printf( "game assembly: 0x%llx\n", base );

	auto localplayer = BasePlayer::GetLocalPlayer( );
	auto inventory = localplayer->inventory( );
	auto belt = inventory->belt( );

	for ( int i = 0; i < belt->capacity( ); ++i )
	{
		auto item = belt->item( i );
		if ( !item )
			continue;

		if (item->id( ) == localplayer->held_item_id( ) )
			std::wcout << L"curent item: " << item->id() << '\n';
		else
			std::wcout << L"item: " << item->id( ) << '\n';

	}
	
	std::wcout << L"[offset less player name $$$$] " << localplayer->display_name( ).buffer << '\n';
	while (true)
	{
		if ( GetAsyncKeyState( VK_END ) & 1 )
			break;


		auto current_id = localplayer->held_item_id( );
		for ( int i = 0; i < belt->capacity( ); ++i )
		{
			auto item = belt->item( i );
			if ( !item )
				continue;

			if ( !( item->id( ) == current_id ) )
				continue;

			auto name = item->name( ).buffer;
			auto desc = item->description( ).buffer;

			if ( name && desc )
				std::wcout << name << L"\n\t" << desc << L"\n\n";
		}
		std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
		/*
		for ( int i = 0; i < EntityRealm::GetEntityCount( ); ++i )
		{
			auto entity = reinterpret_cast< BaseNetworkable* >( EntityRealm::GetEntity( i ) );
			auto prefab_name = entity->get_raw_prefab_name( );
			
			if ( prefab_name.length )
				std::wcout << prefab_name.buffer << '\n';

			//auto e = get_position( 0x00000266D5FF3E80 );
			//std::cout << e.x << e.y << e.z << '\n';
		}
		

		
		std::cout << '\n';
		
		*/
	}	
	
}


