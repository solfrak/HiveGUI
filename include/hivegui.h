#pragma once

#include <stack>
#include <unordered_map>
#include <vector>

#include "UIprimitive.h"
namespace hive::gui
{

	struct RenderCommand
	{
		PrimitiveType type;
		union
		{
			RectanglePrimitive rect;
			TextPrimitive text;
			ImagePrimitive image;
		};
	};
	struct Rectangle
	{
		int x, y;
		int width, height;
	};

	struct Container
	{
		Rectangle rect;
	};

	class HiveGuiContext;


	HiveGuiContext* Initialize();
	void Shutdown(HiveGuiContext* context);

	void BeginFrame(HiveGuiContext* context);
	void EndFrame(HiveGuiContext* context);

	//Container
	void BeginWindow(HiveGuiContext* context, const char* title, Rectangle bounds);
	void EndWindow(HiveGuiContext* context);

	std::vector<RenderCommand> getRenderCommands(HiveGuiContext * context);



}
