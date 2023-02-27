#include "file_engine.h"

#include <fstream>
#include <stdexcept>

namespace dragonbyte_engine
{

	void FileEngine::create()
	{
	
	}
	void FileEngine::tick()
	{

	}

	std::vector<char> FileEngine::read_file(const std::string& a_krFilename)
	{
		std::ifstream file(a_krFilename, std::ios::ate | std::ios::binary);

		if (!file.is_open())
		{
			throw std::runtime_error("Failed to open file!");
		}

		size_t fileSize = static_cast<size_t>(file.tellg());
		std::vector<char> buffer( fileSize );

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();
		return buffer;
	}

} // namespace dragonbyte_engine