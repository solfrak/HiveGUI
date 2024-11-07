#include "hivegui.h"

#include <string>
#include <vector>
#include <functional>
#include <stack>
#include <cassert>

namespace hive::gui
{
	class HiveGuiContext
	{
	public:
		std::stack<Container*> m_container_stack;
		std::unordered_map<size_t, Container*> m_container_pool;

		std::vector<RenderCommand> m_render_commands;
	};

}

size_t stringToHash(const std::string& str)
{
	constexpr std::hash<std::string> hashFunction;
	return hashFunction(str);
}

hive::gui::Container* getContainer(hive::gui::HiveGuiContext *context, size_t id)
{
	hive::gui::Container *value;
	if(context->m_container_pool.find(id) != context->m_container_pool.end())
	{
		value =  context->m_container_pool.at(id);
	}
	else
	{
		hive::gui::Container* container = new hive::gui::Container();
		context->m_container_pool[id] = container;
		value = container;
	}

	return value;

}

hive::gui::HiveGuiContext* hive::gui::Initialize()
{
	return new HiveGuiContext();
}

void hive::gui::Shutdown(HiveGuiContext* context)
{
	for (auto [id, container] : context->m_container_pool)
	{
		delete container;
	}

	delete context;
}

void hive::gui::BeginFrame(HiveGuiContext* context)
{
	context->m_render_commands.clear();
}

void hive::gui::EndFrame(HiveGuiContext* context)
{
	assert(context->m_container_stack.empty());
}

void hive::gui::BeginWindow(HiveGuiContext* context, const char* title, Rectangle bounds)
{
	//Fetch the container by it's ID
	auto container_id = stringToHash(title);
	Container *container = getContainer(context,container_id);

	//If the container was not set
	if(container->rect.width == 0)
	{
		container->rect = bounds;
		//Update Container position with parent if there is
		if (!context->m_container_stack.empty())
		{
			auto parent = context->m_container_stack.top();
			container->rect.x += parent->rect.x;
			container->rect.y += parent->rect.y;
		}
	}


	context->m_container_stack.push(container);

	//Add the command to render the Window
	RenderCommand border_command;
	border_command.type = PrimitiveType::Rectangle;
	//TODO replace the color by the context style color for box
	border_command.rect = {container->rect.x - 1, container->rect.y - 1, container->rect.width + 2, container->rect.height + 2, {100, 100, 100, 255}};
	context->m_render_commands.emplace_back(border_command);


	RenderCommand box_command;
	box_command.type = PrimitiveType::Rectangle;
	//TODO replace the color by the context style color for box
	box_command.rect = {container->rect.x, container->rect.y, container->rect.width, container->rect.height, {50, 50, 50, 255}};
	context->m_render_commands.emplace_back(box_command);

	RenderCommand header_command;
	header_command.type = PrimitiveType::Rectangle;
	//TODO replace the color by the context style color for header
	//TODO replace the header height by style for header
	header_command.rect = {container->rect.x, container->rect.y, container->rect.width, 20, {10, 10, 10, 255}};
	context->m_render_commands.emplace_back(header_command);


	RenderCommand text_command;
	text_command.type = PrimitiveType::Text;
	//TODO replace the text font size and adjustement with the style for the header text
	text_command.text = {container->rect.x + 10, container->rect.y + 5, 10, title, {255, 255, 255, 255}};
	context->m_render_commands.emplace_back(text_command);
}

void hive::gui::EndWindow(HiveGuiContext* context)
{
	context->m_container_stack.pop();
}

std::vector<hive::gui::RenderCommand> hive::gui::getRenderCommands(HiveGuiContext* context)
{
	return context->m_render_commands;
}
