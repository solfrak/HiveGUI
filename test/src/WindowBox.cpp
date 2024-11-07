//
// Created by samuel on 11/6/24.
//
#include <gtest/gtest.h>

#include <hivegui.h>
using namespace hive::gui;

bool checkRectangleCommand(RenderCommand &command, int x, int y, int w, int h)
{
	return command.rect.x == x && command.rect.y == y && command.rect.w == w && command.rect.h == h;
}

TEST(WindowBox, RenderCommandShouldReturnRectangle)
{
	HiveGuiContext* ctx = Initialize();

	BeginFrame(ctx);
	{
		BeginWindow(ctx, "MyWindow", {0, 0, 300, 400});
		{
		}
		EndWindow(ctx);
	}
	EndFrame(ctx);

	auto commands = getRenderCommands(ctx);
	EXPECT_EQ(commands.size(), 2);

	auto first_command = commands[0];
	auto second_command = commands[1];

	EXPECT_EQ(first_command.type, hive::gui::PrimitiveType::Rectangle);
	EXPECT_EQ(second_command.type, hive::gui::PrimitiveType::Rectangle);

	EXPECT_TRUE(checkRectangleCommand(first_command, 0, 0, 300, 400));
	EXPECT_TRUE(checkRectangleCommand(second_command, 0, 0, 300, 20));

	Shutdown(ctx);
}

TEST(WindowBox, RenderCommand2)
{
	HiveGuiContext* ctx = Initialize();

	BeginFrame(ctx);
	{
		BeginWindow(ctx, "MyWindow", {10, 10, 300, 400});
		{
			BeginWindow(ctx, "MyWindow2", {10, 10, 10, 10});
			{

			}
			EndWindow(ctx);
		}
		EndWindow(ctx);
	}
	EndFrame(ctx);

	auto commands = getRenderCommands(ctx);
	EXPECT_EQ(commands.size(), 4);

	auto first_command = commands[0];
	auto second_command = commands[2];

	EXPECT_EQ(first_command.type, hive::gui::PrimitiveType::Rectangle);
	EXPECT_EQ(second_command.type, hive::gui::PrimitiveType::Rectangle);

	EXPECT_TRUE(checkRectangleCommand(first_command, 10, 10, 300, 400));
	EXPECT_TRUE(checkRectangleCommand(second_command, 20, 20, 10, 10));

	Shutdown(ctx);
}
