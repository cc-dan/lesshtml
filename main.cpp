#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdio>

#include "config_parser.h"
#include "html_parser.h"

int main(int argc, const char *argv[])
{
	const std::filesystem::path src("src");
	if (not std::filesystem::is_directory(src))
	{
		std::puts("a directory \"src\" describing a website must exist");
		return 1;
	}

	const std::filesystem::path gen("gen");
	if (not std::filesystem::is_directory(gen))
		std::filesystem::create_directory(gen);

	const std::filesystem::path components_file_path("html_components");
	if (std::filesystem::is_regular_file(components_file_path))
	{
		std::ifstream f(components_file_path);
		if (!f.is_open())
			throw std::runtime_error("couldn't open html_components file");
		parse(f);
	}

	for (const auto &entry : std::filesystem::recursive_directory_iterator(src))
	{
		std::filesystem::path relative = std::filesystem::relative(entry.path(), src);
		if (entry.is_directory())
			std::filesystem::create_directories(gen / relative);
		else if (entry.is_regular_file())
		{
			bool is_html = entry.path().extension().compare(".html") == 0;
			bool is_css = not is_html and entry.path().extension().compare(".css") == 0;

			std::filesystem::create_directories(gen / relative.parent_path());

			if (is_html or is_css)
			{
				std::ifstream raw(entry.path());
				std::ofstream out(gen / relative);
				process(raw, out); // meant for html files, but can be used to minify css files as there's no syntax overlap
			}
			else
				std::filesystem::copy(entry.path(), gen / relative, std::filesystem::copy_options::update_existing);
		}
	}

	return 0;
}
