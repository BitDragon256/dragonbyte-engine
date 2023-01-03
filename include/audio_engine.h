#include "engines.h"

namespace dragonbyte_engine
{

	class AudioEngine : public Engine
	{
	public:
		void initialize() override;
		void tick() override;
		void destruct() override;

	};

} // namespace dragonbyte_engine