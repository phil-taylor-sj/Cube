#pragma once

namespace Levels
{
	enum class CellTypes
	{
		NONE,
		ROOM,
		EDGE_VOID,
		CORNER_VOID,
		BRIDGE_VOID
	};

	enum class CellSubtypes
	{
		NONE,
		UPPER_LEFT,
		UPPER_RIGHT,
		LOWER_LEFT,
		LOWER_RIGHT,
		UPPER_EDGE,
		LOWER_EDGE,
		LEFT_EDGE,
		RIGHT_EDGE,
		YELLOW,
		WHITE,
		GREEN,
		BLUE,
		RED

	};
}