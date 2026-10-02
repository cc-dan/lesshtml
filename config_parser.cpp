#include <string>
#include <stdexcept>

#include "config_parser.h"

std::string get_component_name(std::ifstream &f)
{
	std::string name;

	char c;
	while (f.get(c))
	{
		switch (c)
		{
			case ' ':
			case '\n':
			case '\t':
			case '{':
				return name;
			default:
				name += c;
				break;
		}
	}

	throw std::runtime_error("expected opening of bracket after name");
}

std::string get_component(std::ifstream &f)
{
	std::string component;

	char c;
	while (f.get(c))
	{
		switch (c)
		{
			case '\n':
			case '\t':
				break;
			case '}':
				return component;
			default:
				component += c;
				break;
		}
	}

	throw std::runtime_error("expected closing of bracket after component");
}

void parse(std::ifstream &f)
{
	std::string last_component_name;

	char c;
	while (f.get(c))
	{
		switch (c)
		{
			case ' ':
			case '\n':
			case '\t':
				continue;
			case '{':
				if (last_component_name.empty())
					throw std::runtime_error("expected component name");
				components.insert_or_assign(last_component_name, get_component(f));
				break;
			default:
				f.unget();
				last_component_name = get_component_name(f);
				break;
		}
	}
}
