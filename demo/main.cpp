//
// Created by samuel on 11/6/24.
//

#include <raylib.h>

#include "hivegui.h"
#include <random>
#include <iostream>

int main()
{
	InitWindow(800, 600, "Hello World");

	auto ctx = hive::gui::Initialize();
	std::random_device rd;                     // Obtain a random number from hardware
	std::mt19937 gen(rd());                    // Seed the generator
	std::uniform_int_distribution<uint8_t> dist(0, 255);  // Define the range [0, 255]


	while(!WindowShouldClose())
	{
		//UI
		hive::gui::BeginFrame(ctx);
		{
			BeginWindow(ctx, "MyWindow", {20, 20, 400, 300});
			BeginWindow(ctx, "Hello World", {20, 40, 100, 100});
			EndWindow(ctx);
			EndWindow(ctx);

		}
		EndFrame(ctx);


		//Rendering
		BeginDrawing();
		{
			ClearBackground(RAYWHITE);

			auto render_command = getRenderCommands(ctx);
			for (auto command : render_command)
			{
				switch (command.type)
				{
				case hive::gui::PrimitiveType::Rectangle:
					DrawRectangle(command.rect.x, command.rect.y, command.rect.w, command.rect.h, {
						              command.rect.color.r, command.rect.color.g, command.rect.color.b,
						              command.rect.color.a
					              });
					break;
				case hive::gui::PrimitiveType::Text:
					DrawText(command.text.text, command.text.x, command.text.y, command.text.fontSize, {
						         command.text.color.r, command.text.color.g, command.text.color.b, command.text.color.a
					         });
					break;
				case hive::gui::PrimitiveType::Image:
					std::cout << "Not supported" << std::endl;
					break;
				}
			}
		}
		EndDrawing();
	}

	hive::gui::Shutdown(ctx);
	CloseWindow();
}
