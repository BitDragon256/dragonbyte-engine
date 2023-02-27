#pragma once

#include <string>
#include <vector>

namespace dragonbyte_engine
{

	struct ConfigValue
	{
		std::string value;

		inline int to_int() { return std::stoi(value); };
		inline double to_double() { return std::stod(value); };
	};

	class FileEngine
	{
	public:
		void tick();
		void create();

		ConfigValue get_config_value(const std::string section, const std::string key);

		static std::vector<char> read_file(const std::string& a_krFilename);

	};

} // namespace dragonbyte_engine