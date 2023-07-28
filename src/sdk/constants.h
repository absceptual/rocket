#pragma once

#include <Windows.h>

namespace constants
{
	inline DWORD pid{ };
	inline HANDLE handle{ };
}

namespace offsets
{
	// client
	constexpr size_t localplayer = 0xDEA98C;
	constexpr size_t entitylist = 0x4DFFF7C;
	constexpr size_t position = 0x138;
	constexpr size_t health = 0x100;
	constexpr size_t view_offset = 0x108;
	constexpr size_t team = 0xF4;
	constexpr size_t dormant = 0xED;
	constexpr size_t lifestate = 0x25F;
	constexpr size_t bonematrix = 0x26A8;
	constexpr size_t aimpunch = 0x303C;

	// engine
	constexpr size_t clientstate = 0x59F19C;
	constexpr size_t max_players = 0x388;
	constexpr size_t playerinfo = 0x52C0;
	constexpr size_t angles = 0x4D90;
}

