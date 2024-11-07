//
// Created by samuel on 11/6/24.
//
#pragma once
#include <cstdint>

namespace hive::gui
{
	enum class PrimitiveType
	{
		Rectangle, Text, Image
	};

	struct Color
	{
		uint8_t r, g, b, a;
	};

	struct RectanglePrimitive
	{
		int x, y, w, h;
		Color color;
	};

	struct		TextPrimitive
	{
		int x, y;
		int fontSize;
		const char* text;
		Color color;
	};

	struct ImagePrimitive
	{

	};
}
