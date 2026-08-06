#include <string>
#include <cctype>
#include <span>
#include <iostream>
#include <sstream>

#include "html_parser.h"
#include "config_parser.h"

void read_component_name(std::istream &f, std::ostream &out)
{
	std::string name;

	char c;
	while (f.get(c))
	{
		if (c == '>')
			break;

		name += c;
	}

	const auto &component = components.find(name);
	if (component != components.end())
	{
		std::istringstream raw(component->second);
		std::ostringstream processed;
		process(raw, processed);

		for (const char &character : processed.view())
		{
			if (character == '\n' || character == '\t')
				continue;
			out.put(character);
		}
	}
	else
		throw std::runtime_error("couldn't find component \"" + name + "\"");
}

void read_tag_name(std::istream &f, std::ostream &out)
{
	std::string cached_tag_opening = "<";

	char c;
	f.get(c);
	cached_tag_opening += c;

	if (c != '!')
	{
		out.write(cached_tag_opening.c_str(), cached_tag_opening.size());
		return;
	}

	std::string name;
	while (f.get(c))
	{
		cached_tag_opening += c;

		if (c == '>')
		{
			out.write(cached_tag_opening.c_str(), cached_tag_opening.size());
			return;
		}
		else if (c == ' ' and name == "component")
		{
			read_component_name(f, out);
			return;
		}

		name += c;
	}
}

void process(std::istream &f, std::ostream &out)
{
	char c;
	while (f.get(c))
	{
		switch (c)
		{
			case '<':
				read_tag_name(f, out);
				break;
			default:
				if (c == '\n' || c == '\t')
					break;
				out.put(c);
				break;
		}
	}
}
