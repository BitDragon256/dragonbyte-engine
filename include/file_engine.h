#include "engine.h"

#include <string>

namespace dragonbyte_engine
{

	struct ConfigValue
	{
		std::string value;

		inline int to_int() { return std::stoi(value); };
		inline double to_double() { return std::stod(value); };
	};

	class FileEngine : public Engine
	{
	public:
		void tick() override;

		ConfigValue get_config_value(const std::string section, const std::string key);

	};

} // namespace dragonbyte_engine